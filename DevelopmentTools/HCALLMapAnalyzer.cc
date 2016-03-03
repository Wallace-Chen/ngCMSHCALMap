#include <iostream>
#include <sstream>
#include <fstream>
#include "HCALLMapAnalyzer.h"

int main()
{
  std::ifstream inputFile("officialMap/HCALmapHBEF_G.txt");
  std::string line;

  while( std::getline(inputFile, line) )
  {
    std::istringstream ss(line);
    if(line.at(0) == '#') continue;
    std::cout << line << std::endl;
    //std::string name;
    //int var1, var2, var3;

    //ss >> name >> var1 >> var2 >> var3;
  }
  return 0;
}
