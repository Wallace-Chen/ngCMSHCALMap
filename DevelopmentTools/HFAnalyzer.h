#include <vector>
#include <string>
#include <iostream>

#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "HFMappingObject.h"

class HFAnalyzer : public HFConstant 
{
 public:
  void HFNChannelBasicCheck();
  void PlottingHFFEtoGeo(
                         std::vector<HFFrontEnd> myHFFrontEnd,
                         std::vector<HFGeometry> myHFGeometry
                        );

  void PlottingHFFEtoBEVME(
                           std::vector<HFFrontEnd> myHFFrontEnd,
                           std::vector<HFBackEnd> myHFBackEnd
                          );
  void PlottingHFFEtoBEuTCA(
                            std::vector<HFFrontEnd> myHFFrontEnd,
                            std::vector<HFBackEnd> myHFBackEnd
                           );

 private:
  const char *HFMRBXlabel[NrbxHF*NrmHF] = {"HFM01RM1","HFM01RM2","HFM01RM3",
                                           "HFM02RM1","HFM02RM2","HFM02RM3",
                                           "HFM03RM1","HFM03RM2","HFM03RM3",
                                           "HFM04RM1","HFM04RM2","HFM04RM3",
                                           "HFM05RM1","HFM05RM2","HFM05RM3",
                                           "HFM06RM1","HFM06RM2","HFM06RM3",
                                           "HFM07RM1","HFM07RM2","HFM07RM3",
                                           "HFM08RM1","HFM08RM2","HFM08RM3",
                                           "HFM09RM1","HFM09RM2","HFM09RM3",
                                           "HFM10RM1","HFM10RM2","HFM10RM3",
                                           "HFM11RM1","HFM11RM2","HFM11RM3",
                                           "HFM12RM1","HFM12RM2","HFM12RM3"};

  const char *HFPRBXlabel[NrbxHF*NrmHF] = {"HFP01RM1","HFP01RM2","HFP01RM3",
                                           "HFP02RM1","HFP02RM2","HFP02RM3",
                                           "HFP03RM1","HFP03RM2","HFP03RM3",
                                           "HFP04RM1","HFP04RM2","HFP04RM3",
                                           "HFP05RM1","HFP05RM2","HFP05RM3",
                                           "HFP06RM1","HFP06RM2","HFP06RM3",
                                           "HFP07RM1","HFP07RM2","HFP07RM3",
                                           "HFP08RM1","HFP08RM2","HFP08RM3",
                                           "HFP09RM1","HFP09RM2","HFP09RM3",
                                           "HFP10RM1","HFP10RM2","HFP10RM3",
                                           "HFP11RM1","HFP11RM2","HFP11RM3",
                                           "HFP12RM1","HFP12RM2","HFP12RM3"};

  const char *HFRMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI1FICH0"     ,"RMFI1FICH1"     ,"RMFI1FICH2",
                                                     "RMFI2FICH0"     ,"RMFI2FICH1"     ,"RMFI2FICH2",
                                                     "RMFI3FICH0"     ,"RMFI3FICH1"     ,"RMFI3FICH2",
                                                     "RMFI4FICH0"     ,"RMFI4FICH1"     ,"RMFI4FICH2",
                                                     "RMFI5FICH0"     ,"RMFI5FICH1"     ,"RMFI5FICH2",
                                                     "RMFI6FICH0"     ,"RMFI6FICH1"     ,"RMFI6FICH2",
                                                     "RMFI7FICH0"     ,"RMFI7FICH1"     ,"RMFI7FICH2",
                                                     "RMFI8FICH0"     ,"RMFI8FICH1"     ,"RMFI8FICH2"};
  //the target directory for output plots
  std::string dir = "LMapvalidationPlots/";
};
