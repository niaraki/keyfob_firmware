/**
********************************************************************************
* @file     hal_dio.c
* @author   M.Niaraki
* @date     07/21/2023
* @brief    This module implements DIO driver
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include "hal.h"
#include "hal_dio_cfg.h"
#include "hll.h"
#include "stm32f030x6.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup DIO DIO
 *   @brief
 *    @{
 */
typedef struct
{
    _IO U8  port_index;
    _IO U8  pin_index;
    _IO U32 pin_mask;
    _IO GPIO_TypeDef *reg;
} dio_lookup_t;

static inline dio_lookup_t
dio_lookup(dio_channel_t channel)
{
    dio_lookup_t result = { 0U };
    result.port_index   = channel / NUM_PIN_IN_PORT;
    result.pin_index    = channel % NUM_PIN_IN_PORT;
    result.pin_mask     = ((1UL) << result.pin_index);
    result.reg          = gp_dio_regs[result.port_index];
    return result;
}

void
hal_dio_init(const dio_config_t *configs)
{
    gp_dio_regs[0]->AFR[0] = 0;
}

void
hal_dio_set_mode(dio_channel_t channel, dio_mode_t mode)
{
}

void
hal_dio_write(dio_channel_t channel, dio_state_t state)
{
    ASSERT((state < DIO_MAX_PIN_STATE));
    ASSERT((channel < DIO_MAX_CHANNEL_NUMBER));

    dio_lookup_t chi = dio_lookup(channel);

    if (DIO_HIGH == state)
        chi.reg->BSRR |= (chi.pin_mask);
    else
        chi.reg->BRR |= (chi.pin_mask);
}

void
hal_dio_toggle(dio_channel_t channel)
{
    ASSERT((channel < DIO_MAX_CHANNEL_NUMBER));

    dio_lookup_t chi = dio_lookup(channel);
    U32          odr = chi.reg->ODR;
    chi.reg->BSRR
        = ((odr & chi.pin_mask) << NUM_PIN_IN_PORT) | (~odr & chi.pin_mask);
}

dio_state_t
hal_dio_read(dio_channel_t channel)
{
    ASSERT((channel < DIO_MAX_CHANNEL_NUMBER));

    dio_state_t  result = DIO_LOW;
    dio_lookup_t chi    = dio_lookup(channel);
    if ((chi.pin_mask & chi.reg->IDR) == chi.pin_mask)
        result = DIO_HIGH;

    return result;
}
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
