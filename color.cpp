#include "color.h"
#include "hexxx.h"
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

uint8_t gammaCorrection[ 256 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 23, 23, 24, 24, 25, 26, 26, 27, 28, 28, 29, 30, 30, 31, 32, 33, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 61, 62, 63, 64, 65, 66, 67, 69, 70, 71, 72, 74, 75, 76, 77, 79, 80, 81, 83, 84, 86, 87, 88, 90, 91, 93, 94, 96, 97, 99, 100, 102, 103, 105, 107, 108, 110, 111, 113, 115, 116, 118, 120, 122, 123, 125, 127, 129, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 175, 177, 179, 181, 184, 186, 188, 191, 193, 195, 198, 200, 202, 205, 207, 210, 212, 215, 217, 220, 222, 225, 227, 230, 233, 235, 238, 241, 243, 246, 249, 252, 255 };

uint8_t gammaError[ 256 ] = { 0, 35, 45, 52, 57, 62, 66, 70, 74, 77, 80, 82, 85, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 107, 109, 111, 112, 114, 115, 117, 118, 120, 121, 122, 124, 125, 126, 127, 129, 130, 131, 132, 133, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 152, 153, 154, 155, 156, 157, 158, 159, 159, 160, 161, 162, 163, 163, 164, 165, 166, 167, 167, 168, 169, 170, 170, 171, 172, 172, 173, 174, 175, 175, 176, 177, 177, 178, 179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 185, 186, 186, 187, 188, 188, 189, 190, 190, 191, 191, 192, 193, 193, 194, 194, 195, 195, 196, 197, 197, 198, 198, 199, 199, 200, 201, 201, 202, 202, 203, 203, 204, 204, 205, 205, 206, 206, 207, 207, 208, 208, 209, 209, 210, 210, 211, 211, 212, 212, 213, 213, 214, 214, 215, 215, 216, 216, 217, 217, 218, 218, 219, 219, 220, 220, 221, 221, 222, 222, 222, 223, 223, 224, 224, 225, 225, 226, 226, 226, 227, 227, 228, 228, 229, 229, 229, 230, 230, 231, 231, 232, 232, 232, 233, 233, 234, 234, 235, 235, 235, 236, 236, 237, 237, 237, 238, 238, 239, 239, 239, 240, 240, 241, 241, 241, 242, 242, 243, 243, 243, 244, 244, 245, 245, 245, 246, 246, 246, 247, 247, 248, 248, 248, 249, 249, 249, 250, 250, 251, 251, 251, 252, 252, 252, 253, 253, 253, 254, 254, 255 };

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

uint8_t applyGammaError( uint8_t input ) {
  return gammaError[ input ];
}

ws2811_led_t applyGammaError( ws2811_led_t c ) {
  return color( 
    applyGammaError( getRed( c ) ), 
    applyGammaError( getGreen( c ) ), 
    applyGammaError( getBlue( c ) ) 
  );
}

ws2811_led_t applyGammaError( uint8_t red, uint8_t green, uint8_t blue ) {
  return color( 
    applyGammaError( red ), 
    applyGammaError( green ), 
    applyGammaError( blue ) 
  );
}

ws2811_led_t darkenColor( ws2811_led_t c, int multiplier, int diviser, int min ) {
  uint8_t red = multiplier * (uint32_t)getRed( c ) / diviser;
  uint8_t green = multiplier * (uint32_t)getGreen( c ) / diviser;
  uint8_t blue = multiplier * (uint32_t)getBlue( c ) / diviser;
  if( red <= min ) red = 0;
  if( green <= min ) green = 0;
  if( blue <= min ) blue = 0;
  return color( red, green, blue );
}

ws2811_led_t darkenColor( ws2811_led_t c, double factor ) {
  uint8_t red = factor * getRed( c );
  uint8_t green = factor * getGreen( c );
  uint8_t blue = factor * getBlue( c );
  return color( red, green, blue );
}

void darkenhexagon() {
  for( int i = 0; i < LED_COUNT - 3; i++ ) {
    setColor( i, darkenColor( getColor( i ) ) );
  }
}

ws2811_led_t randomColor( int brightness ) {
  return color( rand() % brightness, rand() % brightness, rand() % brightness );
}
