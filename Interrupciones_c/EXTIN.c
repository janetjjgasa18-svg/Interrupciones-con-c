#include "EXTIN.h"
#include "GPIO.h" // Necesario para acceder a los registros de GPIOC

void EXTIN_Init(void) {
    RCC->APB2ENR |= (1 << 2) | (1 << 0); 
    
    GPIOA->CRL &= ~(0xF << 0);   // Limpiar configuración previa de PA0
    GPIOA->CRL |= (0x8 << 0);    // Modo de entrada con Pull-up/Pull-down
    GPIOA->ODR |= (1 << 0);      // Activar la resistencia Pull-up
    
    AFIO->EXTICR[0] &= ~(0xF << 0); 
    
    // Interrupciones 
    EXTI->IMR |= (1 << 0);       
    EXTI->FTSR |= (1 << 0);
    
    NVIC_EnableIRQ(EXTI0_IRQn);
}

// Manejador de la interrupción 
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & (1 << 0)) {
        GPIOC->ODR ^= (1U << 13); 
        for (volatile int i = 0; i < 150000; i++); 
        EXTI->PR = (1 << 0); 
    }
}