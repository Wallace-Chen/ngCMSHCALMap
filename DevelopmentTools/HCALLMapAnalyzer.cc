#include <sstream>
#include <fstream>

#include "HCALMappingObject.h"

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
    //std::string name;
    //int var1, var2, var3;
    HOFrontEnd thisHOFrontEnd;
    HOBackEnd thisHOBackEnd;
    HOPMTBox thisHOPMTBox;
    HOGeometry thisHOGeometry;
    HOTriggerTower thisHOTriggerTower;
    
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

    myHOFrontEnd.push_back(thisHOFrontEnd);
    myHOBackEnd.push_back(thisHOBackEnd);
    myHOPMTBox.push_back(thisHOPMTBox);
    myHOGeometry.push_back(thisHOGeometry);
    myHOTriggerTower.push_back(thisHOTriggerTower);
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

  std::string txtfliename;
  if( RunMode == "HBHEHFVME" ) txtfliename = "officialMap/HCALmapHBEF_G.txt";
  else if( RunMode == "HBHEHFuTCA" ) txtfliename = "officialMap/HCALmapHBEF_G_uHTR.txt";
  else if( RunMode == "HOVME" ) txtfliename = "officialMap/HCALmapHO_G.txt";
  else { std::cout << "Invalid run mode! what the fuck is going on!!!" << std::cout; return -2; }

  //initialize the variables we need in analysis
  std::vector<HBFrontEnd> myHBFrontEnd;
  std::vector<HEFrontEnd> myHEFrontEnd;
  std::vector<HFFrontEnd> myHFFrontEnd;
  std::vector<HOFrontEnd> myHOFrontEnd;

  std::vector<HBBackEnd> myHBBackEnd;
  std::vector<HEBackEnd> myHEBackEnd;
  std::vector<HFBackEnd> myHFBackEnd;
  std::vector<HOBackEnd> myHOBackEnd;

  std::vector<HBPMTBox> myHBPMTBox;
  std::vector<HEPMTBox> myHEPMTBox;
  std::vector<HFPMTBox> myHFPMTBox;
  std::vector<HOPMTBox> myHOPMTBox;

  std::vector<HBGeometry> myHBGeometry;
  std::vector<HEGeometry> myHEGeometry;
  std::vector<HFGeometry> myHFGeometry;
  std::vector<HOGeometry> myHOGeometry;

  std::vector<HBTriggerTower> myHBTriggerTower;
  std::vector<HETriggerTower> myHETriggerTower;
  std::vector<HFTriggerTower> myHFTriggerTower;
  std::vector<HOTriggerTower> myHOTriggerTower;

  //#side eta phi dphi depth det rbx wedge rm pixel qie adc rm_fi fi_ch crate htr fpga htr_fi dcc_sl spigo dcc slb slbin slbin2 slnam rctcra rctcar rctcon rctnam fedid QIEId

  if( RunMode == "HBHEHFVME" )
  {

  }
  else if( RunMode == "HBHEHFuTCA" )
  {

  }
  else if( RunMode == "HOVME" )
  {
    int NChannel = GetHOFromLMap(txtfliename, myHOFrontEnd, myHOBackEnd, myHOPMTBox, myHOGeometry, myHOTriggerTower);
    std::cout << "How many Channels do we have in HO ? " << NChannel << std::endl;
    std::cout << "Re-calculate from Front End: " << (HOAnalyzer::NrbxHO0*HOAnalyzer::NrmHO0 + HOAnalyzer::NrbxHO12*HOAnalyzer::NrmHO12) * HOAnalyzer::Nrm_fiber * HOAnalyzer::Nfiber_ch << std::endl;
    std::cout << "Re-calculate from Back End: " << HOAnalyzer::Ncrate * HOAnalyzer::Nhtr * HOAnalyzer::Nfpga * HOAnalyzer::Nhtr_fiber * HOAnalyzer::Nfiber_ch + HOAnalyzer::NspecialHOX << std::endl;
    std::cout << "Re-calculate from Geometry: " << HOAnalyzer::NHOside * HOAnalyzer::NHOeta * HOAnalyzer::NHOphi * HOAnalyzer::NHOdepth + HOAnalyzer::NnormalHOX + HOAnalyzer::NspecialHOX << std::endl;

    HOAnalyzer::PlottingHOFEtoGeo(myHOFrontEnd,myHOGeometry);
    //HOAnalyzer::PlottingHOFEtoBE(myHOFrontEnd,myHOBackEnd);
  }

  return 0;
}

