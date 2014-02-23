#include "Vector3D.h"

Vector3D::Vector3D(double pX, double pY, double pZ)
{
  x=pX;
  y=pY;
  y=pZ;
}

double   const Vector3D::getX()
{
  return x;
}

double   const Vector3D::getY()
{
  return y;
}

double   const Vector3D::getZ()
{
  return z;
}

Vector3D const Vector3D::add(const Vector3D &other)
{
  Vector3D res(x+other.x, y+other.y, z+other.z);
  return res;
}

Vector3D const Vector3D::sub(const Vector3D &other)
{
  Vector3D res(x-other.x, y-other.y, z-other.z);
  return res;
}

double   const  Vector3D::length()
{
  return sqrt(x*x+y*y+z*z);
}

Vector3D const  Vector3D::normalize()
{
  if(this->length()>0.0)
    {
      return this->mult(1.0/this->length());
    }
  else
    {
      // FIXME what shall we do if we are the 0 vector?
      return *this;
    }
}

Vector3D const Vector3D::mult(double scalar)
{
  return Vector3D(x*scalar, y*scalar, z*scalar);
}

std::ostream& operator<<(std::ostream &strm, const Vector3D &a)
{
  return strm << "Thorsten";
}
