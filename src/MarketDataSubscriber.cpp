#include "MarketDataSubscriber.hpp"

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

using namespace std;

MarketDataSubscriber::MarketDataSubscriber(CThostFtdcMdApi* pApi, const char* pBrokerId, const char* pUserId, const char* pPassword)
  : mpApi(pApi), mRequestId(0)
{
  memset(&mReq, 0, sizeof(mReq));

  strcpy(mReq.BrokerID, pBrokerId);
  strcpy(mReq.UserID, pUserId);
  strcpy(mReq.Password, pPassword);
}

void MarketDataSubscriber::OnFrontConnected()
{
  cerr << "-->" << __FUNCTION__ << endl;    
  
  int ret = -1;
  ret = mpApi->ReqUserLogin(&mReq, mRequestId);
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

  ifstream in("./etc/instruments");
  string instrument;
  char* ppInstrumentId[1024];
  int iInstrumentId = 0;
  while (getline(in, instrument))
    {
      cout << instrument << " " << instrument.size() << endl;
      ppInstrumentId[iInstrumentId] = (char*)malloc(instrument.size()+1);
      memset(ppInstrumentId[iInstrumentId], 0, instrument.size()+1);
      strcpy(ppInstrumentId[iInstrumentId], instrument.c_str());
      iInstrumentId++;
    }

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
  string instrument(pDepthMarketData->InstrumentID);
  string file_name = "./data/"+instrument;
  ofstream out(file_name.c_str(), std::ofstream::out | std::ofstream::app);
  std::time_t result = std::time(NULL);
  
  out << std::asctime(std::localtime(&result)) << pDepthMarketData->LastPrice << endl;
  cerr << pDepthMarketData->LastPrice << endl;
  cerr << pDepthMarketData->AskPrice1 << endl;
  cerr << pDepthMarketData->BidPrice1 << endl;
  out.close();
}
