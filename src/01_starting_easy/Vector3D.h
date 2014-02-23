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
  Vector3D(const double pX, const double pY, const double pZ);

  // get the X value
  double   getX() const;

  // get the Y value
  double   getY() const;

  // get the Z value
  double   getZ() const;

  // return a new Vector3D which is the sum of us and the other
  Vector3D add(const Vector3D &other) const;

  // return a new Vector3D which is we-other
  Vector3D sub(const Vector3D &other) const;

  // the length of ourself
  double  length() const;

  // a new vector which point in the same direction we do, but with length 1
  Vector3D normalize() const;

  // a new vector where all values have been multiplied with your scalar
  Vector3D mult(double scalar) const;

 private:
  double x,y,z;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const Vector3D &a);

#endif
