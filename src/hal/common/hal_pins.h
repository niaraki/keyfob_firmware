/**
********************************************************************************
* @file     hal_pins.h
* @author   M.Niaraki
* @date     07/22/2023
* @brief    This header is used to define pins of the MCU
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_PINS_H
#define __HAL_PINS_H

#define NUM_PIN_IN_PORT (16U)

typedef enum
{
    PORTA = (0U),
    PORTB,
    NUM_PORTS
} port_t;

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
    NUM_PINS
} pin_t;

#endif /* __HAL_PINS_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
