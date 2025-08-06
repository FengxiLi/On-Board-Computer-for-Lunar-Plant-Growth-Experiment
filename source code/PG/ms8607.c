// ms8607.c
#include "ms8607.h"
#include <stdio.h>         // perror
#include <unistd.h>        // usleep, close
#include <stdint.h>        // fixed-width types
#include <fcntl.h>         // open
#include <sys/ioctl.h>     // ioctl
#include <linux/i2c-dev.h> // I2C_SLAVE

#define I2C_BUS         "/dev/i2c-1"
#define ADDR_PRESSURE   0x76
#define ADDR_HUMIDITY   0x40

#define CMD_RESET       0x1E
#define CMD_CONV_D1     0x48
#define CMD_CONV_D2     0x58
#define CMD_ADC_READ    0x00
#define CMD_PROM_READ   0xA0
#define CMD_HUM_NOHOLD  0xE5

static int     fd_i2c;
static uint16_t C[7];

/** Send a single command byte over I2C */
static int8_t write_i2c_cmd(uint8_t cmd) {
    return write(fd_i2c, &cmd, 1) == 1 ? 0 : -1;
}

/** Read a 16-bit calibration word from PROM at index idx */
static uint16_t read_prom(int idx) {
    uint8_t buf[2];
    uint8_t cmd = CMD_PROM_READ + (idx * 2);
    write_i2c_cmd(cmd);
    read(fd_i2c, buf, 2);
    return (uint16_t)((buf[0] << 8) | buf[1]);
}

/** Read a 24-bit ADC conversion result */
static uint32_t read_adc(void) {
    uint8_t buf[3];
    write_i2c_cmd(CMD_ADC_READ);
    read(fd_i2c, buf, 3);
    return ((uint32_t)buf[0] << 16) | ((uint32_t)buf[1] << 8) | buf[2];
}

/** Initialize the MS8607 sensor and read calibration constants */
void ms8607_init(void) {
    fd_i2c = open(I2C_BUS, O_RDWR);
    if (fd_i2c < 0) {
        perror("ms8607: open I2C bus");
        return;
    }
    if (ioctl(fd_i2c, I2C_SLAVE, ADDR_PRESSURE) < 0) {
        perror("ms8607: select pressure sensor");
        close(fd_i2c);
        return;
    }

    /* Reset the sensor */
    write_i2c_cmd(CMD_RESET);
    usleep(3000);

    /* Read calibration constants C[0]..C[6] */
    for (int i = 0; i < 7; i++) {
        C[i] = read_prom(i);
    }
}

/**
 * Read temperature, pressure and humidity:
 *  - Perform pressure & temperature conversions
 *  - Compute compensated values
 *  - Read humidity in no-hold mode
 */
void ms8607_read(float *temp_c, float *press_mbar, float *hum_pct) {
    /* Select pressure sensor */
    ioctl(fd_i2c, I2C_SLAVE, ADDR_PRESSURE);

    /* Start D1 (pressure) conversion, then read */
    write_i2c_cmd(CMD_CONV_D1);
    usleep(10000);
    uint32_t D1 = read_adc();

    /* Start D2 (temperature) conversion, then read */
    write_i2c_cmd(CMD_CONV_D2);
    usleep(10000);
    uint32_t D2 = read_adc();

    /* Calculate temperature difference and actual temperature */
    int32_t dT   = (int32_t)D2 - ((int32_t)C[5] << 8);
    int32_t TEMP = 2000 + (int32_t)(((int64_t)dT * C[6]) >> 23);

    /* Compute offset and sensitivity with corrected shifts */
    int64_t OFF  = ((int64_t)C[2] << 17) + (((int64_t)dT * C[4]) >> 6);
    int64_t SENS = ((int64_t)C[1] << 16) + (((int64_t)dT * C[3]) >> 7);

    /* Calculate actual pressure in Pa */
    int64_t P_pa = (((int64_t)D1 * SENS) >> 21) - OFF;
    int32_t P    = (int32_t)(P_pa >> 15);

    /* Convert to user units */
    *temp_c     = TEMP / 100.0f;  // degrees Celsius
    *press_mbar = P / 100.0f;     // millibar

    /* Select humidity sensor */
    ioctl(fd_i2c, I2C_SLAVE, ADDR_HUMIDITY);

    /* Trigger humidity conversion and read */
    uint8_t cmd = CMD_HUM_NOHOLD;
    write(fd_i2c, &cmd, 1);
    usleep(50000);

    uint8_t buf[3];
    read(fd_i2c, buf, 3);
    uint16_t rh_raw = ((uint16_t)buf[0] << 8) | (buf[1] & 0xFC);
    *hum_pct = ((125.0f * rh_raw) / 65536.0f) - 6.0f;
}

/** Clean up by closing the I2C file descriptor */
void ms8607_cleanup(void) {
    if (fd_i2c >= 0) {
        close(fd_i2c);
        fd_i2c = -1;
    }
}

