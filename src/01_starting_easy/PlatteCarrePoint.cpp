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

bool PlatteCarrePoint::isBetween(bool pXAxis, PlatteCarrePoint& pFrom, PlatteCarrePoint& pTo) const
{
  // should we check vs the X axis?
  if(pXAxis)
    {
      // the left and right border has to be on the same y level
      if(pFrom.getPcpY()!=pTo.getPcpY())
        {
          throw "PlatteCarrePoint::isBetween with pFrom and pTo not on the same y axis";
        }
      return (this->getPcpY()==pFrom.getPcpY() && this->getPcpX()>=pFrom.getPcpX() && getPcpX()<=pTo.getPcpX());
    }
  // should we check vs the Y axis?
  else
    {
      // the top and bottom border has to be on the same x level
      if(pFrom.getPcpX()!=pTo.getPcpX())
        {
          throw "PlatteCarrePoint::isBetween with pFrom and pTo not on the same x axis";
        }
      return (this->getPcpX()==pFrom.getPcpX() && this->getPcpY()>=pFrom.getPcpY() && getPcpY()<=pTo.getPcpY());
    }
}

bool PlatteCarrePoint::operator <(const PlatteCarrePoint& pOther) const
{
  if(pOther.getPcpX()!=this->getPcpX())
    {
      return (pOther.getPcpX()<this->getPcpX());
    }
  else if(pOther.getPcpX()!=this->getPcpX())
    {
      return (pOther.getPcpY()<this->getPcpY());
    }
  else
    {
      return (pOther.getHeight()<this->getHeight());
    }
}

bool PlatteCarrePoint::operator==(const PlatteCarrePoint& pOther)
{
  return (
          this->getPcpX()==pOther.getPcpX() &&
          this->getPcpY()==pOther.getPcpY() &&
          this->getHeight()==pOther.getHeight()
          );
}
