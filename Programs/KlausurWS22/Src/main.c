/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor für technische Informatik
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

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"
#include "test.h"
#include "io.h"
#include "TFT_board.h"

/* ======== Definitionen ======== */
#define PLAYER_NONE  0
#define PLAYER_1     1
#define PLAYER_2     2

/* ======== Globale Spielvariablen ======== */
static int board[9];
static int currentPlayer;
static bool gameOver;

void setPlayerLEDs(void) {
    switchLEDsOff(0xFFFF);

    if (currentPlayer == PLAYER_1) {
        // grüne LEDs D20–D23
        switchLEDsOn(0xF000);
    } else {
        // blaue LEDs D8–D11
        switchLEDsOn(0x000F);
    }
}

void resetGame(void) {
    for (int i = 0; i < 9; i++) {
        board[i] = PLAYER_NONE;
    }

    gameOver = false;
    currentPlayer = PLAYER_1;

    drawNewBoard();
    setPlayerLEDs();
}

int checkWinner(void) {
    const int winPatterns[8][3] = {
        {0,1,2}, // Reihen
        {3,4,5},
        {6,7,8}, 
        {0,3,6}, // Spalten
        {1,4,7},
        {2,5,8}, 
        {0,4,8}, // Diagonalen
        {2,4,6} 
    };

    for (int i = 0; i < 8; i++) {
        int a = winPatterns[i][0];
        int b = winPatterns[i][1];
        int c = winPatterns[i][2];

        if (board[a] != PLAYER_NONE && board[a] == board[b] && board[b] == board[c]) {
            return board[a];
        }
    }
    return PLAYER_NONE;
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void){
	initITSboard();                 // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	if (!checkVersionFlashFonts()) {
	    // Ueberpruefe Version der Fonts im Flash passt nicht zur Software Version
		Error_Handler();
	}
	
    //Zum testen in der Datei test.h die passende Aufgabe definieren
	//testIO();
	//testBoard();
    //testTouch();
	
	
	 resetGame();

    while (1) {

        /* RESET jederzeit über S0 */
        if (buttonPressed(0)) {
            resetGame();
            delay(300); // Entprellen
            continue;
        }

        if (gameOver) {
            continue;
        }

        int field = getTouch();
        if (field < 0 || field > 8) {
            continue;
        }

        /* Feld bereits belegt → ignorieren */
        if (board[field] != PLAYER_NONE) {
            continue;
        }

        /* Stein setzen */
        if (currentPlayer == PLAYER_1) {
            drawCycle(field);
            board[field] = PLAYER_1;
        } else {
            drawQuad(field);
            board[field] = PLAYER_2;
        }

        /* Gewinner prüfen */
        int winner = checkWinner();
        if (winner != PLAYER_NONE) {
            gameOver = true;
            switchLEDsOff(0xFFFF);

            if (winner == PLAYER_1) {
                // grüne LEDs D16–D23
                switchLEDsOn(0xFF00);
            } else {
                // blaue LEDs D8–D15
                switchLEDsOn(0x00FF);
            }
            continue;
        }

        /* Spieler wechseln */
        currentPlayer = (currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1;
        setPlayerLEDs();

        delay(200); // Touch-Entprellung
    }
}



// EOF
