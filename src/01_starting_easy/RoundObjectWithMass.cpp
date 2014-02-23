#include "RoundObjectWithMass.h"

RoundObjectWithMass::RoundObjectWithMass(const char* pName, const double pMass, double pRadius, double x, double y, double z) : ObjectWithMass(pName, pMass, x, y, z)
{
  radius=pRadius;
}

double RoundObjectWithMass::getRadius() const
{
  return this->radius;
}

std::ostream& operator<<(std::ostream &strm, const RoundObjectWithMass &a)
{
  return strm << "Object: " << a.getName() << " Mass: " << a.getMass() << " Radius: " << a.getRadius() << " Pos: " << a.getPosition();
}
