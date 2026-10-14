
#include "display.h"
#include "keypad.h"
#include <stdbool.h>

/**  statisches Terminal fuer das KeyPad
  *  es ist static, weil es modulintern ist und nicht nach außen sichtbar sein soll
  */
static Terminal keyPadTerm;

/**
  * @brief Diese Funktion initialisiert das LCD Display, die Touch Funktionalitaet
  *        und das KeyPad.
  */
void initDisplay(void){
    /* KeyPad zeichnen und Terminal merken */
    keyPadTerm = makeKeyPad();
}

/**
  * @brief Diese Funktion gibt einen farbigen String auf KeyPad-Terminal aus. 
  *
  * @param  s String, der ausgegeben wird.
  *
  * @param  c Textfarbe des zu druckende Strings.
  */
void printStr(char *s, COLOR c){
    setTextColorTerm(c, &keyPadTerm);
    printTerm(s, &keyPadTerm);
}

/**
  * @brief Diese Funktion loescht das KeyPad-Terminal.
  */
void clearDisplay(void){
    clearTerm(&keyPadTerm);
}

/**
  * @brief Diese Funktion liest die n�chste Eingabe vom KeyPad.
  *        Sie kann eine genau size Zeichen lange Zahl sein
  *        oder eine der Reset Eingaben (C oder *).
  *        Ein Reset-Key (C oder *) kann an beliebiger Stelle stehen und 
  *        beendet sofort die Eingabe.
  *        Eine Zahl wird mit dem Enter-Key (Key ohne Aufschrift)  
  *        abgeschlossen.
  *        W�hrend des Eingabeprozesses werden alle nicht gueltigen
  *        Zeichen verworfen. Werden mehr als size Ziffern eingegeben,
  *        werden die �berz�hligen auch verworfen.
  *        Die g�ltigen eingegebenen Ziffer '0' bis '9' werden auf dem KeyPad-
  *        Terminal ausgegeben.
  *
  * @param resetOnly = true: Als Eingabe wird nur ein Reset-Key akzeptiert.
  *        Dies wird z.B. benoetigt, wenn das Spiel beendet ist und der Spieler
  *        nur einen Reset-Key eingeben darf.
  *  
  * @param size Laenge des Felds a und somit Anzahl der Ziffern, die eingelesen werden.
  *
  * @param a Feld der Laenge size. Die Ziffern (0 bis 9) der eingelesenen
  *        Zahl werden in diesem Feld zuueckgegeben.
  *
  * @retval RESET_KEY, RESET_AND_HELP_KEY oder NEXT_GUESS_READ (s. defines)      
  */
char nextInput(bool resetOnly, int size, uint8_t *a){
    int index = 0;

    while (1){
        char key = getKeyPadInput();

        if (key == 0){
            continue;   // Fehler / kein Key
        }

        /* Reset-Tasten haben immer Prioritaet */
        if (key == RESET_KEY){  
            return RESET_KEY; //'C'
        }

        if (key == RESET_AND_HELP_KEY){
            return RESET_AND_HELP_KEY; //'*'
        }

        /* Wenn nur Reset erlaubt ist, alles andere ignorieren */
        if (resetOnly){
            continue;
        }

        /* Ziffern verarbeiten */
        if ((key >= '0') && (key <= '9')){
            if (index < size){
                a[index] = (uint8_t)(key - '0');
                index++;
                printChar(key, &keyPadTerm);
            }
            continue;
        }

        /* Enter beendet die Eingabe */
        if (key == ' '){
            if (index == size)
            {
                return NEXT_GUESS_READ; //' '
            }
            continue;
        }

        /* alle anderen Zeichen werden verworfen */
    }
}


// EOF