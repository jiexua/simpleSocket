#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MYSOCKETGXRD_H_
#define _MYSOCKETGXRD_H_
/*
该线程从各个客户端读取数据,并将数据分帧
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
 
class MySocketRD : public MyThread
{
public:
	MySocketRD(MySocketPrivate* myPDataPrt_, int netType_=1);
	virtual ~MySocketRD(void);
 
	int Run();
	//从缓存中读取帧数据处理，请按需自行处理该函数
	int AddFrame(const std::string link, const unsigned char *buf, int len);
private:
	bool running;
	int netType;//数据读写处理类型
	MySocketPrivate *myPDataPrt;
	QueueData<RDS> ReadData;
};
 
#endif