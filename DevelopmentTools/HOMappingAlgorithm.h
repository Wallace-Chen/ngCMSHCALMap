#include <vector>
#include <iostream>

#include "HOMappingObject.h"

class HOMappingAlgorithm : public HOConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<HOFrontEnd> myHOFrontEnd; std::vector<HOBackEnd> myHOBackEnd; std::vector<HOSiPM> myHOSiPM; std::vector<HOGeometry> myHOGeometry; std::vector<HOTriggerTower> myHOTriggerTower;
  void ConstructHOLMapObject();
 private:
  void ConstructHOFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHOBackEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHOGeometry(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHOSiPM(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHOTriggerTower();
};
