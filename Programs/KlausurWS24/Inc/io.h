#ifndef _IO_H
#define _IO_H

#include <stdint.h>
#include <stdbool.h>

void setLEDs(uint8_t noLeds);

bool buttonPressed(uint8_t button);

#endif