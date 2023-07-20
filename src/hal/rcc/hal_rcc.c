/**
********************************************************************************
* @file     hal_rcc.c
* @author   M.Niaraki
* @date     07/18/2023
* @brief    This module implements RCC driver
* @note     notes
  @verbatim
================================================================================
More information should come here
================================================================================
  @endverbatim
*/
#include "hal.h"
#include "hal_rcc_cfg.h"
#include "hll.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup RCC RCC
 *   @brief Reset and Clock Control Module for HAL
 *    @{
 */

/** @brief PLL values are defined to generate 48MHz clock from 8Mhz Xtal (HSE)
 */
#define RCC_PRE_INITED_FREQ (48000000UL)

static inline void
rcc_set_high_freq_clock(rcc_high_freq_t source)
{
    if (RCC_HCLK_HSE == source || RCC_HCLK_PLL == source)
    {
        hal_clear_bit(&gp_rcc_regs->CR, RCC_CR_HSION_Pos);
        hal_set_bit(&gp_rcc_regs->CR, RCC_CR_HSEON_Pos);
        hal_wait_for_bit(&gp_rcc_regs->CR, RCC_CR_HSERDY_Pos);
    }
    else if (RCC_HCLK_HSI == source)
    {
        hal_clear_bit(&gp_rcc_regs->CR, RCC_CR_HSEON_Pos);
        hal_set_bit(&gp_rcc_regs->CR, RCC_CR_HSION_Pos);
        hal_wait_for_bit(&gp_rcc_regs->CR, RCC_CR_HSIRDY_Pos);
    }
    else
    {
        hal_clear_bit(&gp_rcc_regs->CR, RCC_CR_HSEON_Pos);
        hal_clear_bit(&gp_rcc_regs->CR, RCC_CR_HSION_Pos);
    }
}

static inline void
rcc_set_lse(void)
{
    /* Enable the power interface clock */
    hal_set_bit(&gp_rcc_regs->APB1ENR, RCC_APB1ENR_PWREN_Pos);
    /* Enable access to the backup domain */
    hal_set_bit(&gp_pwr_regs->CR, PWR_CR_DBP_Pos);
    /* Reset the backup domain */
    hal_set_bit(&gp_rcc_regs->BDCR, RCC_BDCR_BDRST_Pos);
    /* Release the backup domain reset */
    hal_clear_bit(&gp_rcc_regs->BDCR, RCC_BDCR_BDRST_Pos);
    /* Enable the LSE oscillator */
    hal_set_bit(&gp_rcc_regs->BDCR, RCC_BDCR_LSEON_Pos);
    /* Wait until the LSE oscillator is ready */
    hal_wait_for_bit(&gp_rcc_regs->BDCR, RCC_BDCR_LSERDY_Pos);
    /* Select the LSE oscillator as the RTC clock source */
    hal_set_mask(&gp_rcc_regs->BDCR, RCC_BDCR_RTCSEL_0);
}

static inline void
rcc_set_lsi(void)
{
    /* Enable the LSI oscillator */
    hal_set_bit(&gp_rcc_regs->CSR, RCC_CSR_LSION_Pos);
    /* Wait until the LSI oscillator is ready */
    hal_wait_for_bit(&gp_rcc_regs->CSR, RCC_CSR_LSIRDY_Pos);
    /* Select the LSI oscillator as the RTC clock source */
    hal_set_mask(&gp_rcc_regs->BDCR, RCC_BDCR_RTCSEL_1);
}

static inline void
rcc_set_low_freq_clock(rcc_low_freq_t source)
{
    if (RCC_LCLK_LSI == source)
    {
        rcc_set_lsi();
    }
    else if (RCC_LCLK_LSE == source)
    {
        rcc_set_lse();
    }
    else
    {
        // Disable LSE
        hal_clear_bit(&gp_rcc_regs->BDCR, RCC_BDCR_LSEON_Pos);
        hal_clear_bit(&gp_rcc_regs->BDCR, RCC_BDCR_LSEBYP_Pos);
        // Disable LSI
        hal_clear_bit(&gp_rcc_regs->CSR, RCC_CSR_LSION_Pos);
    }
}

/**
 * @brief This function sets up the PLL unit to generate 48Mhz from 8Mhz HSE
 * clock
 * @attention In a case that you need to change the clock, you should study page
 * 124 of the RCC unit in STM32f030 datasheet and specify MUL/DIV values.
 * */
static inline void
rcc_enable_pll(void)
{
    /* Configure the PLL */
    hal_set_mask(&gp_rcc_regs->CFGR, RCC_CFGR_PLLSRC);
    hal_clear_bit(&gp_rcc_regs->CFGR, RCC_CFGR_PLLXTPRE_Pos);
    hal_clear_mask(&gp_rcc_regs->CFGR, RCC_CFGR_PLLMUL);
    hal_set_mask(&gp_rcc_regs->CFGR, RCC_CFGR_PLLMUL_2);

    /* Set the HCLK clock to 48MHz */
    hal_clear_mask(&gp_rcc_regs->CFGR, RCC_CFGR_HPRE);
    /* Set the PPRE clock to 1 */
    hal_clear_mask(&gp_rcc_regs->CFGR, RCC_CFGR_PPRE);

    /* Enable the PLL */
    hal_set_bit(&gp_rcc_regs->CR, RCC_CR_PLLON_Pos);
    hal_wait_for_bit(&gp_rcc_regs->CR, RCC_CR_PLLRDY_Pos);

    /* Set the PLL as the system clock source */
    hal_clear_mask(&gp_rcc_regs->CFGR, RCC_CFGR_SW);
    hal_set_mask(&gp_rcc_regs->CFGR, RCC_CFGR_SW_PLL);
    hal_wait_for_mask(&gp_rcc_regs->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);
}

static inline void
rcc_set_peripheral_clock(rcc_clk_state_t peripheral, REG reg, U8 bit_index)
{
    if (RCC_CLK_ON == peripheral)
        hal_set_bit(reg, bit_index);
    else
        hal_clear_bit(reg, bit_index);
}

static inline REG
rcc_get_bus_register(rcc_bus_t bus)
{
    REG result = 0;

    if (RCC_BUS_APB2 == bus)
        result = &gp_rcc_regs->APB2ENR;
    else if (RCC_BUS_AHB == bus)
        result = &gp_rcc_regs->AHBENR;
    else
        result = &gp_rcc_regs->APB1ENR;

    return result;
}

static inline void
rcc_set_peri_clock(const rcc_config_t *config,
                   rcc_peri_name_t     name,
                   rcc_clk_state_t     state)
{
    rcc_peri_t peri = config->rcc_peri_table[name];
    REG        reg  = rcc_get_bus_register(peri.bus_type);
    if (RCC_CLK_ON == state)
    {
        hal_set_bit(reg, peri.clock_bit_index);
    }
    else
    {
        hal_clear_bit(reg, peri.clock_bit_index);
    }
}

/**
 * @brief This function is used to initialize RCC unit
 * @param Pointer to the RCC configuration table
 */
void
hal_rcc_init(const rcc_config_t *configs)
{
    rcc_set_high_freq_clock(configs->rcc_high_freq_source);
    rcc_set_low_freq_clock(configs->rcc_low_freq_source);
    rcc_enable_pll();

    /* Set peripherals clock due to configuration table */
    for (U8 index = 0U; index < RCC_PERI_COUNT; index++)
    {
        rcc_peri_t cp = configs->rcc_peri_table[index];
        rcc_set_peri_clock(configs, index, cp.default_clk_state);
    }
}

/**
 * @brief This function is used to check the current system clock and expected
 * value
 * @retval OK:0 , -EFUALT: when we have mismatch
 * */
I8
hal_rcc_check_system_clock(void)
{
    I8 result = 0;
    SystemCoreClockUpdate();
    if (RCC_PRE_INITED_FREQ != SystemCoreClock)
    {
        result = -EFAULT;
    }
    return result;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
