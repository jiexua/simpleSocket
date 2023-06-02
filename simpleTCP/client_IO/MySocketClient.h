#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef MY_SOCKET_CLIENT_H
#define MY_SOCKET_CLIENT_H
 
#ifdef WIN32
#include "afxsock.h"
#else
#define UINT unsigned int 
#endif
#include <string>
#ifdef __linux__
#include <string.h>
#include <stdio.h>
#endif
#include "DataDef.h"
 
class MySocketClient
{
public:
	MySocketClient(std::string ip, UINT port);
	~MySocketClient(void);
 
	int onConnect();
	void disConnect();
	bool isConnect(){ return m_OnConnect; };
	int reSetSocket();
 
	int Read(RDClient &bufs);
	int Read(char* buf, int size);
	int Write(const char* buf, int size);
private:
	#ifdef WIN32
	void SocketThreadInit();
	#endif
private:
	int 	sock_fd;
	//fd_set read_flags,write_flags; // you know what these are  
	std::string m_IpAddress;
	UINT		m_Port;				//
	bool		m_OnConnect;		//
	/*
	*当前写入失败及读取线程都可重新建立链接,m_OnConnecting设置防止冲突
	*/
	bool		m_OnConnecting;		//
	bool        m_ConnectONLog;	    //防止链接错误日志反复记录,切换状态时必定记录
	unsigned int m_log_Interval;	//防止链接错误日志长时间不记录,2018-10-08
};
 
#endif