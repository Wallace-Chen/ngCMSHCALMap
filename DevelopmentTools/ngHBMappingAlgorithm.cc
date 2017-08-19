#include "ngHBMappingAlgorithm.h"

void ngHBMappingAlgorithm::ConstructngHBLMapObject()
{
  std::cout << "#Constructing ngHB LMap Object..." << std::endl;

  for(int irbx=0;irbx<NrbxngHB*2;irbx++)
  {
    for(int irm=0;irm<NrmngHB;irm++)
    {
      for(int irmfi=0;irmfi<Nrm_fiber;irmfi++)
      {
        for(int ifich=0;ifich<Nfiber_ch;ifich++)
        {
          int sideid; irbx<NrbxngHB ? sideid = 1 : sideid = -1;//0..to 17 is P side, while 17 to 35 is M side
          int rbxrmid; irbx<NrbxngHB ? rbxrmid = irbx*NrmngHB+irm : rbxrmid = (irbx-NrbxngHB)*NrmngHB+irm;//ngHB 0...to 71
          int rmfifichid = irmfi*Nfiber_ch+ifich;//ngHB 0...to 47

          ConstructngHBFrontEnd(sideid,rbxrmid,rmfifichid);      
          ConstructngHBBackEnd(sideid,rbxrmid,rmfifichid);  
          ConstructngHBGeometry(sideid,rbxrmid,rmfifichid);
          ConstructngHBSiPM();  
          ConstructngHBTriggerTower();
        }
      }
    }
  }
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBFrontEnd(int sideid, int rbxrmid, int rmfifichid)
{
  ngHBFrontEnd thisngHBFrontEnd;
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHB + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHB + 1) : numberletter = std::to_string(rbxrmid/NrmngHB + 1); 
  //thisngHBFrontEnd.rbx = "ngHB" + sideletter + numberletter;
  thisngHBFrontEnd.rbx = "HB" + sideletter + numberletter;
  thisngHBFrontEnd.rm = rbxrmid%NrmngHB + 1;
  thisngHBFrontEnd.rm_fiber = rmfifichid/Nfiber_ch + 2;
  thisngHBFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie11 map
  thisngHBFrontEnd.qie11 = (thisngHBFrontEnd.rm_fiber -1)/2+1;
  thisngHBFrontEnd.rm_fiber%2 != 0 ? thisngHBFrontEnd.qie11_ch = thisngHBFrontEnd.fiber_ch : thisngHBFrontEnd.qie11_ch = 3 + (thisngHBFrontEnd.fiber_ch+1)%3;
  thisngHBFrontEnd.qie11_id = 999991;
  myngHBFrontEnd.push_back(thisngHBFrontEnd);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBBackEnd(int sideid, int rbxrmid, int rmfifichid)
{
  ngHBBackEnd thisngHBBackEnd;
  //set ucrate id from rbx and rm, 2016 and 2017 should be same
  thisngHBBackEnd.ucrate = ngHBucrateInrbxrmid[((rbxrmid+4)%72)/8];
  //set the uhr slot from rbx and rm and rm_fiber : complicate!!
  //3 types of backend slot : pure HB(1,4,7,10), mixed HB ngHE(2,5,8,11), and pure ngHE(3,6,9,12)
  //mixed ngHB case : rm(rm fiber) 1(23),  2(23),  3(23),  4(23);
  //pure  ngHB case : rm(rm fiber) 1(4567),2(4567),3(4567),4(4567);
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHB + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHB + 1) : numberletter = std::to_string(rbxrmid/NrmngHB + 1);
  std::string rbx = "HB" + sideletter + numberletter;
  int rm = rbxrmid%NrmngHB + 1; int rm_fiber = rmfifichid/Nfiber_ch + 2;
  bool ismixed_ngHB = (rm_fiber==2 || rm_fiber==3);

  if(sideid>0)
  { 
    if( ismixed_ngHB ) (rbxrmid/4)%2==0 ? thisngHBBackEnd.uhtr = 11 : thisngHBBackEnd.uhtr = 8;
    else (rbxrmid/4)%2==0 ? thisngHBBackEnd.uhtr = 10 : thisngHBBackEnd.uhtr = 7;
  }
  else
  { 
    if( ismixed_ngHB ) (rbxrmid/4)%2==0 ? thisngHBBackEnd.uhtr = 5 : thisngHBBackEnd.uhtr = 2;
    else (rbxrmid/4)%2==0 ? thisngHBBackEnd.uhtr = 4 : thisngHBBackEnd.uhtr = 1;
  }

  //fpga variable for the backend, used to be useful in old HTR case....but we still keep a position for it now
  thisngHBBackEnd.ufpga = "uHTR";
  //set uhtr fiber from patch panel
  //first set patch panel info, from front end side
  thisngHBBackEnd.ppcol = (rm_fiber-1)/4+3;
  thisngHBBackEnd.pprow = rm;
  thisngHBBackEnd.pplc = (rm_fiber-1)%4+1;
  std::string cplletter;
  rm_fiber<=4 ? cplletter="A" : cplletter="B";
  thisngHBBackEnd.ppcpl = rbx+"_RM"+std::to_string(rm)+cplletter;
  //then set uhtr fiber infomation from patch panel
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/ngHE/optical_patch.txt
  if( ismixed_ngHB )
  {
    if     (thisngHBBackEnd.ppcol==3){ thisngHBBackEnd.uhtr_fiber = (thisngHBBackEnd.pprow-1)*2+rm_fiber-2+2; }
    else{ std::cout << "the ppCol of HB channel is not 3 in mixed HBHE slot for HB??!! Please check!" << std::endl; }
  }
  else
  {
    if     (thisngHBBackEnd.ppcol==3){ thisngHBBackEnd.uhtr_fiber = thisngHBBackEnd.pprow-1; }
    else if(thisngHBBackEnd.ppcol==4){ thisngHBBackEnd.uhtr_fiber = (thisngHBBackEnd.pprow-1)*3+rm_fiber-5+12; }
    else{ std::cout << "the ppCol of HB channel is neither 3 nor 4 in pure HB slot??!! Please check!" << std::endl; }
  }
  //finally set dodec from back end side
  thisngHBBackEnd.dodec = (thisngHBBackEnd.uhtr_fiber)%12+1;
  //set backend fiber channel : same as the front end one
  thisngHBBackEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set tmp fed id
  thisngHBBackEnd.ufedid = thisngHBBackEnd.ucrate + 1100 -20;
  myngHBBackEnd.push_back(thisngHBBackEnd);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBGeometry(int sideid, int rbxrmid, int rmfifichid)
{
  ngHBGeometry thisngHBGeometry;
  //side -> subdet -> eta, depth -> dphi -> phi
  thisngHBGeometry.side = sideid;
  
  thisngHBGeometry.eta = ngHBetaInrmfifichid[rmfifichid]; 
  thisngHBGeometry.depth = ngHBdepInrmfifichid[rmfifichid]; 
  thisngHBGeometry.dphi = 1;

  if(sideid > 0)
  {
    thisngHBGeometry.phi = ngHBphiInrbxrmid_P[rbxrmid];
  }
  else
  {
    thisngHBGeometry.phi = ngHBphiInrbxrmid_M[rbxrmid];
  }
  
  thisngHBGeometry.subdet = "HB";

  /*
  //No HBX channel in 2017 HB (not ngHB)
  //Over write everything for HBX channels ?
  ( (rbxrmid%4==1 && rmfifichid==29 ) || (rbxrmid%4==1 && rmfifichid==37 ) || (rbxrmid%4==2 && rmfifichid==7 ) || (rbxrmid%4==2 && rmfifichid==18 ) ) ? thisngHBGeometry.subdet = "HBX" : thisngHBGeometry.subdet = "HB";

  if(thisngHBGeometry.subdet == "HBX") 
  {
    //cross check HBX channel with ngHBetaInrmfifichid array
    if(thisngHBGeometry.eta!=0 || thisngHBGeometry.depth!=0) std::cout << "Wrong HBX channel map!" << std::endl;
    thisngHBGeometry.eta = 0;
    thisngHBGeometry.phi = 0;
    thisngHBGeometry.depth = 0;
    thisngHBGeometry.dphi = 0;
  }
  */
  myngHBGeometry.push_back(thisngHBGeometry);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBSiPM()
{
  ngHBSiPM thisngHBSiPM;
  
  myngHBSiPM.push_back(thisngHBSiPM);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBTriggerTower()
{
  ngHBTriggerTower thisngHBTriggerTower;

  myngHBTriggerTower.push_back(thisngHBTriggerTower);
  return ;
}
