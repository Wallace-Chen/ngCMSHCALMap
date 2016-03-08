#include<string>
//FrontEnd electronics struct
struct HBFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
};

struct HEFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
};

//Backend electronics struct
struct HBBackEnd
{
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;

  int dcc, spigot, dcc_sl;

  int ucrate, uhtr, uhtr_fiber;
  std::string ufpga;
  int ufedid;
  
  int fiber_ch;
};

struct HEBackEnd
{
  int crate, htr, htr_fiber;
  std::string fpga;
  int fedid;

  int dcc, spigot, dcc_sl;

  int ucrate, uhtr, uhtr_fiber;
  std::string ufpga;
  int ufedid;
  
  int fiber_ch;
};

//PMT boxes struct
struct HBPMTBox
{
  int wedge;
  int pixel;
};
struct HEPMTBox
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

struct HEGeometry
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

struct HETriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

class HBHEConstant
{
 public:
  // channels in HB
  static const int NchHBHE_all = 2592+2592;
  //Front End variables
  //rbx in HB, 18 for each side
  static const int NrbxHB = 18; static const int NrbxHE = 18;
  //4 rm in all HB rbx, label from 1 to 4
  static const int NrmHB = 4; static const int NrmHE = 4;
  //rm fiber 2,3,4,5,6,7, in total 6 fibers per rm
  static const int Nrm_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  static const int Nfiber_ch = 3;

  static const int Nqie = 3;
  static const int Nqie_ch = 6;

  //Back End variables
  //9 crate in HBHE: 0,1,4,5,10,11,14,15,17
  static const int Ncrate = 9;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18; 12 uhtr in each crate, 1,2,3,4,5,6,7,8,9,10,11,12
  static const int Nhtr = 12; static const int Nuhtr = 12;
  //2 fpga flavors top and bottom in htr, while only uHTR in u
  static const int Nfpga = 2; static const int Nufpga = 1;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8, while 12 in uhtr: 2,3,4,5,6,7,8,9 and 14,15,16,17,18,19,20,21
  static const int Nhtr_fiber = 8; static const int Nuhtr_fiber = 16;

  //Geometry variables in HB: 
  static const int NHBHEside = 2;
  static const int NHBHEphi = 72;

  static const int NHBeta1516 = 2; static const int NHBeta1to14 = 14;
  static const int NHBdeptheta1516 = 2; static const int NHBdeptheta1to14 = 1;
};
