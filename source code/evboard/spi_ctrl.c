// spi_ctrl.c

#include "spi_ctrl.h"
#include "gpio_ctrl.h"        // <-- ?? CS ????

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>

static int spi_fd;
static const uint32_t SPI_SPEED = 250000;    // 250kHz

// ??? SPI?????? GPIO25 ???? CS
void spi_init(void) {


    spi_fd = open("/dev/spidev0.0", O_RDWR);
    if (spi_fd < 0) {
        perror("open /dev/spidev0.0");
        return;
    }

    // ?? SPI Mode1 (CPOL=0, CPHA=1)
    uint8_t mode = SPI_MODE_1;
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, &mode) < 0) {
        perror("SPI_IOC_WR_MODE");
    }

    // ?? 8 bits per word
    uint8_t bits = 8;
    if (ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0) {
        perror("SPI_IOC_WR_BITS_PER_WORD");
    }

    // ????????
    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_SPEED) < 0) {
        perror("SPI_IOC_WR_MAX_SPEED_HZ");
    }
}

// ?? GPIO25 ??? CS ??? 32-bit?4 ?????
uint32_t spi_transfer(uint32_t tx_data) {
    uint8_t tx_buf[4] = {
        (tx_data >> 24) & 0xFF,
        (tx_data >> 16) & 0xFF,
        (tx_data >>  8) & 0xFF,
        (tx_data >>  0) & 0xFF
    };
    uint8_t rx_buf[4] = {0};

    struct spi_ioc_transfer tr = {
        .tx_buf        = (unsigned long)tx_buf,
        .rx_buf        = (unsigned long)rx_buf,
        .len           = 4,    // 4 ?? = 32 ?
        .bits_per_word = 8,    // ???? 8 bit
        .speed_hz      = SPI_SPEED,
        .delay_usecs   = 0,
    };

    // ???? CS
    gpio_set_cs(0);
    // ??? 4 ??
    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr) < 0) {
        perror("SPI transfer failed");
    }
    // ???? CS
    gpio_set_cs(1);

    // ?????????
    usleep(2);

    // ?? 32-bit ????????
    return ((uint32_t)rx_buf[0] << 24) |
           ((uint32_t)rx_buf[1] << 16) |
           ((uint32_t)rx_buf[2] <<  8) |
           ((uint32_t)rx_buf[3]      );
}

// ??
void spi_cleanup(void) {
    close(spi_fd);
    gpio_cleanup();
}


