/**
********************************************************************************
* @file     hal_rcc_cfg.c
* @author   M.Niaraki
* @date     07/18/2023
* @brief    This module implements the config table for RCC driver
* @note     notes
  @verbatim
================================================================================
More information should come here
================================================================================
  @endverbatim
*/

#include "hal_rcc_cfg.h"
#include "hll.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup RCC RCC Config
 *   @brief Reset and Clock Control Module for HAL
 *    @{
 */
enum
{
    RCC_CHANNELS = (1U)
};

/**
 * @ attention The order of defenition in this table must be exactly the same as
 * @see rcc_peri_name_t
 * */
const rcc_peri_t g_rcc_peri_table[RCC_PERI_COUNT] = {
    /* BUS Type | Bit index for Clock Control | Default Clock state */
    { RCC_BUS_AHB, RCC_AHBENR_GPIOAEN_Pos, RCC_CLK_ON },        /* GPIOA*/
    { RCC_BUS_AHB, RCC_AHBENR_GPIOBEN_Pos, RCC_CLK_ON },        /* GPIOB*/
    { RCC_BUS_APB2, RCC_APB2ENR_DBGMCUEN_Pos, RCC_CLK_ON },     /* DEBUG*/
    { RCC_BUS_APB2, RCC_APB2ENR_SYSCFGCOMPEN_Pos, RCC_CLK_ON }, /* SYSCFG*/
    { RCC_BUS_APB2, RCC_APB2ENR_TIM17EN_Pos, RCC_CLK_ON },      /* TIM17*/
};

const rcc_config_t g_rcc_config_table[RCC_CHANNELS] = {
    /* HIGH Freq. Source | LOW Freq. Source | Peripheral Table	*/
    { RCC_HCLK_PLL, RCC_LCLK_LSI, g_rcc_peri_table }
};

/**
 * @brief This function is used by app layer to get access to the
 * configuration table of the RCC unit
 * @retval Pointer to the RCC configuration table
 */
const rcc_config_t *
hal_rcc_cfg_get(void)
{
    return g_rcc_config_table;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
