mkdir -p ./$3/Emap

./HCALLMapProducer HB EMap > ./$3/Emap/Emap_ngHB_$1_$2.txt
./HCALLMapProducer HE EMap > ./$3/Emap/Emap_ngHE_$1_$2.txt
./HCALLMapProducer HF EMap > ./$3/Emap/Emap_ngHF_$1_$2.txt
./HCALLMapProducer HO EMap > ./$3/Emap/Emap_ngHO_$1_$2.txt
./HCALLMapProducer HB EMapHT > ./$3/Emap/EmapHT_ngHB_$1_$2.txt
./HCALLMapProducer HE EMapHT > ./$3/Emap/EmapHT_ngHE_$1_$2.txt
./HCALLMapProducer HF EMapHT > ./$3/Emap/EmapHT_ngHF_$1_$2.txt
./HCALLMapProducer HB EMapCalib > ./$3/Emap/Emapcalib_ngHB_$1_$2.txt
./HCALLMapProducer HE EMapCalib > ./$3/Emap/Emapcalib_ngHE_$1_$2.txt
./HCALLMapProducer HF EMapCalib > ./$3/Emap/Emapcalib_ngHF_$1_$2.txt
./HCALLMapProducer HO EMapCalib > ./$3/Emap/Emapcalib_ngHO_$1_$2.txt
#echo "#Dumping HOCalib EMap Object..."
#echo "#         i    cr    sl    tb   dcc  spigot fib/slb fibch/slbch   subdet   eta   phi   dep" > ./$3/Emap/Emapcalib_HO_$1_$2.txt
#cat officialMap/HO_CU_emap_2018_K.txt | grep "CALIB_HO" >> ./$3/Emap/Emapcalib_HO_$1_$2.txt

echo "#Dumping LaserCalib EMap Object..."
echo "#         i    cr    sl    tb   dcc  spigot fib/slb fibch/slbch   subdet   eta   phi   dep" > ./$3/Emap/Emapcalib_LASMON_$1_$2.txt
cat officialMap/2018HCALEMap_lasermonCalib_K_20180227.txt | grep "LASMON" >> ./$3/Emap/Emapcalib_LASMON_$1_$2.txt

sed -i '/#[a-zA-Z]/d' ./$3/Emap/*.txt
