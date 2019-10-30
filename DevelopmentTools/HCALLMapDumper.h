#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

#include "../../bld/include/sqlite3.h"
//#include <TSQLServer.h>
//#include <TSQLiteServer.h>

#include "HBMappingObject.h"
#include "HEMappingObject.h"
#include "ngHBMappingObject.h"
#include "ngHEMappingObject.h"
#include "HFMappingObject.h"
#include "ngHFMappingObject.h"
#include "HOMappingObject.h"
#include "ngHOMappingObject.h"

class HCALLMapDumper
{
 public:
  //HB,txt
  void printHBLMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower);
  void printHBEMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower);
  void printHBFrontEndMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower);
  void printHBCalibLMapObject(std::vector<HBCalib> myHBCalib);
  void printHBCalibEMapObject(std::vector<HBCalib> myHBCalib);
  //ngHB,txt
  void printngHBLMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower, std::vector<ngHBTriggerTowerFiber> myngHBTriggerTowerFiber);
  void printngHBEMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower);
  void printngHBFrontEndMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower);
  void printngHBCalibLMapObject(std::vector<ngHBCalib> myngHBCalib, int header = 1);
  void printngHBCalibEMapObject(std::vector<ngHBCalib> myngHBCalib);
  //ngHE,txt
  void printngHELMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower);
  void printngHEEMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower);
  void printngHEFrontEndMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower);
  void printngHECalibLMapObject(std::vector<ngHECalib> myngHECalib, int header = 1);
  void printngHECalibEMapObject(std::vector<ngHECalib> myngHECalib);
  //HF(LMap only),txt
  void printHFLMapObject(std::vector<HFFrontEnd> myHFFrontEnd, std::vector<HFBackEnd> myHFBackEnd, std::vector<HFPMTBox> myHFPMTBox, std::vector<HFGeometry> myHFGeometry, std::vector<HFTriggerTower> myHFTriggerTower);
  //ngHF,txt
  void printngHFLMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
  void printngHFEMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
  void printngHFFrontEndMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
  void printngHFCalibLMapObject(std::vector<ngHFCalib> myngHFCalib);
  void printngHFCalibEMapObject(std::vector<ngHFCalib> myngHFCalib);
  //HO,txt
  void printHOLMapObject(std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower);
  void printHOEMapObject(std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower);
  void printHOFrontEndMapObject(std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower);
  void printHOCalibLMapObject(std::vector<HOCalib> myHOCalib);
  //ngHO
  void printngHOLMapObject(std::vector<ngHOFrontEnd> myngHOFrontEnd, std::vector<ngHOBackEnd> myngHOBackEnd, std::vector<ngHOSiPM> myngHOSiPM, std::vector<ngHOGeometry> myngHOGeometry, std::vector<ngHOTriggerTower> myngHOTriggerTower);
  void printngHOEMapObject(std::vector<ngHOFrontEnd> myngHOFrontEnd, std::vector<ngHOBackEnd> myngHOBackEnd, std::vector<ngHOSiPM> myngHOSiPM, std::vector<ngHOGeometry> myngHOGeometry, std::vector<ngHOTriggerTower> myngHOTriggerTower);
  void printngHOCalibLMapObject(std::vector<ngHOCalib> myngHOCalib);
  void printngHOCalibEMapObject(std::vector<ngHOCalib> myngHOCalib);

  // UMap
  void printngHBHEUMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector <ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower, std::vector<ngHBTriggerTowerFiber> myngHBTriggerTowerFiber,
                             std::vector<ngHBCalib> myngHBCalib,
                             std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector <ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower,
                             std::vector<ngHECalib> myngHECalib
  );
  void printngHBHEUMapCalibObject(std::vector<ngHBCalib> myngHBCalib, std::vector<ngHECalib> myngHECalib);
  void printngHBHEPedLMapObject(std::vector<ngHBCalib> myngHBCalib, std::vector<ngHECalib> myngHECalib);
  void printHOUMapObject(std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower, std::vector<HOCalib> myHOCalib);
  void printngHOUMapObject(std::vector<ngHOFrontEnd> myngHOFrontEnd, std::vector<ngHOBackEnd> myngHOBackEnd, std::vector<ngHOSiPM> myngHOSiPM, std::vector<ngHOGeometry> myngHOGeometry, std::vector<ngHOTriggerTower> myngHOTriggerTower, std::vector<ngHOCalib> myngHOCalib);

  //HB,db
  void makedbHBLMapObject(std::string HCALLMapDbStr, std::string HBTableStr,
                          std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower);
  //HBCalib,db
  void makedbHBCalibLMapObject(std::string HCALLMapDbStr, std::string HBCalibTableStr, std::vector<HBCalib> myHBCalib);
  //ngHB,db
  void makedbngHBLMapObject(std::string HCALLMapDbStr, std::string ngHBTableStr,
                            std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower);
  //ngHBCalib,db
  void makedbngHBCalibLMapObject(std::string HCALLMapDbStr, std::string ngHBCalibTableStr, std::vector<ngHBCalib> myngHBCalib);
  //ngHE,db
  void makedbngHELMapObject(std::string HCALLMapDbStr, std::string ngHETableStr,
                            std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower);
  //ngHECalib,db
  void makedbngHECalibLMapObject(std::string HCALLMapDbStr, std::string ngHECalibTableStr, std::vector<ngHECalib> myngHECalib);
  //ngHBHE, db
  void makedbngHBHEUMapObject(std::string HCALLMapDbStr, std::string ngHFTableStr,
                              std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector <ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower, std::vector<ngHBTriggerTowerFiber> myngHBTriggerTowerFiber,
                              std::vector<ngHBCalib> myngHBCalib,
                              std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector <ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower,
                              std::vector<ngHECalib> myngHECalib
  );
  //ngHF,db
  void makedbngHFLMapObject(std::string HCALLMapDbStr, std::string ngHFTableStr,
                            std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower);
  void makedbngHFCalibLMapObject(std::string HCALLMapDbStr, std::string ngHFCalibTableStr, std::vector<ngHFCalib> myngHFCalib);
  //HO,db
  void makedbHOLMapObject(std::string HCALLMapDbStr, std::string HOTableStr,
                          std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower);
  //HOCalib.db, added by Yuan
  void makedbHOCalibLMapObject(std::string HCALLMapDbStr, std::string HOCalibTableStr, std::vector<HOCalib> myHOCalib);
  void makedbHOUMapObject(std::string HCALLMapDbStr, std::string HOCalibTableStr, 
                          std::vector<HOFrontEnd> myHOFrontEnd, std::vector<HOBackEnd> myHOBackEnd, std::vector<HOSiPM> myHOSiPM, std::vector<HOGeometry> myHOGeometry, std::vector<HOTriggerTower> myHOTriggerTower, std::vector<HOCalib> myHOCalib);
  //ngHO,db
  void makedbngHOLMapObject(std::string HCALLMapDbStr, std::string ngHOTableStr,
                          std::vector<ngHOFrontEnd> myngHOFrontEnd, std::vector<ngHOBackEnd> myngHOBackEnd, std::vector<ngHOSiPM> myngHOSiPM, std::vector<ngHOGeometry> myngHOGeometry, std::vector<ngHOTriggerTower> myngHOTriggerTower);
  //ngHOCalib.db
  void makedbngHOCalibLMapObject(std::string HCALLMapDbStr, std::string ngHOCalibTableStr, std::vector<ngHOCalib> myngHOCalib);
  void makedbngHOUMapObject(std::string HCALLMapDbStr, std::string ngHOCalibTableStr, 
                          std::vector<ngHOFrontEnd> myngHOFrontEnd, std::vector<ngHOBackEnd> myngHOBackEnd, std::vector<ngHOSiPM> myngHOSiPM, std::vector<ngHOGeometry> myngHOGeometry, std::vector<ngHOTriggerTower> myngHOTriggerTower, std::vector<ngHOCalib> myngHOCalib);
 private:
  bool ifTableExistInDB(sqlite3 *db, std::string TableName);//note: please use this function after sqlite3_open() and before sqlite3_close()!!
};
