#include <string>
#include <iostream>
#include <iomanip>

class QIE10LMap
{
 public:
  //#side eta phi dphi depth det rbx wedge Box_type W_cable tower row col PMT base-board anode S-coax-PMT S-coax-QIE R-coax-PMT R-coax-QIE QIE rm qie qie-conn qie_ch qie_fib fib_ch trunk_fib trunk crate uHTR uHTR-MTP uHTR_fib fedid QIEid LED
  int side, eta, phi, depth;
  std::string subdet;
  std::string rbx;
  int qie_card, qie_ch;

  void printQIE10LMapInfo();
};

void QIE10LMap::printQIE10LMapInfo()
{
  std::cout << std::setw(10) << "Side : " << side << std::setw(10) << " Eta : " << eta << std::setw(10) << " Phi : " << phi << std::setw(10) << " Depth : " << depth << std::setw(10) << " Det : " << subdet
            << std::setw(10) << " RBX : " << rbx << std::setw(10) << " FECard : " << qie_card << std::setw(10) << " QIE10Ch : " << qie_ch
            << std::endl;
}

class QIE10Condition
{
 public:
  int crate, slot;
  int QIE10_id;
  int QIE10_ch;
  double offsets[16], slopes[16];

  void printQIE10ConditionInfo();
};

void QIE10Condition::printQIE10ConditionInfo()
{
  std::cout << std::setw(10) << "FECrate : " << crate << std::setw(10) << " FESlot : " << slot << std::setw(10) << " QIE10Id : " << QIE10_id << std::setw(10) << " QIE10Ch : " << QIE10_ch
            << std::endl;
}

class QIE10Table
{
 public:
  int eta, phi, depth;
  std::string subdet;
  double offsets[16], slopes[16];

  void printQIE10TableInfo();
};

void QIE10Table::printQIE10TableInfo()
{
  std::cout << std::setw(6) << " " << eta << std::setw(6) << " " << phi << std::setw(6) << " " << depth << std::setw(6) << " " << subdet;
  for(int i=0;i<16;i++){ std::cout << std::setw(6) << " " << offsets[i]; }
  for(int i=0;i<16;i++){ std::cout << std::setw(6) << " " << slopes[i]; }   
  std::cout << std::endl;
}


