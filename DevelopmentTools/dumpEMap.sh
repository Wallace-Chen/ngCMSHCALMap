./HCALLMapProducer HB EMap >> Emap_HB_$1_$2.txt
./HCALLMapProducer HE EMap >> Emap_HE_$1_$2.txt
./HCALLMapProducer HF EMap >> Emap_HF_$1_$2.txt
./HCALLMapProducer HO EMap >> Emap_HO_$1_$2.txt
./HCALLMapProducer HB EMapHT >> EmapHT_HB_$1_$2.txt
./HCALLMapProducer HE EMapHT >> EmapHT_HE_$1_$2.txt
./HCALLMapProducer HF EMapHT >> EmapHT_HF_$1_$2.txt
./HCALLMapProducer HB EMapCalib >> Emapcalib_HB_$1_$2.txt
./HCALLMapProducer HE EMapCalib >> Emapcalib_HE_$1_$2.txt
./HCALLMapProducer HF EMapCalib >> Emapcalib_HF_$1_$2.txt
#./HCALLMapProducer HO EMapCalib
echo "#Dumping HOCalib EMap Object..."
echo "#         i    cr    sl    tb   dcc  spigot fib/slb fibch/slbch   subdet   eta   phi   dep" >> Emapcalib_HO_$1_$2.txt
cat officialMap/HO_CU_emap_2018_K.txt | grep "CALIB_HO" >> Emapcalib_HO_$1_$2.txt
echo "#Dumping LaserCalib EMap Object..."
echo "#         i    cr    sl    tb   dcc  spigot fib/slb fibch/slbch   subdet   eta   phi   dep" >> Emapcalib_LASMON_$1_$2.txt
cat officialMap/2018HCALEMap_lasermonCalib_K_20180227.txt | grep "LASMON" >> Emapcalib_LASMON_$1_$2.txt
sed -i '/#[a-zA-Z]/d' *.txt
