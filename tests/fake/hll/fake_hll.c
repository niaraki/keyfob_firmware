/**
********************************************************************************
* @file     fake_hll.c
* @author   M.Niaraki
* @date     07/19/2023
* @brief    FAKE Registers for Hardware Low Layer
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#include "stm32f0xx.h"
#include "hll.h"

volatile RCC_TypeDef        fake_rcc_regs = { 0 };
volatile RCC_TypeDef *const hll_rcc_regs  = &fake_rcc_regs;

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
