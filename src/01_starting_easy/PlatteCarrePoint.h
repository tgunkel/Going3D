#ifndef _PlatteCarrePoint_h_
#define _PlatteCarrePoint_h_

#include <math.h>
#include <iostream>

#include "Vector3D.h"

/* 
   The represents a point on a sphere with an Equirectangular Projection
   See http://en.wikipedia.org/wiki/Equirectangular_projection

   We have the following representations of ourself:
   - a x/y point in a 2D world, like on a 2D map, a Platte Carre Point
   - longtitude / latitude
   - a 3D point on a 3D sphere
   
 */
class PlatteCarrePoint
{
 public:
  /*
   Constructor for a x/y point in a 2D world with an extra height.
  */
  PlatteCarrePoint(const unsigned int pPcpX, const unsigned int pPcpY, const short pPcpHeight, const unsigned int pMaxPcpX, const unsigned intpMaxPcpY, const unsigned int pSphereRadius);

  // get the column in the row where this point lies
  unsigned int getPcpX() const;

  // get the row where this point lies
  unsigned int getPcpY() const;

  // get the height value of this point in column / row
  short getPcpHeight() const;

  // Longtitude
  double getLongtitude() const;

  // Latitude
  double getLatitude() const;

  // this point as a 3D point on a sphere
  Vector3D getPointIn3D() const;

  // is the point on the water level?
  bool isWater() const;

  // override the == operator
  bool operator==(const PlatteCarrePoint& pOther) const;

  // override the < operator
  bool operator <(const PlatteCarrePoint& pOther) const;

 protected:
  // calculate the latitude for the 2D x or y values
  double getLatitude4Pcp(const unsigned int pValue, const unsigned int pMaxValue) const;

  // calculate the latitude for the 2D x or y values
  double getLongtitude4Pcp(const unsigned int pValue, const unsigned int pMaxValue) const;

  // get the 3D point on a sphere
  Vector3D get3DPoint(const double pLongtitude, const double pLatitude, const unsigned int pSphereRadius, const short pPcpHeight) const;

 private:
  // this is a representation in 2D like in a 2D map with x,y and a height value for mountains
  const unsigned int pcpX, pcpY;
  const short        pcpHeight;

  // the radius of the sphere we are living on
  const unsigned int sphereRadius;

  // this is a representation in 3D with 2 angles
  const double       longtitude, latitude;

  // this is a representation in 3D with a x/y/z point
  const Vector3D     pointIn3D;

  // override the << operator
  friend std::ostream& operator<<(std::ostream &strm, const PlatteCarrePoint &a);

};

#endif
