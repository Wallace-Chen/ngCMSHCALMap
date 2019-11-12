mkdir -p ./$3/Lmap
#Format, sh dumpLMap.sh K 20180501
#echo _$1_$2.txt
#Lmap and LmapCalib for individual subdetectors
./HCALLMapProducer HB LMap > ./$3/Lmap/Lmap_ngHB_$1_$2.txt
./HCALLMapProducer HE LMap > ./$3/Lmap/Lmap_ngHE_$1_$2.txt
./HCALLMapProducer HF LMap > ./$3/Lmap/Lmap_ngHF_$1_$2.txt
./HCALLMapProducer HO LMap > ./$3/Lmap/Lmap_ngHO_$1_$2.txt
./HCALLMapProducer HB LMapCalib > ./$3/Lmap/Lmap_ngHBcalib_$1_$2.txt
./HCALLMapProducer HE LMapCalib > ./$3/Lmap/Lmap_ngHEcalib_$1_$2.txt
./HCALLMapProducer HF LMapCalib > ./$3/Lmap/Lmap_ngHFcalib_$1_$2.txt
./HCALLMapProducer HO LMapCalib > ./$3/Lmap/Lmap_ngHOcalib_$1_$2.txt
#LmapCalib for HBHE, excluding ped-only channels
./HCALLMapProducer HBHELMapCalib > ./$3/Lmap/Lmap_ngHBHEcalib_$1_$2.txt
#LmapCalib for HBHE, including ped-only channels
./HCALLMapProducer HBHEUMapCalib > ./$3/Lmap/Lmap_ngHBHEcalib_all_$1_$2.txt
#LmapCalib Ped-only channels
./HCALLMapProducer HBHEPedLMap > ./$3/Lmap/Lmap_ngHBHEcalib_ped-only_$1_$2.txt
sed -i '/#[a-zA-Z]/d' ./$3/Lmap/*.txt
