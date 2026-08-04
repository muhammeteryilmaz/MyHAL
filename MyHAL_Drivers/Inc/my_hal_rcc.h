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

#define RCC_CR_OFFSET_ADDR		0x00
#define RCC_CFGR_OFFSET_ADDR	0x08


void RCC_HSI_Enable(void);
void RCC_Select_HSI_For_SysClock(void);
uint32_t RCC_Get_SysClock_Source(void);

#endif /* INC_MY_HAL_RCC_H_ */
