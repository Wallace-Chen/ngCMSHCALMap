#include<string>
//FrontEnd electronics struct
struct ngHFFrontEnd
{
  std::string rbx;
  int qie10_fiber, fiber_ch;
  int qie10, qie10_ch;
};

//Backend electronics struct
struct ngHFBackEnd
{
  int ucrate, uhtr, uhtr_fiber;
  std::string ufpga;
  int ufedid;

  int fiber_ch;
};

//PMT boxes struct
struct ngHFPMTBox
{
  int wedge;
  int pixel;
};

//Geometry struct
struct ngHFGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

//Trigger tower struct
struct ngHFTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

class ngHFConstant
{
 public:
  // channels in ngHF
  static const int NchngHF_all = 3456;
  //Front End variables
  //rbx in ngHF, 8 for each side
  static const int NrbxngHF = 8;
  
  //9 QIE10s per ngHF front end rbx
  static const int Nqie10 = 9;
  //QIE10 fiber, always 4,5,6,7,8,9, but is it true ?
  //static const int Nqie10_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2,3(since software people like start from 0)
  static const int Nfiber_ch = 4;

  // 24 channels per QIE card, 1 to 24, but qie8 adc is 0 to 5, should we also start from 0 ?
  static const int Nqie10_ch = 24;

  //Back End variables
  //3 crate in ngHF: 22,29,32, same as old HF
  static const int Ncrate = 3;
  //12 uhtr in each crate, 1,2,3,4,5,6,7,8,9,10,11,12, same as old HF
  static const int Nuhtr = 12;
  //2 fpga flavors top and bottom in htr, while only uHTR in u
  static const int Nufpga = 1;
  //24 in uhtr: 0,1,2,3,4,5,6,7,8,9..22,23
  static const int Nuhtr_fiber = 24;

  //Need to be tuned
  //Geometry variables in ngHF: eta from 29,to 40,41, phi is 1,3,...71 for most eta while dphi == 4 for eta 40,41;
  static const int NngHFside = 2;
  static const int NngHFetadphi2 = 11;
  static const int NngHFetadphi4 = 2;
  static const int NngHFphidphi2 = 36;
  static const int NngHFphidphi4 = 18;
  static const int NngHFdepth = 4;
};
