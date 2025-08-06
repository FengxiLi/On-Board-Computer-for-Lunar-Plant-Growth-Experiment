/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "TLE92464_RegLayer.h"
#include "TLE92464_CommLayer.h"
#include <stdint.h>

/*******************************************************************************
**                        Global Variable Definitions                         **
*******************************************************************************/
uint32_t glob_status;

/*******************************************************************************
**                        Channel Selection Definitions                         **
*******************************************************************************/
uint16_t TLE92464_CHANNEL_SELECT(uint8_t Channel, uint16_t ADDR){
    switch(Channel){
        case 0 : return (0x40 | ADDR);
                       break;
        case 1 : return (0x50 | ADDR);
                       break;
        case 2 : return (0x60 | ADDR);
                       break;
        case 3 : return (0x70 | ADDR);
                       break;
        default: return (0x40 | ADDR);
    }
    
}

/*******************************************************************************
**                         Central Function Definitions                       **
*******************************************************************************/
void TLE92464_Set_CH_CTRL(uint16_t data){
    glob_status = TLE92464_SetReg(CH_CTRL_ADDR, data);
}

uint16_t TLE92464_Get_CH_CTRL(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(CH_CTRL_ADDR, &data);
    return data;
}

void TLE92464_Set_GLOBAL_CONFIG(uint16_t data){
    glob_status = TLE92464_SetReg(GLOBAL_CONFIG_ADDR, data);
}

uint16_t TLE92464_Get_GLOBAL_CONFIG(void)
{
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(GLOBAL_CONFIG_ADDR, &data);
    return data;
}

void TLE92464_Set_GLOBAL_DIAG0(uint16_t data){
    glob_status = TLE92464_SetReg(GLOBAL_DIAG0_ADDR, data);
}

uint16_t TLE92464_Get_GLOBAL_DIAG0(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(GLOBAL_DIAG0_ADDR, &data);
    return data;
}

void TLE92464_Set_GLOBAL_DIAG1(uint16_t data){
    glob_status = TLE92464_SetReg(GLOBAL_DIAG1_ADDR, data);
}

uint16_t TLE92464_Get_GLOBAL_DIAG1(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(GLOBAL_DIAG1_ADDR, &data);
    return data;
}

void TLE92464_Set_GLOBAL_DIAG2(uint16_t data){
    glob_status = TLE92464_SetReg(GLOBAL_DIAG2_ADDR, data);
}

uint16_t TLE92464_Get_GLOBAL_DIAG2(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(GLOBAL_DIAG2_ADDR, &data);
    return data;
}

void TLE92464_Set_VBAT_TH(uint16_t data){
    glob_status = TLE92464_SetReg(VBAT_TH_ADDR, data);
}

uint16_t TLE92464_Get_VBAT_TH(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(VBAT_TH_ADDR, &data);
    return data;
}

void TLE92464_Set_FB_FRZ(uint16_t data){
    glob_status = TLE92464_SetReg(FB_FRZ_ADDR, data);
}

uint16_t TLE92464_Get_FB_FRZ(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(FB_FRZ_ADDR, &data);
    return data;
}

void TLE92464_Set_FB_UPD(uint16_t data){
    glob_status = TLE92464_SetReg(FB_UPD_ADDR, data);
}

uint16_t TLE92464_Get_FB_UPD(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(FB_UPD_ADDR, &data);
    return data;
}

void TLE92464_Set_WD_RELOAD(uint16_t data){
    glob_status = TLE92464_SetReg(WD_RELOAD_ADDR, data);
}

uint16_t TLE92464_Get_WD_RELOAD(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(WD_RELOAD_ADDR, &data);
    return data;
}

void TLE92464_Set_DIAG_ERR_CHGR0(uint16_t data){
    glob_status = TLE92464_SetReg(DIAG_ERR_CHGR0_ADDR, data);
}

uint16_t TLE92464_Get_DIAG_ERR_CHGR0(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(DIAG_ERR_CHGR0_ADDR, &data);
    return data;
}

