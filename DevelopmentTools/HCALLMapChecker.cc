#include "HCALLMapChecker.h"

bool HCALLMapChecker::checkngHELMapObject(std::vector<ngHEFrontEnd> myngHEFrontEnd, std::vector<ngHEBackEnd> myngHEBackEnd, std::vector<ngHESiPM> myngHESiPM, std::vector<ngHEGeometry> myngHEGeometry, std::vector<ngHETriggerTower> myngHETriggerTower)
{
  bool passCollisionCheck = false;
  bool passFrontEnd=true, passBackEnd=true, passGeometry=true;

  std::vector<ngHEFrontEnd> copy_myngHEFrontEnd(myngHEFrontEnd.size());
  std::copy( myngHEFrontEnd.begin(), myngHEFrontEnd.end(), copy_myngHEFrontEnd.begin() );
  std::vector<ngHEBackEnd> copy_myngHEBackEnd(myngHEBackEnd.size());
  std::copy( myngHEBackEnd.begin(), myngHEBackEnd.end(), copy_myngHEBackEnd.begin() );
  std::vector<ngHEGeometry> copy_myngHEGeometry(myngHEGeometry.size());
  std::copy( myngHEGeometry.begin(), myngHEGeometry.end(), copy_myngHEGeometry.begin() );

  for(std::vector<ngHEFrontEnd>::iterator i = copy_myngHEFrontEnd.begin();i!= copy_myngHEFrontEnd.end();i++)
  {
    for(std::vector<ngHEFrontEnd>::iterator j = i+1;j!= copy_myngHEFrontEnd.end();j++)
    {
      bool foundCollision= ((*i).rbx==(*j).rbx) && ((*i).rm==(*j).rm) && ((*i).rm_fiber==(*j).rm_fiber) && ((*i).fiber_ch==(*j).fiber_ch);
      if(foundCollision){ passFrontEnd=false; std::cout << "#RBX:" << (*j).rbx << ",RM:" << (*j).rm << ",RM_FI:" << (*j).rm_fiber << ",FI_CH" << (*j).fiber_ch << std::endl; }
    }
  }

  for(std::vector<ngHEBackEnd>::iterator i = copy_myngHEBackEnd.begin();i!= copy_myngHEBackEnd.end();i++)
  {
    for(std::vector<ngHEBackEnd>::iterator j = i+1;j!= copy_myngHEBackEnd.end();j++)
    {
      bool foundCollision= ((*i).ucrate==(*j).ucrate) && ((*i).uhtr==(*j).uhtr) && ((*i).uhtr_fiber==(*j).uhtr_fiber) && ((*i).fiber_ch==(*j).fiber_ch);
      if(foundCollision){ passBackEnd=false; std::cout << "#Crate:" << (*j).ucrate << ",uHTR:" << (*j).uhtr << ",uHTR_FI:" << (*j).uhtr_fiber << ",FI_CH" << (*j).fiber_ch << std::endl; }
    }
  }

  for(std::vector<ngHEGeometry>::iterator i = copy_myngHEGeometry.begin();i!= copy_myngHEGeometry.end();i++)
  {
    for(std::vector<ngHEGeometry>::iterator j = i+1;j!= copy_myngHEGeometry.end();j++)
    {
      bool foundCollision= ((*i).side==(*j).side) && ((*i).eta==(*j).eta) && ((*i).phi==(*j).phi) && ((*i).depth==(*j).depth);
      if(foundCollision && (*j).subdet!="HEX"){ passGeometry=false; std::cout << "#Side:" << (*j).side << ",Eta:" << (*j).eta << ",Phi:" << (*j).phi << ",Depth" << (*j).depth << std::endl; }
    }
  }

  passCollisionCheck = passFrontEnd && passBackEnd && passGeometry;
  return passCollisionCheck;
}

bool HCALLMapChecker::checkngHFLMapObject(std::vector<ngHFFrontEnd> myngHFFrontEnd, std::vector<ngHFBackEnd> myngHFBackEnd, std::vector<ngHFPMTBox> myngHFPMTBox, std::vector<ngHFGeometry> myngHFGeometry, std::vector<ngHFTriggerTower> myngHFTriggerTower)
{
  bool passCollisionCheck = false;
  bool passFrontEnd=true, passBackEnd=true, passGeometry=true;

  std::vector<ngHFFrontEnd> copy_myngHFFrontEnd(myngHFFrontEnd.size());
  std::copy( myngHFFrontEnd.begin(), myngHFFrontEnd.end(), copy_myngHFFrontEnd.begin() );
  std::vector<ngHFBackEnd> copy_myngHFBackEnd(myngHFBackEnd.size());
  std::copy( myngHFBackEnd.begin(), myngHFBackEnd.end(), copy_myngHFBackEnd.begin() );
  std::vector<ngHFGeometry> copy_myngHFGeometry(myngHFGeometry.size());
  std::copy( myngHFGeometry.begin(), myngHFGeometry.end(), copy_myngHFGeometry.begin() );

  for(std::vector<ngHFFrontEnd>::iterator i = copy_myngHFFrontEnd.begin();i!= copy_myngHFFrontEnd.end();i++)
  {
    for(std::vector<ngHFFrontEnd>::iterator j = i+1;j!= copy_myngHFFrontEnd.end();j++)
    {
      bool foundCollision= ((*i).rbx==(*j).rbx) && ((*i).qie10==(*j).qie10) && ((*i).qie10_ch==(*j).qie10_ch);
      if(foundCollision) passFrontEnd=false;
    }
  }

  for(std::vector<ngHFBackEnd>::iterator i = copy_myngHFBackEnd.begin();i!= copy_myngHFBackEnd.end();i++)
  {
    for(std::vector<ngHFBackEnd>::iterator j = i+1;j!= copy_myngHFBackEnd.end();j++)
    {
      bool foundCollision= ((*i).ucrate==(*j).ucrate) && ((*i).uhtr==(*j).uhtr) && ((*i).uhtr_fiber==(*j).uhtr_fiber) && ((*i).fiber_ch==(*j).fiber_ch);
      if(foundCollision) passBackEnd=false;
    }
  }

  for(std::vector<ngHFGeometry>::iterator i = copy_myngHFGeometry.begin();i!= copy_myngHFGeometry.end();i++)
  {
    for(std::vector<ngHFGeometry>::iterator j = i+1;j!= copy_myngHFGeometry.end();j++)
    {
      bool foundCollision= ((*i).side==(*j).side) && ((*i).eta==(*j).eta) && ((*i).phi==(*j).phi) && ((*i).depth==(*j).depth);
      if(foundCollision) passGeometry=false;
    }
  }

  passCollisionCheck = passFrontEnd && passBackEnd && passGeometry;
  return passCollisionCheck;
}
