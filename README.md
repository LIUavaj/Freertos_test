# Freertos_test

STM32F103C8 embedded project generated with STM32CubeMX and developed with Keil MDK-ARM.

## Project layout

- `Core/`: application entry point, interrupt handlers, and HAL configuration.
- `Drivers/`: STM32 HAL and CMSIS dependencies.
- `User/`: application and LED device code.
- `MDK-ARM/`: Keil project, startup code, and debug configuration.
- `freertos_test_01.ioc`: STM32CubeMX configuration.

## Build

Open `MDK-ARM/freertos_test_01.uvprojx` in Keil uVision, install the STM32F1 device pack, and build the project. The project is configured for ARM Compiler 5.

Generated build output and personal IDE settings are excluded from Git.
