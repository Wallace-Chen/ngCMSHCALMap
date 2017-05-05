#include "ngHEMappingAlgorithm.h"

void ngHEMappingAlgorithm::ConstructngHELMapObject()
{
  std::cout << "#Constructing ngHE LMap Object..." << std::endl;

  for(int irbx=0;irbx<NrbxngHE*2;irbx++)
  {
    for(int irm=0;irm<NrmngHE;irm++)
    {
      for(int irmfi=0;irmfi<Nrm_fiber;irmfi++)
      {
        for(int ifich=0;ifich<Nfiber_ch;ifich++)
        {
          int sideid; irbx<NrbxngHE ? sideid = 1 : sideid = -1;//0..to 17 is P side, while 17 to 35 is M side
          int rbxrmid; irbx<NrbxngHE ? rbxrmid = irbx*NrmngHE+irm : rbxrmid = (irbx-NrbxngHE)*NrmngHE+irm;//ngHE 0...to 71
          int rmfifichid = irmfi*Nfiber_ch+ifich;//ngHE 0...to 47

          ConstructngHEFrontEnd(sideid,rbxrmid,rmfifichid);      
          ConstructngHEBackEnd(sideid,rbxrmid,rmfifichid);  
          ConstructngHEGeometry(sideid,rbxrmid,rmfifichid);
          ConstructngHEPMTBox();  
          ConstructngHETriggerTower();
        }
      }
    }
  }
  return ;
}

void ngHEMappingAlgorithm::ConstructngHEFrontEnd(int sideid, int rbxrmid, int rmfifichid)
{
  ngHEFrontEnd thisngHEFrontEnd;
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHE + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHE + 1) : numberletter = std::to_string(rbxrmid/NrmngHE + 1); 
  thisngHEFrontEnd.rbx = "ngHE" + sideletter + numberletter;
  thisngHEFrontEnd.rm = rbxrmid%NrmngHE + 1;
  thisngHEFrontEnd.rm_fiber = rmfifichid/Nfiber_ch + 1;
  thisngHEFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie8 map
  //thisngHEFrontEnd.qie8 = (thisngHEFrontEnd.rm_fiber -1)/2+1;
  //thisngHEFrontEnd.rm_fiber%2 != 0 ? thisngHEFrontEnd.qie8_ch = thisngHEFrontEnd.fiber_ch : thisngHEFrontEnd.qie8_ch = 3 + (thisngHEFrontEnd.fiber_ch+1)%3;

  myngHEFrontEnd.push_back(thisngHEFrontEnd);
  return ;
}

