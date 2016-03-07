#include <sstream>
#include <fstream>

#include "HBHEAnalyzer.h"
#include "HFAnalyzer.h"
#include "HOAnalyzer.h"

int GetHBHEHFromVMELMap(
                        std::string LMapFileName,
                        std::vector<HBFrontEnd> &myHBFrontEnd, std::vector<HBBackEnd> &myHBBackEnd, std::vector<HBPMTBox> &myHBPMTBox, std::vector<HBGeometry> &myHBGeometry, std::vector<HBTriggerTower> &myHBTriggerTower,
                        std::vector<HEFrontEnd> &myHEFrontEnd, std::vector<HEBackEnd> &myHEBackEnd, std::vector<HEPMTBox> &myHEPMTBox, std::vector<HEGeometry> &myHEGeometry, std::vector<HETriggerTower> &myHETriggerTower,
                        std::vector<HFFrontEnd> &myHFFrontEnd, std::vector<HFBackEnd> &myHFBackEnd, std::vector<HFPMTBox> &myHFPMTBox, std::vector<HFGeometry> &myHFGeometry, std::vector<HFTriggerTower> &myHFTriggerTower
                       )
{
  int NChannel = 0;

  std::ifstream inputFile(LMapFileName.c_str());

  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;

    NChannel++;
    if(line.find("HB") != std::string::npos)
    {
      std::istringstream ss(line);
      HBFrontEnd thisHBFrontEnd; HBBackEnd thisHBBackEnd; HBPMTBox thisHBPMTBox; HBGeometry thisHBGeometry; HBTriggerTower thisHBTriggerTower;

      int tmp;
      std::string tmp_str;
      //#side eta phi dphi depth det 
      //rbx wedge rm pixel qie adc rm_fi fi_ch 
      //crate htr fpga htr_fi dcc_sl spigo dcc 
      //slb slbin slbin2 slnam rctcra rctcar rctcon rctnam 
      //fedid 
      //QIEId
      ss >> tmp
         >> thisHBGeometry.side >> thisHBGeometry.eta >> thisHBGeometry.phi >> thisHBGeometry.dphi >> thisHBGeometry.depth >> thisHBGeometry.subdet
         >> thisHBFrontEnd.rbx >> thisHBPMTBox.wedge >> thisHBFrontEnd.rm >> thisHBPMTBox.pixel >> thisHBFrontEnd.qie8 >> thisHBFrontEnd.qie8_ch >> thisHBFrontEnd.rm_fiber >> thisHBFrontEnd.fiber_ch
         >> thisHBBackEnd.crate >> thisHBBackEnd.htr >> thisHBBackEnd.fpga >> thisHBBackEnd.htr_fiber >> thisHBBackEnd.dcc_sl >> thisHBBackEnd.spigot >> thisHBBackEnd.dcc 
         >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
         >> thisHBBackEnd.fedid
         >> thisHBFrontEnd.qie8id;

      thisHBBackEnd.fiber_ch = thisHBFrontEnd.fiber_ch;

      myHBFrontEnd.push_back(thisHBFrontEnd); myHBBackEnd.push_back(thisHBBackEnd); myHBPMTBox.push_back(thisHBPMTBox); myHBGeometry.push_back(thisHBGeometry); myHBTriggerTower.push_back(thisHBTriggerTower);
    }
    else if(line.find("HE") != std::string::npos)
    {
      std::istringstream ss(line);
      HEFrontEnd thisHEFrontEnd; HEBackEnd thisHEBackEnd; HEPMTBox thisHEPMTBox; HEGeometry thisHEGeometry; HETriggerTower thisHETriggerTower;

      int tmp;
      std::string tmp_str;
      ss >> tmp
         >> thisHEGeometry.side >> thisHEGeometry.eta >> thisHEGeometry.phi >> thisHEGeometry.dphi >> thisHEGeometry.depth >> thisHEGeometry.subdet
         >> thisHEFrontEnd.rbx >> thisHEPMTBox.wedge >> thisHEFrontEnd.rm >> thisHEPMTBox.pixel >> thisHEFrontEnd.qie8 >> thisHEFrontEnd.qie8_ch >> thisHEFrontEnd.rm_fiber >> thisHEFrontEnd.fiber_ch
         >> thisHEBackEnd.crate >> thisHEBackEnd.htr >> thisHEBackEnd.fpga >> thisHEBackEnd.htr_fiber >> thisHEBackEnd.dcc_sl >> thisHEBackEnd.spigot >> thisHEBackEnd.dcc
         >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
         >> thisHEBackEnd.fedid
         >> thisHEFrontEnd.qie8id;

      thisHEBackEnd.fiber_ch = thisHEFrontEnd.fiber_ch;

      myHEFrontEnd.push_back(thisHEFrontEnd); myHEBackEnd.push_back(thisHEBackEnd); myHEPMTBox.push_back(thisHEPMTBox); myHEGeometry.push_back(thisHEGeometry); myHETriggerTower.push_back(thisHETriggerTower);
    }
    else if(line.find("HF") != std::string::npos)
    {
      std::istringstream ss(line);
      HFFrontEnd thisHFFrontEnd; HFBackEnd thisHFBackEnd; HFPMTBox thisHFPMTBox; HFGeometry thisHFGeometry; HFTriggerTower thisHFTriggerTower;

      int tmp;
      std::string tmp_str;
      ss >> tmp
         >> thisHFGeometry.side >> thisHFGeometry.eta >> thisHFGeometry.phi >> thisHFGeometry.dphi >> thisHFGeometry.depth >> thisHFGeometry.subdet
         >> thisHFFrontEnd.rbx >> thisHFPMTBox.wedge >> thisHFFrontEnd.rm >> thisHFPMTBox.pixel >> thisHFFrontEnd.qie8 >> thisHFFrontEnd.qie8_ch >> thisHFFrontEnd.rm_fiber >> thisHFFrontEnd.fiber_ch
         >> thisHFBackEnd.crate >> thisHFBackEnd.htr >> thisHFBackEnd.fpga >> thisHFBackEnd.htr_fiber >> thisHFBackEnd.dcc_sl >> thisHFBackEnd.spigot >> thisHFBackEnd.dcc
         >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
         >> thisHFBackEnd.fedid
         >> thisHFFrontEnd.qie8id;

      thisHFBackEnd.fiber_ch = thisHFFrontEnd.fiber_ch;

      myHFFrontEnd.push_back(thisHFFrontEnd); myHFBackEnd.push_back(thisHFBackEnd); myHFPMTBox.push_back(thisHFPMTBox); myHFGeometry.push_back(thisHFGeometry); myHFTriggerTower.push_back(thisHFTriggerTower);
    }
    else { std::cout << "We are looping over HBEF map but did not find the tag for HBHEHF!! Suck on that!" << std::endl; return -2; }
  }
  return NChannel;
}

