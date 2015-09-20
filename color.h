#ifndef COLOR__H
#define COLOR__H

#include <stdint.h>
#include "ws2811/ws2811.h"

#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xFFFFFF
#define COLOR_RED 0x00FF00
#define COLOR_GREEN 0xFF0000
#define COLOR_BLUE 0x0000FF
#define COLOR_YELLOW 0xFFFF00
#define COLOR_MAGENTA 0x00FFFF
#define COLOR_CYAN 0xFF00FF

ws2811_led_t color( const uint8_t red, const uint8_t green, const uint8_t blue );
uint8_t getRed( const ws2811_led_t color );
uint8_t getGreen( const ws2811_led_t color );
uint8_t getBlue( const ws2811_led_t color );

// GAMMA CORRECTION

extern uint8_t gammaCorrection[256];

uint8_t applyGammaCorrection( const uint8_t input );
ws2811_led_t applyGammaCorrection( const ws2811_led_t color );
ws2811_led_t applyGammaCorrection( const uint8_t red, const uint8_t green, const uint8_t blue );

ws2811_led_t darkenColor( const ws2811_led_t color, int multiplier = 4, int divisor = 5, int min = 10 );
void darkenhexagon();

ws2811_led_t randomColor( const int brightness = 256 );

#endif