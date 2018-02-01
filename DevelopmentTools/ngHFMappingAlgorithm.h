#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <utility>

#include <TSQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>

#include "HFMappingObject.h"
#include "ngHFMappingObject.h"

class ngHFMappingAlgorithm : public ngHFConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHFFrontEnd> myngHFFrontEnd; std::vector<ngHFBackEnd> myngHFBackEnd; std::vector<ngHFPMTBox> myngHFPMTBox; std::vector<ngHFGeometry> myngHFGeometry; std::vector<ngHFTriggerTower> myngHFTriggerTower;
  std::vector<ngHFCalib> myngHFCalib;
  void SplitngHFfromOldHF(std::vector<HFFrontEnd> myHFFrontEnd, std::vector<HFBackEnd> myHFBackEnd, std::vector<HFPMTBox> myHFPMTBox, std::vector<HFGeometry> myHFGeometry, std::vector<HFTriggerTower> myHFTriggerTower);
  void ConstructngHFLMapObject(std::string Mode);
 private:
  void ConstructngHFFrontEnd(int sideid, int rbxqie10id, int qie10chid);
  void ConstructngHFPMTBox(int sideid, int rbxqie10id, int qie10chid);
  void ConstructngHFBackEnd(int sideid, int rbxqie10id, int qie10chid);
  void ConstructngHFGeometry(int sideid, int pmtbox, std::string tower, int anode);
  void ConstructngHFTriggerTower(int eta, int phi);
  void ConstructngHFCalib(int sideid, int rbxqie10id, int qie10chid);
  const int ngHFqie10Inrbxqie10id[Nqie10] = {3,4,5,6,10,11,12,13,14};
  //QIE10 calibration constants
  //LMap add QIE10 ID and QIE10 BarCode
  struct ngHFQIE10CardMap
  {
    std::string rbx,qie,barcode,qie_id;
  };
  std::vector<ngHFQIE10CardMap> myngHFQIE10CardMap;
  void LoadngHFQIEMap(std::string QIE10CardMapFileName);
  void GetngHFQIEInfoToLMap(
                            std::string rbx, int qie,
                            int &qie10_id, std::string &qie10_barcode
                           );
};
