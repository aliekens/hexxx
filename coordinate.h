#ifndef COORDINATE_H
#define COORDINATE_H

#include "vector.h"

class Coordinate {
public:
  double x, y;
  Coordinate();
  Coordinate( double x, double y );
  Coordinate operator+( const Vector& vector );
  void print();
};

#endif