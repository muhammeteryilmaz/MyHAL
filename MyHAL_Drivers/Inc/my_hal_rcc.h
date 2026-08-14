/*
 * my_hal_rcc.h
 *
 *  Created on: Aug 1, 2026
 *      Author: muhammet
 */

#ifndef INC_MY_HAL_RCC_H_
#define INC_MY_HAL_RCC_H_

#include "stdint.h"

#define RCC_ADDR	0x40023800
#define PWR_ADDR 	0x40007000
#define FLASH_ADDR	0x40023C00

#define RCC_CR_OFFSET_ADDR		0x00
#define RCC_CFGR_OFFSET_ADDR	0x08
#define RCC_PLLCFGR_OFFSET_ADDR	0x04
#define RCC_APB1ENR_OFFSET_ADDR	0x40


#define PWR_CR_OFFSET_ADDR		0x00

#define FLASH_ACR_OFFSET_ADDR	0x00

//From ARM Cortex-M4 Generic User Guide for SysTick Control Register addresses
#define SYSTICK_FREQ 1000UL  // 1ms
#define SYST_CSR 				(*(volatile uint32_t *)(0xE000E010)) // SysTick Control and Status Register RW
#define SYST_RVR 				(*(volatile uint32_t *)(0xE000E014)) // SysTick Reload Value Register RW
#define SYST_CVR 				(*(volatile uint32_t *)(0xE000E018)) // SysTick Current Value Register RW
#define SYST_CALIB 				(*(volatile uint32_t *)(0xE000E01C)) // SysTick Calibration Value Register RO



typedef enum {
	RCC_HSI	= 0U,
	RCC_HSE = 16U
} RCC_Oscillator_t;


typedef enum {
	HSI = 0U,
	HSE = 1U,
	PLL_P = 2U,
	PLL_R = 3U
} RCC_SysClock_Source_t;


void RCC_Enable_PLL(void);
void RCC_Enable_Oscillator(RCC_Oscillator_t rcc_hsx);
void RCC_Select_SysClock_Source(RCC_SysClock_Source_t source);
RCC_SysClock_Source_t RCC_Get_SysClock_Source(void);
RCC_Oscillator_t RCC_Get_PLL_Source(void);
uint32_t RCC_Get_SysClock_Freq(void);
uint32_t RCC_Get_HCLK_Freq(void);
void RCC_SysTick_Init(void);
void MyHAL_Delay(uint32_t ms);

#endif /* INC_MY_HAL_RCC_H_ */
