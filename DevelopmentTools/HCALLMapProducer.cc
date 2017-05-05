#include "HCALLMapProducer.h"
#include "HCALLMapDumper.h"

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
  std::cout << "#The valid run modes are: HB, HE, HF, HO" << std::endl;
  std::cout << "#The run mode we have right now is: " << RunMode << std::endl;

  HCALLMapDumper myHCALLMapDumper;

  if( RunMode == "HB" )
  {
    ngHBMappingAlgorithm myngHBMappingAlgorithm;
    myngHBMappingAlgorithm.ConstructngHBLMapObject();

    myHCALLMapDumper.printngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBPMTBox, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);

    //myHCALLMapDumper.printngHBEMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBPMTBox, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);

    //myHCALLMapDumperprintngHBFrontEndMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBPMTBox, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    return 1;
  }
  else if( RunMode == "HE" )
  {
    ngHEMappingAlgorithm myngHEMappingAlgorithm;
    myngHEMappingAlgorithm.ConstructngHELMapObject();

    myHCALLMapDumper.printngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHEPMTBox, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);

    myHCALLMapDumper.printngHEEMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHEPMTBox, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);

    //myHCALLMapDumper.printngHEFrontEndMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHEPMTBox, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    return 1;
  }
  else if( RunMode == "HF" )
  {
    HFMappingAlgorithm myHFMappingAlgorithm;
    myHFMappingAlgorithm.ConstructHFLMapObject();

    //myHCALLMapDumper.printHFLMapObject(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);
    
    ngHFMappingAlgorithm myngHFMappingAlgorithm;
    myngHFMappingAlgorithm.ConstructngHFLMapObject();
    //myngHFMappingAlgorithm.SplitngHFfromOldHF(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);
    
    myHCALLMapDumper.printngHFLMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    
    //myHCALLMapDumper.printngHFEMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
   
    //myHCALLMapDumper.printngHFFrontEndMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    return 1;
  }
  else if( RunMode == "HO" )
  {
    return 1;
  }

  else{ std::cout << "#Invalide Run Mode, the the fuck is going on!" << std::endl; return -1; }
  return 0;
}
