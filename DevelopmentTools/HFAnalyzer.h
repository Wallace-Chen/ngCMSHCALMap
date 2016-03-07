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
  const int NrbxHF = 12;
  //3 rm in all HF rbx, label from 1 to 3
  const int NrmHF = 3;
  //rm fiber 1,2,3,4,5,6,7,8, in total 8 fibers per rm
  const int Nrm_fiber = 8;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  const int Nfiber_ch = 3;

  const int Nqie = 4;
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

  //Need to be tuned
  //Geometry variables in HF: eta from 29,to 40,41, phi is 1,3,...71 for most eta while dphi == 4 for eta 40,41;
  const int NHFside = 2;
  const int NHFetadphi2 = 11;
  const int NHFetadphi4 = 2;
  const int NHFphidphi2 = 36;
  const int NHFphidphi4 = 18;
  const int NHFdepth = 2;

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

  void PlottingHFFEtoGeo(
                         std::vector<HFFrontEnd> myHFFrontEnd,
                         std::vector<HFGeometry> myHFGeometry
                        );

  void PlottingHFFEtoBEVME(
                           std::vector<HFFrontEnd> myHFFrontEnd,
                           std::vector<HFBackEnd> myHFBackEnd
                          );
  /*
  void PlottingHFFEtoBEuTCA(
                            std::vector<HFFrontEnd> myHFFrontEnd,
                            std::vector<HFBackEnd> myHFBackEnd
                           );
  */
}

