#ifndef _WorldModelReaderNasa_h_
#define _WorldModelReaderNasa_h_

#include <math.h>
#include <iostream>
#include <fstream>
#include "PlatteCarrePoint.h"
#include "Tile_Real.h"

/* This reads a 3D modell from a binary file
   See http://visibleearth.nasa.gov/view.php?id=73934 for the source of the file
   The file consists of 2 byte large big endian numbers with the height of the point
 */
class WorldModelReaderNasa
{
 public:
  // constructor
  WorldModelReaderNasa();

  void readFile();

  PlatteCarrePoint readValue(const unsigned int pX, const unsigned int pY);

  Tile* getNiceWorld();

 private:
  void closeFile();
  std::ifstream* nasaFile;


  // is your system little endian, e.g. all standard personal computers
  bool isLittleEndian();
  bool littleEndian;
  
  // this size of the file
  unsigned int cols, rows;
  unsigned int skip_cols, skip_rows;
};

// override the << operator
std::ostream& operator<<(std::ostream &strm, const WorldModelReaderNasa &a);

#endif
