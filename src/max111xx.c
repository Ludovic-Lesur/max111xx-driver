/*
 * max111xx.c
 *
 *  Created on: 01 sep. 2024
 *      Author: Ludo
 */

#include "max111xx.h"

#ifndef MAX111XX_DRIVER_DISABLE_FLAGS_FILE
#include "max111xx_driver_flags.h"
#endif
#include "max111xx_hw.h"
#include "types.h"

#ifndef MAX111XX_DRIVER_DISABLE

/*** MAX111XX local macros ***/

#define MAX111XX_SUB_DELAY_MS   100
#define MAX111XX_TIMEOUT_MS     2000

/*** MAX111XX local structures ***/

/*******************************************************************/
typedef enum {
    MAX111XX_REGISTER_ADC_MODE_CONTROL = 0b00000,
    MAX111XX_REGISTER_ADC_CONFIG = 0b10000,
    MAX111XX_REGISTER_UNIPOLAR = 0b10001,
    MAX111XX_REGISTER_BIPOLAR = 0b10010,
    MAX111XX_REGISTER_RANGE = 0b10011,
    MAX111XX_REGISTER_CUSTOM_SCAN0 = 0b10100,
    MAX111XX_REGISTER_CUSTOM_SCAN1 = 0b10101,
    MAX111XX_REGISTER_SAMPLE_SET = 0b10110,
    MAX111XX_REGISTER_LAST = 0b10111
} MAX111XX_register_t;

/*******************************************************************/
typedef union {
    struct {
        unsigned data :12;
        unsigned channel :4;
    } __attribute__((scalar_storage_order("little-endian")))__attribute__((packed));
    uint16_t value;
} MAX111XX_dout_t;

/*** MAX111XX local functions ***/

/*******************************************************************/
static MAX111XX_status_t _MAX111XX_write_register(MAX111XX_register_t register_address, uint16_t value) {
    // Local variables.
    MAX111XX_status_t status = MAX111XX_SUCCESS;
    uint16_t spi_command = 0;
    uint16_t spi_reply = 0;
    // Build SPI command.
    if (register_address == MAX111XX_REGISTER_ADC_MODE_CONTROL) {
        // Data is 15-bits length.
        spi_command |= value & 0x00007FFF;
    }
    else {
        // Data is 11-bits length.
        spi_command |= (register_address & 0x0000001F) << 11;
        spi_command |= (value & 0x000007FF);
    }
    // SPI transfer.
    status = MAX111XX_HW_spi_write_read_16(&spi_command, &spi_reply, 1);
    if (status != MAX111XX_SUCCESS) goto errors;
errors:
    return status;
}

/*** MAX111XX functions ***/

/*******************************************************************/
MAX111XX_status_t MAX111XX_init(void) {
    // Local variables.
    MAX111XX_status_t status = MAX111XX_SUCCESS;
    // Init hardware interface.
    status = MAX111XX_HW_init();
    if (status != MAX111XX_SUCCESS) goto errors;
errors:
    return status;
}

/*******************************************************************/
MAX111XX_status_t MAX111XX_de_init(void) {
    // Local variables.
    MAX111XX_status_t status = MAX111XX_SUCCESS;
    // Release hardware interface.
    status = MAX111XX_HW_de_init();
    if (status != MAX111XX_SUCCESS) goto errors;
errors:
    return status;
}

/*******************************************************************/
MAX111XX_status_t MAX111XX_convert_channel(MAX111XX_channel_t channel, int32_t* adc_data_xbits) {
    // Local variables.
    MAX111XX_status_t status = MAX111XX_SUCCESS;
    uint16_t spi_command = 0;
    uint8_t eoc_state = 0;
    MAX111XX_dout_t dout = { .value = 0 };
    uint32_t loop_count_ms = 0;
    // Check parameters.
    if (channel >= MAX111XX_CHANNEL_LAST) {
        status = MAX111XX_ERROR_CHANNEL;
        goto errors;
    }
    if (adc_data_xbits == NULL) {
        status = MAX111XX_ERROR_NULL_PARAMETER;
        goto errors;
    }
    // Configure ADC.
    // Single-ended unipolar (already done at POR).
    // Enable averaging: AVGON='1' and NAVG='00' (4 conversions).
    status = _MAX111XX_write_register(MAX111XX_REGISTER_ADC_CONFIG, 0x0200);
    if (status != MAX111XX_SUCCESS) goto errors;
    // Select channel.
    status = _MAX111XX_write_register(MAX111XX_REGISTER_CUSTOM_SCAN1, (0b1 << (channel + 3)));
    if (status != MAX111XX_SUCCESS) goto errors;
    // Scan mode = custom internal: SCAN='0111'.
    // Reset the FIFO: RESET='01'.
    // Auto shutdown: PM='01'.
    // Start conversion: SWCNV='1'.
    status = _MAX111XX_write_register(MAX111XX_REGISTER_ADC_MODE_CONTROL, 0x382A);
    if (status != MAX111XX_SUCCESS) goto errors;
    // Wait for EOC to be pulled low.
    do {
        // Intermediate delay.
        status = MAX111XX_HW_delay_milliseconds(MAX111XX_SUB_DELAY_MS);
        if (status != MAX111XX_SUCCESS) goto errors;
        // Read GPIO.
        status = MAX111XX_HW_gpio_read_eoc(&eoc_state);
        if (status != MAX111XX_SUCCESS) goto errors;
        // Exit if timeout.
        loop_count_ms += MAX111XX_SUB_DELAY_MS;
        if (loop_count_ms > MAX111XX_TIMEOUT_MS) {
            status = MAX111XX_ERROR_CONVERSION_TIMEOUT;
            goto errors;
        }
    }
    while (eoc_state != 0);
    
    // SPI transfer.
    status = MAX111XX_HW_spi_write_read_16(&spi_command, &(dout.value), 1);
    if (status != MAX111XX_SUCCESS) goto errors;
    // Check output data.
    if (dout.channel != channel) {
        status = MAX111XX_ERROR_DOUT_CHANNEL;
        goto errors;
    }
    // Parse output data.
    (*adc_data_xbits) = (int32_t) ((dout.data >> (12 - MAX111XX_DRIVER_NUMBER_OF_BITS)) & MAX111XX_FULL_SCALE);
errors:
    return status;
}

#endif /* MAX111XX_DRIVER_DISABLE */
