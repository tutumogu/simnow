#ifndef FTDC_HPP
#define FTDC_HPP

#include "FtdSubscriber.hpp"

#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiStruct.h"

class Ftdc
{
public:
  Ftdc(CThostFtdcMdApi* pApi, FtdSubscriber* pMdSubscriber);
  static Ftdc* CreateFtdc();
  void Run();
  ~Ftdc();
private:
  CThostFtdcMdApi* mpApi;
  FtdSubscriber* mpMdSubscriber;
};

#endif
