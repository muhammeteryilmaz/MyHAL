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
void GPIO_Enable(void)
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

	*type &= ~(0x1U << gpio.pin); //clear bits
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
void GPIO_Port_Configure(uintptr_t port, GPIO_Moder_t mode, uint8_t pin, GPIO_Type_t otype, GPIO_Speed_t speed, GPIO_Pull_t pupdr)
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
	if (GPIO_GetMode(port, pin) == GPIO_OUTPUT_MODE)
	{
		volatile uint32_t *reg = ((volatile uint32_t *)(port + BSRR_OFFSET_ADDR));
		*reg = (0x1U << pin);
	}
}

/*
 * Resets pin for output mode
 */
void GPIO_Reset_Pin(uintptr_t port, uint8_t pin)
{

	if (GPIO_GetMode(port, pin) == GPIO_OUTPUT_MODE)
	{
		volatile uint32_t *reg = ((volatile uint32_t *)(port + BSRR_OFFSET_ADDR));
		*reg = (0x1U << (16U + pin));
	}
}

GPIO_Pin_State_t GPIO_Read_Pin(uintptr_t port, uint8_t pin)
{
	volatile uint32_t *idr = ((volatile uint32_t *)(port + IDR_OFFSET_ADDR));

	uint32_t current_idr = *idr;

	uint32_t mask = 0;

	mask |= (0x01U << pin);

	current_idr &= mask;

	current_idr = (current_idr >> pin);

	if (current_idr == 1U)
		return SET_STATE;
	if (current_idr == 0U)
		return RESET_STATE;
	return RESET_STATE;
}

void GPIO_Pin_Toggle(uintptr_t port, uint8_t pin)
{

	if (GPIO_GetMode(port, pin) == GPIO_OUTPUT_MODE)
	{
		volatile uint32_t *odr = ((volatile uint32_t *)(port + ODR_OFFSET_ADDR));
		*odr ^= (1U << pin);
	}

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
		return GPIO_OUTPUT_MODE;
	if (port_mode == 0x00)
		return GPIO_INPUT_MODE;
	if (port_mode == 0x02)
		return GPIO_ALTRNT_FUNC_MODE;
	if (port_mode == 0x03)
		return GPIO_ANALOG_MODE;
	else
		return UINT8_MAX;
}

