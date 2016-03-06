#include <vector>
#include <string>
#include <iostream>

#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "HBHEMappingObject.h"

namespace HBHEAnalyzer
{
  // channels in HB
  const int NchHBHE_all = 2592+2592;
  //Front End variables
  //rbx in HB, 18 for each side
  const int NrbxHB = 18;
  //4 rm in all HB rbx, label from 1 to 4
  const int NrmHB = 4;
  //rm fiber 2,3,4,5,6,7, in total 6 fibers per rm
  const int Nrm_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  const int Nfiber_ch = 3;

  const int Nqie = 3;
  const int Nqie_ch = 6;

  //Back End variables
  //4 crate in HB: 0,1,4,5,10,11,14,15,17
  const int Ncrate = 9;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18
  const int Nhtr = 12;
  //2 fpga flavors top and bottom
  const int Nfpga = 2;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8
  const int Nhtr_fiber = 8;

  //Geometry variables in HB: 
  const int NHBside = 2;
  //const int NHBeta = 15;
  const int NHBphi = 72;
  const int NHBdepth = 2;

  const char *HBMRBXlabel[NrbxHB*NrmHB] = {"HBM01RM1","HBM01RM2","HBM01RM3","HBM01RM4",
                                           "HBM02RM1","HBM02RM2","HBM02RM3","HBM02RM4",
                                           "HBM03RM1","HBM03RM2","HBM03RM3","HBM03RM4",
                                           "HBM04RM1","HBM04RM2","HBM04RM3","HBM04RM4",
                                           "HBM05RM1","HBM05RM2","HBM05RM3","HBM05RM4",
                                           "HBM06RM1","HBM06RM2","HBM06RM3","HBM06RM4",
                                           "HBM07RM1","HBM07RM2","HBM07RM3","HBM07RM4",
                                           "HBM08RM1","HBM08RM2","HBM08RM3","HBM08RM4",
                                           "HBM09RM1","HBM09RM2","HBM09RM3","HBM09RM4",
                                           "HBM10RM1","HBM10RM2","HBM10RM3","HBM10RM4",
                                           "HBM11RM1","HBM11RM2","HBM11RM3","HBM11RM4",
                                           "HBM12RM1","HBM12RM2","HBM12RM3","HBM12RM4",
                                           "HBM13RM1","HBM13RM2","HBM13RM3","HBM13RM4",
                                           "HBM14RM1","HBM14RM2","HBM14RM3","HBM14RM4",
                                           "HBM15RM1","HBM15RM2","HBM15RM3","HBM15RM4",
                                           "HBM16RM1","HBM16RM2","HBM16RM3","HBM16RM4",
                                           "HBM17RM1","HBM17RM2","HBM17RM3","HBM17RM4",
                                           "HBM18RM1","HBM18RM2","HBM18RM3","HBM18RM4"};

  const char *HBPRBXlabel[NrbxHB*NrmHB] = {"HBP01RM1","HBP01RM2","HBP01RM3","HBP01RM4",
                                           "HBP02RM1","HBP02RM2","HBP02RM3","HBP02RM4",
                                           "HBP03RM1","HBP03RM2","HBP03RM3","HBP03RM4",
                                           "HBP04RM1","HBP04RM2","HBP04RM3","HBP04RM4",
                                           "HBP05RM1","HBP05RM2","HBP05RM3","HBP05RM4",
                                           "HBP06RM1","HBP06RM2","HBP06RM3","HBP06RM4",
                                           "HBP07RM1","HBP07RM2","HBP07RM3","HBP07RM4",
                                           "HBP08RM1","HBP08RM2","HBP08RM3","HBP08RM4",
                                           "HBP09RM1","HBP09RM2","HBP09RM3","HBP09RM4",
                                           "HBP10RM1","HBP10RM2","HBP10RM3","HBP10RM4",
                                           "HBP11RM1","HBP11RM2","HBP11RM3","HBP11RM4",
                                           "HBP12RM1","HBP12RM2","HBP12RM3","HBP12RM4",
                                           "HBP13RM1","HBP13RM2","HBP13RM3","HBP13RM4",
                                           "HBP14RM1","HBP14RM2","HBP14RM3","HBP14RM4",
                                           "HBP15RM1","HBP15RM2","HBP15RM3","HBP15RM4",
                                           "HBP16RM1","HBP16RM2","HBP16RM3","HBP16RM4",
                                           "HBP17RM1","HBP17RM2","HBP17RM3","HBP17RM4",
                                           "HBP18RM1","HBP18RM2","HBP18RM3","HBP18RM4"};

  const char *HBRMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI2FICH0"     ,"RMFI2FICH1"     ,"RMFI2FICH2",
                                                     "RMFI3FICH0"     ,"RMFI3FICH1"     ,"RMFI3FICH2",
                                                     "RMFI4FICH0"     ,"RMFI4FICH1"     ,"RMFI4FICH2",
                                                     "RMFI5FICH0"     ,"RMFI5FICH1"     ,"RMFI5FICH2",
                                                     "RMFI6FICH0"     ,"RMFI6FICH1"     ,"RMFI6FICH2",
                                                     "RMFI7FICH0"     ,"RMFI7FICH1"     ,"RMFI7FICH2"};
  //the target directory for output plots
  std::string dir = "LMapvalidationPlots/";

  /*
  void PlottingHBFEtoGeo(
                         std::vector<HBFrontEnd> myHBFrontEnd,
                         std::vector<HBGeometry> myHBGeometry
                        );

  void PlottingHBFEtoBE(
                        std::vector<HBFrontEnd> myHBFrontEnd,
                        std::vector<HBBackEnd> myHBBackEnd
                       );
  */
}
