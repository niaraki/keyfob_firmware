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

#include "stm32f0xx_override.h"
#include "hll.h"

/* PWR fakes */
volatile PWR_TypeDef        fake_pwr_regs = { 0 };
volatile PWR_TypeDef *const gp_pwr_regs   = &fake_pwr_regs;

/* RCC fakes */
volatile RCC_TypeDef        fake_rcc_regs = { 0 };
volatile RCC_TypeDef *const gp_rcc_regs   = &fake_rcc_regs;

/* Fake implementation of SystemCoreClockUpdate*/
#define FAKE_RCC_PRE_INITED_FREQ (48000000UL)
uint32_t SystemCoreClock = 0;
uint8_t  IsWrongSystemCoreClockEnabled;

void
SystemCoreClockUpdate(void)
{
    if (0U == IsWrongSystemCoreClockEnabled)
        SystemCoreClock = FAKE_RCC_PRE_INITED_FREQ;
    else
        SystemCoreClock = (FAKE_RCC_PRE_INITED_FREQ - 1U);
}

/* DIO fakes */
volatile GPIO_TypeDef        fake_dio_regs_a = { 0 };
volatile GPIO_TypeDef        fake_dio_regs_b = { 0 };
volatile GPIO_TypeDef *const gp_dio_regs[DIO_CHANNELS]
    = { &fake_dio_regs_a, &fake_dio_regs_b };

/* EXTI fakes */
volatile EXTI_TypeDef        fake_exti_regs = { 0 };
volatile EXTI_TypeDef *const gp_exti_regs   = &fake_exti_regs;

/* SYSCONFIG fakes */
volatile SYSCFG_TypeDef        fake_syscfg_regs = { 0 };
volatile SYSCFG_TypeDef *const gp_syscfg_regs   = &fake_syscfg_regs;
volatile SCB_Type              fake_scb_regs    = { 0 };
volatile SCB_Type *const       gp_scb_regs      = &fake_scb_regs;

/* NVIC fakes*/
volatile NVIC_Type        fake_nvic_regs = { 0 };
volatile NVIC_Type *const gp_nvic_regs   = &fake_nvic_regs;

/* TIM fakes */
volatile TIM_TypeDef        fake_tim_regs_14 = { 0 };
volatile TIM_TypeDef        fake_tim_regs_16 = { 0 };
volatile TIM_TypeDef        fake_tim_regs_17 = { 0 };
volatile TIM_TypeDef *const gp_tim_regs[TIM_CHANNELS]
    = { &fake_tim_regs_14, &fake_tim_regs_16, &fake_tim_regs_17 };

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF
   FILE****/
