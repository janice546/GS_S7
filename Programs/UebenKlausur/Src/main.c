/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Testprogramm: Gruppen-Entprellung von Tastern
  ******************************************************************************
  */

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

// -------------------------------------------------
// Konfiguration
// -------------------------------------------------
#define DEBOUNCE_DELAY_MS     10
#define ANZAHL_LESEVERSUCH   5

// -------------------------------------------------
// Funktionsprototypen
// -------------------------------------------------
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

uint16_t readButtonGroup(void);
uint16_t debounceButtonGroup(void);

// -------------------------------------------------
// Hauptprogramm
// -------------------------------------------------
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1)
    {
        uint16_t buttons = debounceButtonGroup();

        // Button PF0 -> LED PD0
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,
            (!(buttons & (1 << 0))) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        // Button PF1 -> LED PD1
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,
            (!(buttons & (1 << 1))) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        // Button PF2 -> LED PD2
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,
            (!(buttons & (1 << 2))) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        // Button PF3 -> LED PD3
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,
            (!(buttons & (1 << 3))) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

// -------------------------------------------------
// GPIO-Gruppe lesen (PF0–PF3)
// -------------------------------------------------
uint16_t readButtonGroup(void)
{
    return (uint16_t)(GPIOF->IDR & 0x000F);
}

// -------------------------------------------------
// Gruppen-Entprellung (nach deinem Prinzip)
// -------------------------------------------------
uint16_t debounceButtonGroup(void)
{
    uint16_t state1, state2;
    uint16_t stable = 0x000F;   // alle Taster losgelassen

    for (int i = 0; i < ANZAHL_LESEVERSUCH; i++)
    {
        state1 = (uint16_t)(GPIOF->IDR & 0x000F);
        HAL_Delay(DEBOUNCE_DELAY_MS);
        state2 = (uint16_t)(GPIOF->IDR & 0x000F);

        if (state1 == state2)
        {
            stable = state1;
            break;
        }
    }

    return stable;
}



// -------------------------------------------------
// GPIO Initialisierung
// -------------------------------------------------
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Buttons PF0–PF3 (Input, Pull-Up)
    GPIO_InitStruct.Pin  = GPIO_PIN_0 | GPIO_PIN_1 |
                           GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // LEDs PD0–PD3 (Output)
    GPIO_InitStruct.Pin   = GPIO_PIN_0 | GPIO_PIN_1 |
                            GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

// -------------------------------------------------
// System Clock (Standard HAL)
// -------------------------------------------------
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}
