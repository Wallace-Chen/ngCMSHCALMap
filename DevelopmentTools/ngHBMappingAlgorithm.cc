#include "ngHBMappingAlgorithm.h"
void ngHBMappingAlgorithm::ConstructngHBLMapObject(std::string Mode)
{
  myngHBQIE11CardMap.clear();
  std::cout << "#Loading information from QIE allocation file..." << std::endl;
  LoadngHBQIEMap("ngHBHOQIEInput/RBX_RM_QIE_2016Nov03.txt");

  if(Mode == "Normal")
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
            int sideid; irbx<NrbxngHB ? sideid = 1 : sideid = -1;//0..to 11 is P side, while 12 to 23 is M side
            int rbxrmid; irbx<NrbxngHB ? rbxrmid = irbx*NrmngHB+irm : rbxrmid = (irbx-NrbxngHB)*NrmngHB+irm;//ngHB 0...to 71
            int rmfifichid = irmfi*Nfiber_ch+ifich;//ngHB 0...to 63

            ConstructngHBFrontEnd(sideid,rbxrmid,rmfifichid);
            ConstructngHBBackEnd(sideid,rbxrmid,rmfifichid);
            ConstructngHBGeometry(sideid,rbxrmid,rmfifichid);
            ConstructngHBSiPM(sideid,rbxrmid,rmfifichid);
          }
        }
      }
    }
  }
  else if(Mode == "Calib")
  {
    std::cout << "#Constructing ngHB Calib LMap Object..." << std::endl;
    for(int irbx=0;irbx<NrbxngHB*2;irbx++)
    {
      for(int irm=0;irm<NrmngHBCalib;irm++)
      {
        for(int irmfi=0;irmfi<Nrm_fiberCalib;irmfi++)
        {
          for(int ifich=0;ifich<Nfiber_chCalib;ifich++)
          {
            int sideid; irbx<NrbxngHB ? sideid = 1 : sideid = -1;//0..to 17 is P side, while 17 to 35 is M side
            int rbxrmid; irbx<NrbxngHB ? rbxrmid = irbx*NrmngHBCalib+irm : rbxrmid = (irbx-NrbxngHB)*NrmngHBCalib+irm;//ngHB 0...to 17
            int rmfifichid = irmfi*Nfiber_chCalib+ifich;//ngHB 0.. to 2
            //std::cout << "#Side: " << sideid << "; RBXRM: " << rbxrmid << "; RMFIFICH: " << rmfifichid << std::endl;
            ConstructngHBCalib(sideid,rbxrmid,rmfifichid);
          }
        }
      }
    }
  }
  else
  {
    std::cout << "#Invalid generate mode for ngHB Logical map!" << std::endl;
    return ;
  }

  return ;
}

