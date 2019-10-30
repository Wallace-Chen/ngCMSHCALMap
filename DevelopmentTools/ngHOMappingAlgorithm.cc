#include "ngHOMappingAlgorithm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>

void ngHOMappingAlgorithm::ConstructngHOLMapObject(std::string Mode)
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
            ConstructngHOCalib(irbx,irm,irmfi,ifich);
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

void ngHOMappingAlgorithm::ConstructngHOCalib(int irbx, int irm, int irmfi, int ifich)
{
  return;
}
