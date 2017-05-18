#include "HBMappingAlgorithm.h"
void HBMappingAlgorithm::ConstructHBLMapObject()
{
  std::cout << "#Constructing HB LMap Object..." << std::endl;

  for(int irbx=0;irbx<NrbxHB*2;irbx++)
  {
    for(int irm=0;irm<NrmHB;irm++)
    {
      for(int irmfi=0;irmfi<Nrm_fiber;irmfi++)
      {
        for(int ifich=0;ifich<Nfiber_ch;ifich++)
        {
          int sideid; irbx<NrbxHB ? sideid = 1 : sideid = -1;//0..to 11 is P side, while 12 to 23 is M side
          int rbxrmid; irbx<NrbxHB ? rbxrmid = irbx*NrmHB+irm : rbxrmid = (irbx-NrbxHB)*NrmHB+irm;//HB 0...to 35
          int rmfifichid = irmfi*Nfiber_ch+ifich;//HB 0...to 23

          ConstructHBFrontEnd(sideid,rbxrmid,rmfifichid);      
          ConstructHBBackEnd(sideid,rbxrmid,rmfifichid);  
          ConstructHBGeometry(sideid,rbxrmid,rmfifichid);
          ConstructHBHPD();  
          ConstructHBTriggerTower();
        }
      }
    }
  }
  return ;
}

void HBMappingAlgorithm::ConstructHBFrontEnd(int sideid, int rbxrmid, int rmfifichid)
{
  HBFrontEnd thisHBFrontEnd;
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmHB + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmHB + 1) : numberletter = std::to_string(rbxrmid/NrmHB + 1); 
  thisHBFrontEnd.rbx = "HB" + sideletter + numberletter;
  thisHBFrontEnd.rm = rbxrmid%NrmHB + 1;
  thisHBFrontEnd.rm_fiber = rmfifichid/Nfiber_ch +1;
  thisHBFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie8 map
  thisHBFrontEnd.qie8 = (thisHBFrontEnd.rm_fiber -1)/2+1;
  thisHBFrontEnd.rm_fiber%2 != 0 ? thisHBFrontEnd.qie8_ch = thisHBFrontEnd.fiber_ch : thisHBFrontEnd.qie8_ch = 3 + (thisHBFrontEnd.fiber_ch+1)%3;

  myHBFrontEnd.push_back(thisHBFrontEnd);
  return ;
}

void HBMappingAlgorithm::ConstructHBBackEnd(int sideid, int rbxrmid, int rmfifichid)
{
  HBBackEnd thisHBBackEnd;
  //
  thisHBBackEnd.crate = HBcrateInrbxrmid[((rbxrmid+35)%36)/12];
  sideid>0 ? thisHBBackEnd.htr = (((rbxrmid+35)%36)%12)/2 + 13 : thisHBBackEnd.htr = (((rbxrmid+35)%36)%12)/2 + 2;
  rmfifichid<12 ? thisHBBackEnd.fpga = "top" : thisHBBackEnd.fpga = "bot";
  if(sideid>0){ rbxrmid%2 == 0 ? thisHBBackEnd.htr_fiber = (rmfifichid%12)/3 +5 : thisHBBackEnd.htr_fiber = (rmfifichid%12)/3 +1; }
  else{ rbxrmid%2 == 0 ? thisHBBackEnd.htr_fiber = (rmfifichid%12)/3 +1 : thisHBBackEnd.htr_fiber = (rmfifichid%12)/3 +5; }

  thisHBBackEnd.ucrate = HBucrateInrbxrmid[((rbxrmid+35)%36)/12];
  sideid>0 ? thisHBBackEnd.uhtr = (((rbxrmid+35)%36)%12)/2 + 7 : thisHBBackEnd.uhtr = (((rbxrmid+35)%36)%12)/2 + 1;
  thisHBBackEnd.ufpga = "uHTR";
  if(sideid>0)
  { 
    if( rbxrmid%2 == 0){ rmfifichid<12 ? thisHBBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 18 : thisHBBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 6; }
    else{ rmfifichid<12 ? thisHBBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 14 : thisHBBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 2; }
  }
  else
  { 
    if( rbxrmid%2 == 0){ rmfifichid<12 ? thisHBBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 14 : thisHBBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 2; }
    else{ rmfifichid<12 ? thisHBBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 18 : thisHBBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 6; }
  }

  thisHBBackEnd.fiber_ch = rmfifichid%3;

  //set secondary variables
  myHBBackEnd.push_back(thisHBBackEnd);
  return ;
}

void HBMappingAlgorithm::ConstructHBGeometry(int sideid, int rbxrmid, int rmfifichid)
{
  HBGeometry thisHBGeometry;

  thisHBGeometry.subdet = "HB";
  thisHBGeometry.side = sideid;
  
  if(rmfifichid == 12||rmfifichid == 18){ thisHBGeometry.phi = (((rbxrmid+35)%36)/2)*4+3; thisHBGeometry.dphi = 4; }
  else{ thisHBGeometry.phi = rbxrmid*2+1; thisHBGeometry.dphi = 2; }
  
  thisHBGeometry.eta = HBetaInrmfifichid[rmfifichid]; thisHBGeometry.depth = ((rmfifichid+6)%24/6)%2+1;
  
  myHBGeometry.push_back(thisHBGeometry);
  return ;
}

void HBMappingAlgorithm::ConstructHBHPD()
{
  HBHPD thisHBHPD;
  
  myHBHPD.push_back(thisHBHPD);
  return ;
}

void HBMappingAlgorithm::ConstructHBTriggerTower()
{
  HBTriggerTower thisHBTriggerTower;

  myHBTriggerTower.push_back(thisHBTriggerTower);
  return ;
}
