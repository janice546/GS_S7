/**
 * @file stack.h
 * @author Janice Kohrs, HAW Hamburg
 * @date Nov 2026 ddkl
 * @brief Schnittstelle des Stack-Moduls.
 */

#ifndef STACK_H
#define STACK_H

#include "trError.h"

/**
 * @brief Legt eine Zahl auf den Stack.
 * 
 * @param number Zahl, die auf den Stack gelegt wird.
 *
 * @return Fehlermeldung
 */
T_error push(int number);

/**
 * @brief Entfernt die oberste Zahl vom Stack.
 *
 * @param number Zeiger auf die Zahl, die vom Stack entfernt wird.
 * 
 * @return Fehlermeldung
 */
T_error pop(int *elem);

/**
 * @brief Get the Anzahl Elems object
 * 
 * @return int 
 */
int get_anzahl_elems();

T_error get_elem(int position, int *elem);

void loesche_alle_eintrage();

T_error dupliziere_oberen_wert();

T_error vertausche_beiden_oberen_werte();

#endif /* stack_H */
// EOF