/**
********************************************************************************
* @file     hal_interrupt_handlers.h
* @author   M.Niaraki
* @date     07/21/2023
* @brief
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_INTERRUPT_HANDLERS_H
#define __HAL_INTERRUPT_HANDLERS_H

#ifdef __cplusplus
extern "C"
{
#endif

    void SysTick_Handler(void);
    void TIM14_IRQHandler(void);
    void TIM16_IRQHandler(void);
    void TIM17_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_INTERRUPT_HANDLERS_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
