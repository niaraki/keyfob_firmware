/**
********************************************************************************
* @file     main.c
* @author   M.Niaraki
* @date     07/15/2023
* @brief    main file of the firmware
* @note     notes
  @verbatim
================================================================================
More information should come here
================================================================================
  @endverbatim
*
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki</center></h2>
*
* THIS SOFTWARE IS PROVIDED BY NIARAKI ENGINEERING "AS IS" AND ANY EXPRESSED
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL NIARAKI ENGINEERING OR ITS CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************
*/

/** @addtogroup App
 *   @brief Application laye, The main business of the firmware should be
 * Implemented in this layer
 *   @{
 */

/** @defgroup Main Main
 *   @brief The main part of the firmware
 *    @{
 */
#include <stdio.h>
#include <stm32f0xx.h>
#include "config.h"

/**
 * @brief this function can be used for delay
 * @param void
 * @retval void
 * @warning disable compiler optimizationj
 * @attention sample attention
 * @todo solve the bug
 */
void
delay_us(void)
{
    volatile int i = 0;
    while (i < 250000)
    {
        i++;
    }
}

void
activatePll()
{
    // Enable the HSE clock
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY))
        ;
    // Configure the PLL
    RCC->CFGR = RCC_CFGR_PLLSRC;
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE; // HSE not divided
    RCC->CFGR &= ~RCC_CFGR_PLLMUL;   // reset PLL MUL
    RCC->CFGR |= RCC_CFGR_PLLMUL_2;  // PLLM = 6

    // Set the HCLK clock to 48MHz
    RCC->CFGR &= ~RCC_CFGR_HPRE;
    // Set the PPRE clock to 1
    RCC->CFGR &= ~RCC_CFGR_PPRE;

    // Enable the PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ;

    // Set the PLL as the system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        ;
}

void
blinkLed(void)
{
    while (1)
    {
        GPIOA->ODR |= (1 << 4);
        delay_us();
        GPIOA->ODR &= !(1 << 4);
        delay_us();
    }
}

int
main(void)
{
    //    const char* project_name = PROJECT_NAME;

    // set clock to pll and 48mhz
    activatePll();

    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Enable GPIOA clock

    // enable SWD: CLK:PA14 DATA: PA13
    GPIOA->MODER |= GPIO_MODER_MODER14_1
                    | GPIO_MODER_MODER13_1; // PA13 & PA14 -> alternate function
    GPIOA->OTYPER = 0;                      // set push-pull mode
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_13 | GPIO_OTYPER_OT_14);
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1 | GPIO_OSPEEDER_OSPEEDR14_1;

    // Enable debug module clock
    RCC->APB2ENR |= RCC_APB2ENR_DBGMCUEN;

    // Enable SWD
    DBGMCU->CR |= DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY;

    // enable GPIOA  PA4
    GPIOA->MODER |= (1 << 8);
    GPIOA->PUPDR |= (1 << 8);

    // check pll clock
    SystemCoreClockUpdate();
    if (SystemCoreClock != 48000000)
    {
        SystemCoreClock++;
    }

    blinkLed();

    // you don't reach here
    while (1)
        ;

    return 0;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
