#ifndef FONT__H
#define FONT__H

#include <stdint.h>

#include <string>

#include "ws2811/ws2811.h"

extern uint32_t font[5][6];
extern std::string characters;

int printCharacter( int position, char c, ws2811_led_t color );

#endif