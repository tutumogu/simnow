bin_PROGRAMS = simnow testFttc ana
simnow_SOURCES = simnow.cpp Ftdc.cpp FtdSubscriber.cpp FtdTrader.cpp FtdcProperties.cpp
simnow_CPPFLAGS=-I../v6.3.6_20141230traderapi_linux64
simnow_LDFLAGS=-L../v6.3.6_20141230traderapi_linux64
simnow_LDADD=-l:thostmduserapi.so -l:thosttraderapi.so

testFttc_SOURCES = testFttc.cpp FtdTrader.cpp
testFttc_CPPFLAGS=-I../v6.3.6_20141230traderapi_linux64
testFttc_LDFLAGS=-L../v6.3.6_20141230traderapi_linux64
testFttc_LDADD=-l:thostmduserapi.so -l:thosttraderapi.so

ana_SOURCES = ana.cpp
ana_CPPFLAGS=-I../v6.3.6_20141230traderapi_linux64
ana_LDADD=-lboost_filesystem -lboost_regex -lboost_date_time -lboost_system
