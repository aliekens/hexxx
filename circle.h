#ifndef CIRCLE_H
#define CIRCLE_H

#include "coordinate.h"
#include "hexxx.h"
#include "buffer.h"

class Circle {
public:
  Coordinate coordinate;
  double radius;
  Circle( Coordinate coordinate, double radius );
  Circle();
  void render( Buffer *buffer, ws2811_led_t color );
};

#endif