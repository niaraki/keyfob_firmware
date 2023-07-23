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

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup DIO DIO
 *   @brief
 *    @{
 */

#define VALUE_BY_INDEX(VAL, IDX) ((VAL) << (IDX * (2U)))

typedef struct
{
    _IO U8  port_index;
    _IO U8  pin_index;
    _IO U32 pin_mask;
    _IO GPIO_TypeDef *reg;
} dio_channel_info_t;

static inline dio_channel_info_t
dio_get_channel_info(pin_t channel)
{
    dio_channel_info_t result = { 0U };
    result.port_index         = (channel / NUM_PIN_IN_PORT);
    result.pin_index          = (channel % NUM_PIN_IN_PORT);
    result.pin_mask           = ((1UL) << result.pin_index);
    result.reg                = gp_dio_regs[result.port_index];
    return result;
}

static inline void
assert_config_params(const dio_config_t *const config)
{
    ASSERT(config->channel < NUM_PINS);
    ASSERT(config->mode < DIO_NUM_MODE);
    ASSERT((config->speed < DIO_NUM_SPEED) && (2U != config->speed));
    ASSERT(config->af < DIO_NUM_AF);
    ASSERT(config->resistor < DIO_NUM_RESISTOR);
    ASSERT(config->default_state < DIO_NUM_PIN_STATE);
}

static inline void
set_mode(const dio_config_t *const config, dio_channel_info_t *chi)
{
    U8 pin_mode = (U8)config->mode;
    chi->reg->OTYPER |= (pin_mode >= OUTPUT_OD) ? chi->pin_mask : (0UL);
    if (pin_mode > ANALOG)
    {
        pin_mode -= 3;
    }
    chi->reg->MODER |= VALUE_BY_INDEX(pin_mode, chi->pin_index);
}

static inline void
set_speed(const dio_config_t *const config, const dio_channel_info_t *const chi)
{
    U8 speed = (U8)config->speed;
    chi->reg->OSPEEDR |= VALUE_BY_INDEX(speed, chi->pin_index);
}

static inline void
set_resistor(const dio_config_t *const       config,
             const dio_channel_info_t *const chi)
{
    U8 resistor = (U8)config->resistor;
    chi->reg->PUPDR |= VALUE_BY_INDEX(resistor, chi->pin_index);
}

static inline void
set_af(const dio_config_t *const config, const dio_channel_info_t *const chi)
{
    U8 af_value   = (U8)config->af;
    U8 af_reg_idx = (((U8)chi->pin_index) < 8U) ? 0 : 1;
    U8 af_bit_idx = (chi->pin_index % (NUM_PIN_IN_PORT / 2U));
    chi->reg->AFR[af_reg_idx] |= ((af_value) << (af_bit_idx * (4U)));
}

static inline void
set_state(dio_channel_info_t *channel_info, dio_state_t state)
{
    if (DIO_HIGH == state)
        channel_info->reg->BSRR |= (channel_info->pin_mask);
    else
        channel_info->reg->BRR |= (channel_info->pin_mask);
}

inline void
hal_dio_config(const dio_config_t *const config)
{
    assert_config_params(config);

    dio_channel_info_t chi = dio_get_channel_info(config->channel);

    set_mode(config, &chi);
    set_speed(config, &chi);
    set_resistor(config, &chi);
    set_af(config, &chi);
    set_state(&chi, config->default_state);
}

void
hal_dio_init(const dio_config_t *const configs, U16 num_configs)
{
    ASSERT(NULLPTR != configs);

    for (U16 index = 0UL; index < num_configs; index++)
    {
        hal_dio_config(&configs[index]);
    }
}

void
hal_dio_write(pin_t channel, dio_state_t state)
{
    ASSERT((state < DIO_NUM_PIN_STATE));
    ASSERT((channel < NUM_PINS));

    dio_channel_info_t chi = dio_get_channel_info(channel);
    set_state(&chi, state);
}

void
hal_dio_toggle(pin_t channel)
{
    ASSERT((channel < NUM_PINS));

    dio_channel_info_t chi = dio_get_channel_info(channel);
    U32                odr = chi.reg->ODR;
    chi.reg->BSRR
        = ((odr & chi.pin_mask) << NUM_PIN_IN_PORT) | (~odr & chi.pin_mask);
}

dio_state_t
hal_dio_read(pin_t channel)
{
    ASSERT((channel < NUM_PINS));

    dio_state_t        result = DIO_LOW;
    dio_channel_info_t chi    = dio_get_channel_info(channel);
    if ((chi.pin_mask & chi.reg->IDR) == chi.pin_mask)
        result = DIO_HIGH;

    return result;
}

void
hal_dio_write_port(port_t port, U32 value)
{
    ASSERT(port < NUM_PORTS);
    gp_dio_regs[port]->ODR = value;
}

U32
hal_dio_read_port(port_t port)
{
    U32 result = 0;
    ASSERT(port < NUM_PORTS);
    result = gp_dio_regs[port]->ODR;
    return result;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
