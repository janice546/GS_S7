/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    17. Juli 2020
 * @brief   Rahmen fuer C Programme, die auf dem ITSboard ausgefuehrt werden.
 *
 *					25.04.2022 Tobias De Gasperis: printf hinzugefuegt
 ******************************************************************************
 */
 
#include "display.h"
#include "stm32f429xx.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"

#include <stdlib.h>
#include <stdint.h>
#include "test.h"
#include "display.h"
#include "io.h"
#include "masterMind.h"

#define MAX_TRYS               16   // Maximale Anzahl an Versuchen
#define NO_DIGITS               4   // Anzahl Stellen der gesuchten Zahl

// Die gesuchte und die akt. geratene Zahl werden als ein Feld von ASCII Zeichen dargestellt.
static uint8_t sno[NO_DIGITS];         // Die gesuchte Zahl
static uint8_t guess[NO_DIGITS];       // Die akt. geratene Zahl


int main(void){
	initITSboard();                 // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	if (!checkVersionFlashFonts()) {
	    // Ueberpruefe Version der Fonts im Flash passt nicht zur Software Version
		Error_Handler();
	}

   // testIO();
   // testDisplay();
   // testMasterMind();
   
   bool showSecret = false;

	initDisplay();

	// Super Loop gemaess DDC
	while (1){ 
		int versuche = 0;
		bool beendet = false;
		char input = NULL;

		/*Neues Spiel*/
		clearDisplay();
		setLEDs(0);
		genNewNumber(NO_DIGITS, sno);

		if (showSecret){
			printNumber("Gesuchte Zahl: ", NO_DIGITS, sno, NULL);
			showSecret = false;
		}

		/*Spielschleife*/
		while(!beendet && versuche < MAX_TRYS){
			printStr("Bitte Zahl eingeben:\n", DEFAULT_COLOR);
			input = nextInput(false, NO_DIGITS, guess);

			//Spiel abbrechen
			if(input == RESET_KEY){
				beendet = true;
				break;
			}
			if(input == RESET_AND_HELP_KEY){
				beendet = true;
				showSecret = true;
				break;
			}

			versuche++;
			setLEDs(versuche);

			/*Zahl ausgeben*/
			printNumber("Geraten: ", NO_DIGITS, sno, guess);

			/*Gewinn prüfen*/
			if(won(NO_DIGITS, sno, guess)){
				printStr("Gewonnen\n", HIT_COLOR);
				printStr("Neustart mit C oder *\n", DEFAULT_COLOR);
				beendet = true;
				break;
			}
		}

		/*Spieler hat alle Versuche aufgebraucht und hat somit verloren*/
		if(!beendet && versuche >= MAX_TRYS){
			setLEDs(MAX_TRYS);
			printStr("Verloren\n", MISS_COLOR);
			printStr("Neustart mit C oder *\n", DEFAULT_COLOR);
		}

		nextInput(true, NO_DIGITS, guess);
	}
}

// EOF
