#include "circle.h"
#include "hexxx.h"

Circle::Circle( Coordinate coordinate, double radius ) { 
  this->coordinate = coordinate; 
  this->radius = radius; 
}

Circle::Circle() { 
  radius = 0; 
}

void Circle::render( Buffer *buffer, ws2811_led_t color ) { 
  // cast a ray for each LED and check whether it is within a circle
  double radius_squared = radius * radius; // pre-compute what we're gonna need repeatedly
  double radius_plus_border_squared = ( radius + 0.5 / 11 ) * ( radius + 0.5 / 11 );
  double radius_plus_border = sqrt( radius_plus_border_squared );
  double radius_minus_border_squared = ( radius - 0.5 / 11 ) * ( radius - 0.5 / 11 );
  for( int led = 0; led < HEXAGON_LED_COUNT; led++ ) { // for every LED in the hexagon
    double x = led2unitx( led ); // get its unity X coordinate
    double dx = fabs( x - coordinate.x ); // how far is this from the center's X coordinate?
    if( dx <= radius ) { // only continue if in bounding box of circle, skip any computation we don't need
      double y = led2unity( led ); // repeat for Y
      double dy = fabs( y - coordinate.y );
      if( dy <= radius ) {
        double distance_squared = ( dx * dx ) + ( dy * dy ); // compute distance to center
        if( distance_squared <= radius_minus_border_squared ) // we're fully in the circle!
          buffer->setPixel( led, color );
        else if( distance_squared <= radius_plus_border_squared ) { // we're on partly in the circle!
          double factor = ( radius_plus_border - sqrt( distance_squared ) ) * 11; // approximation for computing overlap for anti-aliasing in [0:1], only now we use sqrt
          buffer->setPixel( led, color, factor );
        }
      }
    }
  }
}

double Circle::distance( Coordinate other ) {
  return coordinate.distance( other );
}