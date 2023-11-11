/**
********************************************************************************
* @file     hal_exti.c
* @author   M.Niaraki
* @date     11/03/2023
* @brief    Implements internals of the EXTI module
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include "hal.h"
#include "hal_exti_cfg.h"
#include "hal_pins.h"
#include "hll.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup EXTI EXTI
 *   @brief EXTERNAL Interrupt module
 *    @{
 */

/**@addtogroup EXTI_MACRO Macros
 * @brief Private macros
 * @{
 **/
#define CHANNEL_MASK(channel) (((U32)(1U << channel)))
#define IS_CHANNEL_ACTIVATED(channel) \
    ((gp_exti_regs->PR & CHANNEL_MASK(channel)))
#define IS_CHANNEL_VALID(channel)   ((channel < EXTI_CHANNEL_COUNT))
#define IS_CALLBACK_VALID(callback) ((NULLPTR != callback) && (0 != callback))
/** @}*/

static inline exti_channel_t get_activated_channel(
    exti_channel_t const firstChannel, exti_channel_t const secondChannel);

static inline void execute_channel_callback(exti_channel_t const channel);

static IRQn_Type get_interrupt_number(exti_channel_t const channel);

static void set_exti_mode(exti_channel_t const channel, exti_mode_t const mode);

static inline U32 get_priority_value(exti_priority_t level);

static void set_exti_port(exti_channel_t const channel, port_t const port);

/**@addtogroup EXTI_DS Data structures
 * @brief Data structures used by private functions
 * @{
 **/

exti_callback_t callback_table[EXTI_CHANNEL_COUNT] = { 0 };

/** @}*/

I8
hal_exti_init(const exti_config_t *const configs, U16 num_configs)
{
    ASSERT(NULLPTR != configs);
    ASSERT(num_configs > 0U);

    for (U16 index = 0U; index < num_configs; ++index)
    {
        if (0 != hal_exti_config(&configs[index]))
        {
            return -EFAULT;
        }
    }

    return 0;
}

I8
hal_exti_config(const exti_config_t *const config)
{
    ASSERT(IS_CHANNEL_VALID(config->channel));
    ASSERT(config->mode < EXTI_MODE_COUNT);
    ASSERT(config->priority < EXTI_PRIORITY_COUNT);
    ASSERT(config->port < NUM_PORTS);

    if (!IS_CHANNEL_VALID(config->channel) || (config->port >= NUM_PORTS))
        return -EINVAL;

    set_exti_port(config->channel, config->port);
    set_exti_mode(config->channel, config->mode);

    NVIC_SetPriority(get_interrupt_number(config->channel),
                     get_priority_value(config->priority));

    gp_exti_regs->IMR |= CHANNEL_MASK(config->channel);

    return 0;
}

I8
hal_exti_register_callback(exti_channel_t const  channel,
                           exti_callback_t const callback)
{
    ASSERT(IS_CALLBACK_VALID(callback));
    ASSERT(IS_CHANNEL_VALID(channel));

    if (!IS_CALLBACK_VALID(callback) || !IS_CHANNEL_VALID(channel))
        return -EINVAL;

    IRQn_Type interrupt_number = get_interrupt_number(channel);
    NVIC_DisableIRQ(interrupt_number);
    callback_table[(U8)channel] = callback;
    NVIC_EnableIRQ(interrupt_number);
}

static U8
get_port_index(port_t const port)
{
    U8 result = 0;
    if (PORTA == port)
        result = 0U;
    else if (PORTB == port)
        result = 1U;
    return result;
}

static void
set_exti_port(exti_channel_t const channel, port_t const port)
{
    U8 reg_index = ((U8)channel) / 4U;
    U8 bit_index = ((((U8)channel) % 4U) * 4U);
    gp_syscfg_regs->EXTICR[reg_index] &= ~(0xFU << bit_index);
    gp_syscfg_regs->EXTICR[reg_index] |= (get_port_index(port) << bit_index);
}

static inline U32
get_priority_value(exti_priority_t level)
{
    U32 result = 0x00;
    switch (level)
    {
        case EXTI_PRIORITY_HIGHEST: {
            result = 0x00;
            break;
        }
        case EXTI_PRIORITY_HIGH: {
            result = 0x40;
            break;
        }
        case EXTI_PRIORITY_NORMAL: {
            result = 0x80;
            break;
        }
        case EXTI_PRIORITY_LOW: {
            result = 0xC0;
            break;
        }
        default:
            result = 0;
    }
    return result;
}

static void
set_exti_mode(exti_channel_t const channel, exti_mode_t const mode)
{

    gp_exti_regs->RTSR &= ~CHANNEL_MASK(channel);
    gp_exti_regs->FTSR &= ~CHANNEL_MASK(channel);

    if ((EXTI_MODE_RISING_EDGE == mode) || (EXTI_MODE_BOTH_EDGE == mode))
        gp_exti_regs->RTSR |= CHANNEL_MASK(channel);

    if ((EXTI_MODE_FALLING_EDGE == mode) || (EXTI_MODE_BOTH_EDGE == mode))
        gp_exti_regs->FTSR |= CHANNEL_MASK(channel);
}

static IRQn_Type
get_interrupt_number(exti_channel_t const channel)
{
    IRQn_Type result = EXTI0_1_IRQn;
    if (EXTI_CHANNEL_2 == channel || EXTI_CHANNEL_3 == channel)
    {
        result = EXTI2_3_IRQn;
    }
    else if (EXTI_CHANNEL_4 == channel || EXTI_CHANNEL_15 == channel)
    {
        result = EXTI4_15_IRQn;
    }
    return result;
}

static inline void
execute_channel_callback(exti_channel_t const channel)
{
    if (!IS_CHANNEL_VALID(channel))
        return;

    exti_callback_t callback = callback_table[(U8)channel];
    if (IS_CALLBACK_VALID(callback))
    {
        gp_exti_regs->IMR &= ~CHANNEL_MASK(channel); /*mask interrupt*/
        callback();
        gp_exti_regs->IMR |= CHANNEL_MASK(channel); /*clear mask*/
    }

    gp_exti_regs->PR |= CHANNEL_MASK(channel); /*clear pending bit*/
}

static inline exti_channel_t
get_activated_channel(exti_channel_t const firstChannel,
                      exti_channel_t const secondChannel)
{
    exti_channel_t activated_channel = firstChannel;
    if (IS_CHANNEL_ACTIVATED(secondChannel))
        activated_channel = secondChannel;
    return activated_channel;
}

__FORCEINLINE void
hal_exti0_1_irq_handler(void)
{
    execute_channel_callback(
        get_activated_channel(EXTI_CHANNEL_0, EXTI_CHANNEL_1));
}

__FORCEINLINE void
hal_exti2_3_irq_handler(void)
{
    execute_channel_callback(
        get_activated_channel(EXTI_CHANNEL_2, EXTI_CHANNEL_3));
}

__FORCEINLINE void
hal_exti4_15_irq_handler(void)
{
    execute_channel_callback(
        get_activated_channel(EXTI_CHANNEL_4, EXTI_CHANNEL_15));
}

/** @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF
 * FILE****/
