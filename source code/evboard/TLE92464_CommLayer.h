#ifndef TLE92464_COMMLAYER_H
#define TLE92464_COMMLAYER_H

#include <stdint.h>

// SPI???????? spi_ctrl.c ???
uint32_t TLE92464_SetReg(uint16_t Address, uint32_t data);
uint32_t TLE92464_GetReg(uint16_t Address, uint32_t *data);

#endif // TLE92464_COMMLAYER_H
