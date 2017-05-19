# CMSSW
```
cmsrel CMSSW_8_0_0
cd CMSSW_8_0_0/src
cmsenv
```

# SQLite c++ Support
https://www.sqlite.org/download.html
```
cd $CMSSW_BASE/src
wget https://www.sqlite.org/src/tarball/sqlite.tar.gz .
tar xzf sqlite.tar.gz
mkdir bld
cd bld
../sqlite/configure
make
make sqlite3.c
make test
```

# CMS HCAL Logical Map

```
cd $CMSSW_BASE/src
git clone git@github.com:weihuacern/ngCMSHCALMap.git
scram b -j 10
```

To run the code in DevelopmentTools directory:

```
cd $CMSSW_BASE/src/DevelopmentTools
make
```

To analyze the LMap:

```
./HCALLMapAnalyzer RunMode
```

The valid RunMode are: HBHEHFVME, HBHEHFuTCA, HOVME, ngHEuTCA, ngHFuTCA

Plots To be fixed: HBHE VME FE vs BE plot, crate 0 not showed, fpga how to show in letter ?

To produce the LMap:

```
./HCALLMapProducer RunMode PrdMode
./HCALLMapProducer HF LMap
```

The valid RunMode are: HB,HE,HF,HO
The valid PrdMode are: LMap,EMap,FMap
