#include "ngHFMappingAlgorithm.h"

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

void ngHFMappingAlgorithm::ConstructngHFLMapObject(std::string Mode)
{
  myngHFQIE10CardMap.clear();
  std::cout << "#Loading information from QIE allocation file..." << std::endl;
  LoadngHFQIEMap("ngHFQIEInput/HF_QIE10_CardMap_26May2017.txt");
  //std::cout << myngHFQIE10CardMap.size() << std::endl;

  if(Mode == "Normal")
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
          ConstructngHFPMTBox(sideid,rbxqie10id,qie10chid); //Also construct Geometry
          ConstructngHFBackEnd(sideid,rbxqie10id,qie10chid);
        }
      }
    }
  }
  else if(Mode == "Calib")
  {
    std::cout << "#Constructing ngHF Calib LMap Object..." << std::endl;
    for(int irbx=0;irbx<NrbxngHFCalib*2;irbx++)//4 rbx per side for ngHF
    {
      for(int iqie10=0;iqie10<Nqie10Calib;iqie10++)//1 QIE10 cards for ngHF CU
      {
        for(int iqie10fi=0;iqie10fi<Nqie10_fiberCalib;iqie10fi++)//only 1 QIE10 fiber
        {
          for(int ifich=0;ifich<Nfiber_ch;ifich++)//4 QIE10 fiber per fiber
          {
            int sideid; irbx<NrbxngHFCalib ? sideid = 1 : sideid = -1;//0..to 7 is P side, while 8 to 15 is M side
            int rbxqie10id; irbx<NrbxngHFCalib ? rbxqie10id = irbx*Nqie10Calib+iqie10 : rbxqie10id = (irbx-NrbxngHFCalib)*Nqie10Calib+iqie10;//
            int qie10chid = iqie10fi*Nfiber_ch + ifich;
            ConstructngHFCalib(sideid, rbxqie10id, qie10chid);
          }
        }                                                                                                                                                                                                   
      }
    }
  }
  else
  {
    std::cout << "#Invalid generate mode for ngHF Logical map!" << std::endl;
    return ;
  }

  return ;
}

