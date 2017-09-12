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
