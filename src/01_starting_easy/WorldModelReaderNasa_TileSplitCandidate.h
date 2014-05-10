#ifndef _WorldModelReaderNasa_TileSplitCandidate_h_
#define _WorldModelReaderNasa_TileSplitCandidate_h_

#include <math.h>
#include <iostream>
#include "PlatteCarrePoint.h"
#include "Tile_Real.h"

/* 
   We represent the world with tiles. For each tile we calculate the maximum error
   you have when you use the tile instead of the real data points within the area
   of the tile.
   This class represents a tile and its maximum error. You can sort objects of this
   class so it is easy to find the tile with the biggest error. This is useful to
   split those tiles into smaller ones
 */
class WorldModelReaderNasa_TileSplitCandidate
{
 public:
  // constructor
  WorldModelReaderNasa_TileSplitCandidate(Tile_Real* pTile, double pMaxError, PlatteCarrePoint pMaxErrorPoint);

  Tile_Real*       getTile()          const;
  double           getMaxError()      const;
  PlatteCarrePoint getMaxErrorPoint() const;

  // get a value for the size of the tile
  double           getTileSize()         const;

  bool operator    <(const WorldModelReaderNasa_TileSplitCandidate& pOther) const;

 private:
  Tile_Real* tile;
  double maxError;
  PlatteCarrePoint maxErrorPoint;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const WorldModelReaderNasa_TileSplitCandidate &a);

#endif
