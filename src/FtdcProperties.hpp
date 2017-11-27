#ifndef FTDC_PROPERTIES_HPP
#define FTDC_PROPERTIES_HPP

#include <string>

using namespace std;

class FtdcProperties
{
public:
  FtdcProperties();
  string GetFrontUrl()
  {
    return mFrontUrl;
  }
  string GetBrokerId()
  {
    return mBrokerId;
  }
  string GetUserId()
  {
    return mUserId;
  }
  string GetPassword()
  {
    return mPassword;
  }
private:
  string mFrontUrl;
  string mBrokerId;
  string mUserId;
  string mPassword;
};

#endif
