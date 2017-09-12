#include "HCALTPProducer.h"

void HCALTPProducer::printHBHTEMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping HB HT EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;

  for(auto i=0; i<myHBFrontEnd.size(); i++)
  {
    //sum over depth, 2304 HB HT channels in total. (14*72+2*72)*2=2304
    if(myHBGeometry.at(i).depth!=1) continue;
    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myHBBackEnd.at(i).ucrate << std::setw(6) << myHBBackEnd.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myHBTriggerTower.at(i).trg_fiber << std::setw(12) << myHBTriggerTower.at(i).trg_fiber_ch
              << std::setw(8) << "HT" << std::setw(6) << myHBGeometry.at(i).side * myHBGeometry.at(i).eta << std::setw(6) << myHBGeometry.at(i).phi << std::setw(6) << 0
              << std::endl;
  }
  return ;
}

void HCALTPProducer::printngHBHTEMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping ngHB HT EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;

  for(auto i=0; i<myngHBFrontEnd.size(); i++)
  {
    //sum over depth, 2304 ngHB HT channels in total. (14*72+2*72)*2=2304
    if(myngHBGeometry.at(i).depth!=1) continue;
    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myngHBBackEnd.at(i).ucrate << std::setw(6) << myngHBBackEnd.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myngHBTriggerTower.at(i).trg_fiber << std::setw(12) << myngHBTriggerTower.at(i).trg_fiber_ch
              << std::setw(8) << "HT" << std::setw(6) << myngHBGeometry.at(i).side * myngHBGeometry.at(i).eta << std::setw(6) << myngHBGeometry.at(i).phi << std::setw(6) << 0
              << std::endl;
  }
  return ;
}

void HCALTPProducer::printngHEHTEMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower)
{
  //#       i  cr  sl  tb  dcc  spigot  fiber/slb  fibcha/slbcha  subdet  ieta  iphi  depth
  std::cout << "#Dumping ngHE HT EMap Object..." << std::endl;
  std::cout << "#"
            << std::setw(10) <<"i"
            << std::setw(6) << "cr" << std::setw(6) << "sl" << std::setw(6) << "tb" << std::setw(6) << "dcc" << std::setw(8) << "spigot" << std::setw(8) << "fib/slb" << std::setw(12) << "fibch/slbch"
            << std::setw(8) << "subdet" << std::setw(6) << "eta" << std::setw(6) << "phi" << std::setw(6) << "dep"
            << std::endl;

  for(auto i=0; i<myngHEFrontEnd.size(); i++)
  {
    //sum over depth, 17,18,19,20,21,22,23,24,25,26,27,28, 12*72*2=1728 ngHE HT channels in total.eta 16 go with HB, eta 29 go with HF?, dpho==2 have a split
    if(myngHEGeometry.at(i).eta==17){ if(myngHEGeometry.at(i).depth!=2 ) continue; }
    else if(myngHEGeometry.at(i).eta==29) continue;//rule out eta 29
    else{ if(myngHEGeometry.at(i).depth!=1 ) continue; }//rule out eta 16, sum over depth, and HEX

    std::cout << " "
              << std::setw(10) << "4200458C"
              << std::setw(6) << myngHEBackEnd.at(i).ucrate << std::setw(6) << myngHEBackEnd.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myngHETriggerTower.at(i).trg_fiber << std::setw(12) << myngHETriggerTower.at(i).trg_fiber_ch
              << std::setw(8) << "HT" << std::setw(6) << myngHEGeometry.at(i).side * myngHEGeometry.at(i).eta << std::setw(6) << myngHEGeometry.at(i).phi << std::setw(6) << 0
              << std::endl;
    if(myngHEGeometry.at(i).dphi==2)//split dphi == 2 case
    {
      std::cout << " "
                << std::setw(10) << "4200458C"
                << std::setw(6) << myngHEBackEnd.at(i).ucrate << std::setw(6) << myngHEBackEnd.at(i).uhtr << std::setw(6) << "u" << std::setw(6) << 0 << std::setw(8) << 0 << std::setw(8) << myngHETriggerTower.at(i).trg_fiber << std::setw(12) << myngHETriggerTower.at(i).trg_fiber_ch+1
                << std::setw(8) << "HT" << std::setw(6) << myngHEGeometry.at(i).side * myngHEGeometry.at(i).eta << std::setw(6) << myngHEGeometry.at(i).phi+1 << std::setw(6) << 0
                << std::endl;

    }
  }
  return ;
}
