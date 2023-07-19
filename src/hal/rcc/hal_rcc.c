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
#include "hll.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup RCC RCC
 *   @brief Reset and Clock Controller Module for HAL
 *    @{
 */

/**
 * @brief test function
 * @param a is used to
 * @retval number
 * @warning sample warning
 * @note sample note
 * @bug sample bug
 * @attention sample attention
 * @brief test1 function
 * @retval number
 * @see test
 */
void
hal_rcc_init(const rcc_config_t *configs)
{
    // Enable the HSE clock
    // hll_rcc_regs->CR |= RCC_CR_HSEON;

    // while (!(hll_rcc_regs->CR & RCC_CR_HSERDY))
    //     ;
    // // Configure the PLL
    // hll_rcc_regs->CFGR = RCC_CFGR_PLLSRC;
    // hll_rcc_regs->CFGR &= ~RCC_CFGR_PLLXTPRE; // HSE not divided
    // hll_rcc_regs->CFGR &= ~RCC_CFGR_PLLMUL;   // reset PLL MUL
    // hll_rcc_regs->CFGR |= RCC_CFGR_PLLMUL_2;  // PLLM = 6

    // // Set the HCLK clock to 48MHz
    // hll_rcc_regs->CFGR &= ~RCC_CFGR_HPRE;
    // // Set the PPRE clock to 1
    // hll_rcc_regs->CFGR &= ~RCC_CFGR_PPRE;

    // // Enable the PLL
    // hll_rcc_regs->CR |= RCC_CR_PLLON;
    // while (!(hll_rcc_regs->CR & RCC_CR_PLLRDY))
    //     ;

    // // Set the PLL as the system clock source
    // hll_rcc_regs->CFGR &= ~RCC_CFGR_SW;
    // hll_rcc_regs->CFGR |= RCC_CFGR_SW_PLL;
    // while ((hll_rcc_regs->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
    //     ;
    hll_rcc_regs->CR = 98; // for test
}

void
hal_rcc_test(int test)
{
    int i = test;
    if (i > 1)
        return;
}
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
