#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "HBMappingObject.h"
#include "HEMappingObject.h"
#include "ngHBMappingObject.h"
#include "ngHEMappingObject.h"
#include "HFMappingObject.h"
#include "ngHFMappingObject.h"
#include "HOMappingObject.h"
#include "ngHOMappingObject.h"

class HCALLMapLoader
{
 public:
  //HBHEHF Generation G
  int GetHBHEHFromLMap(
                       std::string LMapFileName,
                       std::vector<HBFrontEnd> &myHBFrontEnd, std::vector<HBBackEnd> &myHBBackEnd, std::vector<HBHPD> &myHBHPD, std::vector<HBGeometry> &myHBGeometry, std::vector<HBTriggerTower> &myHBTriggerTower,
                       std::vector<HEFrontEnd> &myHEFrontEnd, std::vector<HEBackEnd> &myHEBackEnd, std::vector<HEHPD> &myHEHPD, std::vector<HEGeometry> &myHEGeometry, std::vector<HETriggerTower> &myHETriggerTower,
                       std::vector<HFFrontEnd> &myHFFrontEnd, std::vector<HFBackEnd> &myHFBackEnd, std::vector<HFPMTBox> &myHFPMTBox, std::vector<HFGeometry> &myHFGeometry, std::vector<HFTriggerTower> &myHFTriggerTower
                      );
  //HO Generation G
  int GetHOFromLMap(
                    std::string LMapFileName, 
                    std::vector<HOFrontEnd> &myHOFrontEnd, std::vector<HOBackEnd> &myHOBackEnd, std::vector<HOSiPM> &myHOSiPM, std::vector<HOGeometry> &myHOGeometry, std::vector<HOTriggerTower> &myHOTriggerTower
                   );
  //ngHE
  int GetngHEromLMap(
                     std::string LMapFileName,
                     std::vector<ngHEFrontEnd> &myngHEFrontEnd, std::vector<ngHEBackEnd> &myngHEBackEnd, std::vector<ngHESiPM> &myngHESiPM, std::vector<ngHEGeometry> &myngHEGeometry, std::vector<ngHETriggerTower> &myngHETriggerTower
                    );
  //ngHF
  int GetngHFromLMap(
                     std::string LMapFileName,
                     std::vector<ngHFFrontEnd> &myngHFFrontEnd, std::vector<ngHFBackEnd> &myngHFBackEnd, std::vector<ngHFPMTBox> &myngHFPMTBox, std::vector<ngHFGeometry> &myngHFGeometry, std::vector<ngHFTriggerTower> &myngHFTriggerTower
                    );
  int GetngHOFromLMap(
                    std::string LMapFileName, 
                    std::vector<ngHOFrontEnd> &myngHOFrontEnd, std::vector<ngHOBackEnd> &myngHOBackEnd, std::vector<ngHOSiPM> &myngHOSiPM, std::vector<ngHOGeometry> &myngHOGeometry, std::vector<ngHOTriggerTower> &myngHOTriggerTower,
		    std::vector<ngHOCalib> &myngHOCalib
                   );
};