void ngHBMappingAlgorithm::ConstructngHBFrontEnd(int sideid, int rbxrmid, int rmfifichid)
{
  ngHBFrontEnd thisngHBFrontEnd;
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHB + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHB + 1) : numberletter = std::to_string(rbxrmid/NrmngHB + 1); 
  thisngHBFrontEnd.rbx = "HB" + sideletter + numberletter;
  thisngHBFrontEnd.rm = rbxrmid%NrmngHB + 1;
  thisngHBFrontEnd.rm_fiber = rmfifichid/Nfiber_ch + 1;
  thisngHBFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  thisngHBFrontEnd.fiber_indx = thisngHBFrontEnd.rm_fiber + 8*(thisngHBFrontEnd.rm + 4); // for ngHB, it's 4, otherwise it's 0.
  //set secondary variables qie11 map
  //thisngHBFrontEnd.qie11 = (thisngHBFrontEnd.rm_fiber -1)/2+1;
  // rm_fiber -> qie11(card), 4,5 -> 4  6,7 -> 3  8,1 -> 2  2,3 -> 1 if RM is odd
  // rm_fiber -> qie11(card), 4,5 -> 1  6,7 -> 2  8,1 -> 3  2,3 -> 4 if RM is even
  thisngHBFrontEnd.rm % 2 == 0 ? thisngHBFrontEnd.qie11 = 1 + int(((thisngHBFrontEnd.rm_fiber+4)%Nrm_fiber)/2) : thisngHBFrontEnd.qie11 = 4 - int(((thisngHBFrontEnd.rm_fiber+4)%Nrm_fiber)/2);
  (thisngHBFrontEnd.rm + thisngHBFrontEnd.rm_fiber)%2 == 1 ? thisngHBFrontEnd.qie11_ch = thisngHBFrontEnd.fiber_ch + 1 : thisngHBFrontEnd.qie11_ch = 8 + (thisngHBFrontEnd.fiber_ch+1);

  const int mb_rm13[Nrm_fiber*Nfiber_ch] = {30,29,22,21,28,27,20,19,8,7,16,15,2,1,10,9,     //RM13 rmfifichid=0-15
                                            14,13,6,5,12,11,4,3,56,55,64,63,50,49,58,57,    //RM13 rmfifichid=16-31
                                            62,61,54,53,60,59,52,51,40,39,48,47,34,33,42,41,//RM13 rmfifichid=32-47
                                            46,45,38,37,44,43,36,35,24,23,32,31,18,17,26,25 //RM13 rmfifichid=48-63
  };
  const int mb_rm24[Nrm_fiber*Nfiber_ch] = {40,39,48,47,34,33,42,41,62,61,54,53,60,59,52,51,//RM24 rmfifichid=0-15
                                            56,55,64,63,50,49,58,57,14,13,6,5,12,11,4,3,    //RM24 rmfifichid=16-31
                                            8,7,16,15,2,1,10,9,30,29,22,21,28,27,20,19,     //RM24 rmfifichid=16-31
                                            24,23,32,31,18,17,26,25,46,45,38,37,44,43,36,35 //RM24 rmfifichid=16-31
  };
  if     (thisngHBFrontEnd.rm==1||thisngHBFrontEnd.rm==3) {thisngHBFrontEnd.mb_no=mb_rm13[rmfifichid];}
  else if(thisngHBFrontEnd.rm==2||thisngHBFrontEnd.rm==4) {thisngHBFrontEnd.mb_no=mb_rm24[rmfifichid];}
  else  {std::cout << "RM is not 1234, found in ngHBFrontEnd??" << std::endl;}

  //set tmp qie11 id
  //thisngHBFrontEnd.qie11_id = 999991;
  //set qie11 id
  // !!!! Note that in eraM mapping, qie11 has value 1,2,3,4 while 4 is not possible in old version, all qie11_id in qie11=4 channel are 999999
  //GetngHBQIEInfoToLMap(
  //                   thisngHBFrontEnd.rbx, thisngHBFrontEnd.rm, thisngHBFrontEnd.qie11,
  //                   thisngHBFrontEnd.qie11_id
  //                  );
  //if( thisngHBFrontEnd.qie11_id == 999999 ) thisngHBFrontEnd.qie11_id = 999991;
  thisngHBFrontEnd.qie11_id = 999999;
  myngHBFrontEnd.push_back(thisngHBFrontEnd);
  
  ConstructngHBTriggerTower(thisngHBFrontEnd.rm, thisngHBFrontEnd.rm_fiber, thisngHBFrontEnd.fiber_ch, thisngHBFrontEnd.qie11_ch);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBBackEnd(int sideid, int rbxrmid, int rmfifichid)
{
  ngHBBackEnd thisngHBBackEnd;
  //set ucrate id from rbx and rm, eraM and eraL should be same
  thisngHBBackEnd.ucrate = ngHBucrateInrbxrmid[((rbxrmid+4)%72)/8];
  //set the uhr slot from rbx and rm and rm_fiber : complicate!!
  //3 types of backend slot : pure ngHB(1,4,7,10), mixed ngHB ngHE(2,5,8,11), and pure ngHE(3,6,9,12)
  //mixed ngHB case : rm(rm fiber) 1(23),  2(23),  3(23),  4(23);
  //pure  ngHB case : rm(rm fiber) 1(4567),2(4567),3(4567),4(4567);
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHB + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHB + 1) : numberletter = std::to_string(rbxrmid/NrmngHB + 1);
  std::string rbx = "HB" + sideletter + numberletter;
  int rm = rbxrmid%NrmngHB + 1; int rm_fiber = rmfifichid/Nfiber_ch + 1;
