/*
 * TLE92464_RegLayer.h
 *
 *  Created on: 24-Sep-2024
 *      Author: maheshm
 */

#ifndef TLE92464_REGLAYER_H_
#define TLE92464_REGLAYER_H_
#include<stdint.h>

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "TLE92464_RegLayer.h"

/*******************************************************************************
**                          Central Macro Declarations                         **
*******************************************************************************/
#define CH_CTRL_ADDR           (0x00)
#define GLOBAL_CONFIG_ADDR     (0x02)
#define GLOBAL_DIAG0_ADDR      (0x03)
#define GLOBAL_DIAG1_ADDR      (0x04)
#define GLOBAL_DIAG2_ADDR      (0x05)
#define VBAT_TH_ADDR           (0x06)
#define FB_FRZ_ADDR            (0x07)
#define FB_UPD_ADDR            (0x08)
#define WD_RELOAD_ADDR         (0x09)
#define DIAG_ERR_CHGR0_ADDR    (0x0A)
#define DIAG_ERR_CHGR1_ADDR    (0x0B)
#define DIAG_WARN_CHGR0_ADDR   (0x10)
#define DIAG_WARN_CHGR1_ADDR   (0x11)
#define FAULT_MASK0_ADDR       (0x16)
#define FAULT_MASK1_ADDR       (0x17)
#define FAULT_MASK2_ADDR       (0x18)
#define CLK_DIV_ADDR           (0x19)
#define SFF_BIST_ADDR          (0x3F)
#define ICVID_ADDR             (0x0200)
#define PIN_STAT_ADDR          (0x0201)
#define FB_STAT_ADDR           (0x0202)
#define FB_VOLTAGE1_ADDR       (0x0203)
#define FB_VOLTAGE2_ADDR       (0x0204)

/*******************************************************************************
**                          Channel Macro Declarations                         **
*******************************************************************************/
#define SETPOINT_ADDR          (0x40)
#define CTRL_ADDR              (0x41)
#define PERIOD_ADDR            (0x42)
#define INTEGRATOR_LIMIT_ADDR  (0x43)
#define DITHER_CLK_DIV_ADDR    (0x44)
#define DITHER_STEP_ADDR       (0x45)
#define DITHER_CTRL_ADDR       (0x46)
#define CH_CONFIG_ADDR         (0x47)
#define MODE_ADDR              (0x4C)
#define TON_ADDR               (0x4D)
#define CTRL_INT_THRESH_ADDR   (0x4E)
#define FB_DC_ADDR             (0x240)
#define FB_VBAT_ADDR           (0x241)
#define FB_I_AVG_ADDR          (0x242)
#define FB_IMIN_IMAX_ADDR      (0x243)
#define FB_I_AVG_s16_ADDR      (0x244)
#define FB_INT_THRESH_ADDR     (0x245)
#define FB_PERIOD_MIN_MAX_ADDR (0x246)

/*******************************************************************************
**                        Central Function Declarations                        **
*******************************************************************************/
void TLE92464_Init(void);

