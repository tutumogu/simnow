#include "Ftdc.hpp"

Ftdc::Ftdc(CThostFtdcMdApi* pApi, MarketDataSubscriber* pMdSubscriber)
  : mpApi(pApi), mpMdSubscriber(pMdSubscriber)
{
}

Ftdc* Ftdc::CreateFtdc()
{
  CThostFtdcMdApi* pApi = CThostFtdcMdApi::CreateFtdcMdApi("./con/");
  // Guotai
  // MarketDataSubscriber* pSubscriber = new MarketDataSubscriber(pApi, "2071", "10000648", "888888");
  // Simnow
  MarketDataSubscriber* pSubscriber = new MarketDataSubscriber(pApi, "9999", "107262", "12#$qwER");  
  pApi->RegisterSpi(pSubscriber);
  // simnow
  // char pFront[] = "tcp://180.168.146.187:10011";
  // Guotai
  char pFront[] = "tcp://180.169.77.111:42213";  
  pApi->RegisterFront(pFront);

  Ftdc* pFtdc = new Ftdc(pApi, pSubscriber);
  
  return pFtdc;
}

void Ftdc::Run()
{
  mpApi->Init();
  mpApi->Join();    
}

Ftdc::~Ftdc()
{
}
