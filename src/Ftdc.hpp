#ifndef FTDC_HPP
#define FTDC_HPP

#include "MarketDataSubscriber.hpp"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiStruct.h"

class Ftdc
{
public:
  Ftdc(CThostFtdcMdApi* pApi, MarketDataSubscriber* pMdSubscriber);
  static Ftdc* CreateFtdc();
  void Run();
  ~Ftdc();
private:
  CThostFtdcMdApi* mpApi;
  MarketDataSubscriber* mpMdSubscriber;
};

#endif
