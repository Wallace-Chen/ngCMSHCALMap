#include <string>
#include <iostream>
#include <iomanip>

class QIE11LMap
{
 public:
  //#side eta phi dphi depth det rbx wedge Box_type W_cable tower row col PMT base-board anode S-coax-PMT S-coax-QIE R-coax-PMT R-coax-QIE QIE rm qie qie-conn qie_ch qie_fib fib_ch trunk_fib trunk crate uHTR uHTR-MTP uHTR_fib fedid QIEid LED
  int side, eta, phi, depth;
  std::string subdet;
  std::string rbx;
  int qie_ch;
  int qie_id;

  void printQIE11LMapInfo();
};

void QIE11LMap::printQIE11LMapInfo()
{
  std::cout << std::setw(10) << "Side : " << side << std::setw(10) << " Eta : " << eta << std::setw(10) << " Phi : " << phi << std::setw(10) << " Depth : " << depth << std::setw(10) << " Det : " << subdet
            << std::setw(10) << " RBX : " << rbx << std::setw(10) << " QIE11Ch : " << qie_ch << std::setw(10) << " QIE11ID : " << qie_id
            << std::endl;
}

class QIE11Condition
{
 public:
  int QIE11_id;
  int QIE11_ch;
  std::string QIE11_shunt;
  double offsets[16], slopes[16];

  void printQIE11ConditionInfo();
};

void QIE11Condition::printQIE11ConditionInfo()
{
  std::cout << std::setw(10) << " QIE11Id : " << QIE11_id << std::setw(10) << " QIE11Ch : " << QIE11_ch
            << std::endl;
}

class QIE11Table
{
 public:
  int eta, phi, depth;
  std::string subdet;
  double offsets[16], slopes[16];

  void printQIE11TableInfo();
};

void QIE11Table::printQIE11TableInfo()
{
  std::cout << std::setw(6) << " " << eta << std::setw(6) << " " << phi << std::setw(6) << " " << depth << std::setw(6) << " " << subdet;
  for(int i=0;i<16;i++){ std::cout << std::setw(6) << " " << offsets[i]; }
  for(int i=0;i<16;i++){ std::cout << std::setw(6) << " " << slopes[i]; }   
  std::cout << std::endl;
}


