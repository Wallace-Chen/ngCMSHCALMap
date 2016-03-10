#include <vector>
#include <string>
#include <iostream>

#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "ngHFMappingObject.h"

class ngHFAnalyzer : public ngHFConstant 
{
 public:
  void ngHFNChannelBasicCheck();
  void PlottingngHFFEtoGeo(
                         std::vector<HFFrontEnd> myHFFrontEnd,
                         std::vector<HFGeometry> myHFGeometry
                        );

  void PlottingngHFFEtoBEVME(
                           std::vector<HFFrontEnd> myHFFrontEnd,
                           std::vector<HFBackEnd> myHFBackEnd
                          );
  void PlottingngHFFEtoBEuTCA(
                            std::vector<HFFrontEnd> myHFFrontEnd,
                            std::vector<HFBackEnd> myHFBackEnd
                           );

 private:
  //the target directory for output plots
  std::string dir = "LMapvalidationPlots/";
};
