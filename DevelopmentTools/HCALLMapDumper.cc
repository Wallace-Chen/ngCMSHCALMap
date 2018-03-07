#include "HCALLMapDumper.h"

void HCALLMapDumper::printHBLMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower)
{
  std::cout << "#Dumping HB LMap Object..." << std::endl;
  //Side Eta Phi dPhi Depth Det 
  //RBX 
  //Wedge Pix 
  //QIE8 QIECH RM RM_FI FI_CH 
  //ppCol ppRow ppCpl ppLC dodec 
  //Crate uHTR uHTR_FI FEDid 
  //QIE8id
  //TP_FI TP_CH
  std::cout << "#"
            << std::setw(6) << "Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(6) << "Depth" << std::setw(6) << "Det"
            << std::setw(6) << "RBX"
            << std::setw(6) << "Wedge" << std::setw(6) << "Pix"
            << std::setw(6) << "QIE8" << std::setw(6) << "QIECH" << std::setw(6) << "RM" << std::setw(6) << "RM_FI" << std::setw(6) << "FI_CH"
            << std::setw(6) << "ppCol" << std::setw(6) << "ppRow" << std::setw(15) << "ppCpl" << std::setw(6) << "ppLC" << std::setw(6) << "dodec"
            << std::setw(6) << "Crate" << std::setw(6) << "uHTR" << std::setw(9) << "uHTR_FI" << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE8id"
            << std::setw(6) << "TP_FI" << std::setw(6) << "TP_CH"
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
              << std::setw(6) << myHBBackEnd.at(i).ucrate << std::setw(6) << myHBBackEnd.at(i).uhtr << std::setw(9) << myHBBackEnd.at(i).uhtr_fiber << std::setw(6) << myHBBackEnd.at(i).ufedid
              << std::setw(9) << myHBFrontEnd.at(i).qie8_id
              << std::setw(6) << myHBTriggerTower.at(i).trg_fiber << std::setw(6) << myHBTriggerTower.at(i).trg_fiber_ch
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printHBEMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping HB EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;

  for(auto i=0; i<myHBFrontEnd.size(); i++)
  {
    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myHBBackEnd.at(i).ucrate << std::setw(6) << myHBBackEnd.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myHBBackEnd.at(i).uhtr_fiber << std::setw(12) << myHBBackEnd.at(i).fiber_ch
              << std::setw(8) << myHBGeometry.at(i).subdet << std::setw(6) << myHBGeometry.at(i).side * myHBGeometry.at(i).eta << std::setw(6) << myHBGeometry.at(i).phi << std::setw(6) << myHBGeometry.at(i).depth
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printHBFrontEndMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping HB FrontEnd Map Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(9) << "dep"
            << std::setw(8) << "subdet"
            << std::setw(6) << "rbx" << std::setw(6) << "rm"
            << std::endl;

  for(auto i=0; i<myHBFrontEnd.size(); i++)
  {
    std::cout
              //<< "HBGeometry(side,eta,phi,depth): "
              << " "
              << std::setw(6) << myHBGeometry.at(i).side * myHBGeometry.at(i).eta << std::setw(6) << myHBGeometry.at(i).phi << std::setw(6) << myHBGeometry.at(i).depth
              << std::setw(8) << myHBGeometry.at(i).subdet
              << std::setw(9) << myHBFrontEnd.at(i).rbx << std::setw(6) << myHBFrontEnd.at(i).rm
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printHBCalibLMapObject(std::vector<HBCalib> myHBCalib)
{
  //Side Eta Phi dPhi Depth Det
  //RBX Wedge
  //QIE8 QIECH RM RM_FI FI_CH
  //Trunk cpCol cpRow cpCpl cpLC cpOct
  //ppCol ppRow ppCpl ppLC dodec
  //Crate uHTR uHTR_FI FEDid
  //QIE8id
  std::cout << "#Dumping HB Calib LMap Object..." << std::endl; 
  std::cout << "#"
            << std::setw(6) << "Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(9) << "CH_TYPE" << std::setw(10) << "Det"
            << std::setw(6) << "RBX" << std::setw(6) << "Wedge"
            << std::setw(6) << "QIE8" << std::setw(6) << "QIECH" << std::setw(3) << "RM" << std::setw(6) << "RM_FI" << std::setw(6) << "FI_CH"
            << std::setw(6) << "Trunk" << std::setw(6) << "cpCol" << std::setw(6) << "cpRow" << std::setw(9) << "cpCpl" << std::setw(6) << "cpLC" << std::setw(6) << "cpOct"
            << std::setw(6) << "ppCol" << std::setw(6) << "ppRow" << std::setw(9) << "ppCpl" << std::setw(6) << "ppLC" << std::setw(6) << "dodec"
            << std::setw(6) << "Crate" << std::setw(6) << "uHTR" << std::setw(9) << "uHTR_FI"
            << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE8id"
            << std::endl;

  for(auto i=0; i<myHBCalib.size(); i++)
  {
    std::cout
              << " "
              << std::setw(6) << myHBCalib.at(i).side << std::setw(6) << myHBCalib.at(i).eta << std::setw(6) << myHBCalib.at(i).phi << std::setw(6) << myHBCalib.at(i).dphi << std::setw(9) << myHBCalib.at(i).depth << std::setw(10) << myHBCalib.at(i).subdet
              << std::setw(6) << myHBCalib.at(i).rbx << std::setw(6) << myHBCalib.at(i).wedge
              << std::setw(6) << myHBCalib.at(i).qie8 << std::setw(6) << myHBCalib.at(i).qie8_ch << std::setw(3) << myHBCalib.at(i).rm << std::setw(6) << myHBCalib.at(i).rm_fiber << std::setw(6) << myHBCalib.at(i).fiber_ch
              << std::setw(6) << myHBCalib.at(i).trunk << std::setw(6) << myHBCalib.at(i).cpcol << std::setw(6) << myHBCalib.at(i).cprow << std::setw(9) << myHBCalib.at(i).cpcpl << std::setw(6) << myHBCalib.at(i).cplc << std::setw(6) << myHBCalib.at(i).cpoct
              << std::setw(6) << myHBCalib.at(i).ppcol << std::setw(6) << myHBCalib.at(i).pprow << std::setw(9) << myHBCalib.at(i).ppcpl << std::setw(6) << myHBCalib.at(i).pplc << std::setw(6) << myHBCalib.at(i).dodec
              << std::setw(6) << myHBCalib.at(i).ucrate << std::setw(6) << myHBCalib.at(i).uhtr << std::setw(9) << myHBCalib.at(i).uhtr_fiber
              << std::setw(6) << myHBCalib.at(i).ufedid
              << std::setw(9) << myHBCalib.at(i).qie8_id
              << std::endl;
  }

  return ;
}

void HCALLMapDumper::printHBCalibEMapObject(std::vector<HBCalib> myHBCalib)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping HBCalib EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(9) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;

  for(auto i=0; i<myHBCalib.size(); i++)
  {
    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myHBCalib.at(i).ucrate << std::setw(6) << myHBCalib.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myHBCalib.at(i).uhtr_fiber << std::setw(12) << myHBCalib.at(i).fiber_ch
              << std::setw(9) << myHBCalib.at(i).subdet << std::setw(6) << myHBCalib.at(i).side * myHBCalib.at(i).eta << std::setw(6) << myHBCalib.at(i).phi << std::setw(6) << myHBCalib.at(i).depth
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printngHBLMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower)
{
  std::cout << "#Dumping ngHB LMap Object..." << std::endl;
  //Side Eta Phi dPhi Depth Det 
  //RBX 
  //Wedge BV 
  //QIE11 QIECH RM RM_FI FI_CH 
  //ppCol ppRow ppCpl ppLC dodec 
  //Crate uHTR uHTR_FI FEDid 
  //QIE11id
  //TP_FI TP_CH
  std::cout << "#"
            << std::setw(6) << "Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(6) << "Depth" << std::setw(6) << "Det"
            << std::setw(6) << "RBX"
            << std::setw(6) << "Wedge" << std::setw(6) << "BV"
            << std::setw(6) << "QIE11" << std::setw(6) << "QIECH" << std::setw(6) << "RM" << std::setw(6) << "RM_FI" << std::setw(6) << "FI_CH"
            << std::setw(6) << "ppCol" << std::setw(6) << "ppRow" << std::setw(15) << "ppCpl" << std::setw(6) << "ppLC" << std::setw(6) << "dodec"
            << std::setw(6) << "Crate" << std::setw(6) << "uHTR" << std::setw(9) << "uHTR_FI" << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE11id"
            << std::setw(6) << "TP_FI" << std::setw(6) << "TP_CH"
            << std::endl;
  for(auto i=0; i<myngHBFrontEnd.size(); i++)
  {
    std::cout
              << " "
              << std::setw(6) << myngHBGeometry.at(i).side << std::setw(6) << myngHBGeometry.at(i).eta << std::setw(6) << myngHBGeometry.at(i).phi << std::setw(6) << myngHBGeometry.at(i).dphi << std::setw(6) << myngHBGeometry.at(i).depth << std::setw(6) << myngHBGeometry.at(i).subdet
              << std::setw(6) << myngHBFrontEnd.at(i).rbx
              << std::setw(6) << myngHBSiPM.at(i).wedge << std::setw(6) << myngHBSiPM.at(i).bv
              << std::setw(6) << myngHBFrontEnd.at(i).qie11 << std::setw(6) << myngHBFrontEnd.at(i).qie11_ch << std::setw(6) << myngHBFrontEnd.at(i).rm << std::setw(6) << myngHBFrontEnd.at(i).rm_fiber << std::setw(6) << myngHBFrontEnd.at(i).fiber_ch
              << std::setw(6) << myngHBBackEnd.at(i).ppcol << std::setw(6) << myngHBBackEnd.at(i).pprow << std::setw(15) << myngHBBackEnd.at(i).ppcpl << std::setw(6) << myngHBBackEnd.at(i).pplc << std::setw(6) << myngHBBackEnd.at(i).dodec
              << std::setw(6) << myngHBBackEnd.at(i).ucrate << std::setw(6) << myngHBBackEnd.at(i).uhtr << std::setw(9) << myngHBBackEnd.at(i).uhtr_fiber << std::setw(6) << myngHBBackEnd.at(i).ufedid
              << std::setw(9) << myngHBFrontEnd.at(i).qie11_id
              << std::setw(6) << myngHBTriggerTower.at(i).trg_fiber << std::setw(6) << myngHBTriggerTower.at(i).trg_fiber_ch
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
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;

  for(auto i=0; i<myngHBFrontEnd.size(); i++)
  {
    if( myngHBGeometry.at(i).subdet == "HBX" ) continue;
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
    if( myngHBGeometry.at(i).subdet == "HBX" ) continue;
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
  //Side Eta Phi dPhi Depth Det 
  //RBX 
  //Wedge BV
  //QIE11 QIECH RM RM_FI FI_CH 
  //ppCol ppRow ppCpl ppLC docdec 
  //Crate uHTR uHTR_FI 
  //FEDid 
  //QIE11id
  //TP_FI TP_CH
  std::cout << "#"
            << std::setw(6) << "Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(6) << "Depth" << std::setw(6) << "Det"
            << std::setw(6) << "RBX"
            << std::setw(6) << "Wedge" << std::setw(6) << "BV"
            << std::setw(6) << "QIE11" << std::setw(6) << "QIECH" << std::setw(6) << "RM" << std::setw(6) << "RM_FI" << std::setw(6) << "FI_CH"
            << std::setw(6) << "ppCol" << std::setw(6) << "ppRow" << std::setw(15) << "ppCpl" << std::setw(6) << "ppLC" << std::setw(6) << "dodec"
            << std::setw(6) << "Crate" << std::setw(6) << "uHTR" << std::setw(9) << "uHTR_FI"
            << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE11id"
            << std::setw(6) << "TP_FI" << std::setw(6) << "TP_CH"
            << std::endl;
  for(auto i=0; i<myngHEFrontEnd.size(); i++)
  {
    std::cout
              << " "
              << std::setw(6) << myngHEGeometry.at(i).side << std::setw(6) << myngHEGeometry.at(i).eta << std::setw(6) << myngHEGeometry.at(i).phi << std::setw(6) << myngHEGeometry.at(i).dphi << std::setw(6) << myngHEGeometry.at(i).depth << std::setw(6) << myngHEGeometry.at(i).subdet
              << std::setw(6) << myngHEFrontEnd.at(i).rbx 
              << std::setw(6) << myngHESiPM.at(i).wedge << std::setw(6) << myngHESiPM.at(i).bv
              << std::setw(6) << myngHEFrontEnd.at(i).qie11 << std::setw(6) << myngHEFrontEnd.at(i).qie11_ch << std::setw(6) << myngHEFrontEnd.at(i).rm << std::setw(6) << myngHEFrontEnd.at(i).rm_fiber << std::setw(6) << myngHEFrontEnd.at(i).fiber_ch
              << std::setw(6) << myngHEBackEnd.at(i).ppcol << std::setw(6) << myngHEBackEnd.at(i).pprow << std::setw(15) << myngHEBackEnd.at(i).ppcpl << std::setw(6) << myngHEBackEnd.at(i).pplc << std::setw(6) << myngHEBackEnd.at(i).dodec
              << std::setw(6) << myngHEBackEnd.at(i).ucrate << std::setw(6) << myngHEBackEnd.at(i).uhtr << std::setw(9) << myngHEBackEnd.at(i).uhtr_fiber
              << std::setw(6) << myngHEBackEnd.at(i).ufedid
              << std::setw(9) << myngHEFrontEnd.at(i).qie11_id
              << std::setw(6) << myngHETriggerTower.at(i).trg_fiber << std::setw(6) << myngHETriggerTower.at(i).trg_fiber_ch
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
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;

  for(auto i=0; i<myngHEFrontEnd.size(); i++)
  {
    if( myngHEGeometry.at(i).subdet == "HEX" ) continue;
    //if( myngHEFrontEnd.at(i).rbx != "HEP01" ) continue;
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
  //# eta phi depth det rbx rm
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

void HCALLMapDumper::printngHECalibLMapObject(std::vector<ngHECalib> myngHECalib)
{
  //Side Eta Phi dPhi Depth Det 
  //RBX Wedge
  //QIE11 QIECH RM RM_FI FI_CH 
  //Trunk cpCol cpRow cpCpl cpLC cpOct
  //ppCol ppRow ppCpl ppLC docdec 
  //Crate uHTR uHTR_FI 
  //FEDid 
  //QIE11id
  std::cout << "#Dumping ngHE Calib LMap Object..." << std::endl; 
  std::cout << "#"
            << std::setw(6) << "Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(9) << "CH_TYPE" << std::setw(10) << "Det"
            << std::setw(6) << "RBX" << std::setw(6) << "Wedge"
            << std::setw(6) << "QIE11" << std::setw(6) << "QIECH" << std::setw(3) << "RM" << std::setw(6) << "RM_FI" << std::setw(6) << "FI_CH"
            << std::setw(6) << "Trunk" << std::setw(6) << "cpCol" << std::setw(6) << "cpRow" << std::setw(9) << "cpCpl" << std::setw(6) << "cpLC" << std::setw(6) << "cpOct"
            << std::setw(6) << "ppCol" << std::setw(6) << "ppRow" << std::setw(9) << "ppCpl" << std::setw(6) << "ppLC" << std::setw(6) << "dodec"
            << std::setw(6) << "Crate" << std::setw(6) << "uHTR" << std::setw(9) << "uHTR_FI"
            << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE11id"
            << std::endl;

  for(auto i=0; i<myngHECalib.size(); i++)
  {
    std::cout
              << " "
              << std::setw(6) << myngHECalib.at(i).side << std::setw(6) << myngHECalib.at(i).eta << std::setw(6) << myngHECalib.at(i).phi << std::setw(6) << myngHECalib.at(i).dphi << std::setw(9) << myngHECalib.at(i).depth << std::setw(10) << myngHECalib.at(i).subdet
              << std::setw(6) << myngHECalib.at(i).rbx << std::setw(6) << myngHECalib.at(i).wedge
              << std::setw(6) << myngHECalib.at(i).qie11 << std::setw(6) << myngHECalib.at(i).qie11_ch << std::setw(3) << myngHECalib.at(i).rm << std::setw(6) << myngHECalib.at(i).rm_fiber << std::setw(6) << myngHECalib.at(i).fiber_ch
              << std::setw(6) << myngHECalib.at(i).trunk << std::setw(6) << myngHECalib.at(i).cpcol << std::setw(6) << myngHECalib.at(i).cprow << std::setw(9) << myngHECalib.at(i).cpcpl << std::setw(6) << myngHECalib.at(i).cplc << std::setw(6) << myngHECalib.at(i).cpoct
              << std::setw(6) << myngHECalib.at(i).ppcol << std::setw(6) << myngHECalib.at(i).pprow << std::setw(9) << myngHECalib.at(i).ppcpl << std::setw(6) << myngHECalib.at(i).pplc << std::setw(6) << myngHECalib.at(i).dodec
              << std::setw(6) << myngHECalib.at(i).ucrate << std::setw(6) << myngHECalib.at(i).uhtr << std::setw(9) << myngHECalib.at(i).uhtr_fiber
              << std::setw(6) << myngHECalib.at(i).ufedid
              << std::setw(9) << myngHECalib.at(i).qie11_id
              << std::endl;
  }

  return ;
}

void HCALLMapDumper::printngHECalibEMapObject(std::vector<ngHECalib> myngHECalib)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth                                                                                                                 
  std::cout << "#Dumping ngHECalib EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(9) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;
  
  for(auto i=0; i<myngHECalib.size(); i++)
  { 
    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myngHECalib.at(i).ucrate << std::setw(6) << myngHECalib.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myngHECalib.at(i).uhtr_fiber << std::setw(12) << myngHECalib.at(i).fiber_ch 
              << std::setw(9) << myngHECalib.at(i).subdet << std::setw(6) << myngHECalib.at(i).side * myngHECalib.at(i).eta << std::setw(6) << myngHECalib.at(i).phi << std::setw(6) << myngHECalib.at(i).depth
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
            << std::setw(6) << "TP_FI" << std::setw(6) << "TP_CH"
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
              << std::setw(6) << myngHFTriggerTower.at(i).trg_fiber << std::setw(6) << myngHFTriggerTower.at(i).trg_fiber_ch
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
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep" 
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

void HCALLMapDumper::printngHFCalibLMapObject(std::vector<ngHFCalib> myngHFCalib)
{
  //Side Eta Phi dPhi Depth Det 
  //RBX Sector
  //QIE10 QIECH QIE10_FI FI_CH 
  //ppCol ppRow ppCpl ppLC docdec 
  //Crate uHTR uHTR_FI 
  //FEDid 
  //QIE11id
  std::cout << "#Dumping ngHF Calib LMap Object..." << std::endl; 
  std::cout << "#"
            << std::setw(6) << "Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(9) << "CH_TYPE" << std::setw(10) << "Det"
            << std::setw(6) << "RBX" << std::setw(7) << "Sector"
            << std::setw(6) << "QIE10" << std::setw(6) << "QIECH" << std::setw(9) << "QIE10_FI" << std::setw(6) << "FI_CH"
            << std::setw(6) << "ppCol" << std::setw(6) << "ppRow" << std::setw(9) << "ppCpl" << std::setw(6) << "ppLC" << std::setw(6) << "dodec"
            << std::setw(6) << "Crate" << std::setw(6) << "uHTR" << std::setw(9) << "uHTR_FI"
            << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE10id" << std::setw(25) << "QIE10BarCode"
            << std::endl;

  for(auto i=0; i<myngHFCalib.size(); i++)
  {
    std::cout
              << " "
              << std::setw(6) << myngHFCalib.at(i).side << std::setw(6) << myngHFCalib.at(i).eta << std::setw(6) << myngHFCalib.at(i).phi << std::setw(6) << myngHFCalib.at(i).dphi << std::setw(9) << myngHFCalib.at(i).depth << std::setw(10) << myngHFCalib.at(i).subdet
              << std::setw(6) << myngHFCalib.at(i).rbx << std::setw(7) << myngHFCalib.at(i).sector
              << std::setw(6) << myngHFCalib.at(i).qie10 << std::setw(6) << myngHFCalib.at(i).qie10_ch << std::setw(9) << myngHFCalib.at(i).qie10_fiber << std::setw(6) << myngHFCalib.at(i).fiber_ch
              << std::setw(6) << myngHFCalib.at(i).ppcol << std::setw(6) << myngHFCalib.at(i).pprow << std::setw(9) << myngHFCalib.at(i).ppcpl << std::setw(6) << myngHFCalib.at(i).pplc << std::setw(6) << myngHFCalib.at(i).dodec
              << std::setw(6) << myngHFCalib.at(i).ucrate << std::setw(6) << myngHFCalib.at(i).uhtr << std::setw(9) << myngHFCalib.at(i).uhtr_fiber
              << std::setw(6) << myngHFCalib.at(i).ufedid
              << std::setw(9) << myngHFCalib.at(i).qie10_id << std::setw(25) << myngHFCalib.at(i).qie10_barcode
              << std::endl;
  }

  return ;
}

void HCALLMapDumper::printngHFCalibEMapObject(std::vector<ngHFCalib> myngHFCalib)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth                                                                                                                 
  std::cout << "#Dumping ngHFCalib EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(9) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;
  
  for(auto i=0; i<myngHFCalib.size(); i++)
  { 
    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myngHFCalib.at(i).ucrate << std::setw(6) << myngHFCalib.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myngHFCalib.at(i).uhtr_fiber << std::setw(12) << myngHFCalib.at(i).fiber_ch 
              << std::setw(9) << myngHFCalib.at(i).subdet << std::setw(6) << myngHFCalib.at(i).side * myngHFCalib.at(i).eta << std::setw(6) << myngHFCalib.at(i).phi << std::setw(6) << myngHFCalib.at(i).depth
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printHOLMapObject(std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower)
{
  //Side Eta Phi dPhi Depth Det
  //RBX 
  //Sect Pix Let_Code
  //QIE8 QIECH RM RM_FI FI_CH
  //Block_Coupler Crate HTR HTR_TB HTR_FI DCC_SL Spigot DCC FEDid
  //QIE8Id

  std::cout << "#Dumping HO LMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) <<"Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(6) << "Depth" << std::setw(6) << "Det"
            << std::setw(9) << "RBX"
            << std::setw(6) << "Sect" << std::setw(6) << "Pix" << std::setw(9) << "Let_Code"
            << std::setw(6) << "QIE8" << std::setw(6) << "QIECH" << std::setw(6) << "RM" << std::setw(6) << "RM_FI" << std::setw(6) << "FI_CH"
            << std::setw(15) << "Block_Coupler" << std::setw(6) << "Crate" << std::setw(6) << "HTR" << std::setw(6) << "HTRTB" << std::setw(9) << "HTR_FI" << std::setw(9) << "DCC_SL" << std::setw(9) << "Spigot" << std::setw(6) << "DCC" << std::setw(6) << "FEDid"
            << std::setw(9) << "QIE8id"
            << std::endl;

  for(auto i=0; i<myHOFrontEnd.size(); i++)
  { 
    std::cout 
              << " "
              //<< "HOGeometry(side,eta,phi,dphi,depth,subdet): "
              << std::setw(6) << myHOGeometry.at(i).side << std::setw(6) << myHOGeometry.at(i).eta << std::setw(6) << myHOGeometry.at(i).phi << std::setw(6) << myHOGeometry.at(i).dphi << std::setw(6) << myHOGeometry.at(i).depth << std::setw(6) << myHOGeometry.at(i).subdet
              //ngRBX
              << std::setw(9) << myHOFrontEnd.at(i).rbx
              //<< "HOSiPM(Sector, Pixel, Letter Code): "
              << std::setw(6) << myHOSiPM.at(i).sector << std::setw(6) << myHOSiPM.at(i).pixel << std::setw(9) << myHOSiPM.at(i).letter_code
              //<< "HOFrontEnd(qie8,qie8_ch,rm,rm_fiber,fiber_ch): "
              << std::setw(6) << myHOFrontEnd.at(i).qie8 << std::setw(6) << myHOFrontEnd.at(i).qie8_ch << std::setw(6) << myHOFrontEnd.at(i).rm << std::setw(6) << myHOFrontEnd.at(i).rm_fiber << std::setw(6)  << myHOFrontEnd.at(i).fiber_ch
              //<< "HOBackEnd(crate,htr,fpga,htr_fiber): "
              << std::setw(15) << myHOBackEnd.at(i).block_coupler << std::setw(6) << myHOBackEnd.at(i).crate << std::setw(6) << myHOBackEnd.at(i).htr << std::setw(6) << myHOBackEnd.at(i).fpga << std::setw(9) << myHOBackEnd.at(i).htr_fiber << std::setw(9) << myHOBackEnd.at(i).dcc_sl << std::setw(9) << myHOBackEnd.at(i).spigot << std::setw(6) << myHOBackEnd.at(i).dcc << std::setw(6) << myHOBackEnd.at(i).fedid
              //<< "HOFrontEnd(qie_id): "
              << std::setw(9) << myHOFrontEnd.at(i).qie8_id
              << std::endl;
  }

  return ;
}

void HCALLMapDumper::printHOEMapObject(std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower)
{ 
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping HO EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"  
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch" 
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;
    
  for(auto i=0; i<myHOFrontEnd.size(); i++)
  { 
    std::string emaptb = "";
    myHOBackEnd.at(i).fpga == "top" ? emaptb="t" : emaptb="b";
    int emapdepth = 0;
    myHOGeometry.at(i).subdet == "HOX" ? emapdepth = -999 : emapdepth = myHOGeometry.at(i).depth;
    std::cout 
              //<< "HOGeometry(side,eta,phi,depth): "
              << " " 
              << std::setw(10) << "4200458C"
              << std::setw(6) << myHOBackEnd.at(i).crate << std::setw(6) << myHOBackEnd.at(i).htr << std::setw(6) << emaptb << std::setw(6) << /*myHOBackEnd.at(i).dcc*/ myHOBackEnd.at(i).fedid-700 << std::setw(8) << myHOBackEnd.at(i).spigot << std::setw(8) << myHOBackEnd.at(i).htr_fiber << std::setw(12) << myHOBackEnd.at(i).fiber_ch
              << std::setw(8) << myHOGeometry.at(i).subdet << std::setw(6) << myHOGeometry.at(i).side * myHOGeometry.at(i).eta << std::setw(6) << myHOGeometry.at(i).phi << std::setw(6) << emapdepth
              << std::endl;
  }
  return ;
}

void HCALLMapDumper::printHOFrontEndMapObject(std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping HO FrontEnd Map Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(9) << "dep"
            << std::setw(8) << "subdet"
            << std::setw(6) << "rbx" << std::setw(6) << "rm"
            << std::endl;

  for(auto i=0; i<myHOFrontEnd.size(); i++)
  {
    if(myHOGeometry.at(i).subdet == "HOX") continue;
    std::cout
              //<< "HOGeometry(side,eta,phi,depth): "
              << " "
              << std::setw(6) << myHOGeometry.at(i).side * myHOGeometry.at(i).eta << std::setw(6) << myHOGeometry.at(i).phi << std::setw(6) << myHOGeometry.at(i).depth
              << std::setw(8) << myHOGeometry.at(i).subdet
              << std::setw(9) << myHOFrontEnd.at(i).rbx << std::setw(6) << myHOFrontEnd.at(i).rm
              << std::endl;
  }
  return ;
}

//Added by Yuan                                                                                                                                                                                             
void HCALLMapDumper::printHOCalibLMapObject(std::vector<HOCalib> myHOCalib)
{
  std::cout << "#Dumping HO Calib LMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(6) << "Side" << std::setw(6) << "Eta" << std::setw(6) << "Phi" << std::setw(6) << "dPhi" << std::setw(9) << "Depth" << std::setw(12) << "Det"
            << std::setw(9) << "RBX"
            << std::setw(6) << "Sect"
            << std::setw(6) << "RM" << std::setw(6) << "RM_FI" << std::setw(6) << "FI_CH"
            << std::setw(6) << "ppCol" << std::setw(6) << "ppRow" << std::setw(20) << "ppCpl" << std::setw(6) << "ppLC"
            << std::setw(6) << "Crate" << std::setw(6) << "HTR" << std::setw(6) << "fpga" << std::setw(9) << "HTR_FI"
            << std::setw(6) << "DCC" << std::setw(8) << "Spigot"
            << std::setw(9) << "QIE8id"
            << std::endl;

  for(auto i=0;i<myHOCalib.size();i++)
  {
    std::cout << " "
              << std::setw(6) << myHOCalib.at(i).side << std::setw(6) << myHOCalib.at(i).eta << std::setw(6) << myHOCalib.at(i).phi << std::setw(6) << myHOCalib.at(i).dphi << std::setw(9) << myHOCalib.at(i).depth << std::setw(12) << myHOCalib.at(i).subdet
              << std::setw(9) << myHOCalib.at(i).rbx
              << std::setw(6) << myHOCalib.at(i).sector
              << std::setw(6) << myHOCalib.at(i).rm << std::setw(6) << myHOCalib.at(i).rm_fiber << std::setw(6) << myHOCalib.at(i).fiber_ch
              << std::setw(6) << myHOCalib.at(i).ppcol << std::setw(6) << myHOCalib.at(i).pprow << std::setw(20) << myHOCalib.at(i).ppcpl << std::setw(6) << myHOCalib.at(i).pplc
              << std::setw(6) << myHOCalib.at(i).crate << std::setw(6) << myHOCalib.at(i).htr << std::setw(6) << myHOCalib.at(i).fpga << std::setw(9) << myHOCalib.at(i).htr_fiber
              << std::setw(6) << myHOCalib.at(i).dcc << std::setw(8) << myHOCalib.at(i).spigot
              << std::setw(9) << myHOCalib.at(i).qie8_id
              << std::endl;
  }
  return;
}

void HCALLMapDumper::makedbHBLMapObject(std::string HCALLMapDbStr, std::string HBTableStr,
                                        std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;

  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,HBTableStr);
  if(TableExist)
  { 
    std::cout << "#Table: " << HBTableStr <<" already in the database!! Please check!" << std::endl; return ;
  }
  else{ std::cout << "#Table: " << HBTableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det 
  //RBX 
  //Wedge Pix 
  //QIE8 QIECH RM RM_FI FI_CH 
  //ppCol ppRow ppCpl ppLC dodec 
  //Crate uHTR uHTR_FI FEDid 
  //QIE8id
  //TP_FI TP_CH
  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + HBTableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "RBX TEXT NOT NULL, " \
                            "Wedge INT NOT NULL, Pix INT NOT NULL, " \
                            "QIE8 INT NOT NULL, QIECH INT NOT NULL, RM INT NOT NULL, RM_FI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "ppCol INT NOT NULL, ppRow INT NOT NULL, ppCpl TEXT NOT NULL, ppLC INT NOT NULL, dodec INT NOT NULL, " \
                            "Crate INT NOT NULL, uHTR INT NOT NULL, uHTR_FI INT NOT NULL, FEDid INT NOT NULL, " \
                            "QIE8id INT NOT NULL, " \
                            "TP_FI INT NOT NULL, TP_CH INT NOT NULL);";
                    
  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }
  
  for(auto i=0; i<myHBFrontEnd.size(); i++)
  {
    std::string one = "INSERT INTO " + HBTableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "RBX," \
                      "Wedge,Pix," \
                      "QIE8,QIECH,RM,RM_FI,FI_CH," \
                      "ppCol,ppRow,ppCpl,ppLC,dodec," \
                      "Crate,uHTR,uHTR_FI,FEDid," \
                      "QIE8id," \
                      "TP_FI,TP_CH) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myHBGeometry.at(i).side)+","+std::to_string(myHBGeometry.at(i).eta)+","+std::to_string(myHBGeometry.at(i).phi)+","+std::to_string(myHBGeometry.at(i).dphi)+","+std::to_string(myHBGeometry.at(i).depth)+",'"+myHBGeometry.at(i).subdet+"','"
                      +myHBFrontEnd.at(i).rbx+"',"
                      +std::to_string(myHBHPD.at(i).wedge)+","+std::to_string(myHBHPD.at(i).pixel)+","
                      +std::to_string(myHBFrontEnd.at(i).qie8)+","+std::to_string(myHBFrontEnd.at(i).qie8_ch)+","+std::to_string(myHBFrontEnd.at(i).rm)+","+std::to_string(myHBFrontEnd.at(i).rm_fiber)+","+std::to_string(myHBFrontEnd.at(i).fiber_ch)+","
                      +std::to_string(myHBBackEnd.at(i).ppcol)+","+std::to_string(myHBBackEnd.at(i).pprow)+",'"+myHBBackEnd.at(i).ppcpl+"',"+std::to_string(myHBBackEnd.at(i).pplc)+","+std::to_string(myHBBackEnd.at(i).dodec)+","
                      +std::to_string(myHBBackEnd.at(i).ucrate)+","+std::to_string(myHBBackEnd.at(i).uhtr)+","+std::to_string(myHBBackEnd.at(i).uhtr_fiber)+","+std::to_string(myHBBackEnd.at(i).ufedid)+","
                      +std::to_string(myHBFrontEnd.at(i).qie8_id)+","
                      +std::to_string(myHBTriggerTower.at(i).trg_fiber)+","+std::to_string(myHBTriggerTower.at(i).trg_fiber_ch)+");";

    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg);
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);
  
  return ;
}

void HCALLMapDumper::makedbHBCalibLMapObject(std::string HCALLMapDbStr, std::string HBCalibTableStr, std::vector<HBCalib> myHBCalib)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;

  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,HBCalibTableStr);
  if(TableExist)
  { 
    std::cout << "#Table: " << HBCalibTableStr <<" already in the database!! Please check!" << std::endl; return ;
  }
  else{ std::cout << "#Table: " << HBCalibTableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det
  //RBX Wedge
  //QIE8 QIECH RM RM_FI FI_CH
  //Trunk cpCol cpRow cpCpl cpLC cpOct
  //ppCol ppRow ppCpl ppLC dodec
  //Crate uHTR uHTR_FI FEDid
  //QIE8id

  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + HBCalibTableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "RBX TEXT NOT NULL, Wedge INT NOT NULL, " \
                            "QIE8 INT NOT NULL, QIECH INT NOT NULL, RM INT NOT NULL, RM_FI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "Trunk TEXT NOT NULL, cpCol INT NOT NULL, cpRow INT NOT NULL, cpCpl TEXT NOT NULL, cpLC INT NOT NULL, cpOct INT NOT NULL, " \
                            "ppCol INT NOT NULL, ppRow INT NOT NULL, ppCpl TEXT NOT NULL, ppLC INT NOT NULL, dodec INT NOT NULL, " \
                            "Crate INT NOT NULL, uHTR INT NOT NULL, uHTR_FI INT NOT NULL, FEDid INT NOT NULL, " \
                            "QIE8id INT NOT NULL);";
                    
  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }
  
  for(auto i=0; i<myHBCalib.size(); i++)
  { 
    std::string one = "INSERT INTO " + HBCalibTableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "RBX,Wedge," \
                      "QIE8,QIECH,RM,RM_FI,FI_CH," \
                      "Trunk,cpCol,cpRow,cpCpl,cpLC,cpOct," \
                      "ppCol,ppRow,ppCpl,ppLC,dodec," \
                      "Crate,uHTR,uHTR_FI,FEDid," \
                      "QIE8id) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myHBCalib.at(i).side)+","+std::to_string(myHBCalib.at(i).eta)+","+std::to_string(myHBCalib.at(i).phi)+","+std::to_string(myHBCalib.at(i).dphi)+","+std::to_string(myHBCalib.at(i).depth)+",'"+myHBCalib.at(i).subdet+"','"
                      +myHBCalib.at(i).rbx+"',"+std::to_string(myHBCalib.at(i).wedge)+","
                      +std::to_string(myHBCalib.at(i).qie8)+","+std::to_string(myHBCalib.at(i).qie8_ch)+","+std::to_string(myHBCalib.at(i).rm)+","+std::to_string(myHBCalib.at(i).rm_fiber)+","+std::to_string(myHBCalib.at(i).fiber_ch)+",'"
                      +myHBCalib.at(i).trunk+"',"+std::to_string(myHBCalib.at(i).cpcol)+","+std::to_string(myHBCalib.at(i).cprow)+",'"+myHBCalib.at(i).cpcpl+"',"+std::to_string(myHBCalib.at(i).cplc)+","+std::to_string(myHBCalib.at(i).cpoct)+","
                      +std::to_string(myHBCalib.at(i).ppcol)+","+std::to_string(myHBCalib.at(i).pprow)+",'"+myHBCalib.at(i).ppcpl+"',"+std::to_string(myHBCalib.at(i).pplc)+","+std::to_string(myHBCalib.at(i).dodec)+","
                      +std::to_string(myHBCalib.at(i).ucrate)+","+std::to_string(myHBCalib.at(i).uhtr)+","+std::to_string(myHBCalib.at(i).uhtr_fiber)+","+std::to_string(myHBCalib.at(i).ufedid)+","
                      +std::to_string(myHBCalib.at(i).qie8_id)+");";
 
    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg); 
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);

  return ;
}

void HCALLMapDumper::makedbngHBLMapObject(std::string HCALLMapDbStr, std::string ngHBTableStr,
                                          std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;

  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,ngHBTableStr);
  if(TableExist){ std::cout << "#Table: " << ngHBTableStr <<" already in the database!! Please check!" << std::endl; return ; }
  else{ std::cout << "#Table: " << ngHBTableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det 
  //ngRBX 
  //Wedge Pix 
  //QIE11 QIECH RM RM_FI FI_CH 
  //ppCol ppRow ppCpl ppLC dodec 
  //Crate uHTR uHTR_FI FEDid 
  //QIE11id
  //TP_FI TP_CH
  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + ngHBTableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "ngRBX TEXT NOT NULL, " \
                            "Wedge INT NOT NULL, Pix INT NOT NULL, " \
                            "QIE11 INT NOT NULL, QIECH INT NOT NULL, RM INT NOT NULL, RM_FI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "ppCol INT NOT NULL, ppRow INT NOT NULL, ppCpl TEXT NOT NULL, ppLC INT NOT NULL, dodec INT NOT NULL, " \
                            "Crate INT NOT NULL, uHTR INT NOT NULL, uHTR_FI INT NOT NULL, FEDid INT NOT NULL, " \
                            "QIE11id INT NOT NULL, " \
                            "TP_FI INT NOT NULL, TP_CH INT NOT NULL);";
                    
  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }
  
  for(auto i=0; i<myngHBFrontEnd.size(); i++)
  {
    std::string one = "INSERT INTO " + ngHBTableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "ngRBX," \
                      "Wedge,Pix," \
                      "QIE11,QIECH,RM,RM_FI,FI_CH," \
                      "ppCol,ppRow,ppCpl,ppLC,dodec," \
                      "Crate,uHTR,uHTR_FI,FEDid," \
                      "QIE11id," \
                      "TP_FI,TP_CH) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myngHBGeometry.at(i).side)+","+std::to_string(myngHBGeometry.at(i).eta)+","+std::to_string(myngHBGeometry.at(i).phi)+","+std::to_string(myngHBGeometry.at(i).dphi)+","+std::to_string(myngHBGeometry.at(i).depth)+",'"+myngHBGeometry.at(i).subdet+"','"
                      +myngHBFrontEnd.at(i).rbx+"',"
                      +std::to_string(myngHBSiPM.at(i).wedge)+","+std::to_string(myngHBSiPM.at(i).bv)+","
                      +std::to_string(myngHBFrontEnd.at(i).qie11)+","+std::to_string(myngHBFrontEnd.at(i).qie11_ch)+","+std::to_string(myngHBFrontEnd.at(i).rm)+","+std::to_string(myngHBFrontEnd.at(i).rm_fiber)+","+std::to_string(myngHBFrontEnd.at(i).fiber_ch)+","
                      +std::to_string(myngHBBackEnd.at(i).ppcol)+","+std::to_string(myngHBBackEnd.at(i).pprow)+",'"+myngHBBackEnd.at(i).ppcpl+"',"+std::to_string(myngHBBackEnd.at(i).pplc)+","+std::to_string(myngHBBackEnd.at(i).dodec)+","
                      +std::to_string(myngHBBackEnd.at(i).ucrate)+","+std::to_string(myngHBBackEnd.at(i).uhtr)+","+std::to_string(myngHBBackEnd.at(i).uhtr_fiber)+","+std::to_string(myngHBBackEnd.at(i).ufedid)+","
                      +std::to_string(myngHBFrontEnd.at(i).qie11_id)+","
                      +std::to_string(myngHBTriggerTower.at(i).trg_fiber)+","+std::to_string(myngHBTriggerTower.at(i).trg_fiber_ch)+");";

    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg);
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);
  
  return ;
}

