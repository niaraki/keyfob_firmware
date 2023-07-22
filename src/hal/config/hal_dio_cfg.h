/**
********************************************************************************
* @file     hal_dio_cfg.h
* @author   M.Niaraki
* @date     07/21/2023
* @brief    This header defines DIO config defenitions
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_DIO_CFG_H
#define __HAL_DIO_CFG_H

#include "hal_common_defines.h"

#define NUM_PIN_IN_PORT (16U)

typedef enum
{
    PA0 = (0U),
    PA1,
    PA2,
    PA3,
    PA4,
    PA5,
    PA6,
    PA7,
    PA8,
    PA9,
    PA10,
    PA11,
    PA12,
    PA13,
    PA14,
    PA15,
    PB0,
    PB1,
    PB2,
    PB3,
    PB4,
    PB5,
    PB6,
    PB7,
    PB8,
    PB9,
    PB10,
    PB11,
    PB12,
    PB13,
    PB14,
    PB15,
    DIO_NUM_CHANNEL
} dio_channel_t;

typedef enum
{
    INPUT     = (0U),
    OUTPUT_PP = (1U),
    AF_PP     = (2U),
    ANALOG    = (3U),
    OUTPUT_OD = (4U),
    AF_OD     = (5U),
    DIO_NUM_MODE
} dio_mode_t;

typedef enum
{
    RES_DISABLE = (0U),
    PULLUP      = (1U),
    PULLDOWN    = (2U),
    DIO_NUM_RESISTOR
} dio_resistor_t;

typedef enum
{
    DIO_LOW = (0U),
    DIO_HIGH,
    DIO_NUM_PIN_STATE
} dio_state_t;

typedef enum
{
    SLOW          = (0U),
    MEDIUM        = (1U),
    FAST          = (3U),
    DIO_NUM_SPEED = (4U)
} dio_speed_t;

typedef enum
{
    AF_0 = (0U),
    AF_1,
    AF_2,
    AF_3,
    AF_4,
    AF_5,
    AF_6,
    AF_7,
    DIO_NUM_AF
} dio_af_t;

typedef enum
{
    EXTI_DISABLE = (0UL),
    EXTI_RISING,
    EXTI_FALLING,
    EXTI_BOTH_EDGES,
    DIO_NUM_EXTI
} dio_exti_t;

typedef struct
{
    dio_channel_t  channel;
    dio_mode_t     mode;
    dio_af_t       af;
    dio_resistor_t resistor;
    dio_state_t    default_state;
    dio_speed_t    speed;
    dio_exti_t     exti;
} dio_config_t;

#ifdef __cplusplus
extern "C"
{
#endif

    const dio_config_t *hal_dio_cfg_get(void);
    U16                 hal_dio_cfg_get_size(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_DIO_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
