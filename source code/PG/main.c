// main.c
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>   // mkdir
#include <unistd.h>     // access()

#include "geiger_counter.h"
#include "ms8607.h"
#include "scd41.h"

int main(void) {
    geiger_init();
    ms8607_init();
    scd41_init();

    printf("PG project started. Press Ctrl+C to exit.\n");

    while (1) {
        time_t now = time(NULL);
        char ts[32];
        strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", localtime(&now));

        // Count Geiger pulses for 60 seconds
        int pulses = geiger_count_interval(60);

        // Read MS8607 sensor
        float temp1, press, hum1;
        ms8607_read(&temp1, &press, &hum1);

        // Read SCD41 sensor
        int co2;
        float temp2, hum2;
        scd41_read(&co2, &temp2, &hum2);

        // Print all measurements
        printf("[%s] Geiger pulses: %4d | MS8607 T: %.2f C P: %.2f mbar H: %.2f%% | "
               "SCD41 CO2: %4d ppm T: %.2f C H: %.2f%%\n",
               ts, pulses, temp1, press, hum1, co2, temp2, hum2);
        fflush(stdout);

        // --- Overwrite GUI real-time data file ---
        FILE *fp = fopen("/tmp/sensor_data.txt", "w");
        if (fp) {
            fprintf(fp, "%s,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f\n",
                    ts, pulses, temp1, press, hum1, co2, temp2, hum2);
            fclose(fp);
        }

        // --- Append to total history ---
        FILE *total_log = fopen("sensor_data.csv", "a");
        if (total_log) {
            fprintf(total_log, "%s,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f\n",
                    ts, pulses, temp1, press, hum1, co2, temp2, hum2);
            fclose(total_log);
        }

        // --- Append to daily log in logs/YYYY-MM-DD.csv ---
        // Create logs/ directory if needed
        if (access("logs", F_OK) != 0) {
            mkdir("logs", 0755);
        }

        char log_path[64];
        strftime(log_path, sizeof(log_path), "logs/%Y-%m-%d.csv", localtime(&now));
        FILE *daily_log = fopen(log_path, "a");
        if (daily_log) {
            fprintf(daily_log, "%s,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f\n",
                    ts, pulses, temp1, press, hum1, co2, temp2, hum2);
            fclose(daily_log);
        }
    }

    geiger_cleanup();
    ms8607_cleanup();
    scd41_cleanup();
    return 0;
}

