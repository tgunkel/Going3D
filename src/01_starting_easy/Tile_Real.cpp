#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "Tile_Real.h"

Tile_Real::Tile_Real(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight) : upperLeft(pUpperLeft), upperRight(pUpperRight), lowerLeft(pLowerLeft), lowerRight(pLowerRight)
{
  
}

void Tile_Real::FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const
{
  Vector3D ul=this->upperLeft.get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);
  Vector3D ur=this->upperRight.get3DPoint4PlanePane(pZoomX, pZoomY, pZoomZ, pShift);
  Vector3D ll=this->lowerLeft.get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);
  Vector3D lr=this->lowerRight.get3DPoint4PlanePane(pZoomX, pZoomY, pZoomZ, pShift);
  
  //std::cout << "Triangles: " << ul << " " << ur << " " << ll << " " << lr << std::endl;
  
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
