#include <vector>
#include <iostream>

#include "ngHOMappingObject.h"

class ngHOMappingAlgorithm : public ngHOConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHOFrontEnd> myngHOFrontEnd; std::vector<ngHOBackEnd> myngHOBackEnd; std::vector<ngHOSiPM> myngHOSiPM; std::vector<ngHOGeometry> myngHOGeometry; std::vector<ngHOTriggerTower> myngHOTriggerTower;
  std::vector<ngHOCalib> myngHOCalib;
  void ConstructngHOLMapObject(std::string Mode);
 private:
  void ConstructngHOFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHOBackEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHOGeometry(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHOSiPM(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHOTriggerTower();
  void ConstructngHOCalib(int irbx, int irm, int irmfi, int ifich);

  const int ngHOphiInrbxrmid[72] = {71,72,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
};
