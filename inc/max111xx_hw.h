/*
 * max111xx_hw.h
 *
 *  Created on: 01 sep. 2024
 *      Author: Ludo
 */

#ifndef __MAX111XX_HW_H__
#define __MAX111XX_HW_H__

#include "max111xx.h"
#include "types.h"

/*** MAX111XX HW functions ***/

/*!******************************************************************
 * \fn MAX111XX_status_t MAX111XX_HW_init(void)
 * \brief Init MAX111XX hardware interface.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		Function execution status.
 *******************************************************************/
MAX111XX_status_t MAX111XX_HW_init(void);

/*!******************************************************************
 * \fn MAX111XX_status_t MAX111XX_HW_de_init(void)
 * \brief Release MAX111XX hardware interface.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		Function execution status.
 *******************************************************************/
MAX111XX_status_t MAX111XX_HW_de_init(void);

/*!******************************************************************
 * \fn MAX111XX_status_t MAX111XX_HW_spi_write_read_16(uint16_t* tx_data, uint16_t* rx_data, uint8_t transfer_size)
 * \brief Write data to ADC over SPI interface.
 * \param[in]	tx_data: Byte array to send.
 * \param[in]	transfer_size: Number of bytes to send and receive.
 * \param[out] 	rx_data: Pointer to the received bytes.
 * \retval		Function execution status.
 *******************************************************************/
MAX111XX_status_t MAX111XX_HW_spi_write_read_16(uint16_t* tx_data, uint16_t* rx_data, uint8_t transfer_size);

/*!******************************************************************
 * \fn MAX111XX_status_t MAX111XX_HW_gpio_read_eoc(uint8_t* state)
 * \brief Read EOC GPIO state.
 * \param[in]  	none
 * \param[out] 	state: Pointer to byte that will indicate the pin state.
 * \retval		Function execution status.
 *******************************************************************/
MAX111XX_status_t MAX111XX_HW_gpio_read_eoc(uint8_t* state);

/*!******************************************************************
 * \fn MAX111XX_status_t MAX111XX_HW_delay_milliseconds(uint32_t delay_ms)
 * \brief Delay function.
 * \param[in]  	delay_ms: Delay to wait in ms.
 * \param[out] 	none
 * \retval		Function execution status.
 *******************************************************************/
MAX111XX_status_t MAX111XX_HW_delay_milliseconds(uint32_t delay_ms);

#endif /* __MAX111XX_HW_H__ */
