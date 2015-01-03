#include "PlatteCarrePoint.h"
#include <math.h>

PlatteCarrePoint::PlatteCarrePoint(const unsigned int pPcpX, const unsigned int pPcpY, const short pPcpHeight, const unsigned int pPcpMaxX, const unsigned int pPcpMaxY, const unsigned int pSphereRadius) : 
  pcpX(pPcpX), 
  pcpY(pPcpY), 
  pcpHeight(pPcpHeight),
  sphereRadius(pSphereRadius),
  longtitude(getLtitude(pPcpX, pPcpMaxX)),
  latitude  (getLtitude(pPcpY, pPcpMaxY)),
  pointIn3D(get3DPoint(longtitude, latitude, sphereRadius, pPcpHeight))
{  
  //std::cout << *this << std::endl;
}

double PlatteCarrePoint::getLtitude(const unsigned int pValue, const unsigned int pMaxValue) const
{
  return (pValue/((double) pMaxValue)*360.0)-180.0;
}

Vector3D PlatteCarrePoint::get3DPoint(const double pLongtitude, const double pLatitude, const unsigned int pSphereRadius, const short pPcpHeight) const
{
  // we declare the north  - south axis        to be the z axis
  // we declare the east   - west  axis        to be the x axis
  // we declare the viewer - earth center axis to be the y axis

  // this is the point at 0/0
  Vector3D result=Vector3D(0, pSphereRadius+(int) pPcpHeight, 0);

  // now rotate it according to the longtitude to the left or the right (arround the z axis)
  result=result.rotateZ(pLongtitude);

  // now rotate it according to the latitude up or down (arround the x axis)
  result=result.rotateX(pLatitude);

  return result;
}

unsigned int PlatteCarrePoint::getPcpX() const
{
  return this->pcpX;
}

unsigned int PlatteCarrePoint::getPcpY() const
{
  return this->pcpY;
}

short PlatteCarrePoint::getPcpHeight() const
{
  return this->pcpHeight;
}

double PlatteCarrePoint::getLongtitude() const
{
  return this->longtitude;
}

double PlatteCarrePoint::getLatitude() const
{
  return this->latitude;
}

Vector3D PlatteCarrePoint::getPointIn3D() const
{
  return this->pointIn3D;
}

bool PlatteCarrePoint::isWater() const
{
  return (this->getPcpHeight()<0.0000000000001);
}

std::ostream& operator<<(std::ostream &strm, const PlatteCarrePoint &a)
{
  return strm << "PlatteCarre: " << a.getPcpX() << "/" << a.getPcpY() << " > " << a.getPcpHeight() << " Angle: " << a.getLongtitude() << " / " << a.getLatitude() << " 3D point: " << a.getPointIn3D();
}

bool PlatteCarrePoint::operator <(const PlatteCarrePoint& pOther) const
{
  if(pOther.getPcpX()!=this->getPcpX())
    {
      return (this->getPcpX()<pOther.getPcpX());
    }
  else if(pOther.getPcpY()!=this->getPcpY())
    {
      return (this->getPcpY()<pOther.getPcpY());
    }
  else
    {
      return (this->getPcpHeight()<pOther.getPcpHeight());
    }
}

bool PlatteCarrePoint::operator==(const PlatteCarrePoint& pOther) const
{
  return (
          this->getPcpX()==pOther.getPcpX() &&
          this->getPcpY()==pOther.getPcpY() &&
          this->getPcpHeight()==pOther.getPcpHeight()
          );
}

