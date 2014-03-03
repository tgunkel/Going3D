#include "Camera.h"

Camera::Camera(const Vector3D pPosition, const Vector3D pLookAt) : position(pPosition), lookAt(pLookAt)
{

}

Vector3D Camera::getPosition() const
{
  return this->position;
}

Vector3D Camera::getLookAt() const
{
  return this->lookAt;
}

std::ostream& operator<<(std::ostream &strm, const Camera &a)
{
  return strm << "Camera: Pos " << a.getPosition() << " Look: " << a.getLookAt();
}
