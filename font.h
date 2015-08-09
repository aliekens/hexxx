#ifndef FONT__H
#define FONT__H

#include <stdint.h>

#include <string>

#include "ws2811/ws2811.h"

extern uint32_t font[5][6];
extern std::string characters;

void printCharacter( int skewedx, int skewedy, char c, ws2811_led_t color );
void printString( int skewedx, int skewedy, std::string str, ws2811_led_t color );

#endif