#ifndef _Vector3D_h_
#define _Vector3D_h_

#include <math.h>
#include <iostream>

/* Small class to represent a point in a 3D world

 */
class Vector3D
{
 public:
  // constructor
  Vector3D(double pX, double pY, double pZ);

  // get the X value
  double   const getX();

  // get the Y value
  double   const getY();

  // get the Z value
  double   const getZ();

  // return a new Vector3D which is the sum of us and the other
  Vector3D const add(const Vector3D &other);

  // return a new Vector3D which is we-other
  Vector3D const sub(const Vector3D &other);

  // the length of ourself
  double   const length();

  // a new vector which point in the same direction we do, but with length 1
  Vector3D const normalize();

  // a new vector where all values have been multiplied with your scalar
  Vector3D const mult(double scalar);  

 private:
  double x,y,z;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const Vector3D &a);

#endif
