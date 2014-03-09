#include "WorldModelReaderNasa.h"

WorldModelReaderNasa::WorldModelReaderNasa()
{
  this->littleEndian=this->isLittleEndian();
  this->cols=86400;
  this->rows=43200;
  this->skip_cols=1000;
  this->skip_rows=1000;

  this->nasaFile=new std::ifstream("data/srtm_ramp2.world.86400x43200.bin", std::ios::in|std::ios::binary);
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

PlatteCarrePoint WorldModelReaderNasa::readValue(const unsigned int pX, const unsigned int pY)
{
  char buffer[2];
  unsigned char upper;
  unsigned char lower;

  unsigned long fpos=((unsigned long) 2 * (unsigned long) pX * (unsigned long) this->cols) + ((unsigned long) pY * (unsigned long) 2);
  this->nasaFile->seekg(fpos);
  this->nasaFile->read(buffer, 2);
  
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
            PlatteCarrePoint pcp=this->readValue(cur_row, cur_col);
            if(pcp.getHeight()==0)
              std::cout << " " << " ";
            else
              std::cout << pcp.getHeight()/1000 << " ";
          }
        std::cout << std::endl;
      }
  }
}

Tile* WorldModelReaderNasa::getNiceWorld()
{
  Tile_Real* start=new Tile_Real(this->readValue(0,          0),
                                 this->readValue(0,          this->rows),
                                 this->readValue(this->cols, 0),
                                 this->readValue(this->cols, this->rows)
                                 );
  return start;
}