void TLE92464_Set_CH_CTRL(uint16_t data);
uint16_t TLE92464_Get_CH_CTRL(void);
void TLE92464_Set_GLOBAL_CONFIG(uint16_t data);
uint16_t TLE92464_Get_GLOBAL_CONFIG(void);
void TLE92464_Set_GLOBAL_DIAG0(uint16_t data);
uint16_t TLE92464_Get_GLOBAL_DIAG0(void);
void TLE92464_Set_GLOBAL_DIAG1(uint16_t data);
uint16_t TLE92464_Get_GLOBAL_DIAG1(void);
void TLE92464_Set_GLOBAL_DIAG2(uint16_t data);
uint16_t TLE92464_Get_GLOBAL_DIAG2(void);
void TLE92464_Set_VBAT_TH(uint16_t data);
uint16_t TLE92464_Get_VBAT_TH(void);
void TLE92464_Set_FB_FRZ(uint16_t data);
uint16_t TLE92464_Get_FB_FRZ(void);
void TLE92464_Set_FB_UPD(uint16_t data);
uint16_t TLE92464_Get_FB_UPD(void);
void TLE92464_Set_WD_RELOAD(uint16_t data);
uint16_t TLE92464_Get_WD_RELOAD(void);
void TLE92464_Set_DIAG_ERR_CHGR0(uint16_t data);
uint16_t TLE92464_Get_DIAG_ERR_CHGR0(void);
void TLE92464_Set_DIAG_ERR_CHGR1(uint16_t data);
uint16_t TLE92464_Get_DIAG_ERR_CHGR1(void);
void TLE92464_Set_DIAG_WARN_CHGR0(uint16_t data);
uint16_t TLE92464_Get_DIAG_WARN_CHGR0(void);
void TLE92464_Set_DIAG_WARN_CHGR1(uint16_t data);
uint16_t TLE92464_Get_DIAG_WARN_CHGR1(void);
void TLE92464_Set_FAULT_MASK0(uint16_t data);
uint16_t TLE92464_Get_FAULT_MASK0(void);
void TLE92464_Set_FAULT_MASK1(uint16_t data);
uint16_t TLE92464_Get_FAULT_MASK1(void);
void TLE92464_Set_FAULT_MASK2(uint16_t data);
uint16_t TLE92464_Get_FAULT_MASK2(void);
void TLE92464_Set_CLK_DIV(uint16_t data);
uint16_t TLE92464_Get_CLK_DIV(void);
void TLE92464_Set_SFF_BIST(uint16_t data);
uint16_t TLE92464_Get_SFF_BIST(void);
uint16_t TLE92464_Get_ICVID(void);
uint16_t TLE92464_Get_PIN_STAT(void);
uint32_t TLE92464_Get_FB_STAT(void);
uint32_t TLE92464_Get_FB_VOLTAGE1(void);
uint32_t TLE92464_Get_FB_VOLTAGE2(void);

/*******************************************************************************
**                        Channel Function Declarations                        **
*******************************************************************************/
void TLE92464_Set_SETPOINT(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_SETPOINT(uint8_t Channel);
void TLE92464_Set_CTRL(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_CTRL(uint8_t Channel);
void TLE92464_Set_PERIOD(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_PERIOD(uint8_t Channel);
void TLE92464_Set_INTEGRATOR_LIMIT(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_INTEGRATOR_LIMIT(uint8_t Channel);
void TLE92464_Set_DITHER_CLK_DIV(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_DITHER_CLK_DIV(uint8_t Channel);
void TLE92464_Set_DITHER_STEP(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_DITHER_STEP(uint8_t Channel);
void TLE92464_Set_DITHER_CTRL(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_DITHER_CTRL(uint8_t Channel);
void TLE92464_Set_CH_CONFIG(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_CH_CONFIG(uint8_t Channel);
void TLE92464_Set_MODE(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_MODE(uint8_t Channel);
void TLE92464_Set_TON(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_TON(uint8_t Channel);
void TLE92464_Set_CTRL_INT_THRESH(uint8_t Channel, uint16_t data);
uint16_t TLE92464_Get_CTRL_INT_THRESH(uint8_t Channel);
uint32_t TLE92464_Get_FB_DC(uint8_t Channel);
uint32_t TLE92464_Get_FB_VBAT(uint8_t Channel);
uint32_t TLE92464_Get_FB_I_AVG(uint8_t Channel);
uint32_t TLE92464_Get_FB_IMIN_IMAX(uint8_t Channel);
uint32_t TLE92464_Get_FB_I_AVG_s16(uint8_t Channel);
uint32_t TLE92464_Get_FB_INT_THRESH(uint8_t Channel);
uint32_t TLE92464_Get_FB_PERIOD_MIN_MAX(uint8_t Channel);

/*******************************************************************************
**                        Channel Selection Declarations                        **
*******************************************************************************/
uint16_t TLE92464_CHANNEL_SELECT(uint8_t Channel, uint16_t ADDR);


#endif /* TLE92464_REGLAYER_H_ */
