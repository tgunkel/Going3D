#ifndef _PlatteCarrePoint_h_
#define _PlatteCarrePoint_h_

#include <math.h>
#include <iostream>

#include "Vector3D.h"

/* This defines a 2D point with a height. 
   See http://en.wikipedia.org/wiki/Equirectangular_projection
 */
class PlatteCarrePoint
{
 public:
  // constructor
  PlatteCarrePoint(const unsigned int pX, const unsigned int pY, const short pHeight);

  Vector3D get3DPoint4PlanePane(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const;

  short getHeight();

 private:
  unsigned int x, y;
  short height;

  // override the << operator
  friend std::ostream& operator<<(std::ostream &strm, const PlatteCarrePoint &a);

};


#endif