void HCALLMapDumper::makedbngHELMapObject(std::string HCALLMapDbStr, std::string ngHETableStr,
                                          std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;

  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,ngHETableStr);
  if(TableExist){ std::cout << "#Table: " << ngHETableStr <<" already in the database!! Please check!" << std::endl; return ; }
  else{ std::cout << "#Table: " << ngHETableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det 
  //ngRBX 
  //Wedge Pix 
  //QIE11 QIECH RM RM_FI FI_CH 
  //ppCol ppRow ppCpl ppLC dodec 
  //Crate uHTR uHTR_FI FEDid 
  //QIE11id
  //TP_FI TP_CH
  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + ngHETableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "ngRBX TEXT NOT NULL, " \
                            "Wedge INT NOT NULL, Pix INT NOT NULL, " \
                            "QIE11 INT NOT NULL, QIECH INT NOT NULL, RM INT NOT NULL, RM_FI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "ppCol INT NOT NULL, ppRow INT NOT NULL, ppCpl TEXT NOT NULL, ppLC INT NOT NULL, dodec INT NOT NULL, " \
                            "Crate INT NOT NULL, uHTR INT NOT NULL, uHTR_FI INT NOT NULL, FEDid INT NOT NULL, " \
                            "QIE11id INT NOT NULL, " \
                            "TP_FI INT NOT NULL, TP_CH INT NOT NULL);";
                    
  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }
  
  for(auto i=0; i<myngHEFrontEnd.size(); i++)
  {
    std::string one = "INSERT INTO " + ngHETableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "ngRBX," \
                      "Wedge,Pix," \
                      "QIE11,QIECH,RM,RM_FI,FI_CH," \
                      "ppCol,ppRow,ppCpl,ppLC,dodec," \
                      "Crate,uHTR,uHTR_FI,FEDid," \
                      "QIE11id," \
                      "TP_FI,TP_CH) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myngHEGeometry.at(i).side)+","+std::to_string(myngHEGeometry.at(i).eta)+","+std::to_string(myngHEGeometry.at(i).phi)+","+std::to_string(myngHEGeometry.at(i).dphi)+","+std::to_string(myngHEGeometry.at(i).depth)+",'"+myngHEGeometry.at(i).subdet+"','"
                      +myngHEFrontEnd.at(i).rbx+"',"
                      +std::to_string(myngHESiPM.at(i).wedge)+","+std::to_string(myngHESiPM.at(i).bv)+","
                      +std::to_string(myngHEFrontEnd.at(i).qie11)+","+std::to_string(myngHEFrontEnd.at(i).qie11_ch)+","+std::to_string(myngHEFrontEnd.at(i).rm)+","+std::to_string(myngHEFrontEnd.at(i).rm_fiber)+","+std::to_string(myngHEFrontEnd.at(i).fiber_ch)+","
                      +std::to_string(myngHEBackEnd.at(i).ppcol)+","+std::to_string(myngHEBackEnd.at(i).pprow)+",'"+myngHEBackEnd.at(i).ppcpl+"',"+std::to_string(myngHEBackEnd.at(i).pplc)+","+std::to_string(myngHEBackEnd.at(i).dodec)+","
                      +std::to_string(myngHEBackEnd.at(i).ucrate)+","+std::to_string(myngHEBackEnd.at(i).uhtr)+","+std::to_string(myngHEBackEnd.at(i).uhtr_fiber)+","+std::to_string(myngHEBackEnd.at(i).ufedid)+","
                      +std::to_string(myngHEFrontEnd.at(i).qie11_id)+","
                      +std::to_string(myngHETriggerTower.at(i).trg_fiber)+","+std::to_string(myngHETriggerTower.at(i).trg_fiber_ch)+");";

    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg);
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);
  
  return ;
}

