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
    /* check params */
    ASSERT((state < DIO_MAX_PIN_STATE));
    ASSERT((channel < DIO_MAX_CHANNEL_NUMBER));

    /* select port and pin due to the channel*/
    U8 port_index = channel / NUM_PIN_IN_PORT;
    U8 pin_index  = channel % NUM_PIN_IN_PORT;

    /* apply to target the register */
    if (DIO_HIGH == state)
        gp_dio_regs[port_index]->BSRR |= ((1UL) << (pin_index));
    else
        gp_dio_regs[port_index]->BRR |= ((1UL) << (pin_index));
}

void
hal_dio_toggle(dio_channel_t channel)
{
    /* check params */
    ASSERT((channel < DIO_MAX_CHANNEL_NUMBER));

    /* select port and pin due to the channel*/
    U8  port_index = channel / NUM_PIN_IN_PORT;
    U8  pin_index  = channel % NUM_PIN_IN_PORT;
    U32 pin_mask   = ((1UL) << pin_index);
    U32 odr_value  = gp_dio_regs[port_index]->ODR;

    /* apply to the target register */
    gp_dio_regs[port_index]->BSRR
        = ((odr_value & pin_mask) << NUM_PIN_IN_PORT) | (~odr_value & pin_mask);
}

dio_state_t
hal_dio_read(dio_channel_t channel)
{
    dio_state_t result = DIO_LOW;

    /* check params */
    ASSERT((channel < DIO_MAX_CHANNEL_NUMBER));

    /* select port and pin due to the channel*/
    U8  port_index = channel / NUM_PIN_IN_PORT;
    U8  pin_index  = channel % NUM_PIN_IN_PORT;
    U32 pin_mask   = ((1UL) << pin_index);
    U32 idr_value  = gp_dio_regs[port_index]->IDR;

    if ((pin_mask & idr_value) == pin_mask)
        result = DIO_HIGH;

    return result;
}
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
