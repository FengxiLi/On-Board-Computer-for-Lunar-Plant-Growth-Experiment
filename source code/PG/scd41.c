// scd41.c
#include "scd41.h"
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS         "/dev/i2c-1"
#define SCD41_ADDR      0x62
#define CMD_START_MEAS  0x21B1
#define CMD_READ_MEAS   0xEC05

static int fd_scd;

/** Open I²C bus and send start-measurement command */
void scd41_init(void) {
    fd_scd = open(I2C_BUS, O_RDWR);
    ioctl(fd_scd, I2C_SLAVE, SCD41_ADDR);
    uint8_t cmd[2] = { CMD_START_MEAS >> 8, CMD_START_MEAS & 0xFF };
    write(fd_scd, cmd, 2);
    sleep(5);  // wait for first measurement
}

/**
 * Read one measurement from SCD41:
 *   - Issue read command
 *   - Parse CO2, temperature, and humidity
 */
int scd41_read(int *co2_ppm, float *temp_c, float *hum_pct) {
    ioctl(fd_scd, I2C_SLAVE, SCD41_ADDR);
    uint8_t cmd[2] = { CMD_READ_MEAS >> 8, CMD_READ_MEAS & 0xFF }, buf[9];
    write(fd_scd, cmd, 2);
    usleep(10000);
    if (read(fd_scd, buf, 9) != 9) return -1;
    *co2_ppm = (buf[0]<<8) | buf[1];
    uint16_t tr = (buf[3]<<8) | buf[4];
    uint16_t hr = (buf[6]<<8) | buf[7];
    *temp_c  = -45.0f + 175.0f * (tr / 65536.0f);
    *hum_pct = 100.0f * (hr / 65536.0f);
    return 0;
}

/** Close the I²C file descriptor */
void scd41_cleanup(void) {
    close(fd_scd);
}
