#include "WorldModel.h"
#include <fstream>
#include <endian.h>

WorldModel::WorldModel()
{
  this->littleEndian=this->isLittleEndian();
  this->cols=86400;
  this->rows=43200;
  this->skip_cols=1000;
  this->skip_rows=1000;
}

bool WorldModel::isLittleEndian()
{
  char buffer[2];
  buffer[0]=1;
  buffer[1]=2;
  // assume the lower value is left
  int res=((((int) buffer[0]) << 8) + buffer[1]);
  // 256+2=258
  return (res==258);
}

void WorldModel::readFile()
{
  std::cout << "Reading file" << std::endl;
  std::streampos size;

  char buffer[2];
  unsigned char upper;
  unsigned char lower;

  std::ifstream myfile("data/srtm_ramp2.world.86400x43200.bin", std::ios::in|std::ios::binary);
  if (myfile.is_open())
  {
    std::cout << "File is open!" << std::endl;

    long counter=0;
    for(unsigned int cur_row=0; cur_row<this->rows; cur_row++)
      {
        for(unsigned int cur_col=0; cur_col<this->cols; cur_col++)
          {
            myfile.read(buffer, 2);

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

            if((cur_col/this->skip_cols)*this->skip_cols==cur_col
               && (cur_row/this->skip_rows)*this->skip_rows==cur_row)
              {
                if(value==0)
                  std::cout << " " << " ";
                else
                  std::cout << value/1000 << " ";
              }
            
            counter++;
          }
        if((cur_row/this->skip_rows)*this->skip_rows==cur_row)
           std::cout << std::endl;
      }
    myfile.close();
    std::cout << counter << std::endl;
  }
}
