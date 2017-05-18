#include <vector>
#include <string>
#include <iostream>

#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "HOMappingObject.h"

class HOAnalyzer : public HOConstant
{
 public:
  void HONChannelBasicCheck();
  void PlottingHOFEtoGeo(
                         std::vector<HOFrontEnd> myHOFrontEnd,
                         std::vector<HOGeometry> myHOGeometry
                        );

  void PlottingHOFEtoBEVME(
                           std::vector<HOFrontEnd> myHOFrontEnd,
                           std::vector<HOBackEnd> myHOBackEnd
                          );
 private:
  const char *HO0RBXlabel[NrbxHO0*NrmHO0] = {"HO001RM1","HO001RM2","HO001RM3",
                                             "HO002RM2","HO002RM3","HO002RM4",//
                                             "HO003RM2","HO003RM3","HO003RM4",//
                                             "HO004RM1","HO004RM2","HO004RM3",
                                             "HO005RM1","HO005RM2","HO005RM3",
                                             "HO006RM2","HO006RM3","HO006RM4",//
                                             "HO007RM2","HO007RM3","HO007RM4",//
                                             "HO008RM1","HO008RM2","HO008RM3",
                                             "HO009RM1","HO009RM2","HO009RM3",
                                             "HO010RM2","HO010RM3","HO010RM4",//
                                             "HO011RM2","HO011RM3","HO011RM4",//
                                             "HO012RM1","HO012RM2","HO012RM3"};

  const char *HO1PRBXlabel[NrbxHO12*NrmHO12/4] = {"HO1P02RM1","HO1P02RM2","HO1P02RM3","HO1P02RM4",
                                                  "HO1P04RM1","HO1P04RM2","HO1P04RM3","HO1P04RM4",
                                                  "HO1P06RM1","HO1P06RM3","HO1P06RM3","HO1P06RM4",
                                                  "HO1P08RM1","HO1P08RM2","HO1P08RM3","HO1P08RM4",
                                                  "HO1P10RM1","HO1P10RM2","HO1P10RM3","HO1P10RM4",
                                                  "HO1P12RM1","HO1P12RM2","HO1P12RM3","HO1P12RM4"};
  const char *HO2PRBXlabel[NrbxHO12*NrmHO12/4] = {"HO2P02RM1","HO2P02RM2","HO2P02RM3","HO2P02RM4",
                                                  "HO2P04RM1","HO2P04RM2","HO2P04RM3","HO2P04RM4",
                                                  "HO2P06RM1","HO2P06RM3","HO2P06RM3","HO2P06RM4",
                                                  "HO2P08RM1","HO2P08RM2","HO2P08RM3","HO2P08RM4",
                                                  "HO2P10RM1","HO2P10RM2","HO2P10RM3","HO2P10RM4",
                                                  "HO2P12RM1","HO2P12RM2","HO2P12RM3","HO2P12RM4"};
  const char *HO1MRBXlabel[NrbxHO12*NrmHO12/4] = {"HO1M02RM1","HO1M02RM2","HO1M02RM3","HO1M02RM4",
                                                  "HO1M04RM1","HO1M04RM2","HO1M04RM3","HO1M04RM4",
                                                  "HO1M06RM1","HO1M06RM3","HO1M06RM3","HO1M06RM4",
                                                  "HO1M08RM1","HO1M08RM2","HO1M08RM3","HO1M08RM4",
                                                  "HO1M10RM1","HO1M10RM2","HO1M10RM3","HO1M10RM4",
                                                  "HO1M12RM1","HO1M12RM2","HO1M12RM3","HO1M12RM4"};
  const char *HO2MRBXlabel[NrbxHO12*NrmHO12/4] = {"HO2M02RM1","HO2M02RM2","HO2M02RM3","HO2M02RM4",
                                                  "HO2M04RM1","HO2M04RM2","HO2M04RM3","HO2M04RM4",
                                                  "HO2M06RM1","HO2M06RM3","HO2M06RM3","HO2M06RM4",
                                                  "HO2M08RM1","HO2M08RM2","HO2M08RM3","HO2M08RM4",
                                                  "HO2M10RM1","HO2M10RM2","HO2M10RM3","HO2M10RM4",
                                                  "HO2M12RM1","HO2M12RM2","HO2M12RM3","HO2M12RM4"};
  //HO0 has 2 HOX channels for all rbx rm in different rm fibers
  const char *HO0RMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI2FICH0"     ,"RMFI2FICH1"     ,"RMFI2FICH2",
                                                      "RMFI3FICH0"     ,"RMFI3FICH1"     ,"RMFI3FICH2",
                                                      "RMFI4FICH0"     ,"RMFI4FICH1"     ,"RMFI4FICH2(HOX)",
                                                      "RMFI5FICH0"     ,"RMFI5FICH1"     ,"RMFI5FICH2",
                                                      "RMFI6FICH0"     ,"RMFI6FICH1(HOX)","RMFI6FICH2",
                                                      "RMFI7FICH0"     ,"RMFI7FICH1"     ,"RMFI7FICH2"};
  //no HOX channels in HO1
  const char *HO1RMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI2FICH0"     ,"RMFI2FICH1"     ,"RMFI2FICH2",
                                                      "RMFI3FICH0"     ,"RMFI3FICH1"     ,"RMFI3FICH2",
                                                      "RMFI4FICH0"     ,"RMFI4FICH1"     ,"RMFI4FICH2",
                                                      "RMFI5FICH0"     ,"RMFI5FICH1"     ,"RMFI5FICH2",
                                                      "RMFI6FICH0"     ,"RMFI6FICH1"     ,"RMFI6FICH2",
                                                      "RMFI7FICH0"     ,"RMFI7FICH1"     ,"RMFI7FICH2"};
  //HO2 has 2 HOX channels for all rbx rm in same rm fiber
  const char *HO2RMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI2FICH0"     ,"RMFI2FICH1"     ,"RMFI2FICH2",
                                                      "RMFI3FICH0"     ,"RMFI3FICH1"     ,"RMFI3FICH2",
                                                      "RMFI4FICH0"     ,"RMFI4FICH1"     ,"RMFI4FICH2",
                                                      "RMFI5FICH0"     ,"RMFI5FICH1"     ,"RMFI5FICH2",
                                                      "RMFI6FICH0(HOX)","RMFI6FICH1(HOX)","RMFI6FICH2(HOX)",
                                                      "RMFI7FICH0"     ,"RMFI7FICH1"     ,"RMFI7FICH2"};
  //the target directory for output plots
  std::string dir = "LMapValidationPlots/";
};
