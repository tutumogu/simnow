#ifndef FTTC_H
#define FTTC_H

#include "ThostFtdcTraderApi.h"

class Fttc
{
public:
  Fttc(CThostFttcTraderApi* pApi, FtdSubscriber* pMdSubscriber);
  static Fttc* CreateFttc();
  void Run();
  ~Fttc();
private:
  CThostFttcMdApi* mpApi;
  FtdSubscriber* mpMdSubscriber;
};

#endif