void HCALLMapDumper::makedbngHECalibLMapObject(std::string HCALLMapDbStr, std::string ngHECalibTableStr, std::vector<ngHECalib> myngHECalib)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;
                                                                                                                                                                                                            
  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,ngHECalibTableStr);
  if(TableExist){ std::cout << "#Table: " << ngHECalibTableStr <<" already in the database!! Please check!" << std::endl; return ; }
  else{ std::cout << "#Table: " << ngHECalibTableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det 
  //RBX Wedge
  //QIE11 QIECH RM RM_FI FI_CH 
  //Trunk cpCol cpRow cpCpl cpLC cpOct
  //ppCol ppRow ppCpl ppLC docdec 
  //Crate uHTR uHTR_FI 
  //FEDid 
  //QIE11id

  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + ngHECalibTableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "ngRBX TEXT NOT NULL, Wedge INT NOT NULL, " \
                            "QIE11 INT NOT NULL, QIECH INT NOT NULL, RM INT NOT NULL, RM_FI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "Trunk TEXT NOT NULL, cpCol INT NOT NULL, cpRow INT NOT NULL, cpCpl TEXT NOT NULL, cpLC INT NOT NULL, cpOct INT NOT NULL, " \
                            "ppCol INT NOT NULL, ppRow INT NOT NULL, ppCpl TEXT NOT NULL, ppLC INT NOT NULL, dodec INT NOT NULL, " \
                            "Crate INT NOT NULL, uHTR INT NOT NULL, uHTR_FI INT NOT NULL, FEDid INT NOT NULL, " \
                            "QIE11id INT NOT NULL);";

  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }

  for(auto i=0; i<myngHECalib.size(); i++)
  {
    std::string one = "INSERT INTO " + ngHECalibTableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "ngRBX,Wedge," \
                      "QIE11,QIECH,RM,RM_FI,FI_CH," \
                      "Trunk,cpCol,cpRow,cpCpl,cpLC,cpOct," \
                      "ppCol,ppRow,ppCpl,ppLC,dodec," \
                      "Crate,uHTR,uHTR_FI,FEDid," \
                      "QIE11id) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myngHECalib.at(i).side)+","+std::to_string(myngHECalib.at(i).eta)+","+std::to_string(myngHECalib.at(i).phi)+","+std::to_string(myngHECalib.at(i).dphi)+","+std::to_string(myngHECalib.at(i).depth)+",'"+myngHECalib.at(i).subdet+"','"
                      +myngHECalib.at(i).rbx+"',"+std::to_string(myngHECalib.at(i).wedge)+","
                      +std::to_string(myngHECalib.at(i).qie11)+","+std::to_string(myngHECalib.at(i).qie11_ch)+","+std::to_string(myngHECalib.at(i).rm)+","+std::to_string(myngHECalib.at(i).rm_fiber)+","+std::to_string(myngHECalib.at(i).fiber_ch)+",'"
                      +myngHECalib.at(i).trunk+"',"+std::to_string(myngHECalib.at(i).cpcol)+","+std::to_string(myngHECalib.at(i).cprow)+",'"+myngHECalib.at(i).cpcpl+"',"+std::to_string(myngHECalib.at(i).cplc)+","+std::to_string(myngHECalib.at(i).cpoct)+","
                      +std::to_string(myngHECalib.at(i).ppcol)+","+std::to_string(myngHECalib.at(i).pprow)+",'"+myngHECalib.at(i).ppcpl+"',"+std::to_string(myngHECalib.at(i).pplc)+","+std::to_string(myngHECalib.at(i).dodec)+","
                      +std::to_string(myngHECalib.at(i).ucrate)+","+std::to_string(myngHECalib.at(i).uhtr)+","+std::to_string(myngHECalib.at(i).uhtr_fiber)+","+std::to_string(myngHECalib.at(i).ufedid)+","
                      +std::to_string(myngHECalib.at(i).qie11_id)+");";
    
    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg); 
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);

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
  //TP_FI TP_CH
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
                            "QIE10id INT NOT NULL, QIE10BarCode TEXT NOT NULL, " \
                            "TP_FI INT NOT NULL, TP_CH INT NOT NULL);";
                    
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
                      "QIE10id,QIE10BarCode," \
                      "TP_FI,TP_CH) ";
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
                      +std::to_string(myngHFFrontEnd.at(i).qie10_id)+",'"+myngHFFrontEnd.at(i).qie10_barcode+"',"
                      +std::to_string(myngHFTriggerTower.at(i).trg_fiber)+","+std::to_string(myngHFTriggerTower.at(i).trg_fiber_ch)+");";

    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg);
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);
  
  return ;
}

