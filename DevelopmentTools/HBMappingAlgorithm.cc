#include "HBMappingAlgorithm.h"
void HBMappingAlgorithm::ConstructHBLMapObject()
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
  //  thisHBFrontEnd.qie8 = (thisHBFrontEnd.rm_fiber -1)/2+1;
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
