#ifndef _Tile_Real_h_
#define _Tile_Real_h_

#include <iostream>
#include <list>
#include "PlatteCarrePoint.h"
#include "Tile.h"
#include "Tile_Virtual.h"

/* Class to represent a tile in a 3D world, with acutal coordinates, no more childeren

 */
class Tile_Real : public Tile
{
 public:
  // constructor
  Tile_Real(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight);

  // debug method to paint us
  void FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const;

  // get the upper left point
  PlatteCarrePoint getUpperLeft() const;

  // get the upper right point
  PlatteCarrePoint getUpperRight() const;

  // get the lower right point
  PlatteCarrePoint getLowerRight() const;

  // get the lower left point
  PlatteCarrePoint getLowerLeft() const;

  // estimate the value at this position based on the corner values we know
  PlatteCarrePoint getEstimated(PlatteCarrePoint pPoint) const;

 protected:

 private:
  PlatteCarrePoint upperLeft, upperRight, lowerLeft, lowerRight;
  Tile_Real * parent;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const Tile_Real &a);

#endif
