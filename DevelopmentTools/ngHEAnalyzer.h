#include <vector>
#include <string>
#include <iostream>

#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "ngHEMappingObject.h"

class ngHEAnalyzer : public ngHEConstant 
{
 public:
  void ngHENChannelBasicCheck();
  void PlottingngHEFEtoGeo(
                           std::vector<ngHEFrontEnd> myngHEFrontEnd,
                           std::vector<ngHEGeometry> myngHEGeometry
                          );
  void PlottingngHEFEtoBEuTCA(
                              std::vector<ngHEFrontEnd> myngHEFrontEnd,
                              std::vector<ngHEBackEnd> myngHEBackEnd
                             );
  void PlottingngHEBEuTCAtoGeo(
                               std::vector<ngHEBackEnd> myngHEBackEnd,
                               std::vector<ngHEGeometry> myngHEGeometry
                              );

 private:
  //the target directory for output plots
  std::string dir = "LMapValidationPlots/";

  const char *ngHEMRBXlabel[NrbxngHE*NrmngHE] = {"ngHEM01RM1","ngHEM01RM2","ngHEM01RM3","ngHEM01RM4",
                                                 "ngHEM02RM1","ngHEM02RM2","ngHEM02RM3","ngHEM02RM4",
                                                 "ngHEM03RM1","ngHEM03RM2","ngHEM03RM3","ngHEM03RM4",
                                                 "ngHEM04RM1","ngHEM04RM2","ngHEM04RM3","ngHEM04RM4",
                                                 "ngHEM05RM1","ngHEM05RM2","ngHEM05RM3","ngHEM05RM4",
                                                 "ngHEM06RM1","ngHEM06RM2","ngHEM06RM3","ngHEM06RM4",
                                                 "ngHEM07RM1","ngHEM07RM2","ngHEM07RM3","ngHEM07RM4",
                                                 "ngHEM08RM1","ngHEM08RM2","ngHEM08RM3","ngHEM08RM4",
                                                 "ngHEM09RM1","ngHEM09RM2","ngHEM09RM3","ngHEM09RM4",
                                                 "ngHEM10RM1","ngHEM10RM2","ngHEM10RM3","ngHEM10RM4",
                                                 "ngHEM11RM1","ngHEM11RM2","ngHEM11RM3","ngHEM11RM4",
                                                 "ngHEM12RM1","ngHEM12RM2","ngHEM12RM3","ngHEM12RM4",
                                                 "ngHEM13RM1","ngHEM13RM2","ngHEM13RM3","ngHEM13RM4",
                                                 "ngHEM14RM1","ngHEM14RM2","ngHEM14RM3","ngHEM14RM4",
                                                 "ngHEM15RM1","ngHEM15RM2","ngHEM15RM3","ngHEM15RM4",
                                                 "ngHEM16RM1","ngHEM16RM2","ngHEM16RM3","ngHEM16RM4",
                                                 "ngHEM17RM1","ngHEM17RM2","ngHEM17RM3","ngHEM17RM4",
                                                 "ngHEM18RM1","ngHEM18RM2","ngHEM18RM3","ngHEM18RM4"};

  const char *ngHEPRBXlabel[NrbxngHE*NrmngHE] = {"ngHEP01RM1","ngHEP01RM2","ngHEP01RM3","ngHEP01RM4",
                                                 "ngHEP02RM1","ngHEP02RM2","ngHEP02RM3","ngHEP02RM4",
                                                 "ngHEP03RM1","ngHEP03RM2","ngHEP03RM3","ngHEP03RM4",   
                                                 "ngHEP04RM1","ngHEP04RM2","ngHEP04RM3","ngHEP04RM4",   
                                                 "ngHEP05RM1","ngHEP05RM2","ngHEP05RM3","ngHEP05RM4",   
                                                 "ngHEP06RM1","ngHEP06RM2","ngHEP06RM3","ngHEP06RM4",   
                                                 "ngHEP07RM1","ngHEP07RM2","ngHEP07RM3","ngHEP07RM4",
                                                 "ngHEP08RM1","ngHEP08RM2","ngHEP08RM3","ngHEP08RM4",
                                                 "ngHEP09RM1","ngHEP09RM2","ngHEP09RM3","ngHEP09RM4",
                                                 "ngHEP10RM1","ngHEP10RM2","ngHEP10RM3","ngHEP10RM4",
                                                 "ngHEP11RM1","ngHEP11RM2","ngHEP11RM3","ngHEP11RM4",
                                                 "ngHEP12RM1","ngHEP12RM2","ngHEP12RM3","ngHEP12RM4",
                                                 "ngHEP13RM1","ngHEP13RM2","ngHEP13RM3","ngHEP13RM4",
                                                 "ngHEP14RM1","ngHEP14RM2","ngHEP14RM3","ngHEP14RM4",
                                                 "ngHEP15RM1","ngHEP15RM2","ngHEP15RM3","ngHEP15RM4",
                                                 "ngHEP16RM1","ngHEP16RM2","ngHEP16RM3","ngHEP16RM4",
                                                 "ngHEP17RM1","ngHEP17RM2","ngHEP17RM3","ngHEP17RM4",
                                                 "ngHEP18RM1","ngHEP18RM2","ngHEP18RM3","ngHEP18RM4"};

