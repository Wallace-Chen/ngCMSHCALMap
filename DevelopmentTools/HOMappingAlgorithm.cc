#include "HOMappingAlgorithm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>

void HOMappingAlgorithm::ConstructHOLMapObject(std::string Mode)
{

  if(Mode == "Calib")
  {
    std::cout << "#Constructing HO Calib Object..." << std::endl;
    for(int irbx=0;irbx<(NrbxHO0+NrbxHO12);irbx++)
    {
      for(int irm=0;irm<NrmHOCalib;irm++)
      {
        for(int irmfi=0;irmfi<Nrm_fiberCalib;irmfi++)
        {
          for(int ifich=0;ifich<Nfiber_ch;ifich++)
          {
            ConstructHOCalib(irbx,irm,irmfi,ifich);
          }
        }
      }

    }

  }
  else
  {
    std::cout << "Invalid generate mode for HO mapping!" << std::endl;
    return;  
  }

  return;
}

void HOMappingAlgorithm::ConstructHOCalib(int irbx, int irm, int irmfi, int ifich)
{
  HOCalib thisHOCalib;
  std::string sideletter;
  std::string numberletter;

  
  //calculte sideid: -2[24-29], -1[12-17], 0[0-11], 1[18-23], 2[30-35], valid when the numbers of rbx in HO12 are equal 
  int sideid=0;
  if(irbx/(NrbxHO0+NrbxHO12/2)) {sideid = 2;}
  else if(irbx/NrbxHO0) {sideid = 1;}
  if((irbx >= NrbxHO0 && irbx < (NrbxHO0+NrbxHO12/4)) || (irbx >= (NrbxHO0+NrbxHO12/2) && irbx < (NrbxHO0+NrbxHO12/4*3)))
  {
    sideid = -sideid;
  }
  

  //frontend
  thisHOCalib.rm = 5;
  thisHOCalib.rm_fiber = 1;
  thisHOCalib.fiber_ch = ifich;

  //detector
  thisHOCalib.eta = sideid;
  thisHOCalib.side = ( (thisHOCalib.eta == 0) ? 0 : thisHOCalib.eta/abs(thisHOCalib.eta));
  thisHOCalib.dphi = ( (thisHOCalib.eta == 0) ? 6 : 12 );
  thisHOCalib.name = "CALIB_HO";
  thisHOCalib.det  = "HO";
  thisHOCalib.ch_type = (thisHOCalib.fiber_ch == 2) ? 7 : thisHOCalib.fiber_ch;

  int sector;
  switch (thisHOCalib.eta)
  {
    case 0:
      sideletter = "0";
      sector = irbx+1;
      break;

    case -1:
      sideletter = "1M";
      sector = 2*(irbx+1-NrbxHO0);
      break;

    case 1:
      sideletter = "1P";
      sector = 2*(irbx+1-NrbxHO0-NrbxHO12/4);
      break;

    case -2:
      sideletter = "2M";
      sector = 2*(irbx+1-NrbxHO0-NrbxHO12/2);
      break;

    case 2:
      sideletter = "2P";
      sector = 2*(irbx+1-NrbxHO0-NrbxHO12/4*3);
      break;

    default:
      std::cout << "Error occured when determing eta!" << std::endl;
      return;
  }
 
  //detector and frontend 
  numberletter = (sector < 10) ? ("0"+std::to_string(sector)) : std::to_string(sector); 
  thisHOCalib.rbx = "HO"+sideletter+numberletter ;
  thisHOCalib.sector = sector;
  thisHOCalib.phi = ( thisHOCalib.side == 0 ) ? HOphiInrbxrmid[(thisHOCalib.sector-1)*6] : HOphiInrbxrmid[(thisHOCalib.sector/2-1)*12];
  thisHOCalib.qie8_id = 999994;

  //Filter: Normally 2 channels per fiber except 5 fibers having 3 channels, defined in the array rbxSPHOCalib
  int i=0;
  while(rbxSPHOCalib[i] != "")
  {
    using namespace std;
    if( !thisHOCalib.rbx.compare(rbxSPHOCalib[i]) && (thisHOCalib.fiber_ch == 2) )
    {
      i = -1; //flag meaning this is on the list
      break;
    }
    i++;
  }
  if((thisHOCalib.fiber_ch == 2) && (i != -1))
  {
    return;
  }

  //Patch Panel---Frontend
  (thisHOCalib.eta == 0) ?  thisHOCalib.ppcpl = thisHOCalib.det + "-0_CU" : thisHOCalib.ppcpl = thisHOCalib.det + std::to_string(thisHOCalib.eta) + "_CU";
  int HO0ppLCInWedge[8] = {1, 3, 3, 1, 1, 3, 3, 1};//for HO0 rbx pplc variable
  thisHOCalib.pprow = 3 - abs(thisHOCalib.eta);
  //HO0 and HO12 have different arrangement, needs separate algorithm. Only valid when sector<16!!
  if( thisHOCalib.side == 0 )
  {
    thisHOCalib.pplc = ((thisHOCalib.sector-1)/2)%NppCol + 1;
    thisHOCalib.ppcol = HO0ppLCInWedge[(thisHOCalib.sector-1)%8]+thisHOCalib.sector/9;
    //brute force to find all sectors which have the same ppcol value, i+1 is the sector running from 1 to NrbxHO0 (12). Then give value to ppcpl.
    for(int i=0;i<NrbxHO0;i++)
    {
      if( ( HO0ppLCInWedge[(i+1-1)%8]+(i+1)/9 ) == thisHOCalib.ppcol )
      {
        thisHOCalib.ppcpl = thisHOCalib.ppcpl + "_" + std::to_string(i+1);
      }
    }
  } 
  else if( abs(thisHOCalib.side) == 1 )
  {
    thisHOCalib.pplc = (thisHOCalib.sector/2-1)%NppCol + 1;
    thisHOCalib.ppcol = (thisHOCalib.side == -1) ? (thisHOCalib.sector/2-1)/NppCol + 1 : (thisHOCalib.sector/2-1)/NppCol + 1 + 2;
    //ppcpl value for this part is kind of tricky, especially for _2-8, no good algorithm for the time being...
    ( thisHOCalib.ppcol == 1 || thisHOCalib.ppcol == 3 ) ? thisHOCalib.ppcpl = thisHOCalib.ppcpl + "_2-8" : thisHOCalib.ppcpl = thisHOCalib.ppcpl + "_10_12";
  }

  //Backend
  int HOCrateInWedgeCalib[3] = {13, 7, 6};//for HO crate variable
  int HOdccInWedgeCalib[3] = {30, 26, 28};//for HO dcc variable
  int HOPatchPanelSlotOccuNum[NppLC] = {4, 2, 4, 2};//This array is the number of coloums occupied for every slots, same for HO0 and HO12 in this case
  thisHOCalib.crate = HOCrateInWedgeCalib[abs(thisHOCalib.eta)];
  thisHOCalib.dcc = HOdccInWedgeCalib[abs(thisHOCalib.eta)];
  thisHOCalib.htr = 8;
  //This is to calculate the offset, see patch panel graph for demonstration
  int offset = 0;
  for(int i=0;i<thisHOCalib.ppcol-1;i++)
  {
    offset += HOPatchPanelSlotOccuNum[i];
  }

  thisHOCalib.htr_fiber = (thisHOCalib.pplc + offset - 1)%Nhtr_fiber + 1;
  if( (thisHOCalib.pplc + offset - 1)/Nhtr_fiber == 1)
  {
    thisHOCalib.fpga = "top";
    thisHOCalib.spigot = 12;
  }
  else{ thisHOCalib.fpga = "bot"; thisHOCalib.spigot = 13;}

  myHOCalib.push_back(thisHOCalib);
  return;
}
