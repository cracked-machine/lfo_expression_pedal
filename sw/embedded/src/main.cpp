#include <stm32g071xx.h>
#include <main.hpp>
#include <timer_manager.hpp>

constexpr auto delay_microsecond = stm32::TimerManager::delay_microsecond;
constexpr auto delay = stm32::delay_millisecond;

void setup()
{

    // RCC
        // enable HSI16
        RCC->CR |= RCC_CR_HSION_Msk;
        while((RCC->CR & RCC_CR_HSIRDY) == 0) { } 
        // No div at HSISYS prescaler, 
        RCC->CR &= ~RCC_CR_HSIDIV_Msk;
        // select SYSCLK source as HSISYS, no div for AHB/APB prescalers
        RCC->CFGR &= ~RCC_CFGR_SW_Msk;
        RCC->CFGR &= ~RCC_CFGR_PPRE_Msk;
        RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
        
        SysTick_Config(SystemCoreClock / 1000U);
        // NVIC_SetPriority(SysTick_IRQn, 3U);
    
    // TIM15 (APB) for DAC trigger
        RCC->APBENR2 |= RCC_APBENR2_TIM15EN_Msk;    // enable clock for TIM15
        TIM15->CR2 |= TIM_CR2_MMS_1;                // TRGO = 0x20 -> Update Event
        TIM15->CR1 |= TIM_CR1_ARPE_Msk;             // Enable preload (more stable to runtime frequency updates)
        TIM15->CNT = 0;                             // Initialise the counter to zero
        TIM15->PSC = 1;                             // Set the prescaler
        TIM15->ARR = 512;                          // Set the auto reload threshold
        // NVIC_EnableIRQ(TIM15_IRQn);
        // NVIC_SetPriority(TIM15_IRQn, 0U);
        TIM15->CR1 |= TIM_CR1_CEN_Msk;

    // DAC (APB) 
        RCC->APBENR1 |= RCC_APBENR1_DAC1EN_Msk;
        DAC->CR = 0;
        DAC->MCR |= DAC_MCR_MODE1_1;    // buffer disabled
        DAC->CR |= DAC_CR_TEN1_Msk;     // trigger enable
        DAC->CR |= DAC_CR_TSEL1_3;      // 0x1000 -> dac_ch1_trg8 interconnect -> TIM15 trigger
        DAC->CR |= DAC_CR_WAVE1_1;      // triagle waveform enabled
        DAC->CR |= (DAC_CR_MAMP1_0 | DAC_CR_MAMP1_3);    // maximum amplitude!
        DAC->CR |= DAC_CR_EN1_Msk;      // enable the DAC output on channel 1


    // TIM17 (APB) for delay
        // RCC->APBENR2 |= RCC_APBENR2_TIM17EN_Msk;
        // stm32::TimerManager::initialise(TIM17);
        // TIM17->PSC = 1;
        // TIM17->ARR = 1024;
        // TIM17->DIER |= TIM_DIER_UIE_Msk;
        // NVIC_EnableIRQ(TIM17_IRQn);
        // NVIC_SetPriority(TIM17_IRQn, 0U);
        // TIM17->CR1 |= TIM_CR1_CEN_Msk;
    
    // TIM3 (APB) for rotary encoder
        RCC->APBENR1 |= RCC_APBENR1_TIM3EN_Msk;
        

    // EXTI (AHB) for foot switch/user buttons

    // I2C1 (APB) for OLED display

}

int main()
{
    setup();
    while (1)
    {
        // delay(2000);
        // DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1_Msk;
    }

}

void TIM17_IRQHandler()
{
    // clear the interrupt status flag
    TIM17->SR &= ~TIM_SR_UIF_Msk;
}


void TIM15_IRQHandler()
{
    // clear the interrupt status flag
    TIM15->SR &= ~TIM_SR_UIF_Msk;
}
