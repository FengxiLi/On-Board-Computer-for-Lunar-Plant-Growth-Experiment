#include "gpio_ctrl.h"
#include "spi_ctrl.h"
#include "TLE92464_RegLayer.h"
#include "TLE92464_CommLayer.h"
#include <unistd.h>
#include <stdio.h>

void TLE9246x_Init();

int main() {
    printf("[DEBUG] Start gpio_init()\n");
    gpio_init();
    printf("[DEBUG] gpio_init() done\n");

    
    printf("[DEBUG] Start spi_init()\n");
    spi_init();
    printf("[DEBUG] spi_init() done\n");

    printf("[DEBUG] Set EN = 1\n");
    gpio_set_en(1);
    usleep(500 * 1000);

    printf("[DEBUG] Set RESN = 0\n");
    gpio_set_resn(0);
    usleep(500 * 1000);

    printf("[DEBUG] Set RESN = 1\n");
    gpio_set_resn(1);
    usleep(500 * 1000);
    printf("[DEBUG] Call TLE9246x_Init()\n");
    TLE9246x_Init();

    printf("[DEBUG] TLE9246x_Init() done\n");

    printf("[DEBUG] Entering main loop...\n");   

 while (1) {

        sleep(1);
    }

    spi_cleanup();
    gpio_cleanup();
    return 0;
}



void TLE9246x_Init(void)
{
  TLE92464_Get_FB_STAT();
  TLE92464_Get_FB_STAT();

  TLE92464_Set_GLOBAL_CONFIG(0x4004);
  TLE92464_Set_GLOBAL_CONFIG(0x4004);
  
  TLE92464_Get_GLOBAL_CONFIG();
  TLE92464_Get_GLOBAL_CONFIG();
    
  TLE92464_Set_GLOBAL_DIAG0(0x0000);
  TLE92464_Set_GLOBAL_DIAG0(0x0000);
  TLE92464_Set_GLOBAL_DIAG1(0x0000);
  TLE92464_Set_GLOBAL_DIAG1(0x0000);
  TLE92464_Set_GLOBAL_DIAG2(0x0000);
  TLE92464_Set_GLOBAL_DIAG2(0x0000);
  TLE92464_Set_DIAG_ERR_CHGR0(0x0000);
  TLE92464_Set_DIAG_ERR_CHGR0(0x0000);
  TLE92464_Set_DIAG_ERR_CHGR1(0x0000);
  TLE92464_Set_DIAG_ERR_CHGR1(0x0000);
  TLE92464_Set_DIAG_WARN_CHGR0(0x0000);
  TLE92464_Set_DIAG_WARN_CHGR0(0x0000);
  TLE92464_Set_DIAG_WARN_CHGR1(0x0000);
  TLE92464_Set_DIAG_WARN_CHGR1(0x0000);
      usleep(500 * 1000);
      
  TLE92464_Set_SETPOINT(0x00,0x0666);
  TLE92464_Set_SETPOINT(0x00,0x0666);
  
  TLE92464_Set_MODE(0x00,0x0003);
  TLE92464_Set_MODE(0x00,0x0003);

 
  TLE92464_Set_CH_CTRL(0x8001);
  TLE92464_Set_CH_CTRL(0x8001);
  
  TLE92464_Get_MODE(0x00);
  TLE92464_Get_MODE(0x00);
  
    TLE92464_Get_CH_CTRL();
    TLE92464_Get_CH_CTRL();
      
  //TLE92464_Set_PERIOD(0x00, 0x06E1);
 //TLE92464_Set_PERIOD(0x00, 0x06E1);

  
 // TLE92464_Set_DITHER_CLK_DIV(0x00, 1838);
  //TLE92464_Set_DITHER_CLK_DIV(0x00, 1838);
  //TLE92464_Set_DITHER_STEP(0x00, 0000);
//TLE92464_Set_DITHER_STEP(0x00, 0000);
 // TLE92464_Set_TON(0, 0x06E1);
 // TLE92464_Set_TON(0, 0x06E1);
  TLE92464_Set_DITHER_CTRL(0x00, 0x0000);
  TLE92464_Set_DITHER_CTRL(0x00, 0x0000);
  
  TLE92464_Get_FB_STAT();
  TLE92464_Get_FB_STAT();
  TLE92464_Debug_Channel(0);
debug_feedback_channel(0);

 TLE92464_Get_FB_VOLTAGE1();
  TLE92464_Get_FB_VOLTAGE1();
 TLE92464_Get_FB_VOLTAGE2();
  TLE92464_Get_FB_VOLTAGE2();
 
  TLE92464_Get_ICVID();
  TLE92464_Get_ICVID();

}

