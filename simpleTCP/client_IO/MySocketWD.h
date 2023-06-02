#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MYSOCKETWD_H_
#define _MYSOCKETWD_H_
/*
*从缓存采集数据,向服务端发送数据
*/
#ifdef WIN32
#include "win32Thread.h"
#endif
#ifdef linux
#include "myThread.h"
#endif
#include "DataDef.h"
#include "queuedata.h"
 
class MySocketClient;
 
class MySocketWD : public MyThread
{
public:
	MySocketWD(void);
	virtual ~MySocketWD(void);
 
	void setPrivateDataPtr(MySocketClient *myPData, int _netType=1);
	int Run();
 
	int add_data(const char* buf, int len);
	int getBuffer(unsigned char * _buf);
	int getHeartBeatBuffer(unsigned char * buf);
private:
	bool running;
	int netType;//数据读写处理类型
	unsigned int heartBeatWrite;
	MySocketClient *myPDataPrt;
	QueueData<TCP_Data> WriteData;
};
 
#endif