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
cat PandasTest/HCALEmapCALIB_J.txt | grep "CALIB_HO"
