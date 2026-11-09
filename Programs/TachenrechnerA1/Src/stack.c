/**
 * @file stack.c
 * @author Janice Kohrs
 * @brief Stack LiFo
 * @version 0.1
 * @date 2026-11-05
 */

#include "stack.h"

#define MAX_SIZE 100

static int stack[MAX_SIZE];
static int index = -1;

T_error push(int number) { 
    if(index >= MAX_SIZE -1){
        return ERROR_STACK_OVERFLOW;
    }

    ++index;
    stack[index] = number;
    return ERROR_NONE;   
}

T_error pop(int *elem) { 
    if(index <= -1){
        return ERROR_STACK_UNDERFLOW;
    }

    *elem = stack[index];
    --index;
    return ERROR_NONE; 
}

int get_anzahl_elems(){
    return index + 1;
}

T_error get_elem(int position, int *elem){
    if(index <= -1 || position > index || position < 0){
        return ERROR_STACK_UNDERFLOW;
    }
    *elem = stack[index - position];
    return ERROR_NONE;
}

void loesche_alle_eintrage(){
    index = -1;
}

T_error dupliziere_oberen_wert(){
    if(index <= -1){
        return ERROR_STACK_UNDERFLOW; 
    }
    int obere_wert = stack[index];
    T_error err = push(obere_wert);
    if(err != ERROR_NONE){
        return err;
    }
    return ERROR_NONE;
}

T_error vertausche_beiden_oberen_werte(){
    if(index <= 0){
        return ERROR_STACK_UNDERFLOW; 
    }
    int wert_oben = stack[index];
    int wert_unten = stack[index-1];

    stack[index-1] = wert_oben;
    stack[index] = wert_unten;

    return ERROR_NONE;
}

