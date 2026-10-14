/**
 ******************************************************************************
 * @file    kniffel.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    20. Jan. 2025
 * @brief   Dieses Modul speichert den Zustand der W�rfel.
 *
 ******************************************************************************
 */

#include "kniffel.h"
#include "main.h"
#include "random.h"

static int wuerfel[NO_DICE] = {1,1,1,1,1};

static bool fix[NO_DICE] = {false};

/**
  * @brief Diese Funktion liefert den aktuellen Wert eines W�rfels.
  *
  * @param  die Der W�rfel, dessen Wert bestimmt wird.
  *	
  * @retval Der Wert des W�rfels.
  */
uint8_t getDie(uint8_t die){
    return wuerfel[die];
}

/**
  * @brief Diese Funktion �berpr�ft, ob alle W�rfel den Wert 1 haben - also
	*        ein Kniffel vorliegt.
  *
  * @retval true gdw. ein Kniffel liegt vor.
  */
bool isKniffel(void){
    return(wuerfel[0] == wuerfel[1] &&
           wuerfel[1] == wuerfel[2] &&
           wuerfel[2] == wuerfel[3] &&
           wuerfel[3] == wuerfel[4]);
}

bool isKniffelChat(void){
    for (int i = 1; i < NO_DICE; i++){
        if (wuerfel[i] != wuerfel[0]){
            return false;
        }
    }
    return true;
}

/**
  * @brief Diese Funktion �berpr�ft, ob die Werte der W�rfel eine Strasse ergeben
  *        also eintweder 1 2 3 4 5 oder 2 3 4 5 6 sind.
  *
  * @retval true gdw. eine Strasse liegt vor.
  */
bool isStreet(void){
    bool seen[7] = {false};

    for (int i = 0; i < NO_DICE; i++){
        seen[wuerfel[i]] = true;
    }

    return (seen[1] && seen[2] && seen[3] && seen[4] && seen[5]) ||
           (seen[2] && seen[3] && seen[4] && seen[5] && seen[6]);
}

/**
  * @brief Diese Funktion fixiert den W�rfel mit der Nummer die. Ein fixierter
	*        W�rfel wird beim n�chsten Wurf nicht geworfen / gew�rfelt.
  *
  * @param  die Die Nummer des W�rfels, der fixiert wird.
  */
void fixDie(uint8_t die){
    fix[die] = true;
}

/**
  * @brief Diese Funktion l�st die Fixierung aller W�rfel auf, so dass alle 
	*        W�rfel beim n�chsten Wurf mit gew�rfelt werden.
  */
void releaseDice(void){
    for(int i = 0; i < NO_DICE; i++){
        fix[i] = false;
    }
}

/**
  * @brief Diese Funktion �berpr�ft, ob der W�rfel mit der Nummer die fixiert ist.
  *
  * @param  die Die Nummer des W�rfels, der �berpr�ft wird.
  *	
  * @retval true gdw. der W�rfel mit der Nummer die ist fixiert.
  */
bool isFixed(uint8_t die){
    return fix[die];
}

/**
  * @brief Diese Funktion w�rfelt die W�rfel, die nicht fixiert sind. Somit
	*        erhalten diese W�rfel einen neuen Wert.
  */
void rollDice(void){
    for(int i = 0; i < NO_DICE; i++){
        if(fix[i] == false){
            wuerfel[i] = (nxtRandNumber() % 6) + 1;
        }
    }
}


// EOF