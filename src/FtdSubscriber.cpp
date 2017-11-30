#include "FtdSubscriber.hpp"

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

using namespace std;

FtdSubscriber::FtdSubscriber(CThostFtdcMdApi* pApi, const char* pBrokerId, const char* pUserId, const char* pPassword)
  : mpApi(pApi), mRequestId(0)
{
  memset(&mReq, 0, sizeof(mReq));

  strcpy(mReq.BrokerID, pBrokerId);
  strcpy(mReq.UserID, pUserId);
  strcpy(mReq.Password, pPassword);
}

void FtdSubscriber::OnFrontConnected()
{
  cerr << "-->" << __FUNCTION__ << endl;    
  
  int ret = -1;
  ret = mpApi->ReqUserLogin(&mReq, mRequestId);
  cerr << "ReqUserLogin:" << ret << endl;
}

void FtdSubscriber::OnFrontDisconnected(int nReason)
{
  cerr << "-->" << __FUNCTION__ << endl;  
}

void FtdSubscriber::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "-->" << __FUNCTION__ << endl;
  cerr << "OnRspUserLogin:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
  cerr << "TradingDay:" << pRspUserLogin->TradingDay << endl;
  cerr << "LoginTime:" << pRspUserLogin->LoginTime << endl;
  cerr << "BrokerID:" << pRspUserLogin->BrokerID << endl;
  cerr << "UserID:" << pRspUserLogin->UserID << endl;

  ifstream if_instruments("./etc/instruments");
  string instrument;
  char* ppInstrumentId[1024];
  int iInstrumentId = 0;
  while (getline(if_instruments, instrument))
    {
      ppInstrumentId[iInstrumentId] = (char*)malloc(instrument.size()+1);
      memset(ppInstrumentId[iInstrumentId], 0, instrument.size()+1);
      strcpy(ppInstrumentId[iInstrumentId], instrument.c_str());
      iInstrumentId++;
    }

  int ret = mpApi->SubscribeMarketData(ppInstrumentId, iInstrumentId);
  cerr << "SubscribeMarketData:" << ret << endl;
}

void FtdSubscriber::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "-->" << __FUNCTION__ << endl;
  cerr << "OnRspSubMarketData:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
  cerr << pSpecificInstrument->InstrumentID << endl;
}

void FtdSubscriber::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
  cerr << "-->" << __FUNCTION__ << endl;
  cerr << pDepthMarketData->InstrumentID << endl;

  // The article below explains struct tm should not be freed by invoker
  // https://stackoverflow.com/questions/6210880/does-returned-struct-of-localtime-need-to-be-freed
  std::time_t time1 = std::time(NULL);
  struct tm* tm_time1 = std::localtime(&time1);
  char time_yyyy_mm_dd[32];
  strftime(time_yyyy_mm_dd, 32, "%Y%m%d", tm_time1);
  string instrument(pDepthMarketData->InstrumentID);
  string file_name = "./data/"+instrument+"-"+time_yyyy_mm_dd;
  ofstream out(file_name.c_str(), std::ofstream::out | std::ofstream::app);

  std::time_t time2 = std::time(NULL);
  struct tm* tm_time2 = std::localtime(&time2);
  char time_yyyy_mm_dd_HH_MM_SS[128];
  strftime(time_yyyy_mm_dd_HH_MM_SS, 128, "%F %T: ", tm_time2);

  out << time_yyyy_mm_dd_HH_MM_SS << ","
      << pDepthMarketData->TradingDay << ","
      << pDepthMarketData->InstrumentID << ","
      << pDepthMarketData->ExchangeID << ","
      << pDepthMarketData->ExchangeInstID << ","
      << pDepthMarketData->LastPrice << ","
      << pDepthMarketData->PreSettlementPrice << ","
      << pDepthMarketData->PreClosePrice << ","
      << pDepthMarketData->PreOpenInterest << ","
      << pDepthMarketData->OpenPrice << ","
      << pDepthMarketData->HighestPrice << ","
      << pDepthMarketData->LowestPrice << ","
      << pDepthMarketData->Volume << ","
      << pDepthMarketData->Turnover << ","
      << pDepthMarketData->OpenInterest << ","
      << pDepthMarketData->ClosePrice << ","
      << pDepthMarketData->SettlementPrice << ","
      << pDepthMarketData->UpperLimitPrice << ","
      << pDepthMarketData->LowerLimitPrice << ","
      << pDepthMarketData->PreDelta << ","
      << pDepthMarketData->CurrDelta << ","
      << pDepthMarketData->UpdateTime << ","
      << pDepthMarketData->UpdateMillisec << ","
      << pDepthMarketData->BidPrice1 << ","
      << pDepthMarketData->BidVolume1 << ","
      << pDepthMarketData->AskPrice1 << ","
      << pDepthMarketData->AskVolume1 << ","
      << pDepthMarketData->BidPrice2 << ","
      << pDepthMarketData->BidVolume2 << ","
      << pDepthMarketData->AskPrice2 << ","
      << pDepthMarketData->AskVolume2 << ","
      << pDepthMarketData->BidPrice3 << ","
      << pDepthMarketData->BidVolume3 << ","
      << pDepthMarketData->AskPrice3 << ","
      << pDepthMarketData->AskVolume3 << ","
      << pDepthMarketData->BidPrice4 << ","
      << pDepthMarketData->BidVolume4 << ","
      << pDepthMarketData->AskPrice4 << ","
      << pDepthMarketData->AskVolume4 << ","
      << pDepthMarketData->BidPrice5 << ","
      << pDepthMarketData->BidVolume5 << ","
      << pDepthMarketData->AskPrice5 << ","
      << pDepthMarketData->AskVolume5 << ","
      << pDepthMarketData->AveragePrice << ","
      << pDepthMarketData->ActionDay
      << endl;
}

void FtdSubscriber::OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast)
{
  cerr << "--->>> "<< "OnRspError" << endl;
  IsErrorRspInfo(pRspInfo);
}

bool FtdSubscriber::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
  bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
  if (bResult)
    cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
  return bResult;
}