// What is the definition of mixed ngHB in eraM???? Suppose it's the same for now.  
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
  //  thisngHBBackEnd.ppcol = (rm_fiber-1)/4+3;
  thisngHBBackEnd.ppcol = sideid>0 ? (rm_fiber-1)/4+3 : (rm_fiber-1)/4+7;
  thisngHBBackEnd.pprow = rm;
  thisngHBBackEnd.pplc = (rm_fiber-1)%4+1;
  std::string cplletter;
  rm_fiber<=4 ? cplletter="A" : cplletter="B";
  thisngHBBackEnd.ppcpl = rbx+"_RM"+std::to_string(rm)+cplletter;

  //  printf("ppcol = %3d ( or %3d ?), ppcpl = %7s \n",thisngHBBackEnd.ppcol, ((rm_fiber-1)/4+1),thisngHBBackEnd.ppcpl);

  //then set uhtr fiber infomation from patch panel
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/ngHBHE/ngngHBHE/optical_patch_2018calib.txt
  /*
  The pure ngHB uHTRs - slots 4 10:

|                 crate 34 slot 10                          |                 crate 34 slot 4                           |  
             HEP17                         ngHBP17                         HEM17                         ngHBM17            
                              | ------------ |                             | ------------ |                                Calib
| ------------ | ------------ | 04b------08b | 12b04t08t12t | ------------ | ------------ | 04b------08b | 12b04t08t12t |  RM4
| ------------ | ------------ | 03b------07b | 11b03t07t11t | ------------ | ------------ | 03b------07b | 11b03t07t11t |  RM3
| ------------ | ------------ | 02b------06b | 10b02t06t10t | ------------ | ------------ | 02b------06b | 10b02t06t10t |  RM2
| ------------ | ------------ | 01b------05b | 09b01t05t09t | ------------ | ------------ | 01b------05b | 09b01t05t09t |  RM1


  The mixed ngHB/HE uHTRs - slots 5 11:

|                 crate 34 slot 11                          |                 crate 34 slot 5                           |
             HEP17                         ngHBP17                          HEM17                        ngHBM17            
                              | ------11b12b |                             | ------11b12b |                                Calib
| ---------10t | 11t---12t--- | ---09b10b--- | ------------ | ---------10t | 11t---12t--- | ---09b10b--- | ------------ |  RM4
| ---07t---08t | ---09t------ | ---07b08b--- | ------------ | ---07t---08t | ---09t------ | ---07b08b--- | ------------ |  RM3
| ---------04t | 05t---06t--- | ---05b06b--- | ------------ | ---------04t | 05t---06t--- | ---05b06b--- | ------------ |  RM2
| ---01t---02t | ---03t------ | ---03b04b--- | ------------ | ---01t---02t | ---03t------ | ---03b04b--- | ------------ |  RM1

  if( ismixed_ngHB )
  {
    if     (thisngHBBackEnd.ppcol==3){ thisngHBBackEnd.uhtr_fiber = (thisngHBBackEnd.pprow-1)*2+rm_fiber-2+2; }
    else{ std::cout << "the ppCol of ngHB channel is not 3 in mixed ngHBHE slot for ngHB??!! Please check!" << std::endl; }
  }
  else
  {
    if     (thisngHBBackEnd.ppcol==3){ thisngHBBackEnd.uhtr_fiber = thisngHBBackEnd.pprow-1; }
    else if(thisngHBBackEnd.ppcol==4){ thisngHBBackEnd.uhtr_fiber = (thisngHBBackEnd.pprow-1)*3+rm_fiber-5+12; }
    else{ std::cout << "the ppCol of ngHB channel is neither 3 nor 4 in pure ngHB slot??!! Please check!" << std::endl; }
  }
  */

  if( ismixed_ngHB )
  {
    if     (thisngHBBackEnd.ppcol==3 || thisngHBBackEnd.ppcol==7 ){ thisngHBBackEnd.uhtr_fiber = (thisngHBBackEnd.pprow-1)*2+rm_fiber-2+2; }
    else{ std::cout << "the ppCol of ngHB channel is not 3 in mixed ngHBHE slot for ngHB??!! Please check!" << std::endl; }
  }
  else
  {
    //notice here we change the order, first rm_fiber then rm!!!
    if     (thisngHBBackEnd.ppcol==3 || thisngHBBackEnd.ppcol==7){ thisngHBBackEnd.uhtr_fiber = (int(rm_fiber)/4)*4+thisngHBBackEnd.pprow-1; }
    else if(thisngHBBackEnd.ppcol==4 || thisngHBBackEnd.ppcol==8){ thisngHBBackEnd.uhtr_fiber = (rm_fiber-5)*4+thisngHBBackEnd.pprow-1+8; }
    else{ std::cout << "the ppCol of ngHB channel is neither 3 nor 4 in pure ngHB slot??!! Please check!" << std::endl; }
  }

  //finally set dodec from back end side
  thisngHBBackEnd.dodec = (thisngHBBackEnd.uhtr_fiber)%12+1;
  //set backend fiber channel : same as the front end one
  thisngHBBackEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set tmp fed id
  //backend slot 7 to 12 odd number backend slot 1 to 6 even number, 
  const std::map<int, std::pair<int, int> > ngHBufedidInucrate = { {20,{1102,1103}},{21,{1104,1105}},{24,{1100,1101}},{25,{1106,1107}},{30,{1116,1117}},{31,{1108,1109}},{34,{1114,1115}},{35,{1110,1111}},{37,{1112,1113}} };
  thisngHBBackEnd.uhtr <= 6 ? thisngHBBackEnd.ufedid = ((ngHBufedidInucrate.find(thisngHBBackEnd.ucrate))->second).first : thisngHBBackEnd.ufedid = ((ngHBufedidInucrate.find(thisngHBBackEnd.ucrate))->second).second;
  myngHBBackEnd.push_back(thisngHBBackEnd);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBGeometry(int sideid, int rbxrmid, int rmfifichid)
{
  ngHBGeometry thisngHBGeometry;
  //side -> subdet -> eta, depth -> dphi -> phi
  thisngHBGeometry.side = sideid;
  int rm = rbxrmid%NrmngHB + 1;
   
  // rm_fi -> eta, 4,5 -> 1-4  6,7 -> 5-8  8,1 -> 9-12  2,3 -> 13-16
  thisngHBGeometry.eta = ngHBetaInrmfifichid[((rmfifichid+40)%64)%16] + int(((rmfifichid+40)%64)/16)*4; 
  rm % 2 == 0 ? thisngHBGeometry.depth = ngHBdepInrmfifichidRM24[rmfifichid/4] : thisngHBGeometry.depth = ngHBdepInrmfifichidRM13[rmfifichid/4];
  thisngHBGeometry.dphi = 1;

  if(sideid > 0)
  {
    thisngHBGeometry.phi = ngHBphiInrbxrmid_P[rbxrmid];
  }
  else
  {
    thisngHBGeometry.phi = ngHBphiInrbxrmid_M[rbxrmid];
  }
 
  // Dealing with HBX channels: eta=16 and dept=4 or MB=6 for rm=1,2 and MB=62 for rm-2,4 
  ( (rm==1 && rmfifichid==18) || (rm==2 && rmfifichid==8) || (rm==3 && rmfifichid==18) || (rm==4 && rmfifichid==8) ) ? thisngHBGeometry.subdet = "HBX" : thisngHBGeometry.subdet = "HB";
  if(thisngHBGeometry.subdet == "HBX"){
    if(!(thisngHBGeometry.eta==16 && thisngHBGeometry.depth==4)) std::cout << "Wrong HBX channel map!" << std::endl;
    thisngHBGeometry.depth = -999; // overwrite depth for now
  }

  myngHBGeometry.push_back(thisngHBGeometry);
  ConstructngHBTriggerTowerFiber(thisngHBGeometry.eta, thisngHBGeometry.phi, thisngHBGeometry.depth);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBSiPM(int sideid, int rbxrmid, int rmfifichid)
{
  ngHBSiPM thisngHBSiPM;
  thisngHBSiPM.wedge = rbxrmid/NrmngHB+1;
  int rm = rbxrmid%NrmngHB + 1;
  // bias voltage is 1 to 64 per rm, rm 13 has the same pattern while rm 24 has the same pattern
  const int bv_rm13[Nrm_fiber*Nfiber_ch] = {59,63,57,61,3,7,1,5,50,54,52,56,10,14,12,16,    //rmfifichid = 0-15
                                            60,64,58,62,4,8,2,6,36,40,34,38,28,32,26,30,    //rmfifichid = 16-31
                                            42,46,44,48,18,22,20,24,35,39,33,37,27,31,25,29,//rmfifichid = 32-47
                                            41,45,43,47,17,21,19,23,49,53,51,55,9,13,11,15  //rmfifichid = 48-63
  };
  const int bv_rm24[Nrm_fiber*Nfiber_ch] = {35,39,33,37,27,31,25,29,42,46,44,48,18,22,20,24,//rmfifichid = 0-15
                                            36,40,34,38,28,32,26,30,60,64,58,62,4,8,2,6,    //rmfifichid = 16-31
                                            50,54,52,56,10,14,12,16,59,63,57,61,3,7,1,5,    //rmfifichid = 32-47
                                            49,53,51,55,9,13,11,15,41,45,43,47,17,21,19,23  //rmfifichid = 48-63
  };
  if     (rm==1||rm==3) {thisngHBSiPM.bv=bv_rm13[rmfifichid];}
  else if(rm==2||rm==4) {thisngHBSiPM.bv=bv_rm24[rmfifichid];}
  else  {std::cout << "RM is not 1234, found in ngHBSiPM??" << std::endl;}
  
  myngHBSiPM.push_back(thisngHBSiPM);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBTriggerTower(int rm, int rm_fiber, int fiber_ch, int qie11_ch)
{
  ngHBTriggerTower thisngHBTriggerTower;
  //trigger ind
  thisngHBTriggerTower.trg_ind = ((rm - 1)%2)*16 + qie11_ch - 1;
  //trigger indx
  thisngHBTriggerTower.trg_indx = ((rm - 1)%2)*16 + (rm_fiber%2)*8 + fiber_ch;
  //trigger jm
  thisngHBTriggerTower.trg_jm = ngHBtrgjmIntpind[thisngHBTriggerTower.trg_ind];
  //trigger_uhtr
  thisngHBTriggerTower.trg_uhtr = ngHBtrguhtrIntpindx[thisngHBTriggerTower.trg_indx];
  
  myngHBTriggerTower.push_back(thisngHBTriggerTower);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBTriggerTowerFiber(int eta, int phi, int depth)
{
  ngHBTriggerTowerFiber thisngHBTriggerTowerFiber;
  thisngHBTriggerTowerFiber.trg_fiber = -1;
  if(eta<=0 || phi<=0 || depth<=0)
  {
    thisngHBTriggerTowerFiber.trg_fiber = -1;
    thisngHBTriggerTowerFiber.trg_fiber_ch = -1;
  }
  else
  {
    if(eta <= 20)
    {
      if     (eta >= 1  && eta <=12) thisngHBTriggerTowerFiber.trg_fiber = (int)((eta-1)/2);
      else if(eta >= 13 && eta <=18) thisngHBTriggerTowerFiber.trg_fiber = (int)((eta-13)/2);
      else thisngHBTriggerTowerFiber.trg_fiber = 0;
    }
    else
    {
      if     (eta >= 21 && eta <=24) thisngHBTriggerTowerFiber.trg_fiber = (int)((eta-21)/2) + 1;
      else if(eta >= 25 && eta <=26) thisngHBTriggerTowerFiber.trg_fiber = 3;
      else thisngHBTriggerTowerFiber.trg_fiber = 3;
    }
    thisngHBTriggerTowerFiber.trg_fiber_ch = ((eta-1)%2)*4 + ((phi+69)%72)%4;
  }
  myngHBTriggerTowerFiber.push_back(thisngHBTriggerTowerFiber);
  return;
}

void ngHBMappingAlgorithm::ConstructngHBCalib(int sideid, int rbxrmid, int rmfifichid)
{
  ngHBCalib thisngHBCalib;
  //set up frontend part
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHBCalib + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHBCalib + 1) : numberletter = std::to_string(rbxrmid/NrmngHBCalib + 1);
  thisngHBCalib.rbx = "HB" + sideletter + numberletter;
  thisngHBCalib.rm = rbxrmid%NrmngHBCalib + 5;//rm=5 for calibration channels
  thisngHBCalib.rm_fiber = rmfifichid/Nfiber_chCalib + 1;
//  thisngHBCalib.fiber_ch = rmfifichid%Nfiber_chCalib + 5;
  thisngHBCalib.fiber_ch = rmfifichid%Nfiber_chCalib;
  //set qie11 variables
  thisngHBCalib.qie11 = 1;
  thisngHBCalib.qie11_ch = thisngHBCalib.fiber_ch + 1 + (thisngHBCalib.rm_fiber-1) % 2 * 8;
  thisngHBCalib.qie11_id = 999991;
  thisngHBCalib.wedge = rbxrmid/NrmngHBCalib + 1;
//  thisngHBCalib.trunk = (thisngHBCalib.wedge - 1)%3 + 1 + (thisngHBCalib.rm_fiber - 1) * 3;
  thisngHBCalib.trunk = (thisngHBCalib.wedge - 1)%3 + 1;
  if( thisngHBCalib.rm_fiber==1 ) thisngHBCalib.trunk += 3; // This change is due to Dick's email...
  int ngHBcpColInWedge[NrbxngHB] = {4, 4, 5, 1, 1, 2, 2, 3, 3, 5, 6, 6, 7, 7, 8, 8, 9, 9};
  thisngHBCalib.cpcol = ngHBcpColInWedge[thisngHBCalib.wedge-1];
  sideid < 0 ? thisngHBCalib.cprow = 1 : thisngHBCalib.cprow = 3;
  int ngHBSectorInWedge[NrbxngHB] = {2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3};
  std::string sector_str = std::to_string(ngHBSectorInWedge[thisngHBCalib.wedge-1]);
  bool if12InxyzWedge = (sector_str == "1" && thisngHBCalib.wedge%2 == 0) || (sector_str == "2" && thisngHBCalib.wedge%2 == 1) || (sector_str == "3" && thisngHBCalib.wedge%2 == 1);
  if( if12InxyzWedge ) thisngHBCalib.cplc = ( thisngHBCalib.rm_fiber )%2 + 1;
  else thisngHBCalib.cplc = ( thisngHBCalib.rm_fiber )%2 + 1 + 2;
//  thisngHBCalib.cpoct = ( sideid < 0 ? 7 : 3 );
  thisngHBCalib.cpoct = (4-thisngHBCalib.cprow)*2 + 1 + (thisngHBCalib.cplc+1)%2;
  const std::map<int, std::string > ngHBcpCplInCpCol = {
          {1,"04-05"}, {2,"06-07"}, {3,"08-09"},
          {4,"01-02"}, {5,"03-10"}, {6,"11-12"},
          {7,"13-14"}, {8,"15-16"}, {9,"17-18"}
  };
  thisngHBCalib.cpcpl = "HB" + sideletter + ngHBcpCplInCpCol.find(thisngHBCalib.cpcol)->second;
  // determine ribbon, indicates top or bot for the cpOctFib: http://cmsdoc.cern.ch/cms/HCALdocs/document/Mapping/Calib/ngCU_patch/ngCU_HBHE_patch.txt
  //- the ngCUpatch x-block:
  //         cpCol 1                   cpCol 2                   cpCol 3                    
  //         Hxx04-05                  Hxx06-07                  Hxx08-09           coupler block label
  //   crate 20     crate 20     crate 21    crate 21      crate 25    crate 25
  //| 01b20 02b20 01t20 02t20 | 01b21 02b21 01t21 02t21 | 01b25 02b25 01t25 02t25 |
  //| 03b20 04b20 03t20 04t20 | 03b21 04b21 03t21 04t21 | 03b25 04b25 03t25 04t25 | 
  //| 05b20 06b20 05t20 06t20 | 05b21 06b21 05t21 06t21 | 05b25 06b25 05t25 06t25 |
  //| 07b20 08b20 07t20 08t20 | 07b21 08b21 07t21 08t21 | 07b25 08b25 07t25 08t25 |
  //                                
  //- the ngCUpatch y-block:
  //                                  
  //         cpCol 4                   cpCol 5                   cpCol 6           
  //         Hxx01-02                  Hxx03-10                  Hxx11-12           coupler block label
  //   crate 30     crate 24     crate 24    crate 31      crate 31    crate 35          
  //| 01t30 02t30 01b24 02b24 | 01t24 02t24 01b31 02b31 | 01t31 02t31 01b35 02b35 |
  //| 03t30 04t30 03b24 04b24 | 03t24 04t24 03b31 04b31 | 03t31 04t31 03b35 04b35 | 
  //| 05t30 06t30 05b24 06b24 | 05t24 06t24 05b31 06b31 | 05t31 06t31 05b35 06b35 |
  //| 07t30 08t30 07b24 08b24 | 07t24 08t24 07b31 08b31 | 07t31 08t31 07b35 08b35 |
  //                                                                 
  //- the ngCUpatch z-block:
  //                                                                   
  //         cpCol 7                   cpCol 8                   cpCol 9         
  //         Hxx13-14                  Hxx15-16                  Hxx17-18           coupler block label
  //   crate 35     crate 37     crate 37    crate 34      crate 34    crate 30          
  //| 01t35 02t35 01b37 02b37 | 01t37 02t37 01b34 02b34 | 01t34 02t34 01b30 02b30 | 
  //| 03t35 04t35 03b37 04b37 | 03t37 04t37 03b34 04b34 | 03t34 04t34 03b30 04b30 | 
  //| 05t35 06t35 05b37 06b37 | 05t37 06t37 05b34 06b34 | 05t34 06t34 05b30 06b30 |
  //| 07t35 08t35 07b37 08b37 | 07t37 08t37 07b34 08b34 | 07t34 08t34 07b30 08b30 |
  // To set bot or top, just note that order in x-block is bt while in y,z-block is tb
  if(thisngHBCalib.cpcol<=3 && thisngHBCalib.cpcol>=1) {//meaning x-block
    thisngHBCalib.ribbon = (thisngHBCalib.cplc == 1 || thisngHBCalib.cplc == 2) ? "bot" : "top";
  } else if(thisngHBCalib.cpcol<=9 && thisngHBCalib.cpcol>=4){//meaning yz-block
    thisngHBCalib.ribbon = (thisngHBCalib.cplc == 1 || thisngHBCalib.cplc == 2) ? "top" : "bot";
  }

  //set up patch panel
  sideid < 0 ? thisngHBCalib.ppcol = 6 : thisngHBCalib.ppcol = 3;
  thisngHBCalib.pprow = 5;
  thisngHBCalib.pplc = (thisngHBCalib.cpoct - 1)%4 + 1;
  thisngHBCalib.ppcpl = "EB" + sideletter + numberletter + "_CU";
  int ngHBuCrateInWedge[NrbxngHB] = {30, 24, 24, 20, 20, 21, 21, 25, 25, 31, 31, 35, 35, 37, 37, 34, 34, 30};
  thisngHBCalib.ucrate = ngHBuCrateInWedge[thisngHBCalib.wedge-1];
  sideid > 0 ? ( thisngHBCalib.uhtr = ( thisngHBCalib.wedge%2 == 0 ? 8 : 11 ) ) : ( thisngHBCalib.uhtr = (thisngHBCalib.wedge%2 == 0 ? 2 : 5 ) );
  (thisngHBCalib.cpoct%2 == 0) ?  thisngHBCalib.uhtr_fiber = 11 : thisngHBCalib.uhtr_fiber = 10 ;
  thisngHBCalib.dodec = thisngHBCalib.uhtr_fiber%12 + 1;
  const std::map<int, std::pair<int, int> > ngHBufedidInucrate = { {20,{1102,1103}},{21,{1104,1105}},{24,{1100,1101}},{25,{1106,1107}},{30,{1116,1117}},{31,{1108,1109}},{34,{1114,1115}},{35,{1110,1111}},{37,{1112,1113}} };
  sideid < 0 ? thisngHBCalib.ufedid = (ngHBufedidInucrate.find(thisngHBCalib.ucrate)->second).first : thisngHBCalib.ufedid = (ngHBufedidInucrate.find(thisngHBCalib.ucrate)->second).second;
  //set up geometry
  thisngHBCalib.side = sideid;
  thisngHBCalib.eta = 1;
  thisngHBCalib.phi = ( thisngHBCalib.wedge*4 - 5 + 72 ) % 72;
  thisngHBCalib.dphi = 4;
  if(thisngHBCalib.rm_fiber == 2 && thisngHBCalib.fiber_ch>=4 && thisngHBCalib.fiber_ch <=6)
    thisngHBCalib.depth = thisngHBCalib.fiber_ch - 4;
  else{
    thisngHBCalib.depth = 7;
//    thisngHBCalib.cpoct = thisngHBCalib.cplc + 2;//cpOctFib =  same as cpLC + 2
  }
  thisngHBCalib.subdet = "CALIB_HB";
  myngHBCalib.push_back(thisngHBCalib);

  return;
}

void ngHBMappingAlgorithm::LoadngHBQIEMap(std::string QIE11CardMapFileName)                                                                                                                                 
{
  std::ifstream inputFile(QIE11CardMapFileName.c_str());
  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;
    if(!(line.at(0) == 'H' && line.at(1) == 'B')) continue; 
    //std::istringstream ss(line);
    std::stringstream ss(line);
    ngHBQIE11CardMap thisngHBQIE11CardMap;

    //ngHBM01 ngHB19.1.37 RM1 101402 101422 101440
    //ngHBM01 ngHB19.2.53 RM2 100282 100244 100300
    //ngHBM01 ngHB19.3.09 RM3 999999 999999 999999
    //ngHBM01 ngHB19.4.24 RM4 100551 100892 101452
    //rbx, rm, qie11, qie_id;
    std::string tmp;
    std::string rbx_tmp, rm_tmp;
    std::string qie_id_1, qie_id_2, qie_id_3;
    ss >> thisngHBQIE11CardMap.rbx >> tmp >> rm_tmp >> qie_id_1 >> qie_id_2 >> qie_id_3;
    //std::cout << qie_id_1 << ", " << qie_id_2 << ", " << qie_id_3 << std::endl;
    thisngHBQIE11CardMap.rm = rm_tmp.back();

    thisngHBQIE11CardMap.qie11 = "1";
    thisngHBQIE11CardMap.qie_id = qie_id_1;
    myngHBQIE11CardMap.push_back(thisngHBQIE11CardMap);
    thisngHBQIE11CardMap.qie11.clear(); thisngHBQIE11CardMap.qie_id.clear();
    thisngHBQIE11CardMap.qie11 = "2";
    thisngHBQIE11CardMap.qie_id = qie_id_2;
    myngHBQIE11CardMap.push_back(thisngHBQIE11CardMap);
    thisngHBQIE11CardMap.qie11.clear(); thisngHBQIE11CardMap.qie_id.clear();
    thisngHBQIE11CardMap.qie11 = "3";
    thisngHBQIE11CardMap.qie_id = qie_id_3;
    myngHBQIE11CardMap.push_back(thisngHBQIE11CardMap);
    thisngHBQIE11CardMap.qie11.clear(); thisngHBQIE11CardMap.qie_id.clear();
  }
  return ;
}

void ngHBMappingAlgorithm::GetngHBQIEInfoToLMap(
                                            std::string rbx, int rm, int qie11,
                                            int &qie11_id
                                           )
{
  bool qie11match = false;
  for(auto i=0; i<myngHBQIE11CardMap.size(); i++)
  {
    qie11match = (rbx==myngHBQIE11CardMap.at(i).rbx) && (rm==std::stoi(myngHBQIE11CardMap.at(i).rm)) && (qie11==std::stoi(myngHBQIE11CardMap.at(i).qie11));
    if(qie11match)
    {
      qie11_id = std::stoi(myngHBQIE11CardMap.at(i).qie_id);
      break;
    }
    else continue;
  }
  if(!qie11match) std::cout << "#QIE 10 card not found in front end coordinates ???!!!" << std::endl;
  return ;
}
