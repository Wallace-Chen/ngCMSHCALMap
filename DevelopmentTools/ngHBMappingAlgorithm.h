#include <vector>
#include <iostream>

#include "ngHBMappingObject.h"

class ngHBMappingAlgorithm : public ngHBConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHBFrontEnd> myngHBFrontEnd; std::vector<ngHBBackEnd> myngHBBackEnd; std::vector<ngHBPMTBox> myngHBPMTBox; std::vector<ngHBGeometry> myngHBGeometry; std::vector<ngHBTriggerTower> myngHBTriggerTower;
  void ConstructngHBLMapObject();
 private:
  void ConstructngHBFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHBBackEnd(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHBGeometry(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHBPMTBox();
  void ConstructngHBTriggerTower();  
  
  const int ngHBucrateInrbxrmid[Ncrate] = {30,24,20,21,25,31,35,37,34};
  const int ngHBuhtrInrmfifichidType1[Nrm_fiber] = {2, 3, 0, 12,13,14};
  const int ngHBuhtrInrmfifichidType2[Nrm_fiber] = {4, 5, 1, 15,16,17};
  const int ngHBuhtrInrmfifichidType3[Nrm_fiber] = {6, 7, 2, 18,19,20};
  const int ngHBuhtrInrmfifichidType4[Nrm_fiber] = {8, 9, 3, 21,22,23};

  //http://cmsdoc.cern.ch/cms/HCAL/document/Calorimeters/HE/ngHB/ODU/ngHB_RM_fib_symmetries.txt
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/Arjan-verified_26-aug-2016/HBHEP07_template.xls
  const int ngHBphiInrbxrmid_P[NrbxngHB*NrmngHB] = {71,72,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
  const int ngHBphiInrbxrmid_M[NrbxngHB*NrmngHB] = {2,1,72,71,6,5,4,3,10,9,8,7,14,13,12,11,18,17,16,15,22,21,20,19,26,25,24,23,30,29,28,27,34,33,32,31,38,37,36,35,42,41,40,39,46,45,44,43,50,49,48,47,54,53,52,51,58,57,56,55,62,61,60,59,66,65,64,63,70,69,68,67};

  const int ngHBetaInrmfifichid[Nrm_fiber*Nfiber_ch]=
  {
    16, 15, 14,//RM fiber 2
    15, 13, 16,//RM fiber 3
    10, 6,  2, //RM fiber 4
    8,  4,  12,//RM fiber 5
    11, 7,  3, //RM fiber 6
    5,  1,  9, //RM fiber 7
  };

  const int ngHBdepInrmfifichid[Nrm_fiber*Nfiber_ch]=
  {
    2, 2, 1, //RM fiber 2
    1, 1, 1, //RM fiber 3
    1, 1, 1, //RM fiber 4
    1, 1, 1, //RM fiber 5
    1, 1, 1, //RM fiber 6
    1, 1, 1, //RM fiber 7
  };

};

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
          ConstructngHBPMTBox();  
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
  thisngHBFrontEnd.rbx = "ngHB" + sideletter + numberletter;
  thisngHBFrontEnd.rm = rbxrmid%NrmngHB + 1;
  thisngHBFrontEnd.rm_fiber = rmfifichid/Nfiber_ch + 2;
  thisngHBFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie8 map
  //thisngHBFrontEnd.qie8 = (thisngHBFrontEnd.rm_fiber -1)/2+1;
  //thisngHBFrontEnd.rm_fiber%2 != 0 ? thisngHBFrontEnd.qie8_ch = thisngHBFrontEnd.fiber_ch : thisngHBFrontEnd.qie8_ch = 3 + (thisngHBFrontEnd.fiber_ch+1)%3;

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
  int rm = rbxrmid%NrmngHB + 1; double rm_fiber = rmfifichid/Nfiber_ch + 2;
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
  //set uhtr fiber from rm and rm fiber, P and M symmetry, RM1-RM3 and RM2-RM4
  if(sideid>0)
  {
    if     ( rbxrmid%NrmngHB == 0 ){ thisngHBBackEnd.uhtr_fiber = ngHBuhtrInrmfifichidType1[rmfifichid/Nfiber_ch]; } 
    else if( rbxrmid%NrmngHB == 1 ){ thisngHBBackEnd.uhtr_fiber = ngHBuhtrInrmfifichidType2[rmfifichid/Nfiber_ch]; }
    else if( rbxrmid%NrmngHB == 2 ){ thisngHBBackEnd.uhtr_fiber = ngHBuhtrInrmfifichidType3[rmfifichid/Nfiber_ch]; }
    else thisngHBBackEnd.uhtr_fiber = ngHBuhtrInrmfifichidType4[rmfifichid/Nfiber_ch];
  }
  else
  {
    if     ( rbxrmid%NrmngHB == 0 ){ thisngHBBackEnd.uhtr_fiber = ngHBuhtrInrmfifichidType3[rmfifichid/Nfiber_ch]; }
    else if( rbxrmid%NrmngHB == 1 ){ thisngHBBackEnd.uhtr_fiber = ngHBuhtrInrmfifichidType4[rmfifichid/Nfiber_ch]; }
    else if( rbxrmid%NrmngHB == 2 ){ thisngHBBackEnd.uhtr_fiber = ngHBuhtrInrmfifichidType1[rmfifichid/Nfiber_ch]; }
    else thisngHBBackEnd.uhtr_fiber = ngHBuhtrInrmfifichidType2[rmfifichid/Nfiber_ch];
  }
  
  //set backend fiber channel : same as the front end one
  thisngHBBackEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables
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

void ngHBMappingAlgorithm::ConstructngHBPMTBox()
{
  ngHBPMTBox thisngHBPMTBox;
  
  myngHBPMTBox.push_back(thisngHBPMTBox);
  return ;
}

void ngHBMappingAlgorithm::ConstructngHBTriggerTower()
{
  ngHBTriggerTower thisngHBTriggerTower;

  myngHBTriggerTower.push_back(thisngHBTriggerTower);
  return ;
}
