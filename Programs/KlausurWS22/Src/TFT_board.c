/**
 ******************************************************************************
 * @file    TFT_board.c
 * @author  XXX
 *
 * @date    3. Feb. 2023
 *
 * @brief   Darstellung des TicTacToe Boards auf dem TFT Display des ITS Boards.
 *
 ******************************************************************************
 */
 
#include "TFT_board.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "LCD_general.h"
#include "init.h"


#define COLOR_BG			GRAY         // Hintergrundfarbe
#define COLOR_LINE		    BLACK        // Farbe der Trennlinien des Spielfelds  
#define COLOR_SP1			GREEN        // Farbe der runden Spielsteine
#define COLOR_SP2			BLUE         // Farbe der quadratischen Spielsteine

#define ZB       5                   // Breite einer Trennlinie
#define QKL      101                 // Kantenlaenge des Quadrats eines Felds des Spielbretts
#define ZL       (3*QKL + 2*ZB)      // Laenge einer Trennlinie des Spielfelds

#define U_X     83
#define U_Y     3

typedef struct {
	Coordinate topLeft;
    Coordinate bottomRight;
} Rectangle;

// Die vier Trennlinien werden als Rechtecke dargestellt. 
// Das folgende Feld enthaelt die Koordinaten dieser Rechtecke.
static Rectangle line[] = {
   {.topLeft     = {.x = U_X,                   .y = U_Y +        QKL},
    .bottomRight = {.x = U_X + ZL,              .y = U_Y +        QKL + ZB}
   },
   {.topLeft     = {.x = U_X,                   .y = U_Y + ZB + 2*QKL},
    .bottomRight = {.x = U_X + ZL,              .y = U_Y + ZB + 2*QKL + ZB} 
   }, 
   {.topLeft     = {.x = U_X + QKL,             .y = U_Y},
    .bottomRight = {.x = U_X + QKL + ZB,        .y = U_Y + ZL} 
   },   
   {.topLeft     = {.x = U_X + ZB + 2*QKL,      .y = U_Y},
    .bottomRight = {.x = U_X + ZB + 2*QKL + ZB, .y = U_Y + ZL} 
   }
};

// Die Mittelpunkte der 9 Felder des Spielbretts
static Coordinate  mp[] = {
    {.x = U_X +                QKL/2 + 1, .y = U_Y +                 QKL/2 + 1},
    {.x = U_X +                QKL/2 + 1, .y = U_Y +   (QKL + ZB) +  QKL/2 + 1},
    {.x = U_X +                QKL/2 + 1, .y = U_Y + 2*(QKL + ZB) +  QKL/2 + 1},

    {.x = U_X +   (QKL + ZB) + QKL/2 + 1, .y = U_Y +                 QKL/2 + 1},
    {.x = U_X +   (QKL + ZB) + QKL/2 + 1, .y = U_Y +   (QKL + ZB) +  QKL/2 + 1},
    {.x = U_X +   (QKL + ZB) + QKL/2 + 1, .y = U_Y + 2*(QKL + ZB) +  QKL/2 + 1},
		
    {.x = U_X + 2*(QKL + ZB) + QKL/2 + 1, .y = U_Y +                 QKL/2 + 1},
    {.x = U_X + 2*(QKL + ZB) + QKL/2 + 1, .y = U_Y +   (QKL + ZB) +  QKL/2 + 1},
    {.x = U_X + 2*(QKL + ZB) + QKL/2 + 1, .y = U_Y + 2*(QKL + ZB) +  QKL/2 + 1}};

/**
 * @brief  Diese Funktion loescht den Bildschirm und zeichnet ein leeres Spielbrett. 
 *         Es besteht aus den vier Linien, die das Spielbrett in 9 Felder unterteilen.
 *         Die Mittelpunkte der 9 Spielfelder werden mit einem 3x3 Pixel Punkt gekennzeichnet.
 *         
 * @retval none
 */
void drawNewBoard(void){
    GUI_clear(COLOR_BG);
    for(int i = 0; i < 4; i++){
        GUI_drawRectangle(line[i].topLeft, line[i].bottomRight, COLOR_LINE, true, ZB);
    }
    
}


/**
 * @brief  Diese Funktion zeichnet einen gruenen Kreis auf ein Feld des Spielbretts. 
 *
 * @param  pos Nummer des Felds des Spielbretts, auf das der gruene Kreis gezeichnet wird. 
 * @retval none
 */
void drawCycle(int pos){
    GUI_drawCircle(mp[pos], (QKL/2 - 2* ZB), COLOR_SP1, true, ZB);
}


/**
 * @brief  Diese Funktion zeichnet ein blaues Quadrat auf ein Feld des Spielbretts. 
 *
 * @param  pos Nummer des Felds des Spielbretts, auf das das blaue Quadart gezeichnet wird. 
 * @retval none
 */
void drawQuad(int pos){
    Coordinate tl = {.x = (mp[pos].x - (QKL/2 - 2 * ZB)), .y = (mp[pos].y - (QKL/2 - 2* ZB))};
    Coordinate br = {.x = (mp[pos].x + (QKL/2 - 2* ZB)), .y = (mp[pos].y + (QKL/2 - 2* ZB))};
    GUI_drawRectangle(tl, br, COLOR_SP2, true, ZB);
}


/**
 * @brief  Diese Funktion ueberprueft, ob gerade auf ein Feld des Spielfelds gedrueckt wird. 
 *
 * @retval Falls gerade auf ein Feld des Spielbretts gedrueckt wird, die Nummer des Felds.
 *         Ansonsten -1 (z.B. Es wird nicht auf das LCD gedrueckt oder die Koordinate
 *         des aktuellen Druckpunkts kann keinem Feld des Spielbretts eindeutig zugeordnet
 *         werden.)
 */
int getTouch(void){
    // Pruefe, ob ueberhaupt gedrueckt wird
    if (!TP_pressed()) {
        return -1;
    }

    Coordinate touchPoint = TP_get();

    int half = QKL / 2;
    for(int i = 0; i < 9; i++){
        if(touchPoint.x >= mp[i].x - half && 
           touchPoint.x <= mp[i].x + half &&
           touchPoint.y >= mp[i].y - half &&
           touchPoint.y <= mp[i].y + half){
               return i;
           }
    }

    //Touch, aber kein Feld getroffen
    return -1;
}
// EOF
