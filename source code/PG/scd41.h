// scd41.h
#ifndef SCD41_H
#define SCD41_H

/** Initialize the SCD41 sensor (start continuous measurement) */
void scd41_init(void);

/**
 * Read SCD41 sensor data:
 *  @param co2_ppm  returns CO2 concentration in ppm
 *  @param temp_c   returns temperature in degrees Celsius
 *  @param hum_pct  returns humidity in percent
 *  @return 0 on success, -1 on failure
 */
int scd41_read(int *co2_ppm, float *temp_c, float *hum_pct);

/** Close the I²C file descriptor */
void scd41_cleanup(void);

#endif // SCD41_H
