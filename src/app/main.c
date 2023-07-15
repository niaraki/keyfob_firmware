#include <stdio.h>
#include <stm32f0xx.h>

void delay_us()
{
	int i = 0;
	while (i < 250000) {
		i++;
	}
}

void activatePll()
{
	// Enable the HSE clock
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));
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
	while (!(RCC->CR & RCC_CR_PLLRDY));


	// Set the PLL as the system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

void blinkLed(void)
{
	while (1) {
		GPIOA->ODR |= (1 << 4);
		delay_us();
		GPIOA->ODR &= !(1 << 4);
		delay_us();
	}
}

int main(void)
{
	// set clock to pll and 48mhz
	activatePll();

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Enable GPIOA clock

	// enable SWD: CLK:PA14 DATA: PA13
	GPIOA->MODER |= GPIO_MODER_MODER14_1 | GPIO_MODER_MODER13_1; // PA13 & PA14 -> alternate function
	GPIOA->OTYPER = 0;                                   // set push-pull mode
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
	if (SystemCoreClock != 48000000) {
		SystemCoreClock++;
	}

	blinkLed();

	// you don't reach here
	while (1);

	return 0;
}