void TLE92464_Set_DIAG_ERR_CHGR1(uint16_t data){
    glob_status = TLE92464_SetReg(DIAG_ERR_CHGR1_ADDR, data);
}

uint16_t TLE92464_Get_DIAG_ERR_CHGR1(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(DIAG_ERR_CHGR1_ADDR, &data);
    return data;
}

void TLE92464_Set_DIAG_WARN_CHGR0(uint16_t data){
    glob_status = TLE92464_SetReg(DIAG_WARN_CHGR0_ADDR, data);
}

uint16_t TLE92464_Get_DIAG_WARN_CHGR0(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(DIAG_WARN_CHGR0_ADDR, &data);
    return data;
}

void TLE92464_Set_DIAG_WARN_CHGR1(uint16_t data){
    glob_status = TLE92464_SetReg(DIAG_WARN_CHGR1_ADDR, data);
}

uint16_t TLE92464_Get_DIAG_WARN_CHGR1(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(DIAG_WARN_CHGR1_ADDR, &data);
    return data;
}

void TLE92464_Set_FAULT_MASK0(uint16_t data){
    glob_status = TLE92464_SetReg(FAULT_MASK0_ADDR, data);
}

uint16_t TLE92464_Get_FAULT_MASK0(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(FAULT_MASK0_ADDR, &data);
    return data;
}

void TLE92464_Set_FAULT_MASK1(uint16_t data){
    glob_status = TLE92464_SetReg(FAULT_MASK1_ADDR, data);
}

uint16_t TLE92464_Get_FAULT_MASK1(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(FAULT_MASK1_ADDR, &data);
    return data;
}

void TLE92464_Set_FAULT_MASK2(uint16_t data){
    glob_status = TLE92464_SetReg(FAULT_MASK2_ADDR, data);
}

uint16_t TLE92464_Get_FAULT_MASK2(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(FAULT_MASK2_ADDR, &data);
    return data;
}

void TLE92464_Set_CLK_DIV(uint16_t data){
    glob_status = TLE92464_SetReg(CLK_DIV_ADDR, data);
}

uint16_t TLE92464_Get_CLK_DIV(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(CLK_DIV_ADDR, &data);
    return data;
}

void TLE92464_Set_SFF_BIST(uint16_t data){
    glob_status = TLE92464_SetReg(SFF_BIST_ADDR, data);
}

uint16_t TLE92464_Get_SFF_BIST(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(SFF_BIST_ADDR, &data);
    return data;
}

uint16_t TLE92464_Get_ICVID(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(ICVID_ADDR, &data);
    return data;
}

uint16_t TLE92464_Get_PIN_STAT(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(PIN_STAT_ADDR, &data);
    return data;
}

uint32_t TLE92464_Get_FB_STAT(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(FB_STAT_ADDR, &data);
    return data;
}

uint32_t TLE92464_Get_FB_VOLTAGE1(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(FB_VOLTAGE1_ADDR, &data);
    return data;
}

uint32_t TLE92464_Get_FB_VOLTAGE2(void){
    uint32_t data = 0u;
    glob_status = TLE92464_GetReg(FB_VOLTAGE2_ADDR, &data);
    return data;
}

/*******************************************************************************
**                         Channel Function Definitions                        **
*******************************************************************************/
void TLE92464_Set_SETPOINT(uint8_t Channel, uint16_t data){
    //ADDRS is a Channel select address
    uint16_t SETPOINT_ADDRS = TLE92464_CHANNEL_SELECT(Channel, SETPOINT_ADDR);
    glob_status = TLE92464_SetReg(SETPOINT_ADDRS, data);
}

uint16_t TLE92464_Get_SETPOINT(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t SETPOINT_ADDRS = TLE92464_CHANNEL_SELECT(Channel, SETPOINT_ADDR);
    glob_status = TLE92464_GetReg(SETPOINT_ADDRS, &data);
    return data;
}

void TLE92464_Set_CTRL(uint8_t Channel, uint16_t data){
    uint16_t CTRL_ADDRS = TLE92464_CHANNEL_SELECT(Channel, CTRL_ADDR);
    glob_status = TLE92464_SetReg(CTRL_ADDRS, data);
}

