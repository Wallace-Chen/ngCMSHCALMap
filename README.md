# ngCMSHCALMap

cmsrel CMSSW_8_0_0

cd CMSSW_8_0_0/src

cmsenv

git clone git@github.com:weihua19900704/ngCMSHCALMap.git

scram b -j 10

To run the code in DevelopmentTools directory:

cd DevelopmentTools

make

./HCALLMapAnalyzer RunMode

The valid RunMode are: HBHEHFVME, HBHEHFuTCA, HOVME

