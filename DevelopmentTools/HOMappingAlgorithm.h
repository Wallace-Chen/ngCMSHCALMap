#include <vector>
#include <iostream>

#include "HOMappingObject.h"

class HOMappingAlgorithm : public HOConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<HOFrontEnd> myHOFrontEnd; std::vector<HOBackEnd> myHOBackEnd; std::vector<HOSiPM> myHOSiPM; std::vector<HOGeometry> myHOGeometry; std::vector<HOTriggerTower> myHOTriggerTower;
  std::vector<HOCalib> myHOCalib;
  void ConstructHOLMapObject(std::string Mode);
 private:
  void ConstructHOFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHOBackEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHOGeometry(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHOSiPM(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHOTriggerTower();
  void ConstructHOCalib(int irbx, int irm, int irmfi, int ifich);

  const int HOphiInrbxrmid[72] = {71,72,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
};