void HFAnalyzer::PlottingHFFEtoGeo(
                                   std::vector<HFFrontEnd> myHFFrontEnd,
                                   std::vector<HFGeometry> myHFGeometry
                                  )
{
  TCanvas *c = new TCanvas("c", "",0,51,4500,2000);
  c->Divide(3,2); c->SetFillColor(0); c->cd();

  TH2D *hfprbxphi = new TH2D("hfprbxphi", "Phi in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxeta = new TH2D("hfprbxeta", "Eta in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxdep = new TH2D("hfprbxdep", "Dep in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);

  TH2D *hfmrbxphi = new TH2D("hfmrbxphi", "Phi in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxeta = new TH2D("hfmrbxeta", "Eta in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxdep = new TH2D("hfmrbxdep", "Dep in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);

  for(auto i=0; i<NchHF_all; i++)
  {
    std::string thisrbx = (myHFFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zphi = (myHFGeometry.at(i)).phi;
    double zeta = (myHFGeometry.at(i)).side * (myHFGeometry.at(i)).eta;
    double zdepth = (myHFGeometry.at(i)).depth;

    double x = ((myHFFrontEnd.at(i)).rm_fiber-1)*3 + (myHFFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....12 for HF,0, 2,4,6,8,10,12 for other HF,12

    double rmid = (myHFFrontEnd.at(i)).rm;
    double y = (rbxid-1)*3 + rmid;

    if( thisrbx.find("HFP") != std::string::npos ){ hfprbxphi->Fill(x,y,zphi); hfprbxeta->Fill(x,y,zeta); hfprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("HFM") != std::string::npos ){ hfmrbxphi->Fill(x,y,zphi); hfmrbxeta->Fill(x,y,zeta); hfmrbxdep->Fill(x,y,zdepth); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hfprbxphi->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxeta->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxdep->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
    hfmrbxphi->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxeta->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxdep->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHF*NrmHF;i++) 
  { 
    hfprbxphi->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxeta->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxdep->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]);
    hfmrbxphi->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxeta->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxdep->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]);
  }

  hfprbxphi->SetStats(0); hfprbxeta->SetStats(0); hfprbxdep->SetStats(0);
  hfmrbxphi->SetStats(0); hfmrbxeta->SetStats(0); hfmrbxdep->SetStats(0);

  c->cd(1); hfprbxphi->Draw("colztext"); c->cd(2); hfprbxeta->Draw("colztext"); c->cd(3); hfprbxdep->Draw("colztext");
  c->cd(4); hfmrbxphi->Draw("colztext"); c->cd(5); hfmrbxeta->Draw("colztext"); c->cd(6); hfmrbxdep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_HFFEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_HFFEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_HFFEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

void HFAnalyzer::PlottingHFFEtoBEVME(
                                     std::vector<HFFrontEnd> myHFFrontEnd,
                                     std::vector<HFBackEnd> myHFBackEnd
                                    )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,2000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *hfprbxcrate = new TH2D("hfprbxcrate", "Crate in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxhtr = new TH2D("hfprbxhtr", "HTR in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxfpga = new TH2D("hfprbxfpga", "FPGA in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxhtr_fiber = new TH2D("hfprbxhtr_fiber", "HTRfiber in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxcrate = new TH2D("hfmrbxcrate", "Crate in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxhtr = new TH2D("hfmrbxhtr", "HTR in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxfpga = new TH2D("hfmrbxfpga", "FPGA in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxhtr_fiber = new TH2D("hfmrbxhtr_fiber", "HTRfiber in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);

  for(auto i=0; i<NchHF_all; i++)
  {
    std::string thisrbx = (myHFFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zcrate = (myHFBackEnd.at(i)).crate;
    double zhtr = (myHFBackEnd.at(i)).htr;
    double zfpga = 2000;
    ((myHFBackEnd.at(i)).fpga)=="top" ? zfpga = 1 : zfpga = -1;
    double zhtr_fiber = (myHFBackEnd.at(i)).htr_fiber;

    double x = ((myHFFrontEnd.at(i)).rm_fiber-1)*3 + (myHFFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....12 for HF,0, 2,4,6,8,10,12 for other HF,12
    double rmid = (myHFFrontEnd.at(i)).rm;
    double y = (rbxid-1)*3 + rmid;
    
    if( thisrbx.find("HFP") != std::string::npos ){ hfprbxcrate->Fill(x,y,zcrate); hfprbxhtr->Fill(x,y,zhtr); hfprbxfpga->Fill(x,y,zfpga); hfprbxhtr_fiber->Fill(x,y,zhtr_fiber); }
    else if( thisrbx.find("HFM") != std::string::npos ){ hfmrbxcrate->Fill(x,y,zcrate); hfmrbxhtr->Fill(x,y,zhtr); hfmrbxfpga->Fill(x,y,zfpga); hfmrbxhtr_fiber->Fill(x,y,zhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hfprbxcrate->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxhtr->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); 
    hfprbxfpga->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxhtr_fiber->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);

    hfmrbxcrate->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxhtr->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
    hfmrbxfpga->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHF*NrmHF;i++) 
  { 
    hfprbxcrate->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxhtr->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); 
    hfprbxfpga->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxhtr_fiber->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]);
    
    hfmrbxcrate->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxhtr->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]);
    hfmrbxfpga->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxhtr_fiber->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]);
  }

  hfprbxcrate->SetStats(0); hfprbxhtr->SetStats(0); hfprbxfpga->SetStats(0); hfprbxhtr_fiber->SetStats(0);
  hfmrbxcrate->SetStats(0); hfmrbxhtr->SetStats(0); hfmrbxfpga->SetStats(0); hfmrbxhtr_fiber->SetStats(0);

  c->cd(1); hfprbxcrate->Draw("colztext"); c->cd(2); hfprbxhtr->Draw("colztext"); c->cd(3); hfprbxfpga->Draw("colztext"); c->cd(4); hfprbxhtr_fiber->Draw("colztext");
  c->cd(5); hfmrbxcrate->Draw("colztext"); c->cd(6); hfmrbxhtr->Draw("colztext"); c->cd(7); hfmrbxfpga->Draw("colztext"); c->cd(8); hfmrbxhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HFFEcratehtrfpgahtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HFFEcratehtrfpgahtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HFFEcratehtrfpgahtr_fiber.C").c_str() );
  c->Close();

  return ;
}

