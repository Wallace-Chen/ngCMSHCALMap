#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <time.h>

#include "HCALFrontEndMap.h"
#include "HCALLMapLoaderABCDE_FrontEndMap.h"
#include "HCALFrontEndMapDumper.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"#Please give at least 1 argument " << "RunMode " << std::endl;
    std::cerr <<"# Valid configurations are " << std::endl;
    std::cerr <<"# ./HCALLMapAnalyzer RunMode" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::cout << "#The valid run modes are: A, B, C, D, E" << std::endl;
  std::cout << "#The run mode we have right now is: " << RunMode << std::endl;

  //initialize the variables we need in analysis
  std::vector<HCALFrontEndMapEntry> myHCALFrontEndMapEntries;
  
  std::string filename_HBEF = "LMap_" + RunMode + "/HCALmapHBEF_" + RunMode +".txt";
  int NChannel_HBEF = HCALLMapLoaderABCDE_FrontEndMap::GetFrontEndMapromLMap( filename_HBEF, myHCALFrontEndMapEntries );

  std::string filename_HO = "LMap_" + RunMode + "/HCALmapHO_" + RunMode +".txt";
  int NChannel_HO = HCALLMapLoaderABCDE_FrontEndMap::GetFrontEndMapromLMap( filename_HO, myHCALFrontEndMapEntries );

  HCALFrontEndMapDumper::HCALFrontEndMapDumper( RunMode, myHCALFrontEndMapEntries );
  return 0;
}

