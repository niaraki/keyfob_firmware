/**
********************************************************************************
* @file     hal_dio_cfg.h
* @author   M.Niaraki
* @date     07/21/2023
* @brief    This header defines the DIO config defenitions
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_DIO_CFG_H
#define __HAL_DIO_CFG_H

#include "hal_common_defines.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup DIO DIO
 *    @{
 */
/** @defgroup DIO_CONFIG Config
 *    @{
 */

/** @addtogroup DIO_CONFIG_DS Data structures
 * @{
 **/

/**@brief Specify the mode of a pin <br/>
 * _PP means the pin is a push-pull(PP) pin.
 * _OD means the pin is a open-drain(OD) pin.
 **/
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

/**@brief Specify the status of internal resistor
 **/
typedef enum
{
    RES_DISABLE = (0U),
    PULLUP      = (1U),
    PULLDOWN    = (2U),
    DIO_NUM_RESISTOR
} dio_resistor_t;

/**@brief Specify the logic level
 * DIO_LOW (0)
 * DIO_HIGH (1)
 **/
typedef enum
{
    DIO_LOW = (0U),
    DIO_HIGH,
    DIO_NUM_PIN_STATE
} dio_state_t;

/**@brief Specify the switching speed of a pin
 **/
typedef enum
{
    SLOW          = (0U),
    MEDIUM        = (1U),
    FAST          = (3U),
    DIO_NUM_SPEED = (4U)
} dio_speed_t;

/**@brief Specify the alternate function of a pin
 **/
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

/**@brief Specify the config entry of a pin.
 * This structure is used by the DIO Configurations table
 * @see g_dio_config_table
 * @see hal_dio_init()
 * @see hal_dio_config()
 **/
typedef struct
{
    pin_t          channel;    /*!< Pin id*/
    dio_mode_t     mode;       /*!< Pin mode */
    dio_af_t       af;         /*!< Alternate function */
    dio_resistor_t resistor;   /*!< Internal resistor */
    dio_state_t default_state; /*!< Default logic state after initialization */
    dio_speed_t speed;         /*!< Switching speed */
} dio_config_t;

/** @}*/

#ifdef __cplusplus
extern "C"
{
#endif

    /** @addtogroup DIO_CONFIG_FUNC Functions
     * @{
     */

    const dio_config_t *hal_dio_cfg_get(void);
    U16                 hal_dio_cfg_get_size(void);

/** @}*/
#ifdef __cplusplus
}
#endif

/**  @}*/
/** @}*/
/** @}*/

#endif /* __HAL_DIO_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
