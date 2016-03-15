//#include "HBHEMappingObject.h" 
//#include "HFMappingObject.h"
//#include "HOMappingObject.h"

namespace HCALLMapDumper
{
  void printHFLMapObject(                     
                         std::vector<HFFrontEnd> myHFFrontEnd, std::vector<HFBackEnd> myHFBackEnd, std::vector<HFPMTBox> myHFPMTBox, std::vector<HFGeometry> myHFGeometry, std::vector<HFTriggerTower> myHFTriggerTower
                        )
  {
    std::cout << "#Dumping HF LMap Object..." << std::endl;

    for(auto i=0; i<myHFFrontEnd.size(); i++)
    {
      std::cout //<< "HFGeometry(side,eta,phi,depth): " 
                << myHFGeometry.at(i).side << " " <<  myHFGeometry.at(i).eta << " " << myHFGeometry.at(i).phi << " " << myHFGeometry.at(i).depth << " "
                //<< "HFFrontEnd(rbx,rm,rm_fiber,fiber_ch,qie8,qie8_ch): " 
                << myHFFrontEnd.at(i).rbx << " " << myHFFrontEnd.at(i).rm << " " << myHFFrontEnd.at(i).rm_fiber << " " << myHFFrontEnd.at(i).fiber_ch << " " << myHFFrontEnd.at(i).qie8 << " " << myHFFrontEnd.at(i).qie8_ch << " "
                //<< "HFBackEnd(ucrate,uhtr,uhtr_fiber,fiber_ch): " 
                << myHFBackEnd.at(i).ucrate << " " << myHFBackEnd.at(i).uhtr << " " << myHFBackEnd.at(i).uhtr_fiber << " " << myHFBackEnd.at(i).fiber_ch << " "
                << std::endl;
    }
    return ;
  }

  void printngHFLMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower)
  {
    std::cout << "#Dumping ngHF LMap Object..." << std::endl;

    for(auto i=0; i<myngHFFrontEnd.size(); i++)
    {
      if(i==0) std::cout << "#Side     Eta       Phi     Depth     PMT    PMT_TYPE W_Cable   S_PMT    S_QIE    R_PMT     R_QIE       ngRBX       QIE10  QIE10_CH  QIE10_FI  FI_CH    uCrate     uHTR    uHTR_FI   FI_CH"<< std::endl;
      std::cout << "  "
                //<< "ngHFGeometry(side,eta,phi,depth): "
                << myngHFGeometry.at(i).side << "        " <<  myngHFGeometry.at(i).eta << "        " << myngHFGeometry.at(i).phi << "        " << myngHFGeometry.at(i).depth << "        "
                //<< "ngHFPMTBox(PMT, PMT Type, Winchester Cable): "
                << myngHFPMTBox.at(i).pmt << "        " << myngHFPMTBox.at(i).pmt_type << "        " << myngHFPMTBox.at(i).winchester_cable << "        "
                //<< "Winchester Cable, PIN to PIN"
                << myngHFPMTBox.at(i).s_coax_pmt << "        " << myngHFFrontEnd.at(i).s_coax_qie << "        " << myngHFPMTBox.at(i).r_coax_pmt << "        " << myngHFFrontEnd.at(i).r_coax_qie << "        "
                //<< "ngHFFrontEnd(rbx,rm,rm_fiber,fiber_ch,qie8,qie8_ch): "
                << myngHFFrontEnd.at(i).rbx << "        " << myngHFFrontEnd.at(i).qie10 << "        " << myngHFFrontEnd.at(i).qie10_ch << "        " << myngHFFrontEnd.at(i).qie10_fiber << "        " << myngHFFrontEnd.at(i).fiber_ch << "        "
                //<< "ngHFBackEnd(ucrate,uhtr,uhtr_fiber,fiber_ch): "
                << myngHFBackEnd.at(i).ucrate << "        " << myngHFBackEnd.at(i).uhtr << "        " << myngHFBackEnd.at(i).uhtr_fiber << "        " << myngHFBackEnd.at(i).fiber_ch << "        "
                << std::endl;
    }
    return ;
  }
}
