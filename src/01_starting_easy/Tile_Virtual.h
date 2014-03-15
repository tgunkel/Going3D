#ifndef _Tile_Virtual_h_
#define _Tile_Virtual_h_

#include <iostream>
#include <list>
#include <set>
#include "PlatteCarrePoint.h"
#include "Tile.h"

/* Class to represent a tile in a 3D world

 */
class Tile_Virtual : public Tile
{
 public:
  // constructor
  Tile_Virtual(Tile* pUpper_left, Tile* pUpper_right, Tile* pLower_left, Tile* pLower_right);

  // get the upper left point (by asking our children)
  const PlatteCarrePoint& getUpperLeft() const;

  // get the upper right point (by asking our children)
  const PlatteCarrePoint& getUpperRight() const;

  // get the lower right point (by asking our children)
  const PlatteCarrePoint& getLowerRight() const;

  // get the lower left point (by asking our children)
  const PlatteCarrePoint& getLowerLeft() const;

  // get the upper left tile
  Tile* getUpperLeftTile() const;

  // get the upper right tile
  Tile* getUpperRightTile() const;

  // get the lower right tile
  Tile* getLowerRightTile() const;

  // get the lower left tile
  Tile* getLowerLeftTile() const;

  // replace this tile with another one
  void replaceTile(Tile * pNewTile, Tile * pOldTile);

  // you have two points, pFrom and pTo, which are both on the same axis (see pXaxis) and you want to find all point which are on that axis and between both point
  void getAllPointsOnAxis(std::set<PlatteCarrePoint> pResult, bool pXAxis, const PlatteCarrePoint& pFrom, const PlatteCarrePoint& pTo) const;

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
