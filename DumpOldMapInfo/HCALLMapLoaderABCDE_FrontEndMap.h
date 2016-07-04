namespace HCALLMapLoaderABCDE_FrontEndMap
{
  int GetFrontEndMapromLMap(
                            std::string LMapFileName,
                            std::vector<HCALFrontEndMapEntry> &myHCALFrontEndMapEntry
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
      HCALFrontEndMapEntry thisHCALFrontEndMapEntry;

      int tmp;
      std::string tmp_str;
      
      if( LMapFileName.find("HBEF_") != std::string::npos )//loading uHTR variables
      {
        //ABCDE LMap formata HBHEHF
        //#   side    eta    phi   dphi  depth    det     
        //rbx  wedge     rm  pixel   qie    adc  rm_fi  fi_ch  
        //crate    htr   fpga  htr_fi  dcc_sl  spigo    dcc    
        //slb  slbin  slbin2           slnam    rctcra rctcar rctcon               rctnam     
        //fedid

        ss >> tmp
           >> thisHCALFrontEndMapEntry.side >> thisHCALFrontEndMapEntry.eta >> thisHCALFrontEndMapEntry.phi >> tmp >> thisHCALFrontEndMapEntry.depth >> thisHCALFrontEndMapEntry.subdet
           >> thisHCALFrontEndMapEntry.rbx >> tmp >> thisHCALFrontEndMapEntry.rm >> tmp >> tmp >> tmp >> tmp >> tmp
           >> tmp >> tmp >> tmp_str >> tmp >> tmp >> tmp >> tmp // backend variables, no need to include them 
           >> tmp >> tmp_str >> tmp_str >> tmp_str >> tmp >> tmp >> tmp >> tmp_str //skip variables for RCR, RIP
           >> tmp;//fed id , no need
      }
      else if( LMapFileName.find("HO_") != std::string::npos )//loading uHTR variables
      {
        //ABCDE LMap formata HBHEHF
        //#   side    eta    phi   dphi  depth    det     
        //rbx  sector    rm  pixel   qie    adc  rm_fi  fi_ch let_code  
        //crate    htr   fpga  htr_fi  dcc_sl  spigo    dcc  fedid

        ss >> tmp
           >> thisHCALFrontEndMapEntry.side >> thisHCALFrontEndMapEntry.eta >> thisHCALFrontEndMapEntry.phi >> tmp >> thisHCALFrontEndMapEntry.depth >> thisHCALFrontEndMapEntry.subdet
           >> thisHCALFrontEndMapEntry.rbx >> tmp >> thisHCALFrontEndMapEntry.rm >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp_str
           >> tmp >> tmp >> tmp_str >> tmp >> tmp >> tmp >> tmp >> tmp;
      }

      myHCALFrontEndMapEntry.push_back(thisHCALFrontEndMapEntry);
    }

    return NChannel;
  }
}
