#include <vector>
#include <iostream>

#include "HFMappingObject.h"

class HFMappingAlgorithm : public HFConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<HFFrontEnd> myHFFrontEnd; std::vector<HFBackEnd> myHFBackEnd; std::vector<HFPMTBox> myHFPMTBox; std::vector<HFGeometry> myHFGeometry; std::vector<HFTriggerTower> myHFTriggerTower;
  void ConstructHFLMapObject();
 private:
  void ConstructHFFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructHFBackEnd(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructHFGeometry(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructHFPMTBox();      
  void ConstructHFTriggerTower();  

  const int HFcrateInrbxrmid[Ncrate] = {2,9,12};
  const int HFucrateInrbxrmid[Ncrate] = {22,29,32};
  const int HFetaInrmfifichidType1[Nrm_fiber*Nfiber_ch] = {33,31,29,32,30,34, 33,31,29,32,30,34, 41,37,35,38,36,39, 41,37,35,38,36,39};
  const int HFetaInrmfifichidType2[Nrm_fiber*Nfiber_ch] = {34,32,30,31,29,33, 34,32,30,31,29,33, 40,38,36,37,35,39, 40,38,36,37,35,39};
};
