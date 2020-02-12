#include "HCALLMapLoader.h"
#include <limits>

int HCALLMapLoader::GetHBHEHFromLMap(
                                     std::string LMapFileName,
                                     std::vector<HBFrontEnd> &myHBFrontEnd, std::vector<HBBackEnd> &myHBBackEnd, std::vector<HBHPD> &myHBHPD, std::vector<HBGeometry> &myHBGeometry, std::vector<HBTriggerTower> &myHBTriggerTower,
                                     std::vector<HEFrontEnd> &myHEFrontEnd, std::vector<HEBackEnd> &myHEBackEnd, std::vector<HEHPD> &myHEHPD, std::vector<HEGeometry> &myHEGeometry, std::vector<HETriggerTower> &myHETriggerTower,
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
      HBFrontEnd thisHBFrontEnd; HBBackEnd thisHBBackEnd; HBHPD thisHBHPD; HBGeometry thisHBGeometry; HBTriggerTower thisHBTriggerTower;

      int tmp;
      std::string tmp_str;
      //#side eta phi dphi depth det 
      //rbx wedge rm pixel qie adc rm_fi fi_ch 
      //crate htr fpga htr_fi dcc_sl spigo dcc 
      //slb slbin slbin2 slnam rctcra rctcar rctcon rctnam 
      //fedid 
      //QIEId
      if( LMapFileName.find("_uHTR") != std::string::npos )//loading uHTR variables
      {
        ss >> tmp
           >> thisHBGeometry.side >> thisHBGeometry.eta >> thisHBGeometry.phi >> thisHBGeometry.dphi >> thisHBGeometry.depth >> thisHBGeometry.subdet
           >> thisHBFrontEnd.rbx >> thisHBHPD.wedge >> thisHBFrontEnd.rm >> thisHBHPD.pixel >> thisHBFrontEnd.qie8 >> thisHBFrontEnd.qie8_ch >> thisHBFrontEnd.rm_fiber >> thisHBFrontEnd.fiber_ch
           >> thisHBBackEnd.ucrate >> thisHBBackEnd.uhtr >> thisHBBackEnd.ufpga >> thisHBBackEnd.uhtr_fiber >> thisHBBackEnd.dcc_sl >> thisHBBackEnd.spigot >> thisHBBackEnd.dcc
           >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
           >> thisHBBackEnd.ufedid
           >> thisHBFrontEnd.qie8_id;
      }
      else
      {
        ss >> tmp
           >> thisHBGeometry.side >> thisHBGeometry.eta >> thisHBGeometry.phi >> thisHBGeometry.dphi >> thisHBGeometry.depth >> thisHBGeometry.subdet
           >> thisHBFrontEnd.rbx >> thisHBHPD.wedge >> thisHBFrontEnd.rm >> thisHBHPD.pixel >> thisHBFrontEnd.qie8 >> thisHBFrontEnd.qie8_ch >> thisHBFrontEnd.rm_fiber >> thisHBFrontEnd.fiber_ch
           >> thisHBBackEnd.crate >> thisHBBackEnd.htr >> thisHBBackEnd.fpga >> thisHBBackEnd.htr_fiber >> thisHBBackEnd.dcc_sl >> thisHBBackEnd.spigot >> thisHBBackEnd.dcc 
           >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
           >> thisHBBackEnd.fedid
           >> thisHBFrontEnd.qie8_id;
      }
      thisHBBackEnd.fiber_ch = thisHBFrontEnd.fiber_ch;

      myHBFrontEnd.push_back(thisHBFrontEnd); myHBBackEnd.push_back(thisHBBackEnd); myHBHPD.push_back(thisHBHPD); myHBGeometry.push_back(thisHBGeometry); myHBTriggerTower.push_back(thisHBTriggerTower);
    }
    else if(line.find("HE") != std::string::npos)
    {
      std::istringstream ss(line);
      HEFrontEnd thisHEFrontEnd; HEBackEnd thisHEBackEnd; HEHPD thisHEHPD; HEGeometry thisHEGeometry; HETriggerTower thisHETriggerTower;

      int tmp;
      std::string tmp_str;
      if( LMapFileName.find("_uHTR") != std::string::npos )//loading uHTR variables
      {
        ss >> tmp
           >> thisHEGeometry.side >> thisHEGeometry.eta >> thisHEGeometry.phi >> thisHEGeometry.dphi >> thisHEGeometry.depth >> thisHEGeometry.subdet 
           >> thisHEFrontEnd.rbx >> thisHEHPD.wedge >> thisHEFrontEnd.rm >> thisHEHPD.pixel >> thisHEFrontEnd.qie8 >> thisHEFrontEnd.qie8_ch >> thisHEFrontEnd.rm_fiber >> thisHEFrontEnd.fiber_ch
           >> thisHEBackEnd.ucrate >> thisHEBackEnd.uhtr >> thisHEBackEnd.ufpga >> thisHEBackEnd.uhtr_fiber >> thisHEBackEnd.dcc_sl >> thisHEBackEnd.spigot >> thisHEBackEnd.dcc
           >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
           >> thisHEBackEnd.ufedid
           >> thisHEFrontEnd.qie8_id;
      }
      else
      {
        ss >> tmp
           >> thisHEGeometry.side >> thisHEGeometry.eta >> thisHEGeometry.phi >> thisHEGeometry.dphi >> thisHEGeometry.depth >> thisHEGeometry.subdet
           >> thisHEFrontEnd.rbx >> thisHEHPD.wedge >> thisHEFrontEnd.rm >> thisHEHPD.pixel >> thisHEFrontEnd.qie8 >> thisHEFrontEnd.qie8_ch >> thisHEFrontEnd.rm_fiber >> thisHEFrontEnd.fiber_ch
           >> thisHEBackEnd.crate >> thisHEBackEnd.htr >> thisHEBackEnd.fpga >> thisHEBackEnd.htr_fiber >> thisHEBackEnd.dcc_sl >> thisHEBackEnd.spigot >> thisHEBackEnd.dcc
           >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
           >> thisHEBackEnd.fedid
           >> thisHEFrontEnd.qie8_id;
      }
      thisHEBackEnd.fiber_ch = thisHEFrontEnd.fiber_ch;

      myHEFrontEnd.push_back(thisHEFrontEnd); myHEBackEnd.push_back(thisHEBackEnd); myHEHPD.push_back(thisHEHPD); myHEGeometry.push_back(thisHEGeometry); myHETriggerTower.push_back(thisHETriggerTower);
    }
    else if(line.find("HF") != std::string::npos)
    {
      std::istringstream ss(line);
      HFFrontEnd thisHFFrontEnd; HFBackEnd thisHFBackEnd; HFPMTBox thisHFPMTBox; HFGeometry thisHFGeometry; HFTriggerTower thisHFTriggerTower;

      int tmp;
      std::string tmp_str;

      if( LMapFileName.find("_uHTR") != std::string::npos )//loading uHTR variables
      {
        ss >> tmp
           >> thisHFGeometry.side >> thisHFGeometry.eta >> thisHFGeometry.phi >> thisHFGeometry.dphi >> thisHFGeometry.depth >> thisHFGeometry.subdet
           >> thisHFFrontEnd.rbx >> thisHFPMTBox.wedge >> thisHFFrontEnd.rm >> thisHFPMTBox.pixel >> thisHFFrontEnd.qie8 >> thisHFFrontEnd.qie8_ch >> thisHFFrontEnd.rm_fiber >> thisHFFrontEnd.fiber_ch
           >> thisHFBackEnd.ucrate >> thisHFBackEnd.uhtr >> thisHFBackEnd.ufpga >> thisHFBackEnd.uhtr_fiber >> thisHFBackEnd.dcc_sl >> thisHFBackEnd.spigot >> thisHFBackEnd.dcc
           >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
           >> thisHFBackEnd.ufedid
           >> thisHFFrontEnd.qie8_id;
      }
      else
      {
        ss >> tmp
           >> thisHFGeometry.side >> thisHFGeometry.eta >> thisHFGeometry.phi >> thisHFGeometry.dphi >> thisHFGeometry.depth >> thisHFGeometry.subdet
           >> thisHFFrontEnd.rbx >> thisHFPMTBox.wedge >> thisHFFrontEnd.rm >> thisHFPMTBox.pixel >> thisHFFrontEnd.qie8 >> thisHFFrontEnd.qie8_ch >> thisHFFrontEnd.rm_fiber >> thisHFFrontEnd.fiber_ch
           >> thisHFBackEnd.crate >> thisHFBackEnd.htr >> thisHFBackEnd.fpga >> thisHFBackEnd.htr_fiber >> thisHFBackEnd.dcc_sl >> thisHFBackEnd.spigot >> thisHFBackEnd.dcc
           >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
           >> thisHFBackEnd.fedid
           >> thisHFFrontEnd.qie8_id;
      }
      thisHFBackEnd.fiber_ch = thisHFFrontEnd.fiber_ch;

      myHFFrontEnd.push_back(thisHFFrontEnd); myHFBackEnd.push_back(thisHFBackEnd); myHFPMTBox.push_back(thisHFPMTBox); myHFGeometry.push_back(thisHFGeometry); myHFTriggerTower.push_back(thisHFTriggerTower);
    }
    else { std::cout << "#We are looping over HBEF map but did not find the tag for HBHEHF!! Suck on that!" << std::endl; return -2; }
  }
  return NChannel;
}

