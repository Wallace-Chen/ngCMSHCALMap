#include <vector>
#include <iostream>
#include <map>
#include <utility>

#include "ngHBMappingObject.h"

class ngHBMappingAlgorithm : public ngHBConstant
{
 public:
  //the variables we need to fill into the LMap
  std::vector<ngHBFrontEnd> myngHBFrontEnd; std::vector<ngHBBackEnd> myngHBBackEnd; std::vector<ngHBSiPM> myngHBSiPM; std::vector<ngHBGeometry> myngHBGeometry; std::vector<ngHBTriggerTower> myngHBTriggerTower;
  void ConstructngHBLMapObject();
 private:
  void ConstructngHBFrontEnd(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHBBackEnd(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHBGeometry(int sideid, int rbxrmid, int rmfifichid);      
  void ConstructngHBSiPM(int sideid, int rbxrmid, int rmfifichid);
  void ConstructngHBTriggerTower();  

  //we have rm fiber and fiber channel map to give us the ability to design a tp fw within latency
  /*
  Original input from Dick:
          natural  RM2,4   RM1,3
  card Tx rm_fib   rm_fib  rm_fib
  
   1   1    1        1      2
   1   2    2        2      1
   2   1    3        7      4
   2   2    4        4      7
   3   1    5        5      6
   3   2    6        6      5
   4   1    7        3      8
   4   2    8        8      3
  Translate into final based coordinates:
  */
  const std::map<int, int> ngHBrmfifinalTonature_rm13 = { {1,2}, {2,1}, {3,8}, {4,3}, {5,6}, {6,5}, {7,4}, {8,7} };
  const std::map<int, int> ngHBrmfifinalTonature_rm24 = { {1,1}, {2,2}, {3,7}, {4,4}, {5,5}, {6,6}, {7,3}, {8,8} };
  /*
  Original input from Dick, fiber channel map:
  QIEold Link QIEnew Fib_chnew
  1      0    1      0
  2      0    3      2
  3      0    2      1
  4      0    4      3
  5      0    5      4
  6      0    7      6
  7      0    6      5
  8      0    8      7
  9      1    9      0
  10     1    11     2
  11     1    10     1
  12     1    12     3
  13     1    13     4
  14     1    15     6
  15     1    14     5
  16     1    16     7
  Translate into final based coordinates:
  QIEold Link QIEnew Fib_chnew Fib_old
  1      0    1      0         0
  3      0    2      1         2
  2      0    3      2         1
  4      0    4      3         3
  5      0    5      4         4
  7      0    6      5         6
  6      0    7      6         5
  8      0    8      7         7
  9      1    9      0         0
  11     1    10     1         2
  10     1    11     2         1
  12     1    12     3         3
  13     1    13     4         4
  15     1    14     5         6
  14     1    15     6         5
  16     1    16     7         7
  */
  const std::map<int, int> ngHBfichfinalTonature = { {0,0}, {1,2}, {2,1}, {3,3}, {4,4}, {5,6}, {6,5}, {7,7} };
  std::pair<int,int> ngHBGetQIEcardch(int rm, int rm_fiber_final, int fiber_ch_final);

  const int ngHBucrateInrbxrmid[Ncrate] = {30,24,20,21,25,31,35,37,34};
  
  //http://cmsdoc.cern.ch/cms/HCAL/document/Calorimeters/HE/ngHB/ODU/ngHB_RM_fib_symmetries.txt
  //http://cmsdoc.cern.ch/cms/HCAL/document/Mapping/HBHE/ngHBHE/Arjan-verified_26-aug-2016/HBHEP07_template.xls
  const int ngHBphiInrbxrmid_P[NrbxngHB*NrmngHB] = {71,72,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
  const int ngHBphiInrbxrmid_M[NrbxngHB*NrmngHB] = {2,1,72,71,6,5,4,3,10,9,8,7,14,13,12,11,18,17,16,15,22,21,20,19,26,25,24,23,30,29,28,27,34,33,32,31,38,37,36,35,42,41,40,39,46,45,44,43,50,49,48,47,54,53,52,51,58,57,56,55,62,61,60,59,66,65,64,63,70,69,68,67};

  const int ngHBetaInqiecardchid_RM13[Nqie11*Nqie11_ch]=
  {
    16,16,15,15,14,14,13,13, 2, 2, 1, 1, 4, 4, 3, 3,//qie 1
    12,12,11,11,10,10, 9, 9, 6, 6, 5, 5, 8, 8, 7, 7,//qie 2
     8, 8, 7, 7, 6, 6, 5, 5,10,10, 9, 9,12,12,11,11,//qie 3
     4, 4, 3, 3, 2, 2, 1, 1,14,14,13,13,16,16,15,15 //qie 4
  };

  const int ngHBetaInqiecardchid_RM24[Nqie11*Nqie11_ch]=
  {
    2, 2, 1, 1, 4, 4, 3, 3,16,16,15,15,14,14,13,13,//qie 1
    6, 6, 5, 5, 8, 8, 7, 7,12,12,11,11,10,10, 9, 9,//qie 2
    10,10, 9, 9,12,12,11,11,8, 8, 7, 7, 6, 6, 5, 5,//qie 3
    14,14,13,13,16,16,15,15,4, 4, 3, 3, 2, 2, 1, 1 //qie 4
  };
  const int ngHBdepInqiechid[Nqie11_ch]={1,4,1,4,1,4,1,4,3,2,3,2,3,2,3,2};
};
