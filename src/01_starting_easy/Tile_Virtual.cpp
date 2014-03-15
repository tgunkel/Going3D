#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "Tile_Virtual.h"

Tile_Virtual::Tile_Virtual(Tile* pUpper_left, Tile* pUpper_right, Tile* pLower_left, Tile* pLower_right) : Tile()
{
  this->zoom_upper_left=pUpper_left;
  this->zoom_upper_right=pUpper_right;
  this->zoom_lower_left=pLower_left;
  this->zoom_lower_right=pLower_right;
  
  this->zoom_upper_left->setParent(this);
  this->zoom_upper_right->setParent(this);
  this->zoom_lower_left->setParent(this);
  this->zoom_lower_right->setParent(this);
}

const PlatteCarrePoint& Tile_Virtual::getUpperLeft() const
{
  return this->zoom_upper_left->getUpperLeft();
}

const PlatteCarrePoint& Tile_Virtual::getUpperRight() const
{
  return this->zoom_upper_right->getUpperRight();
}

const PlatteCarrePoint& Tile_Virtual::getLowerRight() const
{
  return this->zoom_lower_right->getLowerRight();
}

const PlatteCarrePoint& Tile_Virtual::getLowerLeft() const
{
  return this->zoom_lower_left->getLowerLeft();
}

Tile* Tile_Virtual::getUpperLeftTile() const
{
  return this->zoom_upper_left;
}

Tile* Tile_Virtual::getUpperRightTile() const
{
  return this->zoom_upper_right;
}

Tile* Tile_Virtual::getLowerRightTile() const
{
  return this->zoom_lower_right;
}

Tile* Tile_Virtual::getLowerLeftTile() const
{
  return this->zoom_lower_left;
}

void Tile_Virtual::replaceTile(Tile * pNewTile, Tile * pOldTile)
{
  if(this->zoom_upper_left==pOldTile) this->zoom_upper_left=pNewTile;
  else if(this->zoom_upper_right==pOldTile) this->zoom_upper_right=pNewTile;
  else if(this->zoom_lower_left==pOldTile) this->zoom_lower_left=pNewTile;
  else if(this->zoom_lower_right==pOldTile) this->zoom_lower_right=pNewTile;
  else
    {
      std::cout << "Error: Replace failed" << std::endl << pNewTile << *pNewTile << " with " << std::endl << pOldTile << *pOldTile << std::endl;
      throw "Replace failed";
    }
}

void Tile_Virtual::FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const
{
  if(zoom_upper_left!=NULL && zoom_upper_right!=NULL && zoom_lower_left!=NULL && zoom_lower_right!=NULL)
    {
      zoom_upper_left ->FIXME_paint(pZoomX, pZoomY, pZoomZ, pShift);
      zoom_upper_right->FIXME_paint(pZoomX, pZoomY, pZoomZ, pShift);
      zoom_lower_left ->FIXME_paint(pZoomX, pZoomY, pZoomZ, pShift);
      zoom_lower_right->FIXME_paint(pZoomX, pZoomY, pZoomZ, pShift);
    }
}


void Tile_Virtual::getAllPointsOnAxis(std::set<PlatteCarrePoint> pResult, bool pXAxis, PlatteCarrePoint& pFrom, PlatteCarrePoint& pTo) const
{
  if(pXAxis)
    {
      assert(pFrom.getPcpY()==pTo.getPcpY());

      // the x axis is totaly left of us
      if(this->getUpperLeft().getPcpY()>pTo.getPcpY())
        return;

      // the x axis is totaly left of us
      if(this->getLowerLeft().getPcpY()<pTo.getPcpY())
        return;
      
      // the range is totaly above us
      if(this->getUpperLeft().getPcpX()>pTo.getPcpX())
        return;

      // the range is totaly below us us
      if(this->getUpperRight().getPcpX()<pFrom.getPcpX())
        return;
    }
  else
    {
      assert(pFrom.getPcpX()==pTo.getPcpX());

      // the y axis is totaly above us
      if(this->getUpperLeft().getPcpX()>pTo.getPcpX())
        return;

      // the Y axis is totaly below of us
      if(this->getUpperRight().getPcpX()<pTo.getPcpX())
        return;
      
      // the range is totaly left of us
      if(this->getUpperLeft().getPcpY()>pTo.getPcpY())
        return;

      // the range is totaly below us us
      if(this->getLowerLeft().getPcpY()<pFrom.getPcpY())
        return;
    }

  // the axis and the points are within us. Ask our children about it
  zoom_upper_left ->getAllPointsOnAxis(pResult, pXAxis, pFrom, pTo);
  zoom_upper_right->getAllPointsOnAxis(pResult, pXAxis, pFrom, pTo);
  zoom_lower_left ->getAllPointsOnAxis(pResult, pXAxis, pFrom, pTo);
  zoom_lower_right->getAllPointsOnAxis(pResult, pXAxis, pFrom, pTo);
}
