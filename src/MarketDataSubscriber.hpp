#ifndef MARKET_DATA_SUBSCRIBER_HPP
#define MARKET_DATA_SUBSCRIBER_HPP

#include "ThostFtdcMdApi.h"

class MarketDataSubscriber : public CThostFtdcMdSpi
{
public:
  MarketDataSubscriber(CThostFtdcMdApi* pApi);
  virtual void OnFrontConnected();
  virtual void OnFrontDisconnected(int nReason);
  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
private:
  CThostFtdcMdApi* mpApi;
  int mRequestId;
};

#endif
