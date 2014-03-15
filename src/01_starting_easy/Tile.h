#ifndef _Tile_h_
#define _Tile_h_

#include <iostream>
#include <list>
#include <set>
#include <cassert>
#include "PlatteCarrePoint.h"

class Tile_Virtual;

/* Class to represent a tile in a 3D world

 */
class Tile
{
 public:
  // constructor
  Tile();

  // get the upper left point
  virtual const PlatteCarrePoint& getUpperLeft() const=0;

  // get the upper right point
  virtual const PlatteCarrePoint& getUpperRight() const=0;
  
  // get the lower right point
  virtual const PlatteCarrePoint& getLowerRight() const=0;

  // get the lower left point
  virtual const PlatteCarrePoint& getLowerLeft() const=0;

  // get the parent Tile for you (must be a virtual one, real ones have no children as they are real
  Tile_Virtual* getParent() const;

  // the the parent of all parents
  const Tile* getSuperParent() const;

  // set the parent Tile for this Tile
  void setParent(Tile_Virtual* pParent);

  // calculate an estimated value for a point within this tile
  double getEstimatedValue(unsigned int x, unsigned int y) const;

  // you have two points, pFrom and pTo, which are both on the same axis (see pXaxis) and you want to find all point which are on that axis and between both point
  virtual void getAllPointsOnAxis(std::set<PlatteCarrePoint>& pResult, bool pXAxis, const PlatteCarrePoint& pFrom, const PlatteCarrePoint& pTo) const=0;

  // debug method to paint us
  virtual void FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const=0;

  // is this a real Tile or a virtual one
  virtual bool isReal() const=0;

 protected:

 private:
  Tile_Virtual * parent;

  // override the << operator
  friend std::ostream& operator<<(std::ostream &strm, const Tile &a);

};

#endif
