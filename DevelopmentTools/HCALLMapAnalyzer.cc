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
  std::cout << "#The valid run modes are: HBHEHFVME, HBHEHFuTCA, HOVME ngHEuTCA ngHFuTCA" << std::endl;
  std::cout << "#The run mode we have right now is: " << RunMode << std::endl;

  HCALLMapLoader myHCALLMapLoader;
  HCALLMapDumper myHCALLMapDumper;

  //initialize the variables we need in analysis
  std::vector<HBFrontEnd> myHBFrontEnd; std::vector<HBBackEnd> myHBBackEnd; std::vector<HBHPD> myHBHPD; std::vector<HBGeometry> myHBGeometry; std::vector<HBTriggerTower> myHBTriggerTower;
  std::vector<HEFrontEnd> myHEFrontEnd; std::vector<HEBackEnd> myHEBackEnd; std::vector<HEHPD> myHEHPD; std::vector<HEGeometry> myHEGeometry; std::vector<HETriggerTower> myHETriggerTower;
  std::vector<ngHEFrontEnd> myngHEFrontEnd; std::vector<ngHEBackEnd> myngHEBackEnd; std::vector<ngHESiPM> myngHESiPM; std::vector<ngHEGeometry> myngHEGeometry; std::vector<ngHETriggerTower> myngHETriggerTower;
  std::vector<HFFrontEnd> myHFFrontEnd; std::vector<HFBackEnd> myHFBackEnd; std::vector<HFPMTBox> myHFPMTBox; std::vector<HFGeometry> myHFGeometry; std::vector<HFTriggerTower> myHFTriggerTower;
  std::vector<ngHFFrontEnd> myngHFFrontEnd; std::vector<ngHFBackEnd> myngHFBackEnd; std::vector<ngHFPMTBox> myngHFPMTBox; std::vector<ngHFGeometry> myngHFGeometry; std::vector<ngHFTriggerTower> myngHFTriggerTower;
  std::vector<HOFrontEnd> myHOFrontEnd; std::vector<HOBackEnd> myHOBackEnd; std::vector<HOSiPM> myHOSiPM; std::vector<HOGeometry> myHOGeometry; std::vector<HOTriggerTower> myHOTriggerTower;
  
  if( RunMode == "HBHEHFVME" )
  {
    std::string txtfilename = "officialMap/HCALmapHBEF_G.txt";
    int NChannel = myHCALLMapLoader.GetHBHEHFromLMap(
                                                     txtfilename,
                                                     myHBFrontEnd, myHBBackEnd, myHBHPD, myHBGeometry, myHBTriggerTower,
                                                     myHEFrontEnd, myHEBackEnd, myHEHPD, myHEGeometry, myHETriggerTower,
                                                     myHFFrontEnd, myHFBackEnd, myHFPMTBox, myHFGeometry, myHFTriggerTower
                                                    );
    HBAnalyzer myHBAnalyzer;
    HEAnalyzer myHEAnalyzer;
    HFAnalyzer myHFAnalyzer;

    if(NChannel == myHBAnalyzer.NchHB_all + myHEAnalyzer.NchHE_all + myHFAnalyzer.NchHF_all){ std::cout << "#The number of channels we get from Lmap text file equals to the Number of channel we expected, Good!" << std::endl; }
    else{ std::cout << "#We have " << NChannel << " channels from txt Lmap while we have " << myHBAnalyzer.NchHB_all + myHEAnalyzer.NchHE_all + myHFAnalyzer.NchHF_all << " channels expected in HBHEHF, something must be wrong!" << std::endl; return -1; }

    myHBAnalyzer.HBNChannelBasicCheck();
    myHBAnalyzer.PlottingHBFEtoGeo(myHBFrontEnd,myHBGeometry);
    myHBAnalyzer.PlottingHBFEtoBEVME(myHBFrontEnd,myHBBackEnd);

    myHEAnalyzer.HENChannelBasicCheck();
    myHEAnalyzer.PlottingHEFEtoGeo(myHEFrontEnd,myHEGeometry);
    myHEAnalyzer.PlottingHEFEtoBEVME(myHEFrontEnd,myHEBackEnd);

    myHFAnalyzer.HFNChannelBasicCheck();
    myHFAnalyzer.PlottingHFFEtoGeo(myHFFrontEnd,myHFGeometry);
    myHFAnalyzer.PlottingHFFEtoBEVME(myHFFrontEnd,myHFBackEnd);
    return 1;
  }
  else if( RunMode == "HBHEHFuTCA" )
  {
    std::string txtfilename = "officialMap/HCALmapHBEF_G_uHTR.txt";
    int NChannel = myHCALLMapLoader.GetHBHEHFromLMap(
                                                     txtfilename,
                                                     myHBFrontEnd, myHBBackEnd, myHBHPD, myHBGeometry, myHBTriggerTower,
                                                     myHEFrontEnd, myHEBackEnd, myHEHPD, myHEGeometry, myHETriggerTower,
                                                     myHFFrontEnd, myHFBackEnd, myHFPMTBox, myHFGeometry, myHFTriggerTower
                                                    );
    HBAnalyzer myHBAnalyzer;
    HEAnalyzer myHEAnalyzer;
    HFAnalyzer myHFAnalyzer;

    if(NChannel == myHBAnalyzer.NchHB_all + myHEAnalyzer.NchHE_all + myHFAnalyzer.NchHF_all){ std::cout << "#The number of channels we get from Lmap text file equals to the Number of channel we expected, Good!" << std::endl; }
    else{ std::cout << "#We have " << NChannel << " channels from txt Lmap while we have " << myHBAnalyzer.NchHB_all + myHEAnalyzer.NchHE_all + myHFAnalyzer.NchHF_all << " channels expected in HBHEHF, something must be wrong!" << std::endl; return -1; }

    myHBAnalyzer.HBNChannelBasicCheck();
    myHBAnalyzer.PlottingHBFEtoGeo(myHBFrontEnd,myHBGeometry);
    myHBAnalyzer.PlottingHBFEtoBEuTCA(myHBFrontEnd,myHBBackEnd);

    myHEAnalyzer.HENChannelBasicCheck();
    myHEAnalyzer.PlottingHEFEtoGeo(myHEFrontEnd,myHEGeometry);
    myHEAnalyzer.PlottingHEFEtoBEuTCA(myHEFrontEnd,myHEBackEnd);

    myHFAnalyzer.HFNChannelBasicCheck();
    myHFAnalyzer.PlottingHFFEtoGeo(myHFFrontEnd,myHFGeometry);
    myHFAnalyzer.PlottingHFFEtoBEuTCA(myHFFrontEnd,myHFBackEnd);
    return 1;
  }
  else if( RunMode == "HOVME" )
  {
    HOAnalyzer myHOAnalyzer;
    std::string txtfilename = "officialMap/HCALmapHO_G.txt";
    int NChannel = myHCALLMapLoader.GetHOFromLMap(txtfilename, myHOFrontEnd, myHOBackEnd, myHOSiPM, myHOGeometry, myHOTriggerTower);
    if(NChannel == myHOAnalyzer.NchHO_all){ std::cout << "#The number of channels we get from Lmap text file equals to the Number of channel we expected, Good!" << std::endl; }
    else{ std::cout << "#We have " << NChannel << " channels from txt Lmap while we have " << myHOAnalyzer.NchHO_all << " channels expected in HO, something must be wrong!" << std::endl; return -1; }

    myHOAnalyzer.HONChannelBasicCheck();
    myHOAnalyzer.PlottingHOFEtoGeo(myHOFrontEnd,myHOGeometry);
    myHOAnalyzer.PlottingHOFEtoBEVME(myHOFrontEnd,myHOBackEnd);
    return 1;
  }
  else if( RunMode == "ngHEuTCA" )
  {
    std::string txtfilename = "officialMap/ngHELMap_v0.txt";
    int NChannel = myHCALLMapLoader.GetngHEromLMap(
                                                   txtfilename,
                                                   myngHEFrontEnd, myngHEBackEnd, myngHESiPM, myngHEGeometry, myngHETriggerTower
                                                  );

    ngHEAnalyzer myngHEAnalyzer;
    myngHEAnalyzer.PlottingngHEFEtoGeo(myngHEFrontEnd, myngHEGeometry);
    myngHEAnalyzer.PlottingngHEFEtoBEuTCA(myngHEFrontEnd,myngHEBackEnd);
    myngHEAnalyzer.PlottingngHEBEuTCAtoGeo(myngHEBackEnd, myngHEGeometry);
    return 1;
  }
  else if( RunMode == "ngHFuTCA" )
  {
    std::string txtfilename = "officialMap/ngHF2017LMap_20170505_pre06.txt";
    int NChannel = myHCALLMapLoader.GetngHFromLMap(
                                                   txtfilename,
                                                   myngHFFrontEnd, myngHFBackEnd, myngHFPMTBox, myngHFGeometry, myngHFTriggerTower
                                                  );

    ngHFAnalyzer myngHFAnalyzer;
    myngHFAnalyzer.PlottingngHFFEtoGeo(myngHFFrontEnd, myngHFGeometry);
    myngHFAnalyzer.PlottingngHFFEtoBEuTCA(myngHFFrontEnd,myngHFBackEnd);
    myngHFAnalyzer.PlottingngHFBEuTCAtoGeo(myngHFBackEnd, myngHFGeometry);
    return 1;
  }
  else{ std::cout << "#Invalide Run Mode, the the fuck is going on!" << std::endl; return -1; }

  return 0;
}
