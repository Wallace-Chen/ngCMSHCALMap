#include "HBMappingAlgorithm.h"
void HBMappingAlgorithm::ConstructHBLMapObject(std::string Mode)
{
  if(Mode == "Normal")
  {
    std::cout << "#Loading information from QIE allocation file..." << std::endl;
    LoadHBQIEMap("HBHOQIEInput/RBX_RM_QIE_2016Nov03.txt");
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
  }
  else if(Mode == "Calib")
  {
    std::cout << "#Constructing HB Calib LMap Object..." << std::endl;
    for(int irbx=0;irbx<NrbxHB*2;irbx++)
    {
      for(int irm=0;irm<NrmHBCalib;irm++)
      {
        for(int irmfi=0;irmfi<Nrm_fiberCalib;irmfi++)
        {
          for(int ifich=0;ifich<Nfiber_ch;ifich++)
          {
            int sideid; irbx<NrbxHB ? sideid = 1 : sideid = -1;//0..to 17 is P side, while 17 to 35 is M side
            int rbxrmid; irbx<NrbxHB ? rbxrmid = irbx*NrmHBCalib+irm : rbxrmid = (irbx-NrbxHB)*NrmHBCalib+irm;//HB 0...to 71
            int rmfifichid = irmfi*Nfiber_ch+ifich;//HB
            //std::cout << "#Side: " << sideid << "; RBXRM: " << rbxrmid << "; RMFIFICH: " << rmfifichid << std::endl;
            ConstructHBCalib(sideid,rbxrmid,rmfifichid);
          }
        }
      }
    }
  }
  else
  {
    std::cout << "#Invalid generate mode for HB Logical map!" << std::endl;
    return ;
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
  //thisHBFrontEnd.qie8 = (thisHBFrontEnd.rm_fiber -1)/2+1;
  thisHBFrontEnd.qie8 = int(thisHBFrontEnd.rm_fiber/2);
  thisHBFrontEnd.rm_fiber%2 == 0 ? thisHBFrontEnd.qie8_ch = thisHBFrontEnd.fiber_ch : thisHBFrontEnd.qie8_ch = 3 + (thisHBFrontEnd.fiber_ch+1)%3;
  //set tmp qie8 id
  //thisHBFrontEnd.qie8_id = 999991;
  //set qie8 id
  GetHBQIEInfoToLMap(
                     thisHBFrontEnd.rbx, thisHBFrontEnd.rm, thisHBFrontEnd.qie8,
                     thisHBFrontEnd.qie8_id
                    );
  if( thisHBFrontEnd.qie8_id == 999999 ) thisHBFrontEnd.qie8_id = 999991;
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
  //  thisHBBackEnd.ppcol = (rm_fiber-1)/4+3;
  thisHBBackEnd.ppcol = sideid>0 ? (rm_fiber-1)/4+3 : (rm_fiber-1)/4+7;
  thisHBBackEnd.pprow = rm;
  thisHBBackEnd.pplc = (rm_fiber-1)%4+1;
  std::string cplletter;
  rm_fiber<=4 ? cplletter="A" : cplletter="B";
  thisHBBackEnd.ppcpl = rbx+"_RM"+std::to_string(rm)+cplletter;

  //  printf("ppcol = %3d ( or %3d ?), ppcpl = %7s \n",thisHBBackEnd.ppcol, ((rm_fiber-1)/4+1),thisHBBackEnd.ppcpl);

  //then set uhtr fiber infomation from patch panel
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/optical_patch_2018calib.txt
  /*
  The pure HB uHTRs - slots 4 10:

|                 crate 34 slot 10                          |                 crate 34 slot 4                           |  
             HEP17                         HBP17                         HEM17                         HBM17            
                              | ------------ |                             | ------------ |                                Calib
| ------------ | ------------ | 04b------08b | 12b04t08t12t | ------------ | ------------ | 04b------08b | 12b04t08t12t |  RM4
| ------------ | ------------ | 03b------07b | 11b03t07t11t | ------------ | ------------ | 03b------07b | 11b03t07t11t |  RM3
| ------------ | ------------ | 02b------06b | 10b02t06t10t | ------------ | ------------ | 02b------06b | 10b02t06t10t |  RM2
| ------------ | ------------ | 01b------05b | 09b01t05t09t | ------------ | ------------ | 01b------05b | 09b01t05t09t |  RM1


  The mixed HB/HE uHTRs - slots 5 11:

|                 crate 34 slot 11                          |                 crate 34 slot 5                           |
             HEP17                         HBP17                          HEM17                        HBM17            
                              | ------11b12b |                             | ------11b12b |                                Calib
| ---------10t | 11t---12t--- | ---09b10b--- | ------------ | ---------10t | 11t---12t--- | ---09b10b--- | ------------ |  RM4
| ---07t---08t | ---09t------ | ---07b08b--- | ------------ | ---07t---08t | ---09t------ | ---07b08b--- | ------------ |  RM3
| ---------04t | 05t---06t--- | ---05b06b--- | ------------ | ---------04t | 05t---06t--- | ---05b06b--- | ------------ |  RM2
| ---01t---02t | ---03t------ | ---03b04b--- | ------------ | ---01t---02t | ---03t------ | ---03b04b--- | ------------ |  RM1

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
  */

  if( ismixed_HB )
  {
    if     (thisHBBackEnd.ppcol==3 || thisHBBackEnd.ppcol==7 ){ thisHBBackEnd.uhtr_fiber = (thisHBBackEnd.pprow-1)*2+rm_fiber-2+2; }
    else{ std::cout << "the ppCol of HB channel is not 3 in mixed HBHE slot for HB??!! Please check!" << std::endl; }
  }
  else
  {
    //notice here we change the order, first rm_fiber then rm!!!
    if     (thisHBBackEnd.ppcol==3 || thisHBBackEnd.ppcol==7){ thisHBBackEnd.uhtr_fiber = (int(rm_fiber)/4)*4+thisHBBackEnd.pprow-1; }
    else if(thisHBBackEnd.ppcol==4 || thisHBBackEnd.ppcol==8){ thisHBBackEnd.uhtr_fiber = (rm_fiber-5)*4+thisHBBackEnd.pprow-1+8; }
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

void HBMappingAlgorithm::ConstructHBCalib(int sideid, int rbxrmid, int rmfifichid)
{
  HBCalib thisHBCalib;
  //set up frontend part
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmHBCalib + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmHBCalib + 1) : numberletter = std::to_string(rbxrmid/NrmHBCalib + 1); 
  thisHBCalib.rbx = "HB" + sideletter + numberletter;
  thisHBCalib.rm = rbxrmid%NrmHBCalib + 5; //rm=5 for calibration channels
  thisHBCalib.rm_fiber = rmfifichid/Nfiber_ch + 1;
  thisHBCalib.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie8 map
  thisHBCalib.qie8 = int(thisHBCalib.rm_fiber/2) + 1;                                                                                                                                                     
  thisHBCalib.qie8_ch = thisHBCalib.fiber_ch;
  //set tmp qie8 id                                                                                                                                                                                        
  thisHBCalib.qie8_id = 100000;
  thisHBCalib.wedge = rbxrmid/NrmHBCalib + 1; //1,...,18
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
  int HBtrunkSectorInWedge[NrbxHB] = {2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3};
  int HBcpColInWedge[NrbxHB] = {4, 4, 5, 1, 1, 2, 2, 3, 3, 5, 6, 6, 7, 7, 8, 8, 9, 9};
  std::string trunk_sector_str = std::to_string(HBtrunkSectorInWedge[thisHBCalib.wedge-1]);
  thisHBCalib.trunk = trunk_sector_str + "-" + std::to_string( thisHBCalib.rm_fiber );
  thisHBCalib.cpcol = HBcpColInWedge[thisHBCalib.wedge-1];
  sideid < 0 ? thisHBCalib.cprow = 1 : thisHBCalib.cprow = 3;
  bool if12InxyzWedge = (trunk_sector_str == "1" && thisHBCalib.wedge%2 == 0) || (trunk_sector_str == "2" && thisHBCalib.wedge%2 == 1) || (trunk_sector_str == "3" && thisHBCalib.wedge%2 == 1);
  if( if12InxyzWedge ) thisHBCalib.cplc = thisHBCalib.rm_fiber;                                                                                                                                         
  else thisHBCalib.cplc = thisHBCalib.rm_fiber + 2;
  thisHBCalib.cpoct = (4-thisHBCalib.cprow)*2 + thisHBCalib.rm_fiber;
  const std::map<int, std::string > HBcpCplInCpCol = { 
                                                      {1,"04-05"}, {2,"06-07"}, {3,"08-09"},
                                                      {4,"01-02"}, {5,"03-10"}, {6,"11-12"},
                                                      {7,"13-14"}, {8,"15-16"}, {9,"17-18"}
                                                     };
  thisHBCalib.cpcpl = "HB" + sideletter + HBcpCplInCpCol.find(thisHBCalib.cpcol)->second;
  //set up patch panel
  /*
- the calib fibers for each patch arrive in a single 8-fiber octopus, terminated LC
  from a central calib fiber patch, which receives all the calib fibers from the entirety of HBHE
- There are two fibers from each HB RBX, and one fiber from each legacy HB RBX, meaning that 6 (or perhaps 8)
  of the 8 fibers are used (I allow here the possibility that ngHB RBXes may have two fibers).
- The P-side RBXes come to coupler column 3, the M-side to coupler column 6:
         HEP17                 HBP17                 HEM17                 HBM17     
                      | e1e2b1b2 |                     | e1e2b1b2 |                        calib |HBEP16| |HBEP17|
| 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 |  RM4
| 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 |  RM3
| 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 |  RM2
| 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 | 01020304 | 05060708 |  RM1
  */
  sideid < 0 ? thisHBCalib.ppcol = 6 : thisHBCalib.ppcol = 3;
  thisHBCalib.pprow = 5;
  //thisHBCalib.pplc = (thisHBCalib.rm_fiber-1)%4+1;
  thisHBCalib.pplc = thisHBCalib.rm_fiber + 2;
  //thisHBCalib.dodec = (thisHBCalib.uhtr_fiber)%12+1;
  thisHBCalib.dodec = 11;
  thisHBCalib.ppcpl = "EB" + sideletter + numberletter + "_CU";

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
  int HBuCrateInWedge[NrbxHB] = {30, 24, 24, 20, 20, 21, 21, 25, 25, 31, 31, 35, 35, 37, 37, 34, 34, 30};
  thisHBCalib.ucrate = HBuCrateInWedge[thisHBCalib.wedge-1];
  if     (thisHBCalib.ppcol == 6) thisHBCalib.uhtr = 5;
  else if(thisHBCalib.ppcol == 3) thisHBCalib.uhtr = 11;
  else{ std::cout << "#HB Calib channel not in ppcol 6 nor ppcol 3, please check!!" << std::endl; thisHBCalib.uhtr = 0; }
  if     (thisHBCalib.rm_fiber == 1) thisHBCalib.uhtr_fiber = 10;
  else if(thisHBCalib.rm_fiber == 2) thisHBCalib.uhtr_fiber = 11; //this is only for ngHB
  else{ std::cout << "#HB Calib channel not in RM fiber 1, please check!!" << std::endl; thisHBCalib.uhtr_fiber = -1; }
  const std::map<int, std::pair<int, int> > HBufedidInucrate = { {20,{1102,1103}},{21,{1104,1105}},{24,{1100,1101}},{25,{1106,1107}},{30,{1116,1117}},{31,{1108,1109}},{34,{1114,1115}},{35,{1110,1111}},{37,{1112,1113}} };
  thisHBCalib.uhtr <= 6 ? thisHBCalib.ufedid = ((HBufedidInucrate.find(thisHBCalib.ucrate))->second).first : thisHBCalib.ufedid = ((HBufedidInucrate.find(thisHBCalib.ucrate))->second).second;

  //set up Geometry part
  thisHBCalib.side = sideid;
  thisHBCalib.eta = 1;
  thisHBCalib.depth = thisHBCalib.fiber_ch;
  thisHBCalib.dphi = 4;
  //if(sideid > 0)
  //{
  //follow HB P side rm 1
  thisHBCalib.phi = HBphiInrbxrmid_P[(thisHBCalib.wedge-1)*4+thisHBCalib.rm-5];
  //}
  //else
  //{
    //thisHBCalib.phi = HBphiInrbxrmid_M_dphi1[(thisHBCalib.wedge-1)*4+thisHBCalib.rm-5];
  //}
  thisHBCalib.subdet = "CALIB_HB";

  myHBCalib.push_back(thisHBCalib);
  return ;
}

void HBMappingAlgorithm::LoadHBQIEMap(std::string QIE8CardMapFileName)                                                                                                                                 
{
  std::ifstream inputFile(QIE8CardMapFileName.c_str());
  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;
    if(!(line.at(0) == 'H' && line.at(1) == 'B')) continue; 
    //std::istringstream ss(line);
    std::stringstream ss(line);
    HBQIE8CardMap thisHBQIE8CardMap;

    //HBM01 HB19.1.37 RM1 101402 101422 101440
    //HBM01 HB19.2.53 RM2 100282 100244 100300
    //HBM01 HB19.3.09 RM3 999999 999999 999999
    //HBM01 HB19.4.24 RM4 100551 100892 101452
    //rbx, rm, qie8, qie_id;
    std::string tmp;
    std::string rbx_tmp, rm_tmp;
    std::string qie_id_1, qie_id_2, qie_id_3;
    ss >> thisHBQIE8CardMap.rbx >> tmp >> rm_tmp >> qie_id_1 >> qie_id_2 >> qie_id_3;
    //std::cout << qie_id_1 << ", " << qie_id_2 << ", " << qie_id_3 << std::endl;
    thisHBQIE8CardMap.rm = rm_tmp.back();

    thisHBQIE8CardMap.qie8 = "1";
    thisHBQIE8CardMap.qie_id = qie_id_1;
    myHBQIE8CardMap.push_back(thisHBQIE8CardMap);
    thisHBQIE8CardMap.qie8.clear(); thisHBQIE8CardMap.qie_id.clear();
    thisHBQIE8CardMap.qie8 = "2";
    thisHBQIE8CardMap.qie_id = qie_id_2;
    myHBQIE8CardMap.push_back(thisHBQIE8CardMap);
    thisHBQIE8CardMap.qie8.clear(); thisHBQIE8CardMap.qie_id.clear();
    thisHBQIE8CardMap.qie8 = "3";
    thisHBQIE8CardMap.qie_id = qie_id_3;
    myHBQIE8CardMap.push_back(thisHBQIE8CardMap);
    thisHBQIE8CardMap.qie8.clear(); thisHBQIE8CardMap.qie_id.clear();
  }
  return ;
}

void HBMappingAlgorithm::GetHBQIEInfoToLMap(
                                            std::string rbx, int rm, int qie8,
                                            int &qie8_id
                                           )
{
  bool qie8match = false;
  for(auto i=0; i<myHBQIE8CardMap.size(); i++)
  {
    qie8match = (rbx==myHBQIE8CardMap.at(i).rbx) && (rm==std::stoi(myHBQIE8CardMap.at(i).rm)) && (qie8==std::stoi(myHBQIE8CardMap.at(i).qie8));
    if(qie8match)
    {
      qie8_id = std::stoi(myHBQIE8CardMap.at(i).qie_id);
      break;
    }
    else continue;
  }
  if(!qie8match) std::cout << "#QIE 10 card not found in front end coordinates ???!!!" << std::endl;
  return ;
}
