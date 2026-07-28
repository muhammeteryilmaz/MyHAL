/*
 * my_hal_gpio.c
 *
 *  Created on: Jul 24, 2026
 *      Author: muhammet
 */


#include "my_hal_gpio.h"

static GPIO_Config_t gpio;



/*
 * Starts GPIO Clock.
 */
void GPIO_Init(void)
{
	RCC_AHB1ENR |= (0x1U << 1U);
}

/*
 * Puts the gpio's values into the related registers.
 */
void GPIO_Port_Write(void)
{
	volatile uint32_t *moder = (volatile uint32_t *)(gpio.port + MODER_OFFSET_ADDR);
	volatile uint32_t *type = (volatile uint32_t *)(gpio.port + OTYPER_OFFSET_ADDR);
	volatile uint32_t *speed = (volatile uint32_t *)(gpio.port + OSPEED_OFFSET_ADDR);
	volatile uint32_t *pupdr = (volatile uint32_t *)(gpio.port + PUPDR_OFFSET_ADDR);

	*moder &= ~(0x3U << gpio.pin*2); //clear bits
	*moder |= (gpio.mode << gpio.pin*2); // set 0 and 1 bit as 01

	*type &= ~(0x3U << gpio.pin); //clear bits
	*type |= (gpio.otype << gpio.pin);

	*speed &= ~(0x3U << gpio.pin*2); //clear bits
	*speed |= (gpio.speed << gpio.pin*2);

	*pupdr &= ~(0x3U << gpio.pin*2); //clear bits
	*pupdr |= (gpio.pupdr << gpio.pin*2);
}

/*
 *
 * port: GPIOx, ex: GPIOB_ADDR
 *
 * mode: Input, output, function, analog. Ex:INPUT_MODE				0x00
 *
 * pin: 0-15
 *
 * OTYPE Reset Value: 		0x00000000 for all ports
 *
 * OSPEEDDR Reset Value: 	0x0C000000 for port A,  0x000000C0 for port B,  0x00000000 for other ports
 *
 * PUPDR Reset Values: 		0x64000000 for port A,  0x00000100 for port B   0x00000000 for other ports
 */
void GPIO_Port_Configure(uintptr_t port, uint8_t mode, uint8_t pin, uint32_t otype, uint32_t speed, uint32_t pupdr)
{

	if (pin <= 15)
	{
		gpio.port = port;
		gpio.mode = mode;
		gpio.pin = pin;
		gpio.otype = otype;
		gpio.speed = speed;
		gpio.pupdr = pupdr;

		GPIO_Port_Write();
	}
}


/*
 * Sets pin for output mode
 */
void GPIO_Set_Pin(uintptr_t port, uint8_t pin)
{

	volatile uint32_t *reg = ((volatile uint32_t *)(port + BSRR_OFFSET_ADDR));

	if (GPIO_GetMode(port, pin) == OUTPUT_MODE)
		*reg = (0x1U << pin);
}

/*
 * Resets pin for output mode
 */
void GPIO_Reset_Pin(uintptr_t port, uint8_t pin)
{

	volatile uint32_t *reg = ((volatile uint32_t *)(port + BSRR_OFFSET_ADDR));

	if (GPIO_GetMode(port, pin) == OUTPUT_MODE)
		*reg = (0x1U << (16U + pin));

}

/*
 * return Port Mode such as Output, Input, Alternate Function, and analog.
 */
uint8_t GPIO_GetMode(uintptr_t port, uint8_t pin)
{
	volatile uint32_t *moder = (volatile uint32_t *)(port + MODER_OFFSET_ADDR);

	uint32_t port_mode = *moder;

	uint32_t mask = 0;

	mask |= (0x03U << (pin*2U));

	port_mode &= mask;

	port_mode = (port_mode >> (pin*2U));

	if (port_mode == 0x01)
		return OUTPUT_MODE;
	if (port_mode == 0x00)
		return INPUT_MODE;
	if (port_mode == 0x02)
		return ALTRNT_FUNC_MODE;
	if (port_mode == 0x03)
		return ANALOG_MODE;
	else
		return UINT8_MAX;
}

