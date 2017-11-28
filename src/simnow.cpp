#include "Ftdc.hpp"
#include "iconvpp.hpp"
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
   cerr << "Simnow starting..." << endl;
  
  Ftdc* pFtdc = Ftdc::CreateFtdc();
  pFtdc->Run();

  delete pFtdc;

  return 0;
}
