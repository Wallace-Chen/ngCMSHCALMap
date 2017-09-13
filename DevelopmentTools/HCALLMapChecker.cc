#include "HCALLMapChecker.h"

bool HCALLMapChecker::checkHBLMapObject(std::vector<HBFrontEnd> myHBFrontEnd, std::vector<HBBackEnd> myHBBackEnd, std::vector<HBHPD> myHBHPD, std::vector<HBGeometry> myHBGeometry, std::vector<HBTriggerTower> myHBTriggerTower)
{
  bool passCollisionCheck = false;
  bool passFrontEnd=true, passBackEnd=true, passGeometry=true;

  std::vector<HBFrontEnd> copy_myHBFrontEnd(myHBFrontEnd.size());
  std::copy( myHBFrontEnd.begin(), myHBFrontEnd.end(), copy_myHBFrontEnd.begin() );
  std::vector<HBBackEnd> copy_myHBBackEnd(myHBBackEnd.size());
  std::copy( myHBBackEnd.begin(), myHBBackEnd.end(), copy_myHBBackEnd.begin() );
  std::vector<HBGeometry> copy_myHBGeometry(myHBGeometry.size());
  std::copy( myHBGeometry.begin(), myHBGeometry.end(), copy_myHBGeometry.begin() );

  for(std::vector<HBFrontEnd>::iterator i = copy_myHBFrontEnd.begin();i!= copy_myHBFrontEnd.end();i++)
  {
    for(std::vector<HBFrontEnd>::iterator j = i+1;j!= copy_myHBFrontEnd.end();j++)
    {
      bool foundCollision= ((*i).rbx==(*j).rbx) && ((*i).rm==(*j).rm) && ((*i).rm_fiber==(*j).rm_fiber) && ((*i).fiber_ch==(*j).fiber_ch);
      if(foundCollision){ passFrontEnd=false; std::cout << "#RBX:" << (*j).rbx << ",RM:" << (*j).rm << ",RM_FI:" << (*j).rm_fiber << ",FI_CH" << (*j).fiber_ch << std::endl; }
    }
  }

  for(std::vector<HBBackEnd>::iterator i = copy_myHBBackEnd.begin();i!= copy_myHBBackEnd.end();i++)
  {
    for(std::vector<HBBackEnd>::iterator j = i+1;j!= copy_myHBBackEnd.end();j++)
    {
      bool foundCollision= ((*i).ucrate==(*j).ucrate) && ((*i).uhtr==(*j).uhtr) && ((*i).uhtr_fiber==(*j).uhtr_fiber) && ((*i).fiber_ch==(*j).fiber_ch);
      if(foundCollision){ passBackEnd=false; std::cout << "#Crate:" << (*j).ucrate << ",uHTR:" << (*j).uhtr << ",uHTR_FI:" << (*j).uhtr_fiber << ",FI_CH" << (*j).fiber_ch << std::endl; }
    }
  }

  for(std::vector<HBGeometry>::iterator i = copy_myHBGeometry.begin();i!= copy_myHBGeometry.end();i++)
  {
    for(std::vector<HBGeometry>::iterator j = i+1;j!= copy_myHBGeometry.end();j++)
    {
      bool foundCollision= ((*i).side==(*j).side) && ((*i).eta==(*j).eta) && ((*i).phi==(*j).phi) && ((*i).depth==(*j).depth);
      if(foundCollision){ passGeometry=false; std::cout << "#Side:" << (*j).side << ",Eta:" << (*j).eta << ",Phi:" << (*j).phi << ",Depth" << (*j).depth << std::endl; }
    }
  }

  passCollisionCheck = passFrontEnd && passBackEnd && passGeometry;
  return passCollisionCheck;
}

bool HCALLMapChecker::checkngHBLMapObject(std::vector<ngHBFrontEnd> myngHBFrontEnd, std::vector<ngHBBackEnd> myngHBBackEnd, std::vector<ngHBSiPM> myngHBSiPM, std::vector<ngHBGeometry> myngHBGeometry, std::vector<ngHBTriggerTower> myngHBTriggerTower)
{
  bool passCollisionCheck = false;
  bool passFrontEnd=true, passBackEnd=true, passGeometry=true;

  std::vector<ngHBFrontEnd> copy_myngHBFrontEnd(myngHBFrontEnd.size());
  std::copy( myngHBFrontEnd.begin(), myngHBFrontEnd.end(), copy_myngHBFrontEnd.begin() );
  std::vector<ngHBBackEnd> copy_myngHBBackEnd(myngHBBackEnd.size());
  std::copy( myngHBBackEnd.begin(), myngHBBackEnd.end(), copy_myngHBBackEnd.begin() );
  std::vector<ngHBGeometry> copy_myngHBGeometry(myngHBGeometry.size());
  std::copy( myngHBGeometry.begin(), myngHBGeometry.end(), copy_myngHBGeometry.begin() );

  for(std::vector<ngHBFrontEnd>::iterator i = copy_myngHBFrontEnd.begin();i!= copy_myngHBFrontEnd.end();i++)
  {
    for(std::vector<ngHBFrontEnd>::iterator j = i+1;j!= copy_myngHBFrontEnd.end();j++)
    {
      bool foundCollision= ((*i).rbx==(*j).rbx) && ((*i).rm==(*j).rm) && ((*i).rm_fiber==(*j).rm_fiber) && ((*i).fiber_ch==(*j).fiber_ch);
      if(foundCollision){ passFrontEnd=false; std::cout << "#RBX:" << (*j).rbx << ",RM:" << (*j).rm << ",RM_FI:" << (*j).rm_fiber << ",FI_CH" << (*j).fiber_ch << std::endl; }
    }
  }

  for(std::vector<ngHBBackEnd>::iterator i = copy_myngHBBackEnd.begin();i!= copy_myngHBBackEnd.end();i++)
  {
    for(std::vector<ngHBBackEnd>::iterator j = i+1;j!= copy_myngHBBackEnd.end();j++)
    {
      bool foundCollision= ((*i).ucrate==(*j).ucrate) && ((*i).uhtr==(*j).uhtr) && ((*i).uhtr_fiber==(*j).uhtr_fiber) && ((*i).fiber_ch==(*j).fiber_ch);
      if(foundCollision){ passBackEnd=false; std::cout << "#Crate:" << (*j).ucrate << ",uHTR:" << (*j).uhtr << ",uHTR_FI:" << (*j).uhtr_fiber << ",FI_CH" << (*j).fiber_ch << std::endl; }
    }
  }

  for(std::vector<ngHBGeometry>::iterator i = copy_myngHBGeometry.begin();i!= copy_myngHBGeometry.end();i++)
  {
    for(std::vector<ngHBGeometry>::iterator j = i+1;j!= copy_myngHBGeometry.end();j++)
    {
      bool foundCollision= ((*i).side==(*j).side) && ((*i).eta==(*j).eta) && ((*i).phi==(*j).phi) && ((*i).depth==(*j).depth);
      if(foundCollision && (*j).subdet!="HBX"){ passGeometry=false; std::cout << "#Side:" << (*j).side << ",Eta:" << (*j).eta << ",Phi:" << (*j).phi << ",Depth" << (*j).depth << std::endl; }
    }
  }

  passCollisionCheck = passFrontEnd && passBackEnd && passGeometry;
  return passCollisionCheck;
}

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
