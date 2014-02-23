#include "ObjectWithMass.h"

ObjectWithMass::ObjectWithMass(const char* pName, const double pMass, const double x, const double y, const double z) : position(x,y,z)
{
  this->name=pName;
  this->mass=pMass;
}

const char* ObjectWithMass::getName() const
{
  return this->name;
}

double ObjectWithMass::getMass() const
{
  return this->mass;
}

Vector3D ObjectWithMass::getPosition() const
{
  return this->position;
}

Vector3D ObjectWithMass::getDistance(const ObjectWithMass &other) const
{
  return this->position.sub(other.position);
}

double ObjectWithMass::getGravityAcceleration(const ObjectWithMass &other) const
{
  Vector3D wayToOther=getDistance(other);
  double distance=wayToOther.length();
  return GRAVITYCONST*other.getMass()/distance/distance;
}

std::ostream& operator<<(std::ostream &strm, const ObjectWithMass &a)
{
  return strm << "Object: " << a.getName() << " Mass: " << a.getMass() << " Pos: " << a.getPosition();
}
