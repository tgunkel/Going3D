#ifndef _ObjectWithMass_h_
#define _ObjectWithMass_h_

#include "Vector3D.h"

class ObjectWithMass
{
 public:
  // Constructor
  ObjectWithMass(const char* pName, const double pMass, const double x, const double y, const double z);

  // Name of the object
  const char* getName()     const;

  // Mass
  double      getMass()     const;

  // Position
  Vector3D    getPosition() const;

  // Distance to other object as a vector
  Vector3D    getDistance(const ObjectWithMass &other) const;

  // get the acceleration through another object
  double getGravityAcceleration(const ObjectWithMass &other) const;

  // http://en.wikipedia.org/wiki/Gravitational_constant
  const static double GRAVITYCONST=.0000000000667384;

 private:
  const char* name;
  double mass;
  Vector3D position;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const ObjectWithMass &a);

#endif
