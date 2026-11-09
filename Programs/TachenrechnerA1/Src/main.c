/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   RPN-Taschenrechner
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "display.h"
#include "init.h"
#include "lcd.h"
#include "scanner.h"
#include "stm32f4xx_hal.h"
#include "token.h"
#include "stack.h"
#include "operator.h"

int main(void) {
   initITSboard(); 
   init_display();

   bool fehlerzustand = false;

   while (1) {
      T_token neu = next_token();
      T_error err = ERROR_NONE;

      if(fehlerzustand == true && neu.tok != CLEAR){
         continue; //der Schleifendurchlauf wird sofort beendet, die switches werden nicht ausgeführt
      }

      switch(neu.tok){
         case NUMBER:
            err = push(neu.val);
            break;
         case CLEAR:
            loesche_alle_eintrage();
            set_normal_mode();
            err = ERROR_NONE;
            fehlerzustand = false;
            break;
         case PLUS:
            err = addiere();
            break;
         case MINUS:
            err = subtrahiere();
            break;
         case MULT:
            err = multipliziere();
            break;
         case DIV:
            err = dividiere();
            break;
         case PRT:
            err = oberen_wert_ausgeben();
            break;
         case PRT_ALL:
            err = oberen_drei_werte_ausgeben();
            break;
         case SWAP:
            err = vertausche_beiden_oberen_werte();
            break;
         case DOUBLE:
            err = dupliziere_oberen_wert();
            break;
         case UNEXPECTED:
            err = ERROR_UNEXPECTED_INPUT;
            break;
         case OVERFLOW:
            err = ERROR_NUMBER;
            break;
         default: 
            break;
      }

      char *fehlermeldung = NULL;

      switch(err){
         case ERROR_STACK_OVERFLOW:
            fehlermeldung = "Error: Stack Overflow";
            break;
         case ERROR_STACK_UNDERFLOW:
            fehlermeldung = "Error: Stack Underflow";
            break;
         case ERROR_DIVISION_BY_ZERO:
            fehlermeldung = "Error: Division by Zero";
            break;
         case ERROR_ARITHMETIC_OVERFLOW:
            fehlermeldung = "Error: Arithmetic Overflow";
            break;
         case ERROR_ARITHMETIC_UNDERFLOW:
            fehlermeldung = "Error: Arithmetischer Underflow";
            break;
         case ERROR_UNEXPECTED_INPUT:
            fehlermeldung = "Error: Unexpected input key";
            break;
         case ERROR_NUMBER:
            fehlermeldung = "Error: Overflow during input of number";
            break;
         default: 
            break;
      }

      if(fehlermeldung != NULL){
         set_err_mode();
         print_stdout(fehlermeldung);
         print_stdout("\n Reset mit C");
         fehlerzustand = true;
      }
   }
}

// EOF
