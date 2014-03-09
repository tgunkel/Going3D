#include "Tile.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>


Tile::Tile(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight) : upperLeft(pUpperLeft), upperRight(pUpperRight), lowerLeft(pLowerLeft), lowerRight(pLowerRight)
{
  zoom_upper_left=NULL;
  zoom_upper_right=NULL;
  zoom_lower_left=NULL;
  zoom_lower_right=NULL;
}

void Tile::FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const
{
  if(zoom_upper_left!=NULL && zoom_upper_right!=NULL && zoom_lower_left!=NULL && zoom_lower_right!=NULL)
    {
      zoom_upper_left ->FIXME_paint(pZoomX, pZoomY, pZoomZ, pShift);
      zoom_upper_right->FIXME_paint(pZoomX, pZoomY, pZoomZ, pShift);
      zoom_lower_left ->FIXME_paint(pZoomX, pZoomY, pZoomZ, pShift);
      zoom_lower_right->FIXME_paint(pZoomX, pZoomY, pZoomZ, pShift);
    }
  else
    {
      Vector3D ul=this->upperLeft.get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);
      Vector3D ur=this->upperRight.get3DPoint4PlanePane(pZoomX, pZoomY, pZoomZ, pShift);
      Vector3D ll=this->lowerLeft.get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);
      Vector3D lr=this->lowerRight.get3DPoint4PlanePane(pZoomX, pZoomY, pZoomZ, pShift);

      std::cout << "Triangles: " << ul << " " << ur << " " << ll << " " << lr << std::endl;

      glBegin(GL_TRIANGLES);
      glColor3f(1.0, 1.0, 0.0);
      glVertex3f(ul.getX(), ul.getY(), ul.getZ());
      glVertex3f(ur.getX(), ur.getY(), ur.getZ());
      glVertex3f(ll.getX(), ll.getY(), ll.getZ());
      glEnd();
      
      glBegin(GL_TRIANGLES);
      glColor3f(1.0, 0.0, 0.5);
      glVertex3f(ur.getX(), ur.getY(), ur.getZ());
      glVertex3f(ll.getX(), ll.getY(), ll.getZ());
      glVertex3f(lr.getX(), lr.getY(), lr.getZ());
      glEnd();
    }
}