int HCALLMapLoader::GetHOFromLMap(
                                  std::string LMapFileName, 
                                  std::vector<HOFrontEnd> &myHOFrontEnd, std::vector<HOBackEnd> &myHOBackEnd, std::vector<HOSiPM> &myHOSiPM, std::vector<HOGeometry> &myHOGeometry, std::vector<HOTriggerTower> &myHOTriggerTower
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
    HOFrontEnd thisHOFrontEnd; HOBackEnd thisHOBackEnd; HOSiPM thisHOSiPM; HOGeometry thisHOGeometry; HOTriggerTower thisHOTriggerTower;
    
    //#side eta phi dphi depth det 
    //rbx sector rm pixel qie adc rm_fi fi_ch let_code 
    //crate block_coupler htr fpga htr_fi dcc_sl spigo dcc fedid 
    //QIEId
    int tmp;

    ss >> tmp
       >> thisHOGeometry.side >> thisHOGeometry.eta >> thisHOGeometry.phi >> thisHOGeometry.dphi >> thisHOGeometry.depth >> thisHOGeometry.subdet
       >> thisHOFrontEnd.rbx >> thisHOSiPM.sector >> thisHOFrontEnd.rm >> thisHOSiPM.pixel >> thisHOFrontEnd.qie8 >> thisHOFrontEnd.qie8_ch >> thisHOFrontEnd.rm_fiber >> thisHOFrontEnd.fiber_ch >> thisHOSiPM.letter_code
       >> thisHOBackEnd.crate >> thisHOBackEnd.block_coupler >> thisHOBackEnd.htr >> thisHOBackEnd.fpga >> thisHOBackEnd.htr_fiber >> thisHOBackEnd.dcc_sl >> thisHOBackEnd.spigot >> thisHOBackEnd.dcc >> thisHOBackEnd.fedid 
       >> thisHOFrontEnd.qie8_id;

    thisHOBackEnd.fiber_ch = thisHOFrontEnd.fiber_ch;
    //std::cout << thisHOGeometry.eta << std::endl;

    myHOFrontEnd.push_back(thisHOFrontEnd); myHOBackEnd.push_back(thisHOBackEnd); myHOSiPM.push_back(thisHOSiPM); myHOGeometry.push_back(thisHOGeometry); myHOTriggerTower.push_back(thisHOTriggerTower);
  }
  return NChannel;
}

