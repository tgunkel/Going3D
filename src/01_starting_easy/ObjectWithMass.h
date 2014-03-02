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

  // The current speed
  Vector3D    getSpeed() const;

  // The current speed
  Vector3D    getAcceleration() const;

  // get the acceleration through another object
  Vector3D getGravityForce(const ObjectWithMass &other) const;

  // get the acceleration through another object
  Vector3D getGravityAcceleration(const ObjectWithMass &other) const;

  // get the color of the object
  RBGColor getColor() const;

  // move object to next position
  void updatePosition(double pTimePassed);

  // for experiments, add a speed value
  void addSpeedFromOutside(Vector3D pSpeed);

  // for experiments, add a speed value
  void setAccelerationFromOutside(Vector3D pAcceleration);

  // http://en.wikipedia.org/wiki/Gravitational_constant
  const static double GRAVITYCONST=.0000000000667384;

 private:
  const char* name;
  double mass;
  Vector3D position;
  RBGColor color;
  Vector3D speed;
  Vector3D acceleration;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const ObjectWithMass &a);

#endif
