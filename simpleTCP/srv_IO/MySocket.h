#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MySocket_H_
#define _MySocket_H_
/*
*建立socket服务端
*/
#include "DataDef.h"
 
class MySocketPrivate;
class MySocketSrv;
class MySocketRD;
class MySocketWD;
 
class MySocket
{
public:
	MySocket(unsigned int port,int netType_=1);
	~MySocket(void);
public:
 
	int Read(){ return -1; };
	int Write(){ return -1; };
	//
	//int Read(char* buf, int size);
	int Write(const char* buf, int size);
private:
	MySocketPrivate *my_PrivateData;
	MySocketSrv *my_SocketSrv;
	MySocketRD *m_MySocketRD;
	MySocketWD *m_MySocketWD;
};
 
#endif //_MYSOCKET_H_