#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "Tile_Real.h"

Tile_Real::Tile_Real(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight) : 
  Tile(),
  upperLeft(pUpperLeft), 
  upperRight(pUpperRight), 
  lowerLeft(pLowerLeft), 
  lowerRight(pLowerRight)
{

}

void Tile_Real::FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const
{
  Vector3D ul=this->upperLeft.get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);
  Vector3D ur=this->upperRight.get3DPoint4PlanePane(pZoomX, pZoomY, pZoomZ, pShift);
  Vector3D ll=this->lowerLeft.get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);
  Vector3D lr=this->lowerRight.get3DPoint4PlanePane(pZoomX, pZoomY, pZoomZ, pShift);
  
  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(ul.getX(), ul.getY(), -ul.getZ()/5.0);
  glVertex3f(ur.getX(), ur.getY(), -ur.getZ()/5.0);
  glVertex3f(ll.getX(), ll.getY(), -ll.getZ()/5.0);
  glEnd();
  
  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(ur.getX(), ur.getY(), -ur.getZ()/5.0);
  glVertex3f(ll.getX(), ll.getY(), -ll.getZ()/5.0);
  glVertex3f(lr.getX(), lr.getY(), -lr.getZ()/5.0);
  glEnd();

}

const PlatteCarrePoint& Tile_Real::getUpperLeft() const
{
  return this->upperLeft;
}

const PlatteCarrePoint& Tile_Real::getUpperRight() const
{
  return this->upperRight;
}

const PlatteCarrePoint& Tile_Real::getLowerRight() const
{
  return this->lowerRight;
}

const PlatteCarrePoint& Tile_Real::getLowerLeft() const
{
  return this->lowerLeft;
}

void Tile_Real::getAllPointsOnAxis(std::set<PlatteCarrePoint>& pResult, bool pXAxis, const PlatteCarrePoint& pFrom, const PlatteCarrePoint& pTo) const
{ 
  std::cout << "Searching in " << *this << " on X-Axis " << pXAxis << " " << pFrom << " " << pTo << std::endl;

  if(this->getUpperLeft().isBetween(pXAxis,  pFrom, pTo))
    {
      std::cout << "Hit " << this->getUpperLeft() << std::endl;      
      pResult.insert(this->getUpperLeft());
    }

  if(this->getUpperRight().isBetween(pXAxis, pFrom, pTo))
    {
      std::cout << "Hit " << this->getUpperRight() << std::endl;      
      pResult.insert(this->getUpperRight());
    }

  if(this->getLowerLeft().isBetween(pXAxis,  pFrom, pTo))
    {
      std::cout << "Hit " << this->getLowerLeft() << std::endl;      
      pResult.insert(this->getLowerLeft());
    }

  if(this->getLowerRight().isBetween(pXAxis, pFrom, pTo))
    {
      std::cout << "Hit " << this->getLowerRight() << std::endl;      
      pResult.insert(this->getLowerRight());
    }
}

std::ostream& operator<<(std::ostream &strm, const Tile_Real &a)
{
  return strm << "Tile_Real ( UL:" << a.getUpperLeft() << "  LL: " << a.getLowerLeft() << " UR:" << a.getUpperRight() << "  LR:" << a.getLowerRight() << ")";
}
