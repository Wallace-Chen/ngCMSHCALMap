#include "ngHEMappingAlgorithm.h"

void ngHEMappingAlgorithm::ConstructngHELMapObject(std::string Mode)
{
  if(Mode == "Normal")
  {
    std::cout << "#Constructing ngHE LMap Object..." << std::endl;
    LoadngHEQIEMap("ngHEQIEInput/HE_QIE11_CardMap_26Jan2018_Fake.txt");

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
          }
        }
      }
    }
  }
  else if(Mode == "Calib")
  {
    std::cout << "#Constructing ngHE Calib LMap Object..." << std::endl;

    for(int irbx=0;irbx<NrbxngHE*2;irbx++)
    {
      for(int irm=0;irm<NrmngHECalib;irm++)
      {
        for(int irmfi=0;irmfi<Nrm_fiberCalib;irmfi++)
        {
          for(int ifich=0;ifich<Nfiber_ch;ifich++)
          {
            int sideid; irbx<NrbxngHE ? sideid = 1 : sideid = -1;//0..to 17 is P side, while 17 to 35 is M side
            int rbxrmid; irbx<NrbxngHE ? rbxrmid = irbx*NrmngHECalib+irm : rbxrmid = (irbx-NrbxngHE)*NrmngHECalib+irm;//ngHE 0...to 71
            int rmfifichid = irmfi*Nfiber_ch+ifich;//ngHE 0...to 47
            //std::cout << "#Side: " << sideid << "; RBXRM: " << rbxrmid << "; RMFIFICH: " << rmfifichid << std::endl;
            ConstructngHECalib(sideid,rbxrmid,rmfifichid);
          }
        }
      }
    }
  }
  else
  {
    std::cout << "#Invalid generate mode for ngHE Logical map!" << std::endl;
    return ;
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
  GetngHEQIEInfoToLMap(
                       thisngHEFrontEnd.rbx, thisngHEFrontEnd.rm, thisngHEFrontEnd.qie11,
                       thisngHEFrontEnd.qie11_id
                      );
  //thisngHEFrontEnd.qie11_id = 600000;

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
  //  thisngHEBackEnd.ppcol = (rm_fiber-1)/4+1;
  thisngHEBackEnd.ppcol = sideid>0 ? (rm_fiber-1)/4+1 : (rm_fiber-1)/4+5;
  thisngHEBackEnd.pprow = rm;
  thisngHEBackEnd.pplc = (rm_fiber-1)%4+1;
  std::string cplletter;
  rm_fiber<=4 ? cplletter="A" : cplletter="B";
  thisngHEBackEnd.ppcpl = rbx+"_RM"+std::to_string(rm)+cplletter;
  //then set uhtr fiber infomation from patch panel
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/optical_patch_2018calib.txt
  /*
  
  The mixed HB/HE uHTRs - slots 5 11:

|                 crate 34 slot 11                          |                 crate 34 slot 5                           |
             HEP17                         HBP17                          HEM17                        HBM17            
                              | ------11b12b |                             | ------11b12b |                                Calib
| ---------10t | 11t---12t--- | ---09b10b--- | ------------ | ---------10t | 11t---12t--- | ---09b10b--- | ------------ |  RM4
| ---07t---08t | ---09t------ | ---07b08b--- | ------------ | ---07t---08t | ---09t------ | ---07b08b--- | ------------ |  RM3
| ---------04t | 05t---06t--- | ---05b06b--- | ------------ | ---------04t | 05t---06t--- | ---05b06b--- | ------------ |  RM2
| ---01t---02t | ---03t------ | ---03b04b--- | ------------ | ---01t---02t | ---03t------ | ---03b04b--- | ------------ |  RM1


  The pure HE uHTRs - slots 6 12:

|                 crate 34 slot 12                          |                 crate 34 slot 6                           |  
             HEP17                         HBP17                          HEM17                        HBM17            
                              | 12b12t------ |                             | 12b12t------ |                                Calib
| 07t08t09t--- | ---10t---11t | ------------ | ------------ | 07t08t09t--- | ---10t---11t | ------------ | ------------ |  RM4
| 02t---03t--- | 04t---05t06t | ------------ | ------------ | 02t---03t--- | 04t---05t06t | ------------ | ------------ |  RM3
| 07b08b09b--- | ---10b---11b | ------------ | ------------ | 07b08b09b--- | ---10b---11b | ------------ | ------------ |  RM2
| 02b---03b--- | 04b---05b06b | ------------ | ------------ | 02b---03b--- | 04b---05b06b | ------------ | ------------ |  RM1
   */
  if( ismixed_ngHE )//FIXME
  {
    const int ngHEuhtrfiInpp_mixed_c1[4][4]=//rm(pprow),rmfiber
    {
      {-1,1,-1,2},//rm 1 pprow 1
      {-1,-1,-1,4},//rm 2 pprow 2
      {-1,7,-1,8},//rm 3 pprow 3
      {-1,-1,-1,10} //rm 4 pprow 4
    };
    const int ngHEuhtrfiInpp_mixed_c2[4][4]=//rm(pprow),rmfiber
    {
      {-1,3,-1,-1},//rm 1 pprow 1
      {5,-1,6,-1},//rm 2 pprow 2
      {-1,9,-1,-1},//rm 3 pprow 3
      {11,-1,12,-1} //rm 4 pprow 4
    };
    if     (thisngHEBackEnd.ppcol==1 || thisngHEBackEnd.ppcol==5 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrfiInpp_mixed_c1[thisngHEBackEnd.pprow-1][rm_fiber-1]-1+12; } 
    else if(thisngHEBackEnd.ppcol==2 || thisngHEBackEnd.ppcol==6 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrfiInpp_mixed_c2[thisngHEBackEnd.pprow-1][rm_fiber-5]-1+12; }
    else{ std::cout << "the ppCol of ngHE channel is neither 1 nor 2 in mixed HBHE slot for ngHE??!! Please check!" << std::endl; }
  }
  else//FIXME
  {
    const int ngHEuhtrfiInpp_pure_c1[4][4]=//rm(pprow),rmfiber
    {
      { 2,-1, 3,-1},//rm 1 pprow 1
      { 7, 8, 9,-1},//rm 2 pprow 2
      { 2,-1, 3,-1},//rm 3 pprow 3
      { 7, 8, 9,-1} //rm 4 pprow 4
    };
    const int ngHEuhtrfiInpp_pure_c2[4][4]=//rm(pprow),rmfiber
    {
      {4,-1, 5, 6},//rm 1 pprow 1
      {-1,10,-1,11},//rm 2 pprow 2
      {4,-1, 5, 6},//rm 3 pprow 3
      {-1,10,-1,11} //rm 4 pprow 4
    };
    if     (thisngHEBackEnd.ppcol==1 || thisngHEBackEnd.ppcol==5){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrfiInpp_pure_c1[thisngHEBackEnd.pprow-1][rm_fiber-1]-1; }
    else if(thisngHEBackEnd.ppcol==2 || thisngHEBackEnd.ppcol==6){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrfiInpp_pure_c2[thisngHEBackEnd.pprow-1][rm_fiber-5]-1; }
    else{ std::cout << "the ppCol of ngHE channel is neither 1 nor 2 in pure ngHE slot??!! Please check!" << std::endl; }

    if (thisngHEBackEnd.pprow==3 || thisngHEBackEnd.pprow==4) thisngHEBackEnd.uhtr_fiber = thisngHEBackEnd.uhtr_fiber + 12;
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
  //FED 1102,1103,1104,1105,1100,1101,1106,1107,1116,1117,1108,1109,1114,1115,1110,1111,1112,1113
  //backend slot 7 to 12 odd number backend slot 1 to 6 even number, 
  const std::map<int, std::pair<int, int> > ngHEufedidInucrate = { {20,{1102,1103}},{21,{1104,1105}},{24,{1100,1101}},{25,{1106,1107}},{30,{1116,1117}},{31,{1108,1109}},{34,{1114,1115}},{35,{1110,1111}},{37,{1112,1113}} };
  thisngHEBackEnd.uhtr <= 6 ? thisngHEBackEnd.ufedid = ((ngHEufedidInucrate.find(thisngHEBackEnd.ucrate))->second).first : thisngHEBackEnd.ufedid = ((ngHEufedidInucrate.find(thisngHEBackEnd.ucrate))->second).second;
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
  ConstructngHETriggerTower(thisngHEGeometry.eta, thisngHEGeometry.phi);
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

void ngHEMappingAlgorithm::ConstructngHETriggerTower(int eta, int phi)
{
  ngHETriggerTower thisngHETriggerTower;
  thisngHETriggerTower.trg_fiber = -1;
  if(eta<=0 || phi<=0) 
  {
    thisngHETriggerTower.trg_fiber = -1;
    thisngHETriggerTower.trg_fiber_ch = -1;       
  }
  else if(eta==29)//special fix for eta 29 HE, tail go with eta 28. more details in phase 1 upgrade note
  {
    thisngHETriggerTower.trg_fiber = -1;
    thisngHETriggerTower.trg_fiber_ch = -1;
  }
  else
  {
    if(eta <= 20)
    {
      if     (eta >= 1  && eta <=12) thisngHETriggerTower.trg_fiber = (int)((eta-1)/2);
      else if(eta >= 13 && eta <=18) thisngHETriggerTower.trg_fiber = (int)((eta-13)/2);
      else thisngHETriggerTower.trg_fiber = 0;
    }
    else
    {
      if     (eta >= 21 && eta <=24) thisngHETriggerTower.trg_fiber = (int)((eta-21)/2) + 1;
      else if(eta >= 25 && eta <=26) thisngHETriggerTower.trg_fiber = 3;
      else thisngHETriggerTower.trg_fiber = 3;
    }
    thisngHETriggerTower.trg_fiber_ch = ((eta-1)%2)*4 + ((phi+69)%72)%4;
  }
  myngHETriggerTower.push_back(thisngHETriggerTower);
  return ;
}

void ngHEMappingAlgorithm::ConstructngHECalib(int sideid, int rbxrmid, int rmfifichid)
{
  ngHECalib thisngHECalib;
  //set up frontend part
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHECalib + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHECalib + 1) : numberletter = std::to_string(rbxrmid/NrmngHECalib + 1); 
  thisngHECalib.rbx = "HE" + sideletter + numberletter;
  thisngHECalib.rm = rbxrmid%NrmngHECalib + 5; //rm=5 for calibration channels
  thisngHECalib.rm_fiber = rmfifichid/Nfiber_ch + 1;
  thisngHECalib.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie11 map
  thisngHECalib.qie11 = (thisngHECalib.rm_fiber-1)/2+1;
  thisngHECalib.qie11_ch = ((thisngHECalib.rm_fiber-1)%2)*6+thisngHECalib.fiber_ch+1;
  //set tmp qie11 id                                                                                                                                                                                        
  thisngHECalib.qie11_id = 600000;
  thisngHECalib.wedge = rbxrmid/NrmngHECalib + 1; //1,...,18
  //set up ngCU patch part
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/Calib/ngCU_patch/ngCU_HBHE_patch_2018-jan-17.txt
  /*
 Input side of the patch blocks
 
 - the ngCUpatch x-block:
 
           cpCol 1                   cpCol 2                   cpCol 3                    
           Hxx04-05                  Hxx06-07                  Hxx08-09           coupler block label
 | 04ep1 04ep2 05ep1 05ep2 | 06ep1 06ep2 07ep1 07ep2 | 08ep1 08ep2 09ep1 09ep2 |
 | 04bp1 04bp2 05bp1 05bp2 | 06bp1 06bp2 07bp1 07bp2 | 08bp1 08bp2 09bp1 09bp2 | 
 | 04em1 04em2 05em1 05em2 | 06em1 06em2 07em1 07em2 | 08em1 08em2 09em1 09em2 |
 | 04bm1 04bm2 05bm1 05bm2 | 06bm1 06bm2 07bm1 07bm2 | 08bm1 08bm2 09bm1 09bm2 |
 
 - the ngCUpatch y-block:
 
           cpCol 4                   cpCol 5                   cpCol 6           
           Hxx01-02                  Hxx03-10                  Hxx11-12           coupler block label
 | 01ep1 01ep2 02ep1 02ep2 | 03ep1 03ep2 10ep1 10ep2 | 11ep1 11ep2 12ep1 12ep2 |
 | 01bp1 01bp2 02bp1 02bp2 | 03bp1 03bp2 10bp1 10bp2 | 11bp1 11bp2 12bp1 12bp2 | 
 | 01em1 01em2 02em1 02em2 | 03em1 03em2 10em1 10em2 | 11em1 11em2 12em1 12em2 |
 | 01bm1 01bm2 02bm1 02bm2 | 03bm1 03bm2 10bm1 10bm2 | 11bm1 11bm2 12bm1 12bm2 |
 
 - the ngCUpatch z-block:
 
           cpCol 7                   cpCol 8                   cpCol 9         
           Hxx13-14                  Hxx15-16                  Hxx17-18           coupler block label
 | 13ep1 13ep2 14ep1 14ep2 | 15ep1 15ep2 16ep1 16ep2 | 17ep1 17ep2 18ep1 18ep2 | 
 | 13bp1 13bp2 14bp1 14bp2 | 15bp1 15bp2 16bp1 16bp2 | 17bp1 17bp2 18bp1 18bp2 | 
 | 13em1 13em2 14em1 14em2 | 15em1 15em2 16em1 16em2 | 17em1 17em2 18em1 18em2 |
 | 13bm1 13bm2 14bm1 14bm2 | 15bm1 15bm2 16bm1 16bm2 | 17bm1 17bm2 18bm1 18bm2 |

 - the octopus fibers at the ngCU patch then also follow a simple pattern:
  1   2
  -   -
  1   2   ep
  3   4   bp
  5   6   em
  7   8   bm

 Output side of the patch blocks
 
            cpCol 1                   cpCol 2                   cpCol 3                    
           Hxx04-05                  Hxx06-07                  Hxx08-09           coupler block label
    crate 20     crate 20     crate 21    crate 21      crate 25    crate 25
 | 01b20 02b20 01t20 02t20 | 01b21 02b21 01t21 02t21 | 01b25 02b25 01t25 02t25 |
 | 03b20 04b20 03t20 04t20 | 03b21 04b21 03t21 04t21 | 03b25 04b25 03t25 04t25 | 
 | 05b20 06b20 05t20 06t20 | 05b21 06b21 05t21 06t21 | 05b25 06b25 05t25 06t25 |
 | 07b20 08b20 07t20 08t20 | 07b21 08b21 07t21 08t21 | 07b25 08b25 07t25 08t25 |
 
 - the ngCUpatch y-block:
 
           cpCol 4                   cpCol 5                   cpCol 6           
           Hxx01-02                  Hxx03-10                  Hxx11-12           coupler block label
    crate 30     crate 24     crate 24    crate 31      crate 31    crate 35          
 | 01t30 02t30 01b24 02b24 | 01t24 02t24 01b31 02b31 | 01t31 02t31 01b35 02b35 |
 | 03t30 04t30 03b24 04b24 | 03t24 04t24 03b31 04b31 | 03t31 04t31 03b35 04b35 | 
 | 05t30 06t30 05b24 06b24 | 05t24 06t24 05b31 06b31 | 05t31 06t31 05b35 06b35 |
 | 07t30 08t30 07b24 08b24 | 07t24 08t24 07b31 08b31 | 07t31 08t31 07b35 08b35 |
 
 - the ngCUpatch z-block:
 
           cpCol 7                   cpCol 8                   cpCol 9         
           Hxx13-14                  Hxx15-16                  Hxx17-18           coupler block label
    crate 35     crate 37     crate 37    crate 34      crate 34    crate 30          
 | 01t35 02t35 01b37 02b37 | 01t37 02t37 01b34 02b34 | 01t34 02t34 01b30 02b30 | 
 | 03t35 04t35 03b37 04b37 | 03t37 04t37 03b34 04b34 | 03t34 04t34 03b30 04b30 | 
 | 05t35 06t35 05b37 06b37 | 05t37 06t37 05b34 06b34 | 05t34 06t34 05b30 06b30 |
 | 07t35 08t35 07b37 08b37 | 07t37 08t37 07b34 08b34 | 07t34 08t34 07b30 08b30 |

 - there are exceptions:
   HEP01 CU: 
   rm_fib_1 = LC1 = 1-2
   rm_fib 2 = LC2 = 1-1
  */
  /*
 - all the HE CU trunks are duplex 8-fiber ribbons in which 12 fibers are active (6 RBXes x 2 fibers)
   Although adjacent triplets of RBXes always share a bundle, the two triplets in a bundle are not
   always adjacent, and the triplets often cross partition boundaries, since the triplets start
   with sector 1 rather than sector 2.  There are 3 bundles per det-hemisphere, eg, for HBM:
 HEMx   4  5  6  7  8  9
 HEMy   1  2  3 10 11 12 
 HEMz  13 14 15 16 17 18
 - there are exceptions:
   HEP01 CU: 
   rm_fib_1 = LC1 = 1-2
   rm_fib 2 = LC2 = 1-1
  */
  int ngHEtrunkSectorInWedge[NrbxngHE] = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2};
  int ngHEcpColInWedge[NrbxngHE] = {4, 4, 5, 1, 1, 2, 2, 3, 3, 5, 6, 6, 7, 7, 8, 8, 9, 9};
  thisngHECalib.trunk = std::to_string(ngHEtrunkSectorInWedge[thisngHECalib.wedge-1]) + "-" + std::to_string( ((thisngHECalib.wedge-1)%3)*2 + thisngHECalib.rm_fiber );
  thisngHECalib.cpcol = ngHEcpColInWedge[thisngHECalib.wedge-1];
  sideid < 0 ? thisngHECalib.cprow = 2 : thisngHECalib.cprow = 4;
  thisngHECalib.cplc = thisngHECalib.rm_fiber;
  thisngHECalib.cpoct = (4-thisngHECalib.cprow)*2 + thisngHECalib.rm_fiber;
  const std::map<int, std::string > ngHEcpCplInCpCol = { 
                                                        {1,"04-05"}, {2,"06-07"}, {3,"08-09"},
                                                        {4,"01-02"}, {5,"03-10"}, {6,"11-12"},
                                                        {7,"13-14"}, {8,"15-16"}, {9,"17-18"}
                                                       };
  thisngHECalib.cpcpl = "HE" + sideletter + ngHEcpCplInCpCol.find(thisngHECalib.cpcol)->second;
  //thisngHECalib.cpcpl = "HE" + sideletter + "03-10";
  //set up patch panel
  /*
- the calib fibers for each patch arrive in a single 8-fiber octopus, terminated LC
  from a central calib fiber patch, which receives all the calib fibers from the entirety of HBHE
- There are two fibers from each ngHE RBX, and one fiber from each legacy HB RBX, meaning that 6 (or perhaps 8)
  of the 8 fibers are used (I allow here the possibility that ngHB RBXes may have two fibers).
- The P-side RBXes come to coupler column 3, the M-side to coupler column 6:

         HEP17                 HBP17                 HEM17                 HBM17     
                      | e1e2b1b2 |                     | e1e2b1b2 |                        calib |HBEP16| |HBEP17|
| 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 |  RM4
| 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 |  RM3
| 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 |  RM2
| 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 |  RM1
  */
  sideid < 0 ? thisngHECalib.ppcol = 6 : thisngHECalib.ppcol = 3;
  thisngHECalib.pprow = 5;
  //thisngHECalib.pplc = (thisngHECalib.rm_fiber-1)%4+1;
  thisngHECalib.pplc = thisngHECalib.rm_fiber;
  //thisngHECalib.dodec = (thisngHECalib.uhtr_fiber)%12+1;
  thisngHECalib.dodec = 12;
  thisngHECalib.ppcpl = "EB" + sideletter + numberletter + "_CU";

  //set up backend part
  /*
  The mixed HB/HE uHTRs - slots 5 11:

|                 crate 34 slot 11                          |                 crate 34 slot 5                           |
             HEP17                         HBP17                          HEM17                        HBM17            
                              | ------11b12b |                             | ------11b12b |                                Calib
| ---------10t | 11t---12t--- | ---09b10b--- | ------------ | ---------10t | 11t---12t--- | ---09b10b--- | ------------ |  RM4
| ---07t---08t | ---09t------ | ---07b08b--- | ------------ | ---07t---08t | ---09t------ | ---07b08b--- | ------------ |  RM3
| ---------04t | 05t---06t--- | ---05b06b--- | ------------ | ---------04t | 05t---06t--- | ---05b06b--- | ------------ |  RM2
| ---01t---02t | ---03t------ | ---03b04b--- | ------------ | ---01t---02t | ---03t------ | ---03b04b--- | ------------ |  RM1


  The pure HE uHTRs - slots 6 12:

|                 crate 34 slot 12                          |                 crate 34 slot 6                           |  
             HEP17                         HBP17                          HEM17                        HBM17            
                              | 12b12t------ |                             | 12b12t------ |                                Calib
| 07t08t09t--- | ---10t---11t | ------------ | ------------ | 07t08t09t--- | ---10t---11t | ------------ | ------------ |  RM4
| 02t---03t--- | 04t---05t06t | ------------ | ------------ | 02t---03t--- | 04t---05t06t | ------------ | ------------ |  RM3
| 07b08b09b--- | ---10b---11b | ------------ | ------------ | 07b08b09b--- | ---10b---11b | ------------ | ------------ |  RM2
| 02b---03b--- | 04b---05b06b | ------------ | ------------ | 02b---03b--- | 04b---05b06b | ------------ | ------------ |  RM1
  */
  int ngHEuCrateInWedge[NrbxngHE] = {30, 24, 24, 20, 20, 21, 21, 25, 25, 31, 31, 35, 35, 37, 37, 34, 34, 30};
  thisngHECalib.ucrate = ngHEuCrateInWedge[thisngHECalib.wedge-1];
  if     (thisngHECalib.ppcol == 6) thisngHECalib.uhtr = 6;
  else if(thisngHECalib.ppcol == 3) thisngHECalib.uhtr = 12;
  else{ std::cout << "#ngHE Calib channel not in ppcol 6 nor ppcol 3, please check!!" << std::endl; thisngHECalib.uhtr = 0; }
  if     (thisngHECalib.rm_fiber == 1) thisngHECalib.uhtr_fiber = 11;
  else if(thisngHECalib.rm_fiber == 2) thisngHECalib.uhtr_fiber = 23;
  else{ std::cout << "#ngHE Calib channel not in RM fiber 1 nor RM fiber 2, please check!!" << std::endl; thisngHECalib.uhtr_fiber = -1; }
  const std::map<int, std::pair<int, int> > ngHEufedidInucrate = { {20,{1102,1103}},{21,{1104,1105}},{24,{1100,1101}},{25,{1106,1107}},{30,{1116,1117}},{31,{1108,1109}},{34,{1114,1115}},{35,{1110,1111}},{37,{1112,1113}} };
  thisngHECalib.uhtr <= 6 ? thisngHECalib.ufedid = ((ngHEufedidInucrate.find(thisngHECalib.ucrate))->second).first : thisngHECalib.ufedid = ((ngHEufedidInucrate.find(thisngHECalib.ucrate))->second).second;

  //set up Geometry part
  thisngHECalib.side = sideid;
  thisngHECalib.eta = 1;
  thisngHECalib.rm_fiber == 1 ? thisngHECalib.depth = 6 : thisngHECalib.depth = thisngHECalib.fiber_ch;
  thisngHECalib.dphi = 4;
  //if(sideid > 0)
  //{
  //follow ngHE P side rm 1
  thisngHECalib.phi = ngHEphiInrbxrmid_P_dphi1[(thisngHECalib.wedge-1)*4+thisngHECalib.rm-5];
  //}
  //else
  //{
    //thisngHECalib.phi = ngHEphiInrbxrmid_M_dphi1[(thisngHECalib.wedge-1)*4+thisngHECalib.rm-5];
  //}
  thisngHECalib.subdet = "CALIB_HE";
  if(thisngHECalib.rm_fiber == 1 && thisngHECalib.fiber_ch != 0) return ; //do not fill the calibration channel when calibration pedestal

  myngHECalib.push_back(thisngHECalib);
  return ;
}

