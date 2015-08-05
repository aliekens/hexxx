#include "color.h"
#include <stdlib.h>

ws2811_led_t color( uint8_t red, uint8_t green, uint8_t blue ) {
  return ( (uint32_t)green << 16 ) | ( (uint32_t)red << 8 ) | ( (uint32_t)blue );
}

uint8_t getRed( ws2811_led_t color ) {
  return (uint8_t)( ( color & 0x00ff00 ) >> 8 );
}

uint8_t getGreen( ws2811_led_t color ) {
  return (uint8_t)( ( color & 0xff0000 ) >> 16 );
}

uint8_t getBlue( ws2811_led_t color ) {
  return (uint8_t)( ( color & 0x0000ff ) >> 0 );
}

// GAMMA CORRECTION

uint8_t gammaCorrection[ 256 ] = {
  0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 
  3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 
  7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 
  10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 
  14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 
  18, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22, 22, 23, 
  23, 23, 24, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 
  28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 
  33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 38, 38, 38, 39, 
  39, 39, 40, 40, 41, 41, 41, 42, 42, 43, 43, 44, 44, 44, 45, 45, 
  46, 46, 47, 47, 47, 48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 
  53, 54, 54, 55, 55, 56, 56, 57, 58, 58, 59, 59, 60, 60, 61, 62, 
  62, 63, 63, 64, 65, 65, 66, 67, 67, 68, 69, 69, 70, 71, 72, 72, 
  73, 74, 75, 76, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 
  88, 89, 90, 91, 92, 93, 95, 96, 97, 99, 100, 102, 103, 105, 107, 108, 
  110, 112, 114, 117, 119, 122, 124, 127, 131, 135, 139, 144, 150, 158, 171, 255
};

uint8_t applyGammaCorrection( uint8_t input ) {
  return gammaCorrection[ input ];
}

ws2811_led_t applyGammaCorrection( ws2811_led_t c ) {
  return color( 
    applyGammaCorrection( getRed( c ) ), 
    applyGammaCorrection( getGreen( c ) ), 
    applyGammaCorrection( getBlue( c ) ) 
  );
}

ws2811_led_t applyGammaCorrection( uint8_t red, uint8_t green, uint8_t blue ) {
  return color( 
    applyGammaCorrection( red ), 
    applyGammaCorrection( green ), 
    applyGammaCorrection( blue ) 
  );
}

ws2811_led_t darkenColor( ws2811_led_t c ) {
  return color( getRed( c ) / 20 * 19, getGreen( c ) / 20 * 19, getBlue( c ) / 20 * 19 );
}

ws2811_led_t randomColor( int brightness ) {
  return color( rand() % brightness, rand() % brightness, rand() % brightness );
}
