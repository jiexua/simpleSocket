#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MySocketWD_H_
#define _MySocketWD_H_
/*
该线程向指定客户端写入数据,将数据协议编码并序列化
*/
#ifdef WIN32
#include "win32Thread.h"
#endif
#ifdef linux
#include "myThread.h"
#endif
#include "DataDef.h"
#include "queuedata.h"
 
class MySocketPrivate;
 
class MySocketWD : public MyThread
{
public:
	MySocketWD(MySocketPrivate* myPDataPrt_,int netType_=1);
	virtual ~MySocketWD(void);
 
	int Run();
	int AddData(const char* buf, int len);
	int getBuffer(unsigned long long &_ipInt, unsigned char* _buf);
private:
	bool running;
	int netType;
	MySocketPrivate *myPDataPrt;
	QueueData<WDS> WriteData;
};
 
#endif