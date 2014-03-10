#include "Tile.h"

std::ostream& operator<<(std::ostream &strm, const Tile &a)
{
  return strm << "(" << a.getUpperLeft() << "/" << a.getUpperRight() << "/" << a.getLowerLeft() << "/" << a.getLowerRight() << ")";
}
