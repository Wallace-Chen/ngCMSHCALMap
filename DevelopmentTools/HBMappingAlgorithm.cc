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
          ConstructHBHPD(sideid,rbxrmid,rmfifichid);
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
  thisHBFrontEnd.rm_fiber = rmfifichid/Nfiber_ch + 2;
  thisHBFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie8 map
  thisHBFrontEnd.qie8 = (thisHBFrontEnd.rm_fiber -1)/2+1;
  thisHBFrontEnd.rm_fiber%2 == 0 ? thisHBFrontEnd.qie8_ch = thisHBFrontEnd.fiber_ch : thisHBFrontEnd.qie8_ch = 3 + (thisHBFrontEnd.fiber_ch+1)%3;
  //set tmp qie8 id
  thisHBFrontEnd.qie8_id = 999991;
  myHBFrontEnd.push_back(thisHBFrontEnd);
  return ;
}

void HBMappingAlgorithm::ConstructHBBackEnd(int sideid, int rbxrmid, int rmfifichid)
{
  HBBackEnd thisHBBackEnd;
  //set ucrate id from rbx and rm, 2016 and 2017 should be same
  thisHBBackEnd.ucrate = HBucrateInrbxrmid[((rbxrmid+4)%72)/8];
  //set the uhr slot from rbx and rm and rm_fiber : complicate!!
  //3 types of backend slot : pure HB(1,4,7,10), mixed HB ngHE(2,5,8,11), and pure ngHE(3,6,9,12)
  //mixed HB case : rm(rm fiber) 1(23),  2(23),  3(23),  4(23);
  //pure  HB case : rm(rm fiber) 1(4567),2(4567),3(4567),4(4567);
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmHB + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmHB + 1) : numberletter = std::to_string(rbxrmid/NrmHB + 1);
  std::string rbx = "HB" + sideletter + numberletter;
  int rm = rbxrmid%NrmHB + 1; int rm_fiber = rmfifichid/Nfiber_ch + 2;
  bool ismixed_HB = (rm_fiber==2 || rm_fiber==3);
  
  if(sideid>0)
  { 
    if( ismixed_HB ) (rbxrmid/4)%2==0 ? thisHBBackEnd.uhtr = 11 : thisHBBackEnd.uhtr = 8;
    else (rbxrmid/4)%2==0 ? thisHBBackEnd.uhtr = 10 : thisHBBackEnd.uhtr = 7;
  }
  else
  { 
    if( ismixed_HB ) (rbxrmid/4)%2==0 ? thisHBBackEnd.uhtr = 5 : thisHBBackEnd.uhtr = 2;
    else (rbxrmid/4)%2==0 ? thisHBBackEnd.uhtr = 4 : thisHBBackEnd.uhtr = 1;
  }
  //fpga variable for the backend, used to be useful in old HTR case....but we still keep a position for it now
  thisHBBackEnd.ufpga = "uHTR";
  //set uhtr fiber from patch panel
  //first set patch panel info, from front end side
  thisHBBackEnd.ppcol = (rm_fiber-1)/4+3;
  thisHBBackEnd.pprow = rm;
  thisHBBackEnd.pplc = (rm_fiber-1)%4+1;
  std::string cplletter;
  rm_fiber<=4 ? cplletter="A" : cplletter="B";
  thisHBBackEnd.ppcpl = rbx+"_RM"+std::to_string(rm)+cplletter;
  //then set uhtr fiber infomation from patch panel
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/ngHE/optical_patch.txt
  /*
  The P-side pure HB uHTR (xx indicates an empty spigot):
         HEM04                 HBM04                 HEP04                 HBP04
| -------- | -------- | -------- | -------- | -------- | -------- | xx----03 | 212223xx |  RM4
| -------- | -------- | -------- | -------- | -------- | -------- | xx----02 | 181920xx |  RM3
| -------- | -------- | -------- | -------- | -------- | -------- | xx----01 | 151617xx |  RM2
| -------- | -------- | -------- | -------- | -------- | -------- | xx----00 | 121314xx |  RM1

  The P-side mixed uHTR (xx indicates an empty spigot):

         HEM04                 HBM04                 HEP04                 HBP04
| -------- | -------- | -------- | -------- | ------17 | 22--23-- | xx0809-- | ------xx |  RM4
| -------- | -------- | -------- | -------- | --15--16 | --21---- | xx0607-- | ------xx |  RM3
| -------- | -------- | -------- | -------- | ------14 | 19--20-- | xx0405-- | ------xx |  RM2
| -------- | -------- | -------- | -------- | --12--13 | --18---- | xx0203-- | ------xx |  RM1
  */

  if( ismixed_HB )
  {
    if     (thisHBBackEnd.ppcol==3){ thisHBBackEnd.uhtr_fiber = (thisHBBackEnd.pprow-1)*2+rm_fiber-2+2; }
    else{ std::cout << "the ppCol of HB channel is not 3 in mixed HBHE slot for HB??!! Please check!" << std::endl; }
  }
  else
  {
    if     (thisHBBackEnd.ppcol==3){ thisHBBackEnd.uhtr_fiber = thisHBBackEnd.pprow-1; }
    else if(thisHBBackEnd.ppcol==4){ thisHBBackEnd.uhtr_fiber = (thisHBBackEnd.pprow-1)*3+rm_fiber-5+12; }
    else{ std::cout << "the ppCol of HB channel is neither 3 nor 4 in pure HB slot??!! Please check!" << std::endl; }
  }
  //finally set dodec from back end side
  thisHBBackEnd.dodec = (thisHBBackEnd.uhtr_fiber)%12+1;
  //set backend fiber channel : same as the front end one
  thisHBBackEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set tmp fed id
  //backend slot 7 to 12 odd number backend slot 1 to 6 even number, 
  const std::map<int, std::pair<int, int> > HBufedidInucrate = { {20,{1102,1103}},{21,{1104,1105}},{24,{1100,1101}},{25,{1106,1107}},{30,{1116,1117}},{31,{1108,1109}},{34,{1114,1115}},{35,{1110,1111}},{37,{1112,1113}} };
  thisHBBackEnd.uhtr <= 6 ? thisHBBackEnd.ufedid = ((HBufedidInucrate.find(thisHBBackEnd.ucrate))->second).first : thisHBBackEnd.ufedid = ((HBufedidInucrate.find(thisHBBackEnd.ucrate))->second).second;
  myHBBackEnd.push_back(thisHBBackEnd);
  return ;
}

