#include "PlatteCarrePoint.h"
#include <math.h>

PlatteCarrePoint::PlatteCarrePoint(const unsigned int pPcpX, const unsigned int pPcpY, const short pPcpHeight, const unsigned int pPcpMaxX, const unsigned int pPcpMaxY, const unsigned int pSphereRadius) : 
  pcpX(pPcpX), 
  pcpY(pPcpY), 
  pcpHeight(pPcpHeight),
  sphereRadius(pSphereRadius),
  longtitude(getLongtitude4Pcp(pPcpX, pPcpMaxX)),
  latitude  (getLatitude4Pcp(pPcpY, pPcpMaxY)),
  pointIn3D(get3DPoint(longtitude, latitude, sphereRadius, pPcpHeight))
{  
  // std::cout << *this << std::endl;
}

double PlatteCarrePoint::getLatitude4Pcp(const unsigned int pValue, const unsigned int pMaxValue) const
{
  return -((pValue/((double) pMaxValue)*180.0)-90.0);
}

double PlatteCarrePoint::getLongtitude4Pcp(const unsigned int pValue, const unsigned int pMaxValue) const
{
  return -((pValue/((double) pMaxValue)*360.0)-180.0);
}

Vector3D PlatteCarrePoint::get3DPoint(const double pLongtitude, const double pLatitude, const unsigned int pSphereRadius, const short pPcpHeight) const
{
  // http://stackoverflow.com/questions/10473852/convert-latitude-and-longitude-to-point-in-3d-space?rq=1
  double lng=pLongtitude*M_PI/180.0;
  double lat=pLatitude  *M_PI/180.0;

  double h=(double) pSphereRadius+((double) pPcpHeight);

  Vector3D result=Vector3D(
                           h*cos(lat)*cos(lng),
                           h*cos(lat)*sin(lng),
                           h*sin(lat)
                           );

  
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

