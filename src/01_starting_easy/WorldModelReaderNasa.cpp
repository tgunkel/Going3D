#include "WorldModelReaderNasa.h"
#include <cassert>
#include <cmath>

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


Tile_Virtual* WorldModelReaderNasa::splitTile(Tile_Real* pTile, PlatteCarrePoint pSplitPos)
{
  // upper left tile
  Tile* ul=new Tile_Real(this->readValue(pTile->getUpperLeft().getPcpX(),  pTile->getUpperLeft().getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pTile->getUpperLeft().getPcpY()),
                         this->readValue(pTile->getUpperLeft().getPcpX(),  pSplitPos.getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pSplitPos.getPcpY())
                         );
  
  // upper right tile
  Tile* ur=new Tile_Real(this->readValue(pSplitPos.getPcpX(),              pTile->getUpperRight().getPcpY()),
                         this->readValue(pTile->getUpperRight().getPcpX(), pTile->getUpperRight().getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pSplitPos.getPcpY()),
                         this->readValue(pTile->getUpperRight().getPcpX(), pSplitPos.getPcpY())
                         );
  

  // lower left tile
  Tile* ll=new Tile_Real(this->readValue(pTile->getLowerLeft().getPcpX(),  pSplitPos.getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pSplitPos.getPcpY()),
                         this->readValue(pTile->getLowerLeft().getPcpX(),  pTile->getLowerLeft().getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pTile->getLowerLeft().getPcpY())
                         );
  
  // lower right tile
  Tile* lr=new Tile_Real(this->readValue(pSplitPos.getPcpX(),              pSplitPos.getPcpY()),
                         this->readValue(pTile->getLowerRight().getPcpX(), pSplitPos.getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pTile->getLowerRight().getPcpY()),
                         this->readValue(pTile->getLowerRight().getPcpX(), pTile->getLowerRight().getPcpY())
                         );

  Tile_Virtual* result=new Tile_Virtual(ul, ur, ll, lr);


  std::cout << "Tile : " << *pTile << std::endl;
  std::cout << "Split: " << pSplitPos << std::endl;
  std::cout << "ul   : " << *ul << std::endl;
  std::cout << "ur   : " << *ur << std::endl;
  std::cout << "ll   : " << *ll << std::endl;
  std::cout << "lr   : " << *lr << std::endl;

  // match the original outer corners
  assert(ul->getUpperLeft() ==pTile->getUpperLeft());
  assert(ur->getUpperRight()==pTile->getUpperRight());
  assert(ll->getLowerLeft() ==pTile->getLowerLeft());
  assert(lr->getLowerRight()==pTile->getLowerRight());

  // match the new center
  assert(ul->getLowerRight()==pSplitPos);
  assert(ur->getLowerLeft() ==pSplitPos);
  assert(ll->getUpperRight()==pSplitPos);
  assert(lr->getUpperLeft() ==pSplitPos);

  // match the border connect points
  assert(ul->getUpperRight()==ur->getUpperLeft());
  assert(ul->getLowerLeft()==ll->getUpperLeft());
  assert(ll->getLowerRight()==lr->getLowerLeft());

  return result;
}

PlatteCarrePoint WorldModelReaderNasa::getPointInTileWithMaxError(Tile_Real* pTile)
{
  const long step_x=50;
  const long step_y=50;
  const long minsize_x=500;
  const long minsize_y=500;

  double max_estimated_error=0;
  unsigned int x=0,y=0;
  short  h=0;

  for(unsigned long cur_row=pTile->getUpperLeft().getPcpY()+minsize_y; (cur_row+minsize_y)<pTile->getLowerLeft().getPcpY(); cur_row+=step_y)
    {
      for(unsigned long cur_col=pTile->getUpperLeft().getPcpX()+minsize_x; (cur_col+minsize_x)<pTile->getUpperRight().getPcpX(); cur_col+=step_x)
        {
          assert(cur_col>=pTile->getUpperLeft().getPcpX());
          assert(cur_col<=pTile->getUpperRight().getPcpX());
          assert(cur_row>=pTile->getUpperLeft().getPcpY());
          assert(cur_row<=pTile->getLowerLeft().getPcpY());

          PlatteCarrePoint pcp=this->readValue(cur_col, cur_row);

          double current_error=std::abs(pcp.getHeight()-pTile->getEstimatedValue(cur_col, cur_row));
          if(current_error>max_estimated_error)
            {
              //std::cout << "New max error: " << pcp << " " << current_error << std::endl;
              max_estimated_error=current_error;
              x=pcp.getPcpX();
              y=pcp.getPcpY();              
              h=pcp.getHeight();
            }
        }
    }

  if(max_estimated_error==0)
    {
      throw "No point with max error found";
    }

  PlatteCarrePoint result(x,y,h);
  std::cout << "Max error for " << *pTile << " found at " << result << " with estimated value " <<  pTile->getEstimatedValue(result.getPcpX(), result.getPcpY()) << std::endl;
  return result;
}
        
Tile_Virtual* WorldModelReaderNasa::splitTile(Tile_Real* pTile)
{
  // first find place where your tile has the biggest difference to the true value
  PlatteCarrePoint max_error_point=this->getPointInTileWithMaxError(pTile);

  // next split the tile at this point into 4 new ones
  Tile_Virtual* new_head=this->splitTile(pTile, max_error_point);

  // now replace us at our father
  Tile_Virtual* father=pTile->getParent();
  if(father!=NULL)
    {
      father->replaceTile(new_head, pTile);
    }
  return new_head;
}


/*
Tile_Virtual* WorldModelReaderNasa::splitTileWithMaxError(Tile_Real* pTile)
{
  
}
*/

Tile* WorldModelReaderNasa::getNiceWorld()
{
  Tile_Real *start=new Tile_Real(this->readValue(0,            0),
                                 this->readValue(this->cols-1, 0),
                                 this->readValue(0,            this->rows-1),
                                 this->readValue(this->cols-1, this->rows-1)
                                 );

  Tile_Virtual* result;
  result=splitTile(start);

  Tile_Real* lr;
  Tile_Real* ur;
  Tile_Real* ul;
  Tile_Real* ll;

  lr=(Tile_Real*) result->getLowerRightTile();
  try {
    splitTile(lr);
  } catch (char const* s) {
    std::cout << "Exception: " << s << std::endl;
  }

  ur=(Tile_Real*) result->getUpperRightTile();
  try {
    splitTile(ur);
  } catch (char const* s) {
    std::cout << "Exception: " << s << std::endl;
  }

  ul=(Tile_Real*) result->getUpperLeftTile();
  try {
    splitTile(ul);
  } catch (char const* s) {
    std::cout << "Exception: " << s << std::endl;
  }

  ll=(Tile_Real*) result->getLowerLeftTile();
  splitTile(ll);

  std::cout << "This is the head" << *result << std::endl;
  std::cout << "This is UL"       << *result->getUpperLeftTile() << std::endl;
  std::cout << "This is UR"       << *result->getUpperRightTile() << std::endl;
  std::cout << "This is LL"       << *result->getLowerLeftTile() << std::endl;
  std::cout << "This is LR"       << *result->getLowerRightTile() << std::endl;

  return result;
}

