#ifndef _ngHOMapObject_H_
#define _ngHOMapObject_H_

#include<string>
//FrontEnd electronics struct
struct ngHOFrontEnd
{
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8_id;
};

//Backend electronics struct
struct ngHOBackEnd
{
  std::string block_coupler;
  int crate, htr, htr_fiber;
  int fedid;
  int mtp;
  int dodeca = 0;
};

//PMT boxes struct
struct ngHOSiPM
{
  int sector;
  int pixel;
  std::string letter_code;
};

//Geometry struct
struct ngHOGeometry
{
  int side;
  int eta, phi, depth;
  int dphi;
  std::string subdet;
};

//Trigger tower struct
struct ngHOTriggerTower
{
  int trg_fiber, trg_fiber_ch;
};

struct ngHOCalib
{
  //FE
  std::string rbx;
  int rm, rm_fiber, fiber_ch;
  int qie8, qie8_ch, qie8_id;

  //BE
  int crate, htr, htr_fiber;
  int fedid;
  int mtp;
  int dodeca;
  std::string block_coupler;

  //Geo
  int side, eta, phi, depth;
  std::string subdet;//HO
  int dphi;

  //SIPM
  int pixel, sector;
  std::string letter_code;
};
// The below constants are not checked yet for ngHO, needs to be checked before using them!!!
// Currently ngHO mapping will be loaded from external files.
class ngHOConstant
{
 public:


  //2376 channels in HO and HOX
  static const int NchHO_all = 2376;
  //Front End variables
  //rbx in HO, different in 0 and 12
  static const int NrbxHO0 = 1*12;
  static const int NrbxHO12 = 4*6;
  //3 rm in HO0 while 4 rm in HO1P, HO1M, HO2P, HO2M
  //for HO0 part, 1,4,5,8,9,12, rm is 1,2,3; 2,3,6,7,10,11, rm is 2,3,4
  static const int NrmHO0 = 3;
  static const int NrmHO12 = 4;
  //rm fiber 2,3,4,5,6,7, in total 6 fibers per rm
  static const int Nrm_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  static const int Nfiber_ch = 3;

  static const int Nqie = 3;
  static const int Nqie_ch = 6;

  //Back End variables
  //4 crate in HO: 3,6,7,12
  static const int Ncrate = 4;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18
  static const int Nhtr = 12;
  //2 fpga flavors top and bottom
  static const int Nfpga = 2;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8
  static const int Nhtr_fiber = 8;
  //216 HOX channels in HO map in total, while 72 special HOX channels with no patch panel attachment, htr slot is 21
  static const int NspecialHOX = 72;


  static const int NppCol = 4;
  static const int NppLC = 4;

  //Geimetry variables,2160 channels, side -1 or +1, eta from 1 to 15, phi 1 to 72, depth always 4
  static const int NHOside = 2;
  static const int NHOeta = 15;
  static const int NHOphi = 72;
  static const int NHOdepth = 1;
  //144 normal HOX channels,only in side -1, eta 4 and eta 15, for all phis
  static const int NnormalHOX = 2*72;
  //72 special HOX channels, only in side +1, eta 15, for all phis

  //Calibration channels
  static const int NrmHOCalib = 1;
  static const int Nrm_fiberCalib = 1;
  //static const int Nfiber_chCalib[4] = {1,2,3,4};
  //Special Processing, they have 3 channels per fiber rather than 2
  const std::string rbxSPHOCalib[5] = {"HO010","HO1M10","HO1P10","HO2M12","HO2P10"};

};
#endif
