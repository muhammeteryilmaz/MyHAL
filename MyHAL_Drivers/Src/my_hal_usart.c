/*
 * usart.c
 *
 *  Created on: Aug 26, 2026
 *      Author: muhammet
 */


#include "my_hal_usart.h"


void RCC_APB2_USART1_Enable(void)
{
	RCC_APB2ENR |= (1U << 0x04); //USART Clock Enable
}

void USART_Enable(void)
{
	volatile uint32_t *usart_cr1 = (volatile uint32_t *)(USART1_ADDR+USART_CR1_OFFSET_ADDR);

	*usart_cr1 |= (1U << 0xD); //USART Enable
	*usart_cr1 |= (0U << 0xC); //M: Word Length = 8

}

void Set_USART1(void)
{

}
