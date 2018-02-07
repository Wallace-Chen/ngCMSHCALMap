# Setup CMSSW
```
cmsrel CMSSW_8_0_0
cd CMSSW_8_0_0/src
cmsenv
```

# SQLite C++ Support
https://www.sqlite.org/download.html<br />
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
## For package owner
```
cd $CMSSW_BASE/src
git clone git@github.com:weihuacern/ngCMSHCALMap.git
```

## For package developer
- Fork the code with your personal github ID. See [details](https://help.github.com/articles/fork-a-repo/). <br />
- Make a clean git clone in the src directory. <br />
```
cd $CMSSW_BASE/src/
git clone git@github.com:yourgithubid/ngCMSHCALMap.git ngCMSHCALMap
cd ngCMSHCALMap
git remote add upstream git@github.com:weihuacern/ngCMSHCALMap.git
```

- Update your repository to be exactly same like master branch before start your changes: <br />
```
git remote update
git merge upstream/master
```

- Make your own change and commit. <br />
```
git commit -a -m "Added feature A, B, C"
git push
```

- Make a pull request against the ngCMSHCALMap. See [details](https://help.github.com/articles/using-pull-requests/).<br />

- To run the code in DevelopmentTools directory:<br />

```
cd $CMSSW_BASE/src/ngCMSHCALMap/DevelopmentTools
make
```

- To analyze the LMap:<br />

```
./HCALLMapAnalyzer RunMode
```
The valid RunMode are: HBHEHFVME, HBHEHFuTCA, HOVME, ngHEuTCA, ngHFuTCA.<br />
Plots To be fixed: HBHE VME FE vs BE plot, crate 0 not showed, fpga how to show in letter?<br />

- To produce the LMap:<br />
```
./HCALLMapProducer RunMode PrdMode
./HCALLMapProducer HF LMap
```
The valid RunMode are: HB, HE, HF, HO.<br />
The valid PrdMode are: LMap, EMap, FMap, HT, LMapCalib, EMapCalib.<br />

- Shell script to dump the LMap and EMap:<br />
```
sh dumpLMap.sh K 20180501
sh dumpEMap.sh >> 2018HCALEMap_All_K_20180501.txt
```


# Data visualization
- plotly installation and setup
```
pip install --install-option="--prefix=$CMSSW_BASE/python" plotly
python
import plotly
plotly.tools.set_credentials_file(username='DemoAccount', api_key='lr1c37zw81')
```


# Test of GUI
```
javac frm.java
java frm
```

# Documnetation
```
doxygen -g Doxyfile
doxygen Doxyfile
cd latex
make
```

# Pandas Test
- To read xls file and dump Emap directly:<br />
```
cd $CMSSW_BASE/src/ngCMSHCALMap/DevelopmentTools/PandasTest
pip install --install-option="--prefix=$CMSSW_BASE/python" xlrd
export PYTHONPATH=$CMSSW_BASE/python/lib/python2.6/site-packages:$PYTHONPATH
python DumpEMapfromCalib.py >> HCALEmapCALIB_J.txt
```

# Generate QIE tables from Database
- Location of QIE database files: /eos/user/h/hua/QIEDB<br />
```
cd $CMSSW_BASE/src/ngCMSHCALMap/DevelopmentTools/SQLQIEDBTest
python QIETableMaker.py
```
