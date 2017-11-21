#include <string.h>

#include <iostream>

#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiStruct.h"

#include "MarketDataSubscriber.hpp"
#include "MyTrader.hpp"

using namespace std;

int main()
{
  CThostFtdcMdApi* pApi = CThostFtdcMdApi::CreateFtdcMdApi("./con/");
  MarketDataSubscriber* pSubscriber = new MarketDataSubscriber(pApi);
  pApi->RegisterSpi(pSubscriber);

  cerr << "simnow" << endl;
  char pFront[] = "tcp://180.168.146.187:10001";
  pApi->RegisterFront(pFront);
  pApi->Init();
  pApi->Join();

  /*
  CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
  MyTrader trader(pApi);
  pApi->RegisterSpi((CThostFtdcTraderSpi*)&trader);
  pApi->SubscribePublicTopic(THOST_TERT_RESTART);					// 注册公有流
  pApi->SubscribePrivateTopic(THOST_TERT_RESTART);
  char pFront[] = "tcp://180.169.77.111:42205";
  pApi->RegisterFront(pFront);
  pApi->Init();
  pApi->Join();
  pApi->Release();
  */
  return 0;
}