uint16_t TLE92464_Get_CTRL(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t CTRL_ADDRS = TLE92464_CHANNEL_SELECT(Channel, SETPOINT_ADDR);
    glob_status = TLE92464_GetReg(CTRL_ADDRS, &data);
    return data;
}

void TLE92464_Set_PERIOD(uint8_t Channel, uint16_t data){
    uint16_t PERIOD_ADDRS = TLE92464_CHANNEL_SELECT(Channel, PERIOD_ADDR);
    glob_status = TLE92464_SetReg(PERIOD_ADDRS, data);
}

uint16_t TLE92464_Get_PERIOD(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t PERIOD_ADDRS = TLE92464_CHANNEL_SELECT(Channel, PERIOD_ADDR);
    glob_status = TLE92464_GetReg(PERIOD_ADDRS, &data);
    return data;
}

void TLE92464_Set_INTEGRATOR_LIMIT(uint8_t Channel, uint16_t data){
    uint16_t INTEGRATOR_LIMIT_ADDRS = TLE92464_CHANNEL_SELECT(Channel, INTEGRATOR_LIMIT_ADDR);
    glob_status = TLE92464_SetReg(INTEGRATOR_LIMIT_ADDRS, data);
}

uint16_t TLE92464_Get_INTEGRATOR_LIMIT(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t INTEGRATOR_LIMIT_ADDRS = TLE92464_CHANNEL_SELECT(Channel, INTEGRATOR_LIMIT_ADDR);
    glob_status = TLE92464_GetReg(INTEGRATOR_LIMIT_ADDRS, &data);
    return data;
}

void TLE92464_Set_DITHER_CLK_DIV(uint8_t Channel, uint16_t data){
    uint16_t DITHER_CLK_DIV_ADDRS = TLE92464_CHANNEL_SELECT(Channel, DITHER_CLK_DIV_ADDR);
    glob_status = TLE92464_SetReg(DITHER_CLK_DIV_ADDRS, data);
}

uint16_t TLE92464_Get_DITHER_CLK_DIV(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t DITHER_CLK_DIV_ADDRS = TLE92464_CHANNEL_SELECT(Channel, DITHER_CLK_DIV_ADDR);
    glob_status = TLE92464_GetReg(DITHER_CLK_DIV_ADDRS, &data);
    return data;
}

void TLE92464_Set_DITHER_STEP(uint8_t Channel, uint16_t data){
    uint16_t DITHER_STEP_ADDRS = TLE92464_CHANNEL_SELECT(Channel, DITHER_STEP_ADDR);
    glob_status = TLE92464_SetReg(DITHER_STEP_ADDRS, data);
}

uint16_t TLE92464_Get_DITHER_STEP(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t DITHER_STEP_ADDRS = TLE92464_CHANNEL_SELECT(Channel, DITHER_STEP_ADDR);
    glob_status = TLE92464_GetReg(DITHER_STEP_ADDRS, &data);
    return data; 
}

void TLE92464_Set_DITHER_CTRL(uint8_t Channel, uint16_t data){
    uint16_t DITHER_CTRL_ADDRS = TLE92464_CHANNEL_SELECT(Channel, DITHER_CTRL_ADDR);
    glob_status = TLE92464_SetReg(DITHER_CTRL_ADDRS, data);
}

uint16_t TLE92464_Get_DITHER_CTRL(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t DITHER_CTRL_ADDRS = TLE92464_CHANNEL_SELECT(Channel, DITHER_CTRL_ADDR);
    glob_status = TLE92464_GetReg(DITHER_CTRL_ADDRS, &data);
    return data;
}

void TLE92464_Set_CH_CONFIG(uint8_t Channel, uint16_t data){
    uint16_t CH_CONFIG_ADDRS = TLE92464_CHANNEL_SELECT(Channel, CH_CONFIG_ADDR);
    glob_status = TLE92464_SetReg(CH_CONFIG_ADDRS, data);
}

uint16_t TLE92464_Get_CH_CONFIG(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t CH_CONFIG_ADDRS = TLE92464_CHANNEL_SELECT(Channel, CH_CONFIG_ADDR);
    glob_status = TLE92464_GetReg(CH_CONFIG_ADDRS, &data);
    return data;
}

