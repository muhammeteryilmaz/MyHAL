/*
 * my_hal_rcc.c
 *
 *  Created on: Aug 1, 2026
 *      Author: muhammet
 */

#include "my_hal_rcc.h"




void RCC_Enable_Oscillator(RCC_Oscillator_t rcc_hsx)
{
	volatile uint32_t *rcc_cr = (volatile uint32_t *)(RCC_ADDR + RCC_CR_OFFSET_ADDR);


	*rcc_cr |= (1U << rcc_hsx); // oscillator ON


	// wait until rcc oscillator is ready
	uint32_t timeout = 0U;
	    while(((*rcc_cr & (1U << (rcc_hsx + 1U))) == 0U)){
	        timeout++;
	        if(timeout > 10000U){
	            return;  // HSE yok, timeout
	        }
	    }
}

void RCC_Enable_PLL(void)
{
	// voltage regulator

	volatile uint32_t *pwr_cr = (volatile uint32_t *)(PWR_ADDR + PWR_CR_OFFSET_ADDR);

	*pwr_cr &= ~(0x3U << 14); //clear bits
	*pwr_cr |= (0x3U << 14); // set as scale 1



	// flash latency

	volatile uint32_t *flash_acr = (volatile uint32_t *)(FLASH_ADDR + FLASH_ACR_OFFSET_ADDR);

	*flash_acr = *flash_acr | (1U << 10) | (1U << 9) | (1U << 8) | (0x05U << 0);


	//ahb, apb1 apb2 hclk configurations
	volatile uint32_t *rcc_cfgr = (volatile uint32_t *)(RCC_ADDR + RCC_CFGR_OFFSET_ADDR);

	*rcc_cfgr = *rcc_cfgr | (4U << 13) | (5U << 10) | (8U << 4);

	// pll register configurations
	volatile uint32_t *rcc_pllcfgr = (volatile uint32_t *)(RCC_ADDR + RCC_PLLCFGR_OFFSET_ADDR);

	*rcc_pllcfgr = *rcc_pllcfgr | (0U << 16) | (180U << 6) | (4U << 0);

	//pll
	volatile uint32_t *rcc_cr = (volatile uint32_t *)(RCC_ADDR + RCC_CR_OFFSET_ADDR);

	*rcc_cr |= (1U << 24); // pll on


	// wait until pll is ready
	uint32_t timeout = 0U;
	    while(((*rcc_cr & (1U << 25)) == 0U)){
	        timeout++;
	        if(timeout > 10000U){
	            return;  // no pll, timeout
	        }
	    }
}

void RCC_Select_SysClock_Source(RCC_SysClock_Source_t source)
{
	volatile uint32_t *rcc_cfgr = (volatile uint32_t *)(RCC_ADDR + RCC_CFGR_OFFSET_ADDR);

	*rcc_cfgr &= ~(0x3U << 0); //clear bits and set with 00
	*rcc_cfgr |= (source << 0); //set source

	uint32_t timeout = 0U;
	while (((*rcc_cfgr >> 2U) & 0x3U) != (uint32_t)source)
	{
		timeout++;

		if (timeout > 10000U)
			return;
	}

}

RCC_SysClock_Source_t RCC_Get_SysClock_Source(void)
{
	volatile uint32_t *rcc_cfgr = (volatile uint32_t *)(RCC_ADDR + RCC_CFGR_OFFSET_ADDR);

	RCC_SysClock_Source_t source = (RCC_SysClock_Source_t)((*rcc_cfgr >> 2U) & 0x3U);

	return source;

}
