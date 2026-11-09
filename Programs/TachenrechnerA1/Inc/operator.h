/**
 * @file operator.h
 * @author Janice Kohrs, HAW Hamburg
 * @date Nov 2026
 * @brief Schnittstelle des OPERATOR-Moduls.
 */

#ifndef OPERATOR_H
#define OPERATOR_H

#include "trError.h"

/**
 * @brief Addiert die oberen beiden Werte von Stack und legt die Summe wieder auf den Stack ab
 * 
 * @return T_error 
 */
T_error addiere();

/**
 * @brief Subtrahiert den oberen Stackwert vom darunterliegenden Wert // wert2 - wert1
 * 
 * @return T_error 
 */
T_error subtrahiere();

T_error multipliziere();

T_error dividiere();

T_error oberen_wert_ausgeben();

T_error oberen_drei_werte_ausgeben();

#endif /* OPERATOR_H */
// EOF