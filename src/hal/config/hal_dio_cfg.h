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
    DIO_MAX_CHANNEL_NUMBER
} dio_channel_t;

typedef enum
{
    DIO_INPUT = (0U),
    DIO_OUTPUT,
    DIO_AF1,
    DIO_AF2,
    DIO_AF3,
    DIO_MAX_MODE
} dio_mode_t;

typedef enum
{
    DIO_PULLUP = 0,
    DIO_PULLDOWN,
    DIO_OPENDRAIN,
    DIO_MAX_RESISTOR
} dio_resistor_t;

typedef enum
{
    DIO_LOW = (0U),
    DIO_HIGH,
    DIO_MAX_PIN_STATE
} dio_state_t;

typedef enum
{
    DIO_SLOW = (0U),
    DIO_FAST,
    DIO_MAX_SPEED
} dio_speed_t;

typedef struct
{
    dio_channel_t  channel;
    dio_mode_t     mode;
    dio_resistor_t resistor;
    dio_speed_t    speed;
} dio_config_t;

#ifdef __cplusplus
extern "C"
{
#endif

    const dio_config_t *hal_dio_cfg_get(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_DIO_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
