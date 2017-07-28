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
       
    //#Side Eta Phi dPhi Depth Det 
    //ngRBX Wedge PMTBx PMT_TYPE W_Cable Tower PMT BaseBoard Anode S_PMT S_QIE R_PMT R_QIE 
    //QIE10 QIETB QIECH QIEFI FI_CH Trunk_FI nCable MTP 
    //Crate uHTR uHTR_Rx uHTR_FI FEDid
    //QIE10id QIE10BarCode
 
    //1 34 1 2 2 HF 
    //HFP01 1 1 A 1 H6 5 B 1 11 2 12 1     
    //3 TOP 1 4 0 1 14193 4    
    //32 12 1 12 1122
    //500751 0x6b000000 0xba086a70

    ss >> thisQIE10LMap.side >> thisQIE10LMap.eta >> thisQIE10LMap.phi >> tmp >> thisQIE10LMap.depth >> thisQIE10LMap.subdet
       >> thisQIE10LMap.rbx >> tmp >> tmp >> tmp_str >> tmp >> tmp_str >> tmp >> tmp_str >> tmp >> tmp >> tmp >> tmp >> tmp
       >> thisQIE10LMap.qie_card >> tmp_str >> thisQIE10LMap.qie_ch >> tmp >> tmp >> tmp >> tmp >> tmp
       >> tmp >> tmp >> tmp >> tmp >> tmp 
       >> thisQIE10LMap.qie_id >> tmp_str >> tmp_str;
    
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
    //# QIE10ID QIE10 
    //Offsets(CapID*4+Range) Slopes(CapID*4+Range)
    ss >> thisQIE10Condition.QIE10_id >> thisQIE10Condition.QIE10_ch
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
    //(*it).printQIE10ConditionInfo();
  }
  std::cout << "#Calculating QIE10 Conditions average!" << std::endl;
  double ave_offsets[24][16]={{0}}, ave_slopes[24][16]={{0}};
  int NQIE10Cards=0;
  for(std::vector<QIE10Condition>::iterator it = myQIE10Condition.begin(); it != myQIE10Condition.end(); ++it) 
  {
    int qie10ch = (*it).QIE10_ch;
    if(qie10ch==1) NQIE10Cards++;
    for(int i=0;i<16;i++)
    { 
      ave_offsets[qie10ch-1][i] += (*it).offsets[i];
      ave_slopes[qie10ch-1][i] += (*it).slopes[i];
    }
  }
  std::cout << "#NQIE10Cards:" << NQIE10Cards << "; Printing QIE10 Conditions average!" << std::endl;
  for(int i=0;i<24;i++)
  {
    for(int j=0;j<16;j++)
    {
      ave_offsets[i][j]=ave_offsets[i][j]/NQIE10Cards;
      ave_slopes[i][j]=ave_slopes[i][j]/NQIE10Cards;
    }
    /*
    std::cout << "#QIE10Chs: " << i+1;
    for(int j=0;j<16;j++)
    {
      std::cout << " " << ave_offsets[i][j];
    }
    for(int j=0;j<16;j++)
    {
      std::cout << " " << ave_slopes[i][j];
      if(j==15) std::cout << std::endl;
    }
    */
  }

  std::cout << "#Printing QIE10 LMap information!" << std::endl;
  for(std::vector<QIE10LMap>::iterator it = myQIE10LMap.begin(); it != myQIE10LMap.end(); ++it)
  { 
    //(*it).printQIE10LMapInfo();
  }

  std::vector<QIE10Table> myQIE10Table;
  std::cout << "#Linking QIE10 condition constant table..." << std::endl;
  int Nch_matched=0, Nch_unmatched=0;
  for(std::vector<QIE10LMap>::iterator it1 = myQIE10LMap.begin(); it1 != myQIE10LMap.end(); ++it1)
  {
    bool matched = false;
    for(std::vector<QIE10Condition>::iterator it2 = myQIE10Condition.begin(); it2 != myQIE10Condition.end(); ++it2)
    {
      matched = ((*it1).qie_id == (*it2).QIE10_id) && ((*it1).qie_ch == (*it2).QIE10_ch);
      if( matched )
      { 
        //std::cout << "Matched!" << std::endl;
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
        Nch_matched++;
        myQIE10Table.push_back(thisQIE10Table);
        break;
      }
    }
    //If not found in QIE condition
    if( !matched )
    {
      //(*it1).printQIE10LMapInfo();
      //std::cout << "#LMap do not find match in QIE10 table!" << std::endl;
      QIE10Table thisQIE10Table;
      thisQIE10Table.eta = (*it1).eta * (*it1).side;
      thisQIE10Table.phi = (*it1).phi;
      thisQIE10Table.depth = (*it1).depth;
      thisQIE10Table.subdet = (*it1).subdet;
      for(int i=0;i<16;i++)
      {
        int aveqie10ch=(*it1).qie_ch;
        //thisQIE10Table.offsets[i] = -10000;
        //thisQIE10Table.slopes[i] = -1;
        thisQIE10Table.offsets[i] = ave_offsets[aveqie10ch-1][i];
        thisQIE10Table.slopes[i] = ave_slopes[aveqie10ch-1][i];
      }
      Nch_unmatched++;
      myQIE10Table.push_back(thisQIE10Table);
    }
  }

  std::cout << "#Matched ngHF chs: " << Nch_matched << "; UnMatched ngHF chs:" << Nch_unmatched << "; Total ngHF chs: " << Nch_matched+Nch_unmatched << std::endl;
  std::cout << "#Printing QIE10 condition constant table!" << std::endl;
  for(std::vector<QIE10Table>::iterator it = myQIE10Table.begin(); it != myQIE10Table.end(); ++it)
  {
    (*it).printQIE10TableInfo();
  }

  return 0;
}
