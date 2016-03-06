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

namespace HOAnalyzer
{
  //2376 channels in HO and HOX
  const int NchHO_all = 2376;
  //Front End variables
  //rbx in HO, different in 0 and 12
  const int NrbxHO0 = 1*12;
  const int NrbxHO12 = 4*6;
  //3 rm in HO0 while 4 rm in HO1P, HO1M, HO2P, HO2M
  //for HO0 part, 1,4,5,8,9,12, rm is 1,2,3; 2,3,6,7,10,11, rm is 2,3,4
  const int NrmHO0 = 3;
  const int NrmHO12 = 4;
  //rm fiber 2,3,4,5,6,7, in total 6 fibers per rm
  const int Nrm_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  const int Nfiber_ch = 3;

  const int Nqie = 3;
  const int Nqie_ch = 6;

  //Back End variables
  //4 crate in HO: 3,6,7,12
  const int Ncrate = 4;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18
  const int Nhtr = 12;
  //2 fpga flavors top and bottom
  const int Nfpga = 2;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8
  const int Nhtr_fiber = 8;
  //216 HOX channels in HO map in total, while 72 special HOX channels with no patch panel attachment, htr slot is 21
  const int NspecialHOX = 72;

  //Geimetry variables,2160 channels, side -1 or +1, eta from 1 to 15, phi 1 to 72, depth always 4
  const int NHOside = 2;
  const int NHOeta = 15;
  const int NHOphi = 72;
  const int NHOdepth = 1;
  //144 normal HOX channels,only in side -1, eta 4 and eta 15, for all phis
  const int NnormalHOX = 2*72;
  //72 special HOX channels, only in side +1, eta 15, for all phis

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
  std::string dir = "LMapvalidationPlots/";

  void PlottingHOFEtoGeo(
                         std::vector<HOFrontEnd> myHOFrontEnd,
                         std::vector<HOGeometry> myHOGeometry
                        );

  void PlottingHOFEtoBE(
                        std::vector<HOFrontEnd> myHOFrontEnd,
                        std::vector<HOBackEnd> myHOBackEnd
                       );
}

