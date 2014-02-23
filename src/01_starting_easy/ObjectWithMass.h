#ifndef _ObjectWithMass_h_
#define _ObjectWithMass_h_

#include "Vector3D.h"

class ObjectWithMass
{
 public:
  // Constructor
  ObjectWithMass(const char* pName, const double pMass, double x, double y, double z);

  // Name of the object
  const char* getName()     const;

  // Mass
  double      getMass()     const;

  // Position
  Vector3D    getPosition() const;

  // Distance to other object as a vector
  Vector3D    getDistance(const ObjectWithMass &other) const;

 private:
  const char* name;
  double mass;
  Vector3D position;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const ObjectWithMass &a);

#endif
