#include "WorldModelReaderNasa.h"
#include <cassert>
#include <cmath>

WorldModelReaderNasa::WorldModelReaderNasa()
{
  littleEndian=this->isLittleEndian();
  cols=86400;
  rows=43200;
  skip_cols=1000;
  skip_rows=1000;

  nasaFile=new std::ifstream("data/srtm_ramp2.world.86400x43200.bin", std::ios::in|std::ios::binary);
}

void WorldModelReaderNasa::closeFile()
{
  this->nasaFile->close();
}

bool WorldModelReaderNasa::isLittleEndian()
{
  char buffer[2];
  buffer[0]=1;
  buffer[1]=2;
  // assume the lower value is left
  int res=((((int) buffer[0]) << 8) + buffer[1]);
  // 256+2=258
  return (res==258);
}

PlatteCarrePoint WorldModelReaderNasa::readValue(const unsigned int pX, const unsigned int pY) const
{
  if (this->nasaFile->is_open())
  {
    char buffer[2];
    unsigned char upper;
    unsigned char lower;
    
    unsigned long fpos=((unsigned long) 2 * (unsigned long) pY * (unsigned long) this->cols) + ((unsigned long) pX * (unsigned long) 2);
    this->nasaFile->seekg(fpos, std::ios_base::beg);
    this->nasaFile->read(buffer, 2);

    if(this->nasaFile->eof())
      {
        std::cout << "Error: Hitting EOF at position: " << fpos << std::endl;
        throw "EOF while reading file";
      }
    else
      {
        // depending of the endian of your system one of the bytes is upper and one lower
        if(this->littleEndian)
          {
            upper=(unsigned char) buffer[0];
            lower=(unsigned char) buffer[1];
          }
        else
          {
            upper=(unsigned char) buffer[1];
            lower=(unsigned char) buffer[0];
          }
        
        // move the upper up and leave the lower low
        short value=((((short) upper << 8) + lower));
        
        return PlatteCarrePoint(pX, pY, value);
      }
  }
  else
  {
    std::cout << "Error: File not open" << std::endl;
    throw "File not open error";
  }
}

void WorldModelReaderNasa::readFile()
{
  std::cout << "Reading file" << std::endl;


  if (this->nasaFile->is_open())
  {
    std::cout << "File is open!" << std::endl;

    for(unsigned long cur_row=0; cur_row<this->rows; cur_row+=this->skip_rows)
      {
        for(unsigned long cur_col=0; cur_col<this->cols; cur_col+=this->skip_cols)
          {
            PlatteCarrePoint pcp=this->readValue(cur_col, cur_row);
            if(pcp.getHeight()==0)
              std::cout << " " << " ";
            else
              std::cout << pcp.getHeight()/1000 << " ";
          }
        std::cout << std::endl;
      }
  }
}


std::list<Tile*> WorldModelReaderNasa::getNiceWorld()
{
  std::list<Tile*> result;

  unsigned int step_x=300;
  unsigned int step_y=300;

  unsigned int pos_x=0;
  unsigned int pos_y=0;


  while(pos_y+step_y<this->rows)
    {
      //std::cout << "Debug " << pos_x << "/" << pos_y << std::endl;
      while(pos_x+step_x<this->cols)
        {
          Tile *t=new Tile(this->readValue(pos_x,        pos_y),         // Upper left
                           this->readValue(pos_x+step_x, pos_y),         // Upper right
                           this->readValue(pos_x,        pos_y+step_y),  // Lower left
                           this->readValue(pos_x+step_x, pos_y+step_y)   // Lower right
                           );
          result.push_back(t);
          pos_x=pos_x+step_x;
        }
      pos_y=pos_y+step_x;
      pos_x=0;
    }
  return result;
}

