#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MYSOCKETRD_H_
#define _MYSOCKETRD_H_
/*
*从服务端获取数据
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
 
class MySocketRD : public MyThread
{
public:
	MySocketRD(void);
	virtual ~MySocketRD(void);
 
	void setPrivateDataPtr(MySocketClient *myPData, int _netType=1);
	int Run();
	//从缓存中读取帧数据处理，请按需自行处理该函数
	int AddFrame(const unsigned char *buf, int len);
private:
	bool	running;
	int		netType;//数据读写处理类型
	MySocketClient	*myPDataPrt;
	QueueData<TCP_Data> ReadData;
};
 
#endif