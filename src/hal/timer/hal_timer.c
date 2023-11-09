/**
********************************************************************************
* @file     hal_timer.c
* @author   M.Niaraki
* @date     11/12/2023
* @brief    this module implements simple timer driver for stm32
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

/** @defgroup TIMER TIMER
 *   @brief Timer Module for HAL
 *    @{
 */

timer_ovf_callback_t timer_ovf_callbacks[TIMER_CHANNEL_COUNT];
#define IS_CHANNEL_VALID(channel) (channel < TIMER_CHANNEL_COUNT)

static inline BOOL timer_is_callback_valid(
    const timer_ovf_callback_t *const callback);
static inline U32 timer_get_interrupt_number(const timer_channel_t channel);
static __FORCEINLINE void timer_execute_callback(const timer_channel_t channel);

static inline BOOL
timer_is_callback_valid(const timer_ovf_callback_t *const callback)
{
    if ((NULLPTR == *callback) || (0 == *callback))
    {
        return FALSE;
    }
    return TRUE;
}

static __FORCEINLINE void
timer_execute_callback(const timer_channel_t channel)
{
    timer_ovf_callback_t callback = timer_ovf_callbacks[channel];

    if ((gp_tim_regs[channel]->SR & TIM_SR_UIF))
    {
        if (timer_is_callback_valid(&callback))
            callback();
        gp_tim_regs[channel]->SR &= ~TIM_SR_UIF;
    }
}

static inline U32
timer_get_interrupt_number(const timer_channel_t channel)
{
    U32 result = TIM14_IRQn;
    if (TIMER_CHANNEL_16 == channel)
        result = TIM16_IRQn;
    else if (TIMER_CHANNEL_17 == channel)
        result = TIM17_IRQn;
    else
        result = TIM14_IRQn;
    return result;
}

I8
hal_timer_init(const timer_config_t *const configs, U16 num_configs)
{
    for (U32 index = 0U; index < num_configs; ++index)
    {
        U8 channel = configs[index].channel;
        if (!IS_CHANNEL_VALID(channel))
            return -EINVAL;

        gp_tim_regs[channel]->PSC = configs[index].prescaler - 1U;
        gp_tim_regs[channel]->ARR = configs[index].reload - 1U;
        gp_tim_regs[channel]->CR1 &= ~TIM_CR1_DIR;
        gp_tim_regs[channel]->CR1 |= TIM_CR1_ARPE;
        gp_tim_regs[channel]->CR1 |= TIM_CR1_URS;
        gp_tim_regs[channel]->EGR |= TIM_EGR_UG;
    }

    return 0;
}

void
hal_timer_start(timer_channel_t const channel)
{
    if (!IS_CHANNEL_VALID(channel))
        return -EINVAL;

    gp_tim_regs[channel]->CNT = 0U;
    gp_tim_regs[channel]->DIER |= TIM_DIER_UIE;
    gp_tim_regs[channel]->SR &= ~TIM_SR_UIF;
    gp_tim_regs[channel]->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(timer_get_interrupt_number(channel));
}

void
hal_timer_stop(timer_channel_t const channel)
{
    if (!IS_CHANNEL_VALID(channel))
        return -EINVAL;

    NVIC_DisableIRQ(timer_get_interrupt_number(channel));
    gp_tim_regs[channel]->CR1 &= ~TIM_CR1_CEN;
    gp_tim_regs[channel]->SR &= ~TIM_SR_UIF;
    gp_tim_regs[channel]->CNT = 0U;
}

void
hal_timer_restart(timer_channel_t const channel)
{
    if (!IS_CHANNEL_VALID(channel))
        return -EINVAL;

    NVIC_DisableIRQ(timer_get_interrupt_number(channel));
    gp_tim_regs[channel]->CR1 &= ~TIM_CR1_CEN;
    gp_tim_regs[channel]->CNT = 0U;
    NVIC_EnableIRQ(timer_get_interrupt_number(channel));
    gp_tim_regs[channel]->CR1 |= TIM_CR1_CEN;
}

void
hal_timer_register_callback(timer_channel_t      channel,
                            timer_ovf_callback_t callback)
{
    if (!IS_CHANNEL_VALID(channel))
        return -EINVAL;

    if (!timer_is_callback_valid(&callback))
        return;

    timer_ovf_callbacks[channel] = callback;
}

U32
hal_timer_read(timer_channel_t const channel)
{
    if (!IS_CHANNEL_VALID(channel))
        return -EINVAL;

    return ((U32)gp_tim_regs[channel]->CNT);
}

void
hal_tim14_irq_handler()
{
    timer_execute_callback(TIMER_CHANNEL_14);
}

void
hal_tim16_irq_handler()
{
    timer_execute_callback(TIMER_CHANNEL_16);
}

void
hal_tim17_irq_handler()
{
    timer_execute_callback(TIMER_CHANNEL_17);
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
