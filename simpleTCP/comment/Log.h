#ifndef CHANNELLOG_H
#define CHANNELLOG_H
 
#include <stdio.h>
#include <stdarg.h>
#include <string>
//#ifndef LOGUDPPORT
//#define LOGUDPPORT	989
//#endif
//#define MAXDATASIZE 10240
//extern bool m_bDebug;
 
#ifdef WIN32
#include "win32Thread.h"
#endif
 
#ifdef linux
#include "myThread.h"
#include <string.h>
#endif
 
#include <queue>
#include "Mutex.h"
 
#ifndef WIN32
#include <string>
#include <sstream>
namespace std
{
	template < typename T > std::string to_string(const T & n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}
int GetPrivateProfileString(const char *AppName, const char *key, const char *defaultvalue, char *lpReturnedString, const int nSize, const char *lpFileName);
int GetPrivateProfileInt(const char *AppName,const char *key,const int defaultvalue,const char *lpFileName);
 
 
#endif
 
 
enum eLogType 
{
	eHardError		= 1,
	eSoftError		= 2,
	eConfigError	= 3,
	eParameterError = 4,
	eReadError		= 5,
	eWriteError		= 6,
	eControlMessage = 7,
	eResponseMessage = 8,
	eTipMessage		= 9
};
 
struct MyLogStruct
{
	MyLogStruct():type(0)
	{
		memset(szBuffer, 0, 1024);
	};
	int type;
	char   szBuffer[1024];
};
 
class CLogger : public MyThread
{
public:
	CLogger();
	~CLogger();
	int Run();
public:
	void Log(const eLogType type, const char* lpszFormat, ...);
	static CLogger* createInstance( void );
private:
	bool getFirstLog(MyLogStruct &it);
	void addLog(MyLogStruct it);
private:
	static CLogger* m_pLogInstance;
	bool running;
	//for cache
	std::queue<MyLogStruct> mylogs;
	PYMutex m_Mutex_Log;
	int i_log_over;
};
#endif