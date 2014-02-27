#ifndef _RBGColor_h_
#define _RBGColor_h_

#include <iostream>

/* Small class to represent a RBG color
 */
class RBGColor
{
 public:
  // constructor
  RBGColor(const unsigned char pRed, const unsigned char pGreen, const unsigned char pBlue);

  // get the Red value
  unsigned char getRed() const;
  double        getRedInPercent() const;

  // get the green value
  unsigned char getGreen() const;
  double        getGreenInPercent() const;

  // get the blue value
  unsigned char getBlue() const;
  double        getBlueInPercent() const;

 private:
  unsigned char red,green,blue;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const RBGColor &a);

#endif
