#ifndef _RoundObjectWithMass_h_
#define _RoundObjectWithMass_h_

#include "ObjectWithMass.h"
#include "RBGColor.h"

/* A round object with a mass
*/
class RoundObjectWithMass : public ObjectWithMass
{
 public:
  // Constructor
  RoundObjectWithMass(const char* pName, const double pMass, double pRadius, const Vector3D pPos, RBGColor pColor);

  // the radius of this object
  double getRadius() const;

 private:
  double radius;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const RoundObjectWithMass &a);

#endif
