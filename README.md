# Description

This repository contains the **MAX111xx** ADC driver (MAX11135 to MAX11143).

# Dependencies

The driver relies on:

* An external `types.h` header file defining the **standard C types** of the targeted MCU.
* The **embedded utility functions** defined in the [embedded-utils](https://github.com/Ludovic-Lesur/embedded-utils) repository.

Here is the versions compatibility table:

| **max111xx-driver** | **embedded-utils** |
|:---:|:---:|
| [sw2.0](https://github.com/Ludovic-Lesur/max111xx-driver/releases/tag/sw2.0) | >= [sw1.3](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw1.3) |
| [sw1.0](https://github.com/Ludovic-Lesur/max111xx-driver/releases/tag/sw1.0) | >= [sw1.3](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw1.3) |

# Compilation flags

| **Flag name** | **Value** | **Description** |
|:---:|:---:|:---:|
| `MAX111XX_DRIVER_DISABLE_FLAGS_FILE` | `defined` / `undefined` | Disable the `max111xx_driver_flags.h` header file inclusion when compilation flags are given in the project settings or by command line. |
| `MAX111XX_DRIVER_DISABLE` | `defined` / `undefined` | Disable the MAX111xx driver. |
| `MAX111XX_DRIVER_GPIO_ERROR_BASE_LAST` | `<value>` | Last error base of the low level GPIO driver. |
| `MAX111XX_DRIVER_SPI_ERROR_BASE_LAST` | `<value>` | Last error base of the low level SPI driver. |
| `MAX111XX_DRIVER_DELAY_ERROR_BASE_LAST` | `<value>` | Last error base of the low level delay driver. |
| `MAX111XX_DRIVER_NUMBER_OF_CHANNELS` | `4` / `8` / `16` | Number of channels of the ADC (depends on part number, refer to datasheet). |
| `MAX111XX_DRIVER_NUMBER_OF_BITS` | `8` / `10` / `12` | Number of bits of the ADC (depends on part number, refer to datasheet). |
