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
  virtual PlatteCarrePoint getUpperLeft() const=0;

  virtual PlatteCarrePoint getUpperRight() const=0;
  
  virtual PlatteCarrePoint getLowerRight() const=0;

  virtual PlatteCarrePoint getLowerLeft() const=0;

  // debug method to paint us
  virtual void FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const=0;

 protected:

 private:
  // override the << operator
  friend std::ostream& operator<<(std::ostream &strm, const Tile &a);

};

#endif
