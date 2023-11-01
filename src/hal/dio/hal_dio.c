/**
********************************************************************************
* @file     hal_dio.c
* @author   M.Niaraki
* @date     07/21/2023
* @brief    Implements internals of the DIO module
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include "hal.h"
#include "hal_dio_cfg.h"
#include "hal_pins.h"
#include "hll.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup DIO DIO
 *   @brief Digital Input/Output module
 *    @{
 */

/**@addtogroup DIO_MACRO Macros
 * @brief Private macros
 * @{
 **/

/**@brief This macro creates the final value for those registers that contain
 *two bits of configuration for each pin
 **/
#define VALUE_BY_INDEX(VAL, IDX) ((VAL) << (IDX * (2U)))

/** @}*/

/**@addtogroup DIO_DS Data structures
 * @brief Data structures used by private functions
 * @{
 **/

/**@brief Detail information about the selected channel
 **/
typedef struct
{
    _IO U8  port_index;    /**!< Index of the port that contains the pin */
    _IO U8  pin_index;     /**!< Index of the pin in the port*/
    _IO U32 pin_mask;      /**!< Bit mask according to pin index*/
    _IO GPIO_TypeDef *reg; /**!< Corresponding reg. defined in the HLL*/
} dio_channel_info_t;

/** @}*/

/**@brief Calc more information about the channel
 * @param channel is the selected pin
 * @retval dio_channel_info_t which contains more detail about the selected
 * pin*/
static inline dio_channel_info_t
dio_get_channel_info(pin_t channel)
{
    dio_channel_info_t result = { 0U };
    result.port_index         = (((U8)channel) / NUM_PIN_IN_PORT);
    result.pin_index          = (((U8)channel) % NUM_PIN_IN_PORT);
    result.pin_mask           = ((1UL) << result.pin_index);
    /* Link the corresponding register from the HLL for the specified channel*/
    if (result.port_index >= NUM_PORTS)
        result.port_index = 0;
    result.reg = gp_dio_regs[result.port_index];
    return result;
}

/**@brief Check config parameters before applying them to registers
 * @param Pointer to the required settings
 * @retval None
 **/
static inline void
assert_config_params(const dio_config_t *const config)
{
    ASSERT(config->channel < NUM_PINS);
    ASSERT(config->mode < DIO_MODE_COUNT);
    /* Speed value 2, has been reserved by ST*/
    ASSERT((config->speed < DIO_SPEED_COUNT)
           && (DIO_SPEED_RESERVED_SPEED != config->speed));
    ASSERT(config->af < DIO_AF_COUNT);
    ASSERT(config->resistor < DIO_RES_COUNT);
    ASSERT(config->default_state < DIO_STATE_COUNT);
}

/**@brief Set MODER and OTYPER registers according to the passed config.
 * @param config is required settings
 * @param chi is channel information
 * @retval None
 **/
static inline void
set_mode(const dio_config_t *const config, dio_channel_info_t *chi)
{
    U8 pin_mode = ((U8)config->mode);
    chi->reg->OTYPER &= ~((chi->pin_mask)); /*Clear OTYPER for the pin*/
    chi->reg->OTYPER
        |= ((config->mode) >= DIO_MODE_OUTPUT_OD) ? chi->pin_mask : (0UL);
    /*Make AF_OD(5) and OUTPUT_OD(4) to the range of MODER register*/
    if (config->mode > DIO_MODE_ANALOG)
    {
        pin_mode -= 3;
    }
    /*Clear and set MODER for the pin*/
    chi->reg->MODER &= ~VALUE_BY_INDEX(3U, chi->pin_index);
    chi->reg->MODER |= VALUE_BY_INDEX(pin_mode, chi->pin_index);
}

/**@brief Set OSPEEDR register which specifies the switching speed of a pin
 * @param config is the required settings
 * @param chi as the channel information
 * @retval None
 **/
static inline void
set_speed(const dio_config_t *const config, const dio_channel_info_t *const chi)
{
    U8 speed = (U8)config->speed;
    /*Clear and set OSPEEDR register for the pin*/
    chi->reg->OSPEEDR &= ~VALUE_BY_INDEX(3U, chi->pin_index);
    chi->reg->OSPEEDR |= VALUE_BY_INDEX(speed, chi->pin_index);
}

/**@brief Set PUPDR register which specifies pull-up/down status of the internal
 *resistor
 * @param config is the required settings
 * @param chi as the channel information
 * @retval None
 **/
static inline void
set_resistor(const dio_config_t *const       config,
             const dio_channel_info_t *const chi)
{
    U8 resistor = (U8)config->resistor;
    /*Clear and set PUPDR register for the pin*/
    chi->reg->PUPDR &= ~VALUE_BY_INDEX(3U, chi->pin_index);
    chi->reg->PUPDR |= VALUE_BY_INDEX(resistor, chi->pin_index);
}

/**@brief Set registers for Alternate Functions (Multiplexed
 *functions of a pin)
 * @param config is the required settings
 * @param chi as the channel information
 * @retval None
 **/
