#include "line.h"
#include "hexxx.h"

Line::Line() {
}

Line::Line( Coordinate coordinate, Vector vector ) { 
  this->coordinate = coordinate; 
  this->vector = vector; 
}

void Line::render( Buffer *buffer, ws2811_led_t color ) {
  for( int led = 0; led < HEXAGON_LED_COUNT; led++ ) { // for every LED in the hexagon
    Coordinate ledCoordinate( led2unitx( led ), led2unity( led ) );
    double d = distance( ledCoordinate );
    if( d < 1.0 / 11 )
      buffer->setPixel( led, color, 1 - d * 11 );
  }
}

double Line::distance( Coordinate point ) {
  Vector v = vector;
  v.normalize();
  Coordinate c1 = coordinate;
  Coordinate c2 = coordinate + v;
  return fabs(
    ( c2.x - c1.x ) * ( c1.y - point.y ) -
    ( c1.x - point.x ) * ( c2.y - c1.y )
  );
}
