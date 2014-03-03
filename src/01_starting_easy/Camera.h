#ifndef _Camera_h_
#define _Camera_h_

#include <math.h>
#include <iostream>

#include "ObjectWithMass.h"

/* Small class to represent a point in a 3D world

 */
class Camera
{
 public:
  // constructor
  Camera(const Vector3D pPosition, const Vector3D pLookAt);

  // get the position
  Vector3D getPosition() const;

  // get the view direction
  Vector3D getLookAt() const;

 private:
  Vector3D position,lookAt;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const Camera &a);

#endif
