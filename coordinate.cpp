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

void Coordinate::print() { 
  std::cout << x << "\t" << y << std::endl; 
}
