#include "Fttc.hpp"

Fttc::Fttc(CThostFttcMdApi* pApi, FtdSubscriber* pMdSubscriber)
  : mpApi(pApi), mpMdSubscriber(pMdSubscriber)
{
}

Fttc* Fttc::CreateFttc()
{
  CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
  
  // Guotai
  // FtdSubscriber* pSubscriber = new FtdSubscriber(pApi, "2071", "10000648", "888888");
  // Simnow
  FtdSubscriber* pSubscriber = new FtdSubscriber(pApi, "9999", "107262", "12#$qwER");  
  pApi->RegisterSpi(pSubscriber);
  // simnow
  char pFront[] = "tcp://180.168.146.187:10011";
  // Guotai
  // char pFront[] = "tcp://180.169.77.111:42213";  
  pApi->RegisterFront(pFront);

  Fttc* pFttc = new Fttc(pApi, pSubscriber);
  
  return pFttc;
}

void Fttc::Run()
{
  mpApi->Init();
  mpApi->Join();    
}

Fttc::~Fttc()
{
}

