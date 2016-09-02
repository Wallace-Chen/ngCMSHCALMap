#include <vector>
#include <iostream>

#include "ngHEMappingObject.h"

class ngHEMappingAlgorithm : public ngHEConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHEFrontEnd> myngHEFrontEnd; std::vector<ngHEBackEnd> myngHEBackEnd; std::vector<ngHEPMTBox> myngHEPMTBox; std::vector<ngHEGeometry> myngHEGeometry; std::vector<ngHETriggerTower> myngHETriggerTower;
  void ConstructngHELMapObject();
 private:
  void ConstructngHEFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHEBackEnd(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHEGeometry(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHEPMTBox();
  void ConstructngHETriggerTower();  
  
  const int ngHEucrateInrbxrmid[Ncrate] = {30,24,20,21,25,31,35,37,34};
  const int ngHEuhtrInrmfifichidType1[Nrm_fiber] = {18,19,20,14,15,18,19,20};
  const int ngHEuhtrInrmfifichidType2[Nrm_fiber] = {21,22,23,16,17,21,22,23};
  const int ngHEuhtrInrmfifichidType3[Nrm_fiber] = {6,7,8,2,3,6,7,8};
  const int ngHEuhtrInrmfifichidType4[Nrm_fiber] = {9,10,11,4,5,9,10,11};

  const int ngHEphiInrbxrmid_P_dphi1[NrbxngHE*NrmngHE] = {71,72,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
  const int ngHEphiInrbxrmid_P_dphi2[NrbxngHE*NrmngHE] = {71,71,1,1,3,3,5,5,7,7,9,9,11,11,13,13,15,15,17,17,19,19,21,21,23,23,25,25,27,27,29,29,31,31,33,33,35,35,37,37,39,39,41,41,43,43,45,45,47,47,49,49,51,51,53,53,55,55,57,57,59,59,61,61,63,63,65,65,67,67,69,69};
  const int ngHEphiInrbxrmid_M_dphi1[NrbxngHE*NrmngHE] = {2,1,72,71,6,5,4,3,10,9,8,7,14,13,12,11,18,17,16,15,22,21,20,19,26,25,24,23,30,29,28,27,34,33,32,31,38,37,36,35,42,41,40,39,46,45,44,43,50,49,48,47,54,53,52,51,58,57,56,55,62,61,60,59,66,65,64,63,70,69,68,67};
  const int ngHEphiInrbxrmid_M_dphi2[NrbxngHE*NrmngHE] = {1,1,71,71,5,5,3,3,9,9,7,7,13,13,11,11,17,17,15,15,21,21,19,19,25,25,23,23,29,29,27,27,33,33,31,31,37,37,35,35,41,41,39,39,45,45,43,43,49,49,47,47,53,53,51,51,57,57,55,55,61,61,59,59,65,65,63,63,69,69,67,67};
  const int ngHEetaInrmfifichidType1[Nrm_fiber*Nfiber_ch] = {16,17,17,18,18,18,18,18,28,28,28,28,28,28,28,29,29,26,//rm fiber 1,2,3
                                                             19,19,19,19,19,19,20,20,20,20,20,20,22,22,22,22,22,22,24,24,24,24,24,24,26,26,26,26,26,26};//rm fiber 4,5,6,7,8
  const int ngHEetaInrmfifichidType2[Nrm_fiber*Nfiber_ch] = {16,17,17,18,18,18,18,18,27,27,27,27,27,27,27,29,29,26,//rm fiber 1,2,3
                                                             19,19,19,19,19,19,20,20,20,20,20,20,21,21,21,21,21,21,23,23,23,23,23,23,25,25,25,25,25,25};//rm fiber 4,5,6,7,8
  //special case in depth : only 1(HB),2(HB),4(ngHE) for eta 16, only 2(ngHE),3(ngHE) for eta 17
  const int ngHEdepthInrmfifichidType1[Nrm_fiber*Nfiber_ch] = {4,2,3,1,2,3,4,5,1,2,3,4,5,6,7,1,3,7,//rm fiber 1,2,3
                                                               1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6};//rm fiber 4,5,6,7,8
  const int ngHEdepthInrmfifichidType2[Nrm_fiber*Nfiber_ch] = {4,2,3,1,2,3,4,5,1,2,3,4,5,6,7,2,3,7,//rm fiber 1,2,3
                                                               1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6};//rm fiber 4,5,6,7,8
};

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
  thisngHEFrontEnd.rm_fiber = rmfifichid/Nfiber_ch +1;
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
  //
  thisngHEBackEnd.ucrate = ngHEucrateInrbxrmid[((rbxrmid+4)%72)/8];
  if(sideid>0)
  { 
    if( rmfifichid < 18 ) (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 11 : thisngHEBackEnd.uhtr = 8;
    else (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 12 : thisngHEBackEnd.uhtr = 9;
  }
  else
  { 
    if( rmfifichid < 18 ) (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 5 : thisngHEBackEnd.uhtr = 2;
    else (rbxrmid/4)%2==0 ? thisngHEBackEnd.uhtr = 6 : thisngHEBackEnd.uhtr = 3;
  }

  thisngHEBackEnd.ufpga = "uHTR";
  
  if(sideid>0)
  {
    if     ( rbxrmid%4 == 0 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType1[rmfifichid/6]; } 
    else if( rbxrmid%4 == 1 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType2[rmfifichid/6]; }
    else if( rbxrmid%4 == 2 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType3[rmfifichid/6]; }
    else thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType4[rmfifichid/6];
  }
  else
  {
    if     ( rbxrmid%4 == 0 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType3[rmfifichid/6]; }
    else if( rbxrmid%4 == 1 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType4[rmfifichid/6]; }
    else if( rbxrmid%4 == 2 ){ thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType1[rmfifichid/6]; }
    else thisngHEBackEnd.uhtr_fiber = ngHEuhtrInrmfifichidType2[rmfifichid/6];
  }
  
  thisngHEBackEnd.fiber_ch = rmfifichid%6;

  //set secondary variables
  myngHEBackEnd.push_back(thisngHEBackEnd);
  return ;
}

void ngHEMappingAlgorithm::ConstructngHEGeometry(int sideid, int rbxrmid, int rmfifichid)
{
  ngHEGeometry thisngHEGeometry;
  //side -> subdet -> eta, depth -> dphi -> phi
  thisngHEGeometry.side = sideid;
  
  if(rbxrmid%2 == 0){ thisngHEGeometry.eta = ngHEetaInrmfifichidType1[rmfifichid]; thisngHEGeometry.depth = ngHEdepthInrmfifichidType1[rmfifichid]; }
  else{ thisngHEGeometry.eta = ngHEetaInrmfifichidType2[rmfifichid]; thisngHEGeometry.depth = ngHEdepthInrmfifichidType2[rmfifichid]; }
  
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
  ( rbxrmid%2==1 && (rmfifichid == 16 || rmfifichid == 17) ) ? thisngHEGeometry.subdet = "HEX" : thisngHEGeometry.subdet = "HE";

  if(thisngHEGeometry.subdet == "HEX") 
  {
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
