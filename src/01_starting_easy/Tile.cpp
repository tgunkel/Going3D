#include "Tile.h"

Tile::Tile()
{
  this->parent=NULL;
}

Tile_Virtual* Tile::getParent() const
{
  return this->parent;
}

void Tile::setParent(Tile_Virtual* pParent)
{
  this->parent=pParent;
}

double Tile::getEstimatedValue(unsigned int x, unsigned int y) const
{
  // calculate to what percentage your point is to the right or down side of this Tile
  double rightInPercent=(x-getUpperLeft().getPcpX())/(getUpperRight().getPcpX()-getUpperLeft().getPcpX());
  double downInPercent= (y-getUpperLeft().getPcpY())/(getUpperLeft().getPcpY()-getLowerLeft().getPcpY());

  assert(rightInPercent>=0 && rightInPercent<=1);
  assert(downInPercent>=0  && downInPercent<=1);

  // the more your point is to one corner, the more do we count that corner in
  double lr_est=((double)getLowerRight().getHeight())*   rightInPercent *   downInPercent;
  double ul_est=((double)getUpperLeft(). getHeight())*(1-rightInPercent)*(1-downInPercent);
  double ur_est=((double)getUpperRight().getHeight())*   rightInPercent *(1-downInPercent);
  double ll_est=((double)getLowerLeft() .getHeight())*(1-rightInPercent)*   downInPercent;

  // form average
  double res=(lr_est+ul_est+ur_est+ll_est)/4.0;
  return res;
}

std::ostream& operator<<(std::ostream &strm, const Tile &a)
{
  return strm << "( UL:" << a.getUpperLeft() << "  LL: " << a.getLowerLeft() << " UR:" << a.getUpperRight() << "  LR:" << a.getLowerRight() << ")";
}
