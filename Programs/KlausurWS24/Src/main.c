/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    22. Jan. 2025
 * @brief   Die Klausuraufgabe Kniffel.
 *
 ******************************************************************************
 */

#include "main.h"
#include <stdlib.h>
#include "init.h"
#include "io.h"
#include "display.h"
#include "kniffel.h"
#include "test.h"
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "delay.h"

#define DELAY 300

typedef enum {
    GAME_RUNNING,
    GAME_WON
} GameState;

static GameState gameState = GAME_RUNNING;

static uint8_t counter = 0;

bool checkGewinn(){
   if(isKniffel() || isStreet()){
      for(int i = 0; i < NO_DICE; i++){
         displayDie(i, getDie(i), DIE_COLOR_WIN);
      }
      return true;
   }
   return false;
}

void neustart(){
   clearDisplay();
   releaseDice();

   counter = 0;
   setLEDs(counter);
   
   gameState = GAME_RUNNING;

   rollDice();
   for(int i = 0; i < NO_DICE; i++){
      displayDie(i, getDie(i), DIE_COLOR_DEFAULT);
   }
}

void nichtWuerfeln(uint8_t die){
   fixDie(die);
   displayDie(die, getDie(die), DIE_COLOR_FIXED);
}

int main(void){
   // Initialisierung der HW
   initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);

   /*
   Coordinate tl = {1,1};
   GUI_disStr(tl, "eins", &Font20, YELLOW, BLUE);
   delay(500);
   GUI_disStr(tl, "zwei", &Font16, WHITE, BLUE);

   //Schaltet D8 und D12 an
   GPIOD->ODR = GPIOD->ODR | 0x0011;
   //Schaltet D16, D17 und D22, D23 an
   GPIOE->ODR = GPIOE->ODR | 0x00C3;

   delay(3000);
   //Schaltet D8 und D12 aus
   GPIOD->ODR = GPIOD->ODR & ~0x0011;
   //Schaltet D16, D17 und D22, D23 aus
   GPIOE->ODR = GPIOE->ODR & ~0x00C3;

   delay(3000);
   GPIOD->ODR = GPIOD->ODR | 0x00FF;
   GPIOE->ODR = GPIOE->ODR | 0x00FF;
   delay(3000);
   GPIOD->ODR = GPIOD->ODR & ~0x0011;
   //Schaltet D16, D17 und D22, D23 aus
   GPIOE->ODR = GPIOE->ODR & ~0x00C3;
   

   HAL_GPIO_TogglePin(GPIOD, 0x0001);
   HAL_GPIO_TogglePin(GPIOE, 0x00FF);
   delay(500);
   HAL_GPIO_TogglePin(GPIOD, 0x0001);
*/

   
   neustart();

   while(1){
      if(gameState == GAME_WON){
        if(buttonPressed(7)){
            neustart();
        }
        continue;
      }

      //Wuerfel fixieren
      for(int i = 0; i < 5; i++){
         if(buttonPressed(i)){
            nichtWuerfeln(i);
            //delay(DELAY);
         }
      }
      
      //alle Wuerfel sind wieder gruen (unfixiert)
      if(buttonPressed(5)){
         releaseDice();
         for(int i = 0; i < NO_DICE; i++){
            displayDie(i, getDie(i), DIE_COLOR_DEFAULT);
         }
         //delay(DELAY);
      }
      //gruene Wuerfel wuerfeln und  ++counter
      if(buttonPressed(6)){
         rollDice();
         for(int i = 0; i < NO_DICE; i++){
            if(!isFixed(i)){
               displayDie(i, getDie(i), DIE_COLOR_DEFAULT);
            }
         }
         ++counter;
         setLEDs(counter);

         if(checkGewinn()){
            Coordinate tl = {1,5};
	         GUI_disStr(tl, "GEWONNEN!", &Font20, GREEN, WHITE);
            Coordinate tlr = {150,10};
	         GUI_disStr(tlr, "-> Druecke S7 um neuzustarten", &Font16, BLUE, WHITE);

            gameState = GAME_WON;
         }
         //delay(200);
      }
      
      if(buttonPressed(7)){
         neustart();
         //delay(DELAY);
      }
      
   }
	
#ifdef AUFGABE3
   testIO();
#endif

#ifdef AUFGABE4
   testDisplay();
#endif

#ifdef AUFGABE5 
	 testKniffel();
#endif
   
}
// EOF