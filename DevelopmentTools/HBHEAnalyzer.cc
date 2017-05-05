#include "HBHEAnalyzer.h"

void HBHEAnalyzer::HBHENChannelBasicCheck()
{
  std::cout << "How many Channels do we have in HBHE ? " << NchHBHE_all << std::endl;
  std::cout << "Re-calculate from Front End: " << 2 * (NrbxHB * NrmHB + NrbxHE * NrmHE) * Nrm_fiber * Nfiber_ch << std::endl;
  std::cout << "Re-calculate from Back End(VME): " << Ncrate * Nhtr * Nfpga * Nhtr_fiber * Nfiber_ch << std::endl;
  std::cout << "Re-calculate from Back End(uTCA): " << Ncrate * Nuhtr * Nufpga * Nuhtr_fiber * Nfiber_ch << std::endl;
  //std::cout << "Re-calculate from Geometry: " << NHBHEside * (NHBeta1to14 * NHBdeptheta1to14 + NHBeta1516 * NHBdeptheta1516 + ) * NHBHEphi << std::endl;
  return ;
}

void HBHEAnalyzer::PlottingHBFEtoGeo(
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

  for(auto i=0; i<(NchHBHE_all/2); i++)
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
    hbprbxphi->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxeta->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxdep->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hbmrbxphi->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxeta->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxdep->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
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

void HBHEAnalyzer::PlottingHEFEtoGeo(
                                     std::vector<HEFrontEnd> myHEFrontEnd,
                                     std::vector<HEGeometry> myHEGeometry
                                    )
{
  TCanvas *c = new TCanvas("c", "",0,51,4500,6000);
  c->Divide(3,2); c->SetFillColor(0); c->cd();

  TH2D *heprbxphi = new TH2D("heprbxphi", "Phi in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxeta = new TH2D("heprbxeta", "Eta in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxdep = new TH2D("heprbxdep", "Dep in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);

  TH2D *hemrbxphi = new TH2D("hemrbxphi", "Phi in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxeta = new TH2D("hemrbxeta", "Eta in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxdep = new TH2D("hemrbxdep", "Dep in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);

  for(auto i=0; i<(NchHBHE_all/2); i++)
  {
    std::string thisrbx = (myHEFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zphi = (myHEGeometry.at(i)).phi;
    double zeta = (myHEGeometry.at(i)).side * (myHEGeometry.at(i)).eta;
    double zdepth = (myHEGeometry.at(i)).depth;

    double x = ((myHEFrontEnd.at(i)).rm_fiber-2)*3 + (myHEFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....18
    double rmid = (myHEFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;

    if( thisrbx.find("HEP") != std::string::npos ){ heprbxphi->Fill(x,y,zphi); heprbxeta->Fill(x,y,zeta); heprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("HEM") != std::string::npos ){ hemrbxphi->Fill(x,y,zphi); hemrbxeta->Fill(x,y,zeta); hemrbxdep->Fill(x,y,zdepth); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    heprbxphi->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxeta->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxdep->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hemrbxphi->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxeta->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxdep->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHE*NrmHE;i++) 
  { 
    heprbxphi->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxeta->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxdep->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]);
    hemrbxphi->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxeta->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxdep->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
  }

  heprbxphi->SetStats(0); heprbxeta->SetStats(0); heprbxdep->SetStats(0);
  hemrbxphi->SetStats(0); hemrbxeta->SetStats(0); hemrbxdep->SetStats(0);

  c->cd(1); heprbxphi->Draw("colztext"); c->cd(2); heprbxeta->Draw("colztext"); c->cd(3); heprbxdep->Draw("colztext");
  c->cd(4); hemrbxphi->Draw("colztext"); c->cd(5); hemrbxeta->Draw("colztext"); c->cd(6); hemrbxdep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_HEFEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_HEFEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_HEFEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

void HBHEAnalyzer::PlottingHBFEtoBEVME(
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

  for(auto i=0; i<NchHBHE_all/2; i++)
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
    hbprbxcrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); 
    hbprbxfpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);

    hbmrbxcrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hbmrbxfpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
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

void HBHEAnalyzer::PlottingHEFEtoBEVME(
                                       std::vector<HEFrontEnd> myHEFrontEnd,
                                       std::vector<HEBackEnd> myHEBackEnd
                                      )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *heprbxcrate = new TH2D("heprbxcrate", "Crate in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxhtr = new TH2D("heprbxhtr", "HTR in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxfpga = new TH2D("heprbxfpga", "FPGA in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxhtr_fiber = new TH2D("heprbxhtr_fiber", "HTRfiber in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxcrate = new TH2D("hemrbxcrate", "Crate in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxhtr = new TH2D("hemrbxhtr", "HTR in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxfpga = new TH2D("hemrbxfpga", "FPGA in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxhtr_fiber = new TH2D("hemrbxhtr_fiber", "HTRfiber in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);

  for(auto i=0; i<NchHBHE_all/2; i++)
  {
    std::string thisrbx = (myHEFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zcrate = (myHEBackEnd.at(i)).crate;
    double zhtr = (myHEBackEnd.at(i)).htr;
    double zfpga = 2000;
    ((myHEBackEnd.at(i)).fpga)=="top" ? zfpga = 1 : zfpga = -1;
    double zhtr_fiber = (myHEBackEnd.at(i)).htr_fiber;

    double x = ((myHEFrontEnd.at(i)).rm_fiber-2)*3 + (myHEFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....18
    double rmid = (myHEFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("HEP") != std::string::npos ){ heprbxcrate->Fill(x,y,zcrate); heprbxhtr->Fill(x,y,zhtr); heprbxfpga->Fill(x,y,zfpga); heprbxhtr_fiber->Fill(x,y,zhtr_fiber); }
    else if( thisrbx.find("HEM") != std::string::npos ){ hemrbxcrate->Fill(x,y,zcrate); hemrbxhtr->Fill(x,y,zhtr); hemrbxfpga->Fill(x,y,zfpga); hemrbxhtr_fiber->Fill(x,y,zhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    heprbxcrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); 
    heprbxfpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);

    hemrbxcrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hemrbxfpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHE*NrmHE;i++) 
  { 
    heprbxcrate->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxhtr->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); 
    heprbxfpga->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxhtr_fiber->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]);
    
    hemrbxcrate->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxhtr->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
    hemrbxfpga->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxhtr_fiber->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
  }

  heprbxcrate->SetStats(0); heprbxhtr->SetStats(0); heprbxfpga->SetStats(0); heprbxhtr_fiber->SetStats(0);
  hemrbxcrate->SetStats(0); hemrbxhtr->SetStats(0); hemrbxfpga->SetStats(0); hemrbxhtr_fiber->SetStats(0);

  c->cd(1); heprbxcrate->Draw("colztext"); c->cd(2); heprbxhtr->Draw("colztext"); c->cd(3); heprbxfpga->Draw("colztext"); c->cd(4); heprbxhtr_fiber->Draw("colztext");
  c->cd(5); hemrbxcrate->Draw("colztext"); c->cd(6); hemrbxhtr->Draw("colztext"); c->cd(7); hemrbxfpga->Draw("colztext"); c->cd(8); hemrbxhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HEFEcratehtrfpgahtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HEFEcratehtrfpgahtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HEFEcratehtrfpgahtr_fiber.C").c_str() );
  c->Close();

  return ;
}

void HBHEAnalyzer::PlottingHBFEtoBEuTCA(
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

  for(auto i=0; i<NchHBHE_all/2; i++)
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
    hbprbxucrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxuhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); 
    hbprbxufpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);

    hbmrbxucrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxuhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hbmrbxufpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
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

void HBHEAnalyzer::PlottingHEFEtoBEuTCA(
                                        std::vector<HEFrontEnd> myHEFrontEnd,
                                        std::vector<HEBackEnd> myHEBackEnd
                                       )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *heprbxucrate = new TH2D("heprbxucrate", "uCrate in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxuhtr = new TH2D("heprbxuhtr", "uHTR in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxufpga = new TH2D("heprbxufpga", "uFPGA in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxuhtr_fiber = new TH2D("heprbxuhtr_fiber", "uHTRfiber in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxucrate = new TH2D("hemrbxucrate", "uCrate in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxuhtr = new TH2D("hemrbxuhtr", "uHTR in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxufpga = new TH2D("hemrbxufpga", "uFPGA in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxuhtr_fiber = new TH2D("hemrbxuhtr_fiber", "uHTRfiber in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);

  for(auto i=0; i<NchHBHE_all/2; i++)
  {
    std::string thisrbx = (myHEFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zucrate = (myHEBackEnd.at(i)).ucrate;
    double zuhtr = (myHEBackEnd.at(i)).uhtr;
    double zufpga = 2000;
    ((myHEBackEnd.at(i)).ufpga)=="uHTR" ? zufpga = 10 : zufpga = -10;
    double zuhtr_fiber = (myHEBackEnd.at(i)).uhtr_fiber;

    double x = ((myHEFrontEnd.at(i)).rm_fiber-2)*3 + (myHEFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,2,....18
    double rmid = (myHEFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("HEP") != std::string::npos ){ heprbxucrate->Fill(x,y,zucrate); heprbxuhtr->Fill(x,y,zuhtr); heprbxufpga->Fill(x,y,zufpga); heprbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
    else if( thisrbx.find("HEM") != std::string::npos ){ hemrbxucrate->Fill(x,y,zucrate); hemrbxuhtr->Fill(x,y,zuhtr); hemrbxufpga->Fill(x,y,zufpga); hemrbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    heprbxucrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxuhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); 
    heprbxufpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);

    hemrbxucrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxuhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hemrbxufpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHE*NrmHE;i++) 
  { 
    heprbxucrate->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxuhtr->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); 
    heprbxufpga->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]);
    
    hemrbxucrate->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxuhtr->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
    hemrbxufpga->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
  }

  heprbxucrate->SetStats(0); heprbxuhtr->SetStats(0); heprbxufpga->SetStats(0); heprbxuhtr_fiber->SetStats(0);
  hemrbxucrate->SetStats(0); hemrbxuhtr->SetStats(0); hemrbxufpga->SetStats(0); hemrbxuhtr_fiber->SetStats(0);

  c->cd(1); heprbxucrate->Draw("colztext"); c->cd(2); heprbxuhtr->Draw("colztext"); c->cd(3); heprbxufpga->Draw("colztext"); c->cd(4); heprbxuhtr_fiber->Draw("colztext");
  c->cd(5); hemrbxucrate->Draw("colztext"); c->cd(6); hemrbxuhtr->Draw("colztext"); c->cd(7); hemrbxufpga->Draw("colztext"); c->cd(8); hemrbxuhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HEFEucrateuhtrufpgauhtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HEFEucrateuhtrufpgauhtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HEFEucrateuhtrufpgauhtr_fiber.C").c_str() );
  c->Close();

  return ;
}

