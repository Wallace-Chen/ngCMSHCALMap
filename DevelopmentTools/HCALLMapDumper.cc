#include "HCALLMapDumper.h"

void HCALLMapDumper::printHBLMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower)
{
  std::cout << "#Dumping HB LMap Object..." << std::endl;
  //Side Eta Phi dPhi Depth Det 
  //RBX 
  //Wedge Pix 
  //QIE8 QIECH RM RM_FI FI_CH 
  //ppCol ppRow ppCpl ppLC docdec 
  //Crate uHTR uHTR_FI 
  //FEDid 
  //QIE8id

  std::cout << "#"
            << std::setw(6) << "Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(6) << "Depth" << std::setw(6) << "Det"
            << std::setw(6) << "RBX"
            << std::setw(6) << "Wedge" << std::setw(6) << "Pix"
            << std::setw(6) << "QIE8" << std::setw(6) << "QIECH" << std::setw(6) << "RM" << std::setw(6) << "RM_FI" << std::setw(6) << "FI_CH"
            << std::setw(6) << "ppCol" << std::setw(6) << "ppRow" << std::setw(15) << "ppCpl" << std::setw(6) << "ppLC" << std::setw(6) << "dodec"
            << std::setw(6) << "Crate" << std::setw(6) << "uHTR" << std::setw(9) << "uHTR_FI"
            << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE8id"
            << std::endl;
  for(auto i=0; i<myHBFrontEnd.size(); i++)
  {
    std::cout
              << " "
              << std::setw(6) << myHBGeometry.at(i).side << std::setw(6) << myHBGeometry.at(i).eta << std::setw(6) << myHBGeometry.at(i).phi << std::setw(6) << myHBGeometry.at(i).dphi << std::setw(6) << myHBGeometry.at(i).depth << std::setw(6) << myHBGeometry.at(i).subdet
              << std::setw(6) << myHBFrontEnd.at(i).rbx 
              << std::setw(6) << myHBHPD.at(i).wedge << std::setw(6) << myHBHPD.at(i).pixel
              << std::setw(6) << myHBFrontEnd.at(i).qie8 << std::setw(6) << myHBFrontEnd.at(i).qie8_ch << std::setw(6) << myHBFrontEnd.at(i).rm << std::setw(6) << myHBFrontEnd.at(i).rm_fiber << std::setw(6) << myHBFrontEnd.at(i).fiber_ch
              << std::setw(6) << myHBBackEnd.at(i).ppcol << std::setw(6) << myHBBackEnd.at(i).pprow << std::setw(15) << myHBBackEnd.at(i).ppcpl << std::setw(6) << myHBBackEnd.at(i).pplc << std::setw(6) << myHBBackEnd.at(i).dodec
              << std::setw(6) << myHBBackEnd.at(i).ucrate << std::setw(6) << myHBBackEnd.at(i).uhtr << std::setw(9) << myHBBackEnd.at(i).uhtr_fiber
              << std::setw(6) << myHBBackEnd.at(i).ufedid
              << std::setw(9) << myHBFrontEnd.at(i).qie8_id
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHBLMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower)
{
  std::cout << "#Dumping ngHB LMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) <<"Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "Depth" << std::setw(6) << "Det"
            << std::setw(9) << "ngRBX" << std::setw(9) << "RM" << std::setw(9) << "RM_FI" << std::setw(9) << "FI_CH"
            << std::setw(9) << "uCrate" << std::setw(9) << "uHTR" << std::setw(9) << "uHTR_FI" << std::setw(9) << "FI_CH" << std::endl;
  for(auto i=0; i<myngHBFrontEnd.size(); i++)
  {
    //if( myngHBFrontEnd.at(i).rbx != "ngHBP02" ) continue;
    std::cout
              << " "
              << std::setw(6) << myngHBGeometry.at(i).side << std::setw(6) << myngHBGeometry.at(i).eta << std::setw(6) << myngHBGeometry.at(i).phi << std::setw(6) << myngHBGeometry.at(i).depth << std::setw(6) << myngHBGeometry.at(i).subdet
              << std::setw(9) << myngHBFrontEnd.at(i).rbx << std::setw(9) << myngHBFrontEnd.at(i).rm << std::setw(9) << myngHBFrontEnd.at(i).rm_fiber << std::setw(9) << myngHBFrontEnd.at(i).fiber_ch
              << std::setw(9) << myngHBBackEnd.at(i).ucrate << std::setw(9) << myngHBBackEnd.at(i).uhtr << std::setw(9) << myngHBBackEnd.at(i).uhtr_fiber << std::setw(9) << myngHBBackEnd.at(i).fiber_ch
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHBEMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping ngHB EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(9) << "dep"
            << std::endl;

  for(auto i=0; i<myngHBFrontEnd.size(); i++)
  {
    if( myngHBGeometry.at(i).subdet == "HEX" ) continue;
    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myngHBBackEnd.at(i).ucrate << std::setw(6) << myngHBBackEnd.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myngHBBackEnd.at(i).uhtr_fiber << std::setw(12) << myngHBBackEnd.at(i).fiber_ch
              << std::setw(8) << myngHBGeometry.at(i).subdet << std::setw(6) << myngHBGeometry.at(i).side * myngHBGeometry.at(i).eta << std::setw(6) << myngHBGeometry.at(i).phi << std::setw(6) << myngHBGeometry.at(i).depth
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHBFrontEndMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping ngHB FrontEnd Map Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(9) << "dep"
            << std::setw(8) << "subdet"
            << std::setw(6) << "rbx" << std::setw(6) << "rm"
            << std::endl;
    
  for(auto i=0; i<myngHBFrontEnd.size(); i++)
  {
    if( myngHBGeometry.at(i).subdet == "HEX" ) continue;
    std::cout
              //<< "ngHBGeometry(side,eta,phi,depth): "
              << " "
              << std::setw(6) << myngHBGeometry.at(i).side * myngHBGeometry.at(i).eta << std::setw(6) << myngHBGeometry.at(i).phi << std::setw(6) << myngHBGeometry.at(i).depth
              << std::setw(8) << myngHBGeometry.at(i).subdet
              << std::setw(9) << myngHBFrontEnd.at(i).rbx << std::setw(6) << myngHBFrontEnd.at(i).rm
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHELMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower)
{
  std::cout << "#Dumping ngHE LMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) <<"Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "Depth" << std::setw(6) << "Det"
            << std::setw(9) << "ngRBX" << std::setw(9) << "RM" << std::setw(9) << "RM_FI" << std::setw(9) << "FI_CH"
            << std::setw(9) << "uCrate" << std::setw(9) << "uHTR" << std::setw(9) << "uHTR_FI" << std::setw(9) << "FI_CH" << std::endl;
  for(auto i=0; i<myngHEFrontEnd.size(); i++)
  {
    //if( myngHEFrontEnd.at(i).rbx != "ngHEP02" ) continue;
    std::cout
              << " "
              << std::setw(6) << myngHEGeometry.at(i).side << std::setw(6) << myngHEGeometry.at(i).eta << std::setw(6) << myngHEGeometry.at(i).phi << std::setw(6) << myngHEGeometry.at(i).depth << std::setw(6) << myngHEGeometry.at(i).subdet
              << std::setw(9) << myngHEFrontEnd.at(i).rbx << std::setw(9) << myngHEFrontEnd.at(i).rm << std::setw(9) << myngHEFrontEnd.at(i).rm_fiber << std::setw(9) << myngHEFrontEnd.at(i).fiber_ch
              << std::setw(9) << myngHEBackEnd.at(i).ucrate << std::setw(9) << myngHEBackEnd.at(i).uhtr << std::setw(9) << myngHEBackEnd.at(i).uhtr_fiber << std::setw(9) << myngHEBackEnd.at(i).fiber_ch
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHEEMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping ngHE EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(9) << "dep"
            << std::endl;

  for(auto i=0; i<myngHEFrontEnd.size(); i++)
  {
    if( myngHEGeometry.at(i).subdet == "HEX" ) continue;
    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myngHEBackEnd.at(i).ucrate << std::setw(6) << myngHEBackEnd.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myngHEBackEnd.at(i).uhtr_fiber << std::setw(12) << myngHEBackEnd.at(i).fiber_ch
              << std::setw(8) << myngHEGeometry.at(i).subdet << std::setw(6) << myngHEGeometry.at(i).side * myngHEGeometry.at(i).eta << std::setw(6) << myngHEGeometry.at(i).phi << std::setw(6) << myngHEGeometry.at(i).depth
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHEFrontEndMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping ngHE FrontEnd Map Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(9) << "dep"
            << std::setw(8) << "subdet"
            << std::setw(6) << "rbx" << std::setw(6) << "rm"
            << std::endl;
    
  for(auto i=0; i<myngHEFrontEnd.size(); i++)
  {
    if( myngHEGeometry.at(i).subdet == "HEX" ) continue;
    std::cout
              //<< "ngHEGeometry(side,eta,phi,depth): "
              << " "
              << std::setw(6) << myngHEGeometry.at(i).side * myngHEGeometry.at(i).eta << std::setw(6) << myngHEGeometry.at(i).phi << std::setw(6) << myngHEGeometry.at(i).depth
              << std::setw(8) << myngHEGeometry.at(i).subdet
              << std::setw(9) << myngHEFrontEnd.at(i).rbx << std::setw(6) << myngHEFrontEnd.at(i).rm
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printHFLMapObject(std::vector<HFFrontEnd> myHFFrontEnd, std::vector<HFBackEnd> myHFBackEnd, std::vector<HFPMTBox> myHFPMTBox, std::vector<HFGeometry> myHFGeometry, std::vector<HFTriggerTower> myHFTriggerTower)
{
  std::cout << "#Dumping HF LMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) <<"Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "Depth"
            //<< std::setw(9) << "PMT" << std::setw(9) << "PMT_TYPE" << std::setw(9) << "W_Cable"
            //<< std::setw(6) << "S_PMT" << std::setw(6) << "S_QIE" << std::setw(6) << "R_PMT" << std::setw(6) << "R_QIE"
            << std::setw(9) << "RBX"<< std::setw(9) << "RM" << std::setw(9) << "RM_FI" << std::setw(9) << "FI_CH" << std::setw(9) << "QIE8" << std::setw(9) << "QIE8_CH"
            << std::setw(9) << "uCrate" << std::setw(9) << "uHTR" << std::setw(9) << "uHTR_FI" << std::setw(9) << "FI_CH" << std::endl;

  for(auto i=0; i<myHFFrontEnd.size(); i++)
  {
    std::cout //<< "HFGeometry(side,eta,phi,depth): " 
              << " "
              << std::setw(6) << myHFGeometry.at(i).side << std::setw(6) <<  myHFGeometry.at(i).eta << std::setw(6) << myHFGeometry.at(i).phi << std::setw(6) << myHFGeometry.at(i).depth
              //<< "HFFrontEnd(rbx,rm,rm_fiber,fiber_ch,qie8,qie8_ch): " 
              << std::setw(9) << myHFFrontEnd.at(i).rbx << std::setw(9) << myHFFrontEnd.at(i).rm << std::setw(9) << myHFFrontEnd.at(i).rm_fiber << std::setw(9) << myHFFrontEnd.at(i).fiber_ch << std::setw(9) << myHFFrontEnd.at(i).qie8 << std::setw(9) << myHFFrontEnd.at(i).qie8_ch
              //<< "HFBackEnd(ucrate,uhtr,uhtr_fiber,fiber_ch): " 
              << std::setw(9) << myHFBackEnd.at(i).ucrate << std::setw(9) << myHFBackEnd.at(i).uhtr << std::setw(9) << myHFBackEnd.at(i).uhtr_fiber << std::setw(9) << myHFBackEnd.at(i).fiber_ch
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHFLMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower)
{
  std::cout << "#Dumping ngHF LMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) <<"Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(6) << "Depth" << std::setw(6) << "Det"
            << std::setw(6) << "ngRBX" 
            << std::setw(6) << "Wedge" << std::setw(6) << "PMTBx" << std::setw(9) << "PMT_TYPE" << std::setw(9) << "W_Cable" << std::setw(6) << "Tower"
            << std::setw(6) << "PMT" << std::setw(10) << "BaseBoard" << std::setw(6) << "Anode"
            << std::setw(6) << "S_PMT" << std::setw(6) << "S_QIE" << std::setw(6) << "R_PMT" << std::setw(6) << "R_QIE"
            << std::setw(6) << "QIE10" << std::setw(6) << "QIETB" << std::setw(6) << "QIECH" << std::setw(6) << "QIEFI" << std::setw(6) << "FI_CH"
            << std::setw(9) << "Trunk_FI" << std::setw(9) << "nCable" << std::setw(6) << "MTP"
            << std::setw(6) << "Crate" << std::setw(6) << "uHTR" << std::setw(9) << "uHTR_Rx" << std::setw(9) << "uHTR_FI"
            << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE10id" << std::setw(25) << "QIE10BarCode"
            << std::endl;

  for(auto i=0; i<myngHFFrontEnd.size(); i++)
  {
    //if( !(myngHFFrontEnd.at(i).fiber_ch==3 && myngHFBackEnd.at(i).uhtr_fiber==13) ) continue;
    //if( !(myngHFPMTBox.at(i).tower=="E12" || myngHFPMTBox.at(i).tower=="H12") ) continue;
    //if( !(myngHFPMTBox.at(i).tower=="E13" || myngHFPMTBox.at(i).tower=="H13") ) continue;
    //if( !(myngHFGeometry.at(i).eta==40 || myngHFGeometry.at(i).eta==41) ) continue;
    //if( !(myngHFPMTBox.at(i).wedge==1) ) continue;
    std::cout 
              << " "
              //<< "ngHFGeometry(side,eta,phi,dphi,depth,subdet): "
              << std::setw(6) << myngHFGeometry.at(i).side << std::setw(6) << myngHFGeometry.at(i).eta << std::setw(6) << myngHFGeometry.at(i).phi << std::setw(6) << myngHFGeometry.at(i).dphi << std::setw(6) << myngHFGeometry.at(i).depth << std::setw(6) << myngHFGeometry.at(i).subdet
              //ngRBX
              << std::setw(6) << myngHFFrontEnd.at(i).rbx
              //<< "ngHFPMTBox(PMT, PMT Type, Winchester Cable,tower): "
              << std::setw(6) << myngHFPMTBox.at(i).wedge << std::setw(6) << myngHFPMTBox.at(i).pmtbox << std::setw(9) << myngHFPMTBox.at(i).pmt_type << std::setw(9) << myngHFPMTBox.at(i).winchester_cable << std::setw(6) << myngHFPMTBox.at(i).tower
              //<< PMT socket, Base board type, anode
              << std::setw(6) << myngHFPMTBox.at(i).pmtsocket << std::setw(10) << myngHFPMTBox.at(i).baseboard_type << std::setw(6) << myngHFPMTBox.at(i).anode
              //<< "Winchester Cable, PIN to PIN"
              << std::setw(6) << myngHFPMTBox.at(i).s_coax_pmt << std::setw(6) << myngHFFrontEnd.at(i).s_coax_qie << std::setw(6) << myngHFPMTBox.at(i).r_coax_pmt << std::setw(6) << myngHFFrontEnd.at(i).r_coax_qie
              //<< "ngHFFrontEnd(qie10,qie10_ch,qie10_fiber,fiber_ch): "
              << std::setw(6) << myngHFFrontEnd.at(i).qie10 << std::setw(6) << myngHFFrontEnd.at(i).qie10_connector << std::setw(6) << myngHFFrontEnd.at(i).qie10_ch << std::setw(6) << myngHFFrontEnd.at(i).qie10_fiber << std::setw(6)  << myngHFFrontEnd.at(i).fiber_ch
              //<< "ngHFBackEnd(trunk_fiber,trunk_ncable,mtp): "
              << std::setw(9) << myngHFBackEnd.at(i).trunk_fiber << std::setw(9) << myngHFBackEnd.at(i).trunk_ncable << std::setw(6) << myngHFBackEnd.at(i).mtp
              //<< "ngHFBackEnd(ucrate,uhtr,uhtr_rx,uhtr_fiber): "
              << std::setw(6) << myngHFBackEnd.at(i).ucrate << std::setw(6) << myngHFBackEnd.at(i).uhtr << std::setw(9) << myngHFBackEnd.at(i).uhtr_rx << std::setw(9) << myngHFBackEnd.at(i).uhtr_fiber
              //<< "ngHFBackEnd(ufedid): "
              << std::setw(6) << myngHFBackEnd.at(i).ufedid
              //<< "ngHFFrontEnd(qie10_id): "
              << std::setw(9) << myngHFFrontEnd.at(i).qie10_id << std::setw(25) << myngHFFrontEnd.at(i).qie10_barcode
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHFEMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower)
{ 
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping ngHF EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i" 
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch" 
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(9) << "dep" 
            << std::endl;
    
  for(auto i=0; i<myngHFFrontEnd.size(); i++)
  { 
    std::cout 
              //<< "ngHFGeometry(side,eta,phi,depth): "
              << " " 
              << std::setw(10) << "4200458C"          
              << std::setw(6) << myngHFBackEnd.at(i).ucrate << std::setw(6) << myngHFBackEnd.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myngHFBackEnd.at(i).uhtr_fiber << std::setw(12) << myngHFBackEnd.at(i).fiber_ch
              << std::setw(8) << myngHFGeometry.at(i).subdet << std::setw(6) << myngHFGeometry.at(i).side * myngHFGeometry.at(i).eta << std::setw(6) << myngHFGeometry.at(i).phi << std::setw(6) << myngHFGeometry.at(i).depth
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHFFrontEndMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping ngHF FrontEnd Map Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(9) << "dep"
            << std::setw(8) << "subdet" 
            << std::setw(6) << "rbx" << std::setw(6) << "rm"
            << std::endl;

  for(auto i=0; i<myngHFFrontEnd.size(); i++)
  {
    std::cout
              //<< "ngHFGeometry(side,eta,phi,depth): "
              << " "
              << std::setw(6) << myngHFGeometry.at(i).side * myngHFGeometry.at(i).eta << std::setw(6) << myngHFGeometry.at(i).phi << std::setw(6) << myngHFGeometry.at(i).depth
              << std::setw(8) << myngHFGeometry.at(i).subdet 
              << std::setw(9) << myngHFFrontEnd.at(i).rbx << std::setw(6) << 0
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::makedbngHFLMapObject(std::string HCALLMapDbStr, std::string ngHFTableStr,
                                          std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;

  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,ngHFTableStr);
  if(TableExist){ std::cout << "#Table: " << ngHFTableStr <<" already in the database!! Please check!" << std::endl; return ; }
  else{ std::cout << "#Table: " << ngHFTableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det 
  //ngRBX 
  //Wedge PMTBx PMT_TYPE W_Cable Tower 
  //PMT BaseBoard Anode 
  //S_PMT S_QIE R_PMT R_QIE 
  //QIE10 QIETB QIECH QIEFI FI_CH 
  //Trunk_FI nCable MTP 
  //Crate uHTR uHTR_Rx uHTR_FI FEDid 
  //QIE10id QIE10BarCode

  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + ngHFTableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "ngRBX TEXT NOT NULL, " \
                            "Wedge INT NOT NULL, PMTBx INT NOT NULL, PMT_TYPE TEXT NOT NULL, W_Cable INT NOT NULL, Tower TEXT NOT NULL, " \
                            "PMT INT NOT NULL, BaseBoard TEXT NOT NULL, Anode INT NOT NULL, " \
                            "S_PMT INT NOT NULL, S_QIE INT NOT NULL, R_PMT INT NOT NULL, R_QIE INT NOT NULL, " \
                            "QIE10 INT NOT NULL, QIETB TEXT NOT NULL, QIECH INT NOT NULL, QIEFI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "Trunk_FI INT NOT NULL, nCable INT NOT NULL, MTP INT NOT NULL, " \
                            "Crate INT NOT NULL, uHTR INT NOT NULL, uHTR_Rx INT NOT NULL, uHTR_FI INT NOT NULL, FEDid INT NOT NULL, " \
                            "QIE10id INT NOT NULL, QIE10BarCode TEXT NOT NULL);";
                    
  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }
  
  for(auto i=0; i<myngHFFrontEnd.size(); i++)
  {
    std::string one = "INSERT INTO " + ngHFTableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "ngRBX," \
                      "Wedge,PMTBx,PMT_TYPE,W_Cable,Tower," \
                      "PMT,BaseBoard,Anode," \
                      "S_PMT,S_QIE,R_PMT,R_QIE," \
                      "QIE10,QIETB,QIECH,QIEFI,FI_CH," \
                      "Trunk_FI,nCable,MTP," \
                      "Crate,uHTR,uHTR_Rx,uHTR_FI,FEDid," \
                      "QIE10id,QIE10BarCode) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myngHFGeometry.at(i).side)+","+std::to_string(myngHFGeometry.at(i).eta)+","+std::to_string(myngHFGeometry.at(i).phi)+","+std::to_string(myngHFGeometry.at(i).dphi)+","+std::to_string(myngHFGeometry.at(i).depth)+",'"+myngHFGeometry.at(i).subdet+"','"
                      +myngHFFrontEnd.at(i).rbx+"',"
                      +std::to_string(myngHFPMTBox.at(i).wedge)+","+std::to_string(myngHFPMTBox.at(i).pmtbox)+",'"+myngHFPMTBox.at(i).pmt_type+"',"+std::to_string(myngHFPMTBox.at(i).winchester_cable)+",'"+myngHFPMTBox.at(i).tower+"',"
                      +std::to_string(myngHFPMTBox.at(i).pmtsocket)+",'"+myngHFPMTBox.at(i).baseboard_type+"',"+std::to_string(myngHFPMTBox.at(i).anode)+","
                      +std::to_string(myngHFPMTBox.at(i).s_coax_pmt)+","+std::to_string(myngHFFrontEnd.at(i).s_coax_qie)+","+std::to_string(myngHFPMTBox.at(i).r_coax_pmt)+","+std::to_string(myngHFFrontEnd.at(i).r_coax_qie)+","
                      +std::to_string(myngHFFrontEnd.at(i).qie10)+",'"+myngHFFrontEnd.at(i).qie10_connector+"',"+std::to_string(myngHFFrontEnd.at(i).qie10_ch)+","+std::to_string(myngHFFrontEnd.at(i).qie10_fiber)+","+std::to_string(myngHFFrontEnd.at(i).fiber_ch)+","
                      +std::to_string(myngHFBackEnd.at(i).trunk_fiber)+","+std::to_string(myngHFBackEnd.at(i).trunk_ncable)+","+std::to_string(myngHFBackEnd.at(i).mtp)+","
                      +std::to_string(myngHFBackEnd.at(i).ucrate)+","+std::to_string(myngHFBackEnd.at(i).uhtr)+","+std::to_string(myngHFBackEnd.at(i).uhtr_rx)+","+std::to_string(myngHFBackEnd.at(i).uhtr_fiber)+","+std::to_string(myngHFBackEnd.at(i).ufedid)+","
                      +std::to_string(myngHFFrontEnd.at(i).qie10_id)+",'"+myngHFFrontEnd.at(i).qie10_barcode+"');";

    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg);
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);
  
  return ;
}

bool HCALLMapDumper::ifTableExistInDB(sqlite3 *db, std::string TableName)
{
  bool exist = false;
  std::string CheckTable = "SELECT name FROM sqlite_master WHERE type='table' AND name='"+TableName+"';";

  sqlite3_stmt *pSelectStatement = NULL;
  int iResult = SQLITE_ERROR;
  iResult = sqlite3_prepare_v2(db, CheckTable.c_str(), -1, &pSelectStatement, 0);

  if((iResult == SQLITE_OK) && (pSelectStatement != NULL))
  {                   
    iResult = sqlite3_step(pSelectStatement);
    //was found?
    if (iResult == SQLITE_ROW)
    {
      exist = true;
      sqlite3_clear_bindings(pSelectStatement);
      sqlite3_reset(pSelectStatement);
    }
    iResult = sqlite3_finalize(pSelectStatement);
  }
  return exist;
}
