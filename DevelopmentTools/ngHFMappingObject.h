#include<string>
//FrontEnd electronics struct
struct ngHFFrontEnd
{
  //interface to BackEnd: 2 side, 72 qie10s per side, 24 qie10 channels per qie10 = 3456
  std::string rbx;
  int qie10_fiber, fiber_ch;
  int qie10, qie10_ch;
  //variables in ROB/Connector
  
  //interface to PMT: 2 side, 72 qie10s per side, 2 qie10 connectors per qie10, and 12 channels per connector
  std::string qie10_connector;//TOP or BOT
  int s_coax_qie, r_coax_qie;//24 in total, 12 each
  //2 side * 72 QIE10s per side * 2 connectors per QIE10 * 24/2(pin to channels) = 3456
};

//Backend electronics struct
struct ngHFBackEnd
{
  //QIE10 -> Y fiber -> MTPs -> uHTR
  //QIEid -> trunk(nCable), MTP; (2 side, 0 to 71)->(14XXX, (1 to 4)); 144 -> (2+8*4+2)*2 = 72
  int trunk_ncable; //HFP for 14191 to 14200, 14191 and 14200 only have MTP 1 and 2, while other have all 4 MTPs; HFM in 14201 to 14210, 14201 and 14210 only have MTP 1 and 2, while other have all 4 MTPs
  int trunk_fiber; //1 to 12
  int yfiber_input; //1 or 2, HFP in 121212 pattern, while HFM in 212121 patter
  int mtp; //1,2,3,4 per trunk cable

  //trunk(nCable), MTP -> crate, slot, Rx; (14XXX, (1 to 4) ) -> ((22,29,32), (1 to 12), (0 or 1)); (2+8*4+2)*2 = 72 -> 3*12*2 = 72
  //Y fiber, QIE fiber -> uhtr fiber
  int ucrate, uhtr, uhtr_rx;
  int uhtr_fiber;
  int fiber_ch;

  std::string ufpga;
  int ufedid;
};

//PMT boxes struct
struct ngHFPMTBox
{
  //connection from Front End, 2 sides * 36 PMT boxes * 4 winchester cable per PMT box * 24 PNIs/2(signal and ref) = 3456 
  //pmt type is important attribue but not the base variables
  int pmtbox;//1 to...36 per side
  std::string pmt_type;//Type A or Type B
  int winchester_cable;//1,2,3,4
  int s_coax_pmt, r_coax_pmt;//24 in total, 12 each

  //interface to the Geometry, 2 side * 36 PMT boxes * 3 types of base board * 8 PMT socket per board * 2 anode per socket (1 or 3) = 3456
  //PMT box -> phi / anode+tower -> eta depth
  std::string tower; //H1 to H24, E1 to E24, different in type A/B PMT boxes, 24 towers per PMT box
  int anode;//1 or 3,1E -> depth 1, 3E -> depth 3, 1H -> depth 2, 3H -> depth 4

  //internal wiring in the PMT
  std::string baseboard_type; //type of base board, A,B and C, per PMT box
  int pmtsocket;//1 to 8, pmt socket in the base board

  int wedge;//1,2,3,4...18, HFP, PMT 1 and 36 -> wedge 1
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
  static const int Nqie10_fiber = 6;
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
  //Geometry variables in ngHF: eta from 29,to 40,41, phi is 1,3,...71 for most eta while dphi == 4 for eta 40,41;4 depth in total, depth 1 and 3 take electromagnetic shower while depth 2 and 4 take hadronic shower
  static const int NngHFside = 2;
  static const int NngHFetadphi2 = 11;
  static const int NngHFetadphi4 = 2;
  static const int NngHFphidphi2 = 36;
  static const int NngHFphidphi4 = 18;
  static const int NngHFdepth = 4;
};
