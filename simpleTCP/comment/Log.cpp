#include "Log.h"
#include <time.h>
#include <sys/timeb.h>
#ifdef __linux__
#ifndef sprintf_s
#define sprintf_s sprintf
#endif
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#endif
 
CLogger* CLogger::m_pLogInstance = NULL;
//extern void WriteLog( const int iMsgType, const std::string strMsg);
extern char LOG_FILE_NAME[128];	//LOGFILE Name, should be defined
extern std::string logdir;
 
void WriteLog1( const int iMsgType, const char * strMsg)
{
	try {
		time_t tt;
		struct timeb tm0;
		struct tm tm1;
		char buf[512];
		FILE * fpLog = NULL;
 
		//time(&tt);
		ftime(&tm0);
		tt = tm0.time;
#ifdef WIN32
		localtime_s(&tm1, &tt);
#else
		localtime_r(&tt, &tm1);
#endif
		sprintf_s(buf, "%04d-%02d-%02d %02d:%02d:%02d.%03d "
			, tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday
			, tm1.tm_hour, tm1.tm_min, tm1.tm_sec, tm0.millitm);
		std::string strTime = buf;
		buf[10] = '\0';
		//file name
		std::string strPath = logdir;	
#ifdef WIN32
		strPath += "\\";
#else
		strPath += "/";
#endif
		strPath += buf;
		strPath += "_";
		//
		switch (iMsgType)
		{
		case eHardError:
			strTime += "[HardErrorIMsg] ";
			break;
		case eSoftError:
			strTime += "[SoftErrorIMsg] ";
			break;
		case eConfigError:
			strTime += "[ConfErrorIMsg] ";
			break;
		case eParameterError:
			strTime += "[ParamErrorMsg] ";
			break;
		case eReadError:
			strTime += "[ReadErrorIMsg] ";
			break;
		case eWriteError:
			strTime += "[WriteErrorMsg] ";
			break;
		case eControlMessage:
			strTime += "[ControlExeMsg] ";
			//strPath += "chain_";
			break;
		case eResponseMessage:
			strTime += "[ResponseUpMsg] ";
			//strPath += "chain_";
			break;
		case eTipMessage:
			strTime += "[NoticeTipIMsg] ";
			break;
		default:
			strTime += "[PromptUnNoMsg] ";
			break;
		}
		strPath += LOG_FILE_NAME;
		//open
#ifdef WIN32
		fopen_s(&fpLog, strPath.c_str(), "a+");
#else
		fpLog = fopen(strPath.c_str(), "a+");
#endif
		if (NULL != fpLog)
		{
			fseek(fpLog, 0, SEEK_END);
			fwrite(strTime.c_str(), strTime.length(), 1, fpLog);
			fwrite(strMsg, strlen(strMsg), 1, fpLog);
			fwrite("\n", 1, 1, fpLog);
			fclose(fpLog);
		}
	}
	catch (...) {
		printf("write log[%d]{%s}error\n", iMsgType, strMsg);
	}
}
 
#ifdef WIN32
#include <windows.h>
#include <atlcomtime.h>
 
extern char SVCNAME[128];
void WriteLog( const int iMsgType, const char * strMsg)
{
	try {
		if (iMsgType < int(eConfigError))
		{
			HANDLE hEventSource;
			LPCTSTR lpszStrings[2];
			hEventSource = RegisterEventSource(NULL, SVCNAME);
			if (NULL != hEventSource)
			{
				lpszStrings[0] = SVCNAME;
				lpszStrings[1] = strMsg;
 
				ReportEvent(hEventSource,        // event log handle
					EVENTLOG_ERROR_TYPE, // event type
					0,                   // event category
					0,           // event identifier
					NULL,                // no security identifier
					2,                   // size of lpszStrings array
					0,                   // no binary data
					lpszStrings,         // array of strings
					NULL);               // no binary data
 
				DeregisterEventSource(hEventSource);
			}
		}
	}
	catch (...) {
		printf("WriteLog[%d]{%s}for Evnet error\n", iMsgType, strMsg);
	}
	WriteLog1(iMsgType, strMsg);
}
#else
void WriteLog( const int iMsgType, const char * strMsg)
{
	WriteLog1(iMsgType, strMsg);
}
#endif	
 
CLogger::CLogger() 
	: running(true)
	, i_log_over(0)
{
	char buf[256] = {0};
	sprintf_s(buf,"mkdir %s",logdir.c_str());
	system(buf);
	this->start();
};
 
CLogger::~CLogger()
{
	running = false;
};
 
