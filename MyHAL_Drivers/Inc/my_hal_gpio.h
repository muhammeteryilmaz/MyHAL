/*
 * my_hal_gpio.h
 *
 *  Created on: Jul 24, 2026
 *      Author: muhammet
 */

#ifndef INC_MY_HAL_GPIO_H_
#define INC_MY_HAL_GPIO_H_

#include <stdint.h>

// I defined registers that I need.


// MODER  REGISTER MODES
#define INPUT_MODE				0x00
#define OUTPUT_MODE				0x01
#define ALTRNT_FUNC_MODE		0x02
#define ANALOG_MODE				0x03

// GPIO OFFSET ADDRESSES
#define MODER_OFFSET_ADDR		0x00
#define OTYPER_OFFSET_ADDR		0x04
#define OSPEED_OFFSET_ADDR		0x08
#define PUPDR_OFFSET_ADDR		0x0C
#define IDR_OFFSET_ADDR			0x10
#define ODR_OFFSET_ADDR			0x14
#define BSRR_OFFSET_ADDR		0x18
#define AHB1ENR_OFFSET       	0x30

//GPIOx and GPIO clock base addresses
#define GPIOB_ADDR				0x40020400
#define RCC_BASE_ADDR        	0x40023800

#define GPIOB_IDR_ADDR			((volatile uint32_t *)(GPIOB_ADDR + IDR_OFFSET_ADDR))
#define GPIOB_ODR_ADDR			((volatile uint32_t *)(GPIOB_ADDR + ODR_OFFSET_ADDR))
#define GPIOB_BSRR_ADDR			((volatile uint32_t *)(GPIOB_ADDR + BSRR_OFFSET_ADDR))

#define RCC_AHB1ENR 			(*(volatile uint32_t *)(RCC_BASE_ADDR + AHB1ENR_OFFSET))

/*
 * GPIO port configuration structure.
 */
typedef struct
{
	uintptr_t port;
	uint8_t pin;
	uint8_t mode;
	uint8_t otype;
	uint8_t speed;
	uint8_t pupdr;
} GPIO_Config_t;

void GPIO_Init(void);
void GPIO_Port_Write(void);
void GPIO_Set_Pin(uintptr_t port, uint8_t pin);
void GPIO_Reset_Pin(uintptr_t port, uint8_t pin);
uint8_t GPIO_GetMode(uintptr_t port, uint8_t pin);
void GPIO_Port_Configure(uintptr_t port, uint8_t mode, uint8_t pin, uint32_t otype, uint32_t speed, uint32_t pupdr);



#endif /* INC_MY_HAL_GPIO_H_ */
