#ifndef SPI_CTRL_H
#define SPI_CTRL_H

#include <stdint.h>

void spi_init();
uint32_t spi_transfer(uint32_t tx_data);
void spi_cleanup();

#endif
