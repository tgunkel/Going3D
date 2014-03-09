#ifndef _Tile_Real_h_
#define _Tile_Real_h_

#include <iostream>
#include <list>
#include "PlatteCarrePoint.h"
#include "Tile.h"

/* Class to represent a tile in a 3D world, with acutal coordinates, no more childeren

 */
class Tile_Real : public Tile
{
 public:
  // constructor
  Tile_Real(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight);

  // debug method to paint us
  void FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const;

 protected:

 private:
  PlatteCarrePoint upperLeft, upperRight, lowerLeft, lowerRight;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const Tile_Real &a);

#endif
