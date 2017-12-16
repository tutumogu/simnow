#include "FtdTrader.hpp"

#include "ThostFtdcTraderApi.h"

int main()
{
  CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
  FtdTrader* pSpi = new FtdTrader(pApi);
  pApi->RegisterSpi((CThostFtdcTraderSpi*)pSpi);
  pApi->SubscribePublicTopic(THOST_TERT_QUICK);
  pApi->SubscribePrivateTopic(THOST_TERT_QUICK);
  pApi->RegisterFront("tcp://180.168.146.187:10001");
  pApi->Init();
  pApi->Join();
  return 0;
}
