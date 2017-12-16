#include "FtdTrader.hpp"

#include "./ThostFtdcTraderApi.h"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>

using namespace std;

extern TThostFtdcPriceType	LIMIT_PRICE;	// 价格
extern TThostFtdcDirectionType	DIRECTION;	// 买卖方向

// 请求编号
extern int iRequestID;

// 会话参数
TThostFtdcFrontIDType	FRONT_ID;	//前置编号
TThostFtdcSessionIDType	SESSION_ID;	//会话编号
TThostFtdcOrderRefType	ORDER_REF;	//报单引用
TThostFtdcOrderRefType	EXECORDER_REF;	//执行宣告引用
TThostFtdcOrderRefType	FORQUOTE_REF;	//询价引用
TThostFtdcOrderRefType	QUOTE_REF;	//报价引用

FtdTrader::FtdTrader(CThostFtdcTraderApi* pApi)
  : mpApi(pApi)
{
}

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void FtdTrader::OnFrontConnected()
{
  cerr << "--->>> " << "OnFrontConnected" << endl;
  CThostFtdcReqUserLoginField req;
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, "9999");
  strcpy(req.UserID, "107262");
  strcpy(req.Password, "12#$qwER");
  int iResult = mpApi->ReqUserLogin(&req, ++mRequestId);
}

///登录请求响应On
void FtdTrader::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "--->>> " << "OnRspUserLogin" << endl;
  cout << pRspInfo->ErrorMsg << endl;
  FRONT_ID = pRspUserLogin->FrontID;
  SESSION_ID = pRspUserLogin->SessionID;
  int iNextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
  iNextOrderRef++;
  sprintf(ORDER_REF, "%d", iNextOrderRef);
  sprintf(EXECORDER_REF, "%d", 1);
  sprintf(FORQUOTE_REF, "%d", 1);
  sprintf(QUOTE_REF, "%d", 1);
  
  CThostFtdcSettlementInfoConfirmField req;  
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, "9999");
  strcpy(req.InvestorID, "107262");
  int iResult = mpApi->ReqSettlementInfoConfirm(&req, ++mRequestId);
  cerr << "--->>> 投资者结算结果确认: " << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;

}

///投资者结算结果确认响应
void FtdTrader::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "--->>> " << "OnRspSettlementInfoConfirm" << endl;

  CThostFtdcQryInstrumentField req;
  memset(&req, 0, sizeof(req));
  
  strcpy(req.InstrumentID, mInstruemtId);
  int iResult = mpApi->ReqQryInstrument(&req, mRequestId);
  cerr << "--->>> 请求查询合约: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
  if (iResult == -2 || iResult == -3) sleep(1000);
}
	
///请求查询合约响应
void FtdTrader:: OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "--->>> " << "OnRspQryInstrument" << endl;
  
  CThostFtdcQryTradingAccountField req;
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, "9999");
  strcpy(req.InvestorID, "107262");
  int iResult = mpApi->ReqQryTradingAccount(&req, ++mRequestId);
  cerr << "--->>> 请求查询资金账户: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
  if (iResult == -2 || iResult == -3) sleep(1000);  
}

///请求查询资金账户响应
void FtdTrader:: OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  CThostFtdcQryInvestorPositionField req;
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, "9999");
  strcpy(req.InstrumentID, mInstruemtId);
  int iResult = mpApi->ReqQryInvestorPosition(&req, ++mRequestId);
  cerr << "--->>> 请求查询投资者持仓: "  << iResult << ((iResult == 0) ? ", 成功" : ", 失败") << endl;
  if (iResult == -2 || iResult == -3) sleep(1000);  
}

///请求查询投资者持仓响应
void FtdTrader::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "--->>> " << "OnRspQryInvestorPosition" << endl;
  ///报单录入请求
  //    ReqOrderInsert();
  //执行宣告录入请求
  //	ReqExecOrderInsert();
  //询价录入
  //	ReqForQuoteInsert();
  //做市商报价录入
  //	ReqQuoteInsert();
  
}

void FtdTrader::ReqOrderInsert()
{
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, "9999");
	///投资者代码
	strcpy(req.InvestorID, "107262");
	///合约代码
	strcpy(req.InstrumentID, mInstruemtId);
	///报单引用
	strcpy(req.OrderRef, ORDER_REF);
	///用户代码
//	TThostFtdcUserIDType	UserID;
	///报单价格条件: 限价
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///买卖方向: 
	req.Direction = DIRECTION;
	///组合开平标志: 开仓
	req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	///组合投机套保标志
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	///价格
	req.LimitPrice = LIMIT_PRICE;
	///数量: 1
	req.VolumeTotalOriginal = 1;
	///有效期类型: 当日有效
	req.TimeCondition = THOST_FTDC_TC_GFD;
	///GTD日期
}

///报单录入请求响应
void FtdTrader::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

///执行宣告录入请求响应
void FtdTrader::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

///询价录入请求响应
void FtdTrader::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

///报价录入请求响应
void FtdTrader::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

///报单操作请求响应
void FtdTrader::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

///执行宣告操作请求响应
void FtdTrader::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
	
///报价操作请求响应
void FtdTrader::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

///错误应答
void FtdTrader::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}
	
///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
void FtdTrader::OnFrontDisconnected(int nReason)
{
}
		
///心跳超时警告。当长时间未收到报文时，该方法被调用。
void FtdTrader::OnHeartBeatWarning(int nTimeLapse)
{
}
	
///报单通知
void FtdTrader::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
}

///执行宣告通知
void FtdTrader::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
}

///询价通知
void FtdTrader::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
}

///报价通知
void FtdTrader::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{
}
	
///成交通知
void FtdTrader::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
}