int GetHOFromLMap(
                  std::string LMapFileName, 
                  std::vector<HOFrontEnd> &myHOFrontEnd, std::vector<HOBackEnd> &myHOBackEnd, std::vector<HOPMTBox> &myHOPMTBox, std::vector<HOGeometry> &myHOGeometry, std::vector<HOTriggerTower> &myHOTriggerTower
                 )
{
  int NChannel = 0;
  std::ifstream inputFile(LMapFileName.c_str());

  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;

    NChannel++;

    std::istringstream ss(line);
    //std::cout << line << std::endl;
    HOFrontEnd thisHOFrontEnd; HOBackEnd thisHOBackEnd; HOPMTBox thisHOPMTBox; HOGeometry thisHOGeometry; HOTriggerTower thisHOTriggerTower;
    
    //#side eta phi dphi depth det 
    //rbx sector rm pixel qie adc rm_fi fi_ch let_code 
    //crate block_coupler htr fpga htr_fi dcc_sl spigo dcc fedid 
    //QIEId
    int tmp;

    ss >> tmp
       >> thisHOGeometry.side >> thisHOGeometry.eta >> thisHOGeometry.phi >> thisHOGeometry.dphi >> thisHOGeometry.depth >> thisHOGeometry.subdet
       >> thisHOFrontEnd.rbx >> thisHOPMTBox.sector >> thisHOFrontEnd.rm >> thisHOPMTBox.pixel >> thisHOFrontEnd.qie8 >> thisHOFrontEnd.qie8_ch >> thisHOFrontEnd.rm_fiber >> thisHOFrontEnd.fiber_ch >> thisHOPMTBox.letter_code
       >> thisHOBackEnd.crate >> thisHOBackEnd.block_coupler >> thisHOBackEnd.htr >> thisHOBackEnd.fpga >> thisHOBackEnd.htr_fiber >> thisHOBackEnd.dcc_sl >> thisHOBackEnd.spigot >> thisHOBackEnd.dcc >> thisHOBackEnd.fedid 
       >> thisHOFrontEnd.qie8id;

    thisHOBackEnd.fiber_ch = thisHOFrontEnd.fiber_ch;
    //std::cout << thisHOGeometry.eta << std::endl;

    myHOFrontEnd.push_back(thisHOFrontEnd); myHOBackEnd.push_back(thisHOBackEnd); myHOPMTBox.push_back(thisHOPMTBox); myHOGeometry.push_back(thisHOGeometry); myHOTriggerTower.push_back(thisHOTriggerTower);
  }

  return NChannel;
}

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give at least 1 argument " << "RunMode " << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./HCALLMapAnalyzer RunMode" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::cout << "The valid run modes are: HBHEHFVME, HBHEHFuTCA, HOVME" << std::endl;
  std::cout << "The run mode we have right now is: " << RunMode << std::endl;

  //initialize the variables we need in analysis
  std::vector<HBFrontEnd> myHBFrontEnd; std::vector<HBBackEnd> myHBBackEnd; std::vector<HBPMTBox> myHBPMTBox; std::vector<HBGeometry> myHBGeometry; std::vector<HBTriggerTower> myHBTriggerTower;
  std::vector<HEFrontEnd> myHEFrontEnd; std::vector<HEBackEnd> myHEBackEnd; std::vector<HEPMTBox> myHEPMTBox; std::vector<HEGeometry> myHEGeometry; std::vector<HETriggerTower> myHETriggerTower;
  std::vector<HFFrontEnd> myHFFrontEnd; std::vector<HFBackEnd> myHFBackEnd; std::vector<HFPMTBox> myHFPMTBox; std::vector<HFGeometry> myHFGeometry; std::vector<HFTriggerTower> myHFTriggerTower;
  std::vector<HOFrontEnd> myHOFrontEnd; std::vector<HOBackEnd> myHOBackEnd; std::vector<HOPMTBox> myHOPMTBox; std::vector<HOGeometry> myHOGeometry; std::vector<HOTriggerTower> myHOTriggerTower;
  
  if( RunMode == "HBHEHFVME" )
  {
    std::string txtfilename = "officialMap/HCALmapHBEF_G.txt";
    int NChannel = GetHBHEHFromVMELMap(
                                       txtfilename,
                                       myHBFrontEnd, myHBBackEnd, myHBPMTBox, myHBGeometry, myHBTriggerTower,
                                       myHEFrontEnd, myHEBackEnd, myHEPMTBox, myHEGeometry, myHETriggerTower,
                                       myHFFrontEnd, myHFBackEnd, myHFPMTBox, myHFGeometry, myHFTriggerTower
                                      );
    //int HFsize = myHFFrontEnd.size();
    //for(int i=0;i<HFsize;i++){  /*if(myHFFrontEnd.at(i).rbx == "HFP01")*/ std::cout << myHFFrontEnd.at(i).rbx << "," << myHFFrontEnd.at(i).rm << "," << myHFFrontEnd.at(i).rm_fiber << "," << myHFFrontEnd.at(i).fiber_ch << std::endl; }    
    
    if(NChannel == HBHEAnalyzer::NchHBHE_all + HFAnalyzer::NchHF_all){ std::cout << "The number of channels we get from Lmap text file equals to the Number of channel we expected, Good!" << std::endl; }
    else{ std::cout << "We have " << NChannel << " channels from txt Lmap while we have " << HBHEAnalyzer::NchHBHE_all + HFAnalyzer::NchHF_all << " channels expected in HBHEHF, something must be wrong!" << std::endl; return -1; }

    std::cout << "How many Channels do we have in HBHE ? " << HBHEAnalyzer::NchHBHE_all << std::endl;
    std::cout << "Re-calculate from Front End: " << 2 * (HBHEAnalyzer::NrbxHB * HBHEAnalyzer::NrmHB + HBHEAnalyzer::NrbxHE * HBHEAnalyzer::NrmHE) * HBHEAnalyzer::Nrm_fiber * HBHEAnalyzer::Nfiber_ch << std::endl;
    std::cout << "Re-calculate from Back End: " << HBHEAnalyzer::Ncrate * HBHEAnalyzer::Nhtr * HBHEAnalyzer::Nfpga * HBHEAnalyzer::Nhtr_fiber * HBHEAnalyzer::Nfiber_ch << std::endl;
    //std::cout << "Re-calculate from Geometry: " << HBHEAnalyzer::NHBHEside * (HBHEAnalyzer::NHBeta1to14 * HBHEAnalyzer::NHBdeptheta1to14 + HBHEAnalyzer::NHBeta1516 * HBHEAnalyzer::NHBdeptheta1516 + ) * HBHEAnalyzer::NHBHEphi << std::endl;

    HBHEAnalyzer::PlottingHBFEtoGeo(myHBFrontEnd,myHBGeometry);
    HBHEAnalyzer::PlottingHBFEtoBEVME(myHBFrontEnd,myHBBackEnd);
    HBHEAnalyzer::PlottingHEFEtoGeo(myHEFrontEnd,myHEGeometry);
    HBHEAnalyzer::PlottingHEFEtoBEVME(myHEFrontEnd,myHEBackEnd);

    std::cout << "How many Channels do we have in HF ? " << HFAnalyzer::NchHF_all << std::endl;
    std::cout << "Re-calculate from Front End: " << 2 * HFAnalyzer::NrbxHF * HFAnalyzer::NrmHF * HFAnalyzer::Nrm_fiber * HFAnalyzer::Nfiber_ch << std::endl;
    std::cout << "Re-calculate from Back End: " << HFAnalyzer::Ncrate * HFAnalyzer::Nhtr * HFAnalyzer::Nfpga * HFAnalyzer::Nhtr_fiber * HFAnalyzer::Nfiber_ch << std::endl;
    std::cout << "Re-calculate from Geometry: " << HFAnalyzer::NHFside * (HFAnalyzer::NHFetadphi2 * HFAnalyzer::NHFphidphi2 + HFAnalyzer::NHFetadphi4 * HFAnalyzer::NHFphidphi4) * HFAnalyzer::NHFdepth << std::endl;

    HFAnalyzer::PlottingHFFEtoGeo(myHFFrontEnd,myHFGeometry);
    HFAnalyzer::PlottingHFFEtoBEVME(myHFFrontEnd,myHFBackEnd);
  }
  else if( RunMode == "HBHEHFuTCA" )
  {
    std::string txtfilename = "officialMap/HCALmapHBEF_G_uHTR.txt";

    //HBHEAnalyzer::PlottingHBFEtoGeo(myHBFrontEnd,myHBGeometry);
    //HBHEAnalyzer::PlottingHBFEtoBEuTCA(myHBFrontEnd,myHBBackEnd);
    //HBHEAnalyzer::PlottingHEFEtoGeo(myHEFrontEnd,myHEGeometry);
    //HBHEAnalyzer::PlottingHEFEtoBEuTCA(myHEFrontEnd,myHEBackEnd);

    //HFAnalyzer::PlottingHFFEtoGeo(myHFFrontEnd,myHFGeometry);
    //HFAnalyzer::PlottingHFFEtoBEuTCA(myHFFrontEnd,myHFBackEnd);
  }
  else if( RunMode == "HOVME" )
  {
    std::string txtfilename = "officialMap/HCALmapHO_G.txt";
    int NChannel = GetHOFromLMap(txtfilename, myHOFrontEnd, myHOBackEnd, myHOPMTBox, myHOGeometry, myHOTriggerTower);
    if(NChannel == HOAnalyzer::NchHO_all){ std::cout << "The number of channels we get from Lmap text file equals to the Number of channel we expected, Good!" << std::endl; }
    else{ std::cout << "We have " << NChannel << " channels from txt Lmap while we have " << HOAnalyzer::NchHO_all << " channels expected in HO, something must be wrong!" << std::endl; return -1; }
    std::cout << "How many Channels do we have in HO ? " << HOAnalyzer::NchHO_all << std::endl;
    std::cout << "Re-calculate from Front End: " << (HOAnalyzer::NrbxHO0*HOAnalyzer::NrmHO0 + HOAnalyzer::NrbxHO12*HOAnalyzer::NrmHO12) * HOAnalyzer::Nrm_fiber * HOAnalyzer::Nfiber_ch << std::endl;
    std::cout << "Re-calculate from Back End: " << HOAnalyzer::Ncrate * HOAnalyzer::Nhtr * HOAnalyzer::Nfpga * HOAnalyzer::Nhtr_fiber * HOAnalyzer::Nfiber_ch + HOAnalyzer::NspecialHOX << std::endl;
    std::cout << "Re-calculate from Geometry: " << HOAnalyzer::NHOside * HOAnalyzer::NHOeta * HOAnalyzer::NHOphi * HOAnalyzer::NHOdepth + HOAnalyzer::NnormalHOX + HOAnalyzer::NspecialHOX << std::endl;

    HOAnalyzer::PlottingHOFEtoGeo(myHOFrontEnd,myHOGeometry);
    HOAnalyzer::PlottingHOFEtoBEVME(myHOFrontEnd,myHOBackEnd);
  }
  else{ std::cout << "Invalide Run Mode, the the fuck is going on!" << std::endl; return -1; }

  return 0;
}