CLogger* CLogger::createInstance( void )
{
	if (m_pLogInstance == NULL)
	{
		m_pLogInstance = new CLogger();
		return m_pLogInstance;
	}
	else
		return m_pLogInstance;
};
 
int CLogger::Run()
{
	MyLogStruct log_;
	while (running) {
		if (getFirstLog(log_))
		{
			WriteLog(log_.type, log_.szBuffer);
#ifndef WIN32
			printf("Log::[%d]-->%s\n", getpid(), log_.szBuffer);
#else
			printf("Log::-->%s\n", log_.szBuffer);
#endif
		}
#ifdef WIN32
		Sleep(10);
#else
		usleep(10000);
#endif
	}
	return 0;
};
 
void CLogger::Log(const eLogType type, const char* lpszFormat, ...)
{
	va_list args;
	//char   szBuffer[2048] = {0};
	MyLogStruct log_;
	log_.type = static_cast<int>(type);
	va_start(args, lpszFormat);
#ifdef WIN32
	vsnprintf_s(log_.szBuffer,sizeof(log_.szBuffer), lpszFormat, args);
#else
	vsnprintf(log_.szBuffer, sizeof(log_.szBuffer), lpszFormat, args);
#endif
	va_end(args); 
	addLog(log_);
}
 
bool CLogger::getFirstLog(MyLogStruct &it) {
	bool ret = false;
	m_Mutex_Log.Lock();
	if (!mylogs.empty()) {
		it = mylogs.front();
		mylogs.pop();
		ret = true;
	}
	m_Mutex_Log.Unlock();
	return ret;
}
 
void CLogger::addLog(MyLogStruct it) {
	m_Mutex_Log.Lock();
	if (mylogs.size() > 100) {
		i_log_over++;
		mylogs.pop();
	}
	mylogs.push(it);
	m_Mutex_Log.Unlock();
	if (i_log_over >= 100) {//每溢出100次，报告一次
		MyLogStruct log_;
		log_.type = static_cast<int>(eTipMessage);
		sprintf(log_.szBuffer,"the size of mylogs queue is up to limmit size[100],[%s %s %d]."
			, __FILE__, __FUNCTION__, __LINE__);
		m_Mutex_Log.Lock();
		mylogs.push(log_);
		m_Mutex_Log.Unlock();
		i_log_over = 0;
	}
}
 
#ifndef WIN32
 
#include <sys/vfs.h>
#include <mntent.h>
//int GetPrivateProfileInt(const char * lpAppName, const char *lpKeyName, int nDefault, const char * lpFileName)
//{
//	return nDefault;
//}
//int GetPrivateProfileString(const char * lpAppName, const char * lpKeyName, const char * szDefault, char * szOut, const int nLen ,const char * lpFileName)
//{
//	strncpy(szOut, szDefault, nLen);
//	return 0;
//}
 
 
int GetPrivateProfileString(const char *AppName, const char *key, const char *defaultvalue, char *lpReturnedString, const int nSize, const char *lpFileName)
{
	bool bFindAppName = false;    
	char tem[1000];
	char *ptr;
	FILE *fp;
	char name[150];
	snprintf(name, sizeof(name), "[%s]", AppName);
	strncpy(lpReturnedString,defaultvalue, nSize);
	if( (lpFileName == NULL) || ((fp=fopen(lpFileName,"rt"))==NULL) )// || fgets(tem,len,fp) == NULL)
	{
		return strlen(lpReturnedString);
	}
	while(fgets(tem,sizeof(tem),fp))
	{   
		if(tem[0] == '[')
		{
			bFindAppName = false;
			if(strstr(tem,name)==tem)
				bFindAppName = true;
		}
		else
		{
			if(bFindAppName == true)
			{
				unsigned int n =strcspn(tem,"=");
				if(static_cast<unsigned int>(strlen(key)) == n
					&& static_cast<int>(strncasecmp(tem,key,n)) == 0)
				{
					strncpy(lpReturnedString, tem+n+1,nSize);
					if( (ptr = strchr(lpReturnedString, '\n')) != NULL)
						*ptr = '\0';
					if( (ptr = strchr(lpReturnedString, '\r')) != NULL)
						*ptr = '\0';
					break;
				}
			}
		}
	}
	fclose(fp);
	return strlen(lpReturnedString);
}
 
 
int GetPrivateProfileInt(const char *AppName,const char *key,const int defaultvalue,const char *lpFileName)
{
	char str[20];
	int nRet = defaultvalue;
	if(GetPrivateProfileString(AppName, key, "", str, sizeof(str), lpFileName) > 0)
	{
		nRet = atoi(str);
	}
	return nRet;
}
#endif