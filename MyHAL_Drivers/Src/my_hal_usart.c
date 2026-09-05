/*
 * usart.c
 *
 *  Created on: Aug 26, 2026
 *      Author: muhammet
 */


#include "my_hal_usart.h"


void RCC_APB2_USART1_Enable(void)
{
	RCC_APB2ENR |= (1U << 0x04); // USART Clock Enable
}

void USART_TX_Enable(void)
{


	USART_CR1 |= (1U << 0x0D); // USART Enable
	USART_CR1 |= (0U << 0x0C); // M: Word Length = 8
	USART_CR2 |= (0U << 0x0C); // Number of stop bits
	USART_CR1 |= (0U << 0x0F); // OVER8 bit is 0 for Baud rate calculations.
	USART_BRR = USART_BRR | (0x222 << 0x04) | (0xE << 0x0); // 546.875 value for 9600 baudrate with 84 MHz PCLK
	USART_CR1 |= (0U << 0x0B); // WAKE is 0, IDLE LINE MODE
	USART_CR1 |= (1U << 0x03); // TE Enable send idle frame as first

}

void USART_RX_Enable(void)
{
	volatile uint32_t *usart_cr1 = (volatile uint32_t *)(USART1_ADDR+USART_CR1_OFFSET_ADDR);

	*usart_cr1 |= (1U << 0xD); // USART Enable
	*usart_cr1 |= (0U << 0xC); // M: Word Length = 8

}

void USART_DR_Load(uint8_t buf, uint32_t len)
{

	while(len)
	{
		USART_DR &= ~(0xFF << 0x0); //clear the data register
		USART_DR |= (buf << 0x0); //write the data
		len -= sizeof(buf);
	}
}