void TLE92464_Set_MODE(uint8_t Channel, uint16_t data){
    uint16_t MODE_ADDRS = TLE92464_CHANNEL_SELECT(Channel, MODE_ADDR);
    glob_status = TLE92464_SetReg(MODE_ADDRS, data);
}

uint16_t TLE92464_Get_MODE(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t MODE_ADDRS = TLE92464_CHANNEL_SELECT(Channel, MODE_ADDR);
    glob_status = TLE92464_GetReg(MODE_ADDRS, &data);
    return data;
}

void TLE92464_Set_TON(uint8_t Channel, uint16_t data){
    uint16_t TON_ADDRS = TLE92464_CHANNEL_SELECT(Channel, TON_ADDR);
    glob_status = TLE92464_SetReg(TON_ADDRS, data);
}

uint16_t TLE92464_Get_TON(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t TON_ADDRS = TLE92464_CHANNEL_SELECT(Channel, TON_ADDR);
    glob_status = TLE92464_GetReg(TON_ADDRS, &data);
    return data;
}

void TLE92464_Set_CTRL_INT_THRESH(uint8_t Channel, uint16_t data){
    uint16_t CTRL_INT_THRESH_ADDRS = TLE92464_CHANNEL_SELECT(Channel, CTRL_INT_THRESH_ADDR);
    glob_status = TLE92464_SetReg(CTRL_INT_THRESH_ADDRS, data);
}

uint16_t TLE92464_Get_CTRL_INT_THRESH(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t CTRL_INT_THRESH_ADDRS = TLE92464_CHANNEL_SELECT(Channel, CTRL_INT_THRESH_ADDR);
    glob_status = TLE92464_GetReg(CTRL_INT_THRESH_ADDRS, &data);
    return data;
}

uint32_t TLE92464_Get_FB_DC(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_DC_ADDRS = TLE92464_CHANNEL_SELECT(Channel, FB_DC_ADDR);
    glob_status = TLE92464_GetReg(FB_DC_ADDRS, &data);
    return data;
}

uint32_t TLE92464_Get_FB_VBAT(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_VBAT_ADDRS = TLE92464_CHANNEL_SELECT(Channel, FB_VBAT_ADDR);
    glob_status = TLE92464_GetReg(FB_VBAT_ADDRS, &data);
    return data;
}

uint32_t TLE92464_Get_FB_I_AVG(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_I_AVG_ADDRS = TLE92464_CHANNEL_SELECT(Channel, FB_I_AVG_ADDR);
    glob_status = TLE92464_GetReg(FB_I_AVG_ADDRS, &data);
    return data;
}

uint32_t TLE92464_Get_FB_IMIN_IMAX(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_IMIN_IMAX_ADDRS = TLE92464_CHANNEL_SELECT(Channel, FB_IMIN_IMAX_ADDR);
    glob_status = TLE92464_GetReg(FB_IMIN_IMAX_ADDRS, &data);
    return data;
}

uint32_t TLE92464_Get_FB_I_AVG_s16(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_I_AVG_s16_ADDRS = TLE92464_CHANNEL_SELECT(Channel, FB_I_AVG_s16_ADDR);
    glob_status = TLE92464_GetReg(FB_I_AVG_s16_ADDRS, &data);
    return data;
}

uint32_t TLE92464_Get_FB_INT_THRESH(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_INT_THRESH_ADDRS = TLE92464_CHANNEL_SELECT(Channel, FB_INT_THRESH_ADDR);
    glob_status = TLE92464_GetReg(FB_INT_THRESH_ADDRS, &data);
    return data;
}

uint32_t TLE92464_Get_FB_PERIOD_MIN_MAX(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_PERIOD_MIN_MAX_ADDRS = TLE92464_CHANNEL_SELECT(Channel, FB_PERIOD_MIN_MAX_ADDR);
    glob_status = TLE92464_GetReg(FB_PERIOD_MIN_MAX_ADDRS, &data);
    return data;
}

