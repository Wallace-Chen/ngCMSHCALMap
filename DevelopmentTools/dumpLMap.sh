#Format, sh dumpLMap.sh K 20180501
#echo _$1_$2.txt
./HCALLMapProducer HB LMap >> Lmap_HB_$1_$2.txt
./HCALLMapProducer HE LMap >> Lmap_ngHE_$1_$2.txt
./HCALLMapProducer HF LMap >> Lmap_ngHF_$1_$2.txt
./HCALLMapProducer HO LMap >> Lmap_HO_$1_$2.txt
./HCALLMapProducer HB LMapCalib >> Lmap_HBcalib_$1_$2.txt
./HCALLMapProducer HE LMapCalib >> Lmap_ngHEcalib_$1_$2.txt
./HCALLMapProducer HF LMapCalib >> Lmap_ngHFcalib_$1_$2.txt
./HCALLMapProducer HO LMapCalib >> Lmap_HOcalib_$1_$2.txt
sed -i '/#[a-zA-Z]/d' *.txt
