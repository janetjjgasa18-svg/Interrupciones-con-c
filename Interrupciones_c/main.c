#include "stm32f10x.h"
#include "GPIO.h"
#include "EXTIN.h"

int main(void) {
    GPIO_PC13_Init(); 
    EXTIN_Init(); 

    while(1) {
    }
}