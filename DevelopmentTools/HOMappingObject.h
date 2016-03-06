//FrontEnd electronics struct
struct HOFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8id;
};

//Backend electronics struct
struct HOBackEnd
{
  double block_coupler;
  int crate, htr, htr_fiber, fiber_ch;
  std::string fpga;
  int fedid;
  int dcc, spigot, dcc_sl;
  //int ucrate, uhtr, uhtr_fiber, fiber_ch;
};

//PMT boxes struct
struct HOPMTBox
{
  int sector;
  int pixel;
  std::string letter_code;
};

//Geometry struct
struct HOGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

//Trigger tower struct
struct HOTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};
