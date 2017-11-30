#ifndef FTD_SUBSCRIBER_HPP
#define FTD_SUBSCRIBER_HPP

#include "ThostFtdcMdApi.h"

#include <map>
#include <string>
#include <fstream>

using namespace std;

class FtdSubscriber : public CThostFtdcMdSpi
{
public:
  FtdSubscriber(CThostFtdcMdApi* pApi, const char* pBrokerId, const char* pUserId, const char* pPassword);
  
  virtual void OnFrontConnected();

  virtual void OnFrontDisconnected(int nReason);

  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthFtd);

  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
						int nRequestID, bool bIsLast);

  bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
    
private:
  CThostFtdcMdApi* mpApi;
  CThostFtdcReqUserLoginField mReq;
  int mRequestId;
};

#endif
