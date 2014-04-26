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

void Tile_Real::FIXME_paintTriangle(const PlatteCarrePoint* p1, const PlatteCarrePoint* p2, const PlatteCarrePoint* p3, const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift, const short pColor) const
{
  /*
  std::cout << "P1 " << *p1 << std::endl;
  std::cout << "P2 " << *p2 << std::endl;
  std::cout << "P3 " << *p3 << std::endl;
  */

  Vector3D v1=p1->get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);
  Vector3D v2=p2->get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);
  Vector3D v3=p3->get3DPoint4PlanePane (pZoomX, pZoomY, pZoomZ, pShift);

  glBegin(GL_TRIANGLES);
  switch(pColor)
    {
    case 0:
      glColor3f(1.0, 0.0, 0.0);
      break;
    case 1:
      glColor3f(0.0, 1.0, 0.0);
      break;
    case 2:
      glColor3f(0.0, 0.0, 1.0);
      break;
    case 3:
      glColor3f(1.0, 1.0, 0.0);
      break;
    default:
      glColor3f(1.0, 0.0, 1.0);
      break;
    }
  glVertex3f(v1.getX(), v1.getY(), -v1.getZ()/1.0);
  glVertex3f(v2.getX(), v2.getY(), -v2.getZ()/1.0);
  glVertex3f(v3.getX(), v3.getY(), -v3.getZ()/1.0);
  glEnd();
}

void Tile_Real::FIXME_paint(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const
{
  // std::cout << "Paint " << *this << std::endl;

  // we want to paint this tile, which is a real tile, no virtual one

  // first we find the middle of this tile, we will us this extra point for painting
  PlatteCarrePoint center(
                          this->upperLeft.getPcpX()+(this->upperRight.getPcpX()-this->upperLeft.getPcpX())/2.0,
                          this->upperLeft.getPcpY()+ (this->lowerLeft.getPcpY() -this->upperLeft.getPcpY())/2.0,
                          (
                           (double) this->getUpperLeft().getHeight() +
                           (double) this->getUpperRight().getHeight() +
                           (double) this->getLowerLeft().getHeight() +
                           (double) this->getLowerRight().getHeight()
                           ) / 4.0
                          );

  // the center should be within the edges
  assert(center.getPcpX()>=this->upperLeft.getPcpX());
  assert(center.getPcpX()>=this->lowerLeft.getPcpX());
  assert(center.getPcpX()<=this->upperRight.getPcpX());
  assert(center.getPcpX()<=this->lowerRight.getPcpX());

  assert(center.getPcpY()>=this->upperLeft.getPcpY());
  assert(center.getPcpY()>=this->upperRight.getPcpY());
  assert(center.getPcpY()<=this->lowerLeft.getPcpY());
  assert(center.getPcpY()<=this->lowerRight.getPcpY());

  // when we paint this tile, we have to find all neighbours of us. Start at the very head
  const Tile* head=this->getSuperParent();

  // find all points we have to paint arround the center
  std::list<PlatteCarrePoint> points_all;
  {
    std::set<PlatteCarrePoint> points_up;
    head->getAllPointsOnAxis(points_up, true, this->getUpperLeft(), this->getUpperRight());
    std::list<PlatteCarrePoint> points_up_lst(points_up.begin(), points_up.end());
    assert(points_up_lst.size()>=2);
    
    std::set<PlatteCarrePoint> points_right;
    head->getAllPointsOnAxis(points_right, false, this->getUpperRight(), this->getLowerRight());
    std::list<PlatteCarrePoint> points_right_lst(points_right.begin(), points_right.end());
    assert(points_right_lst.size()>=2);
    
    std::set<PlatteCarrePoint>  points_down;
    head->getAllPointsOnAxis(points_down, true, this->getLowerLeft(), this->getLowerRight());
    std::list<PlatteCarrePoint> points_down_lst(points_down.begin(), points_down.end());
    points_down_lst.reverse();
    assert(points_down_lst.size()>=2);
    
    std::set<PlatteCarrePoint> points_left;
    head->getAllPointsOnAxis(points_left, false, this->getUpperLeft(), this->getLowerLeft());
    std::list<PlatteCarrePoint> points_left_lst(points_left.begin(), points_left.end());
    assert(points_left_lst.size()>=2);
    points_left_lst.reverse();
    
    points_all.insert(points_all.end(), points_up_lst.begin(),    points_up_lst.end());
    points_all.insert(points_all.end(), points_right_lst.begin(), points_right_lst.end());
    points_all.insert(points_all.end(), points_down_lst.begin(),  points_down_lst.end());
    points_all.insert(points_all.end(), points_left_lst.begin(),  points_left_lst.end());
  }

  PlatteCarrePoint* p1=NULL;
  PlatteCarrePoint* p2=NULL;
  PlatteCarrePoint* p3=&center;

  short color=0;
  std::list<PlatteCarrePoint>::iterator it;
  /*
  for (it = points_all.begin(); it != points_all.end(); ++it)
    {
      std::cout << "DEBUG:" << *it << std::endl;
    }
  */

  for (it = points_all.begin(); it != points_all.end(); ++it)
    {
      p1=&(*it);

      if(p2!=NULL && !(*p1==*p2))
        {
          this->FIXME_paintTriangle(p1, p2, p3, pZoomX, pZoomY, pZoomZ, pShift, color);
          color++;
          if(color>4) color=1;
        }
      p2=p1;
    }

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
  // std::cout << "Searching real in " << *this << " on X-Axis " << (pXAxis ? "true" : "false") << " " << pFrom << " " << pTo << std::endl;

  if(this->getUpperLeft().isBetween(pXAxis,  pFrom, pTo))
    {
      // std::cout << "Hit " << this->getUpperLeft() << std::endl;
      pResult.insert(this->getUpperLeft());
    }

  if(this->getUpperRight().isBetween(pXAxis, pFrom, pTo))
    {
      // std::cout << "Hit " << this->getUpperRight() << std::endl;
      pResult.insert(this->getUpperRight());
    }

  if(this->getLowerLeft().isBetween(pXAxis,  pFrom, pTo))
    {
      // std::cout << "Hit " << this->getLowerLeft() << std::endl;
      pResult.insert(this->getLowerLeft());
    }

  if(this->getLowerRight().isBetween(pXAxis, pFrom, pTo))
    {
      // std::cout << "Hit " << this->getLowerRight() << std::endl;
      pResult.insert(this->getLowerRight());
    }

  // std::cout << "Found results " << pResult.size() << std::endl;

}

bool Tile_Real::isReal() const
{
  return true;
}

std::ostream& operator<<(std::ostream &strm, const Tile_Real &a)
{
  return strm << "Tile_Real ( UL:" << a.getUpperLeft() << "  LL: " << a.getLowerLeft() << " UR:" << a.getUpperRight() << "  LR:" << a.getLowerRight() << ")";
}
