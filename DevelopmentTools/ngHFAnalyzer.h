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

  const char *ngHFMRBXlabel[NrbxngHF*Nqie10] = {
  "ngHFM01QIE03","ngHFM01QIE04","ngHFM01QIE05","ngHFM01QIE06","ngHFM01QIE10","ngHFM01QIE11","ngHFM01QIE12","ngHFM01QIE13","ngHFM01QIE14",
  "ngHFM02QIE03","ngHFM02QIE04","ngHFM02QIE05","ngHFM02QIE06","ngHFM02QIE10","ngHFM02QIE11","ngHFM02QIE12","ngHFM02QIE13","ngHFM02QIE14",
  "ngHFM03QIE03","ngHFM03QIE04","ngHFM03QIE05","ngHFM03QIE06","ngHFM03QIE10","ngHFM03QIE11","ngHFM03QIE12","ngHFM03QIE13","ngHFM03QIE14",
  "ngHFM04QIE03","ngHFM04QIE04","ngHFM04QIE05","ngHFM04QIE06","ngHFM04QIE10","ngHFM04QIE11","ngHFM04QIE12","ngHFM04QIE13","ngHFM04QIE14",
  "ngHFM05QIE03","ngHFM05QIE04","ngHFM05QIE05","ngHFM05QIE06","ngHFM05QIE10","ngHFM05QIE11","ngHFM05QIE12","ngHFM05QIE13","ngHFM05QIE14",
  "ngHFM06QIE03","ngHFM06QIE04","ngHFM06QIE05","ngHFM06QIE06","ngHFM06QIE10","ngHFM06QIE11","ngHFM06QIE12","ngHFM06QIE13","ngHFM06QIE14",
  "ngHFM07QIE03","ngHFM07QIE04","ngHFM07QIE05","ngHFM07QIE06","ngHFM07QIE10","ngHFM07QIE11","ngHFM07QIE12","ngHFM07QIE13","ngHFM07QIE14",
  "ngHFM08QIE03","ngHFM08QIE04","ngHFM08QIE05","ngHFM08QIE06","ngHFM08QIE10","ngHFM08QIE11","ngHFM08QIE12","ngHFM08QIE13","ngHFM08QIE14"};

  const char *ngHFPRBXlabel[NrbxngHF*Nqie10] = {
  "ngHFP01QIE03","ngHFP01QIE04","ngHFP01QIE05","ngHFP01QIE06","ngHFP01QIE10","ngHFP01QIE11","ngHFP01QIE12","ngHFP01QIE13","ngHFP01QIE14",
  "ngHFP02QIE03","ngHFP02QIE04","ngHFP02QIE05","ngHFP02QIE06","ngHFP02QIE10","ngHFP02QIE11","ngHFP02QIE12","ngHFP02QIE13","ngHFP02QIE14",
  "ngHFP03QIE03","ngHFP03QIE04","ngHFP03QIE05","ngHFP03QIE06","ngHFP03QIE10","ngHFP03QIE11","ngHFP03QIE12","ngHFP03QIE13","ngHFP03QIE14",
  "ngHFP04QIE03","ngHFP04QIE04","ngHFP04QIE05","ngHFP04QIE06","ngHFP04QIE10","ngHFP04QIE11","ngHFP04QIE12","ngHFP04QIE13","ngHFP04QIE14",
  "ngHFP05QIE03","ngHFP05QIE04","ngHFP05QIE05","ngHFP05QIE06","ngHFP05QIE10","ngHFP05QIE11","ngHFP05QIE12","ngHFP05QIE13","ngHFP05QIE14",
  "ngHFP06QIE03","ngHFP06QIE04","ngHFP06QIE05","ngHFP06QIE06","ngHFP06QIE10","ngHFP06QIE11","ngHFP06QIE12","ngHFP06QIE13","ngHFP06QIE14",
  "ngHFP07QIE03","ngHFP07QIE04","ngHFP07QIE05","ngHFP07QIE06","ngHFP07QIE10","ngHFP07QIE11","ngHFP07QIE12","ngHFP07QIE13","ngHFP07QIE14",
  "ngHFP08QIE03","ngHFP08QIE04","ngHFP08QIE05","ngHFP08QIE06","ngHFP08QIE10","ngHFP08QIE11","ngHFP08QIE12","ngHFP08QIE13","ngHFP08QIE14"};

  const char *ngHFQIEfiberlabel[Nqie10_fiber*Nfiber_ch] = {"QIEFI1FICH0","QIEFI1FICH1","QIEFI1FICH2","QIEFI1FICH3",
                                                           "QIEFI2FICH0","QIEFI2FICH1","QIEFI2FICH2","QIEFI2FICH3",
                                                           "QIEFI3FICH0","QIEFI3FICH1","QIEFI3FICH2","QIEFI3FICH3",
                                                           "QIEFI4FICH0","QIEFI4FICH1","QIEFI4FICH2","QIEFI4FICH3",
                                                           "QIEFI5FICH0","QIEFI5FICH1","QIEFI5FICH2","QIEFI5FICH3",
                                                           "QIEFI6FICH0","QIEFI6FICH1","QIEFI6FICH2","QIEFI6FICH3"};

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

