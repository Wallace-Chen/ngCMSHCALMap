#ifndef _ngHBMapObject_H_
#define _ngHBMapObject_H_

#include<string>
//FrontEnd electronics struct
struct ngHBFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie11, qie11_ch, qie11_id;
  int fiber_indx;
  int mb_no;
};

//Backend electronics struct
struct ngHBBackEnd
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

//SiPM boxes struct
struct ngHBSiPM
{
  int wedge;
  int bv;
};

//Geometry struct
struct ngHBGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

struct ngHBTriggerTowerFiber
{
  int trg_fiber, trg_fiber_ch;
};

//Trigger tower struct
struct ngHBTriggerTower
{
// The following dies in new era M        
//  int trg_fiber, trg_fiber_ch;
  int trg_ind, trg_indx;
  std::string trg_jm, trg_uhtr; 
};

struct ngHBCalib
{
  //FE
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie11, qie11_ch, qie11_id;
  int mb_no = -1;//Note: mb_no here is fake, a redundant variable, always et to -1.
  int wedge, bv = -1; //Note: bv here is fake, a redundant variable, always set to -1

  //Calibration patch
  int trunk;
  int cpcol, cprow, cplc, cpoct;
  std::string cpcpl;
  std::string ribbon;

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

class ngHBConstant
{
 public:
  // channels in ngHB
  static const int NchngHB_all = 2592;
  //Front End variables
  //rbx in ngHB, 18 for each side
  static const int NrbxngHB = 18;
  //4 rm in all ngHB rbx, label from 1 to 4
  static const int NrmngHB = 4;
  //rm fiber 1,2,3,4,5,6,7,8 in total 6 fibers per rm
  static const int Nrm_fiber = 8;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2,3,4,5,6,7(since software people like start from 0)
  static const int Nfiber_ch = 8;

  static const int Nqie = 3;
  static const int Nqie_ch = 6;

  //Back End variables
  //9 crate in ngHBHE: 0,1,4,5,10,11,14,15,17
  static const int Ncrate = 9;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18 - - - obsolete
  //12 uhtr in each crate, 1,2,3,4,5,6,7,8,9,10,11,12, 3 types of ngHBHE - - - pure ngHB,1,4,7,10, pure HE,3,6,9,12, ngHBHE mixing,2,5,8,11
  static const int Nhtr = 12; static const int Nuhtr = 12;
  //2 fpga flavors top and bottom in htr, while only uHTR in u
  static const int Nfpga = 2; static const int Nufpga = 1;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8, while 12 in uhtr: 2,3,4,5,6,7,8,9 and 14,15,16,17,18,19,20,21
  static const int Nhtr_fiber = 8; static const int Nuhtr_fiber = 16;

  //Geometry variables in ngHB: 
  static const int NngHBside = 2;
  static const int NngHBphi = 72;

  static const int NngHBeta1516 = 2; static const int NngHBeta1to14 = 14;
  static const int NngHBdeptheta1516 = 2; static const int NngHBdeptheta1to14 = 1;

  //2 fibers per rm in calibration module, rm 1,2
  static const int NrmngHBCalib = 1;
  static const int Nrm_fiberCalib = 2;
  static const int Nfiber_chCalib = 8;
};

#endif
