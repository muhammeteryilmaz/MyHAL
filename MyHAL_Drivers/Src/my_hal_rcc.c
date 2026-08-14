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
	            return;  // no HSE , timeout
	        }
	    }
}

void RCC_Enable_PLL(void)
{
	// rcc apb1 enable for pwr_cr

	volatile uint32_t *rcc_apb1enr = (volatile uint32_t *)(RCC_ADDR + RCC_APB1ENR_OFFSET_ADDR);

	*rcc_apb1enr |= (1U << 28); // apb1 bus line power clock enable.


	// voltage regulator

	volatile uint32_t *pwr_cr = (volatile uint32_t *)(PWR_ADDR + PWR_CR_OFFSET_ADDR);

	*pwr_cr &= ~(0x3U << 14); //clear bits
	*pwr_cr |= (0x3U << 14); // set as scale 1



	// flash latency

	volatile uint32_t *flash_acr = (volatile uint32_t *)(FLASH_ADDR + FLASH_ACR_OFFSET_ADDR);

	*flash_acr |= (1U << 10);
	*flash_acr |= (1U << 9);
	*flash_acr |= (1U << 8);

	*flash_acr &= ~(0x0FU << 0);
	*flash_acr |= (5U << 0);

	//ahb, apb1 apb2 hclk configurations
	volatile uint32_t *rcc_cfgr = (volatile uint32_t *)(RCC_ADDR + RCC_CFGR_OFFSET_ADDR);

	*rcc_cfgr &= ~(0x7U << 13);
	*rcc_cfgr |= (0x4U << 13);

	*rcc_cfgr &= ~(0x7U << 10);
	*rcc_cfgr |= (0x5U << 10);

	*rcc_cfgr &= ~(0xFU << 4);
	*rcc_cfgr |= (0x0U << 4);


	// pll register configurations
	volatile uint32_t *rcc_pllcfgr = (volatile uint32_t *)(RCC_ADDR + RCC_PLLCFGR_OFFSET_ADDR);

	*rcc_pllcfgr |= (1U << 22);

	*rcc_pllcfgr &= ~(0x3U << 16);
	*rcc_pllcfgr |= (0U << 16);

	*rcc_pllcfgr &= ~(0x1FFU << 6);
	*rcc_pllcfgr |= (168U << 6);

	*rcc_pllcfgr &= ~(0x3FU << 0);
	*rcc_pllcfgr |= (4U << 0);

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

RCC_Oscillator_t RCC_Get_PLL_Source(void)
{
	volatile uint32_t *rcc_pllcfgr = (volatile uint32_t *)(RCC_ADDR + RCC_PLLCFGR_OFFSET_ADDR);

	uint32_t pll_src = *rcc_pllcfgr;

	pll_src = (pll_src >> 22) & 0x01;

	return (pll_src) ? RCC_HSE : RCC_HSI;

}

uint32_t RCC_Get_SysClock_Freq(void)
{
	volatile uint32_t *rcc_pllcfgr = (volatile uint32_t *)(RCC_ADDR + RCC_PLLCFGR_OFFSET_ADDR);

    uint32_t pllcfgr = *rcc_pllcfgr;

    uint32_t pllm = pllcfgr & 0x3FU;
    uint32_t plln = (pllcfgr >> 6U) & 0x1FFU;
    uint32_t pllp = (pllcfgr >> 16U) & 0x3U;

	pllp = ((2U * pllp) + 2U);



	if (RCC_Get_SysClock_Source() == HSI)
		return 16000000U;

	else if (RCC_Get_SysClock_Source() == HSE)
		return 8000000U;

	return RCC_Get_PLL_Source() ? (((16000000U / pllm) * plln) / pllp) : (((8000000U / pllm) * plln) / pllp);

}

uint32_t RCC_Get_HCLK_Freq(void)
{

	static const uint16_t ahb_prescaler_table[16] =
	{
	    1, 1, 1, 1, 1, 1, 1, 1,
	    2, 4, 8, 16, 64, 128, 256, 512
	};

	volatile uint32_t *rcc_cfgr = (volatile uint32_t *)(RCC_ADDR + RCC_CFGR_OFFSET_ADDR);

	uint32_t ahb_prescaler = ((*rcc_cfgr) >> 4) & 0x0F;

	uint32_t prescaler = ahb_prescaler_table[ahb_prescaler];

	return (RCC_Get_SysClock_Freq() / prescaler);
}

void RCC_SysTick_Init(void)
{

	SYST_RVR = ((RCC_Get_HCLK_Freq() / SYSTICK_FREQ) - 1);
	SYST_CVR = 0;
	SYST_CSR = SYST_CSR | (1U << 0) | (1U << 1) | (1U << 2);

}



void MyHAL_Delay(uint32_t ms)
{
	while(ms)
	{
		if (((SYST_CSR >> 16) & 0x01))
			--ms;
	}
}


