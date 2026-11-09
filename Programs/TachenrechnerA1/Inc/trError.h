/**
 * @file trError.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-11-05
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef TRERROR_H
#define TRERROR_H

typedef enum {
    ERROR_NONE,
    ERROR_STACK_OVERFLOW,
    ERROR_STACK_UNDERFLOW,
    ERROR_DIVISION_BY_ZERO,
    ERROR_ARITHMETIC_OVERFLOW,
    ERROR_ARITHMETIC_UNDERFLOW,
    ERROR_UNEXPECTED_INPUT,
    ERROR_NUMBER
} T_error;

#endif /* TRERROR_H */
// EOF