int HCALLMapLoader::GetngHOFromLMap(
                                  std::string LMapFileName, 
                                  std::vector<ngHOFrontEnd> &myngHOFrontEnd, std::vector<ngHOBackEnd> &myngHOBackEnd, std::vector<ngHOSiPM> &myngHOSiPM, std::vector<ngHOGeometry> &myngHOGeometry, std::vector<ngHOTriggerTower> &myngHOTriggerTower,
				  std::vector<ngHOCalib> &myngHOCalib
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
    ngHOFrontEnd thisngHOFrontEnd; ngHOBackEnd thisngHOBackEnd; ngHOSiPM thisngHOSiPM; ngHOGeometry thisngHOGeometry; ngHOTriggerTower thisngHOTriggerTower;
    ngHOCalib thisngHOCalib;
    
    //#side, eta, phi, dphi, depth, det 
    //rbx, sector, pixel, let_code, qie8, qiech, rm, rm_fi, fi_ch
    //block_coupler, crate, htr, mtp, htr_fi, fedid 
    //QIEId
    //Tx_LC, TM_row, TM_col, TM_fib, TM_label

    ss >> thisngHOGeometry.side >> thisngHOGeometry.eta >> thisngHOGeometry.phi >> thisngHOGeometry.dphi >> thisngHOGeometry.depth >> thisngHOGeometry.subdet
       >> thisngHOFrontEnd.rbx >> thisngHOSiPM.sector >> thisngHOSiPM.pixel >> thisngHOSiPM.letter_code >> thisngHOFrontEnd.qie8 >> thisngHOFrontEnd.qie8_ch >> thisngHOFrontEnd.rm >> thisngHOFrontEnd.rm_fiber >> thisngHOFrontEnd.fiber_ch 
       >> thisngHOBackEnd.block_coupler >> thisngHOBackEnd.crate >> thisngHOBackEnd.htr >> thisngHOBackEnd.mtp >> thisngHOBackEnd.htr_fiber >> thisngHOBackEnd.fedid 
       >> thisngHOFrontEnd.qie8_id
       >> thisngHOTriggerTower.tx_lc >> thisngHOTriggerTower.tm_row >> thisngHOTriggerTower.tm_col >> thisngHOTriggerTower.tm_fib >> thisngHOTriggerTower.tm_label;

    thisngHOBackEnd.dodeca = 0;

    if(thisngHOGeometry.subdet == "CALIB_HO"){
//	thisngHOCalib.side = thisngHOGeometry.side; thisngHOCalib.eta = thisngHOGeometry.eta; thisngHOCalib.phi = thisngHOGeometry.phi; thisngHOCalib.dphi = thisngHOGeometry.dphi; thisngHOCalib.depth = thisngHOGeometry.depth; thisngHOCalib.subdet = thisngHOGeometry.subdet;
//	thisngHOCalib.rbx = thisngHOFrontEnd.rbx; thisngHOCalib.sector = thisngHOSiPM.sector; thisngHOCalib.pixel = thisngHOSiPM.pixel; thisngHOCalib.letter_code = thisngHOSiPM.letter_code; thisngHOCalib.qie8 = thisngHOFrontEnd.qie8; thisngHOCalib.qie8_ch = thisngHOFrontEnd.qie8_ch; thisngHOCalib.rm = thisngHOFrontEnd.rm; thisngHOCalib.rm_fiber = thisngHOFrontEnd.rm_fiber; thisngHOCalib.fiber_ch = thisngHOFrontEnd.fiber_ch;
//	thisngHOCalib.block_coupler = thisngHOBackEnd.block_coupler; thisngHOCalib.crate = thisngHOBackEnd.crate; thisngHOCalib.htr = thisngHOBackEnd.htr; thisngHOCalib.mtp = thisngHOBackEnd.mtp; thisngHOCalib.htr_fiber = thisngHOBackEnd.htr_fiber; thisngHOCalib.fedid = thisngHOBackEnd.fedid;
//	thisngHOCalib.qie8_id = thisngHOFrontEnd.qie8_id;
//	thisngHOCalib.dodeca = thisngHOCalib.htr_fiber % 12 + 1;
//	myngHOCalib.push_back(thisngHOCalib);
	;
    }else if(thisngHOGeometry.subdet == "HO"){
        myngHOFrontEnd.push_back(thisngHOFrontEnd); myngHOBackEnd.push_back(thisngHOBackEnd); myngHOSiPM.push_back(thisngHOSiPM); myngHOGeometry.push_back(thisngHOGeometry); myngHOTriggerTower.push_back(thisngHOTriggerTower);
    }
  }
  return NChannel;
}