void HCALLMapDumper::makedbngHFCalibLMapObject(std::string HCALLMapDbStr, std::string ngHFCalibTableStr, std::vector<ngHFCalib> myngHFCalib)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;
                                                                                                                                                                                                            
  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,ngHFCalibTableStr);
  if(TableExist){ std::cout << "#Table: " << ngHFCalibTableStr <<" already in the database!! Please check!" << std::endl; return ; }
  else{ std::cout << "#Table: " << ngHFCalibTableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det 
  //RBX Sector
  //QIE10 QIECH QIE10_FI FI_CH 
  //ppCol ppRow ppCpl ppLC docdec 
  //Crate uHTR uHTR_FI 
  //FEDid 
  //QIE10id QIE10BarCode

  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + ngHFCalibTableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "ngRBX TEXT NOT NULL, Sector INT NOT NULL, " \
                            "QIE10 INT NOT NULL, QIECH INT NOT NULL, QIE10_FI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "ppCol INT NOT NULL, ppRow INT NOT NULL, ppCpl TEXT NOT NULL, ppLC INT NOT NULL, dodec INT NOT NULL, " \
                            "Crate INT NOT NULL, uHTR INT NOT NULL, uHTR_FI INT NOT NULL, FEDid INT NOT NULL, " \
                            "QIE10id INT NOT NULL, QIE10BarCode TEXT NOT NULL);";

  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }

  for(auto i=0; i<myngHFCalib.size(); i++)
  {
    std::string one = "INSERT INTO " + ngHFCalibTableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "ngRBX,Sector," \
                      "QIE10,QIECH,QIE10_FI,FI_CH," \
                      "ppCol,ppRow,ppCpl,ppLC,dodec," \
                      "Crate,uHTR,uHTR_FI,FEDid," \
                      "QIE10id,QIE10BarCode) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myngHFCalib.at(i).side)+","+std::to_string(myngHFCalib.at(i).eta)+","+std::to_string(myngHFCalib.at(i).phi)+","+std::to_string(myngHFCalib.at(i).dphi)+","+std::to_string(myngHFCalib.at(i).depth)+",'"+myngHFCalib.at(i).subdet+"','"
                      +myngHFCalib.at(i).rbx+"',"+std::to_string(myngHFCalib.at(i).sector)+","
                      +std::to_string(myngHFCalib.at(i).qie10)+","+std::to_string(myngHFCalib.at(i).qie10_ch)+","+std::to_string(myngHFCalib.at(i).qie10_fiber)+","+std::to_string(myngHFCalib.at(i).fiber_ch)+","
                      +std::to_string(myngHFCalib.at(i).ppcol)+","+std::to_string(myngHFCalib.at(i).pprow)+",'"+myngHFCalib.at(i).ppcpl+"',"+std::to_string(myngHFCalib.at(i).pplc)+","+std::to_string(myngHFCalib.at(i).dodec)+","
                      +std::to_string(myngHFCalib.at(i).ucrate)+","+std::to_string(myngHFCalib.at(i).uhtr)+","+std::to_string(myngHFCalib.at(i).uhtr_fiber)+","+std::to_string(myngHFCalib.at(i).ufedid)+","
                      +std::to_string(myngHFCalib.at(i).qie10_id)+",'"+myngHFCalib.at(i).qie10_barcode+"');";
    
    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg); 
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);

  return ;
}

