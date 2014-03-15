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

  // get the column in the row where this point lies
  unsigned int getPcpX() const;

  // get the row where this point lies
  unsigned int getPcpY() const;

  // get the value of this point in column / row
  short getHeight() const;

  // is this point between to other two on the X axis (Y  axis)
  bool isBetween(bool pXAxis, PlatteCarrePoint& pFrom, PlatteCarrePoint& pTo) const;

  bool operator==(const PlatteCarrePoint& pOther) const;

  bool operator <(const PlatteCarrePoint& pOther) const;

 private:
  unsigned int x, y;
  short height;

  // override the << operator
  friend std::ostream& operator<<(std::ostream &strm, const PlatteCarrePoint &a);

};


#endif
