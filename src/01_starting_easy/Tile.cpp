#include "Tile.h"

#include <GL/gl.h>
#include <GL/glut.h>

Tile::Tile(const PlatteCarrePoint pUpperLeft, const PlatteCarrePoint pUpperRight, const PlatteCarrePoint pLowerLeft, const PlatteCarrePoint pLowerRight) : upperLeft(pUpperLeft), upperRight(pUpperRight), lowerLeft(pLowerLeft), lowerRight(pLowerRight)
{
  zoom_upper_left=NULL;
  zoom_upper_right=NULL;
  zoom_lower_left=NULL;
  zoom_lower_right=NULL;
}


void Tile::FIXME_paint(const unsigned int pMaxX, const unsigned int pMaxY) const
{
  if(zoom_upper_left!=NULL && zoom_upper_right!=NULL && zoom_lower_left!=NULL && zoom_lower_right!=NULL)
    {
      zoom_upper_left ->FIXME_paint(pMaxX, pMaxY);
      zoom_upper_right->FIXME_paint(pMaxX, pMaxY);
      zoom_lower_left ->FIXME_paint(pMaxX, pMaxY);
      zoom_lower_right->FIXME_paint(pMaxX, pMaxY);
    }
  else
    {
      Vector3D ul=this->upperLeft.get3DPoint (pMaxX, pMaxY);
      Vector3D ur=this->upperRight.get3DPoint(pMaxX, pMaxY);
      Vector3D ll=this->lowerLeft.get3DPoint  (pMaxX, pMaxY);
      Vector3D lr=this->lowerRight.get3DPoint(pMaxX, pMaxY);
      
      glBegin(GL_TRIANGLES);
      glColor3f(0.1, 0.2, 0.3);
      glVertex3f(ul.getX(), ul.getY(), ul.getZ());
      glVertex3f(ur.getX(), ur.getY(), ur.getZ());
      glVertex3f(ll.getX(), ll.getY(), ll.getZ());
      glEnd();
      
      glBegin(GL_TRIANGLES);
      glColor3f(0.1, 0.2, 0.3);
      glVertex3f(ur.getX(), ur.getY(), ur.getZ());
      glVertex3f(ul.getX(), ul.getY(), ul.getZ());
      glVertex3f(lr.getX(), lr.getY(), lr.getZ());
      glEnd();
    }
}
