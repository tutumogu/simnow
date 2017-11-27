#ifndef MARKET_DATA_SUBSCRIBER_HPP
#define MARKET_DATA_SUBSCRIBER_HPP

#include "ThostFtdcMdApi.h"
#include <map>
#include <string>
#include <fstream>

using namespace std;

class MarketDataSubscriber : public CThostFtdcMdSpi
{
public:
  MarketDataSubscriber(CThostFtdcMdApi* pApi, const char* pBrokerId, const char* pUserId, const char* pPassword);
  virtual void OnFrontConnected();
  virtual void OnFrontDisconnected(int nReason);
  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
private:
  CThostFtdcMdApi* mpApi;
  CThostFtdcReqUserLoginField mReq;
  map<string, ofstream> mInstruments;
  int mRequestId;
};

#endif