  const char *ngHERMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI1FICH0","RMFI1FICH1","RMFI1FICH2","RMFI1FICH3","RMFI1FICH4","RMFI1FICH5",
                                                       "RMFI2FICH0","RMFI2FICH1","RMFI2FICH2","RMFI2FICH3","RMFI2FICH4","RMFI2FICH5",
                                                       "RMFI3FICH0","RMFI3FICH1","RMFI3FICH2","RMFI3FICH3","RMFI3FICH4","RMFI3FICH5",
                                                       "RMFI4FICH0","RMFI4FICH1","RMFI4FICH2","RMFI4FICH3","RMFI4FICH4","RMFI4FICH5",
                                                       "RMFI5FICH0","RMFI5FICH1","RMFI5FICH2","RMFI5FICH3","RMFI5FICH4","RMFI5FICH5",
                                                       "RMFI6FICH0","RMFI6FICH1","RMFI6FICH2","RMFI6FICH3","RMFI6FICH4","RMFI6FICH5",
                                                       "RMFI7FICH0","RMFI7FICH1","RMFI7FICH2","RMFI7FICH3","RMFI7FICH4","RMFI7FICH5",
                                                       "RMFI8FICH0","RMFI8FICH1","RMFI8FICH2","RMFI8FICH3","RMFI8FICH4","RMFI8FICH5"};
  const char *ngHECrateSlotlabel[Ncrate*Nuhtr] = {
  "Cr20Sl01","Cr20Sl02","Cr20Sl03","Cr20Sl04","Cr20Sl05","Cr20Sl06","Cr20Sl07","Cr20Sl08","Cr20Sl09","Cr20Sl10","Cr20Sl11","Cr20Sl12",
  "Cr21Sl01","Cr21Sl02","Cr21Sl03","Cr21Sl04","Cr21Sl05","Cr21Sl06","Cr21Sl07","Cr21Sl08","Cr21Sl09","Cr21Sl10","Cr21Sl11","Cr21Sl12",
  "Cr24Sl01","Cr24Sl02","Cr24Sl03","Cr24Sl04","Cr24Sl05","Cr24Sl06","Cr24Sl07","Cr24Sl08","Cr24Sl09","Cr24Sl10","Cr24Sl11","Cr24Sl12",
  "Cr25Sl01","Cr25Sl02","Cr25Sl03","Cr25Sl04","Cr25Sl05","Cr25Sl06","Cr25Sl07","Cr25Sl08","Cr25Sl09","Cr25Sl10","Cr25Sl11","Cr25Sl12",
  "Cr30Sl01","Cr30Sl02","Cr30Sl03","Cr30Sl04","Cr30Sl05","Cr30Sl06","Cr30Sl07","Cr30Sl08","Cr30Sl09","Cr30Sl10","Cr30Sl11","Cr30Sl12",
  "Cr31Sl01","Cr31Sl02","Cr31Sl03","Cr31Sl04","Cr31Sl05","Cr31Sl06","Cr31Sl07","Cr31Sl08","Cr31Sl09","Cr31Sl10","Cr31Sl11","Cr31Sl12",
  "Cr34Sl01","Cr34Sl02","Cr34Sl03","Cr34Sl04","Cr34Sl05","Cr34Sl06","Cr34Sl07","Cr34Sl08","Cr34Sl09","Cr34Sl10","Cr34Sl11","Cr34Sl12",
  "Cr35Sl01","Cr35Sl02","Cr35Sl03","Cr35Sl04","Cr35Sl05","Cr35Sl06","Cr35Sl07","Cr35Sl08","Cr35Sl09","Cr35Sl10","Cr35Sl11","Cr35Sl12",
  "Cr37Sl01","Cr37Sl02","Cr37Sl03","Cr37Sl04","Cr37Sl05","Cr37Sl06","Cr37Sl07","Cr37Sl08","Cr37Sl09","Cr37Sl10","Cr37Sl11","Cr37Sl12"};

  const char *ngHEFiberFiberChannellabel[Nuhtr_fiber*Nfiber_ch] = {
  "Fi00Ch00","Fi00Ch01","Fi00Ch02","Fi00Ch03","Fi00Ch04","Fi00Ch05",
  "Fi01Ch00","Fi01Ch01","Fi01Ch02","Fi01Ch03","Fi01Ch04","Fi01Ch05",
  "Fi02Ch00","Fi02Ch01","Fi02Ch02","Fi02Ch03","Fi02Ch04","Fi02Ch05",
  "Fi03Ch00","Fi03Ch01","Fi03Ch02","Fi03Ch03","Fi03Ch04","Fi03Ch05",
  "Fi04Ch00","Fi04Ch01","Fi04Ch02","Fi04Ch03","Fi04Ch04","Fi04Ch05",
  "Fi05Ch00","Fi05Ch01","Fi05Ch02","Fi05Ch03","Fi05Ch04","Fi05Ch05",
  "Fi06Ch00","Fi06Ch01","Fi06Ch02","Fi06Ch03","Fi06Ch04","Fi06Ch05",
  "Fi07Ch00","Fi07Ch01","Fi07Ch02","Fi07Ch03","Fi07Ch04","Fi07Ch05",
  "Fi08Ch00","Fi08Ch01","Fi08Ch02","Fi08Ch03","Fi08Ch04","Fi08Ch05",
  "Fi09Ch00","Fi09Ch01","Fi09Ch02","Fi09Ch03","Fi09Ch04","Fi09Ch05",
  "Fi10Ch00","Fi10Ch01","Fi10Ch02","Fi10Ch03","Fi10Ch04","Fi10Ch05",
  "Fi11Ch00","Fi11Ch01","Fi11Ch02","Fi11Ch03","Fi11Ch04","Fi11Ch05",
  "Fi12Ch00","Fi12Ch01","Fi12Ch02","Fi12Ch03","Fi12Ch04","Fi12Ch05",
  "Fi13Ch00","Fi13Ch01","Fi13Ch02","Fi13Ch03","Fi13Ch04","Fi13Ch05",
  "Fi14Ch00","Fi14Ch01","Fi14Ch02","Fi14Ch03","Fi14Ch04","Fi14Ch05",
  "Fi15Ch00","Fi15Ch01","Fi15Ch02","Fi15Ch03","Fi15Ch04","Fi15Ch05",
  "Fi16Ch00","Fi16Ch01","Fi16Ch02","Fi16Ch03","Fi16Ch04","Fi16Ch05",
  "Fi17Ch00","Fi17Ch01","Fi17Ch02","Fi17Ch03","Fi17Ch04","Fi17Ch05",
  "Fi18Ch00","Fi18Ch01","Fi18Ch02","Fi18Ch03","Fi18Ch04","Fi18Ch05",
  "Fi19Ch00","Fi19Ch01","Fi19Ch02","Fi19Ch03","Fi19Ch04","Fi19Ch05",
  "Fi20Ch00","Fi20Ch01","Fi20Ch02","Fi20Ch03","Fi20Ch04","Fi20Ch05",
  "Fi21Ch00","Fi21Ch01","Fi21Ch02","Fi21Ch03","Fi21Ch04","Fi21Ch05",
  "Fi22Ch00","Fi22Ch01","Fi22Ch02","Fi22Ch03","Fi22Ch04","Fi22Ch05",
  "Fi23Ch00","Fi23Ch01","Fi23Ch02","Fi23Ch03","Fi23Ch04","Fi23Ch05"};
};
