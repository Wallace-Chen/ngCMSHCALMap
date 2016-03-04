#include <vector>
#include<string>
#include<iostream>

#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

//FrontEnd electronics struct
struct HBFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
};

struct HEFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
};

struct HFFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
};

struct HOFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
};

//Backend electronics struct
struct HBBackEnd
{
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
  int ufedid;
};

struct HEBackEnd
{
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
  int ufedid;
};

struct HFBackEnd
{
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
  int ufedid;
};

struct HOBackEnd
{
  double block_coupler;
  int crate, htr, htr_fiber, fiber_ch;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  //int ucrate, uhtr, uhtr_fiber, fiber_ch;
};

//PMT boxes struct
struct HBPMTBox
{};
struct HEPMTBox
{};
struct HFPMTBox
{};
struct HOPMTBox
{
  int sector;
  int pixel;
  std::string letter_code;
};

//Geometry struct
struct HBGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

struct HEGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

struct HFGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

struct HOGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

//Trigger tower struct
struct HBTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

struct HETriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

struct HFTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

struct HOTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

namespace HOAnalyzer
{
  //2376 channels in HO and HOX
  //Front End variables
  //rbx in HO, different in 0 and 12
  int NrbxHO0 = 1*12;
  int NrbxHO12 = 4*6;
  //3 rm in HO0 while 4 rm in HO1P, HO1M, HO2P, HO2M
  //for HO0 part, 1,4,5,8,10,12, rm is 1,2,3; 2,3,6,7,9,11, rm is 2,3,4
  int NrmHO0 = 3;
  int NrmHO12 = 4;
  //rm fiber 2,3,4,5,6,7, in total 6 fibers per rm
  int Nrm_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  int Nfiber_ch = 3;

  int Nqie = 3;
  int Nqie_ch = 6;

  //Back End variables
  //4 crate in HO: 3,6,7,12
  int Ncrate = 4;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18
  int Nhtr = 12;
  //2 fpga flavors top and bottom
  int Nfpga = 2;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8
  int Nhtr_fiber = 8;
  //216 HOX channels in HO map in total, while 72 special HOX channels with no patch panel attachment, htr slot is 21
  int NspecialHOX = 72;

  //Geimetry variables,2160 channels, side -1 or +1, eta from 1 to 15, phi 1 to 72, depth always 4
  int NHOside = 2;
  int NHOeta = 15;
  int NHOphi = 72;
  int NHOdepth = 1;
  //144 normal HOX channels,only in side -1, eta 4 and eta 15, for all phis
  int NnormalHOX = 2*72;
  //72 special HOX channels, only in side +1, eta 15, for all phis

  void PlottingHOFEtoGeo(
                         std::vector<HOFrontEnd> myHOFrontEnd,
                         std::vector<HOGeometry> myHOGeometry
                        );
}

void HOAnalyzer::PlottingHOFEtoGeo(
                                   std::vector<HOFrontEnd> myHOFrontEnd,
                                   std::vector<HOGeometry> myHOGeometry
                                  )
{
  const int NPhi = 72;
  const int NHO0RBX = 12;

  const std::string titre="CMS HCAL Channel Mapping";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);

  TCanvas *c = new TCanvas("c", "",0,51,1920,1004);
  c->SetFillColor(0);
  c->cd();

  TH2D *ho0rbxphi = new TH2D("ho0rbxphi", "HO0 RBX vs Phi", NPhi, 1, NPhi+1, NHO0RBX, 1, NHO0RBX+1);
  ho0rbxphi->SetMarkerSize(1.2);

  int HOsize = myHOFrontEnd.size();
  //std::cout << HOsize << std::endl;

  for(auto i=0; i<HOsize; i++)
  {
    std::string thisrbx = (myHOFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    //std::cout << (myHOGeometry.at(i)).eta << std::endl;
    if( (myHOGeometry.at(i)).subdet != "HO") continue;    

    if( thisrbx.find("HO0") != std::string::npos )
    {
      double x = (myHOGeometry.at(i)).phi;
      double y = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );
      
      std::cout << x << "," << y << std::endl;
      ho0rbxphi->Fill(x,y);
    }
  }

  const char *HO0RBXylabel[NHO0RBX] = {"HO001","HO002","HO003","HO004",
                                       "HO005","HO006","HO007","HO008",
                                       "HO009","HO010","HO011","HO012"};
  for (int i=1;i<=NPhi;i++) ho0rbxphi->GetXaxis()->SetBinLabel(i,(std::to_string(i)).c_str());
  for (int i=1;i<=NHO0RBX;i++) ho0rbxphi->GetYaxis()->SetBinLabel(i,HO0RBXylabel[i-1]);
  //ho0rbxphi->SetTitle("");
  ho0rbxphi->SetXTitle("iPhi");
  ho0rbxphi->SetYTitle("HO RBX");
  ho0rbxphi->SetStats(0);

  ho0rbxphi->Draw("colztext");
  title->Draw("same");

  std::string dir;
  dir = "LMapvalidationPlots/";
 
  c->SaveAs( (dir+"_horbxphi.png").c_str() );
  c->SaveAs( (dir+"_horbxphi.pdf").c_str() );
  c->SaveAs( (dir+"_horbxphi.C").c_str() );
  c->Close();

  return ;
}
