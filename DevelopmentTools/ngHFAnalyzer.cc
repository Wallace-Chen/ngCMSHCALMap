#include "ngHFAnalyzer.h"

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

    if( thisrbx.find("HFP") != std::string::npos ){ nghfprbxphi->Fill(x,y,zphi); nghfprbxeta->Fill(x,y,zeta); nghfprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("HFM") != std::string::npos ){ nghfmrbxphi->Fill(x,y,zphi); nghfmrbxeta->Fill(x,y,zeta); nghfmrbxdep->Fill(x,y,zdepth); }
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

    if( thisrbx.find("HFP") != std::string::npos ){ hfprbxucrate->Fill(x,y,zucrate); hfprbxuhtr->Fill(x,y,zuhtr); hfprbxufpga->Fill(x,y,zufpga); hfprbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
    else if( thisrbx.find("HFM") != std::string::npos ){ hfmrbxucrate->Fill(x,y,zucrate); hfmrbxuhtr->Fill(x,y,zuhtr); hfmrbxufpga->Fill(x,y,zufpga); hfmrbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
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