int HCALLMapLoader::GetngHOCalibFromLMap(
                                  std::string LMapFileName, 
                                  std::vector<ngHOFrontEnd> &myngHOFrontEnd, std::vector<ngHOBackEnd> &myngHOBackEnd, std::vector<ngHOSiPM> &myngHOSiPM, std::vector<ngHOGeometry> &myngHOGeometry, std::vector<ngHOTriggerTower> &myngHOTriggerTower,
				  std::vector<ngHOCalib> &myngHOCalib
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
    ngHOFrontEnd thisngHOFrontEnd; ngHOBackEnd thisngHOBackEnd; ngHOSiPM thisngHOSiPM; ngHOGeometry thisngHOGeometry; ngHOTriggerTower thisngHOTriggerTower;
    ngHOCalib thisngHOCalib;
    
    //#side, eta, phi, dphi, depth, det 
    //rbx, sector, pixel, let_code, qie8, qiech, rm, rm_fi, fi_ch
    //block_coupler, crate, htr, mtp, htr_fi, fedid 
    //QIEId

    ss >> thisngHOCalib.side >> thisngHOCalib.eta >> thisngHOCalib.phi >> thisngHOCalib.dphi >> thisngHOCalib.depth >> thisngHOCalib.subdet
       >> thisngHOCalib.rbx >> thisngHOCalib.sector >> thisngHOCalib.pixel >> thisngHOCalib.letter_code >> thisngHOCalib.qie8 >> thisngHOCalib.qie8_ch >> thisngHOCalib.rm >> thisngHOCalib.rm_fiber >> thisngHOCalib.fiber_ch 
       >> thisngHOCalib.block_coupler >> thisngHOCalib.crate >> thisngHOCalib.htr >> thisngHOCalib.mtp >> thisngHOCalib.htr_fiber >> thisngHOCalib.fedid 
       >> thisngHOCalib.qie8_id;


    if(thisngHOCalib.subdet == "CALIB_HO"){
	thisngHOCalib.dodeca = thisngHOCalib.htr_fiber % 12 + 1;
	myngHOCalib.push_back(thisngHOCalib);
    }else if(thisngHOCalib.subdet == "HOX"){
	thisngHOGeometry.side = thisngHOCalib.side; thisngHOGeometry.eta = thisngHOCalib.eta; thisngHOGeometry.phi = thisngHOCalib.phi; thisngHOGeometry.dphi = thisngHOCalib.dphi; thisngHOGeometry.depth = thisngHOCalib.depth; thisngHOGeometry.subdet = thisngHOCalib.subdet;
	thisngHOFrontEnd.rbx = thisngHOCalib.rbx; thisngHOSiPM.sector = thisngHOCalib.sector; thisngHOSiPM.pixel = thisngHOCalib.pixel; thisngHOSiPM.letter_code = thisngHOCalib.letter_code; thisngHOFrontEnd.qie8 = thisngHOCalib.qie8; thisngHOFrontEnd.qie8_ch = thisngHOCalib.qie8_ch; thisngHOFrontEnd.rm = thisngHOCalib.rm; thisngHOFrontEnd.rm_fiber = thisngHOCalib.rm_fiber; thisngHOFrontEnd.fiber_ch = thisngHOCalib.fiber_ch;
	thisngHOBackEnd.block_coupler = thisngHOCalib.block_coupler; thisngHOBackEnd.crate = thisngHOCalib.crate; thisngHOBackEnd.htr = thisngHOCalib.htr; thisngHOBackEnd.mtp = thisngHOCalib.mtp; thisngHOBackEnd.htr_fiber = thisngHOCalib.htr_fiber; thisngHOBackEnd.fedid = thisngHOCalib.fedid;
	thisngHOFrontEnd.qie8_id = thisngHOCalib.qie8_id;
	thisngHOCalib.dodeca = 0;
        thisngHOTriggerTower.tx_lc = "";
	thisngHOTriggerTower.tm_row = "";
	thisngHOTriggerTower.tm_col = "";
	thisngHOTriggerTower.tm_fib = "";
	thisngHOTriggerTower.tm_label = "";
        myngHOFrontEnd.push_back(thisngHOFrontEnd); myngHOBackEnd.push_back(thisngHOBackEnd); myngHOSiPM.push_back(thisngHOSiPM); myngHOGeometry.push_back(thisngHOGeometry); myngHOTriggerTower.push_back(thisngHOTriggerTower);
    }else{
	;
    }
  }
  return NChannel;
}

