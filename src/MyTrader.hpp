#ifndef MY_TRADER_HPP
#define MY_TRADER_HPP

#include "ThostFtdcTraderApi.h"

class MyTrader : public CThostFtdcTraderSpi
{
public:
  MyTrader(CThostFtdcTraderApi* pApi);
  
  virtual void OnFrontConnected();

  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);  
private:
  CThostFtdcTraderApi* mpApi;
};

#endif