void HCALLMapDumper::makedbHOCalibLMapObject(std::string HCALLMapDbStr, std::string HOCalibTableStr, std::vector<HOCalib> myHOCalib)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;

  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,HOCalibTableStr);
  if(TableExist)
  { 
    std::cout << "#Table: " << HOCalibTableStr <<" already in the database!! Please check!" << std::endl; return ;
  }
  else{ std::cout << "#Table: " << HOCalibTableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det
  //RBX 
  //RM RM_FI FI_CH
  //ppCol ppRow ppCpl ppLC
  //Crate HTR FPGA HTR_FI Spigot DCC
  //QIE8id

  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + HOCalibTableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "RBX TEXT NOT NULL, " \
                            "RM INT NOT NULL, RM_FI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "ppCol INT NOT NULL, ppRow INT NOT NULL, ppCpl TEXT NOT NULL, ppLC INT NOT NULL, " \
                            "Crate INT NOT NULL, HTR INT NOT NULL, FPGA INT NOT NULL, HTR_FI INT NOT NULL, Spigot INT NOT NULL, DCC INT NOT NULL, " \
                            "QIE8id INT NOT NULL);";
                    
  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }
  
  for(auto i=0; i<myHOCalib.size(); i++)
  { 
    std::string one = "INSERT INTO " + HOCalibTableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "RBX," \
                      "RM,RM_FI,FI_CH," \
                      "ppCol,ppRow,ppCpl,ppLC," \
                      "Crate,HTR,FPGA,HTR_FI,Spigot,DCC," \
                      "QIE8id) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myHOCalib.at(i).side)+","+std::to_string(myHOCalib.at(i).eta)+","+std::to_string(myHOCalib.at(i).phi)+","+std::to_string(myHOCalib.at(i).dphi)+","+std::to_string(myHOCalib.at(i).depth)+",'"+myHOCalib.at(i).subdet+"','"
                      +myHOCalib.at(i).rbx+"',"
                      +std::to_string(myHOCalib.at(i).rm)+","+std::to_string(myHOCalib.at(i).rm_fiber)+","+std::to_string(myHOCalib.at(i).fiber_ch)+","
//                      +myHOCalib.at(i).trunk+"',"+std::to_string(myHOCalib.at(i).cpcol)+","+std::to_string(myHOCalib.at(i).cprow)+",'"+myHOCalib.at(i).cpcpl+"',"+std::to_string(myHOCalib.at(i).cplc)+","+std::to_string(myHOCalib.at(i).cpoct)+","
                      +std::to_string(myHOCalib.at(i).ppcol)+","+std::to_string(myHOCalib.at(i).pprow)+",'"+myHOCalib.at(i).ppcpl+"',"+std::to_string(myHOCalib.at(i).pplc)+","
                      +std::to_string(myHOCalib.at(i).crate)+","+std::to_string(myHOCalib.at(i).htr)+",'"+myHOCalib.at(i).fpga+"',"+std::to_string(myHOCalib.at(i).htr_fiber)+","+std::to_string(myHOCalib.at(i).spigot)+","+std::to_string(myHOCalib.at(i).dcc)+","
                      +std::to_string(myHOCalib.at(i).qie8_id)+");";
 
    rc = sqlite3_exec(db, (one+two).c_str(), 0, 0, &zErrMsg); 
    if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
    else{ fprintf(stdout, "#%d Records created successfully!\n", i+1); }
  }
  sqlite3_close(db);

  return ;
 

}

