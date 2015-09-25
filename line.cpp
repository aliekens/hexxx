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

Coordinate Line::intersection( Line other ) {
  
  double x1 = coordinate.x;
  double y1 = coordinate.y;
  double x2 = ( coordinate + vector ).x;
  double y2 = ( coordinate + vector ).y;
  double x3 = other.coordinate.x;
  double y3 = other.coordinate.y;
  double x4 = ( other.coordinate + other.vector ).x;
  double y4 = ( other.coordinate + other.vector ).y;
  
  double denominator = ( x1 - x2 ) * ( y3 - y4 ) - ( y1 - y2 ) * ( x3 - x4 );
  double part1 = x1 * y2 - y1 * x2;
  double part2 = x3 * y4 - y3 * x4;
  return Coordinate(
    ( part1 * ( x3 - x4 ) - ( x1 - x2 ) * part2 ) / denominator,
    ( part1 * ( y3 - y4 ) - ( y1 - y2 ) * part2 ) / denominator
  );
}

bool Line::side( Coordinate point ) {
  Coordinate c1 = coordinate;
  Coordinate c2 = coordinate + vector;
  return (
    ( c2.x - c1.x ) * ( c1.y - point.y ) -
    ( c1.x - point.x ) * ( c2.y - c1.y )
  ) > 0;
}
