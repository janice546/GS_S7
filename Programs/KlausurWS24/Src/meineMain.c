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

   rollDice();
   for(int i = 0; i < NO_DICE; i++){
      displayDie(i, getDie(i), DIE_COLOR_DEFAULT);
   }
}

void nichtWuerfeln(uint8_t die){
   fixDie(die);
   displayDie(die, getDie(die), DIE_COLOR_FIXED);
}

int Meinemain(void){
   // Initialisierung der HW
   initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);

   
   neustart();

   while(1){
      //Wuerfel fixieren
      for(int i = 0; i < 5; i++){
         if(buttonPressed(i)){
            nichtWuerfeln(i);
         }
      }
      
      //alle Wuerfel sind wieder gruen (unfixiert)
      if(buttonPressed(5)){
         releaseDice();
         for(int i = 0; i < NO_DICE; i++){
            displayDie(i, getDie(i), DIE_COLOR_DEFAULT);
         }
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
            Coordinate tl = {1,1};
	         GUI_disStr(tl, "GEWONNEN! -> Druecke S7 um neuzustarten", &Font16, BLUE, WHITE);

            //busy wait ist unschön:
            while(!buttonPressed(7)){
               //muss neustarten, um erneut spielen zu können
            }
            neustart();
         }
      }
      
      if(buttonPressed(7)){
         neustart();
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