void debug_feedback_channel(uint8_t ch) {
    // Step 1: Read 4 register values from the target channel
    TLE92464_Get_FB_DC(ch);
    uint32_t fb_dc        = TLE92464_Get_FB_DC(ch);
    TLE92464_Get_FB_VBAT(ch);
    uint32_t fb_vbat      = TLE92464_Get_FB_VBAT(ch);
    TLE92464_Get_FB_I_AVG(ch);
    uint32_t fb_i_avg     = TLE92464_Get_FB_I_AVG(ch);
    TLE92464_Get_FB_I_AVG_s16(ch);
    uint32_t fb_i_avg_s16 = TLE92464_Get_FB_I_AVG_s16(ch);

    // Step 2: Extract TO_MANT and TP_MANT from FB_DC register
    uint16_t TP_MANT = fb_dc & 0x7FF;                // Bits [10:0] - period mantissa
    uint16_t TO_MANT = (fb_dc >> 11) & 0x7FF;        // Bits [21:11] - on-time mantissa

    // Step 3: Extract VBAT_AVG_MANT and EXP from FB_VBAT register
    uint16_t VBAT_MANT = fb_vbat & 0x7FF;            // Bits [10:0] - voltage mantissa
    uint8_t EXP_VBAT = (fb_vbat >> 12) & 0x0F;       // Bits [15:12] - exponent (optional)

    // Step 4: Extract I_AVG_MANT and EXP from FB_I_AVG register
    int16_t I_AVG_MANT = fb_i_avg & 0x0FFF;          // Bits [11:0] - current mantissa (signed)
    if (I_AVG_MANT & 0x0800) I_AVG_MANT -= 0x1000;   // Sign extend 12-bit to int16_t
    uint8_t EXP_IAVG = (fb_i_avg >> 12) & 0x0F;      // Bits [15:12] - exponent (optional)

    // Step 5: Extract I_AVG_s16 from FB_I_AVG_s16 register (signed 16-bit)
    int16_t I_AVG_s16 = fb_i_avg_s16 & 0xFFFF;       // Bits [15:0]
    if (I_AVG_s16 & 0x8000) I_AVG_s16 -= 0x10000;    // Sign extend to int16_t

    // Step 6: Calculate values based on register contents
    float duty_cycle = (TP_MANT > 0) ? ((float)TO_MANT / TP_MANT) * 100.0f : 0.0f;
    float Vbat = (TP_MANT > 0) ? (41.47f * VBAT_MANT / TP_MANT) : 0.0f;
    float Iavg = (TP_MANT > 0) ? (4.0f * I_AVG_MANT / TP_MANT) : 0.0f;
    float Iavg_s16 = 4.0f * I_AVG_s16 / 65535.0f;    // Based on full 16-bit range

    // Step 7: Print debug information
    printf("========== TLE92464 Channel %d Feedback ==========\n", ch);
    printf("[FB_DC]         TP_MANT = %u, TO_MANT = %u\n", TP_MANT, TO_MANT);
    printf("[FB_VBAT]       VBAT_MANT = %u, EXP = %u\n", VBAT_MANT, EXP_VBAT);
    printf("[FB_I_AVG]      I_AVG_MANT = %d, EXP = %u\n", I_AVG_MANT, EXP_IAVG);
    printf("[FB_I_AVG_s16]  I_AVG_s16 = %d\n", I_AVG_s16);
    printf("--------------------------------------------\n");
    printf("Duty Cycle       = %.2f %%\n", duty_cycle);
    printf("VBAT             = %.2f V\n", Vbat);
    printf("I_avg            = %.3f A (from FB_I_AVG)\n", Iavg);
    printf("I_avg_s16        = %.3f A (from FB_I_AVG_s16)\n", Iavg_s16);
    printf("==================================================\n");
}


