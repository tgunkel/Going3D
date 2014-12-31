#include "Tile.h"
#include "Tile_Virtual.h"

Tile::Tile()
{
  this->parent=NULL;
}

Tile_Virtual* Tile::getParent() const
{
  return this->parent;
}

const Tile* Tile::getSuperParent() const
{
  if(this->getParent()==NULL)
    {
      return this;
    }
  else
    {
      return this->getParent()->getSuperParent();
    }
}

void Tile::setParent(Tile_Virtual* pParent)
{
  this->parent=pParent;
}

double Tile::getEstimatedValue(const unsigned int x, const unsigned int y) const
{
  assert(x>=getUpperLeft().getPcpX());
  assert(x<=getUpperRight().getPcpX());
  assert(y>=getUpperLeft().getPcpY());
  assert(y<=getLowerLeft().getPcpY());

  // calculate to what percentage your point is to the right or down side of this Tile
  double rightInPercent=((double)x-(double)getUpperLeft().getPcpX())/((double)getUpperRight().getPcpX()-(double)getUpperLeft().getPcpX());
  double downInPercent= ((double)y-(double)getUpperLeft().getPcpY())/((double)getLowerLeft().getPcpY()-(double)getUpperLeft().getPcpY());

  assert(rightInPercent>=0 && rightInPercent<=1);
  assert(downInPercent>=0  && downInPercent<=1);

  // find a fair x value between upper left and upper right
  double upperRow=(1.0-rightInPercent)*(double)getUpperLeft().getHeight()+(rightInPercent)*(double)getUpperRight().getHeight();

  // find a fair x value between lower left and lower right
  double lowerRow=(1.0-rightInPercent)*(double)getLowerLeft().getHeight()+(rightInPercent)*(double)getLowerRight().getHeight();

  /*
  std::cout << "UPPER: " << getUpperLeft().getHeight() << ", " << getUpperRight().getHeight() << ": " << upperRow << std::endl;
  std::cout << "LOWER: " << getLowerLeft().getHeight() << ", " << getLowerRight().getHeight() << ": " << lowerRow << std::endl;
  */

  assert(upperRow+0.1>=std::min((double)getUpperLeft().getHeight(),  (double)getUpperRight().getHeight()));
  assert(upperRow-0.1<=std::max((double)getUpperLeft().getHeight(),  (double)getUpperRight().getHeight()));
  assert(lowerRow+0.1>=std::min((double)getLowerLeft().getHeight(),  (double)getLowerRight().getHeight()));
  assert(lowerRow-0.1<=std::max((double)getLowerLeft().getHeight(),  (double)getLowerRight().getHeight()));

  // now find a fair y value between the both fair x values
  double res=(1.0-downInPercent)*upperRow+(downInPercent)*lowerRow;

  //std::cout << "Estimated value: for " << x << "/" << y << " right: " << rightInPercent << " down: " << downInPercent << " res: " << res << std::endl;

  return res;
}

double Tile::getTileSize() const
{
  double x=(double) (this->getUpperRight().getPcpX()-this->getUpperLeft().getPcpX());
  double y=(double) (this->getLowerLeft(). getPcpY()-this->getUpperLeft().getPcpY());
  assert(x>0);
  assert(y>0);
  double res=x*y;
  assert(res>0);
  return res;
}


std::ostream& operator<<(std::ostream &strm, const Tile &a)
{
  return strm << "( UL:" << a.getUpperLeft() << "  LL: " << a.getLowerLeft() << " UR:" << a.getUpperRight() << "  LR:" << a.getLowerRight() << " Size: " << a.getTileSize() <<")";
}


