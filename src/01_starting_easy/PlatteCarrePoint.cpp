#include "PlatteCarrePoint.h"

PlatteCarrePoint::PlatteCarrePoint(const unsigned int pX, const unsigned int pY, const short pHeight)
{
  this->x=pX;
  this->y=pY;
  this->height=pHeight;
}

unsigned int PlatteCarrePoint::getPcpX() const
{
  return this->x;
}

unsigned int PlatteCarrePoint::getPcpY() const
{
  return this->y;
}

short PlatteCarrePoint::getHeight() const
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
  return strm << "(" << a.getPcpX() << "/" << a.getPcpY() << "/" << a.getHeight() << ") ";
}

bool PlatteCarrePoint::operator==(const PlatteCarrePoint& pOther)
{
  return (
          this->getPcpX()==pOther.getPcpX() &&
          this->getPcpY()==pOther.getPcpY() &&
          this->getHeight()==pOther.getHeight()
          );
}
