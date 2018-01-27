#include <vector>
#include <iostream>
#include <map>
#include <utility>

#include "ngHEMappingObject.h"

class ngHEMappingAlgorithm : public ngHEConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHEFrontEnd> myngHEFrontEnd; std::vector<ngHEBackEnd> myngHEBackEnd; std::vector<ngHESiPM> myngHESiPM; std::vector<ngHEGeometry> myngHEGeometry; std::vector<ngHETriggerTower> myngHETriggerTower;
  void ConstructngHELMapObject();
 private:
  void ConstructngHEFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHEBackEnd(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHEGeometry(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHESiPM(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHETriggerTower(int eta, int phi);  
  
  const int ngHEucrateInrbxrmid[Ncrate] = {30,24,20,21,25,31,35,37,34};
  //const int ngHEuhtrInrmfifichidType1[Nrm_fiber] = {1,12, 2, 13, 3,14, 4, 5};
  //const int ngHEuhtrInrmfifichidType2[Nrm_fiber] = {6, 7, 8, 15,16, 9,17,10};
  //const int ngHEuhtrInrmfifichidType3[Nrm_fiber] = {13,18,14,19,15,20,16,17};
  //const int ngHEuhtrInrmfifichidType4[Nrm_fiber] = {18,19,20,21,22,21,23,22};

  //http://cmsdoc.cern.ch/cms/HCAL/document/Calorimeters/HE/ngHE/ODU/ngHE_RM_fib_symmetries.txt
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/Arjan-verified_26-aug-2016/HBHEP07_template.xls
  const int ngHEphiInrbxrmid_P_dphi1[NrbxngHE*NrmngHE] = {71,72,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
  const int ngHEphiInrbxrmid_P_dphi2[NrbxngHE*NrmngHE] = {71,71,1,1,3,3,5,5,7,7,9,9,11,11,13,13,15,15,17,17,19,19,21,21,23,23,25,25,27,27,29,29,31,31,33,33,35,35,37,37,39,39,41,41,43,43,45,45,47,47,49,49,51,51,53,53,55,55,57,57,59,59,61,61,63,63,65,65,67,67,69,69};
  const int ngHEphiInrbxrmid_M_dphi1[NrbxngHE*NrmngHE] = {2,1,72,71,6,5,4,3,10,9,8,7,14,13,12,11,18,17,16,15,22,21,20,19,26,25,24,23,30,29,28,27,34,33,32,31,38,37,36,35,42,41,40,39,46,45,44,43,50,49,48,47,54,53,52,51,58,57,56,55,62,61,60,59,66,65,64,63,70,69,68,67};
  const int ngHEphiInrbxrmid_M_dphi2[NrbxngHE*NrmngHE] = {1,1,71,71,5,5,3,3,9,9,7,7,13,13,11,11,17,17,15,15,21,21,19,19,25,25,23,23,29,29,27,27,33,33,31,31,37,37,35,35,41,41,39,39,45,45,43,43,49,49,47,47,53,53,51,51,57,57,55,55,61,61,59,59,65,65,63,63,69,69,67,67};

  const int ngHEetaInrmfifichid_RM1[Nrm_fiber*Nfiber_ch]=
  {
    19, 20, 22, 24, 24, 26, //RM fiber 1
    29, 28, 18, 17, 16, 29, //RM fiber 2
    24, 24, 26, 26, 19, 26, //RM fiber 3
    28, 28, 28, 28, 26, 28, //RM fiber 4
    19, 26, 20, 20, 22, 22, //RM fiber 5
    18, 28, 17, 18, 18, 18, //RM fiber 6
    19, 20, 22, 24, 19, 26, //RM fiber 7
    19, 24, 22, 20, 22, 20  //RM fiber 8
  };

  const int ngHEdepInrmfifichid_RM1[Nrm_fiber*Nfiber_ch]=
  {
    2, 3, 3, 3, 2, 2, //RM fiber 1
    1, 1, 2, 2, 4, 2, //RM fiber 2
    6, 5, 5, 6, 3, 3, //RM fiber 3
    2, 5, 3, 7, 7, 6, //RM fiber 4
    5, 4, 6, 5, 5, 6, //RM fiber 5
    3, 4, 3, 5, 1, 4, //RM fiber 6
    1, 1, 1, 1, 4, 1, //RM fiber 7
    6, 4, 2, 2, 4, 4  //RM fiber 8
  };

  const int ngHEetaInrmfifichid_RM2[Nrm_fiber*Nfiber_ch]=
  {
    19, 19, 21, 20, 21, 20, //RM fiber 1
    19, 20, 21, 23, 19, 25, //RM fiber 2
    23, 25, 20, 21, 23, 20, //RM fiber 3
    18, 18, 18, 17, 27, 18, //RM fiber 4
    27, 27, 27, 27, 29, 0,  //RM fiber 5
    21, 23, 25, 25, 19, 25, //RM fiber 6
    27, 0,  18, 17, 16, 27, //RM fiber 7
    19, 20, 21, 23, 23, 25  //RM fiber 8
  };

  const int ngHEdepInrmfifichid_RM2[Nrm_fiber*Nfiber_ch]=
  {
    5, 6, 2, 2, 4, 4, //RM fiber 1
    1, 1, 1, 1, 4, 1, //RM fiber 2
    6, 4, 5, 6, 4, 6, //RM fiber 3
    1, 4, 5, 3, 4, 3, //RM fiber 4
    7, 3, 5, 6, 3, 0, //RM fiber 5
    5, 5, 6, 5, 3, 3, //RM fiber 6
    1, 0, 2, 2, 4, 2, //RM fiber 7
    2, 3, 3, 3, 2, 2  //RM fiber 8
  };

  const int ngHEetaInrmfifichid_RM3[Nrm_fiber*Nfiber_ch]=
  {
    19, 20, 21, 23, 23, 25, //RM fiber 1
    27, 0,  18, 17, 16, 27, //RM fiber 2
    23, 23, 25, 25, 19, 25, //RM fiber 3
    0,  27, 27, 27, 29, 27, //RM fiber 4
    19, 25, 20, 20, 21, 21, //RM fiber 5
    18, 27, 17, 18, 18, 18, //RM fiber 6
    19, 20, 21, 23, 19, 25, //RM fiber 7
    19, 23, 21, 20, 21, 20  //RM fiber 8
  };

  const int ngHEdepInrmfifichid_RM3[Nrm_fiber*Nfiber_ch]=
  {
    2, 3, 3, 3, 2, 2, //RM fiber 1
    1, 0, 2, 2, 4, 2, //RM fiber 2
    6, 5, 5, 6, 3, 3, //RM fiber 3
    0, 5, 3, 7, 3, 6, //RM fiber 4
    5, 4, 6, 5, 5, 6, //RM fiber 5
    3, 4, 3, 5, 1, 4, //RM fiber 6
    1, 1, 1, 1, 4, 1, //RM fiber 7
    6, 4, 2, 2, 4, 4  //RM fiber 8
  };

  const int ngHEetaInrmfifichid_RM4[Nrm_fiber*Nfiber_ch]=
  {
    19, 19, 22, 20, 22, 20, //RM fiber 1
    19, 20, 22, 24, 19, 26, //RM fiber 2
    24, 26, 20, 22, 24, 20, //RM fiber 3
    18, 18, 18, 17, 28, 18, //RM fiber 4
    28, 28, 28, 28, 26, 28, //RM fiber 5
    22, 24, 26, 26, 19, 26, //RM fiber 6
    29, 28, 18, 17, 16, 29, //RM fiber 7
    19, 20, 22, 24, 24, 26  //RM fiber 8
  };

  const int ngHEdepInrmfifichid_RM4[Nrm_fiber*Nfiber_ch]=
  {
    5, 6, 2, 2, 4, 4, //RM fiber 1
    1, 1, 1, 1, 4, 1, //RM fiber 2
    6, 4, 5, 6, 4, 6, //RM fiber 3
    1, 4, 5, 3, 4, 3, //RM fiber 4
    7, 3, 5, 6, 7, 2, //RM fiber 5
    5, 5, 6, 5, 3, 3, //RM fiber 6
    1, 1, 2, 2, 4, 2, //RM fiber 7
    2, 3, 3, 3, 2, 2  //RM fiber 8
  };

  //QIE11 calibration constants
  //LMap add QIE11 ID
  struct ngHEQIE11CardMap
  {
    std::string rbx, rm, qie, qie_id;
  };
  std::vector<ngHEQIE11CardMap> myngHEQIE11CardMap;
  void LoadngHEQIEMap(std::string QIE11CardMapFileName);
  void GetngHEQIEInfoToLMap(
                            std::string rbx, int rm, int qie,
                            int &qie11_id
                           );
};
