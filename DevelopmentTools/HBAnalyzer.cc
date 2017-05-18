#include "HBAnalyzer.h"

void HBAnalyzer::HBNChannelBasicCheck()
{
  std::cout << "How many Channels do we have in HB ? " << NchHB_all << std::endl;
  std::cout << "Re-calculate from Front End: " << 2 * NrbxHB * NrmHB * Nrm_fiber * Nfiber_ch << std::endl;
  std::cout << "Re-calculate from Back End(VME): " << Ncrate * Nhtr * Nfpga * Nhtr_fiber * Nfiber_ch/2 << std::endl;
  std::cout << "Re-calculate from Back End(uTCA): " << Ncrate * Nuhtr * Nufpga * Nuhtr_fiber * Nfiber_ch/2 << std::endl;
  //std::cout << "Re-calculate from Geometry: " << NHBHEside * (NHBeta1to14 * NHBdeptheta1to14 + NHBeta1516 * NHBdeptheta1516 + ) * NHBHEphi << std::endl;
  return ;
}

void HBAnalyzer::PlottingHBFEtoGeo(
                                   std::vector<HBFrontEnd> myHBFrontEnd,
                                   std::vector<HBGeometry> myHBGeometry
                                  )
{
  TCanvas *c = new TCanvas("c", "",0,51,4500,6000);
  c->Divide(3,2); c->SetFillColor(0); c->cd();

  TH2D *hbprbxphi = new TH2D("hbprbxphi", "Phi in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxeta = new TH2D("hbprbxeta", "Eta in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxdep = new TH2D("hbprbxdep", "Dep in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);

  TH2D *hbmrbxphi = new TH2D("hbmrbxphi", "Phi in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxeta = new TH2D("hbmrbxeta", "Eta in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxdep = new TH2D("hbmrbxdep", "Dep in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);

  for(auto i=0; i<(NchHB_all); i++)
  {
    std::string thisrbx = (myHBFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zphi = (myHBGeometry.at(i)).phi;
    double zeta = (myHBGeometry.at(i)).side * (myHBGeometry.at(i)).eta;
    double zdepth = (myHBGeometry.at(i)).depth;

    double x = ((myHBFrontEnd.at(i)).rm_fiber-2)*3 + (myHBFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....18
    double rmid = (myHBFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;

    if( thisrbx.find("HBP") != std::string::npos ){ hbprbxphi->Fill(x,y,zphi); hbprbxeta->Fill(x,y,zeta); hbprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("HBM") != std::string::npos ){ hbmrbxphi->Fill(x,y,zphi); hbmrbxeta->Fill(x,y,zeta); hbmrbxdep->Fill(x,y,zdepth); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hbprbxphi->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbprbxeta->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbprbxdep->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]);
    hbmrbxphi->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbmrbxeta->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbmrbxdep->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHB*NrmHB;i++) 
  { 
    hbprbxphi->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxeta->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxdep->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]);
    hbmrbxphi->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxeta->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxdep->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
  }

  hbprbxphi->SetStats(0); hbprbxeta->SetStats(0); hbprbxdep->SetStats(0);
  hbmrbxphi->SetStats(0); hbmrbxeta->SetStats(0); hbmrbxdep->SetStats(0);

  c->cd(1); hbprbxphi->Draw("colztext"); c->cd(2); hbprbxeta->Draw("colztext"); c->cd(3); hbprbxdep->Draw("colztext");
  c->cd(4); hbmrbxphi->Draw("colztext"); c->cd(5); hbmrbxeta->Draw("colztext"); c->cd(6); hbmrbxdep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_HBFEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_HBFEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_HBFEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

void HBAnalyzer::PlottingHBFEtoBEVME(
                                     std::vector<HBFrontEnd> myHBFrontEnd,
                                     std::vector<HBBackEnd> myHBBackEnd
                                    )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *hbprbxcrate = new TH2D("hbprbxcrate", "Crate in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxhtr = new TH2D("hbprbxhtr", "HTR in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxfpga = new TH2D("hbprbxfpga", "FPGA in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxhtr_fiber = new TH2D("hbprbxhtr_fiber", "HTRfiber in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxcrate = new TH2D("hbmrbxcrate", "Crate in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxhtr = new TH2D("hbmrbxhtr", "HTR in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxfpga = new TH2D("hbmrbxfpga", "FPGA in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxhtr_fiber = new TH2D("hbmrbxhtr_fiber", "HTRfiber in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);

  for(auto i=0; i<NchHB_all; i++)
  {
    std::string thisrbx = (myHBFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zcrate = (myHBBackEnd.at(i)).crate;
    double zhtr = (myHBBackEnd.at(i)).htr;
    double zfpga = 2000;
    ((myHBBackEnd.at(i)).fpga)=="top" ? zfpga = 1 : zfpga = -1;
    double zhtr_fiber = (myHBBackEnd.at(i)).htr_fiber;

    double x = ((myHBFrontEnd.at(i)).rm_fiber-2)*3 + (myHBFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,2,....18
    double rmid = (myHBFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("HBP") != std::string::npos ){ hbprbxcrate->Fill(x,y,zcrate); hbprbxhtr->Fill(x,y,zhtr); hbprbxfpga->Fill(x,y,zfpga); hbprbxhtr_fiber->Fill(x,y,zhtr_fiber); }
    else if( thisrbx.find("HBM") != std::string::npos ){ hbmrbxcrate->Fill(x,y,zcrate); hbmrbxhtr->Fill(x,y,zhtr); hbmrbxfpga->Fill(x,y,zfpga); hbmrbxhtr_fiber->Fill(x,y,zhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hbprbxcrate->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbprbxhtr->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); 
    hbprbxfpga->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbprbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]);

    hbmrbxcrate->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbmrbxhtr->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]);
    hbmrbxfpga->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbmrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHB*NrmHB;i++) 
  { 
    hbprbxcrate->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxhtr->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); 
    hbprbxfpga->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxhtr_fiber->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]);
    
    hbmrbxcrate->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxhtr->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
    hbmrbxfpga->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxhtr_fiber->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
  }

  hbprbxcrate->SetStats(0); hbprbxhtr->SetStats(0); hbprbxfpga->SetStats(0); hbprbxhtr_fiber->SetStats(0);
  hbmrbxcrate->SetStats(0); hbmrbxhtr->SetStats(0); hbmrbxfpga->SetStats(0); hbmrbxhtr_fiber->SetStats(0);

  c->cd(1); hbprbxcrate->Draw("colztext"); c->cd(2); hbprbxhtr->Draw("colztext"); c->cd(3); hbprbxfpga->Draw("colztext"); c->cd(4); hbprbxhtr_fiber->Draw("colztext");
  c->cd(5); hbmrbxcrate->Draw("colztext"); c->cd(6); hbmrbxhtr->Draw("colztext"); c->cd(7); hbmrbxfpga->Draw("colztext"); c->cd(8); hbmrbxhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HBFEcratehtrfpgahtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HBFEcratehtrfpgahtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HBFEcratehtrfpgahtr_fiber.C").c_str() );
  c->Close();

  return ;
}

void HBAnalyzer::PlottingHBFEtoBEuTCA(
                                      std::vector<HBFrontEnd> myHBFrontEnd,
                                      std::vector<HBBackEnd> myHBBackEnd
                                     )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *hbprbxucrate = new TH2D("hbprbxucrate", "uCrate in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxuhtr = new TH2D("hbprbxuhtr", "uHTR in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxufpga = new TH2D("hbprbxufpga", "uFPGA in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxuhtr_fiber = new TH2D("hbprbxuhtr_fiber", "uHTRfiber in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxucrate = new TH2D("hbmrbxucrate", "uCrate in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxuhtr = new TH2D("hbmrbxuhtr", "uHTR in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxufpga = new TH2D("hbmrbxufpga", "uFPGA in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxuhtr_fiber = new TH2D("hbmrbxuhtr_fiber", "uHTRfiber in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);

  for(auto i=0; i<NchHB_all; i++)
  {
    std::string thisrbx = (myHBFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zucrate = (myHBBackEnd.at(i)).ucrate;
    double zuhtr = (myHBBackEnd.at(i)).uhtr;
    double zufpga = 2000;
    ((myHBBackEnd.at(i)).ufpga)=="uHTR" ? zufpga = 10 : zufpga = -10;
    double zuhtr_fiber = (myHBBackEnd.at(i)).uhtr_fiber;

    double x = ((myHBFrontEnd.at(i)).rm_fiber-2)*3 + (myHBFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,2,....18
    double rmid = (myHBFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("HBP") != std::string::npos ){ hbprbxucrate->Fill(x,y,zucrate); hbprbxuhtr->Fill(x,y,zuhtr); hbprbxufpga->Fill(x,y,zufpga); hbprbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
    else if( thisrbx.find("HBM") != std::string::npos ){ hbmrbxucrate->Fill(x,y,zucrate); hbmrbxuhtr->Fill(x,y,zuhtr); hbmrbxufpga->Fill(x,y,zufpga); hbmrbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hbprbxucrate->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbprbxuhtr->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); 
    hbprbxufpga->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbprbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]);

    hbmrbxucrate->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbmrbxuhtr->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]);
    hbmrbxufpga->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]); hbmrbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBRMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHB*NrmHB;i++) 
  { 
    hbprbxucrate->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxuhtr->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); 
    hbprbxufpga->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]);
    
    hbmrbxucrate->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxuhtr->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
    hbmrbxufpga->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
  }

  hbprbxucrate->SetStats(0); hbprbxuhtr->SetStats(0); hbprbxufpga->SetStats(0); hbprbxuhtr_fiber->SetStats(0);
  hbmrbxucrate->SetStats(0); hbmrbxuhtr->SetStats(0); hbmrbxufpga->SetStats(0); hbmrbxuhtr_fiber->SetStats(0);

  c->cd(1); hbprbxucrate->Draw("colztext"); c->cd(2); hbprbxuhtr->Draw("colztext"); c->cd(3); hbprbxufpga->Draw("colztext"); c->cd(4); hbprbxuhtr_fiber->Draw("colztext");
  c->cd(5); hbmrbxucrate->Draw("colztext"); c->cd(6); hbmrbxuhtr->Draw("colztext"); c->cd(7); hbmrbxufpga->Draw("colztext"); c->cd(8); hbmrbxuhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HBFEucrateuhtrufpgauhtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HBFEucrateuhtrufpgauhtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HBFEucrateuhtrufpgauhtr_fiber.C").c_str() );
  c->Close();

  return ;
}