static inline void
set_af(const dio_config_t *const config, const dio_channel_info_t *const chi)
{
    /*According to the page 138 of the STM32f030 DM, we have two 32-bit
     * registers for specifing the alternate functions for each pin. So, we
     * should setup 4-bit for each pin. the following code calculates the start
     * bit-index of the specified pin as well as the corresponding index of the
     * AFR register*/
    U8 af_value   = (U8)config->af;
    U8 af_reg_idx = 0U;
    if (chi->pin_index < 8U)
        af_reg_idx = 1U;
    U8 af_bit_idx = (chi->pin_index % (NUM_PIN_IN_PORT / 2U));

    /*Clear and set AFR register for the pin*/
    chi->reg->AFR[af_reg_idx] &= ~((7U) << (af_bit_idx * (4U)));
    chi->reg->AFR[af_reg_idx] |= ((af_value) << (af_bit_idx * (4U)));
}

/**@brief Set the value for a pin according to BSRR and BRR registers
 * @param config is the required settings
 * @param chi as the channel information
 * @retval None
 * @note This function uses BSRR and BRR registers. So, it is atomic.
 **/
static inline void
set_state(dio_channel_info_t *channel_info, dio_state_t state)
{
    if (DIO_STATE_HIGH == state)
    {
        channel_info->reg->BSRR |= (channel_info->pin_mask);
    }
    else
    {
        channel_info->reg->BRR |= (channel_info->pin_mask);
    }
}

/** @defgroup DIO_API API
 *   @brief Application Programming Interface
 *   @{
 */

/**@brief Config the pin according to specified settings
 * @param config is the selected settings for the pin
 * @retval None
 * @see dio_config_t
 **/
void
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

/**@brief Initialize DIO pins according to the DIO configurations table.
 * @see g_dio_config_table
 * @param configs is the pointer to the configurations table. you can get the
 * pointer by calling hal_dio_cfg_get()
 * @param num_configs specifies the number of enteries in the conf. table. you
 *can get the size by calling the hal_dio_cfg_get_size()
 * @see hal_dio_cfg_get()
 * @see hal_dio_cfg_get_size()
 * @retval None
 **/
void
hal_dio_init(const dio_config_t *const configs, U16 num_configs)
{
    ASSERT(NULLPTR != configs);

    for (U16 index = 0U; index < num_configs; index++)
    {
        hal_dio_config(&configs[index]);
    }
}

/**@brief Set the state of the pin to high or low
 * @param channel is the selected pin
 * @param state is the new value for the pin
 * @arg DIO_LOW -> logic 0
 * @arg DIO_HIGH -> logic 1
 * @retval None
 * @code
 * hal_dio_write(PA0, DIO_HIGH);
 * @endcode
 **/
void
hal_dio_write(pin_t channel, dio_state_t state)
{
    ASSERT((state < DIO_STATE_HIGH));
    ASSERT((channel < NUM_PINS));

    dio_channel_info_t chi = dio_get_channel_info(channel);
    set_state(&chi, state);
}

/**@brief Toggle the state of the pin
 * @param channel is the selected pin
 * @retval None
 * @code
 * hal_dio_toggle(PA0);
 * @endcode
 * @see pin_t
 **/
void
hal_dio_toggle(pin_t channel)
{
    ASSERT((channel < NUM_PINS));

    dio_channel_info_t chi = dio_get_channel_info(channel);
    U32                odr = chi.reg->ODR;
    chi.reg->BSRR
        = ((odr & chi.pin_mask) << NUM_PIN_IN_PORT) | (~odr & chi.pin_mask);
}

/**@brief Read the state of the pin
 * @param channel is the selected pin
 * @retval None
 * @code
 * dio_state_t state = hal_dio_read(PA0);
 * @endcode
 * @see pin_t
 **/
dio_state_t
hal_dio_read(pin_t channel)
{
    ASSERT((channel < NUM_PINS));

    dio_state_t        result = DIO_STATE_LOW;
    dio_channel_info_t chi    = dio_get_channel_info(channel);
    if ((chi.pin_mask & chi.reg->IDR) == chi.pin_mask)
    {
        result = DIO_STATE_HIGH;
    }

    return result;
}

/**@brief Write the new value the port
 * @param port is the selected port.
 * @param value is the value of the port.
 * @retval None
 * @attention this implementation is based on ODR register. So, it is not
 *atomic.
 * @code
 * hal_dio_write_port(PORTA, 0xFFFFFFFF);
 * @endcode
 * @see port_t
 **/
void
hal_dio_write_port(port_t port, U32 value)
{
    ASSERT(port < NUM_PORTS);
    if (port < NUM_PORTS)
    {
        gp_dio_regs[port]->ODR = value;
    }
}

/**@brief Read the value of the port
 * @param port is the selected port.
 * @attention this implementation is based on ODR register. So, it is not
 *atomic.
 * @code
 * U32 val = hal_dio_read_port(PORTA);
 * @endcode
 **/
U32
hal_dio_read_port(port_t port)
{
    U32 result = 0;
    ASSERT(port < NUM_PORTS);
    if (port < NUM_PORTS)
    {
        result = gp_dio_regs[port]->ODR;
    }
    return result;
}

/** @}*/
/** @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
