#include <vector>
#include <iostream>

#include "ngHFMappingObject.h"

class ngHFMappingAlgorithm : public ngHFConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHFFrontEnd> myngHFFrontEnd; std::vector<ngHFBackEnd> myngHFBackEnd; std::vector<ngHFPMTBox> myngHFPMTBox; std::vector<ngHFGeometry> myngHFGeometry; std::vector<ngHFTriggerTower> myngHFTriggerTower;
  void SplitngHFfromOldHF(std::vector<HFFrontEnd> myHFFrontEnd, std::vector<HFBackEnd> myHFBackEnd, std::vector<HFPMTBox> myHFPMTBox, std::vector<HFGeometry> myHFGeometry, std::vector<HFTriggerTower> myHFTriggerTower);
  //void ConstructngHFLMapObject();
 private:
  //void ConstructngHFFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  //void ConstructngHFBackEnd(int sideid, int rbxrmid, int rmfifichid);      
  //void ConstructngHFGeometry(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHFPMTBox(int rbxqie10id, int qie10_chid, int s_coax_qie, int r_coax_qie);
  //void ConstructngHFTriggerTower();  
  const int ngHFqie10Inrbxqie10id[Nqie10] = {3,4,5,6,10,11,12,13,14};
};

void ngHFMappingAlgorithm::SplitngHFfromOldHF(
                                              std::vector<HFFrontEnd> myHFFrontEnd, std::vector<HFBackEnd> myHFBackEnd, std::vector<HFPMTBox> myHFPMTBox, std::vector<HFGeometry> myHFGeometry, std::vector<HFTriggerTower> myHFTriggerTower
                                             )
{
  std::cout << "#Splitting ngHF LMap Object from old HF LMap..." << std::endl;
  
  for(auto i=0; i<myHFFrontEnd.size(); i++)
  {
    ngHFFrontEnd thisngHFFrontEnd;
    ngHFBackEnd thisngHFBackEnd;
    ngHFGeometry thisngHFGeometry;
    ngHFPMTBox thisngHFPMTBox;
    ngHFTriggerTower thisngHFTriggerTower;

    //fill 3 ngHF FrontEnd variables from old HF: ngrbx, qie10 and qie10_ch
    std::string thisrbx = myHFFrontEnd.at(i).rbx;
    int rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//HF, 1,2,...12
    int rmid = myHFFrontEnd.at(i).rm;
    int rbxrmqie8id = ((rbxid-1)*3+rmid-1)*4 + myHFFrontEnd.at(i).qie8-1;//HF 0,...143
    int rbxqie10id = rbxrmqie8id/2;//0,1,...71 for QIE10 cards
    int qie10_chid = ((myHFFrontEnd.at(i).qie8-1)%2) * 12 + myHFFrontEnd.at(i).qie8_ch * 2;

    thisngHFFrontEnd.qie10 = ngHFqie10Inrbxqie10id[rbxqie10id%9];//3,4,5,6, 10,11,12,13,14
    thisngHFFrontEnd.qie10_ch = ((myHFFrontEnd.at(i).qie8-1)%2) * 12 + myHFFrontEnd.at(i).qie8_ch * 2 + 1;//1,3,5,7,9...23////
    thisngHFFrontEnd.qie10_ch <= 12 ? thisngHFFrontEnd.s_coax_qie = thisngHFFrontEnd.qie10_ch * 2 : thisngHFFrontEnd.s_coax_qie = (thisngHFFrontEnd.qie10_ch-12) * 2;////
    thisngHFFrontEnd.qie10_ch <= 12 ? thisngHFFrontEnd.r_coax_qie = thisngHFFrontEnd.qie10_ch * 2 - 1 : thisngHFFrontEnd.r_coax_qie = (thisngHFFrontEnd.qie10_ch-12) * 2 - 1;////
    
    int ngrbxid = rbxqie10id/9;      
    std::string sideletter; myHFGeometry.at(i).side>0 ? sideletter = "P" : sideletter = "M";
    std::string numberletter; ngrbxid+1 < 10 ? numberletter = "0" + std::to_string(ngrbxid+1) : numberletter = std::to_string(ngrbxid+1);
    thisngHFFrontEnd.rbx = "ngHF" + sideletter + numberletter;
    //derive other ngHF FrontEnd variables from the 3 base variables
    thisngHFFrontEnd.qie10_fiber = (thisngHFFrontEnd.qie10_ch-1)/4 + 4;//
    thisngHFFrontEnd.fiber_ch = (thisngHFFrontEnd.qie10_ch-1)%4;//

    //copy part of backend variables
    thisngHFBackEnd.ucrate = myHFBackEnd.at(i).ucrate;
    thisngHFBackEnd.uhtr = myHFBackEnd.at(i).uhtr;
    thisngHFBackEnd.ufpga = myHFBackEnd.at(i).ufpga;
    thisngHFBackEnd.uhtr_fiber = (rbxqie10id%4)*6 + (thisngHFFrontEnd.qie10_ch-1)/4;//
    thisngHFBackEnd.fiber_ch = thisngHFFrontEnd.fiber_ch;//
    //copy geometry variables
    thisngHFGeometry.eta = myHFGeometry.at(i).eta;
    thisngHFGeometry.phi = myHFGeometry.at(i).phi;
    thisngHFGeometry.depth = myHFGeometry.at(i).depth;////
    thisngHFGeometry.side = myHFGeometry.at(i).side;
    thisngHFGeometry.dphi = myHFGeometry.at(i).dphi;
    thisngHFGeometry.subdet = myHFGeometry.at(i).subdet;

    myngHFFrontEnd.push_back(thisngHFFrontEnd);
    myngHFBackEnd.push_back(thisngHFBackEnd);
    myngHFGeometry.push_back(thisngHFGeometry);
    ConstructngHFPMTBox(rbxqie10id, qie10_chid,thisngHFFrontEnd.s_coax_qie,thisngHFFrontEnd.r_coax_qie);
    //myngHFPMTBox.push_back(thisngHFPMTBox);
    myngHFTriggerTower.push_back(thisngHFTriggerTower);

    //split to another channels, reset some variables
    qie10_chid++;
    thisngHFFrontEnd.qie10_ch++;//2,4,6,8,10...24
    thisngHFFrontEnd.qie10_ch <= 12 ? thisngHFFrontEnd.s_coax_qie = thisngHFFrontEnd.qie10_ch * 2 : thisngHFFrontEnd.s_coax_qie = (thisngHFFrontEnd.qie10_ch-12) * 2;////
    thisngHFFrontEnd.qie10_ch <= 12 ? thisngHFFrontEnd.r_coax_qie = thisngHFFrontEnd.qie10_ch * 2 - 1 : thisngHFFrontEnd.r_coax_qie = (thisngHFFrontEnd.qie10_ch-12) * 2 - 1;////

    myHFGeometry.at(i).depth == 1 ? thisngHFGeometry.depth=4 : thisngHFGeometry.depth=3;
    
    thisngHFFrontEnd.qie10_fiber = (thisngHFFrontEnd.qie10_ch-1)/4 + 4;
    thisngHFFrontEnd.fiber_ch = (thisngHFFrontEnd.qie10_ch-1)%4;
    thisngHFBackEnd.uhtr_fiber = (rbxqie10id%4)*6 + (thisngHFFrontEnd.qie10_ch-1)/4;
    thisngHFBackEnd.fiber_ch = thisngHFFrontEnd.fiber_ch;

    myngHFFrontEnd.push_back(thisngHFFrontEnd);
    myngHFBackEnd.push_back(thisngHFBackEnd);
    myngHFGeometry.push_back(thisngHFGeometry);
    ConstructngHFPMTBox(rbxqie10id, qie10_chid,thisngHFFrontEnd.s_coax_qie,thisngHFFrontEnd.r_coax_qie);
    //myngHFPMTBox.push_back(thisngHFPMTBox);
    myngHFTriggerTower.push_back(thisngHFTriggerTower);
  }
  
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFPMTBox(int rbxqie10id, int qie10_chid, int s_coax_qie, int r_coax_qie)
{
  ngHFPMTBox thisngHFPMTBox;

  thisngHFPMTBox.pmt = rbxqie10id/2+1;//from 0,...71 QIE10 to pmt 1,...36
  thisngHFPMTBox.pmt%2!=0 ? thisngHFPMTBox.pmt_type = "A" : thisngHFPMTBox.pmt_type = "B";//unsymmetric for F P side. Be careful
  thisngHFPMTBox.winchester_cable = (rbxqie10id%2)*2 + (qie10_chid)/12 + 1;
  s_coax_qie <= 12 ? thisngHFPMTBox.s_coax_pmt = 12 - s_coax_qie + 1 : thisngHFPMTBox.s_coax_pmt = 24 - s_coax_qie + 13;
  r_coax_qie <= 12 ? thisngHFPMTBox.r_coax_pmt = 12 - r_coax_qie + 1 : thisngHFPMTBox.r_coax_pmt = 24 - r_coax_qie + 13;

  thisngHFPMTBox.wedge = (thisngHFPMTBox.pmt-1)/2 + 1;
  //thisngHFPMTBox.pixel = ;

  myngHFPMTBox.push_back(thisngHFPMTBox);
  return ;
}

/*
void ngHFMappingAlgorithm::ConstructngHFLMapObject()
{
  std::cout << "Constructing ngHF LMap Object..." << std::endl;

  for(int irbx=0;irbx<NrbxngHF*2;irbx++)
  {
    for(int irm=0;irm<NrmngHF;irm++)
    {
      for(int irmfi=0;irmfi<Nrm_fiber;irmfi++)
      {
        for(int ifich=0;ifich<Nfiber_ch;ifich++)
        {
          int sideid; irbx<NrbxngHF ? sideid = 1 : sideid = -1;//0..to 11 is P side, while 12 to 23 is M side
          int rbxrmid; irbx<NrbxngHF ? rbxrmid = irbx*NrmngHF+irm : rbxrmid = (irbx-NrbxngHF)*NrmngHF+irm;//ngHF 0...to 35
          int rmfifichid = irmfi*Nfiber_ch+ifich;//ngHF 0...to 23

          ConstructngHFFrontEnd(sideid,rbxrmid,rmfifichid);      
          ConstructngHFBackEnd(sideid,rbxrmid,rmfifichid);  
          ConstructngHFGeometry(sideid,rbxrmid,rmfifichid);
          ConstructngHFPMTBox();  
          ConstructngHFTriggerTower();
        }
      }
    }
  }
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFFrontEnd(int sideid, int rbxrmid, int rmfifichid)
{
  ngHFFrontEnd thisngHFFrontEnd;
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxrmid/NrmngHF + 1) < 10 ? numberletter = "0" + std::to_string(rbxrmid/NrmngHF + 1) : numberletter = std::to_string(rbxrmid/NrmngHF + 1); 
  thisngHFFrontEnd.rbx = "ngHF" + sideletter + numberletter;
  thisngHFFrontEnd.rm = rbxrmid%NrmngHF + 1;
  thisngHFFrontEnd.rm_fiber = rmfifichid/Nfiber_ch +1;
  thisngHFFrontEnd.fiber_ch = rmfifichid%Nfiber_ch;
  //set secondary variables qie8 map
  thisngHFFrontEnd.qie8 = (thisngHFFrontEnd.rm_fiber -1)/2+1;
  thisngHFFrontEnd.rm_fiber%2 != 0 ? thisngHFFrontEnd.qie8_ch = thisngHFFrontEnd.fiber_ch : thisngHFFrontEnd.qie8_ch = 3 + (thisngHFFrontEnd.fiber_ch+1)%3;

  myngHFFrontEnd.push_back(thisngHFFrontEnd);
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFBackEnd(int sideid, int rbxrmid, int rmfifichid)
{
  ngHFBackEnd thisngHFBackEnd;
  //
  thisngHFBackEnd.ucrate = ngHFucrateInrbxrmid[((rbxrmid+35)%36)/12];
  sideid>0 ? thisngHFBackEnd.uhtr = (((rbxrmid+35)%36)%12)/2 + 7 : thisngHFBackEnd.uhtr = (((rbxrmid+35)%36)%12)/2 + 1;
  thisngHFBackEnd.ufpga = "uHTR";
  if(sideid>0)
  { 
    if( rbxrmid%2 == 0){ rmfifichid<12 ? thisngHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 18 : thisngHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 6; }
    else{ rmfifichid<12 ? thisngHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 14 : thisngHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 2; }
  }
  else
  { 
    if( rbxrmid%2 == 0){ rmfifichid<12 ? thisngHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 14 : thisngHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 2; }
    else{ rmfifichid<12 ? thisngHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 18 : thisngHFBackEnd.uhtr_fiber = (rmfifichid%12)/3 + 6; }
  }

  thisngHFBackEnd.fiber_ch = rmfifichid%3;

  //set secondary variables
  myngHFBackEnd.push_back(thisngHFBackEnd);
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFGeometry(int sideid, int rbxrmid, int rmfifichid)
{
  ngHFGeometry thisngHFGeometry;

  thisngHFGeometry.subdet = "ngHF";
  thisngHFGeometry.side = sideid;
  
  if(rmfifichid == 12||rmfifichid == 18){ thisngHFGeometry.phi = (((rbxrmid+35)%36)/2)*4+3; thisngHFGeometry.dphi = 4; }
  else{ thisngHFGeometry.phi = rbxrmid*2+1; thisngHFGeometry.dphi = 2; }
  
  if(sideid > 0)
  { 
    if(rbxrmid%2 == 0){ thisngHFGeometry.eta = ngHFetaInrmfifichidType2[rmfifichid]; thisngHFGeometry.depth = ((rmfifichid+6)%24/6)%2+1; }
    else{ thisngHFGeometry.eta = ngHFetaInrmfifichidType1[rmfifichid]; thisngHFGeometry.depth = (rmfifichid/6)%2+1; }
  }
  else
  {
    if(rbxrmid%2 == 0){ thisngHFGeometry.eta = ngHFetaInrmfifichidType1[rmfifichid]; thisngHFGeometry.depth = (rmfifichid/6)%2+1; }
    else{ thisngHFGeometry.eta = ngHFetaInrmfifichidType2[rmfifichid]; thisngHFGeometry.depth = ((rmfifichid+6)%24/6)%2+1; }
  }
  myngHFGeometry.push_back(thisngHFGeometry);
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFPMTBox()
{
  ngHFPMTBox thisngHFPMTBox;
  
  myngHFPMTBox.push_back(thisngHFPMTBox);
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFTriggerTower()
{
  ngHFTriggerTower thisngHFTriggerTower;

  myngHFTriggerTower.push_back(thisngHFTriggerTower);
  return ;
}
*/
