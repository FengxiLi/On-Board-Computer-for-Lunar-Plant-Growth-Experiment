// main.c
#include <stdio.h>
#include <time.h>

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

        // Read temperature, pressure, humidity from MS8607
        float temp1, press, hum1;
        ms8607_read(&temp1, &press, &hum1);

        // Read CO2, temperature, humidity from SCD41
        int co2;
        float temp2, hum2;
        scd41_read(&co2, &temp2, &hum2);

        // Print all measurements with timestamp
        printf("[%s] Geiger pulses: %4d | MS8607 T: %.2f C P: %.2f mbar H: %.2f%% | "
               "SCD41 CO2: %4d ppm T: %.2f C H: %.2f%%\n",
               ts, pulses, temp1, press, hum1, co2, temp2, hum2);
        fflush(stdout);

        // Write latest values for GUI (overwrite)
        FILE *fp = fopen("/tmp/sensor_data.txt", "w");
        if (fp) {
            fprintf(fp, "%s,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f\n",
                    ts, pulses, temp1, press, hum1, co2, temp2, hum2);
            fclose(fp);
        }

        // Append to CSV for historical data (24-hour graph)
        FILE *log = fopen("sensor_data.csv", "a");
        if (log) {
            fprintf(log, "%s,%d,%.2f,%.2f,%.2f,%d,%.2f,%.2f\n",
                    ts, pulses, temp1, press, hum1, co2, temp2, hum2);
            fclose(log);
        }
    }

    geiger_cleanup();
    ms8607_cleanup();
    scd41_cleanup();
    return 0;
}
