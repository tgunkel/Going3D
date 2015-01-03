#include "Tile.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

Tile::Tile(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight) : 
  upperLeft(pUpperLeft), 
  upperRight(pUpperRight), 
  lowerLeft(pLowerLeft), 
  lowerRight(pLowerRight)
{
  // left must be left of right
  assert(pUpperLeft.getPcpX()<=pUpperRight.getPcpX());
  assert(pLowerLeft.getPcpX()<=pLowerRight.getPcpX());

  // up has smaller values than down
  assert(pUpperLeft.getPcpY() <=pLowerLeft.getPcpY());
  assert(pUpperRight.getPcpY()<=pLowerRight.getPcpY());

  // the rest must be equal
  assert(pUpperLeft.getPcpY() ==pUpperRight.getPcpY());
  assert(pLowerLeft.getPcpY() ==pLowerRight.getPcpY());
  assert(pUpperLeft.getPcpX() ==pLowerLeft.getPcpX());
  assert(pUpperRight.getPcpX()==pUpperRight.getPcpX());
}

void Tile::FIXME_paintTriangle(const PlatteCarrePoint* p1, const PlatteCarrePoint* p2, const PlatteCarrePoint* p3, const short pColor) const
{
  assert(pColor>=0 && pColor <=7);

  /*
  std::cout << "P1 " << *p1 << std::endl;
  std::cout << "P2 " << *p2 << std::endl;
  std::cout << "P3 " << *p3 << std::endl;
  */

  Vector3D v1=p1->getPointIn3D();
  Vector3D v2=p2->getPointIn3D();
  Vector3D v3=p3->getPointIn3D();

  glBegin(GL_TRIANGLES);
  switch(pColor)
    {
    case 0:
      glColor3f(1.0, 0.0, 0.0);
      break;
    case 1:
      glColor3f(0.8, 0.0, 0.0);
      break;

    case 2:
      glColor3f(0.0, 1.0, 0.0);
      break;
    case 3:
      glColor3f(0.0, 0.8, 0.0);
      break;

    case 4:
      glColor3f(0.0, 0.0, 1.0);
      break;
    case 5:
      glColor3f(0.0, 0.0, 0.8);
      break;

    case 6:
      glColor3f(1.0, 1.0, 0.0);
      break;
    case 7:
      glColor3f(0.8, 0.8, 0.0);
      break;

    default:
      glColor3f(0.5, 0.5, 0.5);
      break;
    }
  glVertex3f(v1.getX(), v1.getY(), -v1.getZ()/1.0);
  glVertex3f(v2.getX(), v2.getY(), -v2.getZ()/1.0);
  glVertex3f(v3.getX(), v3.getY(), -v3.getZ()/1.0);
  glEnd();
}

void Tile::FIXME_paint() const
{
  // std::cout << "Paint " << *this << std::endl;

  int colora;
  int colorb;

  if(this->isWater())
    {
      colora=4;
      colorb=5;
    }
  else
    {
      colora=2;
      colorb=3;
    }

  this->FIXME_paintTriangle(&this->getLowerLeft(), &this->getUpperLeft(),  &this->getUpperRight(), colora);
  this->FIXME_paintTriangle(&this->getLowerLeft(), &this->getLowerRight(), &this->getUpperRight(), colorb);
}

const PlatteCarrePoint& Tile::getUpperLeft() const
{
  return this->upperLeft;
}

const PlatteCarrePoint& Tile::getUpperRight() const
{
  return this->upperRight;
}

const PlatteCarrePoint& Tile::getLowerRight() const
{
  return this->lowerRight;
}

const PlatteCarrePoint& Tile::getLowerLeft() const
{
  return this->lowerLeft;
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

bool Tile::isWater() const
{
  // only if all are water we are a water tile
  return this->getUpperRight().isWater() && this->getUpperLeft().isWater() && this->getLowerRight().isWater() && this->getLowerLeft().isWater();
}

std::ostream& operator<<(std::ostream &strm, const Tile &a)
{
  return strm << "( UL:" << a.getUpperLeft() << "  LL: " << a.getLowerLeft() << " UR:" << a.getUpperRight() << "  LR:" << a.getLowerRight() << " Size: " << a.getTileSize() <<")";
}


