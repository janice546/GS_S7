/**
 ******************************************************************************
 * @file    display.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    22. Jan. 2025
 * @brief   Dieses Modul implementiert die LCD Ausgabe der W�rfel.
 ******************************************************************************
 */

#include "display.h"
#include "main.h"
#include "LCD_GUI.h"
#include "error.h"
#include <stdlib.h>
#include <stdint.h>

// Dieses Feld speichert die Positionen der W�rfel. Die Position eines W�rfels
// ist durch seine linke obere und rechte untere Ecke beschrieben.

const struct {
	 Coordinate tl;
	 Coordinate br;
	} dicePosData[NO_DICE] = { {.tl = {.x = 382, .y = 40}, .br = {.x = 465, .y = 123}},
		                         {.tl = {.x = 292, .y = 40}, .br = {.x = 375, .y = 123}},
														 {.tl = {.x = 202, .y = 40}, .br = {.x = 285, .y = 123}},
														 {.tl = {.x = 112, .y = 40}, .br = {.x = 195, .y = 123}},
														 {.tl = {.x = 22,  .y = 40}, .br = {.x = 105, .y = 123}}};

// Von der linken oberen Ecke eines W�rfels ausgehend, beschreiben folgende Konstanten 
// den Offset der Mittelpunkte der einzelnen Positionen der W�rfelaugen / W�rfelpunkte.
//
//           |-------------------------|
//           |                         |
//           |  Pos1             Pos2  |
//           |                         |
//           |  Pos3    Pos4     Pos5  |
//           |                         |
//           |  Pos6             Pos7  |
//           |                         |
//           |-------------------------|
											
const Coordinate offsetPos1 = {.x = 1 * 21, .y = 1 * 21};
const Coordinate offsetPos2 = {.x = 3 * 21, .y = 1 * 21};
const Coordinate offsetPos3 = {.x = 1 * 21, .y = 2 * 21};
const Coordinate offsetPos4 = {.x = 2 * 21, .y = 2 * 21};
const Coordinate offsetPos5 = {.x = 3 * 21, .y = 2 * 21};
const Coordinate offsetPos6 = {.x = 1 * 21, .y = 3 * 21};
const Coordinate offsetPos7 = {.x = 3 * 21, .y = 3 * 21};

#define RADIUS_DICE_EYE       6   // 
#define NUMBER_EYES 			6

void clearDisplay(void){
	GUI_clear(BLUE);
}

static void koorAugen(uint8_t value, Coordinate *augen){
	switch(value){
		case 1: augen[0] = offsetPos4;
			return;
		case 2: augen[0] = offsetPos2;
				augen[1] = offsetPos6;
			return;
		case 3: augen[0] = offsetPos2;
				augen[1] = offsetPos4;
				augen[2] = offsetPos6;
			return;
		case 4: augen[0] = offsetPos1;
				augen[1] = offsetPos2;
				augen[2] = offsetPos6;
				augen[3] = offsetPos7;
			return;
		case 5: augen[0] = offsetPos1;
				augen[1] = offsetPos2;
				augen[2] = offsetPos6;
				augen[3] = offsetPos7;
				augen[4] = offsetPos4;
			return;
		case 6: augen[0] = offsetPos1;
				augen[1] = offsetPos2;
				augen[2] = offsetPos3;
				augen[3] = offsetPos5;
				augen[4] = offsetPos6;
				augen[5] = offsetPos7;
			return;
	}
}

/**
  * @brief Diese Funktion zeichnet einen W�rfel auf dem Bildschirm.
  *
  * @param  die Die Nummer des W�rfels, die die Position auf dem Bildschirm 
	*             festlegt. 0 ist der W�rfel rechts au�en. 4 ist der W�rfel
	*             links au�en.
	* @param  val Der Wert, der auf dem W�rfel dargestellt wird.
  * @param  c   Die Farbe des W�rfels.
  */
void displayDie(uint8_t die, uint8_t value, COLOR c){
	Coordinate tl = dicePosData[die].tl;
	Coordinate br = dicePosData[die].br;

	Coordinate augen[NUMBER_EYES] = {};

	koorAugen(value, augen);

	GUI_drawRectangle(tl, br, c, true, DOT_PIXEL_1X1);

	for(int i = 0; i < value; i++){
		Coordinate center;
		center.x = tl.x + augen[i].x;
		center.y = tl.y + augen[i].y;

		GUI_drawCircle(center, RADIUS_DICE_EYE, BLACK, true, DOT_PIXEL_1X1);

	}
}




// EOF