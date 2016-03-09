#include "HCALLMapProducer.h"
#include "HCALLMapDump.h"

int main()
{
  HFMappingAlgorithm myHFMappingAlgorithm;
  myHFMappingAlgorithm.ConstructHFLMapObject();

  printHFLMapObject(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);

  return 0;
}

