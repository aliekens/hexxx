#ifndef COLOR__H
#define COLOR__H

#include <stdint.h>
#include "ws2811/ws2811.h"

ws2811_led_t color( uint8_t red, uint8_t green, uint8_t blue );
uint8_t getRed( ws2811_led_t color );
uint8_t getGreen( ws2811_led_t color );
uint8_t getBlue( ws2811_led_t color );

// GAMMA CORRECTION

extern uint8_t gammaCorrection[256];

uint8_t applyGammaCorrection( uint8_t input );
ws2811_led_t applyGammaCorrection( ws2811_led_t color );
ws2811_led_t applyGammaCorrection( uint8_t red, uint8_t green, uint8_t blue );

#endif