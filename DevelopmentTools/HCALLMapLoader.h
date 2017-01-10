namespace HCALLMapLoader
{
  int GetHBHEHFromLMap(
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
        if( LMapFileName.find("_uHTR") != std::string::npos )//loading uHTR variables
        {
          ss >> tmp
             >> thisHBGeometry.side >> thisHBGeometry.eta >> thisHBGeometry.phi >> thisHBGeometry.dphi >> thisHBGeometry.depth >> thisHBGeometry.subdet
             >> thisHBFrontEnd.rbx >> thisHBPMTBox.wedge >> thisHBFrontEnd.rm >> thisHBPMTBox.pixel >> thisHBFrontEnd.qie8 >> thisHBFrontEnd.qie8_ch >> thisHBFrontEnd.rm_fiber >> thisHBFrontEnd.fiber_ch
             >> thisHBBackEnd.ucrate >> thisHBBackEnd.uhtr >> thisHBBackEnd.ufpga >> thisHBBackEnd.uhtr_fiber >> thisHBBackEnd.dcc_sl >> thisHBBackEnd.spigot >> thisHBBackEnd.dcc
             >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
             >> thisHBBackEnd.ufedid
             >> thisHBFrontEnd.qie8id;
        }
        else
        {
          ss >> tmp
             >> thisHBGeometry.side >> thisHBGeometry.eta >> thisHBGeometry.phi >> thisHBGeometry.dphi >> thisHBGeometry.depth >> thisHBGeometry.subdet
             >> thisHBFrontEnd.rbx >> thisHBPMTBox.wedge >> thisHBFrontEnd.rm >> thisHBPMTBox.pixel >> thisHBFrontEnd.qie8 >> thisHBFrontEnd.qie8_ch >> thisHBFrontEnd.rm_fiber >> thisHBFrontEnd.fiber_ch
             >> thisHBBackEnd.crate >> thisHBBackEnd.htr >> thisHBBackEnd.fpga >> thisHBBackEnd.htr_fiber >> thisHBBackEnd.dcc_sl >> thisHBBackEnd.spigot >> thisHBBackEnd.dcc 
             >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
             >> thisHBBackEnd.fedid
             >> thisHBFrontEnd.qie8id;
        }
        thisHBBackEnd.fiber_ch = thisHBFrontEnd.fiber_ch;

        myHBFrontEnd.push_back(thisHBFrontEnd); myHBBackEnd.push_back(thisHBBackEnd); myHBPMTBox.push_back(thisHBPMTBox); myHBGeometry.push_back(thisHBGeometry); myHBTriggerTower.push_back(thisHBTriggerTower);
      }
      else if(line.find("HE") != std::string::npos)
      {
        std::istringstream ss(line);
        HEFrontEnd thisHEFrontEnd; HEBackEnd thisHEBackEnd; HEPMTBox thisHEPMTBox; HEGeometry thisHEGeometry; HETriggerTower thisHETriggerTower;

        int tmp;
        std::string tmp_str;
        if( LMapFileName.find("_uHTR") != std::string::npos )//loading uHTR variables
        {
          ss >> tmp
             >> thisHEGeometry.side >> thisHEGeometry.eta >> thisHEGeometry.phi >> thisHEGeometry.dphi >> thisHEGeometry.depth >> thisHEGeometry.subdet 
             >> thisHEFrontEnd.rbx >> thisHEPMTBox.wedge >> thisHEFrontEnd.rm >> thisHEPMTBox.pixel >> thisHEFrontEnd.qie8 >> thisHEFrontEnd.qie8_ch >> thisHEFrontEnd.rm_fiber >> thisHEFrontEnd.fiber_ch
             >> thisHEBackEnd.ucrate >> thisHEBackEnd.uhtr >> thisHEBackEnd.ufpga >> thisHEBackEnd.uhtr_fiber >> thisHEBackEnd.dcc_sl >> thisHEBackEnd.spigot >> thisHEBackEnd.dcc
             >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
             >> thisHEBackEnd.ufedid
             >> thisHEFrontEnd.qie8id;
        }
        else
        {
          ss >> tmp
             >> thisHEGeometry.side >> thisHEGeometry.eta >> thisHEGeometry.phi >> thisHEGeometry.dphi >> thisHEGeometry.depth >> thisHEGeometry.subdet
             >> thisHEFrontEnd.rbx >> thisHEPMTBox.wedge >> thisHEFrontEnd.rm >> thisHEPMTBox.pixel >> thisHEFrontEnd.qie8 >> thisHEFrontEnd.qie8_ch >> thisHEFrontEnd.rm_fiber >> thisHEFrontEnd.fiber_ch
             >> thisHEBackEnd.crate >> thisHEBackEnd.htr >> thisHEBackEnd.fpga >> thisHEBackEnd.htr_fiber >> thisHEBackEnd.dcc_sl >> thisHEBackEnd.spigot >> thisHEBackEnd.dcc
             >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
             >> thisHEBackEnd.fedid
             >> thisHEFrontEnd.qie8id;
        }
        thisHEBackEnd.fiber_ch = thisHEFrontEnd.fiber_ch;

        myHEFrontEnd.push_back(thisHEFrontEnd); myHEBackEnd.push_back(thisHEBackEnd); myHEPMTBox.push_back(thisHEPMTBox); myHEGeometry.push_back(thisHEGeometry); myHETriggerTower.push_back(thisHETriggerTower);
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
           >> thisHFFrontEnd.qie8id;
        }
        else
        {
          ss >> tmp
             >> thisHFGeometry.side >> thisHFGeometry.eta >> thisHFGeometry.phi >> thisHFGeometry.dphi >> thisHFGeometry.depth >> thisHFGeometry.subdet
             >> thisHFFrontEnd.rbx >> thisHFPMTBox.wedge >> thisHFFrontEnd.rm >> thisHFPMTBox.pixel >> thisHFFrontEnd.qie8 >> thisHFFrontEnd.qie8_ch >> thisHFFrontEnd.rm_fiber >> thisHFFrontEnd.fiber_ch
             >> thisHFBackEnd.crate >> thisHFBackEnd.htr >> thisHFBackEnd.fpga >> thisHFBackEnd.htr_fiber >> thisHFBackEnd.dcc_sl >> thisHFBackEnd.spigot >> thisHFBackEnd.dcc
             >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
             >> thisHFBackEnd.fedid
             >> thisHFFrontEnd.qie8id;
        }
        thisHFBackEnd.fiber_ch = thisHFFrontEnd.fiber_ch;

        myHFFrontEnd.push_back(thisHFFrontEnd); myHFBackEnd.push_back(thisHFBackEnd); myHFPMTBox.push_back(thisHFPMTBox); myHFGeometry.push_back(thisHFGeometry); myHFTriggerTower.push_back(thisHFTriggerTower);
      }
      else { std::cout << "#We are looping over HBEF map but did not find the tag for HBHEHF!! Suck on that!" << std::endl; return -2; }
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

  int GetngHFromLMap(
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
      //#  Side   Eta   Phi Depth   Subdet   PMT PMT_TYPE  W_Cable S_PMT S_QIE R_PMT R_QIE    ngRBX    QIE10 QIE10_CH QIE10_FI    FI_CH   uCrate     uHTR  uHTR_FI    FI_CH
      //      1    34     1     2    HF        1        A        1    11     2    12     1  ngHFP01        3        1        4        0       32       12        0        0
      ss >> thisngHFGeometry.side >> thisngHFGeometry.eta >> thisngHFGeometry.phi >> thisngHFGeometry.depth >> thisngHFGeometry.subdet
         >> thisngHFPMTBox.pmtbox >> thisngHFPMTBox.pmt_type >> thisngHFPMTBox.winchester_cable 
         >> thisngHFPMTBox.s_coax_pmt 
         >> thisngHFFrontEnd.s_coax_qie
         >> thisngHFPMTBox.r_coax_pmt
         >> thisngHFFrontEnd.r_coax_qie
         >> thisngHFFrontEnd.rbx >> thisngHFFrontEnd.qie10 >> thisngHFFrontEnd.qie10_ch >> thisngHFFrontEnd.qie10_fiber >> thisngHFFrontEnd.fiber_ch
         >> thisngHFBackEnd.ucrate >> thisngHFBackEnd.uhtr >> thisngHFBackEnd.uhtr_fiber >> thisngHFBackEnd.fiber_ch;

      myngHFFrontEnd.push_back(thisngHFFrontEnd); myngHFBackEnd.push_back(thisngHFBackEnd); myngHFPMTBox.push_back(thisngHFPMTBox); myngHFGeometry.push_back(thisngHFGeometry); myngHFTriggerTower.push_back(thisngHFTriggerTower);
    }

    return NChannel;
  }

  int GetngHEromLMap(
                     std::string LMapFileName,
                     std::vector<ngHEFrontEnd> &myngHEFrontEnd, std::vector<ngHEBackEnd> &myngHEBackEnd, std::vector<ngHEPMTBox> &myngHEPMTBox, std::vector<ngHEGeometry> &myngHEGeometry, std::vector<ngHETriggerTower> &myngHETriggerTower
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
      ngHEFrontEnd thisngHEFrontEnd; ngHEBackEnd thisngHEBackEnd; ngHEPMTBox thisngHEPMTBox; ngHEGeometry thisngHEGeometry; ngHETriggerTower thisngHETriggerTower;
      //#  Side   Eta   Phi DepthSubdet    ngRBX       RM    RM_FI    FI_CH   uCrate     uHTR  uHTR_FI    FI_CH
      //      1    16    71     3    HE  ngHEP01        1        1        0       30       11       18        0
      ss >> thisngHEGeometry.side >> thisngHEGeometry.eta >> thisngHEGeometry.phi >> thisngHEGeometry.depth >> thisngHEGeometry.subdet
         >> thisngHEFrontEnd.rbx >> thisngHEFrontEnd.rm >> thisngHEFrontEnd.rm_fiber >> thisngHEFrontEnd.fiber_ch
         >> thisngHEBackEnd.ucrate >> thisngHEBackEnd.uhtr >> thisngHEBackEnd.uhtr_fiber >> thisngHEBackEnd.fiber_ch;

      myngHEFrontEnd.push_back(thisngHEFrontEnd); myngHEBackEnd.push_back(thisngHEBackEnd); myngHEPMTBox.push_back(thisngHEPMTBox); myngHEGeometry.push_back(thisngHEGeometry); myngHETriggerTower.push_back(thisngHETriggerTower);
    }

    return NChannel;
  }
}