void ngHFAnalyzer::PlottingngHFFEtoGeo(
                                       std::vector<ngHFFrontEnd> myngHFFrontEnd,
                                       std::vector<ngHFGeometry> myngHFGeometry
                                      )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(3,2); c->SetFillColor(0); c->cd();

  gStyle->SetTitleFontSize(0.1);

  TH2D *nghfprbxphi = new TH2D("nghfprbxphi", "Phi in ngHFP FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *nghfprbxeta = new TH2D("nghfprbxeta", "Eta in ngHFP FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *nghfprbxdep = new TH2D("nghfprbxdep", "Dep in ngHFP FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);

  TH2D *nghfmrbxphi = new TH2D("nghfmrbxphi", "Phi in ngHFM FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *nghfmrbxeta = new TH2D("nghfmrbxeta", "Eta in ngHFM FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *nghfmrbxdep = new TH2D("nghfmrbxdep", "Dep in ngHFM FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);

  for(auto i=0; i<NchngHF_all; i++)
  {
    std::string thisrbx = (myngHFFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zphi = (myngHFGeometry.at(i)).phi;
    double zeta = (myngHFGeometry.at(i)).side * (myngHFGeometry.at(i)).eta;
    double zdepth = (myngHFGeometry.at(i)).depth;

    double x = ((myngHFFrontEnd.at(i)).qie10_fiber-4)*4 + (myngHFFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....8
    double qie10id = (myngHFFrontEnd.at(i)).qie10;
    double y = -1;
    qie10id < 8 ? y = (rbxid-1)*9 + qie10id-3+1 : y = (rbxid-1)*9 + qie10id-10+5;////

    if( thisrbx.find("ngHFP") != std::string::npos ){ nghfprbxphi->Fill(x,y,zphi); nghfprbxeta->Fill(x,y,zeta); nghfprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("ngHFM") != std::string::npos ){ nghfmrbxphi->Fill(x,y,zphi); nghfmrbxeta->Fill(x,y,zeta); nghfmrbxdep->Fill(x,y,zdepth); }
  }

  for(int i=1;i<=Nqie10_fiber*Nfiber_ch;i++)
  {
    nghfprbxphi->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); nghfprbxeta->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); nghfprbxdep->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]);
    nghfmrbxphi->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); nghfmrbxeta->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); nghfmrbxdep->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxngHF*Nqie10;i++) 
  { 
    nghfprbxphi->GetYaxis()->SetBinLabel(i,ngHFPRBXlabel[i-1]); nghfprbxeta->GetYaxis()->SetBinLabel(i,ngHFPRBXlabel[i-1]); nghfprbxdep->GetYaxis()->SetBinLabel(i,ngHFPRBXlabel[i-1]);
    nghfmrbxphi->GetYaxis()->SetBinLabel(i,ngHFMRBXlabel[i-1]); nghfmrbxeta->GetYaxis()->SetBinLabel(i,ngHFMRBXlabel[i-1]); nghfmrbxdep->GetYaxis()->SetBinLabel(i,ngHFMRBXlabel[i-1]);
  }

  nghfprbxphi->SetStats(0); nghfprbxeta->SetStats(0); nghfprbxdep->SetStats(0);
  nghfmrbxphi->SetStats(0); nghfmrbxeta->SetStats(0); nghfmrbxdep->SetStats(0);

  c->cd(1); nghfprbxphi->Draw("colztext"); c->cd(2); nghfprbxeta->Draw("colztext"); c->cd(3); nghfprbxdep->Draw("colztext");
  c->cd(4); nghfmrbxphi->Draw("colztext"); c->cd(5); nghfmrbxeta->Draw("colztext"); c->cd(6); nghfmrbxdep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_ngHFFEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_ngHFFEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_ngHFFEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

