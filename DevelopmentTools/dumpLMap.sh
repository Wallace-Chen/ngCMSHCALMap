#Format, sh dumpLMap.sh K 20180501
#echo _$1_$2.txt
./HCALLMapProducer HB LMap >> 2018HCALLMap_HB_$1_$2.txt
./HCALLMapProducer HE LMap >> 2018HCALLMap_ngHE_$1_$2.txt
./HCALLMapProducer HF LMap >> 2018HCALLMap_ngHF_$1_$2.txt
./HCALLMapProducer HO LMap >> 2018HCALLMap_HO_$1_$2.txt
./HCALLMapProducer HB LMapCalib >> 2018HCALLMap_HBCalib_$1_$2.txt
./HCALLMapProducer HE LMapCalib >> 2018HCALLMap_ngHECalib_$1_$2.txt
./HCALLMapProducer HF LMapCalib >> 2018HCALLMap_ngHFCalib_$1_$2.txt
#./HCALLMapProducer HO LMapCalib >> 2018HCALLMap_HOCalib_$1_$2.txt
