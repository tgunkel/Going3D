#ifndef _ObjectWithMass_h_
#define _ObjectWithMass_h_

#include "Vector3D.h"
#include "RBGColor.h"

class ObjectWithMass
{
 public:
  // Constructor
  ObjectWithMass(const char* pName, const double pMass, const Vector3D pPos, const  RBGColor pColor);

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

  RBGColor getColor() const;

  // http://en.wikipedia.org/wiki/Gravitational_constant
  const static double GRAVITYCONST=.0000000000667384;

 private:
  const char* name;
  double mass;
  Vector3D position;
  RBGColor color;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const ObjectWithMass &a);

#endif