void ngHFAnalyzer::PlottingngHFFEtoBEuTCA(
                                          std::vector<ngHFFrontEnd> myngHFFrontEnd,
                                          std::vector<ngHFBackEnd> myngHFBackEnd
                                         )
{
  TCanvas *c = new TCanvas("c", "",0,51,8000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  gStyle->SetTitleFontSize(0.1);

  TH2D *hfprbxucrate = new TH2D("hfprbxucrate", "uCrate in ngHFP FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *hfprbxuhtr = new TH2D("hfprbxuhtr", "uHTR in ngHFP FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *hfprbxufpga = new TH2D("hfprbxufpga", "uFPGA in ngHFP FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *hfprbxuhtr_fiber = new TH2D("hfprbxuhtr_fiber", "uHTRfiber in ngHFP FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *hfmrbxucrate = new TH2D("hfmrbxucrate", "uCrate in ngHFM FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *hfmrbxuhtr = new TH2D("hfmrbxuhtr", "uHTR in ngHFM FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *hfmrbxufpga = new TH2D("hfmrbxufpga", "uFPGA in ngHFM FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);
  TH2D *hfmrbxuhtr_fiber = new TH2D("hfmrbxuhtr_fiber", "uHTRfiber in ngHFM FrontEnd", Nqie10_fiber*Nfiber_ch, 1, Nqie10_fiber*Nfiber_ch+1, NrbxngHF*Nqie10, 1, NrbxngHF*Nqie10+1);

  for(auto i=0; i<NchngHF_all; i++)
  {
    std::string thisrbx = (myngHFFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zucrate = (myngHFBackEnd.at(i)).ucrate;
    double zuhtr = (myngHFBackEnd.at(i)).uhtr;
    double zufpga = 2000;
    ((myngHFBackEnd.at(i)).ufpga)=="uHTR" ? zufpga = 10 : zufpga = -10;
    double zuhtr_fiber = (myngHFBackEnd.at(i)).uhtr_fiber;

    double x = ((myngHFFrontEnd.at(i)).qie10_fiber-4)*4 + (myngHFFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....8
    double qie10id = (myngHFFrontEnd.at(i)).qie10;
    double y = -1;
    qie10id < 8 ? y = (rbxid-1)*9 + qie10id-3+1 : y = (rbxid-1)*9 + qie10id-10+5;////

    if( thisrbx.find("ngHFP") != std::string::npos ){ hfprbxucrate->Fill(x,y,zucrate); hfprbxuhtr->Fill(x,y,zuhtr); hfprbxufpga->Fill(x,y,zufpga); hfprbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
    else if( thisrbx.find("ngHFM") != std::string::npos ){ hfmrbxucrate->Fill(x,y,zucrate); hfmrbxuhtr->Fill(x,y,zuhtr); hfmrbxufpga->Fill(x,y,zufpga); hfmrbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
  }

  for(int i=1;i<=Nqie10_fiber*Nfiber_ch;i++)
  { 
    hfprbxucrate->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); hfprbxuhtr->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); 
    hfprbxufpga->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); hfprbxuhtr_fiber->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]);

    hfmrbxucrate->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); hfmrbxuhtr->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]);
    hfmrbxufpga->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]); hfmrbxuhtr_fiber->GetXaxis()->SetBinLabel(i,ngHFQIEfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxngHF*Nqie10;i++) 
  { 
    hfprbxucrate->GetYaxis()->SetBinLabel(i,ngHFPRBXlabel[i-1]); hfprbxuhtr->GetYaxis()->SetBinLabel(i,ngHFPRBXlabel[i-1]); 
    hfprbxufpga->GetYaxis()->SetBinLabel(i,ngHFPRBXlabel[i-1]); hfprbxuhtr_fiber->GetYaxis()->SetBinLabel(i,ngHFPRBXlabel[i-1]);
    
    hfmrbxucrate->GetYaxis()->SetBinLabel(i,ngHFMRBXlabel[i-1]); hfmrbxuhtr->GetYaxis()->SetBinLabel(i,ngHFMRBXlabel[i-1]);
    hfmrbxufpga->GetYaxis()->SetBinLabel(i,ngHFMRBXlabel[i-1]); hfmrbxuhtr_fiber->GetYaxis()->SetBinLabel(i,ngHFMRBXlabel[i-1]);
  }

  hfprbxucrate->SetStats(0); hfprbxuhtr->SetStats(0); hfprbxufpga->SetStats(0); hfprbxuhtr_fiber->SetStats(0);
  hfmrbxucrate->SetStats(0); hfmrbxuhtr->SetStats(0); hfmrbxufpga->SetStats(0); hfmrbxuhtr_fiber->SetStats(0);

  c->cd(1); hfprbxucrate->Draw("colztext"); c->cd(2); hfprbxuhtr->Draw("colztext"); c->cd(3); hfprbxufpga->Draw("colztext"); c->cd(4); hfprbxuhtr_fiber->Draw("colztext");
  c->cd(5); hfmrbxucrate->Draw("colztext"); c->cd(6); hfmrbxuhtr->Draw("colztext"); c->cd(7); hfmrbxufpga->Draw("colztext"); c->cd(8); hfmrbxuhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_ngHFFEucrateuhtrufpgauhtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_ngHFFEucrateuhtrufpgauhtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_ngHFFEucrateuhtrufpgauhtr_fiber.C").c_str() );
  c->Close();

  return ;
}

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

