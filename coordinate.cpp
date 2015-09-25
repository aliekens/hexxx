#include "coordinate.h"
#include "vector.h"
#include <iostream>
#include <math.h>

Coordinate::Coordinate() { 
  x = 0; 
  y = 0; 
}

Coordinate::Coordinate( double x, double y ) { 
  this->x = x;
  this->y = y;
}

Coordinate Coordinate::operator+( const Vector& vector ) { 
  Coordinate result;
  result.x = x + cos( vector.angle ) * vector.norm;
  result.y = y + sin( vector.angle ) * vector.norm;
  return result;
}

Coordinate Coordinate::operator+( const Coordinate& other ) { 
  return Coordinate( x + other.x, y + other.y );
}

Coordinate Coordinate::operator*( const double& d ) { 
  return Coordinate( x * d, y * d );
}

Coordinate Coordinate::operator/( const double& d ) { 
  return Coordinate( x / d, y / d );
}

void Coordinate::print() { 
  std::cout << x << "\t" << y << std::endl;
}

double Coordinate::distance( const Coordinate& other ) const {
  double dx = other.x - x;
  double dy = other.y - y;
  return sqrt( dx * dx + dy * dy );
}
