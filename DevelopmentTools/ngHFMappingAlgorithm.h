#include <vector>
#include <iostream>

#include "ngHFMappingObject.h"

class ngHFMappingAlgorithm : public ngHFConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHFFrontEnd> myngHFFrontEnd; std::vector<ngHFBackEnd> myngHFBackEnd; std::vector<ngHFPMTBox> myngHFPMTBox; std::vector<ngHFGeometry> myngHFGeometry; std::vector<ngHFTriggerTower> myngHFTriggerTower;
  void SplitngHFfromOldHF(std::vector<HFFrontEnd> myHFFrontEnd, std::vector<HFBackEnd> myHFBackEnd, std::vector<HFPMTBox> myHFPMTBox, std::vector<HFGeometry> myHFGeometry, std::vector<HFTriggerTower> myHFTriggerTower);
  void ConstructngHFLMapObject();
 private:
  void ConstructngHFFrontEnd(int sideid, int rbxqie10id, int qie10chid);
  void ConstructngHFPMTBox(int sideid, int rbxqie10id, int qie10chid);
  void ConstructngHFBackEnd(int sideid, int rbxqie10id, int qie10chid);      
  void ConstructngHFGeometry(int sideid, int rbxqie10id, int qie10chid);      
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

    thisngHFFrontEnd.qie10 = ngHFqie10Inrbxqie10id[rbxqie10id%Nqie10];//3,4,5,6, 10,11,12,13,14
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
    //ConstructngHFPMTBox(rbxqie10id, qie10_chid,thisngHFFrontEnd.s_coax_qie,thisngHFFrontEnd.r_coax_qie);
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
    //ConstructngHFPMTBox(rbxqie10id, qie10_chid,thisngHFFrontEnd.s_coax_qie,thisngHFFrontEnd.r_coax_qie);
    //myngHFPMTBox.push_back(thisngHFPMTBox);
    myngHFTriggerTower.push_back(thisngHFTriggerTower);
  }
  
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFLMapObject()
{
  std::cout << "#Constructing ngHF LMap Object..." << std::endl;

  for(int irbx=0;irbx<NrbxngHF*2;irbx++)//8 rbx per side for ngHF
  {
    for(int iqie10=0;iqie10<Nqie10;iqie10++)//9 QIE10 cards per rbx
    {
      for(int iqie10ch=0;iqie10ch<Nqie10_ch;iqie10ch++)//24 qie10 channels per qie card
      {
        int sideid; irbx<NrbxngHF ? sideid = 1 : sideid = -1;//0..to 7 is P side, while 8 to 15 is M side
        int rbxqie10id; irbx<NrbxngHF ? rbxqie10id = irbx*Nqie10+iqie10 : rbxqie10id = (irbx-NrbxngHF)*Nqie10+iqie10;//ngHF 0...to 71
        int qie10chid = iqie10ch;//ngHF 0...to 23

        ConstructngHFFrontEnd(sideid,rbxqie10id,qie10chid);
        ConstructngHFPMTBox(sideid,rbxqie10id,qie10chid);
        //ConstructngHFBackEnd(sideid,rbxqie10id,qie10chid);
        //ConstructngHFGeometry(sideid,rbxqie10id,qie10chid);
        //ConstructngHFTriggerTower();
      }
    }
  }
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFFrontEnd(int sideid, int rbxqie10id, int qie10chid)
{
  ngHFFrontEnd thisngHFFrontEnd;
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxqie10id/Nqie10 + 1) < 10 ? numberletter = "0" + std::to_string(rbxqie10id/Nqie10 + 1) : numberletter = std::to_string(rbxqie10id/Nqie10 + 1); 
  thisngHFFrontEnd.rbx = "ngHF" + sideletter + numberletter;
  thisngHFFrontEnd.qie10 = ngHFqie10Inrbxqie10id[rbxqie10id%Nqie10];////3,4,5,6, 10,11,12,13,14
  thisngHFFrontEnd.qie10_ch = qie10chid+1;//1 to 24
  
  //to PMT direction ...
  thisngHFFrontEnd.s_coax_qie = (qie10chid%12)*2+2;
  thisngHFFrontEnd.r_coax_qie = (qie10chid%12)*2+1;

  //to backend direction ...
  thisngHFFrontEnd.qie10_fiber = qie10chid/Nfiber_ch+4;//4,5,6,7,8,9
  thisngHFFrontEnd.fiber_ch = qie10chid%Nfiber_ch;//0,1,2,3

  myngHFFrontEnd.push_back(thisngHFFrontEnd);
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFPMTBox(int sideid, int rbxqie10id, int qie10chid)
{
  ngHFPMTBox thisngHFPMTBox;
  const int ngHFpmtboxInrbxqie10id[18] = {5,4,4,3,3,2,2,1,1,9,9,8,8,7,7,6,6,5};
  sideid>0 ? thisngHFPMTBox.pmtbox = rbxqie10id/2+1 : thisngHFPMTBox.pmtbox = (rbxqie10id/18)*9 + ngHFpmtboxInrbxqie10id[rbxqie10id%18];//from 0,...71 QIE10 to pmtbox 1,...36, P side normal order, M side in weird pattern : 5 44 33 22 11 99 88 77 66 5 in every 18 QIE10 blocks
  if(sideid>0){ thisngHFPMTBox.pmtbox%2!=0 ? thisngHFPMTBox.pmt_type = "A" : thisngHFPMTBox.pmt_type = "B"; }//different odd/even numbering for M P side. Be careful! P side 1 is A and 2 is B 
  else{ thisngHFPMTBox.pmtbox%2!=0 ? thisngHFPMTBox.pmt_type = "B" : thisngHFPMTBox.pmt_type = "A"; }
  thisngHFPMTBox.winchester_cable = (rbxqie10id%2)*2 + (qie10chid)/12 + 1;
  int s_coax_qie = (qie10chid%12)*2+2; int r_coax_qie = (qie10chid%12)*2+1;
  s_coax_qie <= 12 ? thisngHFPMTBox.s_coax_pmt = 12 - s_coax_qie + 1 : thisngHFPMTBox.s_coax_pmt = 24 - s_coax_qie + 13;
  r_coax_qie <= 12 ? thisngHFPMTBox.r_coax_pmt = 12 - r_coax_qie + 1 : thisngHFPMTBox.r_coax_pmt = 24 - r_coax_qie + 13;
  
  //thisngHFPMTBox.wedge = (thisngHFPMTBox.pmtbox-1)/2 + 1;

  //setting internal wiring information anode and tower
  //http://cmsdoc.cern.ch/cms/HCAL/document/Calorimeters/HF/HF_Readout_box_wiring_draft_May14-2013.pdf
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HF/dual-anode/HF_dual-readout_PMT_box_signal_mapping.xls
  ((thisngHFPMTBox.s_coax_pmt)%4==1) ? thisngHFPMTBox.anode = 3 : thisngHFPMTBox.anode = 1;
  const std::string ngHFtowerInWinchesterPin_TypeAW1[12] = {"E2" ,"H2" ,"E4" ,"H4" ,"E6" ,"H6" ,"E1" ,"H1" ,"E3" ,"H3" ,"E5" ,"H5" };
  const std::string ngHFtowerInWinchesterPin_TypeAW2[12] = {"H2" ,"E2" ,"H4" ,"E4" ,"H6" ,"E6" ,"H1" ,"E1" ,"H3" ,"E3" ,"H5" ,"E5" };
  const std::string ngHFtowerInWinchesterPin_TypeAW3[12] = {"E8" ,"H8" ,"E10","H10","E12","H12","E7" ,"H7" ,"E9" ,"H9" ,"E11","H11"};
  const std::string ngHFtowerInWinchesterPin_TypeAW4[12] = {"H8" ,"E8" ,"H10","E10","H12","E12","H7" ,"E7" ,"H9" ,"E9" ,"H11","E11"};
  const std::string ngHFtowerInWinchesterPin_TypeBW1[12] = {"H14","E14","H16","E16","H18","E18","H15","E15","H17","E17","H19","E19"};
  const std::string ngHFtowerInWinchesterPin_TypeBW2[12] = {"E14","H14","E16","H16","E18","H18","E15","H15","E17","H17","E19","H19"};
  const std::string ngHFtowerInWinchesterPin_TypeBW3[12] = {"H20","E20","H22","E22","H13","E13","H21","E21","H23","E23","H24","E24"};
  const std::string ngHFtowerInWinchesterPin_TypeBW4[12] = {"E20","H20","E22","H22","E13","H13","E21","H21","E23","H23","E24","H24"};
  if     ( thisngHFPMTBox.pmt_type == "A" && thisngHFPMTBox.winchester_cable == 1){ thisngHFPMTBox.tower = ngHFtowerInWinchesterPin_TypeAW1[thisngHFPMTBox.s_coax_pmt/2]; }
  else if( thisngHFPMTBox.pmt_type == "A" && thisngHFPMTBox.winchester_cable == 2){ thisngHFPMTBox.tower = ngHFtowerInWinchesterPin_TypeAW2[thisngHFPMTBox.s_coax_pmt/2]; }
  else if( thisngHFPMTBox.pmt_type == "A" && thisngHFPMTBox.winchester_cable == 3){ thisngHFPMTBox.tower = ngHFtowerInWinchesterPin_TypeAW3[thisngHFPMTBox.s_coax_pmt/2]; }
  else if( thisngHFPMTBox.pmt_type == "A" && thisngHFPMTBox.winchester_cable == 4){ thisngHFPMTBox.tower = ngHFtowerInWinchesterPin_TypeAW4[thisngHFPMTBox.s_coax_pmt/2]; }
  else if( thisngHFPMTBox.pmt_type == "B" && thisngHFPMTBox.winchester_cable == 1){ thisngHFPMTBox.tower = ngHFtowerInWinchesterPin_TypeBW1[thisngHFPMTBox.s_coax_pmt/2]; }
  else if( thisngHFPMTBox.pmt_type == "B" && thisngHFPMTBox.winchester_cable == 2){ thisngHFPMTBox.tower = ngHFtowerInWinchesterPin_TypeBW2[thisngHFPMTBox.s_coax_pmt/2]; }
  else if( thisngHFPMTBox.pmt_type == "B" && thisngHFPMTBox.winchester_cable == 3){ thisngHFPMTBox.tower = ngHFtowerInWinchesterPin_TypeBW3[thisngHFPMTBox.s_coax_pmt/2]; }
  else if( thisngHFPMTBox.pmt_type == "B" && thisngHFPMTBox.winchester_cable == 4){ thisngHFPMTBox.tower = ngHFtowerInWinchesterPin_TypeBW4[thisngHFPMTBox.s_coax_pmt/2]; }
  else{ std::cout << "No coresponding tower from pmt_type and winchester_cable??? what the fuck is going on??" << std::endl; }

  myngHFPMTBox.push_back(thisngHFPMTBox);
  return ;
}

/*
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

void ngHFMappingAlgorithm::ConstructngHFTriggerTower()
{
  ngHFTriggerTower thisngHFTriggerTower;

  myngHFTriggerTower.push_back(thisngHFTriggerTower);
  return ;
}
*/
