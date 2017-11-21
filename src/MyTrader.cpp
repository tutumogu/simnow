#include <string.h>
#include <iostream>

#include "ThostFtdcTraderApi.h"
#include "MyTrader.hpp"

using namespace std;

MyTrader::MyTrader(CThostFtdcTraderApi* pApi)
  : mpApi(pApi)
{
}

void MyTrader::OnFrontConnected()
{
  cout << "MyTrader::OnFrontConnected" << endl;
  CThostFtdcReqAuthenticateField field;
  memset(&field, 0, sizeof(field));
  strcpy(field.UserProductInfo, "N160414FTS");
  strcpy(field.BrokerID, "2071"); // 生产为7090
  strcpy(field.UserID, "10000648");
  strcpy(field.AuthCode, "20160414FTS00001");
  int ret = -1;
  cout << "11" << endl;
  ret = mpApi->ReqAuthenticate(&field, 0);
  cout << "ret:" << ret;  
}

void MyTrader::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cout << "OnRspUserLogin:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
  cout << "TradingDay:" << pRspUserLogin->TradingDay << endl;
  cout << "LoginTime:" << pRspUserLogin->LoginTime << endl;
  cout << "BrokerID:" << pRspUserLogin->BrokerID << endl;
  cout << "UserID:" << pRspUserLogin->UserID << endl;  
}

void MyTrader::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