void HBMappingAlgorithm::ConstructHBGeometry(int sideid, int rbxrmid, int rmfifichid)
{
  HBGeometry thisHBGeometry;
  //side -> subdet -> eta, depth -> dphi -> phi
  thisHBGeometry.side = sideid;
  
  thisHBGeometry.eta = HBetaInrmfifichid[rmfifichid]; 
  thisHBGeometry.depth = HBdepInrmfifichid[rmfifichid]; 
  thisHBGeometry.dphi = 1;

  if(sideid > 0)
  {
    thisHBGeometry.phi = HBphiInrbxrmid_P[rbxrmid];
  }
  else
  {
    thisHBGeometry.phi = HBphiInrbxrmid_M[rbxrmid];
  }
  
  thisHBGeometry.subdet = "HB";

  myHBGeometry.push_back(thisHBGeometry);
  ConstructHBTriggerTower(thisHBGeometry.eta, thisHBGeometry.phi);
  return ;
}

void HBMappingAlgorithm::ConstructHBHPD(int sideid, int rbxrmid, int rmfifichid)
{
  HBHPD thisHBHPD;
  thisHBHPD.wedge = rbxrmid/NrmHB+1;
  //to be honest, i never understand the root of pixel mapping in HB, i borrow it from old map code directly. It will die anyway when we move to sipm
  const int ipixelHB_loc[Nrm_fiber][Nfiber_ch][NrmHB] = 
  {  //  fch = 0           fch = 1           fch = 2
    {{18, 17, 3,  2 }, {13, 3,  17, 7 }, {14, 1,  19, 6 }}, //rmfiber = 2
    {{19, 2,  18, 1 }, {15, 7,  13, 5 }, {17, 19, 1,  3 }}, //rmfiber = 3
    {{9,  4,  16, 11}, {5,  8,  12, 15}, {2,  13, 7,  18}}, //rmfiber = 4
    {{12, 11, 9,  8 }, {7,  15, 5,  13}, {16, 6,  14, 4 }}, //rmfiber = 5
    {{8,  5,  15, 12}, {4,  9,  11, 16}, {1,  14, 6,  19}}, //rmfiber = 6
    {{6,  16, 4,  14}, {3,  18, 2,  17}, {11, 12, 8,  9 }}  //rmfiber = 7
  };
  int rmid = rbxrmid%NrmHB; int rmfiid = rmfifichid/Nfiber_ch; int fichid = rmfifichid%Nfiber_ch;
  thisHBHPD.pixel = ipixelHB_loc[rmfiid][fichid][rmid]; 
  myHBHPD.push_back(thisHBHPD);
  return ;
}

void HBMappingAlgorithm::ConstructHBTriggerTower(int eta, int phi)
{
  HBTriggerTower thisHBTriggerTower;
  thisHBTriggerTower.trg_fiber = -1;
  if(eta<=0 || phi<=0)
  {
    thisHBTriggerTower.trg_fiber = -1;
    thisHBTriggerTower.trg_fiber_ch = -1;
  }
  else
  {
    if(eta <= 20)
    {
      if     (eta >= 1  && eta <=12) thisHBTriggerTower.trg_fiber = (int)((eta-1)/2);
      else if(eta >= 13 && eta <=18) thisHBTriggerTower.trg_fiber = (int)((eta-13)/2);
      else thisHBTriggerTower.trg_fiber = 0;
    }
    else
    {
      if     (eta >= 21 && eta <=24) thisHBTriggerTower.trg_fiber = (int)((eta-21)/2) + 1;
      else if(eta >= 25 && eta <=26) thisHBTriggerTower.trg_fiber = 3;
      else thisHBTriggerTower.trg_fiber = 3;
    }
    thisHBTriggerTower.trg_fiber_ch = ((eta-1)%2)*4 + ((phi+69)%72)%4;
  }
  myHBTriggerTower.push_back(thisHBTriggerTower);
  return ;
}
