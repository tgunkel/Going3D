#ifndef _SystemWithObjects_h_
#define _SystemWithObjects_h_

#include <vector>
#include "ObjectWithMass.h"
#include "Vector3D.h"

/* Class to represent a system full of objects in a 3D world

 */
class SystemWithObjects
{
 public:
  // constructor
  SystemWithObjects(const char* pName);

  // add a new object to the system
  void addNewObject(ObjectWithMass* pObject);

  // some time passed change what changes in such a system
  void updateSystem(const int pTimePassed);

  // override the << operator
  friend std::ostream& operator<<(std::ostream &strm, const SystemWithObjects &a);

 private:
  const char* name;
  long timepassed_seconds;
  std::vector<ObjectWithMass*> objects;
};


#endif
