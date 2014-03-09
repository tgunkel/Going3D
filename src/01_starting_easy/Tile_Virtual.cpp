#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "Tile_Virtual.h"

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
