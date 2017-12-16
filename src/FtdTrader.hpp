#ifndef FT_TRADER_H
#define FT_TRADER_H

#include "ThostFtdcTraderApi.h"

class FtdTrader : public CThostFtdcTraderSpi
{
public:
  FtdTrader(CThostFtdcTraderApi* pApi);
  ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
  virtual void OnFrontConnected();

  ///登录请求响应
  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///投资者结算结果确认响应
  virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
  ///请求查询合约响应
  virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///请求查询资金账户响应
  virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///请求查询投资者持仓响应
  virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///报单录入请求响应
  virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///执行宣告录入请求响应
  virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///询价录入请求响应
  virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///报价录入请求响应
  virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///报单操作请求响应
  virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///执行宣告操作请求响应
  virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
  ///报价操作请求响应
  virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///错误应答
  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
  ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
  virtual void OnFrontDisconnected(int nReason);
		
  ///心跳超时警告。当长时间未收到报文时，该方法被调用。
  virtual void OnHeartBeatWarning(int nTimeLapse);
	
  ///报单通知
  virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

  ///执行宣告通知
  virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

  ///询价通知
  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

  ///报价通知
  virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);
	
  ///成交通知
  virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

private:
  void ReqOrderInsert();
  CThostFtdcTraderApi* mpApi;
  int mRequestId;
  char mInstruemtId[];
  TThostFtdcFrontIDType	FRONT_ID;	//前置编号
  TThostFtdcSessionIDType	SESSION_ID;	//会话编号
  TThostFtdcOrderRefType	ORDER_REF;	//报单引用
  TThostFtdcOrderRefType	EXECORDER_REF;	//执行宣告引用
  TThostFtdcOrderRefType	FORQUOTE_REF;	//询价引用
  TThostFtdcOrderRefType	QUOTE_REF;	//报价引用  
};

#endif
