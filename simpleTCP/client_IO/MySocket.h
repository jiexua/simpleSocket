#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MYSOCKET_H_
#define _MYSOCKET_H_
/*
*建立socket客户端
*/
#include <string>
 
#include "DataDef.h"
 
class MySocketClient;
class MySocketWD;
class MySocketRD;
 
class MySocket
{
public:
	MySocket(int _tranid, NetArg _netarg);
	virtual ~MySocket(void);
public:
 
	virtual int Read(){ return -1; };
	virtual int Write(){ return -1; };
 
	int Write(const char* buf, int size);
private:
	int tranid;
	NetArg netarg;
	MySocketClient *my_PrivateData;
	MySocketWD *m_MySocketWD;
	MySocketRD *m_MySocketRD;
};
 
#endif //_MYSOCKET_H_