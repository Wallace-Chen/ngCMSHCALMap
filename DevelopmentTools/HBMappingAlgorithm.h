#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <utility>

#include "HBMappingObject.h"

class HBMappingAlgorithm : public HBConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<HBFrontEnd> myHBFrontEnd; std::vector<HBBackEnd> myHBBackEnd; std::vector<HBHPD> myHBHPD; std::vector<HBGeometry> myHBGeometry; std::vector<HBTriggerTower> myHBTriggerTower;
  std::vector<HBCalib> myHBCalib;
  void ConstructHBLMapObject(std::string Mode);
 private:
  void ConstructHBFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHBBackEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHBGeometry(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHBHPD(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHBTriggerTower(int eta, int phi);
  void ConstructHBCalib(int sideid, int rbxrmid, int rmfifichid);

  const int HBcrateInrbxrmid[Ncrate] = {10,14,0,1,5,11,15,17,14};
  const int HBucrateInrbxrmid[Ncrate] = {30,24,20,21,25,31,35,37,34};
  
  const int HBphiInrbxrmid_P[NrbxHB*NrmHB] = {71,72,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
  const int HBphiInrbxrmid_M[NrbxHB*NrmHB] = {2,1,72,71,6,5,4,3,10,9,8,7,14,13,12,11,18,17,16,15,22,21,20,19,26,25,24,23,30,29,28,27,34,33,32,31,38,37,36,35,42,41,40,39,46,45,44,43,50,49,48,47,54,53,52,51,58,57,56,55,62,61,60,59,66,65,64,63,70,69,68,67};

  const int HBetaInrmfifichid[Nrm_fiber*Nfiber_ch]=
  {
    16, 15, 14,//RM fiber 2
    15, 13, 16,//RM fiber 3
    10, 6,  2, //RM fiber 4
    8,  4,  12,//RM fiber 5
    11, 7,  3, //RM fiber 6
    5,  1,  9, //RM fiber 7
  };

  const int HBdepInrmfifichid[Nrm_fiber*Nfiber_ch]=
  {
    2, 2, 1, //RM fiber 2
    1, 1, 1, //RM fiber 3
    1, 1, 1, //RM fiber 4
    1, 1, 1, //RM fiber 5
    1, 1, 1, //RM fiber 6
    1, 1, 1, //RM fiber 7
  };

  //Legacy QIE8 calibration constants
  //LMap add QIE8 ID
  struct HBQIE8CardMap
  {
    std::string rbx, rm, qie8, qie_id;
  };
  std::vector<HBQIE8CardMap> myHBQIE8CardMap;
  void LoadHBQIEMap(std::string QIE8CardMapFileName);
  void GetHBQIEInfoToLMap(
                          std::string rbx, int rm, int qie8,
                          int &qie8_id
                         );
};
