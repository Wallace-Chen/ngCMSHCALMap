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

namespace HFAnalyzer
{
  // channels in HF
  const int NchHF_all = 1728;
  //Front End variables
  //rbx in HF, 18 for each side
  const int NrbxHF = 18;
  //4 rm in all HF rbx, label from 1 to 4
  const int NrmHF = 4;
  //rm fiber 2,3,4,5,6,7, in total 6 fibers per rm
  const int Nrm_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  const int Nfiber_ch = 3;

  const int Nqie = 3;
  const int Nqie_ch = 6;

  //Back End variables
  //3 crate in HF: 2,9,12
  const int Ncrate = 3;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18
  const int Nhtr = 12;
  //2 fpga flavors top and bottom
  const int Nfpga = 2;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8
  const int Nhtr_fiber = 8;

  //Geometry variables in HF: eta from 29,to 40,41, phi is 1,3,...71 for most eta while dphi == 4 for eta 40,41;
  const int NHFside = 2;
  //const int NHFeta = 15;
  const int NHFphi = 72;
  const int NHFdepth = 2;

  const char *HFMRBXlabel[NrbxHF*NrmHF] = {"HFM01RM1","HFM01RM2","HFM01RM3","HFM01RM4",
                                           "HFM02RM1","HFM02RM2","HFM02RM3","HFM02RM4",
                                           "HFM03RM1","HFM03RM2","HFM03RM3","HFM03RM4",
                                           "HFM04RM1","HFM04RM2","HFM04RM3","HFM04RM4",
                                           "HFM05RM1","HFM05RM2","HFM05RM3","HFM05RM4",
                                           "HFM06RM1","HFM06RM2","HFM06RM3","HFM06RM4",
                                           "HFM07RM1","HFM07RM2","HFM07RM3","HFM07RM4",
                                           "HFM08RM1","HFM08RM2","HFM08RM3","HFM08RM4",
                                           "HFM09RM1","HFM09RM2","HFM09RM3","HFM09RM4",
                                           "HFM10RM1","HFM10RM2","HFM10RM3","HFM10RM4",
                                           "HFM11RM1","HFM11RM2","HFM11RM3","HFM11RM4",
                                           "HFM12RM1","HFM12RM2","HFM12RM3","HFM12RM4",
                                           "HFM13RM1","HFM13RM2","HFM13RM3","HFM13RM4",
                                           "HFM14RM1","HFM14RM2","HFM14RM3","HFM14RM4",
                                           "HFM15RM1","HFM15RM2","HFM15RM3","HFM15RM4",
                                           "HFM16RM1","HFM16RM2","HFM16RM3","HFM16RM4",
                                           "HFM17RM1","HFM17RM2","HFM17RM3","HFM17RM4",
                                           "HFM18RM1","HFM18RM2","HFM18RM3","HFM18RM4"};

  const char *HFPRBXlabel[NrbxHF*NrmHF] = {"HFP01RM1","HFP01RM2","HFP01RM3","HFP01RM4",
                                           "HFP02RM1","HFP02RM2","HFP02RM3","HFP02RM4",
                                           "HFP03RM1","HFP03RM2","HFP03RM3","HFP03RM4",
                                           "HFP04RM1","HFP04RM2","HFP04RM3","HFP04RM4",
                                           "HFP05RM1","HFP05RM2","HFP05RM3","HFP05RM4",
                                           "HFP06RM1","HFP06RM2","HFP06RM3","HFP06RM4",
                                           "HFP07RM1","HFP07RM2","HFP07RM3","HFP07RM4",
                                           "HFP08RM1","HFP08RM2","HFP08RM3","HFP08RM4",
                                           "HFP09RM1","HFP09RM2","HFP09RM3","HFP09RM4",
                                           "HFP10RM1","HFP10RM2","HFP10RM3","HFP10RM4",
                                           "HFP11RM1","HFP11RM2","HFP11RM3","HFP11RM4",
                                           "HFP12RM1","HFP12RM2","HFP12RM3","HFP12RM4",
                                           "HFP13RM1","HFP13RM2","HFP13RM3","HFP13RM4",
                                           "HFP14RM1","HFP14RM2","HFP14RM3","HFP14RM4",
                                           "HFP15RM1","HFP15RM2","HFP15RM3","HFP15RM4",
                                           "HFP16RM1","HFP16RM2","HFP16RM3","HFP16RM4",
                                           "HFP17RM1","HFP17RM2","HFP17RM3","HFP17RM4",
                                           "HFP18RM1","HFP18RM2","HFP18RM3","HFP18RM4"};

  const char *HFRMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI2FICH0"     ,"RMFI2FICH1"     ,"RMFI2FICH2",
                                                     "RMFI3FICH0"     ,"RMFI3FICH1"     ,"RMFI3FICH2",
                                                     "RMFI4FICH0"     ,"RMFI4FICH1"     ,"RMFI4FICH2",
                                                     "RMFI5FICH0"     ,"RMFI5FICH1"     ,"RMFI5FICH2",
                                                     "RMFI6FICH0"     ,"RMFI6FICH1"     ,"RMFI6FICH2",
                                                     "RMFI7FICH0"     ,"RMFI7FICH1"     ,"RMFI7FICH2"};
  //the target directory for output plots
  std::string dir = "LMapvalidationPlots/";

  /*
  void PlottingHFFEtoGeo(
                         std::vector<HFFrontEnd> myHFFrontEnd,
                         std::vector<HFGeometry> myHFGeometry
                        );

  void PlottingHFFEtoBE(
                        std::vector<HFFrontEnd> myHFFrontEnd,
                        std::vector<HFBackEnd> myHFBackEnd
                       );
  */
}
