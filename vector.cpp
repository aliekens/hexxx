#include "vector.h"

Vector::Vector() {
  angle = 0; 
  norm = 1;
}

Vector::Vector( double angle, double norm ) { 
  this->angle = angle; 
  this->norm = norm; 
}

Vector Vector::operator*( double factor ) {
  return Vector( angle, norm * factor );
}

void Vector::normalize() { 
  norm = 1; 
}
