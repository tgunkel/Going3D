#include "Vector3D.h"

Vector3D::Vector3D(const double pX, const double pY, const double pZ)
{
  x=pX;
  y=pY;
  z=pZ;
}

double Vector3D::getX() const
{
  return x;
}

double   Vector3D::getY() const
{
  return y;
}

double   Vector3D::getZ() const
{
  return z;
}

Vector3D Vector3D::add(const Vector3D &other) const
{
  Vector3D res(x+other.x, y+other.y, z+other.z);
  return res;
}

Vector3D Vector3D::sub(const Vector3D &other) const
{
  Vector3D res(x-other.x, y-other.y, z-other.z);
  return res;
}

double   Vector3D::length() const
{
  return sqrt(x*x+y*y+z*z);
}

Vector3D Vector3D::normalize() const
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

Vector3D Vector3D::mult(double scalar) const
{
  return Vector3D(x*scalar, y*scalar, z*scalar);
}

Vector3D Vector3D::ZERO_ZERO_ZERO()
{
  return Vector3D(0.0, 0.0, 0.0);
}

std::ostream& operator<<(std::ostream &strm, const Vector3D &a)
{
  return strm << "(" << a.getX() << "/" << a.getY() << "/" << a.getZ() << ")";
}
