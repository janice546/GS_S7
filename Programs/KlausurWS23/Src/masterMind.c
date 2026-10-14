#include "masterMind.h"
#include "display.h"
#include "random.h"
#include <stdint.h>

/**
  * @brief Diese Funktion gibt in einer Zeile des KeyPad Terminals eine Zahl aus.
  *        Diese Zahl ist entweder die gesuchte Zahl oder die aktuell geratene Zahl.
  *        Bei der Ausgabe einer geratenen Zahl werden die Ziffern entsprechend
  *        eingefaerbt.
  *        Der Ausgabe wird ein String vorangestellt. Die Ausgabe endet mit 
  *        einem NewLine.
  * 
  * @param s String, der vor der Zahl ausgegeben wird
  *
  * @param size Groesse der Felder sno und guess
  *
  * @param sno Feld, das die Ziffern der gesuchten Zahl enthaelt
  *  
  * @param guess Feld, das die Ziffern der aktuell geratenen Zahl enthaelt
  *        Ist guess == NULL, so wird die gesuchte Zahl ausgegeben.
  *        Ist guess != NULL, wird die geratene Zahl ausgegeben.
  */
void printNumber(char *s, int size, uint8_t *sno, uint8_t *guess)
{
    printStr(s, DEFAULT_COLOR);

    if (guess == NULL)
    {
        for (int i = 0; i < size; i++)
        {
            char buf[2];
            buf[0] = (char)('0' + sno[i]);
            buf[1] = '\0';
            printStr(buf, DEFAULT_COLOR);  //schwarz
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            char buf[2];
            buf[0] = (char)('0' + guess[i]);
            buf[1] = '\0';

            if (sno[i] == guess[i])
                printStr(buf, HIT_COLOR); //blau
            else
                printStr(buf, MISS_COLOR); //rot
        }
    }

    printStr("\n", DEFAULT_COLOR);
}


/**
  * @brief Diese Funktion ueberprueft, ob guess und sno uebereinstimmen.
  *        In diesem Fall ist das Spiel erfolgreich beendet.
  * 
  * @param size Groesse der Felder sno und guess
  *
  * @param sno Feld, das die Ziffern der gesuchten Zahl enthaelt
  *  
  * @param guess Feld, das die Ziffern der aktuell geratenen Zahl enthaelt
  *
  * @retval true: sno und guess stimmen ueberein
  */
bool won(int size, uint8_t *sno, uint8_t *guess){
    for(int i = 0; i < size; i++){
        if(sno[i] != guess[i]){
            return false;
        }
    }
    return true;
}

/**
  * @brief Diese Funktion fuellt sno mit einer neuen Zufallszahl.
  *
  * @param size Groesse des Felds sno
  *
  * @param sno Feld, das mit der neuen Zufallszahl gefuellt wird
  *  
  */
void genNewNumber(int size, uint8_t *sno){
    for(int i = 0; i < size; i++){
        sno[i] =(uint8_t) (nxtRandNumber() % 10);
    }
}


// EOF