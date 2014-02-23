#ifndef _RoundObjectWithMass_h_
#define _RoundObjectWithMass_h_

#include "ObjectWithMass.h"

class RoundObjectWithMass : public ObjectWithMass
{
 public:
  // Constructor
  RoundObjectWithMass(const char* pName, const double pMass, double pRadius, double x, double y, double z);
  double getRadius() const;
 private:
  double radius;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const RoundObjectWithMass &a);

#endif