void HCALLMapDumper::makedbHOLMapObject(std::string HCALLMapDbStr, std::string HOTableStr,
                                        std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower)
{
  sqlite3 *db;
  char *zErrMsg = 0; int rc;

  rc = sqlite3_open(HCALLMapDbStr.c_str(), &db);
  if( rc ){ fprintf(stderr, "#Can't open database: %s\n", sqlite3_errmsg(db)); return ; }
  else{ fprintf(stderr, "#Opened database successfully\n"); }

  //Check if table in the database already??
  bool TableExist = ifTableExistInDB(db,HOTableStr);
  if(TableExist){ std::cout << "#Table: " << HOTableStr <<" already in the database!! Please check!" << std::endl; return ; }
  else{ std::cout << "#Table: " << HOTableStr <<" not in the database... Creating..." << std::endl; }

  //Create Table in SQL
  //i(Unique key)
  //Side Eta Phi dPhi Depth Det
  //RBX 
  //Sect Pix Let_Code
  //QIE8 QIECH RM RM_FI FI_CH
  //Block_Coupler Crate HTR HTR_TB HTR_FI DCC_SL Spigot DCC FEDid
  //QIE8Id

  std::string CreateTable = "CREATE TABLE IF NOT EXISTS " + HOTableStr + "(" \
                            "ID INT PRIMARY KEY NOT NULL, " \
                            "Side INT NOT NULL, Eta INT NOT NULL, Phi INT NOT NULL, dPhi INT NOT NULL, Depth INT NOT NULL, Det TEXT NOT NULL, " \
                            "RBX TEXT NOT NULL, " \
                            "Sect INT NOT NULL, Pix INT NOT NULL, Let_Code TEXT NOT NULL, " \
                            "QIE8 INT NOT NULL, QIECH INT NOT NULL, RM INT NOT NULL, RM_FI INT NOT NULL, FI_CH INT NOT NULL, " \
                            "Block_Coupler REAL NOT NULL, Crate INT NOT NULL, HTR INT NOT NULL, HTR_TB TEXT NOT NULL, HTR_FI INT NOT NULL, DCC_SL INT NOT NULL, Spigot INT NOT NULL, DCC INT NOT NULL, FEDid INT NOT NULL, " \
                            "QIE8id INT NOT NULL);";
                    
  rc = sqlite3_exec(db, CreateTable.c_str(), 0, 0, &zErrMsg);
  if( rc != SQLITE_OK ){ fprintf(stderr, "SQL error: %s\n", zErrMsg); sqlite3_free(zErrMsg); }
  else{ fprintf(stdout, "#Table created successfully\n"); }
  
  for(auto i=0; i<myHOFrontEnd.size(); i++)
  {
    std::string one = "INSERT INTO " + HOTableStr + "(" \
                      "ID," \
                      "Side,Eta,Phi,dPhi,Depth,Det," \
                      "RBX," \
                      "Sect,Pix,Let_Code," \
                      "QIE8,QIECH,RM,RM_FI,FI_CH," \
                      "Block_Coupler,Crate,HTR,HTR_TB,HTR_FI,DCC_SL,Spigot,DCC,FEDid," \
                      "QIE8id) ";
    std::string two = "VALUES("
                      +std::to_string(i)+","
                      +std::to_string(myHOGeometry.at(i).side)+","+std::to_string(myHOGeometry.at(i).eta)+","+std::to_string(myHOGeometry.at(i).phi)+","+std::to_string(myHOGeometry.at(i).dphi)+","+std::to_string(myHOGeometry.at(i).depth)+",'"+myHOGeometry.at(i).subdet+"','"
                      +myHOFrontEnd.at(i).rbx+"',"
                      +std::to_string(myHOSiPM.at(i).sector)+","+std::to_string(myHOSiPM.at(i).pixel)+",'"+myHOSiPM.at(i).letter_code+"',"
                      +std::to_string(myHOFrontEnd.at(i).qie8)+","+std::to_string(myHOFrontEnd.at(i).qie8_ch)+","+std::to_string(myHOFrontEnd.at(i).rm)+","+std::to_string(myHOFrontEnd.at(i).rm_fiber)+","+std::to_string(myHOFrontEnd.at(i).fiber_ch)+","
                      +std::to_string(myHOBackEnd.at(i).block_coupler)+","+std::to_string(myHOBackEnd.at(i).crate)+","+std::to_string(myHOBackEnd.at(i).htr)+",'"+myHOBackEnd.at(i).fpga+"',"+std::to_string(myHOBackEnd.at(i).htr_fiber)+","+std::to_string(myHOBackEnd.at(i).dcc_sl)+","+std::to_string(myHOBackEnd.at(i).spigot)+","+std::to_string(myHOBackEnd.at(i).dcc)+","+std::to_string(myHOBackEnd.at(i).fedid)+","
                      +std::to_string(myHOFrontEnd.at(i).qie8_id)+");";

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
