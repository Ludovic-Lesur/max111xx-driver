/*
 * max111xx.h
 *
 *  Created on: 01 sep. 2024
 *      Author: Ludo
 */

#ifndef __MAX111XX_H__
#define __MAX111XX_H__

#ifndef MAX111XX_DRIVER_DISABLE_FLAGS_FILE
#include "max111xx_driver_flags.h"
#endif
#include "types.h"

/*** MAX111XX macros ***/

#define MAX111XX_FULL_SCALE		((0b1 << MAX111XX_DRIVER_NUMBER_OF_BITS) - 1)

/*** MAX111XX structures ***/

/*!******************************************************************
 * \enum MAX111XX_status_t
 * \brief MAX111XX driver error codes.
 *******************************************************************/
typedef enum {
	// Driver errors.
	MAX111XX_SUCCESS = 0,
	MAX111XX_ERROR_NULL_PARAMETER,
	MAX111XX_ERROR_CHANNEL,
	MAX111XX_ERROR_CONVERSION_TIMEOUT,
	MAX111XX_ERROR_DOUT_CHANNEL,
	// Low level drivers errors.
	MAX111XX_ERROR_BASE_GPIO = 0x0100,
	MAX111XX_ERROR_BASE_SPI = (MAX111XX_ERROR_BASE_GPIO + MAX111XX_DRIVER_GPIO_ERROR_BASE_LAST),
	MAX111XX_ERROR_BASE_DELAY = (MAX111XX_ERROR_BASE_SPI + MAX111XX_DRIVER_SPI_ERROR_BASE_LAST),
	// Last base value.
	MAX111XX_ERROR_BASE_LAST = (MAX111XX_ERROR_BASE_DELAY + MAX111XX_DRIVER_DELAY_ERROR_BASE_LAST)
} MAX111XX_status_t;

/*!******************************************************************
 * \enum MAX111XX_channel_t
 * \brief MAX111XX channels list.
 *******************************************************************/
typedef enum {
	MAX111XX_CHANNEL_AIN0 = 0,
	MAX111XX_CHANNEL_AIN1,
	MAX111XX_CHANNEL_AIN2,
	MAX111XX_CHANNEL_AIN3,
#if (MAX111XX_DRIVER_NUMBER_OF_CHANNELS > 4)
	MAX111XX_CHANNEL_AIN4,
	MAX111XX_CHANNEL_AIN5,
	MAX111XX_CHANNEL_AIN6,
	MAX111XX_CHANNEL_AIN7,
#endif
#if (MAX111XX_DRIVER_NUMBER_OF_CHANNELS > 8)
	MAX111XX_CHANNEL_AIN8,
	MAX111XX_CHANNEL_AIN9,
	MAX111XX_CHANNEL_AIN10,
	MAX111XX_CHANNEL_AIN11,
	MAX111XX_CHANNEL_AIN12,
	MAX111XX_CHANNEL_AIN13,
	MAX111XX_CHANNEL_AIN14,
	MAX111XX_CHANNEL_AIN15,
#endif
	MAX111XX_CHANNEL_LAST
} MAX111XX_channel_t;

/*** MAX111XX functions ***/

/*!******************************************************************
 * \fn MAX111XX_status_t MAX111XX_init(void)
 * \brief Init MAX111XX driver.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		Function execution status.
 *******************************************************************/
MAX111XX_status_t MAX111XX_init(void);

/*!******************************************************************
 * \fn MAX111XX_status_t MAX111XX_de_init_init(void)
 * \brief Release MAX111XX driver.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		Function execution status.
 *******************************************************************/
MAX111XX_status_t MAX111XX_de_init(void);

/*!******************************************************************
 * \fn MAX111XX_status_t MAX111XX_convert_channel(MAX111XX_channel_t channel, uint16_t* adc_data_xbits)
 * \brief Perform a channel conversion.
 * \param[in]  	channel: Channel to convert.
 * \param[out] 	adc_data_xbits: Pointer to short that will contain the x-bits ADC data.
 * \retval		Function execution status.
 *******************************************************************/
MAX111XX_status_t MAX111XX_convert_channel(MAX111XX_channel_t channel, uint16_t* adc_data_xbits);

/*******************************************************************/
#define MAX111XX_exit_error(base) { ERROR_check_exit(max111xx_status, MAX111XX_SUCCESS, base) }

/*******************************************************************/
#define MAX111XX_stack_error(base) { ERROR_check_stack(max111xx_status, MAX111XX_SUCCESS, base) }

/*******************************************************************/
#define MAX111XX_stack_exit_error(base, code) { ERROR_check_stack_exit(max111xx_status, MAX111XX_SUCCESS, base, code) }

#endif /* __MAX111XX_H__ */
