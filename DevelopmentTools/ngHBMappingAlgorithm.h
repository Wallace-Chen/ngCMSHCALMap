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