int HCALLMapLoader::GetngHEromLMap(
                                   std::string LMapFileName,
                                   std::vector<ngHEFrontEnd> &myngHEFrontEnd, std::vector<ngHEBackEnd> &myngHEBackEnd, std::vector<ngHESiPM> &myngHESiPM, std::vector<ngHEGeometry> &myngHEGeometry, std::vector<ngHETriggerTower> &myngHETriggerTower
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
    ngHEFrontEnd thisngHEFrontEnd; ngHEBackEnd thisngHEBackEnd; ngHESiPM thisngHESiPM; ngHEGeometry thisngHEGeometry; ngHETriggerTower thisngHETriggerTower;
    //#  Side   Eta   Phi DepthSubdet    ngRBX       RM    RM_FI    FI_CH   uCrate     uHTR  uHTR_FI    FI_CH
    //      1    16    71     3    HE  ngHEP01        1        1        0       30       11       18        0
    ss >> thisngHEGeometry.side >> thisngHEGeometry.eta >> thisngHEGeometry.phi >> thisngHEGeometry.depth >> thisngHEGeometry.subdet
       >> thisngHEFrontEnd.rbx >> thisngHEFrontEnd.rm >> thisngHEFrontEnd.rm_fiber >> thisngHEFrontEnd.fiber_ch
       >> thisngHEBackEnd.ucrate >> thisngHEBackEnd.uhtr >> thisngHEBackEnd.uhtr_fiber >> thisngHEBackEnd.fiber_ch;

    myngHEFrontEnd.push_back(thisngHEFrontEnd); myngHEBackEnd.push_back(thisngHEBackEnd); myngHESiPM.push_back(thisngHESiPM); myngHEGeometry.push_back(thisngHEGeometry); myngHETriggerTower.push_back(thisngHETriggerTower);
  }
  return NChannel;
}

