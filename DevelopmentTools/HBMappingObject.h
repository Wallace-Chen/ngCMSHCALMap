#ifndef _HBMapObject_H_
#define _HBMapObject_H_

#include<string>
//FrontEnd electronics struct
struct HBFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8_id;
};

//Backend electronics struct
struct HBBackEnd
{
  //patch panel information
  int ppcol,pprow,pplc,dodec;
  std::string ppcpl;

  //old htr info, going to be obsolete after 2018 HB re mapping, but keep it for legacy map dumper information
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;

  //uHTR
  int ucrate, uhtr, uhtr_fiber;
  std::string ufpga;
  int ufedid;
  
  int fiber_ch;
};

//HPD boxes struct
struct HBHPD
{
  int wedge;
  int pixel;
};

//Geometry struct
struct HBGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

//Trigger tower struct
struct HBTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

struct HBCalib
{
  //FE
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8_id;
  int wedge;

  //Calibration patch
  std::string trunk;
  int cpcol, cprow, cplc, cpoct;
  std::string cpcpl;

  //patch panel
  int ppcol, pprow, pplc, dodec;
  std::string ppcpl;

  //backend
  int ucrate, uhtr, uhtr_fiber;
  int ufedid;

  //Geo
  int side, eta, phi, depth; //eta is always 1, phi go with rm 1. Depth 0 to 2
  int dphi; //dphi is always 4
  std::string subdet;
};

class HBConstant
{
 public:
  // channels in HB
  static const int NchHB_all = 2592;
  //Front End variables
  //rbx in HB, 18 for each side
  static const int NrbxHB = 18;
  //4 rm in all HB rbx, label from 1 to 4
  static const int NrmHB = 4;
  //rm fiber 2,3,4,5,6,7, in total 6 fibers per rm
  static const int Nrm_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  static const int Nfiber_ch = 3;

  static const int Nqie = 3;
  static const int Nqie_ch = 6;

  //Back End variables
  //9 crate in HBHE: 0,1,4,5,10,11,14,15,17
  static const int Ncrate = 9;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18 - - - obsolete
  //12 uhtr in each crate, 1,2,3,4,5,6,7,8,9,10,11,12, 3 types of HBHE - - - pure HB,1,4,7,10, pure HE,3,6,9,12, HBHE mixing,2,5,8,11
  static const int Nhtr = 12; static const int Nuhtr = 12;
  //2 fpga flavors top and bottom in htr, while only uHTR in u
  static const int Nfpga = 2; static const int Nufpga = 1;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8, while 12 in uhtr: 2,3,4,5,6,7,8,9 and 14,15,16,17,18,19,20,21
  static const int Nhtr_fiber = 8; static const int Nuhtr_fiber = 16;

  //Geometry variables in HB: 
  static const int NHBside = 2;
  static const int NHBphi = 72;

  static const int NHBeta1516 = 2; static const int NHBeta1to14 = 14;
  static const int NHBdeptheta1516 = 2; static const int NHBdeptheta1to14 = 1;

  //2 fibers per rm in calibration module, rm 1,2
  static const int NrmHBCalib = 1;
  static const int Nrm_fiberCalib = 1;
};

#endif
