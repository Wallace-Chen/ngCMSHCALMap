# ngCMSHCALMap

cmsrel CMSSW_8_0_0

cd CMSSW_8_0_0/src

cmsenv

git clone git@github.com:weihuacern/ngCMSHCALMap.git

scram b -j 10

To run the code in DevelopmentTools directory:

cd DevelopmentTools

make

To analyze the LMap:

./HCALLMapAnalyzer RunMode

The valid RunMode are: HBHEHFVME, HBHEHFuTCA, HOVME

Plots To be fixed: HBHE VME FE vs BE plot, crate 0 not showed, fpga how to show in letter ?

To produce the LMap:

./HCALLMapProducer