#include <stdio.h>

void TLE92464_Debug_Channel(uint8_t channel) {
    printf("========= TLE92464 Channel %d Configuration =========\n", channel);

    // SETPOINT register
    TLE92464_Get_SETPOINT(channel);
    uint16_t setpoint = TLE92464_Get_SETPOINT(channel);
    uint16_t target = setpoint & 0x7FFF;
    uint8_t auto_limit_disabled = (setpoint >> 15) & 0x01;
    float iset = 2.0f * target / 32767.0f; // assuming I_set = 2A * target / (2^15 - 1)
    printf("[SETPOINT] Target = %u, AutoLimit_Disabled = %u, I_set ? %.3f A\n", target, auto_limit_disabled, iset);

    // MODE register
    TLE92464_Get_MODE(channel);
    uint16_t mode = TLE92464_Get_MODE(channel);
    printf("[MODE]     0x%04X\n", mode);

    // CH_CONFIG register
    TLE92464_Get_CH_CONFIG(channel);
    uint16_t ch_config = TLE92464_Get_CH_CONFIG(channel);
    printf("[CH_CONFIG] 0x%04X\n", ch_config);

    // CTRL register
    TLE92464_Get_CTRL(channel);
    uint16_t ctrl = TLE92464_Get_CTRL(channel);
    printf("[CTRL]     0x%04X\n", ctrl);

    // PERIOD register
    TLE92464_Get_PERIOD(channel);
    uint16_t period = TLE92464_Get_PERIOD(channel);
    printf("[PERIOD]   0x%04X (%u)\n", period, period);

    // INTEGRATOR_LIMIT register
    TLE92464_Get_INTEGRATOR_LIMIT(channel);
    uint16_t int_limit = TLE92464_Get_INTEGRATOR_LIMIT(channel);
    printf("[INT_LIM]  0x%04X (%u)\n", int_limit, int_limit);

    // DITHER_CLK_DIV register
    TLE92464_Get_DITHER_CLK_DIV(channel);
    uint16_t clk_div = TLE92464_Get_DITHER_CLK_DIV(channel);
    uint8_t clk_mant = clk_div & 0x0FFF;
    uint8_t clk_exp  = (clk_div >> 12) & 0x0F;
    printf("[CLK_DIV]  MANT = %u, EXP = %u (Raw = 0x%04X)\n", clk_mant, clk_exp, clk_div);

    // DITHER_STEP register
    TLE92464_Get_DITHER_STEP(channel);
    uint16_t dither_step = TLE92464_Get_DITHER_STEP(channel);
    printf("[DITHER_STEP] 0x%04X (%u)\n", dither_step, dither_step);

    // DITHER_CTRL register
    TLE92464_Get_DITHER_CTRL(channel);
    uint16_t dither_ctrl = TLE92464_Get_DITHER_CTRL(channel);
    printf("[DITHER_CTRL] 0x%04X\n", dither_ctrl);

    // TON register
    TLE92464_Get_TON(channel);
    uint16_t ton = TLE92464_Get_TON(channel);
    printf("[TON]      0x%04X (%u)\n", ton, ton);

    // CTRL_INT_THRESH register
    TLE92464_Get_CTRL_INT_THRESH(channel);
    uint16_t ctrl_thresh = TLE92464_Get_CTRL_INT_THRESH(channel);
    printf("[CTRL_INT_THRESH] 0x%04X (%u)\n", ctrl_thresh, ctrl_thresh);

    printf("======================================================\n\n");
}
