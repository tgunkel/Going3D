#ifndef _Tile_Virtual_h_
#define _Tile_Virtual_h_

#include <iostream>
#include <list>
#include "PlatteCarrePoint.h"

#include "Tile.h"

/* Class to represent a tile in a 3D world

 */
class Tile_Virtual : public Tile
{
 public:
  // constructor
  Tile_Virtual(Tile* pUpper_left, Tile* pUpper_right, Tile* pLower_left, Tile* pLower_right);

  PlatteCarrePoint getUpperLeft() const;

  PlatteCarrePoint getUpperRight() const;

  PlatteCarrePoint getLowerRight() const;

  PlatteCarrePoint getLowerLeft() const;

  Tile* getUpperLeftTile() const;

  Tile* getUpperRightTile() const;

  Tile* getLowerRightTile() const;

  Tile* getLowerLeftTile() const;

  void replaceTile(Tile * pNewTile, Tile * pOldTile);

  // debug method to paint us
  void FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const;

 protected:

 private:
  Tile* zoom_upper_left;
  Tile* zoom_upper_right;
  Tile* zoom_lower_left;
  Tile* zoom_lower_right;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const Tile_Virtual &a);

#endif
