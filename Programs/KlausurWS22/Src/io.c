#include "io.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

bool buttonPressed(int no){
    if (no < 0 || no > 7) {
        return false;
    }

    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOF, (uint16_t)(0x0001 << no));

    //nicht gedrückt -> high (1) 1 == true
    //gedrückt -> low (0) == false
    //falls state == 0 -> also gedrückt 0 == 0 -> true
    return (state == GPIO_PIN_RESET); 
}

void switchLEDsOn(uint16_t leds){
    //D23 - D16
    HAL_GPIO_WritePin(GPIOE, leds >> 8, GPIO_PIN_SET);
    //D25 - D8 
    HAL_GPIO_WritePin(GPIOD, leds, GPIO_PIN_SET);
    
}

void switchLEDsOff(uint16_t leds){
    //D23 - D16
    HAL_GPIO_WritePin(GPIOE, leds >> 8, GPIO_PIN_RESET);
    //D25 - D8 
    HAL_GPIO_WritePin(GPIOD, leds, GPIO_PIN_RESET);
}