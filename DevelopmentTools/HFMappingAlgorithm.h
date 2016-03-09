#include <vector>
#include <iostream>

#include "HFMappingObject.h"

class HFMappingAlgorithm : public HFConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<HFFrontEnd> myHFFrontEnd; std::vector<HFBackEnd> myHFBackEnd; std::vector<HFPMTBox> myHFPMTBox; std::vector<HFGeometry> myHFGeometry; std::vector<HFTriggerTower> myHFTriggerTower;
  void ConstructHFLMapObject();
 private:
  void ConstructHFFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHFBackEnd(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructHFGeometry(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructHFPMTBox();      
  void ConstructHFTriggerTower();  

  const int HFcrateInrbxrmid[Ncrate] = {2,9,12};
  const int HFucrateInrbxrmid[Ncrate] = {22,29,32};
  const int HFetaInrmfifichidType1[Nrm_fiber*Nfiber_ch] = {33,31,29,32,30,34, 33,31,29,32,30,34, 41,37,35,38,36,39, 41,37,35,38,36,39};
  const int HFetaInrmfifichidType2[Nrm_fiber*Nfiber_ch] = {34,32,30,31,29,33, 34,32,30,31,29,33, 40,38,36,37,35,39, 40,38,36,37,35,39};
};

void HFMappingAlgorithm::ConstructHFLMapObject()
{
  std::cout << "Constructing HF LMap Object..." << std::endl;

  for(int irbx=0;irbx<NrbxHF*2;irbx++)
  {
    for(int irm=0;irm<NrmHF;irm++)
    {
      for(int irmfi=0;irmfi<Nrm_fiber;irmfi++)
      {
        for(int ifich=0;ifich<Nfiber_ch;ifich++)
        {
          int sideid; irbx<NrbxHF ? sideid = 1 : sideid = -1;//0..to 11 is P side, while 12 to 23 is M side
          int rbxrmid; irbx<NrbxHF ? rbxrmid = irbx*NrmHF+irm : rbxrmid = (irbx-NrbxHF)*NrmHF+irm;//HF 0...to 35
          int rmfifichid = irmfi*Nfiber_ch+ifich;//HF 0...to 23

          ConstructHFFrontEnd(sideid,rbxrmid,rmfifichid);      
          ConstructHFBackEnd(sideid,rbxrmid,rmfifichid);  
          ConstructHFGeometry(sideid,rbxrmid,rmfifichid);
          ConstructHFPMTBox();  
          ConstructHFTriggerTower();
        }
      }
    }
  }
  return ;
}

void HFMappingAlgorithm::ConstructHFFrontEnd(int sideid, int rbxrmid, int rmfifichid)
{
  HFFrontEnd thisHFFrontEnd;
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmHF + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmHF + 1) : numberletter = std::to_string(rbxrmid/NrmHF + 1); 
  thisHFFrontEnd.rbx = "HF" + sideletter + numberletter;
  thisHFFrontEnd.rm = rbxrmid%NrmHF + 1;
  thisHFFrontEnd.rm_fiber = rmfifichid/Nfiber_ch +1;
  thisHFFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie8 map
  thisHFFrontEnd.qie8 = (thisHFFrontEnd.rm_fiber -1)/2+1;
  thisHFFrontEnd.rm_fiber%2 != 0 ? thisHFFrontEnd.qie8_ch = thisHFFrontEnd.fiber_ch : thisHFFrontEnd.qie8_ch = 3 + (thisHFFrontEnd.fiber_ch+1)%3;
  //qie10 map
  //thisHFFrontEnd.qie10 = ;
  //thisHFFrontEnd.qie10_ch = ;

  myHFFrontEnd.push_back(thisHFFrontEnd);
  return ;
}

void HFMappingAlgorithm::ConstructHFBackEnd(int sideid, int rbxrmid, int rmfifichid)
{
  HFBackEnd thisHFBackEnd;
  //
  thisHFBackEnd.crate = HFcrateInrbxrmid[((rbxrmid+35)%36)/12];
  sideid>0 ? thisHFBackEnd.htr = (((rbxrmid+35)%36)%12)/2 + 13 : thisHFBackEnd.htr = (((rbxrmid+35)%36)%12)/2 + 2;
  rmfifichid<12 ? thisHFBackEnd.fpga = "top" : thisHFBackEnd.fpga = "bot";
  if(sideid>0){ rbxrmid%2 == 0 ? thisHFBackEnd.htr_fiber = (rmfifichid%12)/3 +5 : thisHFBackEnd.htr_fiber = (rmfifichid%12)/3 +1; }
  else{ rbxrmid%2 == 0 ? thisHFBackEnd.htr_fiber = (rmfifichid%12)/3 +1 : thisHFBackEnd.htr_fiber = (rmfifichid%12)/3 +5; }

  thisHFBackEnd.ucrate = HFucrateInrbxrmid[((rbxrmid+35)%36)/12];
  sideid>0 ? thisHFBackEnd.uhtr = (((rbxrmid+35)%36)%12)/2 + 7 : thisHFBackEnd.uhtr = (((rbxrmid+35)%36)%12)/2 + 1;
  thisHFBackEnd.ufpga = "uHTR";
  if(sideid>0)
  { 
    if( rbxrmid%2 == 0){ rmfifichid<12 ? thisHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 18 : thisHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 6; }
    else{ rmfifichid<12 ? thisHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 14 : thisHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 2; }
  }
  else
  { 
    if( rbxrmid%2 == 0){ rmfifichid<12 ? thisHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 14 : thisHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 2; }
    else{ rmfifichid<12 ? thisHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 18 : thisHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 6; }
  }

  thisHFBackEnd.fiber_ch = rmfifichid%3;

  //set secondary variables
  myHFBackEnd.push_back(thisHFBackEnd);
  return ;
}

void HFMappingAlgorithm::ConstructHFGeometry(int sideid, int rbxrmid, int rmfifichid)
{
  HFGeometry thisHFGeometry;

  thisHFGeometry.subdet = "HF";
  thisHFGeometry.side = sideid;
  
  if(rmfifichid == 12||rmfifichid == 18){ thisHFGeometry.phi = (((rbxrmid+35)%36)/2)*4+3; thisHFGeometry.dphi = 4; }
  else{ thisHFGeometry.phi = rbxrmid*2+1; thisHFGeometry.dphi = 2; }
  
  if(sideid > 0)
  { 
    if(rbxrmid%2 == 0){ thisHFGeometry.eta = HFetaInrmfifichidType2[rmfifichid]; thisHFGeometry.depth = ((rmfifichid+6)%24/6)%2+1; }
    else{ thisHFGeometry.eta = HFetaInrmfifichidType1[rmfifichid]; thisHFGeometry.depth = (rmfifichid/6)%2+1; }
  }
  else
  {
    if(rbxrmid%2 == 0){ thisHFGeometry.eta = HFetaInrmfifichidType1[rmfifichid]; thisHFGeometry.depth = (rmfifichid/6)%2+1; }
    else{ thisHFGeometry.eta = HFetaInrmfifichidType2[rmfifichid]; thisHFGeometry.depth = ((rmfifichid+6)%24/6)%2+1; }
  }
  myHFGeometry.push_back(thisHFGeometry);
  return ;
}

void HFMappingAlgorithm::ConstructHFPMTBox()
{
  HFPMTBox thisHFPMTBox;
  
  myHFPMTBox.push_back(thisHFPMTBox);
  return ;
}

void HFMappingAlgorithm::ConstructHFTriggerTower()
{
  HFTriggerTower thisHFTriggerTower;

  myHFTriggerTower.push_back(thisHFTriggerTower);
  return ;
}
