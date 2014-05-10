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

double WorldModelReaderNasa_TileSplitCandidate::getTileSize() const
{
  double x=(double) (this->getTile()->getUpperRight().getPcpX()-this->getTile()->getUpperLeft().getPcpX())/1000.0;
  double y=(double) (this->getTile()->getLowerLeft().getPcpY() -this->getTile()->getUpperLeft().getPcpY())/1000.0;
  return (x*y);
}

std::ostream& operator<<(std::ostream &strm, const WorldModelReaderNasa_TileSplitCandidate &a)
{  
  return strm << "TileSplitCandidate: tilesize: " << a.getTileSize() << " error: " << a.getMaxError() << " for " << *a.getTile() << " at " << a.getMaxErrorPoint();
}

bool WorldModelReaderNasa_TileSplitCandidate::operator <(const WorldModelReaderNasa_TileSplitCandidate& pOther) const
{
  if(this->getTileSize()<pOther.getTileSize()) return true;
  else
    return this->getMaxError()<pOther.getMaxError();
}
