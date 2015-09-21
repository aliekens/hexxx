#include "vector.h"

Vector::Vector() {
  angle = 0; 
  norm = 1;
}

Vector::Vector( double angle, double norm ) { 
  this->angle = angle; 
  this->norm = norm; 
}

void Vector::normalize() { 
  norm = 1; 
}
