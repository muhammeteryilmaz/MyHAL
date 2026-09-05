/*
 * usart.h
 *
 *  Created on: Aug 26, 2026
 *      Author: muhammet
 */

#ifndef INC_MY_HAL_USART_H_
#define INC_MY_HAL_USART_H_


#include "my_hal_gpio.h"
#include "stdint.h"



#define USART1_ADDR					0x40011000
#define RCC_BASE_ADDR        		0x40023800
#define RCC_APB2ENR_OFFSET_ADDR		0x44


#define AFRL_OFFSET_ADDR			0x20
#define AFRH_OFFSET_ADDR			0x24

#define USART_SR_OFFSET_ADDR		0x00
#define USART_DR_OFFSET_ADDR		0x04
#define USART_BRR_OFFSET_ADDR		0x08
#define USART_CR1_OFFSET_ADDR		0x0C
#define USART_CR2_OFFSET_ADDR		0x10
#define USART_CR3_OFFSET_ADDR		0x14


#define USART_CR1					*((volatile uint32_t *)(USART1_ADDR + USART_CR1_OFFSET_ADDR))
#define USART_CR2					*((volatile uint32_t *)(USART1_ADDR + USART_CR2_OFFSET_ADDR))
#define USART_CR3					*((volatile uint32_t *)(USART1_ADDR + USART_CR3_OFFSET_ADDR))
#define USART_BRR					*((volatile uint32_t *)(USART1_ADDR + USART_BRR_OFFSET_ADDR))
#define USART_DR					*((volatile uint32_t *)(USART1_ADDR + USART_DR_OFFSET_ADDR))
#define RCC_APB2ENR 				*((volatile uint32_t *)(RCC_BASE_ADDR + RCC_APB2ENR_OFFSET_ADDR))

void RCC_APB2_USART1_Enable(void);

#endif /* INC_MY_HAL_USART_H_ */