void ngHFMappingAlgorithm::ConstructngHFFrontEnd(int sideid, int rbxqie10id, int qie10chid)
{
  ngHFFrontEnd thisngHFFrontEnd;
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; (rbxqie10id/Nqie10 + 1) < 10 ? numberletter = "0" + std::to_string(rbxqie10id/Nqie10 + 1) : numberletter = std::to_string(rbxqie10id/Nqie10 + 1); 
  thisngHFFrontEnd.rbx = "HF" + sideletter + numberletter;
  thisngHFFrontEnd.qie10 = ngHFqie10Inrbxqie10id[rbxqie10id%Nqie10];////3,4,5,6, 10,11,12,13,14
  thisngHFFrontEnd.qie10_ch = qie10chid+1;//1 to 24
  
  //to PMT direction ...
  thisngHFFrontEnd.s_coax_qie = (qie10chid%12)*2+2;
  thisngHFFrontEnd.r_coax_qie = (qie10chid%12)*2+1;

  //to backend direction ...
  thisngHFFrontEnd.qie10_fiber = qie10chid/Nfiber_ch+4;//4,5,6,7,8,9
  thisngHFFrontEnd.fiber_ch = qie10chid%Nfiber_ch;//0,1,2,3

  //ohters...
  thisngHFFrontEnd.qie10_ch<13 ? thisngHFFrontEnd.qie10_connector = "TOP" : thisngHFFrontEnd.qie10_connector = "BOT";
  
  //QIE id ... need to set from a huge xls file
  //thisngHFFrontEnd.qie10_id = 500000;
  //thisngHFFrontEnd.qie10_barcode = "0x3e000000 0xba22f270";
  GetngHFQIEInfoToLMap(
                       thisngHFFrontEnd.rbx, thisngHFFrontEnd.qie10,
                       thisngHFFrontEnd.qie10_id, thisngHFFrontEnd.qie10_barcode
                      );
  //Starting from 09 November 2019, all QIE ids are set to 999999 since these parts are taken by Aleko, including QIE constants
  thisngHFFrontEnd.qie10_id = 999999;
  thisngHFFrontEnd.qie10_barcode = "0x00000000";
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
  //winchester cable assignment different between the P and M side, see : http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HF/ngHF/HF_Winchester-QIE_23-jan-2016.xls
  if(sideid>0)
  { 
    thisngHFPMTBox.winchester_cable = (rbxqie10id%2)*2 + (qie10chid)/12 + 1; 
  }
  else
  { 
    int tmprbx = rbxqie10id/Nqie10 + 1;
    //const int ngHFwinchester_cableInrbxqie10id_RBX0107[9] = {1,1,3,1,3,1,3,1,3};
    //const int ngHFwinchester_cableInrbxqie10id_RBX0208[9] = {1,3,1,3,1,3,1,3,3};
    const int ngHFwinchester_cableInrbxqie10id_RBX0107[9] = {3,1,3,1,3,1,3,1,3};
    const int ngHFwinchester_cableInrbxqie10id_RBX0208[9] = {1,3,1,3,1,3,1,3,1};
    const int ngHFwinchester_cableInrbxqie10id_RBX0305[9] = {3,1,3,1,3,1,3,1,3};
    const int ngHFwinchester_cableInrbxqie10id_RBX0406[9] = {1,3,1,3,1,3,1,3,1};
    //HFM01 07 pattern 113131313 in TOP connector in QIE10
    if     (tmprbx==1 || tmprbx==7){ thisngHFPMTBox.winchester_cable = ngHFwinchester_cableInrbxqie10id_RBX0107[rbxqie10id%Nqie10] + (qie10chid)/12; }
    //HFM02 08 pattern 131313133 in TOP connector in QIE10
    else if(tmprbx==2 || tmprbx==8){ thisngHFPMTBox.winchester_cable = ngHFwinchester_cableInrbxqie10id_RBX0208[rbxqie10id%Nqie10] + (qie10chid)/12; }
    //HFM03 05 pattern 313131313 in TOP connector in QIE10
    else if(tmprbx==3 || tmprbx==5){ thisngHFPMTBox.winchester_cable = ngHFwinchester_cableInrbxqie10id_RBX0305[rbxqie10id%Nqie10] + (qie10chid)/12; }
    //HFM04 06 pattern 131313131 in TOP connector in QIE10
    else if(tmprbx==4 || tmprbx==6){ thisngHFPMTBox.winchester_cable = ngHFwinchester_cableInrbxqie10id_RBX0406[rbxqie10id%Nqie10] + (qie10chid)/12; }
    //HFM01,02 / 07,08 in pattern 11313131....133
    else{ std::cout << "What the fuck?? the rbx id is not in the range [1,8]! " << tmprbx << std::endl; }
  }
  int s_coax_qie = (qie10chid%12)*2+2; int r_coax_qie = (qie10chid%12)*2+1;
  s_coax_qie <= 12 ? thisngHFPMTBox.s_coax_pmt = 12 - s_coax_qie + 1 : thisngHFPMTBox.s_coax_pmt = 24 - s_coax_qie + 13;
  r_coax_qie <= 12 ? thisngHFPMTBox.r_coax_pmt = 12 - r_coax_qie + 1 : thisngHFPMTBox.r_coax_pmt = 24 - r_coax_qie + 13;
  
  //setting internal wiring information anode and tower
  //http://cmsdoc.cern.ch/cms/HCAL/document/Calorimeters/HF/HF_Readout_box_wiring_draft_May14-2013.pdf
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HF/dual-anode/HF_dual-readout_PMT_box_signal_mapping.xls
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
  else{ std::cout << "No corresponding tower from pmt_type and winchester_cable??? what the fuck is going on??" << std::endl; }
  ((thisngHFPMTBox.s_coax_pmt)%4==1) ? thisngHFPMTBox.anode = 3 : thisngHFPMTBox.anode = 1;

  const std::map<std::string, std::string> ngHFbaseboard_typeIntower = {
                                           {"H9" ,"A"},{"H11","A"},{"E9" ,"A"},{"E11","A"},{"H10","A"},{"H12","A"},{"E10","A"},{"E12","A"},//PMT box type A, base board A
                                           {"H5" ,"B"},{"H7" ,"B"},{"E5" ,"B"},{"E7" ,"B"},{"H6" ,"B"},{"H8" ,"B"},{"E6" ,"B"},{"E8" ,"B"},//PMT box type A, base board B
                                           {"H1" ,"C"},{"H3" ,"C"},{"E1" ,"C"},{"E3" ,"C"},{"H2" ,"C"},{"H4" ,"C"},{"E2" ,"C"},{"E4" ,"C"},//PMT box type A, base board C
                                           {"E23","A"},{"E24","A"},{"H23","A"},{"H24","A"},{"E22","A"},{"E13","A"},{"H22","A"},{"H13","A"},//PMT box type B, base board A
                                           {"E19","B"},{"E21","B"},{"H19","B"},{"H21","B"},{"E18","B"},{"E20","B"},{"H18","B"},{"H20","B"},//PMT box type B, base board B
                                           {"E15","C"},{"E17","C"},{"H15","C"},{"H17","C"},{"E14","C"},{"E16","C"},{"H14","C"},{"H16","C"},//PMT box type B, base board C
                                                                       };
  const std::map<std::string, int> ngHFpmtsocketIntower = {
                                   {"H9" ,1},{"H11",2},{"E9" ,3},{"E11",4},{"H10",5},{"H12",6},{"E10",7},{"E12",8},//PMT box type A, base board A
                                   {"H5" ,1},{"H7" ,2},{"E5" ,3},{"E7" ,4},{"H6" ,5},{"H8" ,6},{"E6" ,7},{"E8" ,8},//PMT box type A, base board B
                                   {"H1" ,1},{"H3" ,2},{"E1" ,3},{"E3" ,4},{"H2" ,5},{"H4" ,6},{"E2" ,7},{"E4" ,8},//PMT box type A, base board C
                                   {"E23",1},{"E24",2},{"H23",3},{"H24",4},{"E22",5},{"E13",6},{"H22",7},{"H13",8},//PMT box type B, base board A
                                   {"E19",1},{"E21",2},{"H19",3},{"H21",4},{"E18",5},{"E20",6},{"H18",7},{"H20",8},//PMT box type B, base board B
                                   {"E15",1},{"E17",2},{"H15",3},{"H17",4},{"E14",5},{"E16",6},{"H14",7},{"H16",8},//PMT box type B, base board C
                                                          };
  thisngHFPMTBox.baseboard_type = (ngHFbaseboard_typeIntower.find(thisngHFPMTBox.tower))->second; //type of base board, A,B and C, per PMT box
  thisngHFPMTBox.pmtsocket = (ngHFpmtsocketIntower.find(thisngHFPMTBox.tower))->second;//1 to 8, pmt socket in the base board
  
  thisngHFPMTBox.wedge = (thisngHFPMTBox.pmtbox%36)/2 + 1;

  myngHFPMTBox.push_back(thisngHFPMTBox);
  //Done with PMT box class

  //Build Geometry variables from PMT box
  ConstructngHFGeometry(sideid,thisngHFPMTBox.pmtbox,thisngHFPMTBox.tower,thisngHFPMTBox.anode);
  
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFBackEnd(int sideid, int rbxqie10id, int qie10chid)
{
  ngHFBackEnd thisngHFBackEnd;
  //set trunk, Y fiber and MTP
  const int ngHFtrunk_ncableInrbxqie10id_HFP[72] = 
                                         {
                                          14193,14193,14194,14194,14194,14194,14194,14194,14194,//HFP01
                                          14194,14195,14195,14195,14195,14195,14195,14195,14195,//HFP02
                                          14196,14196,14196,14196,14196,14196,14196,14196,14197,//HFP03
                                          14197,14197,14197,14197,14197,14197,14197,14198,14198,//HFP04
                                          14198,14198,14198,14198,14198,14198,14199,14199,14199,//HFP05
                                          14199,14199,14199,14199,14199,14200,14200,14200,14200,//HFP06
                                          14191,14191,14191,14191,14192,14192,14192,14192,14192,//HFP07
                                          14192,14192,14192,14193,14193,14193,14193,14193,14193,//HFP08
                                         };
  const int ngHFtrunk_ncableInrbxqie10id_HFM[72] = 
                                         {
                                          14204,14204,14204,14204,14204,14204,14204,14203,14203,//HFM01
                                          14205,14205,14205,14205,14205,14205,14205,14205,14204,//HFM02
                                          14207,14206,14206,14206,14206,14206,14206,14206,14206,//HFM03
                                          14208,14208,14207,14207,14207,14207,14207,14207,14207,//HFM04
                                          14209,14209,14209,14208,14208,14208,14208,14208,14208,//HFM05
                                          14210,14210,14210,14210,14209,14209,14209,14209,14209,//HFM06
                                          14202,14202,14202,14202,14202,14201,14201,14201,14201,//HFM07
                                          14203,14203,14203,14203,14203,14203,14202,14202,14202,//HFM08
                                         };
  sideid > 0 ? thisngHFBackEnd.trunk_ncable = ngHFtrunk_ncableInrbxqie10id_HFP[rbxqie10id] : thisngHFBackEnd.trunk_ncable = ngHFtrunk_ncableInrbxqie10id_HFM[rbxqie10id];
  
  //1 or 2, HFP in 121212 pattern, while HFM in 212121 patter
  sideid > 0 ? thisngHFBackEnd.yfiber_input = rbxqie10id%2+1 : thisngHFBackEnd.yfiber_input = (rbxqie10id+1)%2+1;

  const int ngHFmtpInrbxqie10id_HFP[72] =
                                {
                                 4,4,1,1,2,2,3,3,4,//HFP01
                                 4,1,1,2,2,3,3,4,4,//HFP02
                                 1,1,2,2,3,3,4,4,1,//HFP03
                                 1,2,2,3,3,4,4,1,1,//HFP04
                                 2,2,3,3,4,4,1,1,2,//HFP05
                                 2,3,3,4,4,1,1,2,2,//HFP06
                                 1,1,2,2,1,1,2,2,3,//HFP07
                                 3,4,4,1,1,2,2,3,3,//HFP08
                                };
  const int ngHFmtpInrbxqie10id_HFM[72] =
                                {
                                 1,2,2,3,3,4,4,1,1,//HFM01
                                 1,1,2,2,3,3,4,4,1,//HFM02
                                 4,1,1,2,2,3,3,4,4,//HFM03
                                 4,4,1,1,2,2,3,3,4,//HFM04
                                 3,4,4,1,1,2,2,3,3,//HFM05
                                 1,1,2,2,1,1,2,2,3,//HFM06
                                 2,3,3,4,4,1,1,2,2,//HFM07
                                 2,2,3,3,4,4,1,1,2,//HFM08
                                };
  sideid > 0 ? thisngHFBackEnd.mtp = ngHFmtpInrbxqie10id_HFP[rbxqie10id] : thisngHFBackEnd.mtp = ngHFmtpInrbxqie10id_HFM[rbxqie10id];

  //start to mapping crate uHTR slot fiber from trunk ncable, Y fiber, MTP
  //uCrate is determined by nCable only!
  const std::map<int, int> ngHFucrateIntrunk_ncable = {
                                                       {14191,32},{14192,32},{14193,32},{14194,22},{14195,22},{14196,22},{14197,29},{14198,29},{14199,29},{14200,32},//ngHFP cable
                                                       {14201,32},{14202,32},{14203,32},{14204,22},{14205,22},{14206,22},{14207,29},{14208,29},{14209,29},{14210,32},//ngHFM cable
                                                      };
  thisngHFBackEnd.ucrate = (ngHFucrateIntrunk_ncable.find(thisngHFBackEnd.trunk_ncable))->second;
  //uHTR is determined by nCable and MTP, and also different by side, HFP for slot 7 to 12 while HFM for 1 to 6
  std::map<std::pair<int, int>, int> ngHFuhtrIntrunk_ncablemtp = 
                                     {
                                      {{14191,1}, 8},{{14191,2}, 8},
                                      {{14192,1}, 9},{{14192,2}, 9},{{14192,3},10},{{14192,4},10},
                                      {{14193,1},11},{{14193,2},11},{{14193,3},12},{{14193,4},12},
                                      {{14194,1}, 7},{{14194,2}, 7},{{14194,3}, 8},{{14194,4}, 8},
                                      {{14195,1}, 9},{{14195,2}, 9},{{14195,3},10},{{14195,4},10},
                                      {{14196,1},11},{{14196,2},11},{{14196,3},12},{{14196,4},12},
                                      {{14197,1}, 7},{{14197,2}, 7},{{14197,3}, 8},{{14197,4}, 8},
                                      {{14198,1}, 9},{{14198,2}, 9},{{14198,3},10},{{14198,4},10},
                                      {{14199,1},11},{{14199,2},11},{{14199,3},12},{{14199,4},12},
                                      {{14200,1}, 7},{{14200,2}, 7},
                                      {{14201,1}, 2},{{14201,2}, 2},
                                      {{14202,1}, 4},{{14202,2}, 4},{{14202,3}, 3},{{14202,4}, 3},
                                      {{14203,1}, 6},{{14203,2}, 6},{{14203,3}, 5},{{14203,4}, 5},
                                      {{14204,1}, 2},{{14204,2}, 2},{{14204,3}, 1},{{14204,4}, 1},
                                      {{14205,1}, 4},{{14205,2}, 4},{{14205,3}, 3},{{14205,4}, 3},
                                      {{14206,1}, 6},{{14206,2}, 6},{{14206,3}, 5},{{14206,4}, 5},
                                      {{14207,1}, 2},{{14207,2}, 2},{{14207,3}, 1},{{14207,4}, 1},
                                      {{14208,1}, 4},{{14208,2}, 4},{{14208,3}, 3},{{14208,4}, 3},
                                      {{14209,1}, 6},{{14209,2}, 6},{{14209,3}, 5},{{14209,4}, 5},
                                      {{14210,1}, 1},{{14210,2}, 1},
                                     };
  thisngHFBackEnd.uhtr = (ngHFuhtrIntrunk_ncablemtp.find(std::make_pair(thisngHFBackEnd.trunk_ncable,thisngHFBackEnd.mtp)))->second;
  //set RX from MTP, 0 or 1
  thisngHFBackEnd.uhtr_rx = (thisngHFBackEnd.mtp+1)%2;
  //set uHTR fiber from uhtr_rx y fiber and qie_fiber
  /*
  input       output     uHTR       uHTR
  (QIE)       (trunk)    (R0)       (R1)
  1-4         1          0          12
  1-5         2          1          13
  1-6         3          2          14
  1-7         4          3          15
  1-8         5          4          16
  1-9         6          5          17
  2-4         7          6          18
  2-5         8          7          19
  2-6         9          8          20
  2-7        10          9          21
  2-8        11         10          22
  2-9        12         11          23
  */
  thisngHFBackEnd.uhtr_fiber = thisngHFBackEnd.uhtr_rx*12 + (thisngHFBackEnd.yfiber_input-1)*6 + qie10chid/Nfiber_ch;//0,1,2,3,4,5 to 23
  //fiber channel just same as fiber channel
  thisngHFBackEnd.fiber_ch = qie10chid%Nfiber_ch;//0,1,2,3
  //set secondary variables
  thisngHFBackEnd.trunk_fiber = (thisngHFBackEnd.yfiber_input-1)*6 + qie10chid/Nfiber_ch + 1;//1 to 12
  //FED 1118,1119,1120,1121,1122,1123
  //backend slot 7 to 12 odd number backend slot 1 to 6 even number, 
  const std::map<int, std::pair<int, int> > ngHFufedidInucrate = { {22,{1118,1119}},{29,{1120,1121}},{32,{1122,1123}} };
  thisngHFBackEnd.uhtr <= 6 ? thisngHFBackEnd.ufedid = ((ngHFufedidInucrate.find(thisngHFBackEnd.ucrate))->second).first : thisngHFBackEnd.ufedid = ((ngHFufedidInucrate.find(thisngHFBackEnd.ucrate))->second).second;
  myngHFBackEnd.push_back(thisngHFBackEnd);
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFGeometry(int sideid,int pmtbox,std::string tower,int anode)
{
  ngHFGeometry thisngHFGeometry;

  thisngHFGeometry.subdet = "HF";
  thisngHFGeometry.side = sideid;
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HF/dual-anode/ngHF_QIE_MTP_map.xls Phi - - - pmtbox mapping
  //Special fix for Tower E12 H12 E13, H13 on phi : do we have a more elegant way to do that ?
  if(tower=="E12"||tower=="H12"||tower=="E13"||tower=="H13") thisngHFGeometry.phi = (((pmtbox%36)/2)*4+3+68)%72;
  else thisngHFGeometry.phi = pmtbox*2-1; 
  //http://cmsdoc.cern.ch/cms/HCAL/document/Calorimeters/HF/HF_Readout_box_wiring_draft_May14-2013.pdf Eta - - - tower mapping
  //decouple the tower into 2 pieces
  std::string towertype = tower.substr(0,1); int towerid = atoi(tower.substr(1).c_str());
  const std::map<int, int> ngHFetaIntowerid = { 
                                               {15,30}, {17,32}, {14,29},{16,31},//Base board C, PMT Box type B
                                               {19,34}, {21,36}, {18,33},{20,35},//Base board B, PMT Box type B
                                               {23,38}, {24,39}, {22,37},{13,41},//Base board A, PMT Box type B
                                               { 1,29}, { 3,31}, { 2,30},{ 4,32},//Base board C, PMT Box type A
                                               { 5,33}, { 7,35}, { 6,34},{ 8,36},//Base board B, PMT Box type A
                                               { 9,37}, {11,39}, {10,38},{12,40},//Base board A, PMT Box type A
                                              };
  thisngHFGeometry.eta = (ngHFetaIntowerid.find(towerid))->second;
  if     (towertype=="E" && anode==1) thisngHFGeometry.depth = 1;
  else if(towertype=="H" && anode==1) thisngHFGeometry.depth = 2;
  else if(towertype=="E" && anode==3) thisngHFGeometry.depth = 3;
  else if(towertype=="H" && anode==3) thisngHFGeometry.depth = 4;
  else std::cout << "Can not set depth?? What the hell is going on!!" << std::endl;
  if(towerid==12 || towerid==13) thisngHFGeometry.dphi = 4;//tower 12 and tower 13 are for the eta 40,41, where dphi == 4
  else thisngHFGeometry.dphi = 2;
  
  myngHFGeometry.push_back(thisngHFGeometry);
  ConstructngHFTriggerTower(thisngHFGeometry.eta, thisngHFGeometry.phi);
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFTriggerTower(int eta, int phi)
{
  ngHFTriggerTower thisngHFTriggerTower;

  thisngHFTriggerTower.trg_fiber = -1;
  if(eta==29)//special fix for eta 29 HE, tail go with eta 28. more details in phase 1 upgrade note
  {
    thisngHFTriggerTower.trg_fiber = -1;
    thisngHFTriggerTower.trg_fiber_ch = -1;
  }
  else
  {
    if(phi%4==3){ eta==41 ? thisngHFTriggerTower.trg_fiber=1 : thisngHFTriggerTower.trg_fiber=0; }
    else if(phi%4==1){ thisngHFTriggerTower.trg_fiber=1; }
    else{ std::cout << "dPhi is not 2 or 4??" << std::endl; }
    eta==41 ? thisngHFTriggerTower.trg_fiber_ch=10 : thisngHFTriggerTower.trg_fiber_ch = eta-30;
  }
  myngHFTriggerTower.push_back(thisngHFTriggerTower);
  return ;
}

void ngHFMappingAlgorithm::ConstructngHFCalib(int sideid, int rbxqie10id, int qie10chid)
{
  ngHFCalib thisngHFCalib;                                                                                                                                                                                  
  //set up frontend part
  std::string sideletter; sideid>0 ? sideletter = "P" : sideletter = "M";
  std::string numberletter; ((rbxqie10id/Nqie10Calib)*2 + 1) < 10 ? numberletter = "0" + std::to_string((rbxqie10id/Nqie10Calib)*2 + 1) : numberletter = std::to_string((rbxqie10id/Nqie10Calib)*2 + 1); 
  thisngHFCalib.rbx = "HF" + sideletter + numberletter;
  thisngHFCalib.qie10 = 1; //QIE10 in the ngHF CU
  thisngHFCalib.qie10_fiber = qie10chid%Nqie10_fiberCalib + 4;//
  thisngHFCalib.qie10_ch = qie10chid%Nfiber_ch + 1;
  thisngHFCalib.fiber_ch = qie10chid%Nfiber_ch;
  //thisngHFCalib.qie10_id = 500000;
  //std::string qie10_barcode = "0x3e000000 0xba22f270";
  GetngHFQIEInfoToLMap(
                       thisngHFCalib.rbx, thisngHFCalib.qie10,
                       thisngHFCalib.qie10_id, thisngHFCalib.qie10_barcode
                      );
  thisngHFCalib.sector = rbxqie10id/Nqie10Calib + 1;

  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/Calib/ngCU_patch/ngCU_HOHF_patch.txt
  /*
 input side of the HOHF CU patch:
 - where the HO ring designations are 0z 1m 2m 1p 2p
   and the HF Quadrants are directly indicated
 
 | 0z01 0z04 0z05 0z08 | 0z09 0z12 xxxx xxxx | 0z02 0z03 0z06 0z07 | 0z10 0z11 xxxx xxxx |
 | 1m02 1m04 1m06 1m08 | 1m10 1m12 xxxx xxxx | 1p02 1p04 1p06 1p08 | 1p10 1p12 xxxx xxxx | HFPq1 HFPq2 HFPq3 HFPq4 |
 | 2m02 2m04 2m06 2m08 | 2m10 2m12 xxxx xxxx | 2p02 2p04 2p06 2p08 | 2p10 2p12 xxxx xxxx | HFMq1 HFMq2 HFMq3 HFMq4 |
 
 output side of the HOHF CU patch
 
 | 13b1 13b2 13b3 13b4 | 13b5 13b6 xxxx xxxx | 13b7 13b8 13t1 13t2 | 13t3 13t4 xxxx xxxx |
 | 07b1 07b2 07b3 07b4 | 07b5 07b6 xxxx xxxx | 07b7 07b8 07t1 07t2 | 07t3 07t4 xxxx xxxx | 38t01 38t02 38t03 38t04 |
 | 06b1 06b2 06b3 06b4 | 06b5 06b6 xxxx xxxx | 06b7 06b8 06t1 06t2 | 06t3 06t4 xxxx xxxx | 38t05 38t06 38t07 38t08 |
  */
  //set up patch panel
  thisngHFCalib.ppcol = 5;
  sideid < 0 ? thisngHFCalib.pprow = 1 : thisngHFCalib.pprow = 2;
  /*
 HF trunk CU fibers:
 
 4 duplex octopusses, 1 per hemisphere-side (with just 2 LCs used in each! = 8 fibers total)
 
 - HF+ CU Q1-top Q4-bot = HFPq1 HFPq4
 - HF+ CU Q2-bot Q3-top = HFPq2 HFPq3
 - HF- CU Q1-top Q4-bot = HFMq1 HFMq4
 - HF- CU Q2-top Q3-bot = HFMq2 HFMq3
 
   note: for HF+ CU Q2-bot Q3-top alone, the top/bot are actually reversed according
   to the physical geometry of the quadrants
 - here is a useful link: http://cmsonline.cern.ch/cms-elog/966862
   fib 2 in each octopus is used for ngHF CU
 
 HF uHTR fibers are removed: use a calib octopus to crate 38
  */
  int ngHFP_pplcInsector[4] = {1, 2, 1, 2};
  int ngHFM_pplcInsector[4] = {1, 1, 2, 2};
  sideid < 0 ? thisngHFCalib.pplc = ngHFM_pplcInsector[thisngHFCalib.sector-1] : thisngHFCalib.pplc = ngHFP_pplcInsector[thisngHFCalib.sector-1];
  sideid < 0 ? thisngHFCalib.ppcpl = "HFM_CU" : thisngHFCalib.ppcpl = "HFP_CU";
  sideid > 0 ? thisngHFCalib.dodec = rbxqie10id/Nqie10Calib + 1 : thisngHFCalib.dodec = rbxqie10id/Nqie10Calib + 5;

  //set up backend part
  thisngHFCalib.ucrate = 38;
  // On demand from Dick, era=N HCAL maps: HF calib uhtr changed from 6 to 9 (see email Era N HCAL maps on 12 Oct 2019.)
  //thisngHFCalib.uhtr = 6;
  thisngHFCalib.uhtr = 9;
  sideid > 0 ? thisngHFCalib.uhtr_fiber = rbxqie10id/Nqie10Calib : thisngHFCalib.uhtr_fiber = rbxqie10id/Nqie10Calib + 4;
  // On demand from Dick, era=N HCAL maps, all ngHFcalib channesl FED 1134 -> 1131 (see email Hcal Online client crashing debug with CMSSW_11_0_0_patch1 on 12 Feb 2020)
  thisngHFCalib.ufedid = 1131;

  //set up Geometry part
  thisngHFCalib.side = sideid;
  thisngHFCalib.eta = 1;
  thisngHFCalib.fiber_ch == 0 ? thisngHFCalib.depth = 8 : thisngHFCalib.depth = thisngHFCalib.fiber_ch - 1;
  thisngHFCalib.dphi = 18;
  thisngHFCalib.phi = (rbxqie10id/Nqie10Calib)*18 + 1;

  thisngHFCalib.subdet = "CALIB_HF";
  //Starting from 09 November 2019, all QIE ids are set to 999999 since these parts are taken by Aleko, including QIE constants
  thisngHFCalib.qie10_id = 999999;
  thisngHFCalib.qie10_barcode = "0x00000000";
  if(thisngHFCalib.fiber_ch == 3 && thisngHFCalib.sector == 4)
  {
    thisngHFCalib.depth = 9;
    thisngHFCalib.dphi = 72;
    thisngHFCalib.phi = 1;

    myngHFCalib.push_back(thisngHFCalib);
  }
  if(thisngHFCalib.fiber_ch == 3) return ; //do not fill the calibration channel when fiber channel is 3

  myngHFCalib.push_back(thisngHFCalib);

  return ;
}

void ngHFMappingAlgorithm::LoadngHFQIEMap(std::string QIE10CardMapFileName)
{
  std::ifstream inputFile(QIE10CardMapFileName.c_str());
  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;
      
    //std::istringstream ss(line);
    std::stringstream ss(line);
    ngHFQIE10CardMap thisngHFQIE10CardMap;
    std::string barcode1,barcode2;
   
    ss >> thisngHFQIE10CardMap.rbx >> thisngHFQIE10CardMap.qie >> barcode1 >> barcode2 >> thisngHFQIE10CardMap.qie_id;
    //std::cout << thisngHFQIE10CardMap.rbx << std::endl;
    //std::cout << thisngHFQIE10CardMap.qie << std::endl;
    //std::cout << barcode1 << std::endl;
    //std::cout << barcode2 << std::endl;
    //std::cout << thisngHFQIE10CardMap.qie_id << std::endl;
    thisngHFQIE10CardMap.barcode=barcode1+" "+barcode2;
    myngHFQIE10CardMap.push_back(thisngHFQIE10CardMap);
  }
  return ;
}

void ngHFMappingAlgorithm::GetngHFQIEInfoToLMap(
                                                std::string rbx, int qie,
                                                int &qie10_id, std::string &qie10_barcode
                                               )
{
  bool qie10match = false;
  for(auto i=0; i<myngHFQIE10CardMap.size(); i++)
  {
    qie10match = (rbx==myngHFQIE10CardMap.at(i).rbx) && (qie==std::stoi(myngHFQIE10CardMap.at(i).qie));
    if(qie10match)
    {
      qie10_id = std::stoi(myngHFQIE10CardMap.at(i).qie_id);
      qie10_barcode = myngHFQIE10CardMap.at(i).barcode;
      break;
    }
    else continue;
  }
  if(!qie10match) std::cout << "#QIE 10 card not found in front end coordinates !!!" << std::endl;
  return ;
}
