#include "PlatteCarrePoint.h"

PlatteCarrePoint::PlatteCarrePoint(const unsigned int pX, const unsigned int pY, const short pHeight)
{
  this->x=pX;
  this->y=pY;
  this->height=pHeight;
}

short PlatteCarrePoint::getHeight()
{
  return this->height;
}

Vector3D PlatteCarrePoint::get3DPoint(const unsigned int pMaxX, const unsigned int pMaxY) const
{
  return Vector3D(
                  ((double) this->x / (double) pMaxX * 4.0)-2.0,
                  ((double) this->y / (double) pMaxY * 4.0)-2.0,
                  (double) this->height/9000.0*3.0
                  );
}

std::ostream& operator<<(std::ostream &strm, const PlatteCarrePoint &a)
{
  return strm << "(" << a.x << "/" << a.y << "/" << a.height << ") ";
}
