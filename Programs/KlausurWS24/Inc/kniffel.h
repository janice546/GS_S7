#ifndef _KNIFFEL_H
#define _KNIFFEL_H

/**
 ******************************************************************************
 * @file    kniffel.h
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    20. Jan. 2025
 * @brief   Interface des Moduls zum Handling der Würfel.
 ******************************************************************************
 */

#include <stdint.h>
#include <stdbool.h>

/**
  * @brief Diese Funktion liefert den aktuellen Wert eines Würfels.
  *
  * @param  die Der Würfel, dessen Wert bestimmt wird.
  *	
  * @retval Der Wert des Würfels.
  */
uint8_t getDie(uint8_t die);

/**
  * @brief Diese Funktion überprüft, ob alle Würfel den Wert 1 haben - also
	*        ein Kniffel vorliegt.
  *
  * @retval true gdw. ein Kniffel liegt vor.
  */
bool isKniffel(void);

/**
  * @brief Diese Funktion überprüft, ob die Werte der Würfel eine Strasse ergeben
  *        also eintweder 1 2 3 4 5 oder 2 3 4 5 6 sind.
  *
  * @retval true gdw. eine Strasse liegt vor.
  */
bool isStreet(void);

/**
  * @brief Diese Funktion fixiert den Würfel mit der Nummer die. Ein fixierter
	*        Würfel wird beim nächsten Wurf nicht geworfen / gewürfelt.
  *
  * @param  die Die Nummer des Würfels, der fixiert wird.
  */
void fixDie(uint8_t die);

/**
  * @brief Diese Funktion löst die Fixierung aller Würfel auf, so dass alle 
	*        Würfel beim nächsten Wurf mit gewürfelt werden.
  */
void releaseDice(void);

/**
  * @brief Diese Funktion überprüft, ob der Würfel mit der Nummer die fixiert ist.
  *
  * @param  die Die Nummer des Würfels, der überprüft wird.
  *	
  * @retval true gdw. der Würfel mit der Nummer die ist fixiert.
  */
bool isFixed(uint8_t die);

/**
  * @brief Diese Funktion würfelt die Würfel, die nicht fixiert sind. Somit
	*        erhalten diese Würfel einen neuen Wert.
  */
void rollDice(void);

#endif
// EOF
