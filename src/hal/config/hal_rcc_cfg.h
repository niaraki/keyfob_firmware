/**
********************************************************************************
* @file     hal_rcc_cfg.h
* @author   M.Niaraki
* @date     07/18/2023
* @brief    This header defines Reset and Clock Control (RCC) config defenitions
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_RCC_CFG_H
#define __HAL_RCC_CFG_H

#include "hal_common_defines.h"

typedef enum
{
    RCC_HCLK_OFF = (0U),
    RCC_HCLK_HSI,
    RCC_HCLK_HSE,
    RCC_HCLK_PLL
} rcc_high_freq_t;

typedef enum
{
    RCC_LCLK_OFF = (0U),
    RCC_LCLK_LSI,
    RCC_LCLK_LSE
} rcc_low_freq_t;

typedef enum
{
    RCC_CLK_OFF = (0U),
    RCC_CLK_ON
} rcc_clk_state_t;

typedef enum
{
    RCC_GPIOA = (0U),
    RCC_GPIOB,
    RCC_DEBUG,
    RCC_SYSCFG,
    RCC_TIM17,
    RCC_TIM3,
    RCC_PERI_COUNT
} rcc_peri_name_t;

typedef enum
{
    RCC_BUS_APB1 = (0U),
    RCC_BUS_APB2,
    RCC_BUS_AHB
} rcc_bus_t;

typedef struct
{
    rcc_bus_t       bus_type;
    U8              clock_bit_index;
    rcc_clk_state_t default_clk_state;
} rcc_peri_t;

typedef struct
{
    rcc_high_freq_t         rcc_high_freq_source;
    rcc_low_freq_t          rcc_low_freq_source;
    const rcc_peri_t *const rcc_peri_table;
} rcc_config_t;

#ifdef __cplusplus
extern "C"
{
#endif

    const rcc_config_t *hal_rcc_cfg_get(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_RCC_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
