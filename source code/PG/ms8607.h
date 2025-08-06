// ms8607.h
#ifndef MS8607_H
#define MS8607_H

/** Initialize the MS8607: reset sensor and read calibration data */
void ms8607_init(void);

/**
 * Read MS8607 sensor measurements:
 *  @param temp_c      returns temperature in degrees Celsius
 *  @param press_mbar  returns pressure in millibars
 *  @param hum_pct     returns relative humidity in percent
 */
void ms8607_read(float *temp_c, float *press_mbar, float *hum_pct);

/** Close the I2C file descriptor */
void ms8607_cleanup(void);

#endif // MS8607_H
