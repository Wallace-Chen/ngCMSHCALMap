#include <vector>
#include <string>
#include <iostream>

#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "HEMappingObject.h"

class HEAnalyzer : public HEConstant
{
 public:
  void HENChannelBasicCheck();
  void PlottingHEFEtoGeo(
                         std::vector<HEFrontEnd> myHEFrontEnd,
                         std::vector<HEGeometry> myHEGeometry
                        );
  void PlottingHEFEtoBEVME(
                           std::vector<HEFrontEnd> myHEFrontEnd,
                           std::vector<HEBackEnd> myHEBackEnd
                          );
  void PlottingHEFEtoBEuTCA(
                            std::vector<HEFrontEnd> myHEFrontEnd,
                            std::vector<HEBackEnd> myHEBackEnd
                           );
 private:
  const char *HEMRBXlabel[NrbxHE*NrmHE] = {"HEM01RM1","HEM01RM2","HEM01RM3","HEM01RM4",
                                           "HEM02RM1","HEM02RM2","HEM02RM3","HEM02RM4",
                                           "HEM03RM1","HEM03RM2","HEM03RM3","HEM03RM4",
                                           "HEM04RM1","HEM04RM2","HEM04RM3","HEM04RM4",
                                           "HEM05RM1","HEM05RM2","HEM05RM3","HEM05RM4",
                                           "HEM06RM1","HEM06RM2","HEM06RM3","HEM06RM4",
                                           "HEM07RM1","HEM07RM2","HEM07RM3","HEM07RM4",
                                           "HEM08RM1","HEM08RM2","HEM08RM3","HEM08RM4",
                                           "HEM09RM1","HEM09RM2","HEM09RM3","HEM09RM4",
                                           "HEM10RM1","HEM10RM2","HEM10RM3","HEM10RM4",
                                           "HEM11RM1","HEM11RM2","HEM11RM3","HEM11RM4",
                                           "HEM12RM1","HEM12RM2","HEM12RM3","HEM12RM4",
                                           "HEM13RM1","HEM13RM2","HEM13RM3","HEM13RM4",
                                           "HEM14RM1","HEM14RM2","HEM14RM3","HEM14RM4",
                                           "HEM15RM1","HEM15RM2","HEM15RM3","HEM15RM4",
                                           "HEM16RM1","HEM16RM2","HEM16RM3","HEM16RM4",
                                           "HEM17RM1","HEM17RM2","HEM17RM3","HEM17RM4",
                                           "HEM18RM1","HEM18RM2","HEM18RM3","HEM18RM4"};

  const char *HEPRBXlabel[NrbxHE*NrmHE] = {"HEP01RM1","HEP01RM2","HEP01RM3","HEP01RM4",
                                           "HEP02RM1","HEP02RM2","HEP02RM3","HEP02RM4",
                                           "HEP03RM1","HEP03RM2","HEP03RM3","HEP03RM4",   
                                           "HEP04RM1","HEP04RM2","HEP04RM3","HEP04RM4",   
                                           "HEP05RM1","HEP05RM2","HEP05RM3","HEP05RM4",   
                                           "HEP06RM1","HEP06RM2","HEP06RM3","HEP06RM4",   
                                           "HEP07RM1","HEP07RM2","HEP07RM3","HEP07RM4",
                                           "HEP08RM1","HEP08RM2","HEP08RM3","HEP08RM4",
                                           "HEP09RM1","HEP09RM2","HEP09RM3","HEP09RM4",
                                           "HEP10RM1","HEP10RM2","HEP10RM3","HEP10RM4",
                                           "HEP11RM1","HEP11RM2","HEP11RM3","HEP11RM4",
                                           "HEP12RM1","HEP12RM2","HEP12RM3","HEP12RM4",
                                           "HEP13RM1","HEP13RM2","HEP13RM3","HEP13RM4",
                                           "HEP14RM1","HEP14RM2","HEP14RM3","HEP14RM4",
                                           "HEP15RM1","HEP15RM2","HEP15RM3","HEP15RM4",
                                           "HEP16RM1","HEP16RM2","HEP16RM3","HEP16RM4",
                                           "HEP17RM1","HEP17RM2","HEP17RM3","HEP17RM4",
                                           "HEP18RM1","HEP18RM2","HEP18RM3","HEP18RM4"};

  const char *HERMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI2FICH0"     ,"RMFI2FICH1"     ,"RMFI2FICH2",
                                                     "RMFI3FICH0"     ,"RMFI3FICH1"     ,"RMFI3FICH2",
                                                     "RMFI4FICH0"     ,"RMFI4FICH1"     ,"RMFI4FICH2",
                                                     "RMFI5FICH0"     ,"RMFI5FICH1"     ,"RMFI5FICH2",
                                                     "RMFI6FICH0"     ,"RMFI6FICH1"     ,"RMFI6FICH2",
                                                     "RMFI7FICH0"     ,"RMFI7FICH1"     ,"RMFI7FICH2"};
  //the target directory for output plots
  std::string dir = "LMapValidationPlots/";
};
