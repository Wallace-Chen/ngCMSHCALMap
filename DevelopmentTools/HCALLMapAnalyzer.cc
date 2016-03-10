#include <sstream>
#include <fstream>

#include "HCALLMapAnalyzer.h"
#include "HCALLMapLoader.h"
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
  std::cout << "#The valid run modes are: HBHEHFVME, HBHEHFuTCA, HOVME" << std::endl;
  std::cout << "#The run mode we have right now is: " << RunMode << std::endl;

  //initialize the variables we need in analysis
  std::vector<HBFrontEnd> myHBFrontEnd; std::vector<HBBackEnd> myHBBackEnd; std::vector<HBPMTBox> myHBPMTBox; std::vector<HBGeometry> myHBGeometry; std::vector<HBTriggerTower> myHBTriggerTower;
  std::vector<HEFrontEnd> myHEFrontEnd; std::vector<HEBackEnd> myHEBackEnd; std::vector<HEPMTBox> myHEPMTBox; std::vector<HEGeometry> myHEGeometry; std::vector<HETriggerTower> myHETriggerTower;
  std::vector<HFFrontEnd> myHFFrontEnd; std::vector<HFBackEnd> myHFBackEnd; std::vector<HFPMTBox> myHFPMTBox; std::vector<HFGeometry> myHFGeometry; std::vector<HFTriggerTower> myHFTriggerTower;
  std::vector<HOFrontEnd> myHOFrontEnd; std::vector<HOBackEnd> myHOBackEnd; std::vector<HOPMTBox> myHOPMTBox; std::vector<HOGeometry> myHOGeometry; std::vector<HOTriggerTower> myHOTriggerTower;
  
  if( RunMode == "HBHEHFVME" )
  {
    std::string txtfilename = "officialMap/HCALmapHBEF_G.txt";
    int NChannel = HCALLMapLoader::GetHBHEHFromLMap(
                                                    txtfilename,
                                                    myHBFrontEnd, myHBBackEnd, myHBPMTBox, myHBGeometry, myHBTriggerTower,
                                                    myHEFrontEnd, myHEBackEnd, myHEPMTBox, myHEGeometry, myHETriggerTower,
                                                    myHFFrontEnd, myHFBackEnd, myHFPMTBox, myHFGeometry, myHFTriggerTower
                                                   );
    HBHEAnalyzer myHBHEAnalyzer;
    HFAnalyzer myHFAnalyzer;

    if(NChannel == myHBHEAnalyzer.NchHBHE_all + myHFAnalyzer.NchHF_all){ std::cout << "#The number of channels we get from Lmap text file equals to the Number of channel we expected, Good!" << std::endl; }
    else{ std::cout << "#We have " << NChannel << " channels from txt Lmap while we have " << myHBHEAnalyzer.NchHBHE_all + myHFAnalyzer.NchHF_all << " channels expected in HBHEHF, something must be wrong!" << std::endl; return -1; }

    myHBHEAnalyzer.HBHENChannelBasicCheck();
    myHBHEAnalyzer.PlottingHBFEtoGeo(myHBFrontEnd,myHBGeometry);
    myHBHEAnalyzer.PlottingHBFEtoBEVME(myHBFrontEnd,myHBBackEnd);
    myHBHEAnalyzer.PlottingHEFEtoGeo(myHEFrontEnd,myHEGeometry);
    myHBHEAnalyzer.PlottingHEFEtoBEVME(myHEFrontEnd,myHEBackEnd);

    myHFAnalyzer.HFNChannelBasicCheck();
    myHFAnalyzer.PlottingHFFEtoGeo(myHFFrontEnd,myHFGeometry);
    myHFAnalyzer.PlottingHFFEtoBEVME(myHFFrontEnd,myHFBackEnd);
    return 1;
  }
  else if( RunMode == "HBHEHFuTCA" )
  {
    std::string txtfilename = "officialMap/HCALmapHBEF_G_uHTR.txt";
    int NChannel = HCALLMapLoader::GetHBHEHFromLMap(
                                                    txtfilename,
                                                    myHBFrontEnd, myHBBackEnd, myHBPMTBox, myHBGeometry, myHBTriggerTower,
                                                    myHEFrontEnd, myHEBackEnd, myHEPMTBox, myHEGeometry, myHETriggerTower,
                                                    myHFFrontEnd, myHFBackEnd, myHFPMTBox, myHFGeometry, myHFTriggerTower
                                                   );
    HBHEAnalyzer myHBHEAnalyzer;
    HFAnalyzer myHFAnalyzer;

    if(NChannel == myHBHEAnalyzer.NchHBHE_all + myHFAnalyzer.NchHF_all){ std::cout << "#The number of channels we get from Lmap text file equals to the Number of channel we expected, Good!" << std::endl; }
    else{ std::cout << "#We have " << NChannel << " channels from txt Lmap while we have " << myHBHEAnalyzer.NchHBHE_all + myHFAnalyzer.NchHF_all << " channels expected in HBHEHF, something must be wrong!" << std::endl; return -1; }

    myHBHEAnalyzer.HBHENChannelBasicCheck();
    myHBHEAnalyzer.PlottingHBFEtoGeo(myHBFrontEnd,myHBGeometry);
    myHBHEAnalyzer.PlottingHBFEtoBEuTCA(myHBFrontEnd,myHBBackEnd);
    myHBHEAnalyzer.PlottingHEFEtoGeo(myHEFrontEnd,myHEGeometry);
    myHBHEAnalyzer.PlottingHEFEtoBEuTCA(myHEFrontEnd,myHEBackEnd);

    myHFAnalyzer.HFNChannelBasicCheck();
    myHFAnalyzer.PlottingHFFEtoGeo(myHFFrontEnd,myHFGeometry);
    myHFAnalyzer.PlottingHFFEtoBEuTCA(myHFFrontEnd,myHFBackEnd);

    //HCALLMapDumper::printHFLMapObject(myHFFrontEnd, myHFBackEnd, myHFPMTBox, myHFGeometry, myHFTriggerTower);
    return 1;
  }
  else if( RunMode == "HOVME" )
  {
    HOAnalyzer myHOAnalyzer;
    std::string txtfilename = "officialMap/HCALmapHO_G.txt";
    int NChannel = HCALLMapLoader::GetHOFromLMap(txtfilename, myHOFrontEnd, myHOBackEnd, myHOPMTBox, myHOGeometry, myHOTriggerTower);
    if(NChannel == myHOAnalyzer.NchHO_all){ std::cout << "#The number of channels we get from Lmap text file equals to the Number of channel we expected, Good!" << std::endl; }
    else{ std::cout << "#We have " << NChannel << " channels from txt Lmap while we have " << myHOAnalyzer.NchHO_all << " channels expected in HO, something must be wrong!" << std::endl; return -1; }

    myHOAnalyzer.HONChannelBasicCheck();
    myHOAnalyzer.PlottingHOFEtoGeo(myHOFrontEnd,myHOGeometry);
    myHOAnalyzer.PlottingHOFEtoBEVME(myHOFrontEnd,myHOBackEnd);
    return 1;
  }
  else{ std::cout << "#Invalide Run Mode, the the fuck is going on!" << std::endl; return -1; }

  return 0;
}

