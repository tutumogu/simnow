#include <iostream>

#include <stdio.h>
#include <string.h>

#include "MarketDataSubscriber.hpp"

using namespace std;

MarketDataSubscriber::MarketDataSubscriber(CThostFtdcMdApi* pApi)
  : mpApi(pApi), mRequestId(0)
{
}

void MarketDataSubscriber::OnFrontConnected()
{
  cerr << "-->" << __FUNCTION__ << endl;    
  
  CThostFtdcReqUserLoginField req;
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, "9999");
  strcpy(req.UserID, "107262");
  strcpy(req.Password, "12#$qwER");

  int ret = -1;
  ret = mpApi->ReqUserLogin(&req, mRequestId);
  cout << "ReqUserLogin:" << ret << endl;
}

void MarketDataSubscriber::OnFrontDisconnected(int nReason)
{
  cerr << "-->" << __FUNCTION__ << endl;  
}

void MarketDataSubscriber::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "-->" << __FUNCTION__ << endl;
  cerr << "OnRspUserLogin:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
  cerr << "TradingDay:" << pRspUserLogin->TradingDay << endl;
  cerr << "LoginTime:" << pRspUserLogin->LoginTime << endl;
  cerr << "BrokerID:" << pRspUserLogin->BrokerID << endl;
  cerr << "UserID:" << pRspUserLogin->UserID << endl;

  char* ppInstrumentId[1] = {"IF1712"};
  int iInstrumentId = 1;
  
  int ret = mpApi->SubscribeMarketData(ppInstrumentId, iInstrumentId);
  cerr << "SubscribeMarketData:" << ret << endl;
}

void MarketDataSubscriber::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "-->" << __FUNCTION__ << endl;
  cerr << pSpecificInstrument->InstrumentID << endl;  
}

void MarketDataSubscriber::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
  cerr << "-->" << __FUNCTION__ << endl;
  cerr << pDepthMarketData->InstrumentID << endl;
  cerr << pDepthMarketData->LastPrice << endl;
  cerr << pDepthMarketData->AskPrice1 << endl;
  cerr << pDepthMarketData->BidPrice1 << endl;
}