int HCALLMapLoader::GetngHFromLMap(
                                   std::string LMapFileName,
                                   std::vector<ngHFFrontEnd> &myngHFFrontEnd, std::vector<ngHFBackEnd> &myngHFBackEnd, std::vector<ngHFPMTBox> &myngHFPMTBox, std::vector<ngHFGeometry> &myngHFGeometry, std::vector<ngHFTriggerTower> &myngHFTriggerTower
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
    ngHFFrontEnd thisngHFFrontEnd; ngHFBackEnd thisngHFBackEnd; ngHFPMTBox thisngHFPMTBox; ngHFGeometry thisngHFGeometry; ngHFTriggerTower thisngHFTriggerTower;
    //Side   Eta   Phi  dPhi Depth   Det 
    //ngRBX 
    //Wedge PMTBx PMT_TYPE  W_Cable Tower   
    //PMT BaseBoard Anode 
    //S_PMT S_QIE R_PMT R_QIE 
    //QIE10 QIETB QIECH QIEFI FI_CH 
    //Trunk_FI   nCable   MTP 
    //Crate  uHTR  uHTR_Rx  uHTR_FI 
    //FEDid  
    //QIE10id             QIE10BarCode
    //1    34     1     2     2    HF 
    //HFP01     
    //1     1        A        1    H6     
    //5         B     1    
    //11     2    12     1     
    //3   TOP     1     4     0
    //1    14193     4    
    //32    12        1       12  
    //1122   
    //500751    0x6b000000 0xba086a70
    std::string qie10_barcode_p1, qie10_barcode_p2;
    ss >> thisngHFGeometry.side >> thisngHFGeometry.eta >> thisngHFGeometry.phi >> thisngHFGeometry.dphi >>thisngHFGeometry.depth >> thisngHFGeometry.subdet
       >> thisngHFFrontEnd.rbx
       >> thisngHFPMTBox.wedge >> thisngHFPMTBox.pmtbox >> thisngHFPMTBox.pmt_type >> thisngHFPMTBox.winchester_cable >> thisngHFPMTBox.tower
       >> thisngHFPMTBox.pmtsocket >> thisngHFPMTBox.baseboard_type >> thisngHFPMTBox.anode
       >> thisngHFPMTBox.s_coax_pmt >> thisngHFFrontEnd.s_coax_qie >> thisngHFPMTBox.r_coax_pmt >> thisngHFFrontEnd.r_coax_qie
       >> thisngHFFrontEnd.qie10 >> thisngHFFrontEnd.qie10_connector >> thisngHFFrontEnd.qie10_ch >> thisngHFFrontEnd.qie10_fiber >> thisngHFFrontEnd.fiber_ch
       >> thisngHFBackEnd.trunk_fiber >> thisngHFBackEnd.trunk_ncable >> thisngHFBackEnd.mtp
       >> thisngHFBackEnd.ucrate >> thisngHFBackEnd.uhtr >> thisngHFBackEnd.uhtr_rx >> thisngHFBackEnd.uhtr_fiber
       >> thisngHFBackEnd.ufedid
       >> thisngHFFrontEnd.qie10_id>> qie10_barcode_p1 >> qie10_barcode_p2;

    thisngHFFrontEnd.qie10_barcode = qie10_barcode_p1 + " " + qie10_barcode_p2;
    thisngHFBackEnd.fiber_ch = thisngHFFrontEnd.fiber_ch;

    myngHFFrontEnd.push_back(thisngHFFrontEnd); myngHFBackEnd.push_back(thisngHFBackEnd); myngHFPMTBox.push_back(thisngHFPMTBox); myngHFGeometry.push_back(thisngHFGeometry); myngHFTriggerTower.push_back(thisngHFTriggerTower);
  }
  return NChannel;
}
