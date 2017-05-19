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
          ConstructngHESiPM(sideid,rbxrmid,rmfifichid);
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
  thisngHEFrontEnd.rbx = "HE" + sideletter + numberletter;
  thisngHEFrontEnd.rm = rbxrmid%NrmngHE + 1;
  thisngHEFrontEnd.rm_fiber = rmfifichid/Nfiber_ch + 1;
  thisngHEFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie11 map
  //qie11: 1 to 4, qie11_ch: 1 to 12 = 1 rm(48 chs)
  thisngHEFrontEnd.qie11 = (thisngHEFrontEnd.rm_fiber-1)/2+1;
  thisngHEFrontEnd.qie11_ch = ((thisngHEFrontEnd.rm_fiber-1)%2)*6+thisngHEFrontEnd.fiber_ch+1;
  //set tmp qie11 id
  thisngHEFrontEnd.qie11_id = 500000;

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
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHE + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHE + 1) : numberletter = std::to_string(rbxrmid/NrmngHE + 1);
  std::string rbx = "HE" + sideletter + numberletter;
  int rm = rbxrmid%NrmngHE + 1; int rm_fiber = rmfifichid/Nfiber_ch + 1;
  bool ismixed_ngHE = (rm%2!=0 && (rm_fiber==2 || rm_fiber==4 || rm_fiber==6)) || (rm%2==0 && (rm_fiber==4 || rm_fiber==5 || rm_fiber==7) );
  
  if(sideid>0)
  { 
    if( ismixed_ngHE ) (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 11 : thisngHEBackEnd.uhtr = 8;
    else (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 12 : thisngHEBackEnd.uhtr = 9;
  }
  else
  { 
    if( ismixed_ngHE ) (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 5 : thisngHEBackEnd.uhtr = 2;
    else (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 6 : thisngHEBackEnd.uhtr = 3;
  }

  //fpga variable for the backend, used to be useful in old HTR case....but we still keep a position for it now
  thisngHEBackEnd.ufpga = "uHTR";
  //set uhtr fiber from patch panel
  //first set patch panel info, from front end side
  thisngHEBackEnd.ppcol = (rm_fiber-1)/4+1;
  thisngHEBackEnd.pprow = rm;
  thisngHEBackEnd.pplc = (rm_fiber-1)%4+1;
  std::string cplletter;
  rm_fiber<=4 ? cplletter="A" : cplletter="B";
  thisngHEBackEnd.ppcpl = rbx+"_RM"+std::to_string(rm)+cplletter;
  //then set uhtr fiber infomation from patch panel
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/ngHE/optical_patch.txt
  /*
    The P-side mixed uHTR (xx indicates an empty spigot):
  
           HEM04                 HBM04                 HEP04                 HBP04     
  | -------- | -------- | -------- | -------- | ------17 | 22--23-- | xx0809-- | ------xx |  RM4
  | -------- | -------- | -------- | -------- | --15--16 | --21---- | xx0607-- | ------xx |  RM3
  | -------- | -------- | -------- | -------- | ------14 | 19--20-- | xx0405-- | ------xx |  RM2
  | -------- | -------- | -------- | -------- | --12--13 | --18---- | xx0203-- | ------xx |  RM1

    The P-side pure ngHE uHTR (xx indicates an empty spigot):
  
         HEM04                 HBM04                 HEP04                 HBP04     
  | -------- | -------- | -------- | -------- | 080910-- | --21--22 | xx------ | ------xx |  RM4
  | -------- | -------- | -------- | -------- | 06--07-- | 18--1920 | xx------ | ------xx |  RM3
  | -------- | -------- | -------- | -------- | 030405-- | --16--17 | xx------ | ------xx |  RM2
  | -------- | -------- | -------- | -------- | 01--02-- | 13--1415 | xx------ | ------xx |  RM1
  */
  //comment from mapper: why the hell HE is far more complicate than HB?? ok, i know is trigger link requirement, just want to compliant....
  if( ismixed_ngHE )//FIXME
  {
    const int ngHEuhtrfiInpp_mixed_c1[4][4]=//rm(pprow),rmfiber
    {
      {-1,12,-1,13},//rm 1 pprow 1
      {-1,-1,-1,14},//rm 2 pprow 2
      {-1,15,-1,16},//rm 3 pprow 3
      {-1,-1,-1,17} //rm 4 pprow 4
    };
    const int ngHEuhtrfiInpp_mixed_c2[4][4]=//rm(pprow),rmfiber
    {
      {-1,18,-1,-1},//rm 1 pprow 1
      {19,-1,20,-1},//rm 2 pprow 2
      {-1,21,-1,-1},//rm 3 pprow 3
      {22,-1,23,-1} //rm 4 pprow 4
    };
    if     (thisngHEBackEnd.ppcol==1){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrfiInpp_mixed_c1[thisngHEBackEnd.pprow-1][rm_fiber-1]; }
    else if(thisngHEBackEnd.ppcol==2){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrfiInpp_mixed_c2[thisngHEBackEnd.pprow-1][rm_fiber-5]; }
    else{ std::cout << "the ppCol of ngHE channel is neither 1 nor 2 in mixed HBHE slot for ngHE??!! Please check!" << std::endl; }
  }
  else//FIXME
  {
    const int ngHEuhtrfiInpp_pure_c1[4][4]=//rm(pprow),rmfiber
    {
      { 1,-1, 2,-1},//rm 1 pprow 1
      { 3, 4, 5,-1},//rm 2 pprow 2
      { 6,-1, 7,-1},//rm 3 pprow 3
      { 8, 9,10,-1} //rm 4 pprow 4
    };
    const int ngHEuhtrfiInpp_pure_c2[4][4]=//rm(pprow),rmfiber
    {
      {13,-1,14,15},//rm 1 pprow 1
      {-1,16,-1,17},//rm 2 pprow 2
      {18,-1,19,20},//rm 3 pprow 3
      {-1,21,-1,22} //rm 4 pprow 4
    };
    if     (thisngHEBackEnd.ppcol==1){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrfiInpp_pure_c1[thisngHEBackEnd.pprow-1][rm_fiber-1]; }
    else if(thisngHEBackEnd.ppcol==2){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrfiInpp_pure_c2[thisngHEBackEnd.pprow-1][rm_fiber-5]; }
    else{ std::cout << "the ppCol of ngHE channel is neither 1 nor 2 in pure ngHE slot??!! Please check!" << std::endl; }
  }
  if( thisngHEBackEnd.uhtr_fiber<0 )
  { 
    std::cout << "negative uhtr fiber from patch panel mapping??!! Please check!" << std::endl; 
    std::cout << "RBX RM RM_FI : " << rbx << " "<< rm << " " << rm_fiber << std::endl;
  }
  //finally set dodec from back end side
  thisngHEBackEnd.dodec = (thisngHEBackEnd.uhtr_fiber)%12+1;
  //set backend fiber channel : same as the front end one
  thisngHEBackEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set tmp fed id
  thisngHEBackEnd.ufedid = thisngHEBackEnd.ucrate + 1100 -20;
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

void ngHEMappingAlgorithm::ConstructngHESiPM(int sideid, int rbxrmid, int rmfifichid)
{
  ngHESiPM thisngHESiPM;
  thisngHESiPM.wedge = rbxrmid/NrmngHE+1;
  int rm = rbxrmid%NrmngHE+1; int rmfiid = rmfifichid/Nfiber_ch; int fichid = rmfifichid%Nfiber_ch;
  //bias voltage is 1 to 48 per rm, rm 13 in same patterm rm 24 in the other same patter
  //rm1: 16 30 31 32 21 22 8 7 15 14 13 24 44 36 37 45 29 39 23 38 40 48 47 46 33 26 42 34 35 43 28 27 12 11 1 9 2 3 4 5 10 6 41 25 20 19 18 17
  //rm2: 40 48 21 22 23 24 7 6 5 4 15 3 45 31 39 46 32 47 8 16 14 13 30 29 41 33 35 43 42 18 38 37 44 36 28 34 1 2 10 11 12 17 9 27 26 25 20 19
  //rm3: 16 30 31 32 21 22 8 7 15 14 13 24 44 36 37 45 29 39 23 38 40 48 47 46 33 26 42 34 35 43 28 27 12 11 1 9 2 3 4 5 10 6 41 25 20 19 18 17
  //rm4: 40 48 21 22 23 24 7 6 5 4 15 3 45 31 39 46 32 47 8 16 14 13 30 29 41 33 35 43 42 18 38 37 44 36 28 34 1 2 10 11 12 17 9 27 26 25 20 19
  const int bv_rm13[Nrm_fiber*Nfiber_ch] = {16,30,31,32,21,22,8,7,15,14,13,24,44,36,37,45,29,39,23,38,40,48,47,46,33,26,42,34,35,43,28,27,12,11,1,9,2,3,4,5,10,6,41,25,20,19,18,17};
  const int bv_rm24[Nrm_fiber*Nfiber_ch] = {40,48,21,22,23,24,7,6,5,4,15,3,45,31,39,46,32,47,8,16,14,13,30,29,41,33,35,43,42,18,38,37,44,36,28,34,1,2,10,11,12,17,9,27,26,25,20,19};
  if     (rm==1||rm==3){ thisngHESiPM.bv = bv_rm13[rmfifichid]; }
  else if(rm==2||rm==4){ thisngHESiPM.bv = bv_rm24[rmfifichid]; }
  else{ std::cout << "rm is not 1234??" << std::endl; }
  myngHESiPM.push_back(thisngHESiPM);
  return ;
}

void ngHEMappingAlgorithm::ConstructngHETriggerTower()
{
  ngHETriggerTower thisngHETriggerTower;

  myngHETriggerTower.push_back(thisngHETriggerTower);
  return ;
}
