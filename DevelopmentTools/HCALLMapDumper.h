#include <vector>
#include <iostream>
#include <iomanip>

#include "bld/sqlite3.h"
//#include <TSQLServer.h>
//#include <TSQLiteServer.h>

#include "HBHEMappingObject.h"
#include "ngHBMappingObject.h"
#include "ngHEMappingObject.h"
#include "HFMappingObject.h"
#include "ngHFMappingObject.h"
#include "HOMappingObject.h"

class HCALLMapDumper
{
 public:
  void printHFLMapObject(std::vector<HFFrontEnd> myHFFrontEnd, std::vector<HFBackEnd> myHFBackEnd, std::vector<HFPMTBox> myHFPMTBox, std::vector<HFGeometry> myHFGeometry, std::vector<HFTriggerTower> myHFTriggerTower);
  void printngHFLMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
  void printngHFEMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
  void printngHFFrontEndMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
  void printngHELMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHEPMTBox> myngHEPMTBox, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower);
  void printngHEEMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHEPMTBox> myngHEPMTBox, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower);
  void printngHEFrontEndMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHEPMTBox> myngHEPMTBox, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower);
  void printngHBLMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBPMTBox> myngHBPMTBox, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower);
  void printngHBEMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBPMTBox> myngHBPMTBox, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower);
  void printngHBFrontEndMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBPMTBox> myngHBPMTBox, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower);

  void makedbngHFLMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
};
