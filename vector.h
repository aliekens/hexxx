#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
  double angle, norm;
  Vector();
  Vector( double angle, double norm );
  void normalize();
};

#endif