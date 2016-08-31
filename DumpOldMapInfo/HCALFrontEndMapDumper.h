//#include "HBHEMappingObject.h" 
//#include "HFMappingObject.h"
//#include "HOMappingObject.h"
#include <iomanip>

namespace HCALFrontEndMapDumper
{
  void HCALFrontEndMapDumper( std::string RunMode, std::vector<HCALFrontEndMapEntry> myHCALFrontEndMapEntries )
  {
    std::ofstream HCALFrontEndMapfile (("HCALFrontEndMap_"+RunMode+"_NoQIE10.txt").c_str());
    if (HCALFrontEndMapfile.is_open())
    {
      char tempbuff[30];
      std::stringstream mystream;
      std::string date;
      time_t myTime;
      time(&myTime);

      strftime(tempbuff,128,"%d.%b.%Y",localtime(&myTime) );
      mystream << tempbuff;
      date = mystream.str();

      //# eta phi depth subdet rbx rm
      HCALFrontEndMapfile << "#file created " + date << std::endl;
      HCALFrontEndMapfile << "#Writing HCAL Front End Map... IOV " + RunMode << std::endl;
      HCALFrontEndMapfile << "#"
                          << std::setw(9) << "eta" << std::setw(9) << "phi" << std::setw(9) << "depth" << std::setw(9) << "subdet" << std::setw(9) << "rbx" << std::setw(9) << "rm"<< std::endl;

      for(int i=0; i<myHCALFrontEndMapEntries.size(); i++)
      {
        if( myHCALFrontEndMapEntries.at(i).subdet == "HOX" ) continue;
        //if( myHCALFrontEndMapEntries.at(i).subdet != "HB" || myHCALFrontEndMapEntries.at(i).subdet != "HO" ) continue;

        HCALFrontEndMapfile << " "          
                            << std::setw(9) << myHCALFrontEndMapEntries.at(i).side*myHCALFrontEndMapEntries.at(i).eta << std::setw(9) << myHCALFrontEndMapEntries.at(i).phi << std::setw(9) << myHCALFrontEndMapEntries.at(i).depth << std::setw(9) << myHCALFrontEndMapEntries.at(i).subdet << std::setw(9) << myHCALFrontEndMapEntries.at(i).rbx << std::setw(9) << myHCALFrontEndMapEntries.at(i).rm
                            << std::endl;
      }
      HCALFrontEndMapfile.close();
    }
    else std::cout << "Unable to open file";
    return ;
  }
}
