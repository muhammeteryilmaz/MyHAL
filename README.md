# MyHAL

A custom Hardware Abstraction Layer (HAL) developed for STM32 microcontrollers using direct register access.

> **Project Status:** Work in Progress

---

## About

MyHAL is a personal learning project focused on understanding STM32 peripherals by implementing a custom Hardware Abstraction Layer from scratch instead of relying on the STM32 HAL library.

The main objectives are:

- Learn STM32 peripherals at register level.
- Improve embedded software architecture skills.
- Develop reusable peripheral drivers.
- Minimize dependency on vendor libraries.

---

## Features

### Current

- [x] GPIO (In Progress)

### Planned

- [ ] UART
- [ ] SPI
- [ ] I2C
- [ ] ADC
- [ ] DMA

---

## Project Structure

```text
MyHAL/
├── Core/
├── Drivers/
├── MyHAL_Drivers/
│   ├── Inc/
│   └── Src/
├── STM32F446ZETX_FLASH.ld
├── MyHAL.ioc
├── README.md
├── LICENSE
└── .gitignore
```

---

## Development

The custom drivers are located in:

```text
MyHAL_Drivers/
```

The STM32CubeIDE generated files are kept only to provide:

- Startup code
- Linker script
- CMSIS support
- Project configuration

The peripheral drivers inside **MyHAL_Drivers** are implemented manually using direct register access.

---

## Target MCU

- STM32F446ZET6

---

## Toolchain

- STM32CubeIDE
- ARM GCC (arm-none-eabi-gcc)
- Git
- GitHub

---

## License

This project is licensed under the MIT License.
