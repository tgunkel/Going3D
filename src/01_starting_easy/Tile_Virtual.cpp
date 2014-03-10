#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "Tile_Virtual.h"

Tile_Virtual::Tile_Virtual(Tile* pUpper_left, Tile* pUpper_right, Tile* pLower_left, Tile* pLower_right)
{
  this->zoom_upper_left=pUpper_left;
  this->zoom_upper_right=pUpper_right;
  this->zoom_lower_left=pLower_left;
  this->zoom_lower_right=pLower_right;
}

PlatteCarrePoint Tile_Virtual::getUpperLeft() const
{
  return this->zoom_upper_left->getUpperLeft();
}

PlatteCarrePoint Tile_Virtual::getUpperRight() const
{
  return this->zoom_upper_right->getUpperRight();
}

PlatteCarrePoint Tile_Virtual::getLowerRight() const
{
  return this->zoom_lower_right->getLowerRight();
}

PlatteCarrePoint Tile_Virtual::getLowerLeft() const
{
  return this->zoom_lower_left->getLowerLeft();

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
