#include "RBGColor.h"

RBGColor::RBGColor(const unsigned char pRed, const unsigned char pGreen, const unsigned char pBlue)
{
  this->red=pRed;
  this->green=pGreen;
  this->blue=pBlue;
}

unsigned char RBGColor::getRed() const
{
  return this->red;
}

double RBGColor::getRedInPercent() const
{
  return this->getRed()/255.0;
}

unsigned char RBGColor::getBlue() const
{
  return this->blue;
}

double RBGColor::getBlueInPercent() const
{
  return this->getBlue()/255.0;
}

unsigned char RBGColor::getGreen() const
{
  return this->green;
}

double RBGColor::getGreenInPercent() const
{
  return this->getGreen()/255.0;
}

std::ostream& operator<<(std::ostream &strm, const RBGColor &a)
{
  return strm << "(" << a.getRed() << "/" << a.getGreen() << "/" << a.getBlue() << ")";
}