void ngHEMappingAlgorithm::LoadngHEQIEMap(std::string QIE11CardMapFileName)
{
  std::ifstream inputFile(QIE11CardMapFileName.c_str());
  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;

    std::stringstream ss(line);
    ngHEQIE11CardMap thisngHEQIE11CardMap;
    
    ss >> thisngHEQIE11CardMap.rbx >> thisngHEQIE11CardMap.rm >> thisngHEQIE11CardMap.qie >> thisngHEQIE11CardMap.qie_id;
    //std::cout << thisngHEQIE11CardMap.rbx << std::endl;
    //std::cout << thisngHEQIE11CardMap.rm << std::endl;
    //std::cout << thisngHEQIE11CardMap.qie << std::endl;
    //std::cout << thisngHEQIE11CardMap.qie_id << std::endl;
    myngHEQIE11CardMap.push_back(thisngHEQIE11CardMap);
  }
  return ;
}

void ngHEMappingAlgorithm::GetngHEQIEInfoToLMap(
                                                std::string rbx, int rm, int qie,
                                                int &qie11_id
                                               )
{
  bool qie11match = false;
  for(auto i=0; i<myngHEQIE11CardMap.size(); i++)
  {
    qie11match = (rbx==myngHEQIE11CardMap.at(i).rbx) && (qie==std::stoi(myngHEQIE11CardMap.at(i).qie));
    if(qie11match)
    {
      qie11_id = std::stoi(myngHEQIE11CardMap.at(i).qie_id);
      break;
    }
    else continue;
  }
  if(!qie11match) std::cout << "#QIE 11 card not found in front end coordinates ???!!!" << std::endl;
  return ;
}                                                                                                                                                                                                           
