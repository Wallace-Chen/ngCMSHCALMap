#include <sstream>
#include <fstream>
#include <vector>
#include "QIE10Gen.h"

void GetQIE10LMap(
                  std::string QIE10LMapFileName,
                  std::vector<QIE10LMap> &myQIE10LMap
                 )

{
  std::ifstream inputFile(QIE10LMapFileName.c_str());

  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;
    std::istringstream ss(line);
    QIE10LMap thisQIE10LMap;

    int tmp;
    std::string tmp_str;
       
    //#side eta phi dphi depth det 
    //rbx wedge Box_type W_cable tower row col PMT base-board anode S-coax-PMT S-coax-QIE R-coax-PMT R-coax-QIE
    //QIE rm qie qie-conn qie_ch qie_fib fib_ch trunk_fib trunk 
    //crate uHTR uHTR-MTP uHTR_fib fedid QIEid LED
 
    //1 33 39 2 4 HF 
    //ngHFP05 11 B 1 H18 4 4 7 B 3 9 4 10 3 
    //QIE10 -1 4 TOP 2 4 1 1 3HF14200P7F04/0/S2F07/MTP3 
    //36 3 0 0 1132 500613 1

    ss >> thisQIE10LMap.side >> thisQIE10LMap.eta >> thisQIE10LMap.phi >> tmp >> thisQIE10LMap.depth >> thisQIE10LMap.subdet
       >> thisQIE10LMap.rbx >> tmp >> tmp_str >> tmp >> tmp_str >> tmp >> tmp >> tmp >> tmp_str >> tmp >> tmp >> tmp >> tmp >> tmp
       >> tmp_str >> tmp >> thisQIE10LMap.qie_card >> tmp_str >> thisQIE10LMap.qie_ch >> tmp >> tmp >> tmp >> tmp_str
       >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;
    
    myQIE10LMap.push_back(thisQIE10LMap);
  } 

  return ;
}

void GetQIE10Condition(
                       std::string QIE10ConditionFileName,
                       std::vector<QIE10Condition> &myQIE10Condition
                      )

{
  std::ifstream inputFile(QIE10ConditionFileName.c_str());

  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;
    
    std::istringstream ss(line);
    QIE10Condition thisQIE10Condition;
    int tmp;
    std::string tmp_str;
    //# crate slot s/n channel 
    //4 x offsets capID0 4 x offsets capID1 4 x offsets capID2 4 x offsets capID3 
    //4 x slopes capID0 4 x slopes capID1 4 x slopes capID2 4 x slopes capID3
    ss >> thisQIE10Condition.crate >> thisQIE10Condition.slot >> thisQIE10Condition.QIE10_id >> thisQIE10Condition.QIE10_ch
       >> thisQIE10Condition.offsets[0] >> thisQIE10Condition.offsets[1] >> thisQIE10Condition.offsets[2] >> thisQIE10Condition.offsets[3] >> thisQIE10Condition.offsets[4] >> thisQIE10Condition.offsets[5] >> thisQIE10Condition.offsets[6] >> thisQIE10Condition.offsets[7] >> thisQIE10Condition.offsets[8] >> thisQIE10Condition.offsets[9] >> thisQIE10Condition.offsets[10] >> thisQIE10Condition.offsets[11] >> thisQIE10Condition.offsets[12] >> thisQIE10Condition.offsets[13] >> thisQIE10Condition.offsets[14] >> thisQIE10Condition.offsets[15]
       >> thisQIE10Condition.slopes[0] >> thisQIE10Condition.slopes[1] >> thisQIE10Condition.slopes[2] >> thisQIE10Condition.slopes[3] >> thisQIE10Condition.slopes[4] >> thisQIE10Condition.slopes[5] >> thisQIE10Condition.slopes[6] >> thisQIE10Condition.slopes[7] >> thisQIE10Condition.slopes[8] >> thisQIE10Condition.slopes[9] >> thisQIE10Condition.slopes[10] >> thisQIE10Condition.slopes[11] >> thisQIE10Condition.slopes[12] >> thisQIE10Condition.slopes[13] >> thisQIE10Condition.slopes[14] >> thisQIE10Condition.slopes[15];

    myQIE10Condition.push_back(thisQIE10Condition);
  }

  return ;
}

int main()
{
  std::vector<QIE10Condition> myQIE10Condition;
  std::vector<QIE10LMap> myQIE10LMap;

  GetQIE10Condition("QIE10_conditions.txt", myQIE10Condition);
  GetQIE10LMap("QIE10_LMap.txt", myQIE10LMap);

  std::cout << "#Printing QIE10 Conditions information!" << std::endl;
  for(std::vector<QIE10Condition>::iterator it = myQIE10Condition.begin(); it != myQIE10Condition.end(); ++it) 
  {
    (*it).printQIE10ConditionInfo();
  }
  std::cout << "#Printing QIE10 LMap information!" << std::endl;
  for(std::vector<QIE10LMap>::iterator it = myQIE10LMap.begin(); it != myQIE10LMap.end(); ++it)
  { 
    (*it).printQIE10LMapInfo();
  }

  std::vector<QIE10Table> myQIE10Table;
  std::cout << "#Linking QIE10 condition constant table..." << std::endl;
  for(std::vector<QIE10LMap>::iterator it1 = myQIE10LMap.begin(); it1 != myQIE10LMap.end(); ++it1)
  {
    for(std::vector<QIE10Condition>::iterator it2 = myQIE10Condition.begin(); it2 != myQIE10Condition.end(); ++it2)
    {
      bool matched = ((*it1).qie_card == (*it2).slot) && ((*it1).qie_ch == (*it2).QIE10_ch);
      if( matched )
      { 
        std::cout << "Matched!" << std::endl;
        QIE10Table thisQIE10Table;
        thisQIE10Table.eta = (*it1).eta * (*it1).side;
        thisQIE10Table.phi = (*it1).phi;
        thisQIE10Table.depth = (*it1).depth;
        thisQIE10Table.subdet = (*it1).subdet;
        for(int i=0;i<16;i++)
        {
          thisQIE10Table.offsets[i] = (*it2).offsets[i];
          thisQIE10Table.slopes[i] = (*it2).slopes[i];
        }
        myQIE10Table.push_back(thisQIE10Table);
        break;
      }
      else
        continue;
    }
  }

  std::cout << "#Printing QIE10 condition constant table!" << std::endl;
  for(std::vector<QIE10Table>::iterator it = myQIE10Table.begin(); it != myQIE10Table.end(); ++it)
  {
    (*it).printQIE10TableInfo();
  }

  return 0;
}
