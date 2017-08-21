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
  thisngHBFrontEnd.rm_fiber = rmfifichid/Nfiber_ch + 1;
  thisngHBFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie11 map
  //first map from swapped rmfi and fich to natural counterpart
  int rm_fiber_nature = -1, fiber_ch_nature=-1;
  (thisngHBFrontEnd.rm==1 || thisngHBFrontEnd.rm==3) ? rm_fiber_nature = (ngHBrmfiswappedTonature_rm13.find(thisngHBFrontEnd.rm_fiber))->second : rm_fiber_nature = (ngHBrmfiswappedTonature_rm24.find(thisngHBFrontEnd.rm_fiber))->second;
  fiber_ch_nature = (ngHBfichswappedTonature.find(thisngHBFrontEnd.fiber_ch))->second; //fiber channle from swapped to natural
  //FIXME
  //Notice here is different from the remapped HB!!! QIE8 ch swap vs rm fi ch swap!!! 
  thisngHBFrontEnd.qie11 = (rm_fiber_nature-1)/2+1;
  rm_fiber_nature%2 != 0 ? thisngHBFrontEnd.qie11_ch = fiber_ch_nature+1 : thisngHBFrontEnd.qie11_ch = 8+fiber_ch_nature+1;
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
  int rm = rbxrmid%NrmngHB + 1; int rm_fiber = rmfifichid/Nfiber_ch + 1;
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
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/optical_patch_2018.txt
  /*
  The pure HB uHTRs - slots 4 10:

|                 crate 34 slot 10                          |                 crate 34 slot 4                           |
             HEP17                         HBP17                         HEM17                         HBM17
| ------------ | ------------ | 04b------08b | 12b04t08t12t | ------------ | ------------ | ------------ | ------------ |  RM4
| ------------ | ------------ | 03b------07b | 11b03t07t11t | ------------ | ------------ | ------------ | ------------ |  RM3
| ------------ | ------------ | 02b------06b | 10b02t06t10t | ------------ | ------------ | ------------ | ------------ |  RM2
| ------------ | ------------ | 01b------05b | 09b01t05t09t | ------------ | ------------ | ------------ | ------------ |  RM1

  The mixed HB/HE uHTRs - slots 5 11:

|                 crate 34 slot 11                          |                 crate 34 slot 5                           |
             HEP17                         HBP17                          HEM17                        HBM17
| ---------10t | 11t---12t--- | ---09b10b--- | ------------ | ---------10t | 11t---12t--- | ---09b10b--- | ------------ |  RM4
| ---07t---08t | ---09t------ | ---07b08b--- | ------------ | ---07t---08t | ---09t------ | ---07b08b--- | ------------ |  RM3
| ---------04t | 05t---06t--- | ---05b06b--- | ------------ | ---------04t | 05t---06t--- | ---05b06b--- | ------------ |  RM2
| ---01t---02t | ---03t------ | ---03b04b--- | ------------ | ---01t---02t | ---03t------ | ---03b04b--- | ------------ |  RM1

[1b-12b]:0 to 11 uhtr fiber
[1t-12t]:12 to 23 uhtr fiber

  The pure HB uHTRs - slots 4 10:

|             crate 34 slot 10              |             crate 34 slot 4               |
         HEP17                 HBP17                 HEM17                 HBM17
| -------- | -------- | 03----07 | 11151923 | ---------| ---------| ---------| -------- |  RM4
| ---------| ---------| 02----06 | 10141822 | ---------| -------- | -------- | -------- |  RM3
| ---------| -------- | 01----05 | 09131721 | ---------| ---------| -------- | -------- |  RM2
| ---------| -------- | 00----04 | 08121620 | ---------| ---------| -------- | -------- |  RM1

  The mixed HB/HE uHTRs - slots 5 11:

|             crate 34 slot 11              |             crate 34 slot 5               |
         HEP17                 HBP17                 HEM17                 HBM17
| ------21 | 22--23-- | --0809-- | -------- | ------21 | 22--23-- | --0809-- | -------- |  RM4
| --18--19 | --20---- | --0607-- | -------- | --18--19 | --20---- | --0607-- | -------- |  RM3
| ------15 | 16--17-- | --0405-- | -------- | ------15 | 16--17-- | --0405-- | -------- |  RM2
| --12--13 | --14---- | --0203-- | -------- | --12--13 | --14---- | --0203-- | -------- |  RM1
  */

  if( ismixed_ngHB )
  {
    if     (thisngHBBackEnd.ppcol==3){ thisngHBBackEnd.uhtr_fiber = (thisngHBBackEnd.pprow-1)*2+rm_fiber-2+2; }
    else{ std::cout << "the ppCol of HB channel is not 3 in mixed HBHE slot for HB??!! Please check!" << std::endl; }
  }
  else
  {
    //notice here we change the order, first rm_fiber then rm!!!
    if     (thisngHBBackEnd.ppcol==3){ thisngHBBackEnd.uhtr_fiber = (int(rm_fiber)/4)*4+thisngHBBackEnd.pprow-1; }
    else if(thisngHBBackEnd.ppcol==4){ thisngHBBackEnd.uhtr_fiber = (rm_fiber-5)*4+thisngHBBackEnd.pprow-1+8; }
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
