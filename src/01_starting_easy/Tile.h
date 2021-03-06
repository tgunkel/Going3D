#ifndef _Tile_h_
#define _Tile_h_

#include <iostream>
#include <list>
#include <set>
#include <cassert>
#include "PlatteCarrePoint.h"
#include <algorithm> // min

/* Class to represent a square in a 3D world
 */
class Tile
{
 public:
  // constructor
  Tile(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight);

  // get the upper left point
  const PlatteCarrePoint& getUpperLeft() const;

  // get the upper right point
  const PlatteCarrePoint& getUpperRight() const;

  // get the lower right point
  const PlatteCarrePoint& getLowerRight() const;

  // get the lower left point
  const PlatteCarrePoint& getLowerLeft() const;

  // debug method to paint us
  void FIXME_paint() const;

  void FIXME_paintTriangle(const PlatteCarrePoint* p1, const PlatteCarrePoint* p2, const PlatteCarrePoint* p3, const short pColor) const;

  // get size of the tile
  double           getTileSize()         const;

  // is the tile a water only tile?
  bool isWater() const;

  // is the tile a mountain tile?
  bool isMountain() const;

 protected:

 private:
  PlatteCarrePoint upperLeft, upperRight, lowerLeft, lowerRight;

  // override the << operator
  friend std::ostream& operator<<(std::ostream &strm, const Tile &a);

};

#endif
