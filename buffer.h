#ifndef BUFFER_H
#define BUFFER_H

#include "hexxx.h"

// Smart buffer for double buffered rendering
// Buffer handles alpha colors
// Rendering calls Gamma correction

class Buffer {
private:
  ws2811_led_t buffer[ HEXAGON_LED_COUNT ];
public:
  Buffer();
  void fill( ws2811_led_t color );
  void fill( ws2811_led_t color, double alpha );
  ws2811_led_t getPixel( int led );
  void setPixel( int led, ws2811_led_t color );
  void setPixel( int led, ws2811_led_t color, double alpha ); // alpha between 0 and 1
  void render();
  void rotate(double angle, Buffer* rotated);
  void rotate(double angle);
  void darken(double factor);
};

#endif