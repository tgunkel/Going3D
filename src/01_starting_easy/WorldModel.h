#ifndef _WorldModel_h_
#define _WorldModel_h_

#include <math.h>
#include <iostream>

/* This reads a 3D modell from a binary file
   See http://visibleearth.nasa.gov/view.php?id=73934 for the source of the file
   The file consists of 2 byte large big endian numbers with the height of the point
 */
class WorldModel
{
 public:
  // constructor
  WorldModel();

  void readFile();

 private:
  // is your system little endian, e.g. all standard personal computers
  bool isLittleEndian();
  bool littleEndian;
  
  // this size of the file
  unsigned int cols, rows;
  unsigned int skip_cols, skip_rows;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const WorldModel &a);

#endif
