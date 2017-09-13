#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm> // std::copy

#include "HBMappingObject.h"
#include "HEMappingObject.h"
#include "ngHBMappingObject.h"
#include "ngHEMappingObject.h"
#include "HFMappingObject.h"
#include "ngHFMappingObject.h"
#include "HOMappingObject.h"

class HCALLMapChecker
{
 public:
  //HB
  bool checkHBLMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower);
  //ngHB
  bool checkngHBLMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower);
  //HE?
  //ngHE
  bool checkngHELMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower);
  //HF
  //ngHF
  bool checkngHFLMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
  //HO
 private:
};
