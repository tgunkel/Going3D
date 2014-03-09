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

Vector3D PlatteCarrePoint::get3DPoint4PlanePane(const double pZoomX, const double pZoomY, const double pZoomZ, const Vector3D pShift) const
{
  return Vector3D(
                  ((double) this->x       * (double) pZoomX)+pShift.getX(),
                  ((double) this->y       * (double) pZoomY)+pShift.getY(),
                  ((double)  this->height * (double) pZoomZ)+pShift.getZ()
                  );
}

std::ostream& operator<<(std::ostream &strm, const PlatteCarrePoint &a)
{
  return strm << "(" << a.x << "/" << a.y << "/" << a.height << ") ";
}
