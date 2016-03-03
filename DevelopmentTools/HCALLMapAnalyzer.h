#include<string>

class HBFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch;
  int qie10, qie10_ch;
};

class HEFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch;
  int qie10, qie10_ch;
};

class HFFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch;
  int qie10, qie10_ch;
};

class HOFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch;
};

class HBBackEnd
{
  int crate, htr, htr_fiber;
  int dcc, spigot;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
};

class HEBackEnd
{
  int crate, htr, htr_fiber;
  int dcc, spigot;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
};

class HFBackEnd
{
  int crate, htr, htr_fiber;
  int dcc, spigot;
  int ucrate, uhtr, uhtr_fiber, fiber_ch;
};

class HOBackEnd
{
  int crate, htr, htr_fiber, fiber_ch;
  int dcc, spigot;
  //int ucrate, uhtr, uhtr_fiber, fiber_ch;
};

class HBPMTBox
{};
class HEPMTBox
{};
class HFPMTBox
{};
class HOPMTBox
{};

class HBTile
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

class HETile
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

class HFTile
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

class HOTile
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};


