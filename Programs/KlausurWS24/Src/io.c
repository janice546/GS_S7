#include "io.h"
#include "error.h"
#include "main.h"

#include "stm32f4xx_hal.h"

#include "delay.h"

void setLEDsFunzzt(uint8_t noLeds){
    if(noLeds < 0 || noLeds > 16){
        Error_Handler();
    }

    HAL_GPIO_WritePin(GPIOD, 0x00FF, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, 0x00FF, GPIO_PIN_RESET);

    if(noLeds > 0){
        for(int i = 0; i < noLeds; i++){
            if(i < 8){
                HAL_GPIO_WritePin(GPIOD, 0x00001 << i, GPIO_PIN_SET);
            }
            else{
                HAL_GPIO_WritePin(GPIOE, 0x0001 << (i - 8), GPIO_PIN_SET);
            }
        }
    }
    
}

void setLEDs(uint8_t leds){
    GPIOD->ODR = GPIOD->ODR & ~0x00FF;
    GPIOE->ODR = GPIOE->ODR & ~0x00FF;

    if (leds > 0){
        for(int i = 0; i < leds; i++){
            if(i < 8){
                GPIOD->ODR = GPIOD->ODR | (0x0001 << i);
            }else{
                GPIOE->ODR = GPIOE->ODR | (0x0001 << (i - 8));
            }
        }
    }
}

//einfache Entprellung mit zwei Messungen
bool buttonPressed(uint8_t button){
    if(button < 0 || button > 7){
        Error_Handler();
    }

    GPIO_PinState state1;
    GPIO_PinState state2;

    bool stable = false;
    for(int i = 0; i < 5; i++){
        state1 = HAL_GPIO_ReadPin(GPIOF, 0x0001 << button);
        delay(10);
        state2 = HAL_GPIO_ReadPin(GPIOF, 0x0001 << button);
        if(state1 == state2){
            stable = ( state1 ==GPIO_PIN_RESET);
            break;
        }
    }
     
    return stable;
}


bool buttonPressedFunzzt(uint8_t button){
    if(button < 0 || button > 7){
        Error_Handler();
    }

    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOF, 0x0001 << button);
    
    return (state == GPIO_PIN_RESET);
}

// EOF