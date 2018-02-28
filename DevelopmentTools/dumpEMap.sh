./HCALLMapProducer HB EMap
./HCALLMapProducer HE EMap
./HCALLMapProducer HF EMap
./HCALLMapProducer HO EMap
./HCALLMapProducer HB EMapHT
./HCALLMapProducer HE EMapHT
./HCALLMapProducer HF EMapHT
./HCALLMapProducer HB EMapCalib
./HCALLMapProducer HE EMapCalib
./HCALLMapProducer HF EMapCalib
#./HCALLMapProducer HO EMapCalib
echo "#Dumping HOCalib EMap Object..."
echo "#         i    cr    sl    tb   dcc  spigot fib/slb fibch/slbch   subdet   eta   phi   dep"
cat officialMap/HO_CU_emap_2018_K.txt | grep "CALIB_HO"
echo "#Dumping LaserCalib EMap Object..."
echo "#         i    cr    sl    tb   dcc  spigot fib/slb fibch/slbch   subdet   eta   phi   dep"
cat officialMap/2018HCALEMap_lasermonCalib_K_20180227.txt | grep "LASMON"
