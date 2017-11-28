#ifndef MARKET_DATA_SUBSCRIBER_HPP
#define MARKET_DATA_SUBSCRIBER_HPP

#include "ThostFtdcMdApi.h"
#include "iconvpp.hpp"
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

  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
						int nRequestID, bool bIsLast);

  bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
    
private:
  CThostFtdcMdApi* mpApi;
  CThostFtdcReqUserLoginField mReq;
  iconvpp::converter mCvt;
  iconvpp::converter mCvt2;
  int mRequestId;
};

#endif
