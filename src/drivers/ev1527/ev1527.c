/**
********************************************************************************
* @file     ev1527.c
* @author   M.Niaraki
* @date     11/11/2023
* @brief    this module implements driver for EV1527 remote receiver
* @note     notes
  @verbatim
================================================================================
More information should come here
================================================================================
  @endverbatim
*/
#include "ev1527.h"
#include "hal_dio_cfg.h"
#include "hal_timer.h"

/** @addtogroup DRV
 *   @brief Driver layer external chips
 *   @{
 */

/** @defgroup EV1527 EV1527
 *   @brief EV1527 remote receiver
 *    @{
 */
const U8  NUM_BITS_PER_FRAME   = 24;
const U32 MIN_PREAMPLE_TIME_US = 9200U;
const U32 MIN_OFF_TIME_US      = 200U;
const U32 MAX_OFF_TIME_US      = 400U;

typedef struct
{
    timer_channel_t timer_channel;
    exti_channel_t  exti_channel;
    pin_t           rf_pin;
    _IO BOOL        IsPreambleDetected;
    _IO BOOL        IsFrameReadyToProcess;
    _IO U32         Code;
    _IO U32         CurrentPinChangeTime;
    _IO U32         LastPinChangeTime;
    _IO U32         LastBitDurationTime;
    _IO U8          BitIndex;
} ev1527_t;

static ev1527_t ev1527 = { 0 };
static void     ev1527_pin_change_callback(void);
static void     ev1527_counter_ovf_callback(void);
static void     reset_values(ev1527_t *const receiver);
static void     calc_pin_change_time(ev1527_t *const receiver);
static void     read_frame_bit(ev1527_t *const receiver);

static void
reset_values(ev1527_t *const receiver)
{
    receiver->BitIndex              = NUM_BITS_PER_FRAME - 1U;
    receiver->IsFrameReadyToProcess = FALSE;
    receiver->IsPreambleDetected    = FALSE;
    receiver->Code                  = 0;
    receiver->CurrentPinChangeTime  = 0;
    receiver->LastPinChangeTime     = 0;
}

static void
read_frame_bit(ev1527_t *const receiver)
{
    BOOL IsBitOne = (receiver->LastBitDurationTime < MAX_OFF_TIME_US)
                    && (receiver->LastBitDurationTime >= MIN_OFF_TIME_US);
    receiver->IsFrameReadyToProcess = (BOOL)(receiver->BitIndex == 0U);
    if (TRUE == IsBitOne)
        receiver->Code |= (1U << receiver->BitIndex);
    receiver->BitIndex = (receiver->BitIndex > 0U) ? --receiver->BitIndex : 0U;
}

static void
calc_pin_change_time(ev1527_t *const receiver)
{
    if (receiver->LastPinChangeTime > receiver->CurrentPinChangeTime)
    {
        receiver->LastBitDurationTime = (0xffffU - receiver->LastPinChangeTime)
                                        + receiver->CurrentPinChangeTime;
        return;
    }
    receiver->LastBitDurationTime
        = receiver->CurrentPinChangeTime - receiver->LastPinChangeTime;
}

static void
ev1527_pin_change_callback(void)
{
    static U32 timerValue = 0U;
    if (ev1527.IsFrameReadyToProcess)
        return;

    timerValue = hal_timer_read(ev1527.timer_channel);

    if (DIO_STATE_LOW == hal_dio_read(ev1527.rf_pin))
    {
        ev1527.LastPinChangeTime = timerValue;
        return;
    }

    ev1527.CurrentPinChangeTime = timerValue;
    calc_pin_change_time(&ev1527);

    if (ev1527.IsPreambleDetected)
    {
        read_frame_bit(&ev1527);
        return;
    }

    reset_values(&ev1527);
    ev1527.IsPreambleDetected
        = (U8)(ev1527.LastBitDurationTime >= MIN_PREAMPLE_TIME_US);
}

I8
drv_ev1527_init(timer_channel_t timer_channel,
                exti_channel_t  exti_channel,
                pin_t           rf_pin)
{
    if (hal_exti_register_callback(exti_channel, ev1527_pin_change_callback))
        return -EINVAL;

    ev1527.timer_channel = timer_channel;
    ev1527.exti_channel  = exti_channel;
    ev1527.rf_pin        = rf_pin;
    reset_values(&ev1527);

    return hal_timer_start(ev1527.timer_channel);
}

I8
drv_ev1527_read(U32 *const code)
{
    if (FALSE == ev1527.IsFrameReadyToProcess)
        return -EIO;
    *code = ev1527.Code;
    reset_values(&ev1527);
    return 0;
}

void
drv_ev1527_discard(void)
{
    reset_values(&ev1527);
}
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
