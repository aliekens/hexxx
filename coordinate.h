#ifndef COORDINATE_H
#define COORDINATE_H

#include "vector.h"

class Coordinate {
public:
  double x, y;
  Coordinate();
  Coordinate( double x, double y );
  Coordinate operator+( const Vector& vector );
  Coordinate operator+( const Coordinate& vector );
  Coordinate operator*( const double& d );
  Coordinate operator/( const double& d );
  double distance( const Coordinate& other ) const;
  void print();
};

#endif