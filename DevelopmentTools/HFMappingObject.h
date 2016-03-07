//FrontEnd electronics struct
struct HFFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
  int qie10, qie10_ch;
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
