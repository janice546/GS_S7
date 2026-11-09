/**
 * @file operator.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-11-06
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "operator.h"
#include "limits.h"
#include "stack.h"
#include "display.h"
#include <stdio.h>

#define MIN_ELEMS 2
#define MAX_ZEICHEN 20 //für 32-Bit-int ausreichend auch für negative Zahlen

static T_error hole_zwei_werte(int *wert1, int *wert2){
    //Prüfen, ob mind zwei Elemente sich auf dem Stack befinden
    if(get_anzahl_elems() < MIN_ELEMS){
        return ERROR_STACK_UNDERFLOW;
    }
    T_error err;
    
    //Werte von Stack holen und die Rückgabe werte prüfen
    err = pop(wert1);
    if(err != ERROR_NONE){
        return err;
    }
    err = pop(wert2);
    if(err != ERROR_NONE){
        return err;
    }

    return ERROR_NONE;
}

T_error addiere(){
    int wert1;
    int wert2;

    T_error err = hole_zwei_werte(&wert1, &wert2);
    if(err != ERROR_NONE){
        return err;
    }

    //arithmetische Under- und Overflow prüfen
    if(wert2 < 0 && wert1 < INT_MIN - wert2){
        return ERROR_ARITHMETIC_UNDERFLOW;
    }
    if(wert2 > 0 && wert1 > INT_MAX - wert2){
        return ERROR_ARITHMETIC_OVERFLOW;
    }
    
    //Addition
    int summe = wert1 + wert2;
    //Summe auf den Stack pushen und den Rückgabewert prüfen
    err = push(summe);
    if(err != ERROR_NONE){
        return err;
    }
    return ERROR_NONE;
}

T_error subtrahiere(){
    int wert1;
    int wert2;

    T_error err = hole_zwei_werte(&wert1, &wert2);
    if(err != ERROR_NONE){
        return err;
    }

    //arithmetische Under- und Overflow prüfen
    //wenn wert1 > 0, kann wert2 - wert1 zu klein werden
    if(wert1 > 0 && wert2 < INT_MIN + wert1){
        return ERROR_ARITHMETIC_UNDERFLOW;
    }
    //wenn wert1 < 0, kann wert2 - wert1 zu groß werden
    if(wert1 < 0 && wert2 > INT_MAX + wert1){
        return ERROR_ARITHMETIC_OVERFLOW;
    }
    
    //Subtraktion
    int differenz = wert2 - wert1;
    //Differenz auf den Stack pushen und den Rückgabewert prüfen
    err = push(differenz);
    if(err != ERROR_NONE){
        return err;
    }
    return ERROR_NONE;
}

T_error multipliziere(){
    int wert1;
    int wert2;

    T_error err = hole_zwei_werte(&wert1, &wert2);
    if(err != ERROR_NONE){
        return err;
    }

    //arithmetische Under- und Overflow prüfen
    //INT_MAX=2.147.483.647
    //INT_MIN=-2.147.483.648
    //INT_MAX / -1 = −2.147.483.647   -> Gültig
    //INT_MIN / -1 = +2.147.483.648   -> nicht gültig
    if(wert1 > 0 && wert2 > 0 && wert1 > INT_MAX / wert2){
        return ERROR_ARITHMETIC_OVERFLOW;
    }
    if(wert1 > 0 && wert2 < -1 && wert1 > INT_MIN / wert2){ //Sonderfall: -1, weil INT_MIN / -1 zu einem overflow führt
        return ERROR_ARITHMETIC_UNDERFLOW;                  //deswegen wird der ausgeschlossen
    }
    if(wert1 < 0 && wert2 > 0 && wert1 < INT_MIN / wert2){
        return ERROR_ARITHMETIC_UNDERFLOW;
    }
    if(wert1 < 0 && wert2 < 0 && wert1 < INT_MAX / wert2){
        return ERROR_ARITHMETIC_OVERFLOW;
    }
    
    //Muliplikation
    int produkt = wert1 * wert2;
    //Produkt auf den Stack pushen und den Rückgabewert prüfen
    err = push(produkt);
    if(err != ERROR_NONE){
        return err;
    }

    return ERROR_NONE;
}

T_error dividiere(){
    int wert1;
    int wert2;

    T_error err = hole_zwei_werte(&wert1, &wert2);
    if(err != ERROR_NONE){
        return err;
    }

    //Division durch null
    if(wert1 == 0){
        return ERROR_DIVISION_BY_ZERO;
    }

    //arithmetische Under- und Overflow prüfen
    //INT_MAX=2.147.483.647
    //INT_MIN=-2.147.483.648
    //INT_MAX / -1 = −2.147.483.647   -> Gültig
    //INT_MIN / -1 = +2.147.483.648   -> nicht gültig
    if(wert1 == -1 && wert2 == INT_MIN){
        return ERROR_ARITHMETIC_OVERFLOW;
    }

    //Division
    int quotient = wert2 / wert1;
    //Quotient auf den Stack pushen und den Rückgabewert prüfen
    err = push(quotient);
    if(err != ERROR_NONE){
        return err;
    }

    return ERROR_NONE;
}

T_error oberen_wert_ausgeben(){
    int oberen_wert;
    int oben = 0;
    clear_stdout();

    T_error err = get_elem(oben, &oberen_wert);
    if(err == ERROR_STACK_UNDERFLOW){
        print_stdout("empty stack");
        return ERROR_NONE;
    }
    if(err != ERROR_NONE){
        return err;
    }
    
    //int in String umwandeln
    char ausgabe[MAX_ZEICHEN];
    snprintf(ausgabe, sizeof(ausgabe), "%d", oberen_wert);

    print_stdout(ausgabe);
    return ERROR_NONE;
}

T_error oberen_drei_werte_ausgeben(){
    int wert;
    T_error err;
    int anzahl_stack = get_anzahl_elems();
    int max_ausgabe = 3;
    clear_stdout();

    if(anzahl_stack == 0){
        print_stdout("empty stack");
        return ERROR_NONE;
    }
    if(anzahl_stack < 3){
        max_ausgabe = anzahl_stack;
    }
    
    for(int i = 0; i < max_ausgabe; i++){
        err = get_elem(i, &wert);
        if(err != ERROR_NONE){
            return err;
        }
        //int in String umwandeln
        char ausgabe[MAX_ZEICHEN];
        snprintf(ausgabe, sizeof(ausgabe), "%d\n", wert);

        print_stdout(ausgabe);
    }
    return ERROR_NONE;
}