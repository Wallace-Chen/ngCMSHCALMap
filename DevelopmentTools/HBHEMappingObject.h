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
