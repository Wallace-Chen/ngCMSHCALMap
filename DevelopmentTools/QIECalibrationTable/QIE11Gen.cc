#include <sstream>
#include <fstream>
#include <vector>
#include "QIE11Gen.h"

void GetQIE11LMap(
                  std::string QIE11LMapFileName,
                  std::vector<QIE11LMap> &myQIE11LMap
                 )

{
  std::ifstream inputFile(QIE11LMapFileName.c_str());

  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;
    std::istringstream ss(line);
    QIE11LMap thisQIE11LMap;

    int tmp;
    std::string tmp_str;
 
    //#side  eta  phi  depth  dphi  det  
    //RBX  wedge  rm  BV/pix  card  
    //QIE  rm_fib  fib_ch  pp_col  pp_row  pp_coupler  pp_LC  dodec  
    //crate  uhtr  uhtr_fib  fedid  QIEid
    
    //1  29  63  1  2  ngHE  
    //HEP17  17  1  8  1  
    //7  2  0  1  1  HEP17 RM1A  2  1  
    //34  11  12  1114  600429      
    
    ss >> thisQIE11LMap.side >> thisQIE11LMap.eta >> thisQIE11LMap.phi >> thisQIE11LMap.depth >> tmp >> thisQIE11LMap.subdet
       >> thisQIE11LMap.rbx >> tmp >> tmp >> tmp >> tmp 
       >> thisQIE11LMap.qie_ch >> tmp >> tmp >> tmp >> tmp >> tmp_str >> tmp_str >> tmp >> tmp
       >> tmp >> tmp >> tmp >> tmp >> thisQIE11LMap.qie_id;
    
    myQIE11LMap.push_back(thisQIE11LMap);
  } 

  return ;
}

void GetQIE11Condition(
                       std::string QIE11ConditionFileName,
                       std::vector<QIE11Condition> &myQIE11Condition,
                       std::string ShuntMode
                      )

{
  std::ifstream inputFile(QIE11ConditionFileName.c_str());

  std::string line;
  while( std::getline(inputFile, line) )
  {
    if(line.at(0) == '#') continue;
    
    std::istringstream ss(line);
    QIE11Condition thisQIE11Condition;
    int tmp;
    std::string tmp_str;
    //# crate slot s/n channel 
    //4 x offsets capID0 4 x offsets capID1 4 x offsets capID2 4 x offsets capID3 
    //4 x slopes capID0 4 x slopes capID1 4 x slopes capID2 4 x slopes capID3
    ss >> thisQIE11Condition.QIE11_id >> thisQIE11Condition.QIE11_ch >> thisQIE11Condition.QIE11_shunt
       >> thisQIE11Condition.offsets[0] >> thisQIE11Condition.offsets[1] >> thisQIE11Condition.offsets[2] >> thisQIE11Condition.offsets[3] >> thisQIE11Condition.offsets[4] >> thisQIE11Condition.offsets[5] >> thisQIE11Condition.offsets[6] >> thisQIE11Condition.offsets[7] >> thisQIE11Condition.offsets[8] >> thisQIE11Condition.offsets[9] >> thisQIE11Condition.offsets[10] >> thisQIE11Condition.offsets[11] >> thisQIE11Condition.offsets[12] >> thisQIE11Condition.offsets[13] >> thisQIE11Condition.offsets[14] >> thisQIE11Condition.offsets[15]
       >> thisQIE11Condition.slopes[0] >> thisQIE11Condition.slopes[1] >> thisQIE11Condition.slopes[2] >> thisQIE11Condition.slopes[3] >> thisQIE11Condition.slopes[4] >> thisQIE11Condition.slopes[5] >> thisQIE11Condition.slopes[6] >> thisQIE11Condition.slopes[7] >> thisQIE11Condition.slopes[8] >> thisQIE11Condition.slopes[9] >> thisQIE11Condition.slopes[10] >> thisQIE11Condition.slopes[11] >> thisQIE11Condition.slopes[12] >> thisQIE11Condition.slopes[13] >> thisQIE11Condition.slopes[14] >> thisQIE11Condition.slopes[15];

    if( thisQIE11Condition.QIE11_shunt == ShuntMode ) myQIE11Condition.push_back(thisQIE11Condition);
    else continue;
  }

  return ;
}

int main(int argc, char* argv[])
{
  std::string ShuntMode = argv[1];

  std::vector<QIE11Condition> myQIE11Condition;
  std::vector<QIE11LMap> myQIE11LMap;

  GetQIE11Condition("QIE11_conditions.txt", myQIE11Condition, ShuntMode);
  GetQIE11LMap("QIE11_LMap.txt", myQIE11LMap);

  /*
  std::cout << "#Printing QIE11 Conditions information!" << std::endl;
  for(std::vector<QIE11Condition>::iterator it = myQIE11Condition.begin(); it != myQIE11Condition.end(); ++it) 
  {
    (*it).printQIE11ConditionInfo();
  }
  std::cout << "#Printing QIE11 LMap information!" << std::endl;
  for(std::vector<QIE11LMap>::iterator it = myQIE11LMap.begin(); it != myQIE11LMap.end(); ++it)
  { 
    (*it).printQIE11LMapInfo();
  }
  */

  std::vector<QIE11Table> myQIE11Table;
  std::cout << "#Linking QIE11 condition constant table..." << std::endl;
  for(std::vector<QIE11LMap>::iterator it1 = myQIE11LMap.begin(); it1 != myQIE11LMap.end(); ++it1)
  {
    for(std::vector<QIE11Condition>::iterator it2 = myQIE11Condition.begin(); it2 != myQIE11Condition.end(); ++it2)
    {
      bool matched = ((*it1).qie_id == (*it2).QIE11_id) && ((*it1).qie_ch == (*it2).QIE11_ch) && (ShuntMode==(*it2).QIE11_shunt);
      if( matched )
      { 
        //std::cout << "Matched!" << std::endl;
        QIE11Table thisQIE11Table;
        thisQIE11Table.eta = (*it1).eta * (*it1).side;
        thisQIE11Table.phi = (*it1).phi;
        thisQIE11Table.depth = (*it1).depth;
        thisQIE11Table.subdet = (*it1).subdet;
        for(int i=0;i<16;i++)
        {
          thisQIE11Table.offsets[i] = (*it2).offsets[i];
          thisQIE11Table.slopes[i] = (*it2).slopes[i];
        }
        myQIE11Table.push_back(thisQIE11Table);
        break;
      }
      else
        continue;
    }
  }

  std::cout << "#Printing QIE11 condition constant table! ShuntMode : " << ShuntMode << std::endl;
  for(std::vector<QIE11Table>::iterator it = myQIE11Table.begin(); it != myQIE11Table.end(); ++it)
  {
    (*it).printQIE11TableInfo();
  }

  return 0;
}
