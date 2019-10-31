mkdir -p ./$3/Umap

echo "Dumping on HBHEUMap, please wait, could be quite long..." && ./HCALLMapProducer HBHEUMap && mv ngHBHEUMap.txt ./$3/Umap/Umap_ngHBHE_$1_$2.txt
echo "Dumping on HOMap, please wait, could be quite long..." && ./HCALLMapProducer HO UMap && mv ngHOUMap.txt  ./$3/Umap/Umap_ngHO_$1_$2.txt
echo "Dumping on HFMap, please wait, could be quite long..." && ./HCALLMapProducer HF UMap && mv ngHFUMap.txt  ./$3/Umap/Umap_ngHF_$1_$2.txt
sed -i '/#[a-zA-Z]/d' ./$3/Umap/*.txt
