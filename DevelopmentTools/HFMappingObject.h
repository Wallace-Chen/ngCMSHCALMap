#include<string>
//FrontEnd electronics struct
struct HFFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  //int qie10, qie10_ch;
};

//Backend electronics struct
struct HFBackEnd
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
struct HFPMTBox
{
  int wedge;
  int pixel;
};

//Geometry struct
struct HFGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

//Trigger tower struct
struct HFTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

class HFConstant
{
 public:
  // channels in HF
  static const int NchHF_all = 1728;
  //Front End variables
  //rbx in HF, 12 for each side
  static const int NrbxHF = 12;
  //3 rm in all HF rbx, label from 1 to 3
  static const int NrmHF = 3;
  //rm fiber 1,2,3,4,5,6,7,8, in total 8 fibers per rm
  static const int Nrm_fiber = 8;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  static const int Nfiber_ch = 3;

  static const int Nqie = 4;
  static const int Nqie_ch = 6;

  //Back End variables
  //3 crate in HF: 2,9,12 while 22,29,32 for uCrate
  static const int Ncrate = 3;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18; 12 uhtr in each crate, 1,2,3,4,5,6,7,8,9,10,11,12
  static const int Nhtr = 12; static const int Nuhtr = 12;
  //2 fpga flavors top and bottom in htr, while only uHTR in u
  static const int Nfpga = 2; static const int Nufpga = 1;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8, while 16 in uhtr: 2,3,4,5,6,7,8,9 and 14,15,16,17,18,19,20,21
  static const int Nhtr_fiber = 8; static const int Nuhtr_fiber = 16;

  //Need to be tuned
  //Geometry variables in HF: eta from 29,to 40,41, phi is 1,3,...71 for most eta while dphi == 4 for eta 40,41;
  static const int NHFside = 2;
  static const int NHFetadphi2 = 11;
  static const int NHFetadphi4 = 2;
  static const int NHFphidphi2 = 36;
  static const int NHFphidphi4 = 18;
  static const int NHFdepth = 2;
};
