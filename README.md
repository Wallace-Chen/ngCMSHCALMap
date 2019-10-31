## login from lxplus 7 

```
export SCRAM_ARCH=slc7_amd64_gcc700
```
# Setup CMSSW
```
cmsrel CMSSW_10_6_0
cd CMSSW_10_6_0/src
cmsenv
```

# SQLite C++ Support
- For more details about sqlite/C++ API. See [details](https://www.sqlite.org/download.html). <br />
Probably there's a new version when you install, please then replace the name below (sqlite-autoconf-3300100.tar.gz) with the new name you find.
```
cd $CMSSW_BASE/src
wget https://www.sqlite.org/2019/sqlite-autoconf-3300100.tar.gz -O ./sqlite.tar.gz
tar xzf sqlite.tar.gz
mkdir bld
cd sqlite
./configure --prefix=$CMSSW_BASE/src/bld 
make
make install
cp sqlite3.o ../bld/lib/
chmod 755 ../bld/lib/sqlite3.o
```

## you need to install pandas >= 0.24, openpyxl and xlrd >= 1.0.0 if they are not installed by using

## pandas is fine in lxplus7 and then you can install the rest

```
pip install openpyxl --user
pip install xlrd --user
```
`--user` option you can use if you don't have the privileges to install for example on lxplus

# CMS HCAL Logical Map
## For package owner
```
cd $CMSSW_BASE/src
<!---
git clone git@github.com:weihuacern/ngCMSHCALMap.git
-->
git clone git@github.com:Wallace-Chen/ngCMSHCALMap.git
cd ngCMSHCALMap
git clone git@github.com:ashrafkasem/CMSngHOMAP.git
```

## For package developer
- Fork the code with your personal github ID. See [details](https://help.github.com/articles/fork-a-repo/). <br />
- Make a clean git clone in the src directory. <br />
- Note, here you need to use YOURGITHUBID. <br />
```
cd $CMSSW_BASE/src/
git clone git@github.com:YOURGITHUBID/ngCMSHCALMap.git ngCMSHCALMap
cd ngCMSHCALMap
<!---
git remote add upstream git@github.com:weihuacern/ngCMSHCALMap.git
-->
git remote add upstream git@github.com:Wallace-Chen/ngCMSHCALMap.git
git clone git@github.com:ashrafkasem/CMSngHOMAP.git
```

- Update your repository to be exactly same like master branch before start your changes: <br />
```
git remote update
git merge upstream/master
git submodule update --remote --merge
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
<!---
- To analyze the LMap:<br />

```
./HCALLMapAnalyzer RunMode
```
The valid RunMode are: HBHEHFVME, HBHEHFuTCA, HOVME, ngHEuTCA, ngHFuTCA.<br />
Plots To be fixed: HBHE VME FE vs BE plot, crate 0 not showed, fpga how to show in letter?<br />
-->

- To produce the LMap:<br />
  - The valid RunMode are: HB, HE, HF, HO.<br />                                                                                                                                                            
  - The valid PrdMode are: LMap, EMap, FMap, HT, LMapCalib, EMapCalib.<br />
```
./HCALLMapProducer RunMode PrdMode
./HCALLMapProducer HF LMap
```

- Shell script to dump the LMap and EMap:<br />
```
sh dumpLMap.sh N 20191029 ./
sh dumpEMap.sh N 20191029 ./
sh dumpUMap.sh N 20191029 ./
```

- Shell script to dump all Maps (Emap, Lmap, Umap) one time:<br />
```
sh dumpMap.sh N
```
You'll be prompted twice during this script.

# for ngHO
```
cd $CMSSW_BASE/src/ngCMSHCALMap/DevelopmentTools/CMSngHOMAP
./run_all.py outputdir
```
you will find under the output dir several subdirs 
- `outdir/text`
- `outdir/text_aligned`
- `outdir/xlxs`

the Full Lmap is then can be founded in `outdir/text_aligned/ngHO_Lmap_allCates_alligned.txt`
the Full Emap is then can be founded in `outdir/text_aligned/ngHO_Emap_allCates_alligned.txt`

other files/dirs are used for debugging any problem


<!---
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
-->

# Generate QIE tables from Database
- Location of QIE database files: /eos/user/h/hua/QIEDB<br />
```
cd $CMSSW_BASE/src/ngCMSHCALMap/DevelopmentTools/SQLQIEDBTest
python QIETableMaker.py --QIE11Mode "Normal" >> 2018HCALQIE_All_K_20180501_Normal_HEshunt6_CALIBHEshunt1.txt
python QIETableMaker.py --QIE11Mode "Special" >> 2018HCALQIE_All_K_20180501_Special_HEshunt1_CALIBHEshunt1.txt
```
