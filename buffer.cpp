#include <string.h> // memcpy

#include "buffer.h"
#include "hexxx.h"

Buffer::Buffer() {
  fill( 0 );
}

void Buffer::fill( ws2811_led_t c ) {
  for( int i = 0; i < HEXAGON_LED_COUNT; i++ ) {
    setPixel( i, c );
  }
}

void Buffer::fill( ws2811_led_t c, double alpha ) {
  for( int i = 0; i < HEXAGON_LED_COUNT; i++ ) {
    setPixel( i, c, alpha );
  }
}

void Buffer::setPixel( int led, ws2811_led_t c ) {
  buffer[ led ] = c;
}

ws2811_led_t Buffer::getPixel( int led ) {
  return buffer[ led ];
}

void Buffer::setPixel( int led, ws2811_led_t c, double alpha ) {
  ws2811_led_t previouscolor = getPixel( led );
  int r = getRed( previouscolor ) * ( 1.0 - alpha ) + getRed( c ) * alpha;
  int g = getGreen( previouscolor ) * ( 1.0 - alpha ) + getGreen( c ) * alpha;
  int b = getBlue( previouscolor ) * ( 1.0 - alpha ) + getBlue( c ) * alpha;
  setPixel( led, color( r, g, b ) );
}

void Buffer::render() {
  for( int i = 0; i < HEXAGON_LED_COUNT; i++ ) {
    setColor( i, applyGammaCorrection( buffer[ i ] ) );
  }
}

void Buffer::rotate(double angle, Buffer* rotated) {
  // determine for each (rotated) pixel its original color (before rotation)
  for( int rled = 0; rled < HEXAGON_LED_COUNT; rled++ ) {
    float rx  = led2unitx( rled ),
          ry  = led2unity( rled ),
          x = rx * cos(-angle) - ry * sin(-angle),
          y = ry * cos(-angle) + rx * sin(-angle);
    int led = unit2led(x, y);
    rotated->setPixel(rled, this->getPixel(led));
  }
}

void Buffer::rotate(double angle) {
  Buffer rotated;
  this->rotate(angle, &rotated);
  memcpy(this->buffer, rotated.buffer, sizeof(this->buffer));
}
