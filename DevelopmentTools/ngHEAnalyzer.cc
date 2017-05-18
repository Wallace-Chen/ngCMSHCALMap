#include "ngHEAnalyzer.h"

void ngHEAnalyzer::PlottingngHEFEtoGeo(
                                       std::vector<ngHEFrontEnd> myngHEFrontEnd,
                                       std::vector<ngHEGeometry> myngHEGeometry
                                      )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(3,2); c->SetFillColor(0); c->cd();

  gStyle->SetTitleFontSize(0.1);

  TH2D *ngheprbxphi = new TH2D("ngheprbxphi", "Phi in ngHEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *ngheprbxeta = new TH2D("ngheprbxeta", "Eta in ngHEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *ngheprbxdep = new TH2D("ngheprbxdep", "Dep in ngHEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);

  TH2D *nghemrbxphi = new TH2D("nghemrbxphi", "Phi in ngHEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *nghemrbxeta = new TH2D("nghemrbxeta", "Eta in ngHEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *nghemrbxdep = new TH2D("nghemrbxdep", "Dep in ngHEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);

  for(auto i=0; i<NchngHE_all; i++)
  {
    std::string thisrbx = (myngHEFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zphi = (myngHEGeometry.at(i)).phi;
    double zeta = (myngHEGeometry.at(i)).side * (myngHEGeometry.at(i)).eta;
    double zdepth = (myngHEGeometry.at(i)).depth;

    double x = ((myngHEFrontEnd.at(i)).rm_fiber-1)*6 + (myngHEFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....18
    double rmid = (myngHEFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;

    if( thisrbx.find("ngHEP") != std::string::npos ){ ngheprbxphi->Fill(x,y,zphi); ngheprbxeta->Fill(x,y,zeta); ngheprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("ngHEM") != std::string::npos ){ nghemrbxphi->Fill(x,y,zphi); nghemrbxeta->Fill(x,y,zeta); nghemrbxdep->Fill(x,y,zdepth); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    ngheprbxphi->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); ngheprbxeta->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); ngheprbxdep->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]);
    nghemrbxphi->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); nghemrbxeta->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); nghemrbxdep->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxngHE*NrmngHE;i++) 
  { 
    ngheprbxphi->GetYaxis()->SetBinLabel(i,ngHEPRBXlabel[i-1]); ngheprbxeta->GetYaxis()->SetBinLabel(i,ngHEPRBXlabel[i-1]); ngheprbxdep->GetYaxis()->SetBinLabel(i,ngHEPRBXlabel[i-1]);
    nghemrbxphi->GetYaxis()->SetBinLabel(i,ngHEMRBXlabel[i-1]); nghemrbxeta->GetYaxis()->SetBinLabel(i,ngHEMRBXlabel[i-1]); nghemrbxdep->GetYaxis()->SetBinLabel(i,ngHEMRBXlabel[i-1]);
  }

  ngheprbxphi->SetStats(0); ngheprbxeta->SetStats(0); ngheprbxdep->SetStats(0);
  nghemrbxphi->SetStats(0); nghemrbxeta->SetStats(0); nghemrbxdep->SetStats(0);

  c->cd(1); ngheprbxphi->Draw("colztext"); c->cd(2); ngheprbxeta->Draw("colztext"); c->cd(3); ngheprbxdep->Draw("colztext");
  c->cd(4); nghemrbxphi->Draw("colztext"); c->cd(5); nghemrbxeta->Draw("colztext"); c->cd(6); nghemrbxdep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_ngHEFEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_ngHEFEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_ngHEFEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

void ngHEAnalyzer::PlottingngHEFEtoBEuTCA(
                                          std::vector<ngHEFrontEnd> myngHEFrontEnd,
                                          std::vector<ngHEBackEnd> myngHEBackEnd
                                         )
{
  TCanvas *c = new TCanvas("c", "",0,51,8000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  gStyle->SetTitleFontSize(0.1);

  TH2D *heprbxucrate = new TH2D("heprbxucrate", "uCrate in ngHEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *heprbxuhtr = new TH2D("heprbxuhtr", "uHTR in ngHEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *heprbxufpga = new TH2D("heprbxufpga", "uFPGA in ngHEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *heprbxuhtr_fiber = new TH2D("heprbxuhtr_fiber", "uHTRfiber in ngHEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *hemrbxucrate = new TH2D("hemrbxucrate", "uCrate in ngHEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *hemrbxuhtr = new TH2D("hemrbxuhtr", "uHTR in ngHEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *hemrbxufpga = new TH2D("hemrbxufpga", "uFPGA in ngHEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);
  TH2D *hemrbxuhtr_fiber = new TH2D("hemrbxuhtr_fiber", "uHTRfiber in ngHEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxngHE*NrmngHE, 1, NrbxngHE*NrmngHE+1);

  for(auto i=0; i<NchngHE_all; i++)
  {
    std::string thisrbx = (myngHEFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zucrate = (myngHEBackEnd.at(i)).ucrate;
    double zuhtr = (myngHEBackEnd.at(i)).uhtr;
    double zufpga = 2000;
    ((myngHEBackEnd.at(i)).ufpga)=="uHTR" ? zufpga = 10 : zufpga = -10;
    double zuhtr_fiber = (myngHEBackEnd.at(i)).uhtr_fiber;

    double x = ((myngHEFrontEnd.at(i)).rm_fiber-1)*6 + (myngHEFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,2,....18
    double rmid = (myngHEFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("ngHEP") != std::string::npos ){ heprbxucrate->Fill(x,y,zucrate); heprbxuhtr->Fill(x,y,zuhtr); heprbxufpga->Fill(x,y,zufpga); heprbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
    else if( thisrbx.find("ngHEM") != std::string::npos ){ hemrbxucrate->Fill(x,y,zucrate); hemrbxuhtr->Fill(x,y,zuhtr); hemrbxufpga->Fill(x,y,zufpga); hemrbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    heprbxucrate->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); heprbxuhtr->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); 
    heprbxufpga->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); heprbxuhtr_fiber->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]);

    hemrbxucrate->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); hemrbxuhtr->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]);
    hemrbxufpga->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]); hemrbxuhtr_fiber->GetXaxis()->SetBinLabel(i,ngHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxngHE*NrmngHE;i++) 
  { 
    heprbxucrate->GetYaxis()->SetBinLabel(i,ngHEPRBXlabel[i-1]); heprbxuhtr->GetYaxis()->SetBinLabel(i,ngHEPRBXlabel[i-1]); 
    heprbxufpga->GetYaxis()->SetBinLabel(i,ngHEPRBXlabel[i-1]); heprbxuhtr_fiber->GetYaxis()->SetBinLabel(i,ngHEPRBXlabel[i-1]);
    
    hemrbxucrate->GetYaxis()->SetBinLabel(i,ngHEMRBXlabel[i-1]); hemrbxuhtr->GetYaxis()->SetBinLabel(i,ngHEMRBXlabel[i-1]);
    hemrbxufpga->GetYaxis()->SetBinLabel(i,ngHEMRBXlabel[i-1]); hemrbxuhtr_fiber->GetYaxis()->SetBinLabel(i,ngHEMRBXlabel[i-1]);
  }

  heprbxucrate->SetStats(0); heprbxuhtr->SetStats(0); heprbxufpga->SetStats(0); heprbxuhtr_fiber->SetStats(0);
  hemrbxucrate->SetStats(0); hemrbxuhtr->SetStats(0); hemrbxufpga->SetStats(0); hemrbxuhtr_fiber->SetStats(0);

  c->cd(1); heprbxucrate->Draw("colztext"); c->cd(2); heprbxuhtr->Draw("colztext"); c->cd(3); heprbxufpga->Draw("colztext"); c->cd(4); heprbxuhtr_fiber->Draw("colztext");
  c->cd(5); hemrbxucrate->Draw("colztext"); c->cd(6); hemrbxuhtr->Draw("colztext"); c->cd(7); hemrbxufpga->Draw("colztext"); c->cd(8); hemrbxuhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_ngHEFEucrateuhtrufpgauhtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_ngHEFEucrateuhtrufpgauhtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_ngHEFEucrateuhtrufpgauhtr_fiber.C").c_str() );
  c->Close();

  return ;
}

void ngHEAnalyzer::PlottingngHEBEuTCAtoGeo(
                                           std::vector<ngHEBackEnd> myngHEBackEnd,
                                           std::vector<ngHEGeometry> myngHEGeometry
                                          )
{
  TCanvas *c = new TCanvas("c", "",0,51,2000,6000);
  c->Divide(1,3); c->SetFillColor(0); c->cd();

  gStyle->SetTitleFontSize(0.1);

  TH2D *nghebephi = new TH2D("nghebephi", "Phi in ngHE BackEnd", Nuhtr_fiber*Nfiber_ch, 1, Nuhtr_fiber*Nfiber_ch+1, Ncrate*Nuhtr, 1, Ncrate*Nuhtr+1);
  TH2D *nghebeeta = new TH2D("nghebeeta", "Eta in ngHE BackEnd", Nuhtr_fiber*Nfiber_ch, 1, Nuhtr_fiber*Nfiber_ch+1, Ncrate*Nuhtr, 1, Ncrate*Nuhtr+1);
  TH2D *nghebedep = new TH2D("nghebedep", "Dep in ngHE BackEnd", Nuhtr_fiber*Nfiber_ch, 1, Nuhtr_fiber*Nfiber_ch+1, Ncrate*Nuhtr, 1, Ncrate*Nuhtr+1);

  for(auto i=0; i<NchngHE_all; i++)
  {
    double zphi = (myngHEGeometry.at(i)).phi;
    double zeta = (myngHEGeometry.at(i)).side * (myngHEGeometry.at(i)).eta;
    double zdepth = (myngHEGeometry.at(i)).depth;

    double x = (myngHEBackEnd.at(i)).uhtr_fiber*6 + (myngHEBackEnd.at(i)).fiber_ch + 1;
    double crateid = -1;
    //20,21,24,25,30,31,34,35,37
    if      ((myngHEBackEnd.at(i)).ucrate==20) crateid = 0; 
    else if ((myngHEBackEnd.at(i)).ucrate==21) crateid = 1; 
    else if ((myngHEBackEnd.at(i)).ucrate==24) crateid = 2;
    else if ((myngHEBackEnd.at(i)).ucrate==25) crateid = 3;
    else if ((myngHEBackEnd.at(i)).ucrate==30) crateid = 4;
    else if ((myngHEBackEnd.at(i)).ucrate==31) crateid = 5;
    else if ((myngHEBackEnd.at(i)).ucrate==34) crateid = 6;
    else if ((myngHEBackEnd.at(i)).ucrate==35) crateid = 7;
    else crateid = 8;
    double y = crateid*12 + (myngHEBackEnd.at(i)).uhtr;
    nghebephi->Fill(x,y,zphi); nghebeeta->Fill(x,y,zeta); nghebedep->Fill(x,y,zdepth);
  }

  for(int i=1;i<=Nuhtr_fiber*Nfiber_ch;i++)
  { 
    nghebephi->GetXaxis()->SetBinLabel(i,ngHEFiberFiberChannellabel[i-1]); nghebeeta->GetXaxis()->SetBinLabel(i,ngHEFiberFiberChannellabel[i-1]); nghebedep->GetXaxis()->SetBinLabel(i,ngHEFiberFiberChannellabel[i-1]);
  }
  for(int i=1;i<=Ncrate*Nuhtr;i++) 
  { 
    nghebephi->GetYaxis()->SetBinLabel(i,ngHECrateSlotlabel[i-1]); nghebeeta->GetYaxis()->SetBinLabel(i,ngHECrateSlotlabel[i-1]); nghebedep->GetYaxis()->SetBinLabel(i,ngHECrateSlotlabel[i-1]);
  }

  nghebephi->SetStats(0); nghebeeta->SetStats(0); nghebedep->SetStats(0);

  c->cd(1); nghebephi->Draw("colztext"); c->cd(2); nghebeeta->Draw("colztext"); c->cd(3); nghebedep->Draw("colztext");

  c->SaveAs( (dir+"_ngHEBEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_ngHEBEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_ngHEBEetaphidepth.C").c_str() );
  c->Close();

  return ;
}
