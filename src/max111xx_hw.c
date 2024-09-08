/*
 * max111xx_hw.c
 *
 *  Created on: 01 sep. 2024
 *      Author: Ludo
 */

#include "max111xx_hw.h"

#ifndef MAX111XX_DRIVER_DISABLE_FLAGS_FILE
#include "max111xx_driver_flags.h"
#endif
#include "max111xx.h"
#include "types.h"

#ifndef MAX111XX_DRIVER_DISABLE

/*** MAX111XX HW functions ***/

/*******************************************************************/
MAX111XX_status_t __attribute__((weak)) MAX111XX_HW_init(void) {
	// Local variables.
	MAX111XX_status_t status = MAX111XX_SUCCESS;
	/* To be implemented */
	return status;
}

/*******************************************************************/
MAX111XX_status_t __attribute__((weak)) MAX111XX_HW_de_init(void) {
	// Local variables.
	MAX111XX_status_t status = MAX111XX_SUCCESS;
	/* To be implemented */
	return status;
}

/*******************************************************************/
MAX111XX_status_t __attribute__((weak)) MAX111XX_HW_spi_write_read_16(uint16_t* tx_data, uint16_t* rx_data, uint8_t transfer_size) {
	// Local variables.
	MAX111XX_status_t status = MAX111XX_SUCCESS;
	/* To be implemented */
	UNUSED(tx_data);
	UNUSED(rx_data);
	UNUSED(transfer_size);
	return status;
}

/*******************************************************************/
MAX111XX_status_t __attribute__((weak)) MAX111XX_HW_gpio_read_eoc(uint8_t* state) {
	// Local variables.
	MAX111XX_status_t status = MAX111XX_SUCCESS;
	/* To be implemented */
	UNUSED(state);
	return status;
}

/*******************************************************************/
MAX111XX_status_t __attribute__((weak)) MAX111XX_HW_delay_milliseconds(uint32_t delay_ms) {
	// Local variables.
	MAX111XX_status_t status = MAX111XX_SUCCESS;
	/* To be implemented */
	UNUSED(delay_ms);
	return status;
}

#endif /* MAX111XX_DRIVER_DISABLE */
