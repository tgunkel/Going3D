#include "SystemWithObjects.h"

SystemWithObjects::SystemWithObjects(const char* pName)
{
  this->name=pName;
}

void SystemWithObjects::addNewObject(ObjectWithMass* pObject)
{
  this->objects.push_back(pObject);
}

void SystemWithObjects::updateSystem(const int pTimePassed)
{
  // for each object ...
  for(unsigned int i=0; i < this->objects.size(); i++)
    {
      // ... get the sum of all the accelerations it gets from ...
      Vector3D totalAcceleration=Vector3D::ZERO_ZERO_ZERO();

      // ... the other objects ...
      for(unsigned int k=0; k < this->objects.size(); k++)
        {
          // .. but not from itselt
          if(i!=k)
            {
              Vector3D x=this->objects[i]->getGravityAcceleration(*this->objects[k]);
              totalAcceleration=totalAcceleration.add(x);
            }
        }
      this->objects[i]->setAccelerationFromOutside(totalAcceleration);
      this->objects[i]->updatePosition(pTimePassed);
      std::cout << *this->objects[i] << std::endl;
    }

  /*
  earth.updatePosition(100.0);
  earth_moon.updatePosition(100.0);
  sun.updatePosition(100.0);
  */
}

std::ostream& operator<<(std::ostream &strm, const SystemWithObjects &a)
{
  strm << "System: " << a.name << " " << std::endl;

  for(unsigned int i=0; i < a.objects.size(); i++)
    {
      strm << *a.objects[i] << std::endl;
    }
  return strm;
}
