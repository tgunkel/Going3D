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


Tile_Virtual* WorldModelReaderNasa::splitTile(Tile_Real* pTile, PlatteCarrePoint pSplitPos)
{
  // upper left tile
  Tile_Real* ul=new Tile_Real(this->readValue(pTile->getUpperLeft().getPcpX(),  pTile->getUpperLeft().getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pTile->getUpperLeft().getPcpY()),
                         this->readValue(pTile->getUpperLeft().getPcpX(),  pSplitPos.getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pSplitPos.getPcpY())
                         );

  // upper right tile
  Tile_Real* ur=new Tile_Real(this->readValue(pSplitPos.getPcpX(),              pTile->getUpperRight().getPcpY()),
                         this->readValue(pTile->getUpperRight().getPcpX(), pTile->getUpperRight().getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pSplitPos.getPcpY()),
                         this->readValue(pTile->getUpperRight().getPcpX(), pSplitPos.getPcpY())
                         );
  

  // lower left tile
  Tile_Real* ll=new Tile_Real(this->readValue(pTile->getLowerLeft().getPcpX(),  pSplitPos.getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pSplitPos.getPcpY()),
                         this->readValue(pTile->getLowerLeft().getPcpX(),  pTile->getLowerLeft().getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pTile->getLowerLeft().getPcpY())
                         );
  
  // lower right tile
  Tile_Real* lr=new Tile_Real(this->readValue(pSplitPos.getPcpX(),              pSplitPos.getPcpY()),
                         this->readValue(pTile->getLowerRight().getPcpX(), pSplitPos.getPcpY()),
                         this->readValue(pSplitPos.getPcpX(),              pTile->getLowerRight().getPcpY()),
                         this->readValue(pTile->getLowerRight().getPcpX(), pTile->getLowerRight().getPcpY())
                         );

  // the new Tile gets the father of the one we splited
  Tile_Virtual* result=new Tile_Virtual(ul, ur, ll, lr);
  result->setParent(pTile->getParent());

  // the father has to replace one of his childs with us
  Tile_Virtual* father=pTile->getParent();
  if(father!=NULL)
    {
      father->replaceTile(result, pTile);
    }

  /*
  std::cout << "Tile : " << *pTile << std::endl;
  std::cout << "Split: " << pSplitPos << std::endl;
  std::cout << "ul   : " << *ul << std::endl;
  std::cout << "ur   : " << *ur << std::endl;
  std::cout << "ll   : " << *ll << std::endl;
  std::cout << "lr   : " << *lr << std::endl;
  */

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

  // all new real Tiles are candidates for further splits
  this->splitcandidates.push(this->getSplitCandidateFromTile(ul));
  this->splitcandidates.push(this->getSplitCandidateFromTile(ur));
  this->splitcandidates.push(this->getSplitCandidateFromTile(ll));
  this->splitcandidates.push(this->getSplitCandidateFromTile(lr));

  return result;
}

double WorldModelReaderNasa::getErrorForTileAtPoint(Tile_Real* pTile, PlatteCarrePoint pPcp) const
{
  return std::abs((double)pPcp.getHeight()-pTile->getEstimatedValue(pPcp.getPcpX(), pPcp.getPcpY()));
}

PlatteCarrePoint WorldModelReaderNasa::getPointInTileWithMaxError(Tile_Real* pTile) const
{
  const long step_x=50;
  const long step_y=50;
  const long minsize_x=10;
  const long minsize_y=10;

  double max_estimated_error=-1;
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

          double current_error=getErrorForTileAtPoint(pTile, pcp);

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

  if(max_estimated_error<=0)
    {
      throw "No point with max error found";
    }

  PlatteCarrePoint result(x,y,h);
  std::cout << "Max error for " << *pTile << " found at " << result << " with estimated value " <<  pTile->getEstimatedValue(result.getPcpX(), result.getPcpY()) << std::endl;
  return result;
}

WorldModelReaderNasa_TileSplitCandidate WorldModelReaderNasa::getSplitCandidateFromTile(Tile_Real* pTile) const
{
  // find place where your tile has the biggest difference to the true value
  PlatteCarrePoint max_error_point=this->getPointInTileWithMaxError(pTile);
  double maxError=getErrorForTileAtPoint(pTile, max_error_point);
  WorldModelReaderNasa_TileSplitCandidate splitCandidate=WorldModelReaderNasa_TileSplitCandidate(pTile, maxError, max_error_point);
  return splitCandidate;
}

Tile_Virtual* WorldModelReaderNasa::splitNextCandidate()
{
  Tile_Virtual* result=NULL;

  std::cout << "Do a split for you, candidates: " << splitcandidates.size() << std::endl;

  while(!splitcandidates.empty())
    {
      WorldModelReaderNasa_TileSplitCandidate next=splitcandidates.top();
      splitcandidates.pop();

      std::cout << "Next split candidate " << next << std::endl;
      
      try
        {
          result=splitTile(next.getTile(), next.getMaxErrorPoint());
          break;
        }
      catch(const char* err)
        {
          std::cout << "Split candidate could not be splitted: " << err << std::endl;
        }
    }

  return result;
}

Tile* WorldModelReaderNasa::getNiceWorld()
{
  // the tile represents the whole world by just 4 points
  Tile_Real *start=new Tile_Real(this->readValue(0,            0),
                                 this->readValue(this->cols-1, 0),
                                 this->readValue(0,            this->rows-1),
                                 this->readValue(this->cols-1, this->rows-1)
                                 );

  // this tile is the only split candidate we have for now
  WorldModelReaderNasa_TileSplitCandidate splitCandidate=getSplitCandidateFromTile(start);
  splitcandidates.push(splitCandidate);

  // we split the entry one time to get a virtual one instead of a real tile
  Tile_Virtual* result=splitNextCandidate();

  /*
  for(int c=0; c<3; c++)
    {
      splitNextCandidate();
    }
  */
  return result;
}

