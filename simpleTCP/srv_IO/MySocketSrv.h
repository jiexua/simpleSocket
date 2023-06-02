#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MYSOCKETSRV_H_
#define _MYSOCKETSRV_H_
 
#ifdef WIN32
#include "win32Thread.h"
#endif
#ifdef linux
#include "myThread.h"
#endif
 
class MySocketPrivate;
 
class MySocketSrv :	public MyThread
{
public:
	MySocketSrv();
	virtual ~MySocketSrv();
 
	void setPDataPtr(MySocketPrivate *myPData);
	int Run();
private:
	MySocketPrivate *myPDataPrt;
};
#endif