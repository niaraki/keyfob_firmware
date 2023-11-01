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
    DIO_MODE_INPUT     = (0U),
    DIO_MODE_OUTPUT_PP = (1U),
    DIO_MODE_AF_PP     = (2U),
    DIO_MODE_ANALOG    = (3U),
    DIO_MODE_OUTPUT_OD = (4U),
    DIO_MODE_AF_OD     = (5U),
    DIO_MODE_COUNT
} dio_mode_t;

/**@brief Specify the status of internal resistor
 **/
typedef enum
{
    DIO_RES_DISABLE  = (0U),
    DIO_RES_PULLUP   = (1U),
    DIO_RES_PULLDOWN = (2U),
    DIO_RES_COUNT
} dio_resistor_t;

/**@brief Specify the logic level
 * DIO_LOW (0)
 * DIO_HIGH (1)
 **/
typedef enum
{
    DIO_STATE_LOW = (0U),
    DIO_STATE_HIGH,
    DIO_STATE_COUNT
} dio_state_t;

/**@brief Specify the switching speed of a pin
 **/
typedef enum
{
    DIO_SPEED_SLOW           = (0U),
    DIO_SPEED_MEDIUM         = (1U),
    DIO_SPEED_RESERVED_SPEED = (2U),
    DIO_SPEED_FAST           = (3U),
    DIO_SPEED_COUNT          = (4U)
} dio_speed_t;

/**@brief Specify the alternate function of a pin
 **/
typedef enum
{
    DIO_AF_0 = (0U),
    DIO_AF_1,
    DIO_AF_2,
    DIO_AF_3,
    DIO_AF_4,
    DIO_AF_5,
    DIO_AF_6,
    DIO_AF_7,
    DIO_AF_COUNT
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
