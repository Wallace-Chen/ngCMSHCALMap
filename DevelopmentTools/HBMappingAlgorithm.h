#include <vector>
#include <iostream>

#include "HBMappingObject.h"

class HBMappingAlgorithm : public HBConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<HBFrontEnd> myHBFrontEnd; std::vector<HBBackEnd> myHBBackEnd; std::vector<HBHPD> myHBHPD; std::vector<HBGeometry> myHBGeometry; std::vector<HBTriggerTower> myHBTriggerTower;
  void ConstructHBLMapObject();
 private:
  void ConstructHBFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHBBackEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHBGeometry(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHBHPD();
  void ConstructHBTriggerTower();

  const int HBcrateInrbxrmid[Ncrate] = {4,0,1,5,11,15,17,14,10};
  const int HBucrateInrbxrmid[Ncrate] = {24,20,21,25,31,35,37,34,30};
  const int HBetaInrmfifichid[Nrm_fiber*Nfiber_ch] = {16,15,14, 15,13,16, 10,6,2, 8,4,12, 11,7,3, 5,1,9};
};
