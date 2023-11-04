/**
********************************************************************************
* @file     hal_exti_cfg.h
* @author   M.Niaraki
* @date     11/03/2023
* @brief    This header defines the EXTI config defenitions
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_ETXI_CFG_H
#define __HAL_ETXI_CFG_H

#include "hal_common_defines.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup EXTI EXTI
 *    @{
 */
/** @defgroup EXTI_CONFIG Config
 *    @{
 */

/** @addtogroup EXTI_CONFIG_DS Data structures
 * @{
 **/

/**@brief Specify the external interrupt channel number <br/>
 **/
typedef enum
{
    EXTI_CHANNEL_0 = (0U),
    EXTI_CHANNEL_1,
    EXTI_CHANNEL_2,
    EXTI_CHANNEL_3,
    EXTI_CHANNEL_4,
    EXTI_CHANNEL_5,
    EXTI_CHANNEL_6,
    EXTI_CHANNEL_7,
    EXTI_CHANNEL_8,
    EXTI_CHANNEL_9,
    EXTI_CHANNEL_10,
    EXTI_CHANNEL_11,
    EXTI_CHANNEL_12,
    EXTI_CHANNEL_13,
    EXTI_CHANNEL_14,
    EXTI_CHANNEL_15,
    EXTI_CHANNEL_COUNT,
} exti_channel_t;

typedef enum
{
    EXTI_PRIORITY_HIGHEST = (0U),
    EXTI_PRIORITY_HIGH,
    EXTI_PRIORITY_NORMAL,
    EXTI_PRIORITY_LOW,
    EXTI_PRIORITY_COUNT,
} exti_priority_t;

typedef enum
{
    EXTI_MODE_FALLING_EDGE = (0U),
    EXTI_MODE_RISING_EDGE,
    EXTI_MODE_BOTH_EDGE,
    EXTI_MODE_COUNT,
} exti_mode_t;

typedef struct
{
    exti_channel_t  channel;
    port_t          port;
    exti_mode_t     mode;
    exti_priority_t priority;
} exti_config_t;

/** @}*/

#ifdef __cplusplus
extern "C"
{
#endif

    /** @addtogroup EXTI_CONFIG_FUNC Functions
     * @{
     */

    const exti_config_t *hal_exti_cfg_get(void);
    U16                  hal_exti_cfg_get_size(void);

/** @}*/
#ifdef __cplusplus
}
#endif

/**  @}*/
/** @}*/
/** @}*/

#endif /* __HAL_ETXI_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