void HOAnalyzer::PlottingHOFEtoGeo(
                                   std::vector<HOFrontEnd> myHOFrontEnd,
                                   std::vector<HOGeometry> myHOGeometry
                                  )
{
  const std::string titre="CMS HCAL Channel Mapping";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC(); title->SetTextSize(0.045);

  TCanvas *c = new TCanvas("c", "",0,51,3000,5000);
  c->Divide(2,5); c->SetFillColor(0); c->cd();

  TH2D *ho0rbxphi = new TH2D("ho0rbxphi", "Phi in HO0 FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO0*NrmHO0, 1, NrbxHO0*NrmHO0+1);
  TH2D *ho0rbxeta = new TH2D("ho0rbxeta", "Eta in HO0 FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO0*NrmHO0, 1, NrbxHO0*NrmHO0+1);
  TH2D *ho1prbxphi = new TH2D("ho1prbxphi", "Phi in HO1P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1prbxeta = new TH2D("ho1prbxeta", "Eta in HO1P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2prbxphi = new TH2D("ho2prbxphi", "Phi in HO2P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2prbxeta = new TH2D("ho2prbxeta", "Eta in HO2P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1mrbxphi = new TH2D("ho1mrbxphi", "Phi in HO1M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1mrbxeta = new TH2D("ho1mrbxeta", "Eta in HO1M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2mrbxphi = new TH2D("ho2mrbxphi", "Phi in HO2M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2mrbxeta = new TH2D("ho2mrbxeta", "Eta in HO2M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);

  for(auto i=0; i<NchHO_all; i++)
  {
    std::string thisrbx = (myHOFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    //std::cout << (myHOGeometry.at(i)).eta << std::endl;
    //if( (myHOGeometry.at(i)).subdet != "HO") continue;    
    double zphi = (myHOGeometry.at(i)).phi;
    double zeta = (myHOGeometry.at(i)).side * (myHOGeometry.at(i)).eta;
    double x = ((myHOFrontEnd.at(i)).rm_fiber-2)*3 + (myHOFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....12 for HO0, 2,4,6,8,10,12 for other HO12

    if( thisrbx.find("HO0") != std::string::npos )
    {
      double rmid = -1;//123,234 to 123
      if( rbxid == 1 || rbxid == 4 || rbxid == 5 || rbxid == 8 || rbxid == 9 || rbxid == 12 ) rmid = (myHOFrontEnd.at(i)).rm;
      else rmid = (myHOFrontEnd.at(i)).rm-1;
      double y = (rbxid-1)*3 + rmid;
      //std::cout << x << "," << y << std::endl;
      ho0rbxphi->Fill(x,y,zphi); ho0rbxeta->Fill(x,y,zeta);
    }
    else
    {
      double rmid = (myHOFrontEnd.at(i)).rm;//1234 to 1234
      double y = (rbxid/2-1)*4 + rmid;

      if( thisrbx.find("HO1P") != std::string::npos )
      {
        ho1prbxphi->Fill(x,y,zphi); ho1prbxeta->Fill(x,y,zeta);
      }
      else if( thisrbx.find("HO2P") != std::string::npos )
      {
        ho2prbxphi->Fill(x,y,zphi); ho2prbxeta->Fill(x,y,zeta);
      }
      else if( thisrbx.find("HO1M") != std::string::npos )
      {
        ho1mrbxphi->Fill(x,y,zphi); ho1mrbxeta->Fill(x,y,zeta);
      }
      else if( thisrbx.find("HO2M") != std::string::npos )
      {
        ho2mrbxphi->Fill(x,y,zphi); ho2mrbxeta->Fill(x,y,zeta);
      }
    }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    ho0rbxphi->GetXaxis()->SetBinLabel(i,HO0RMfiberlabel[i-1]); ho0rbxeta->GetXaxis()->SetBinLabel(i,HO0RMfiberlabel[i-1]); 
    ho1prbxphi->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]); ho1prbxeta->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]);
    ho2prbxphi->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]); ho2prbxeta->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]);
    ho1mrbxphi->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]); ho1mrbxeta->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]);
    ho2mrbxphi->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]); ho2mrbxeta->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHO0*NrmHO0;i++) 
  { 
    ho0rbxphi->GetYaxis()->SetBinLabel(i,HO0RBXlabel[i-1]); ho0rbxeta->GetYaxis()->SetBinLabel(i,HO0RBXlabel[i-1]); 
  }
  for(int i=1;i<=NrbxHO12*NrmHO12/4;i++)
  {
    ho1prbxphi->GetYaxis()->SetBinLabel(i,HO1PRBXlabel[i-1]); ho1prbxeta->GetYaxis()->SetBinLabel(i,HO1PRBXlabel[i-1]);
    ho2prbxphi->GetYaxis()->SetBinLabel(i,HO2PRBXlabel[i-1]); ho2prbxeta->GetYaxis()->SetBinLabel(i,HO2PRBXlabel[i-1]);
    ho1mrbxphi->GetYaxis()->SetBinLabel(i,HO1MRBXlabel[i-1]); ho1mrbxeta->GetYaxis()->SetBinLabel(i,HO1MRBXlabel[i-1]);
    ho2mrbxphi->GetYaxis()->SetBinLabel(i,HO2MRBXlabel[i-1]); ho2mrbxeta->GetYaxis()->SetBinLabel(i,HO2MRBXlabel[i-1]);
  }

  //ho1prbxeta->SetXTitle(""); ho1prbxeta->SetYTitle("");
  ho0rbxphi->SetStats(0); ho0rbxeta->SetStats(0);
  ho1prbxphi->SetStats(0); ho1prbxeta->SetStats(0);
  ho2prbxphi->SetStats(0); ho2prbxeta->SetStats(0);
  ho1mrbxphi->SetStats(0); ho1mrbxeta->SetStats(0);
  ho2mrbxphi->SetStats(0); ho2mrbxeta->SetStats(0);

  c->cd(1); ho0rbxphi->Draw("colztext"); c->cd(2); ho0rbxeta->Draw("colztext");
  c->cd(3); ho1prbxphi->Draw("colztext"); c->cd(4); ho1prbxeta->Draw("colztext");
  c->cd(5); ho2prbxphi->Draw("colztext"); c->cd(6); ho2prbxeta->Draw("colztext");
  c->cd(7); ho1mrbxphi->Draw("colztext"); c->cd(8); ho1mrbxeta->Draw("colztext");
  c->cd(9); ho2mrbxphi->Draw("colztext"); c->cd(10); ho2mrbxeta->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_HOFEetaphi.png").c_str() );
  c->SaveAs( (dir+"_HOFEetaphi.pdf").c_str() );
  c->SaveAs( (dir+"_HOFEetaphi.C").c_str() );
  c->Close();

  return ;
}

