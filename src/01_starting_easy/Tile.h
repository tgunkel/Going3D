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
  // constructor
  Tile(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight);

  // split the tile in 4 smaller ones and add them as childs of us
  void split(const unsigned int split_x, const unsigned int split_y);

  // debug method to paint us
  void FIXME_paint(const unsigned int pMaxX, const unsigned int pMaxY) const;

 protected:

 private:
  PlatteCarrePoint upperLeft, upperRight, lowerLeft, lowerRight;
  Tile* zoom_upper_left;
  Tile* zoom_upper_right;
  Tile* zoom_lower_left;
  Tile* zoom_lower_right;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const Vector3D &a);

#endif
