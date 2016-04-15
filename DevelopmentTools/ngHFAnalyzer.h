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
                         std::vector<ngHFFrontEnd> myngHFFrontEnd,
                         std::vector<ngHFGeometry> myngHFGeometry
                          );

  void PlottingngHFFEtoBEVME(
                           std::vector<ngHFFrontEnd> myngHFFrontEnd,
                           std::vector<ngHFBackEnd> myngHFBackEnd
                          );
  void PlottingngHFFEtoBEuTCA(
                            std::vector<ngHFFrontEnd> myngHFFrontEnd,
                            std::vector<ngHFBackEnd> myngHFBackEnd
                           );

  void PlottingngHFBEuTCAtoGeo(
                               std::vector<ngHFBackEnd> myngHFBackEnd,
                               std::vector<ngHFGeometry> myngHFGeometry
                              );


 private:
  //the target directory for output plots
  std::string dir = "LMapvalidationPlots/";


  const char *ngHFCrateSlotlabel[Ncrate*Nuhtr] = {
  "Cr22Sl01","Cr22Sl02","Cr22Sl03","Cr22Sl04","Cr22Sl05","Cr22Sl06","Cr22Sl07","Cr22Sl08","Cr22Sl09","Cr22Sl10","Cr22Sl11","Cr22Sl12",
  "Cr29Sl01","Cr29Sl02","Cr29Sl03","Cr29Sl04","Cr29Sl05","Cr29Sl06","Cr29Sl07","Cr29Sl08","Cr29Sl09","Cr29Sl10","Cr29Sl11","Cr29Sl12",
  "Cr32Sl01","Cr32Sl02","Cr32Sl03","Cr32Sl04","Cr32Sl05","Cr32Sl06","Cr32Sl07","Cr32Sl08","Cr32Sl09","Cr32Sl10","Cr32Sl11","Cr32Sl12"};
 
  const char *ngHFFiberFiberChannellabel[Nuhtr_fiber*Nfiber_ch] = {
  "Fi00Ch00","Fi00Ch01","Fi00Ch02","Fi00Ch03",
  "Fi01Ch00","Fi01Ch01","Fi01Ch02","Fi01Ch03",
  "Fi02Ch00","Fi02Ch01","Fi02Ch02","Fi02Ch03",
  "Fi03Ch00","Fi03Ch01","Fi03Ch02","Fi03Ch03",
  "Fi04Ch00","Fi04Ch01","Fi04Ch02","Fi04Ch03",
  "Fi05Ch00","Fi05Ch01","Fi05Ch02","Fi05Ch03",
  "Fi06Ch00","Fi06Ch01","Fi06Ch02","Fi06Ch03",
  "Fi07Ch00","Fi07Ch01","Fi07Ch02","Fi07Ch03",
  "Fi08Ch00","Fi08Ch01","Fi08Ch02","Fi08Ch03",
  "Fi09Ch00","Fi09Ch01","Fi09Ch02","Fi09Ch03",
  "Fi10Ch00","Fi10Ch01","Fi10Ch02","Fi10Ch03",
  "Fi11Ch00","Fi11Ch01","Fi11Ch02","Fi11Ch03",
  "Fi12Ch00","Fi12Ch01","Fi12Ch02","Fi12Ch03",
  "Fi13Ch00","Fi13Ch01","Fi13Ch02","Fi13Ch03",
  "Fi14Ch00","Fi14Ch01","Fi14Ch02","Fi14Ch03",
  "Fi15Ch00","Fi15Ch01","Fi15Ch02","Fi15Ch03",
  "Fi16Ch00","Fi16Ch01","Fi16Ch02","Fi16Ch03",
  "Fi17Ch00","Fi17Ch01","Fi17Ch02","Fi17Ch03",
  "Fi18Ch00","Fi18Ch01","Fi18Ch02","Fi18Ch03",
  "Fi19Ch00","Fi19Ch01","Fi19Ch02","Fi19Ch03",
  "Fi20Ch00","Fi20Ch01","Fi20Ch02","Fi20Ch03",
  "Fi21Ch00","Fi21Ch01","Fi21Ch02","Fi21Ch03",
  "Fi22Ch00","Fi22Ch01","Fi22Ch02","Fi22Ch03",
  "Fi23Ch00","Fi23Ch01","Fi23Ch02","Fi23Ch03"};
};

void ngHFAnalyzer::PlottingngHFBEuTCAtoGeo(
                                           std::vector<ngHFBackEnd> myngHFBackEnd,
                                           std::vector<ngHFGeometry> myngHFGeometry
                                          )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,2500);
  c->Divide(1,3); c->SetFillColor(0); c->cd();

  TH2D *nghfbephi = new TH2D("nghfbephi", "Phi in ngHF BackEnd", Nuhtr_fiber*Nfiber_ch, 1, Nuhtr_fiber*Nfiber_ch+1, Ncrate*Nuhtr, 1, Ncrate*Nuhtr+1);
  TH2D *nghfbeeta = new TH2D("nghfbeeta", "Eta in ngHF BackEnd", Nuhtr_fiber*Nfiber_ch, 1, Nuhtr_fiber*Nfiber_ch+1, Ncrate*Nuhtr, 1, Ncrate*Nuhtr+1);
  TH2D *nghfbedep = new TH2D("nghfbedep", "Dep in ngHF BackEnd", Nuhtr_fiber*Nfiber_ch, 1, Nuhtr_fiber*Nfiber_ch+1, Ncrate*Nuhtr, 1, Ncrate*Nuhtr+1);

  for(auto i=0; i<NchngHF_all; i++)
  {
    double zphi = (myngHFGeometry.at(i)).phi;
    double zeta = (myngHFGeometry.at(i)).side * (myngHFGeometry.at(i)).eta;
    double zdepth = (myngHFGeometry.at(i)).depth;

    double x = (myngHFBackEnd.at(i)).uhtr_fiber*4 + (myngHFBackEnd.at(i)).fiber_ch + 1;
    double crateid = -1;
    if      ((myngHFBackEnd.at(i)).ucrate==22) crateid = 0; 
    else if ((myngHFBackEnd.at(i)).ucrate==29) crateid = 1; 
    else crateid = 2;
    double y = crateid*12 + (myngHFBackEnd.at(i)).uhtr;
    nghfbephi->Fill(x,y,zphi); nghfbeeta->Fill(x,y,zeta); nghfbedep->Fill(x,y,zdepth);
  }

  for(int i=1;i<=Nuhtr_fiber*Nfiber_ch;i++)
  { 
    nghfbephi->GetXaxis()->SetBinLabel(i,ngHFFiberFiberChannellabel[i-1]); nghfbeeta->GetXaxis()->SetBinLabel(i,ngHFFiberFiberChannellabel[i-1]); nghfbedep->GetXaxis()->SetBinLabel(i,ngHFFiberFiberChannellabel[i-1]);
  }
  for(int i=1;i<=Ncrate*Nuhtr;i++) 
  { 
    nghfbephi->GetYaxis()->SetBinLabel(i,ngHFCrateSlotlabel[i-1]); nghfbeeta->GetYaxis()->SetBinLabel(i,ngHFCrateSlotlabel[i-1]); nghfbedep->GetYaxis()->SetBinLabel(i,ngHFCrateSlotlabel[i-1]);
  }

  nghfbephi->SetStats(0); nghfbeeta->SetStats(0); nghfbedep->SetStats(0);

  c->cd(1); nghfbephi->Draw("colztext"); c->cd(2); nghfbeeta->Draw("colztext"); c->cd(3); nghfbedep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_ngHFBEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_ngHFBEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_ngHFBEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

