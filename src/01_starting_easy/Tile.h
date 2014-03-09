#ifndef _Tile_h_
#define _Tile_h_

#include <iostream>
#include <list>
#include "PlatteCarrePoint.h"

class Tile;

/* Class to represent a tile in a 3D world

 */
class Tile
{
 public:
  // debug method to paint us
  virtual void FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const=0;

 protected:

 private:
};

#endif
