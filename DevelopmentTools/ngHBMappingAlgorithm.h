#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <utility>

#include "ngHBMappingObject.h"

class ngHBMappingAlgorithm : public ngHBConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHBFrontEnd> myngHBFrontEnd; std::vector<ngHBBackEnd> myngHBBackEnd; std::vector<ngHBSiPM> myngHBSiPM; std::vector<ngHBGeometry> myngHBGeometry; std::vector<ngHBTriggerTower> myngHBTriggerTower;std::vector<ngHBTriggerTowerFiber> myngHBTriggerTowerFiber;
  std::vector<ngHBCalib> myngHBCalib;
  void ConstructngHBLMapObject(std::string Mode);
 private:
  void ConstructngHBFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHBBackEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHBGeometry(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHBSiPM(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHBTriggerTower(int rm, int rm_fiber, int fiber_ch, int qie11_ch);
  void ConstructngHBTriggerTowerFiber(int eta, int phi, int depth);
  void ConstructngHBCalib(int sideid, int rbxrmid, int rmfifichid);

  const int ngHBcrateInrbxrmid[Ncrate] = {10,14,0,1,5,11,15,17,14};
  const int ngHBucrateInrbxrmid[Ncrate] = {30,24,20,21,25,31,35,37,34};
  
  const int ngHBphiInrbxrmid_P[NrbxngHB*NrmngHB] = {71,72,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
  const int ngHBphiInrbxrmid_M[NrbxngHB*NrmngHB] = {2,1,72,71,6,5,4,3,10,9,8,7,14,13,12,11,18,17,16,15,22,21,20,19,26,25,24,23,30,29,28,27,34,33,32,31,38,37,36,35,42,41,40,39,46,45,44,43,50,49,48,47,54,53,52,51,58,57,56,55,62,61,60,59,66,65,64,63,70,69,68,67};

  const int ngHBetaInrmfifichid[Nrm_fiber*2]=
  {
    4, 3, 2, 1, 4, 3, 2, 1,//rm_fi is odd, fi_ch=0-7
    2, 1, 4, 3, 2, 1, 4, 3//rm_fi is even, fi_ch=0-7
  };

  const int ngHBdepInrmfifichidRM13[Nrm_fiber*Nfiber_ch]=
  {
    4, 2, 1, 3, 4, 2, 1, 3, 4, 2, 1, 3, 4, 2, 1, 3
  };

  const int ngHBdepInrmfifichidRM24[Nrm_fiber*Nfiber_ch]=
  {
    1, 3, 4, 2, 1, 3, 4, 2, 1, 3, 4, 2, 1, 3, 4, 2
  };
  
  const std::string ngHBtrgjmIntpind[Nrm_fiber*4]=
  {
    "D1", "C1", "B1", "A1", "D3", "C3", "B3", "A3", //RM1/3. fiber 1
    "B4", "A4", "D4", "C4", "B2", "A2", "D2", "C2", //RM1/3. fiber 2
    "B1", "A1", "D1", "C1", "B3", "A3", "D3", "C3", //RM2/4. fiber 1
    "D4", "C4", "B4", "A4", "D2", "C2", "B2", "A2"  //RM2/4. fiber 2
  };

  const std::string ngHBtrguhtrIntpindx[Nrm_fiber*4]=
  {
    "D1", "C1", "B1", "A1", "D3", "C3", "B3", "A3", //RM1/3. fiber 1
    "B4", "A4", "D4", "C4", "B2", "A2", "D2", "C2", //RM1/3. fiber 2
    "D4", "C4", "B4", "A4", "D2", "C2", "B2", "A2", //RM2/4. fiber 1
    "B1", "A1", "D1", "C1", "B3", "A3", "D3", "C3"  //RM2/4. fiber 2
  };
  //Legacy QIE11 calibration constants
  //LMap add QIE11 ID
  struct ngHBQIE11CardMap
  {
    std::string rbx, rm, qie11, qie_id;
  };
  std::vector<ngHBQIE11CardMap> myngHBQIE11CardMap;
  void LoadngHBQIEMap(std::string QIE11CardMapFileName);
  void GetngHBQIEInfoToLMap(
                          std::string rbx, int rm, int qie11,
                          int &qie11_id
                         );
};