void HOAnalyzer::PlottingHOFEtoBE(
                                  std::vector<HOFrontEnd> myHOFrontEnd,
                                  std::vector<HOBackEnd> myHOBackEnd
                                 )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,5000);
  c->Divide(4,5); c->SetFillColor(0); c->cd();

  TH2D *ho0rbxcrate = new TH2D("ho0rbxcrate", "Crate in HO0 FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO0*NrmHO0, 1, NrbxHO0*NrmHO0+1);
  TH2D *ho0rbxhtr = new TH2D("ho0rbxhtr", "HTR in HO0 FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO0*NrmHO0, 1, NrbxHO0*NrmHO0+1);
  TH2D *ho0rbxfpga = new TH2D("ho0rbxfpga", "FPGA in HO0 FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO0*NrmHO0, 1, NrbxHO0*NrmHO0+1);
  TH2D *ho0rbxhtr_fiber = new TH2D("ho0rbxhtr_fiber", "HTRfiber in HO0 FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO0*NrmHO0, 1, NrbxHO0*NrmHO0+1);
  TH2D *ho1prbxcrate = new TH2D("ho1prbxcrate", "Crate in HO1P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1prbxhtr = new TH2D("ho1prbxhtr", "HTR in HO1P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1prbxfpga = new TH2D("ho1prbxfpga", "FPGA in HO1P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1prbxhtr_fiber = new TH2D("ho1prbxhtr_fiber", "HTRfiber in HO1P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2prbxcrate = new TH2D("ho2prbxcrate", "Crate in HO2P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2prbxhtr = new TH2D("ho2prbxhtr", "HTR in HO2P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2prbxfpga = new TH2D("ho2prbxfpga", "FPGA in HO2P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2prbxhtr_fiber = new TH2D("ho2prbxhtr_fiber", "HTRfiber in HO2P FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1mrbxcrate = new TH2D("ho1mrbxcrate", "Crate in HO1M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1mrbxhtr = new TH2D("ho1mrbxhtr", "HTR in HO1M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1mrbxfpga = new TH2D("ho1mrbxfpga", "FPGA in HO1M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho1mrbxhtr_fiber = new TH2D("ho1mrbxhtr_fiber", "HTRfiber in HO1M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2mrbxcrate = new TH2D("ho2mrbxcrate", "Crate in HO2M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2mrbxhtr = new TH2D("ho2mrbxhtr", "HTR in HO2M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2mrbxfpga = new TH2D("ho2mrbxfpga", "FPGA in HO2M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);
  TH2D *ho2mrbxhtr_fiber = new TH2D("ho2mrbxhtr_fiber", "HTRfiber in HO2M FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHO12*NrmHO12/4, 1, NrbxHO12*NrmHO12/4+1);

  for(auto i=0; i<NchHO_all; i++)
  {
    std::string thisrbx = (myHOFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zcrate = (myHOBackEnd.at(i)).crate;
    double zhtr = (myHOBackEnd.at(i)).htr;
    double zfpga = 2000;
    ((myHOBackEnd.at(i)).fpga)=="top" ? zfpga = 1 : zfpga = -1;
    double zhtr_fiber = (myHOBackEnd.at(i)).htr_fiber;

    double x = ((myHOFrontEnd.at(i)).rm_fiber-2)*3 + (myHOFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....12 for HO0, 2,4,6,8,10,12 for other HO12

    if( thisrbx.find("HO0") != std::string::npos )
    {
      double rmid = -1;//123,234 to 123
      if( rbxid == 1 || rbxid == 4 || rbxid == 5 || rbxid == 8 || rbxid == 9 || rbxid == 12 ) rmid = (myHOFrontEnd.at(i)).rm;
      else rmid = (myHOFrontEnd.at(i)).rm-1;
      double y = (rbxid-1)*3 + rmid;
      //std::cout << x << "," << y << std::endl;
      ho0rbxcrate->Fill(x,y,zcrate); ho0rbxhtr->Fill(x,y,zhtr); ho0rbxfpga->Fill(x,y,zfpga); ho0rbxhtr_fiber->Fill(x,y,zhtr_fiber);
    }
    else
    {
      double rmid = (myHOFrontEnd.at(i)).rm;//1234 to 1234
      double y = (rbxid/2-1)*4 + rmid;

      if( thisrbx.find("HO1P") != std::string::npos )
      {
        ho1prbxcrate->Fill(x,y,zcrate); ho1prbxhtr->Fill(x,y,zhtr); ho1prbxfpga->Fill(x,y,zfpga); ho1prbxhtr_fiber->Fill(x,y,zhtr_fiber);
      }
      else if( thisrbx.find("HO2P") != std::string::npos )
      {
        ho2prbxcrate->Fill(x,y,zcrate); ho2prbxhtr->Fill(x,y,zhtr); ho2prbxfpga->Fill(x,y,zfpga); ho2prbxhtr_fiber->Fill(x,y,zhtr_fiber);
      }
      else if( thisrbx.find("HO1M") != std::string::npos )
      {
        ho1mrbxcrate->Fill(x,y,zcrate); ho1mrbxhtr->Fill(x,y,zhtr); ho1mrbxfpga->Fill(x,y,zfpga); ho1mrbxhtr_fiber->Fill(x,y,zhtr_fiber);
      }
      else if( thisrbx.find("HO2M") != std::string::npos )
      {
        ho2mrbxcrate->Fill(x,y,zcrate); ho2mrbxhtr->Fill(x,y,zhtr); ho2mrbxfpga->Fill(x,y,zfpga); ho2mrbxhtr_fiber->Fill(x,y,zhtr_fiber);
      }
    }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    ho0rbxcrate->GetXaxis()->SetBinLabel(i,HO0RMfiberlabel[i-1]); ho0rbxhtr->GetXaxis()->SetBinLabel(i,HO0RMfiberlabel[i-1]); 
    ho0rbxfpga->GetXaxis()->SetBinLabel(i,HO0RMfiberlabel[i-1]); ho0rbxhtr_fiber->GetXaxis()->SetBinLabel(i,HO0RMfiberlabel[i-1]);

    ho1prbxcrate->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]); ho1prbxhtr->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]);
    ho1prbxfpga->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]); ho1prbxhtr_fiber->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]);

    ho2prbxcrate->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]); ho2prbxhtr->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]);
    ho2prbxfpga->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]); ho2prbxhtr_fiber->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]);

    ho1mrbxcrate->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]); ho1mrbxhtr->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]);
    ho1mrbxfpga->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]); ho1mrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HO1RMfiberlabel[i-1]);

    ho2mrbxcrate->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]); ho2mrbxhtr->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]);
    ho2mrbxfpga->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]); ho2mrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HO2RMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHO0*NrmHO0;i++) 
  { 
    ho0rbxcrate->GetYaxis()->SetBinLabel(i,HO0RBXlabel[i-1]); ho0rbxhtr->GetYaxis()->SetBinLabel(i,HO0RBXlabel[i-1]); 
    ho0rbxfpga->GetYaxis()->SetBinLabel(i,HO0RBXlabel[i-1]); ho0rbxhtr_fiber->GetYaxis()->SetBinLabel(i,HO0RBXlabel[i-1]);
  }
  for(int i=1;i<=NrbxHO12*NrmHO12/4;i++)
  {
    ho1prbxcrate->GetYaxis()->SetBinLabel(i,HO1PRBXlabel[i-1]); ho1prbxhtr->GetYaxis()->SetBinLabel(i,HO1PRBXlabel[i-1]);
    ho1prbxfpga->GetYaxis()->SetBinLabel(i,HO1PRBXlabel[i-1]); ho1prbxhtr_fiber->GetYaxis()->SetBinLabel(i,HO1PRBXlabel[i-1]);

    ho2prbxcrate->GetYaxis()->SetBinLabel(i,HO2PRBXlabel[i-1]); ho2prbxhtr->GetYaxis()->SetBinLabel(i,HO2PRBXlabel[i-1]);
    ho2prbxfpga->GetYaxis()->SetBinLabel(i,HO2PRBXlabel[i-1]); ho2prbxhtr_fiber->GetYaxis()->SetBinLabel(i,HO2PRBXlabel[i-1]);

    ho1mrbxcrate->GetYaxis()->SetBinLabel(i,HO1MRBXlabel[i-1]); ho1mrbxhtr->GetYaxis()->SetBinLabel(i,HO1MRBXlabel[i-1]);
    ho1mrbxfpga->GetYaxis()->SetBinLabel(i,HO1MRBXlabel[i-1]); ho1mrbxhtr_fiber->GetYaxis()->SetBinLabel(i,HO1MRBXlabel[i-1]);

    ho2mrbxcrate->GetYaxis()->SetBinLabel(i,HO2MRBXlabel[i-1]); ho2mrbxhtr->GetYaxis()->SetBinLabel(i,HO2MRBXlabel[i-1]);
    ho2mrbxfpga->GetYaxis()->SetBinLabel(i,HO2MRBXlabel[i-1]); ho2mrbxhtr_fiber->GetYaxis()->SetBinLabel(i,HO2MRBXlabel[i-1]);
  }

  ho0rbxcrate->SetStats(0); ho0rbxhtr->SetStats(0); ho0rbxfpga->SetStats(0); ho0rbxhtr_fiber->SetStats(0);
  ho1prbxcrate->SetStats(0); ho1prbxhtr->SetStats(0); ho1prbxfpga->SetStats(0); ho1prbxhtr_fiber->SetStats(0);
  ho2prbxcrate->SetStats(0); ho2prbxhtr->SetStats(0); ho2prbxfpga->SetStats(0); ho2prbxhtr_fiber->SetStats(0);
  ho1mrbxcrate->SetStats(0); ho1mrbxhtr->SetStats(0); ho1mrbxfpga->SetStats(0); ho1mrbxhtr_fiber->SetStats(0);
  ho2mrbxcrate->SetStats(0); ho2mrbxhtr->SetStats(0); ho2mrbxfpga->SetStats(0); ho2mrbxhtr_fiber->SetStats(0);

  c->cd(1); ho0rbxcrate->Draw("colztext"); c->cd(2); ho0rbxhtr->Draw("colztext"); c->cd(3); ho0rbxfpga->Draw("colztext"); c->cd(4); ho0rbxhtr_fiber->Draw("colztext");
  c->cd(5); ho1prbxcrate->Draw("colztext"); c->cd(6); ho1prbxhtr->Draw("colztext"); c->cd(7); ho1prbxfpga->Draw("colztext"); c->cd(8); ho1prbxhtr_fiber->Draw("colztext");
  c->cd(9); ho2prbxcrate->Draw("colztext"); c->cd(10); ho2prbxhtr->Draw("colztext"); c->cd(11); ho2prbxfpga->Draw("colztext"); c->cd(12); ho2prbxhtr_fiber->Draw("colztext");
  c->cd(13); ho1mrbxcrate->Draw("colztext"); c->cd(14); ho1mrbxhtr->Draw("colztext"); c->cd(15); ho1mrbxfpga->Draw("colztext"); c->cd(16); ho1mrbxhtr_fiber->Draw("colztext");
  c->cd(17); ho2mrbxcrate->Draw("colztext"); c->cd(18); ho2mrbxhtr->Draw("colztext"); c->cd(19); ho2mrbxfpga->Draw("colztext"); c->cd(20); ho2mrbxhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HOFEcratehtrfpgahtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HOFEcratehtrfpgahtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HOFEcratehtrfpgahtr_fiber.C").c_str() );
  c->Close();

  return ;
}
