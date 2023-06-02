#include "MySocketPrivate.h"
#include "myFunc.h"
#include "Log.h"
 
#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
 
#define printf_s printf
#define sprintf_s sprintf
 
#pragma message("def printf_s from printf And def sprintf_s from sprintf")
#endif
 
 
#ifdef WIN32
void MySocketPrivate::SocketThreadInit()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
 
	wVersionRequested = MAKEWORD(2, 2);
 
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) 
	{
		//printf("WSAStartup failed with error: %d\n", err);
		CLogger::createInstance()->Log(eSoftError,
			"WSAStartup failed with error: %d, [%s %s %d]"
			, err
			, __FILE__, __FUNCTION__, __LINE__);
		return;
	}
 
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) 
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		//printf("Could not find a usable version of Winsock.dll\n");
		CLogger::createInstance()->Log(eSoftError,
			"Could not find a usable version of Winsock.dll: [%s %s %d]"
			, __FILE__, __FUNCTION__, __LINE__);
		WSACleanup();
		return;
	}
	else {
		printf("The Winsock 2.2 dll was found okay\n");
	}
}
#endif
 
int MySocketPrivate::onConnect()
{
	if (m_OnListen)     //服务器Socket是否已经创建
	{
		//printf_s("it's has been Listten! \r\n");
		CLogger::createInstance()->Log(eTipMessage,
			"it's has been Listten, [%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		return 1;
	}
	else {
		#ifdef WIN32
		m_SSocket = socket(AF_INET, SOCK_STREAM, 0);
		SOCKADDR_IN addrServ;
		addrServ.sin_family = AF_INET;
		addrServ.sin_port = htons(m_Port);
		addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		bind(m_SSocket, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));
 
		/*
		*3.在send(),recv()过程中有时由于网络状况等原因，收发不能预期进行,可以设置收发时限：
		*int nNetTimeout = 1000; //1秒
		*发送时限
		*setsockopt( socket, SOL_SOCKET, SO_SNDTIMEO, ( char * )&nNetTimeout, sizeof( int ) );
		*接收时限
		*setsockopt( socket, SOL_SOCKET, SO_RCVTIMEO, ( char * )&nNetTimeout, sizeof( int ) );
		*4.在send()的时候，返回的是实际发送出去的字节(同步)或发送到socket缓冲区的字节(异步)；系统默认的状态发送和接收一次为8688字节(约
		*为8.5K)；在实际的过程中如果发送或是接收的数据量比较大，可以设置socket缓冲区，避免send(),recv()不断的循环收发：
		* 接收缓冲区
		*int nRecvBufLen = 32 * 1024; //设置为32K
		*setsockopt( s, SOL_SOCKET, SO_RCVBUF, ( const char* )&nRecvBufLen, sizeof( int ) );
		*发送缓冲区
		*int nSendBufLen = 32*1024; //设置为32K
		*setsockopt( s, SOL_SOCKET, SO_SNDBUF, ( const char* )&nSendBufLen, sizeof( int ) );
		*5.在发送数据的时，不执行由系统缓冲区到socket缓冲区的拷贝，以提高程序的性能：
		*int nZero = 0;
		*setsockopt( socket, SOL_SOCKET, SO_SNDBUF, ( char * )&nZero, sizeof( nZero ) );
		*6.在接收数据时，不执行将socket缓冲区的内容拷贝到系统缓冲区：
		*int nZero = 0;
		*setsockopt( s, SOL_SOCKET, SO_RCVBUF, ( char * )&nZero, sizeof( int ) );
		*/
		//如果创建Socket失败则提示，成功则开始监听
		if (listen(m_SSocket, 20) == SOCKET_ERROR)
		{
			closesocket(m_SSocket);
			//printf_s("ServerSocket Create failed! error:%d \r\n",static_cast<int>(GetLastError()));
			CLogger::createInstance()->Log(eParameterError,
				"ServerSocket Create failed! error:%d, [%s %s %d]"
				, static_cast<int>(GetLastError())
				, __FILE__, __FUNCTION__, __LINE__);
			return -1;
		}
		else {
			CLogger::createInstance()->Log(eTipMessage, "on listen port(%d)", m_Port);
			m_OnListen = true;
			return 1;
		}
		#else
		m_SSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (MY_SOCKET_NULL == m_SSocket)
		{
			CLogger::createInstance()->Log(eSoftError,
				"socket create fail ![%s %s %d]!"
				, __FILE__, __FUNCTION__, __LINE__);
			return -1;
		}
		struct sockaddr_in s_add;
		bzero(&s_add, sizeof(struct sockaddr_in));
		s_add.sin_family = AF_INET;
		s_add.sin_addr.s_addr = htonl(INADDR_ANY);
		s_add.sin_port = htons(m_Port);
		if (-1 == bind(m_SSocket, (struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
		{
			CLogger::createInstance()->Log(eSoftError,
				"socket bind fail, %d ![%s %s %d]",m_Port
				, __FILE__, __FUNCTION__, __LINE__);
			return -1;
		}
		else {
			CLogger::createInstance()->Log(eTipMessage,
				"bind success, %d! [%s %s %d]!",m_Port
				, __FILE__, __FUNCTION__, __LINE__);
		}
		if (-1 == listen(m_SSocket, 5))
		{
			CLogger::createInstance()->Log(eSoftError,
				"listen %d fail ![%s %s %d]",m_Port
				, __FILE__, __FUNCTION__, __LINE__);
			return -1;
		}
		else {
			CLogger::createInstance()->Log(eTipMessage,
				"listen success, %d ! [%s %s %d]!",m_Port
				, __FILE__, __FUNCTION__, __LINE__);
		}
		m_OnListen = true;
		return 1;
		#endif
	}
}
 
bool MySocketPrivate::Accept()
{
	bool bRet = true;
	if (m_OnListen)
	{
		#ifdef WIN32
		SOCKADDR_IN cliAddr;
		int length = sizeof(SOCKADDR);
		SOCKET cliSock = accept(m_SSocket, (SOCKADDR*)&cliAddr, &length);
		if (INVALID_SOCKET == cliSock)
		{
			closesocket(cliSock);
			//printf_s("Connect Accept Failed: %d! \r\n",static_cast<int>(GetLastError()));
			CLogger::createInstance()->Log(eSoftError,
				"Connect Accept Failed: %d! , [%s %s %d]"
				, static_cast<int>(GetLastError())
				, __FILE__, __FUNCTION__, __LINE__);
			bRet = false;
		}
		else {
			//cliAddr.sin_addr.S_un.S_addr;
			char _ipport[64] = { 0 };
			//sprintf_s(_ipport,"%s",(char*)inet_ntoa((*(in_addr*)&(cliAddr.sin_addr))));
			sprintf_s(_ipport, "%s:%d", (char*)inet_ntoa((*(in_addr*)&(cliAddr.sin_addr))), cliAddr.sin_port);
			//std::string _linkInfo = _ipport;
			KeyObj_Client _linkInfo((char*)inet_ntoa((*(in_addr*)&(cliAddr.sin_addr))), cliAddr.sin_port);
 
			int nNetTimeout = 100; //1秒
			//setsockopt(cliSock, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
			setsockopt(cliSock, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
			m_MyMutex.Lock();
			m_CSockets[_linkInfo] = cliSock;//添加客户端
			m_MyMutex.Unlock();
			//printf_s("Connect Accept Success: %s \r\n", _ipport);
			CLogger::createInstance()->Log(eTipMessage,
				"Connect Accept Success: %s,[%s %s %d]"
				, _ipport
				, __FILE__, __FUNCTION__, __LINE__);
		}
		#else
		int sin_size = sizeof(struct sockaddr_in);
		struct sockaddr_in c_add;
		// printf("MySocketPrivate::Accept 1\n");
		int nfp = accept(m_SSocket, (struct sockaddr *)(&c_add), (socklen_t*)&sin_size);
		if (-1 == nfp)
		{
			//printf("accept fail !\r\n");
			CLogger::createInstance()->Log(eParameterError,
				"accept fail![%s %s %d]"
				, __FILE__, __FUNCTION__, __LINE__);
			bRet = false;
		}
		else {
			char _ipport[64] = { 0 };
			std::string _ipStr = inet_ntoa((*(in_addr*)&(c_add.sin_addr)));
			//std::string _ipStr = PFunc::intToIp(htonl(c_add.sin_addr.s_addr));
			int _port = static_cast<int>(htons(c_add.sin_port));
			sprintf(_ipport, "%s:%d", _ipStr.c_str(), _port);
			/*
			struct timeval timeout = {3,0};
			//setsockopt(nfp,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(struct timeval));
			setsockopt(nfp,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));
			KeyObj_Client _linkInfo((char*)inet_ntoa((*(in_addr*)&(c_Addr.sin_addr))), cliAddr.sin_port);
			*/
			int  x = fcntl(nfp, F_GETFL, 0);
			fcntl(nfp, F_SETFL, x | O_NONBLOCK);
			KeyObj_Client _linkInfo(_ipStr, _port);
			m_MyMutex.Lock();
			//nfps.push_back(nfp);
			//nfps[KeyObj_Client(_ipStr, _port)] = nfp;
			m_CSockets[_linkInfo] = nfp;
			m_MyMutex.Unlock();
			//printf("accept ok!\r\nServer start get connect from %s\r\n", _ipport);
			CLogger::createInstance()->Log(eTipMessage,
				"accept ok!\r\nServer start get connect from %s.[%s %s %d]"
				, _ipport
				, __FILE__, __FUNCTION__, __LINE__);
		}
		#endif
	}
	else {
		bRet = false;
		//printf_s("m_OnListen is false, please check Listen state, Accept error \r\n");
		CLogger::createInstance()->Log(eTipMessage,
			"m_OnListen is false, please check Listen state, Accept error,[%s %s %d]"
			, __FILE__, __FUNCTION__, __LINE__);
	}
	return bRet;
};
 
bool MySocketPrivate::get_ipInt_list(std::set<long> &ipintlist)
{
	for (std::map<KeyObj_Client, MY_SOCKET>::iterator it = m_CSockets.begin();it!= m_CSockets.end();it++)
	{
		ipintlist.insert(it->first.m_ip);
	}
	return !ipintlist.empty();
}
 
void MySocketPrivate::disConnect()
{
	deleteCSocket();//删除客户端
	deleteSSocket();//删除服务端
	#ifdef WIN32
	WSACleanup();
	#endif
	CLogger::createInstance()->Log(eTipMessage,
		"socket disConnect success and exit: [%s %s %d]!"
		, __FILE__, __FUNCTION__, __LINE__);
}
 
void MySocketPrivate::deleteCSocket()
{
	m_MyMutex.Lock();
	std::map<KeyObj_Client, MY_SOCKET>::iterator it = m_CSockets.begin();
	while (it != m_CSockets.end()) 
	{
		//删除链接
		deleteCSocket(it->second);
		#ifdef WIN32
		it = m_CSockets.erase(it);
		#else
		std::map<KeyObj_Client, MY_SOCKET>::iterator ittemp = it++;
		m_CSockets.erase(ittemp);
		#endif
	}
	m_MyMutex.Unlock();
}
 
void MySocketPrivate::deleteCSocket(MY_SOCKET m_CSocket)
{
	try {
		if (MY_SOCKET_NULL != m_CSocket) 
		{
			#ifdef WIN32
			closesocket(m_CSocket);
			#else
			close(m_CSocket);
			#endif
			m_CSocket = MY_SOCKET_NULL;
		}
	}
	catch (...) {
		CLogger::createInstance()->Log(eSoftError,
			"socket deleteCSocket exception and failed! [%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
	}
}
 
void MySocketPrivate::deleteSSocket()
{
	m_OnListen = false;
	try {
		if (MY_SOCKET_NULL != m_SSocket) 
		{
			#ifdef WIN32
			closesocket(m_SSocket);
			#else
			close(m_SSocket);
			#endif
			m_SSocket = MY_SOCKET_NULL;
		}
	}
	catch (...) {
		CLogger::createInstance()->Log(eSoftError,
			"socket deleteSSocket exception and failed! [%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
	}
};
 
 
//return success read count
int MySocketPrivate::Read(std::map<KeyObj_Client, RDClient> &bufs)
{
	int ret = 0;
	
	m_MyMutex.Lock();
	std::map<KeyObj_Client, MY_SOCKET>::iterator it = m_CSockets.begin();
	while (it != m_CSockets.end()) 
	{
		char _buf[512] = { 0 };
#ifdef WIN32
		int re_one = recv(it->second, _buf, 512, 0);
		if (re_one <= 0) 
		{
			int _error = GetLastError();
			if (_error != 10060) 
			{
				//printf_s("read data failed from %s! return val is %d. \r\n", it->first.c_str(), re);
				CLogger::createInstance()->Log(eReadError,
					"read data failed from %s! return val is %d,error(%d).[%s %s %d]"
					, it->first.m_ipStr.c_str(), re_one, _error
					, __FILE__, __FUNCTION__, __LINE__);
				//删除链接
				deleteCSocket(it->second);
				it = m_CSockets.erase(it);
				continue;
			}
			else {
				re_one = 0;
			}
		}
#else
		int re_one = recv(it->second, _buf, 256, MSG_DONTWAIT);
		if (re_one <= 0)
		{
			if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
			{
				usleep(10);
				re_one = 0;
			}
			else {
				CLogger::createInstance()->Log(eReadError,
					"read data failed from %s! return val is %d.[%s %s %d]"
					, it->first.m_ipStr.c_str(), re_one
					, __FILE__, __FUNCTION__, __LINE__);
				//删除连接
				deleteCSocket(it->second);
				std::map<KeyObj_Client, MY_SOCKET>::iterator ittemp = it++;
				m_CSockets.erase(ittemp);
				continue;
			}
		}
#endif
		if (re_one>0) 
		{
			ret += 1;
			std::map<KeyObj_Client, RDClient>::iterator itrd = bufs.find(it->first);
			if (itrd != bufs.end()) 
			{
				itrd->second.add((unsigned char*)_buf, re_one);
			}
			else {
				bufs[it->first] = RDClient((unsigned char*)_buf, re_one);
			}
		}
		it++;
	}
	m_MyMutex.Unlock();
	return ret;
};
 
//return success count
int MySocketPrivate::Write(const char* buf, int size)
{
	int ret = 0;
 
	m_MyMutex.Lock();
	std::map<KeyObj_Client, MY_SOCKET>::iterator it = m_CSockets.begin();
	while (it != m_CSockets.end()) 
	{
		// printf_s("write data %d to client is started!\r\n",size);
#ifdef WIN32
		int re = send(it->second, buf, size, 0);
		if (re <= 0) 
		{
			int _error = GetLastError();
			if (_error != 10060)
			{
				CLogger::createInstance()->Log(eWriteError,
					"socket write data failed! return val is %d,%s.[%s %s %d]"
					, re, buf
					, __FILE__, __FUNCTION__, __LINE__);
				//删除连接
				deleteCSocket(it->second);
				it = m_CSockets.erase(it);
				continue;
			}
			else {
				re = 0;
			}
		}
#else
		int re = send(it->second, buf, size, MSG_DONTWAIT);
		if (re <= 0) 
		{
			if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
			{
				usleep(10);
				re = 0;
			}
			else {
				CLogger::createInstance()->Log(eWriteError,
					"Write Data Failed! error(%d,%s)! [%s %s %d]"
					, errno, strerror(errno)
					, __FILE__, __FUNCTION__, __LINE__);
				//删除连接
				deleteCSocket(it->second);
				std::map<KeyObj_Client, MY_SOCKET>::iterator ittemp = it++;
				m_CSockets.erase(ittemp);
				continue;
			}
		}
#endif
		else{
			ret += 1;
		}
		it++;
	}
	m_MyMutex.Unlock();
	return ret;
};
 
//return success count
int MySocketPrivate::Write(unsigned long long ipInt, const char* buf, int size)
{
	int ret = 0;
 
	m_MyMutex.Lock();
	std::map<KeyObj_Client, MY_SOCKET>::iterator it = m_CSockets.begin();
	while (it != m_CSockets.end()) 
	{
		// printf_s("write data %d to client is started!\r\n",size);
		//当前版本只针对网络地址做判断,即一台电脑多个客户端连接，都会被发送数据
		if ((unsigned long long)it->first.m_ip == ipInt)
		{
#ifdef WIN32
			int re = send(it->second, buf, size, 0);
			if (re < 0) 
			{
				int _error = GetLastError();
				if (_error != 10060)
				{
					CLogger::createInstance()->Log(eWriteError,
						"socket write data failed! return val is %d,%s.[%s %s %d]"
						, re, buf
						, __FILE__, __FUNCTION__, __LINE__);
					//删除连接
					deleteCSocket(it->second);
					it = m_CSockets.erase(it);
					continue;
				}
				else {
					re = 0;
				}
			}
#else
			int re = send(it->second, buf, size, MSG_DONTWAIT);
			if (re <= 0) 
			{
				if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
				{
					usleep(10);
					re = 0;
				}
				else {
					CLogger::createInstance()->Log(eWriteError,
						"Write Data Failed! error(%d,%s)! [%s %s %d]"
						, errno, strerror(errno)
						, __FILE__, __FUNCTION__, __LINE__);
					//删除连接
					deleteCSocket(it->second);
					std::map<KeyObj_Client, MY_SOCKET>::iterator ittemp = it++;
					m_CSockets.erase(ittemp);
					continue;
				}
			}
#endif
			else {
				ret += 1;
			}
		}
		it++;
	}
	m_MyMutex.Unlock();
	return ret;
}