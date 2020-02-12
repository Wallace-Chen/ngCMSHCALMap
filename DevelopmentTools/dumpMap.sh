if [ "$#" -eq 0 ]; then
  era="M"
  echo "No era parameter, use " ${era}
else
  LC_ALL=C # Turn off locale.
  if [[ $1 == [A-Z] ]]; then
    era=$1
    echo "Era parameter " ${era}
  else
    era="M"
    echo "Invalid era parameter, use " ${era}
  fi
fi
dir=$(date +"%Y-%m-%d")
mkdir -p ./${dir}
printf "Now dumping EMap...\n"
name=$(date +"%Y%m%d")

sh ./dumpEMap.sh ${era} ${name} ${dir}

printf "\nEMap done, to dump LMap, do you want to write the new mapping into the database?"
printf "  \nIf you want to write data, LMaps in the database will be deleted before writing."
printf "\nType N for not touching database (only dump)"
printf "\nType B, E, F, O to delete corresponding H(B,E,F,O) LMaps, or any combination of them to delete multiple LMaps, 'BEO' for example for deleting HB HE and HO LMaps"
printf "  \nLMap and CalibLMap will be deleted and written together for the given sub detector.\n"
read answer
if [[ $answer =~ "B" || $answer =~ "b" ]]
then
  printf "\nngHB (Calib)LMaps deleted."
    echo ".timeout 2000
    DROP TABLE ngHBLogicalMap;
    DROP TABLE ngHBCalibLogicalMap;
    .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
fi
if [[ $answer =~ "E" || $answer =~ "e" ]]
then
  printf "\nngHE (Calib)LMaps deleted."
    echo ".timeout 2000
    DROP TABLE ngHELogicalMap;
    DROP TABLE ngHECalibLogicalMap;
    .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
fi
if [[ $answer =~ "F" || $answer =~ "f" ]]
then
  printf "\nngHF (Calib)LMaps deleted."
    echo ".timeout 2000
    DROP TABLE ngHFLogicalMap;
    DROP TABLE ngHFCalibLogicalMap;
    .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
fi
if [[ $answer =~ "O" || $answer =~ "o" ]]
then
  printf "\nHO (Calib)LMaps deleted."
    echo ".timeout 2000
    DROP TABLE ngHOLogicalMap;
    DROP TABLE ngHOCalibLogicalMap;
    .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
fi
if [[ ! $answer =~ "B" && ! $answer =~ "b" && ! $answer =~ "E" && ! $answer =~ "e" && ! $answer =~ "F" && ! $answer =~ "f" && ! $answer =~ "O" && ! $answer =~ "o" ]]
then
  printf "\nYou choose not to touch LMaps in the database, now will dump it only."
fi

sh ./dumpLMap.sh ${era} ${name} ${dir}

printf "\n\nLMap done, to dump UMap, do you want to clear UMaps in offcial map database?"
printf "\nNote Umap dump will be based on the database, if your map is different from that in database, please MUST choose to clear it before dumping it!!!."
printf "\nType N for not clearing (UMap will be extracted from UMaps in the dataset)" 
printf "\nType BE to clear HBHEUMap, O to clear HOUMap and F to clear HF UMap, or any combination of them to clear multiple sub detectors."
read answer
if [[ $answer =~ "BE" ]];
then
  printf "\nYou choose to clear ngHBHEUniversalMap in database..."
  echo ".timeout 2000
  DROP TABLE ngHBHEUniversalMap;
  .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
fi
if [[ $answer =~ "O" ]];
then
  printf "\nYou choose to clear HOUMap in database..."
  echo ".timeout 2000
  DROP TABLE ngHOUniversalMap;
  .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
  printf "\nNote filling database will take quite long"
fi
if [[  $answer =~ "F" ]]
then
  printf "\nYou choose to clear HF UMaps in database..."
  echo ".timeout 2000
  DROP TABLE ngHFUniversalMap;
  .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
  printf "\nNote filling database will take quite long"
fi
if [[ $answer =~ "N" ]];
then
  printf "\nYou choose not to touch UMaps in the database, now will dump it only."
fi

sh ./dumpUMap.sh ${era} ${name} ${dir}

printf "\nAll done, please check the folder: " ${dir}
