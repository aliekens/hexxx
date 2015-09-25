#ifndef LINE_H
#define LINE_H

#include "coordinate.h"
#include "vector.h"
#include "hexxx.h"
#include "buffer.h"

class Line {
public:
  Coordinate coordinate;
  Vector vector;
  Line();
  Line( Coordinate coordinate, Vector vector );
  void render( Buffer *buffer, ws2811_led_t color );
  double distance( Coordinate point ); // distance of line to point
  Coordinate intersection( Line other );
  bool side( Coordinate point ); // is the point on the left or right side of the line
};

#endif