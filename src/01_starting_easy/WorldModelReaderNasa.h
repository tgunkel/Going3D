#ifndef _WorldModelReaderNasa_h_
#define _WorldModelReaderNasa_h_

#include <math.h>
#include <iostream>
#include <fstream>
#include <queue>
#include "PlatteCarrePoint.h"
#include "Tile.h"

/* This reads a 3D modell from a binary file
   See http://visibleearth.nasa.gov/view.php?id=73934 for the source of the file
   The file consists of 2 byte large big endian numbers with the height of the point
 */
class WorldModelReaderNasa
{
 public:
  // constructor
  WorldModelReaderNasa();

  // read the whole file
  void readFile();

  // read just one value from the file
  PlatteCarrePoint readValue(const unsigned int pX, const unsigned int pY) const;

  // return a pointer to the first tile which represents the data in the file
  std::list<Tile*> getNiceWorld();

 private:
  // close the file
  void closeFile();

  // the file object
  std::ifstream* nasaFile;

  // is your system little endian, e.g. all standard personal computers
  bool isLittleEndian();

  // remember little endian status
  bool littleEndian;
  
  // this size of the file
  unsigned int cols, rows;

  unsigned int skip_cols, skip_rows;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const WorldModelReaderNasa &a);

#endif
