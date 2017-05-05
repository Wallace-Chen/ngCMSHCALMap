#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "HBHEMappingObject.h"
#include "ngHBMappingObject.h"
#include "ngHEMappingObject.h"
#include "HFMappingObject.h"
#include "ngHFMappingObject.h"
#include "HOMappingObject.h"

class HCALLMapLoader
{
 public:
  int GetHBHEHFromLMap(
                       std::string LMapFileName,
                       std::vector<HBFrontEnd> &myHBFrontEnd, std::vector<HBBackEnd> &myHBBackEnd, std::vector<HBPMTBox> &myHBPMTBox, std::vector<HBGeometry> &myHBGeometry, std::vector<HBTriggerTower> &myHBTriggerTower,
                       std::vector<HEFrontEnd> &myHEFrontEnd, std::vector<HEBackEnd> &myHEBackEnd, std::vector<HEPMTBox> &myHEPMTBox, std::vector<HEGeometry> &myHEGeometry, std::vector<HETriggerTower> &myHETriggerTower,
                       std::vector<HFFrontEnd> &myHFFrontEnd, std::vector<HFBackEnd> &myHFBackEnd, std::vector<HFPMTBox> &myHFPMTBox, std::vector<HFGeometry> &myHFGeometry, std::vector<HFTriggerTower> &myHFTriggerTower
                      );
  
  int GetHOFromLMap(
                    std::string LMapFileName, 
                    std::vector<HOFrontEnd> &myHOFrontEnd, std::vector<HOBackEnd> &myHOBackEnd, std::vector<HOPMTBox> &myHOPMTBox, std::vector<HOGeometry> &myHOGeometry, std::vector<HOTriggerTower> &myHOTriggerTower
                   );

  int GetngHFromLMap(
                     std::string LMapFileName,
                     std::vector<ngHFFrontEnd> &myngHFFrontEnd, std::vector<ngHFBackEnd> &myngHFBackEnd, std::vector<ngHFPMTBox> &myngHFPMTBox, std::vector<ngHFGeometry> &myngHFGeometry, std::vector<ngHFTriggerTower> &myngHFTriggerTower
                    );

  int GetngHEromLMap(
                     std::string LMapFileName,
                     std::vector<ngHEFrontEnd> &myngHEFrontEnd, std::vector<ngHEBackEnd> &myngHEBackEnd, std::vector<ngHEPMTBox> &myngHEPMTBox, std::vector<ngHEGeometry> &myngHEGeometry, std::vector<ngHETriggerTower> &myngHETriggerTower
                    );
};
