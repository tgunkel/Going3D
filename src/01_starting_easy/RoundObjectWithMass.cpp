#include "RoundObjectWithMass.h"

RoundObjectWithMass::RoundObjectWithMass(const char* pName, const double pMass, const double pRadius, const Vector3D pPos, const RBGColor pColor) : ObjectWithMass(pName, pMass, pPos, pColor)
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
