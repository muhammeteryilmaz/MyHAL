/*
 * my_hal_rcc.c
 *
 *  Created on: Aug 1, 2026
 *      Author: muhammet
 */

#include "my_hal_rcc.h"




void RCC_HSI_Enable(void)
{
	volatile uint32_t *rcc_cr = (volatile uint32_t *)(RCC_ADDR + RCC_CR_OFFSET_ADDR);


	*rcc_cr |= (1U << 0); // HSI ON


	// wait until HSI is ready
	while(((*rcc_cr & (1U << 1U)) == 0U))
	{

	}

}

void RCC_Select_HSI_For_SysClock(void)
{
	volatile uint32_t *rcc_cfgr = (volatile uint32_t *)(RCC_ADDR + RCC_CFGR_OFFSET_ADDR);

	*rcc_cfgr &= ~(0x3U << 0); //clear bits and set with 00

	// confirm that HSI is used.
	while (((*rcc_cfgr >> 2U) & 0x3U) != 0){

	}
}

uint32_t RCC_Get_SysClock_Source(void)
{
	volatile uint32_t *rcc_cfgr = (volatile uint32_t *)(RCC_ADDR + RCC_CFGR_OFFSET_ADDR);

	return ((*rcc_cfgr >> 2U) & 0x3U);
}
