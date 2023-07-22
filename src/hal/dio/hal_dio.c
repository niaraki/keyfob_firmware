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
} dio_channel_info_t;

static inline dio_channel_info_t
dio_get_channel_info(dio_channel_t channel)
{
    dio_channel_info_t result = { 0U };
    result.port_index         = (channel / NUM_PIN_IN_PORT);
    result.pin_index          = (channel % NUM_PIN_IN_PORT);
    result.pin_mask           = ((1UL) << result.pin_index);
    result.reg                = gp_dio_regs[result.port_index];
    return result;
}

void
hal_dio_init(const dio_config_t *configs, U16 num_configs)
{
    ASSERT(NULLPTR != configs);

    for (U16 index = 0UL; index < num_configs; index++)
    {
        dio_config_t ch_config = configs[index];

        /* check config params */
        ASSERT(ch_config.channel < DIO_NUM_CHANNEL);
        ASSERT(ch_config.mode < DIO_NUM_MODE);
        ASSERT((ch_config.speed < DIO_NUM_SPEED) && (2U != ch_config.speed));
        ASSERT(ch_config.af < DIO_NUM_AF);
        ASSERT(ch_config.resistor < DIO_NUM_RESISTOR);
        ASSERT(ch_config.default_state < DIO_NUM_PIN_STATE);
        ASSERT(ch_config.exti < DIO_NUM_EXTI);

        /* get channel info */
        dio_channel_info_t ch_info = dio_get_channel_info(ch_config.channel);

        /* Set pin mode and pin-type */
        U8 pin_mode = (U8)ch_config.mode;
        ch_info.reg->OTYPER
            |= (pin_mode >= OUTPUT_OD) ? ch_info.pin_mask : (0UL);
        pin_mode = (pin_mode > 3U) ? (pin_mode - 3U) : pin_mode;
        ch_info.reg->MODER |= ((pin_mode) << (ch_info.pin_index * (2U)));

        /* Set speed */
        U8 speed = (U8)ch_config.speed;
        ch_info.reg->OSPEEDR |= ((speed) << (ch_info.pin_index * (2U)));

        /* Set resistor value*/
        U8 resistor = (U8)ch_config.resistor;
        ch_info.reg->PUPDR |= ((resistor) << (ch_info.pin_index * (2U)));

        /* Set default state */
        U8 state = (U8)ch_config.default_state;
        ch_info.reg->ODR |= (state << ch_info.pin_index);
    }
}

void
hal_dio_set_mode(dio_channel_t channel, dio_mode_t mode)
{
    ASSERT((mode < DIO_NUM_MODE));
    ASSERT((channel < DIO_NUM_CHANNEL));
}

void
hal_dio_write(dio_channel_t channel, dio_state_t state)
{
    ASSERT((state < DIO_NUM_PIN_STATE));
    ASSERT((channel < DIO_NUM_CHANNEL));

    dio_channel_info_t ch_info = dio_get_channel_info(channel);

    if (DIO_HIGH == state)
        ch_info.reg->BSRR |= (ch_info.pin_mask);
    else
        ch_info.reg->BRR |= (ch_info.pin_mask);
}

void
hal_dio_toggle(dio_channel_t channel)
{
    ASSERT((channel < DIO_NUM_CHANNEL));

    dio_channel_info_t ch_info = dio_get_channel_info(channel);
    U32                odr     = ch_info.reg->ODR;
    ch_info.reg->BSRR          = ((odr & ch_info.pin_mask) << NUM_PIN_IN_PORT)
                        | (~odr & ch_info.pin_mask);
}

dio_state_t
hal_dio_read(dio_channel_t channel)
{
    ASSERT((channel < DIO_NUM_CHANNEL));

    dio_state_t        result  = DIO_LOW;
    dio_channel_info_t ch_info = dio_get_channel_info(channel);
    if ((ch_info.pin_mask & ch_info.reg->IDR) == ch_info.pin_mask)
        result = DIO_HIGH;

    return result;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
