#include "HCALLMapProducer.h"
#include "HCALTPProducer.h"
#include "HCALLMapLoader.h"
#include "HCALLMapDumper.h"
#include "HCALLMapChecker.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr <<"#Please give at least 2 argument " << "RunMode ProduceMode" << std::endl;
    std::cerr <<"# Valid configurations are " << std::endl;
    std::cerr <<"# ./HCALLMapAnalyzer RunMode PrdMode" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string PrdMode = argv[2];

  std::cout << "#The valid run modes are: HB, HE, HF, HO" << std::endl;
  std::cout << "#The run mode we have right now is: " << RunMode << std::endl;
  std::cout << "#The valid run modes are: LMap, EMap, FMap HT" << std::endl;
  std::cout << "#The produce mode we have right now is: " << PrdMode << std::endl;

  HCALTPProducer myHCALTPProducer;
  HCALLMapLoader myHCALLMapLoader;
  HCALLMapDumper myHCALLMapDumper;
  HCALLMapChecker myHCALLMapChecker;

  if( RunMode == "HB" )
  {
    HBMappingAlgorithm myHBMappingAlgorithm;
    myHBMappingAlgorithm.ConstructHBLMapObject("Normal");
    myHBMappingAlgorithm.ConstructHBLMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkHBLMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
    if( passCollisionCheck ){ std::cout << "#Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#Did not pass collision check! Please check!" << std::endl; return -1;}

    /*
    ngHBMappingAlgorithm myngHBMappingAlgorithm;
    myngHBMappingAlgorithm.ConstructngHBLMapObject();
    bool passCollisionCheck = myHCALLMapChecker.checkngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    if( passCollisionCheck ){ std::cout << "#Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#Did not pass collision check! Please check!" << std::endl; return -1;}
    */

    if( PrdMode == "LMap" )
    {
      myHCALLMapDumper.printHBLMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      myHCALLMapDumper.makedbHBLMapObject("officialMap/HCALLogicalMap.db", "HBLogicalMap",
                                          myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      //      myHCALLMapDumper.printngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
      //myHCALLMapDumper.makedbngHBLMapObject("officialMap/HCALLogicalMap.db", "ngHBLogicalMap",
      //                                    myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      myHCALLMapDumper.printHBEMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      //myHCALLMapDumper.printngHBEMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      myHCALLMapDumper.printHBFrontEndMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      //myHCALLMapDumper.printngHBFrontEndMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "HT" )
    {
      myHCALTPProducer.printHBHTEMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      //myHCALTPProducer.printngHBHTEMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "LMapCalib")
    {

    }
    return 1;
  }
  else if( RunMode == "HE" )
  {
    ngHEMappingAlgorithm myngHEMappingAlgorithm;
    myngHEMappingAlgorithm.ConstructngHELMapObject("Normal");
    myngHEMappingAlgorithm.ConstructngHELMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    if( passCollisionCheck ){ std::cout << "#Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#Did not pass collision check! Please check!" << std::endl; return -1;}
    if( PrdMode == "LMap" )
    {
      myHCALLMapDumper.printngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
      myHCALLMapDumper.makedbngHELMapObject("officialMap/HCALLogicalMap.db", "ngHELogicalMap",
                                            myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      myHCALLMapDumper.printngHEEMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      myHCALLMapDumper.printngHEFrontEndMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "HT" )
    {
      myHCALTPProducer.printngHEHTEMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "LMapCalib")
    {
      myHCALLMapDumper.printngHECalibLMapObject(myngHEMappingAlgorithm.myngHECalib);
      //myHCALLMapDumper.;
    }
    return 1;
  }
  else if( RunMode == "HF" )
  {
    //HFMappingAlgorithm myHFMappingAlgorithm;
    //myHFMappingAlgorithm.ConstructHFLMapObject();
    
    ngHFMappingAlgorithm myngHFMappingAlgorithm;
    myngHFMappingAlgorithm.ConstructngHFLMapObject();
    //myngHFMappingAlgorithm.SplitngHFfromOldHF(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);
    bool passCollisionCheck = myHCALLMapChecker.checkngHFLMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    if( passCollisionCheck ){ std::cout << "#Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#Did not pass collision check! Please check!" << std::endl; return -1;}
    if( PrdMode == "LMap" )
    {
      //myHCALLMapDumper.printHFLMapObject(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);
      myHCALLMapDumper.printngHFLMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
      myHCALLMapDumper.makedbngHFLMapObject("officialMap/HCALLogicalMap.db", "ngHFLogicalMap",
                                            myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      myHCALLMapDumper.printngHFEMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      myHCALLMapDumper.printngHFFrontEndMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "HT" )
    {
      myHCALTPProducer.printngHFHTEMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    return 1;
  }
  else if( RunMode == "HO" )
  {
    HOMappingAlgorithm myHOMappingAlgorithm;
    //so sorry no HO mapping algorithm for now... in a mess... directly load from generation G mapping algotrithm
    int NChannel = myHCALLMapLoader.GetHOFromLMap("officialMap/HCALmapHO_G.txt", myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
    //myHOMappingAlgorithm.ConstructHOLMapObject();

    if( PrdMode == "LMap" )
    {
      myHCALLMapDumper.printHOLMapObject(myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
      myHCALLMapDumper.makedbHOLMapObject("officialMap/HCALLogicalMap.db", "HOLogicalMap",
                                          myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      myHCALLMapDumper.printHOEMapObject(myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      myHCALLMapDumper.printHOFrontEndMapObject(myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
    }
    return 1;
  }

  else{ std::cout << "#Invalide Run Mode, the the fuck is going on!" << std::endl; return -1; }
  return 0;
}
