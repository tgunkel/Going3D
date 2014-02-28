#include "ObjectWithMass.h"

ObjectWithMass::ObjectWithMass(const char* pName, const double pMass, const Vector3D pPos, RBGColor pColor) : position(pPos), color(pColor), speed(Vector3D::ZERO_ZERO_ZERO()), acceleration(Vector3D::ZERO_ZERO_ZERO())
{
  this->name=pName;
  this->mass=pMass;
  this->color=pColor;
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

Vector3D ObjectWithMass::getSpeed() const
{
  return this->speed;
}

RBGColor ObjectWithMass::getColor() const
{
  return this->color;
}

Vector3D ObjectWithMass::getDistance(const ObjectWithMass &other) const
{
  return this->position.sub(other.position);
}

void ObjectWithMass::addSpeedFromOutside(Vector3D pSpeed)
{
  this->speed=this->speed.add(pSpeed);
}

void ObjectWithMass::setAccelerationFromOutside(Vector3D pAcceleration)
{
  this->acceleration=pAcceleration;
}

void ObjectWithMass::updatePosition(double pTimePassed)
{
  Vector3D movement_change=this->acceleration.mult(pTimePassed);
  this->speed=this->speed.add(movement_change);
  Vector3D movement=this->getSpeed().mult(pTimePassed);
  this->position=this->position.add(movement);
}


double ObjectWithMass::getGravityAcceleration(const ObjectWithMass &other) const
{
  Vector3D wayToOther=getDistance(other);
  double distance=wayToOther.length();
  return GRAVITYCONST*other.getMass()/distance/distance;
}

std::ostream& operator<<(std::ostream &strm, const ObjectWithMass &a)
{
  return strm << "Object: " << a.getName() << " Mass: " << a.getMass() << " Pos: " << a.getPosition() << " Speed: " << a.getSpeed();
}
