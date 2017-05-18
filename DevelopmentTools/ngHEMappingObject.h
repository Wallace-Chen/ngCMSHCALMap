#ifndef _ngHEMapObject_H_
#define _ngHEMapObject_H_

#include<string>
//FrontEnd electronics struct
struct ngHEFrontEnd
{
  //interface to BackEnd: 2 side, 18 rbx per side, 4 rm per rbx and 8 rm fibers per rm
  std::string rbx;
  int rm, rm_fiber;
  int qie11_fiber, fiber_ch;
  int qie11, qie11_ch;
  //variables in ROB/Connector
};

//Backend electronics struct
struct ngHEBackEnd
{
  int ucrate, uhtr, uhtr_fiber;
  std::string ufpga;
  int ufedid;

  int fiber_ch;
};

//PMT boxes struct
struct ngHESiPM
{
  int wedge;//1,2,3,4...18
  int pixel;
};

//Geometry struct
struct ngHEGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

//Trigger tower struct
struct ngHETriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

class ngHEConstant
{
 public:
  // channels in ngHE
  static const int NchngHE_all = 6912;
  //Front End variables
  //rbx in ngHE, 18 for each side
  static const int NrbxngHE = 18;
  //1,2,3,4 rm per ngHE RBX
  static const int NrmngHE = 4;
  //rm fiber 1,2,3,4,5,6,7,8, in total 8 fibers per rm
  static const int Nrm_fiber = 8;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2,3(since software people like start from 0)
  static const int Nfiber_ch = 6;
  //9 QIE10s per ngHE front end rbx
  static const int Nqie11 = 4;
  //QIE10 fiber, always 4,5,6,7,8,9, but is it true ?
  //static const int Nqie11_fiber = 6;
  // 12 channels per QIE card, 1 to 12, but qie8 adc is 0 to 5, should we also start from 0 ?
  static const int Nqie11_ch = 12;

  //9 crate shared by HB and HE: 20,21,24,25,30,31,34,35,37
  static const int Ncrate = 9;
  //12 uhtr in each crate, 1,2,3,4,5,6,7,8,9,10,11,12, same as old HF
  static const int Nuhtr = 12, Nuhtr_HB_pure = 4, Nuhtr_HBngHE_mixed = 4, Nuhtr_ngHE_pure = 4;
  //2 fpga flavors top and bottom in htr, while only uHTR in u
  static const int Nufpga = 1;
  //24 in uhtr: 0,1,2,3,4,5,6,7,8,9..22,23; pure HB, 0,1,2,3 and 12 to 23; HB in HBngHE mixed, 2,3,4,5,6,7,8,9; ngHE in HEngHE mixed, 12 to 23;  ngHE in ngHE pure, 1 to 10 and 13 to 22
  static const int Nuhtr_fiber = 24, Nuhtr_fiber_HB_pure = 16, Nuhtr_fiber_HB_HBngHE_mixed = 8, Nuhtr_fiber_ngHE_HBngHE_mixed = 12, Nuhtr_fiber_ngHE_pure = 20;
  //Number of backend ngHE channels = 9 * (4*12+4*20) * 6 = 6912  
  //Number of backend HB channels = 9 * (4*16+4*8) * 3 = 2592  

  //Need to be tuned
  //Geometry variables in ngHE: eta from 16 to 29, only depth 4 for eta 16 and only depth 2 and 3 for eta 17, checks below for the rest of depth eta assignment; phi 1 to 72 for eta 16 to 20 while phi 1,3,..71 for eta 21 to 29
  static const int NngHEside = 2;
  static const int NngHEphieta16to20 = 72;
  static const int NngHEphieta21to29 = 36;
  //number of depths for all _ngHE eta: 16,17,18,19,20,21,22,23,24,25,26,27,28,29
  static const int NngHEdeptheta16to20 = 1+2+5+6+6;//20
  static const int NngHEdeptheta21to29 = 6+6+6+6+6+7+7+7+3;//54
  static const int NngHECalibChannel = 144;
};
#endif
