#include "TLE92464_CommLayer.h"
#include "spi_ctrl.h"   // ?? spi_transfer(uint32_t msg) ????
#include <stdint.h>
#include <stdio.h>

#define TLE92464_SPI_ACTION_WRITE (0x1)
#define TLE92464_SPI_ACTION_READ  (0x0)

/*******************************************************************************
**                         CRC8_SAE_J1850 Function Definitions                **
*******************************************************************************/

uint8_t crc8_sae_j1850(uint32_t value) {
    uint8_t byte1 = (value >> 16) & 0xFF;
    uint8_t byte2 = (value >> 8)  & 0xFF;
    uint8_t byte3 = value & 0xFF;

    uint8_t data[3] = { byte3, byte2, byte1 };
    uint8_t crc = 0xFF;

    for (uint8_t i = 0; i < 3; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x1D;
            else
                crc <<= 1;
        }
    }
    return crc ^ 0xFF;
}

/*******************************************************************************
**                                Set Register                                **
*******************************************************************************/

uint32_t TLE92464_SetReg(uint16_t Address, uint32_t data) {
    uint32_t snd_msg = ((Address << 17) | (TLE92464_SPI_ACTION_WRITE << 16) | data);
    uint8_t crc = crc8_sae_j1850(snd_msg);
    snd_msg = ((uint32_t)crc << 24) | snd_msg;

    printf("[DEBUG] SPI TX (WRITE) = 0x%08X\n", snd_msg);

    uint32_t recv_msg = spi_transfer(snd_msg);

    printf("[DEBUG] SPI RX         = 0x%08X\n", recv_msg);
        usleep(100 * 1000);

    return recv_msg;
}

uint32_t TLE92464_GetReg(uint16_t Address, uint32_t *data) {
    uint32_t snd_msg = ((TLE92464_SPI_ACTION_READ << 17) | Address);
    uint8_t crc = crc8_sae_j1850(snd_msg);
    snd_msg = ((uint32_t)crc << 24) | snd_msg;

    printf("[DEBUG] SPI TX (READ)  = 0x%08X\n", snd_msg);

    uint32_t recv_msg = spi_transfer(snd_msg);

    printf("[DEBUG] SPI RX         = 0x%08X\n", recv_msg);

    *data = recv_msg;
        usleep(100 * 1000);
    return recv_msg;
}