void ngHEMappingAlgorithm::ConstructngHEBackEnd(int sideid, int rbxrmid, int rmfifichid)
{
  ngHEBackEnd thisngHEBackEnd;
  //set ucrate id from rbx and rm, 2016 and 2017 should be same
  thisngHEBackEnd.ucrate = ngHEucrateInrbxrmid[((rbxrmid+4)%72)/8];
  //set the uhr slot from rbx and rm and rm_fiber : complicate!!
  //3 types of backend slot : pure HB(1,4,7,10), mixed HB ngHE(2,5,8,11), and pure ngHE(3,6,9,12)
  //mixed ngHE case : rm(rm fiber) 1(246),  2(457),  3(246),  4(457);
  //pure  ngHE case : rm(rm fiber) 1(13578),2(12368),3(13578),4(12368);
  int rm = rbxrmid%NrmngHE + 1; double rm_fiber = rmfifichid/Nfiber_ch + 1;
  bool ismixed_ngHE = (rm%2!=0 && (rm_fiber==2 || rm_fiber==4 || rm_fiber==6)) || (rm%2==0 && (rm_fiber==4 || rm_fiber==5 || rm_fiber==7) );
  
  if(sideid>0)
  { 
    //if( rmfifichid < 18 ) (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 11 : thisngHEBackEnd.uhtr = 8;
    if( ismixed_ngHE ) (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 11 : thisngHEBackEnd.uhtr = 8;
    else (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 12 : thisngHEBackEnd.uhtr = 9;
  }
  else
  { 
    //if( rmfifichid < 18 ) (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 5 : thisngHEBackEnd.uhtr = 2;
    if( ismixed_ngHE ) (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 5 : thisngHEBackEnd.uhtr = 2;
    else (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 6 : thisngHEBackEnd.uhtr = 3;
  }

  //fpga variable for the backend, used to be useful in old HTR case....but we still keep a position for it now
  thisngHEBackEnd.ufpga = "uHTR";
  //set uhtr fiber from rm and rm fiber, P and M symmetry, RM1-RM3 and RM2-RM4
  if(sideid>0)
  {
    if     ( rbxrmid%NrmngHE == 0 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType1[rmfifichid/Nfiber_ch]; } 
    else if( rbxrmid%NrmngHE == 1 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType2[rmfifichid/Nfiber_ch]; }
    else if( rbxrmid%NrmngHE == 2 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType3[rmfifichid/Nfiber_ch]; }
    else thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType4[rmfifichid/Nfiber_ch];
  }
  else
  {
    if     ( rbxrmid%NrmngHE == 0 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType3[rmfifichid/Nfiber_ch]; }
    else if( rbxrmid%NrmngHE == 1 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType4[rmfifichid/Nfiber_ch]; }
    else if( rbxrmid%NrmngHE == 2 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType1[rmfifichid/Nfiber_ch]; }
    else thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType2[rmfifichid/Nfiber_ch];
  }
  
  //set backend fiber channel : same as the front end one
  thisngHEBackEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables
  myngHEBackEnd.push_back(thisngHEBackEnd);
  return ;
}

void ngHEMappingAlgorithm::ConstructngHEGeometry(int sideid, int rbxrmid, int rmfifichid)
{
  ngHEGeometry thisngHEGeometry;
  //side -> subdet -> eta, depth -> dphi -> phi
  thisngHEGeometry.side = sideid;
  
  if(rbxrmid%NrmngHE == 0)
  { 
    thisngHEGeometry.eta = ngHEetaInrmfifichid_RM1[rmfifichid]; 
    thisngHEGeometry.depth = ngHEdepInrmfifichid_RM1[rmfifichid]; 
  }
  else if(rbxrmid%NrmngHE == 1)
  {
    thisngHEGeometry.eta = ngHEetaInrmfifichid_RM2[rmfifichid];
    thisngHEGeometry.depth = ngHEdepInrmfifichid_RM2[rmfifichid];
  }
  else if(rbxrmid%NrmngHE == 2)
  {
    thisngHEGeometry.eta = ngHEetaInrmfifichid_RM3[rmfifichid];
    thisngHEGeometry.depth = ngHEdepInrmfifichid_RM3[rmfifichid];
  }
  else if(rbxrmid%NrmngHE == 3)
  {
    thisngHEGeometry.eta = ngHEetaInrmfifichid_RM4[rmfifichid];
    thisngHEGeometry.depth = ngHEdepInrmfifichid_RM4[rmfifichid];
  }
  else
  {
    std::cout << "RM is not 1,2,3,or 4?? what the fuck???" << std::endl; 
  }
  //if(rbxrmid%2 == 0){ thisngHEGeometry.eta = ngHEetaInrmfifichidType1[rmfifichid]; thisngHEGeometry.depth = ngHEdepthInrmfifichidType1[rmfifichid]; }
  //else{ thisngHEGeometry.eta = ngHEetaInrmfifichidType2[rmfifichid]; thisngHEGeometry.depth = ngHEdepthInrmfifichidType2[rmfifichid]; }
  
  if( thisngHEGeometry.eta >= 16 && thisngHEGeometry.eta <= 20 ){ thisngHEGeometry.dphi = 1; }
  else if( thisngHEGeometry.eta >= 21 && thisngHEGeometry.eta <= 29 ){ thisngHEGeometry.dphi = 2; }
  else{ thisngHEGeometry.dphi = -1; }

  if(sideid > 0)
  {
    if( thisngHEGeometry.dphi == 1 ) thisngHEGeometry.phi = ngHEphiInrbxrmid_P_dphi1[rbxrmid];
    else if( thisngHEGeometry.dphi == 2 ) thisngHEGeometry.phi = ngHEphiInrbxrmid_P_dphi2[rbxrmid];
    else thisngHEGeometry.phi = 0;
  }
  else
  {
    if( thisngHEGeometry.dphi == 1 ) thisngHEGeometry.phi = ngHEphiInrbxrmid_M_dphi1[rbxrmid];
    else if( thisngHEGeometry.dphi == 2 ) thisngHEGeometry.phi = ngHEphiInrbxrmid_M_dphi2[rbxrmid];
    else thisngHEGeometry.phi = 0;
  }
  
  //Over write everything for HEX channels ?
  //( rbxrmid%2==1 && (rmfifichid == 16 || rmfifichid == 17) ) ? thisngHEGeometry.subdet = "HEX" : thisngHEGeometry.subdet = "HE";
  ( (rbxrmid%4==1 && rmfifichid==29 ) || (rbxrmid%4==1 && rmfifichid==37 ) || (rbxrmid%4==2 && rmfifichid==7 ) || (rbxrmid%4==2 && rmfifichid==18 ) ) ? thisngHEGeometry.subdet = "HEX" : thisngHEGeometry.subdet = "HE";

  if(thisngHEGeometry.subdet == "HEX") 
  {
    //cross check HEX channel with ngHEetaInrmfifichid array
    if(thisngHEGeometry.eta!=0 || thisngHEGeometry.depth!=0) std::cout << "Wrong HEX channel map!" << std::endl;
    thisngHEGeometry.eta = 0;
    thisngHEGeometry.phi = 0;
    thisngHEGeometry.depth = 0;
    thisngHEGeometry.dphi = 0;
  }

  myngHEGeometry.push_back(thisngHEGeometry);
  return ;
}

void ngHEMappingAlgorithm::ConstructngHEPMTBox()
{
  ngHEPMTBox thisngHEPMTBox;
  
  myngHEPMTBox.push_back(thisngHEPMTBox);
  return ;
}

void ngHEMappingAlgorithm::ConstructngHETriggerTower()
{
  ngHETriggerTower thisngHETriggerTower;

  myngHETriggerTower.push_back(thisngHETriggerTower);
  return ;
}
