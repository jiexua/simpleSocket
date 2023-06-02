#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MYSOCKETPRIVATE_H_
#define _MYSOCKETPRIVATE_H_
 
#include <map>
#include <queue>
#include <set>
 
#ifdef WIN32
#include "afxsock.h"
 
#define MY_SOCKET	SOCKET
#define MY_SOCKET_NULL	NULL
#endif
#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
#define printf_s printf
#define sprintf_s sprintf
#define MY_SOCKET	int
#define MY_SOCKET_NULL	(-1)
#endif
 
#include "Mutex.h"
#include "hashmap.h"
#include "DataDef.h"
 
class MySocketPrivate
{
public:
	MySocketPrivate(unsigned int port) 
		: m_Port(port)
		, m_OnListen(false)
	{
		m_SSocket = MY_SOCKET_NULL;
		m_CSockets.clear();
#ifdef WIN32	
		/*
		*	This   function   should   be   called   once   in   each   secondary   thread   
		*   before   the   first   socket   is   created   in   the   new   thread.   
		*/
		SocketThreadInit();
#endif
	};
	~MySocketPrivate(){
		disConnect();
	};
public:
	int onConnect();
	void disConnect();
 
	int Read(std::map<KeyObj_Client,RDClient> &bufs);
	int Write(const char* buf, int size);
	int Write(unsigned long long ipInt,const char* buf, int size);
 
	bool Accept();
	bool get_ipInt_list(std::set<long> &ipintlist);	//获取在线端的整型IP
#ifdef WIN32
private:
	void SocketThreadInit();
#endif
private:
	void deleteSSocket();					//删除服务端
	void deleteCSocket();					//删除所有客户端
	void deleteCSocket(MY_SOCKET m_CSocket);//删除指定客户端
private:
	MY_SOCKET				m_SSocket;			//服务端
	unsigned int			m_Port;				//端口变量
	bool					m_OnListen;			//用于标注侦听
	PYMutex					m_MyMutex;
	std::map<KeyObj_Client,MY_SOCKET>	m_CSockets;		//绑定客户端
};
 
#endif //