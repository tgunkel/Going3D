#include "WorldModelReaderNasa_TileSplitCandidate.h"

WorldModelReaderNasa_TileSplitCandidate::WorldModelReaderNasa_TileSplitCandidate(Tile_Real* pTile, double pMaxError, PlatteCarrePoint pMaxErrorPoint) :
  tile(pTile), maxError(pMaxError), maxErrorPoint(pMaxErrorPoint)
{

};

Tile_Real* WorldModelReaderNasa_TileSplitCandidate::getTile() const
{
  return this->tile;
}

double WorldModelReaderNasa_TileSplitCandidate::getMaxError() const
{
  return this->maxError;
}

PlatteCarrePoint WorldModelReaderNasa_TileSplitCandidate::getMaxErrorPoint() const
{
  return this->maxErrorPoint;
}

std::ostream& operator<<(std::ostream &strm, const WorldModelReaderNasa_TileSplitCandidate &a)
{  
  return strm << "TileSplitCandidate: tilesize: " << a.getTile()->getTileSize() << " error: " << a.getMaxError() << " for " << *a.getTile() << " at " << a.getMaxErrorPoint();
}

bool WorldModelReaderNasa_TileSplitCandidate::operator <(const WorldModelReaderNasa_TileSplitCandidate& pOther) const
{
  if(this->getTile()->getTileSize()<pOther.getTile()->getTileSize())
    {
      return true;
    }
  else
    {
      return false;
      //return this->getMaxError()<pOther.getMaxError();
    }
}
