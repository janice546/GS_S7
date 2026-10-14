#include "stm32f4xx_hal.h"
#include "io.h"
#include "error.h"
#include <stdint.h>

void setLEDs(int noLeds){
     if (noLeds < 0 || noLeds > 16)
    {
        Error_Handler();
    }

    /* Alle LEDs ausschalten */
    HAL_GPIO_WritePin(GPIOE, 0x00FF, GPIO_PIN_RESET); // Pins 15..8
    HAL_GPIO_WritePin(GPIOD, 0x00FF, GPIO_PIN_RESET); // Pins 15..8

    /* LEDs D23 abwärts einschalten */
    for (int i = 0; i < noLeds; i++)
    {
        if (i < 8)
        {
            // D23..D16 → GPIOE Pin 15..8
            HAL_GPIO_WritePin(GPIOE, (uint16_t)(0x0080 >> i), GPIO_PIN_SET);
        }
        else
        {
            // D15..D8 → GPIOD Pin 15..8
            HAL_GPIO_WritePin(GPIOD, (uint16_t)(0x0080 >> (i - 8)), GPIO_PIN_SET);
        }
    }
}
    
