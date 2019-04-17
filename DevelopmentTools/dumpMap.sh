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
echo "Now dumping LMap and EMap..."
name=$(date +"%Y%m%d")
sh ./dumpLMap.sh ${era} ${name} ${dir}
sh ./dumpEMap.sh ${era} ${name} ${dir}
echo "LMap and EMap done, to dump UMap, do you want to clear UMaps in offcial map database?"
echo "Umap dump will be based on the database, if your map is different from that in database, please clear it first."
echo "Type N for not clearing, BE to clear HBHEUMap, HO to clear HOUMap and BEO to clear both UMaps."
read answer
while true
do
  if [[ $answer == "N" ]];
  then
    echo "You choose not to clear in database, now will dump UMap..."
    break
  elif [[ $answer == "BE" ]];
  then
    echo "You choose to clear ngHBHEUniversalMap in database..."
    echo ".timeout 2000
    DROP TABLE ngHBHEUniversalMap;
    .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
    break
  elif [[ $answer == "HO" ]];
  then
    echo "You choose to clear HOUMap in database..."
    echo ".timeout 2000
    DROP TABLE HOUniversalMap;
    .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
    echo "Note filling database will take quite long"
    break
  elif [[  $answer == "BEO" ]]
  then
    echo "You choose to clear both UMaps in database..."
    echo ".timeout 2000
    DROP TABLE HOUniversalMap;
    DROP TABLE ngHBHEUniversalMap;
    .quit" | sqlite3 ./officialMap/HCALLogicalMap.db
    echo "Note filling database will take quite long"
    break
  else
    read -p "Your input does not match options listed above. Please try again: " answer
  fi
done

sh ./dumpUMap.sh ${era} ${name} ${dir}
echo "All done, please check the folder: " ${dir}
