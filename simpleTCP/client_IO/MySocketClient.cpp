#include "MySocketClient.h"
 
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
#endif
 
#include "Log.h"
 
#ifdef WIN32
#include <mstcpip.h>  
 
void MySocketClient::SocketThreadInit()
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
			, err, __FILE__, __FUNCTION__, __LINE__);
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
	else
	{
		printf("The Winsock 2.2 dll was found okay\n");
	}
}
#endif
MySocketClient::MySocketClient(std::string ip, UINT port)
	: m_IpAddress(ip)
	, m_Port(port)
{
	sock_fd = -1;
#ifdef WIN32
	/*initf = true;
	if(!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)){
		CLogger::createInstance()->Log(eTipMessage,"AfxWinInit initial failed!");
		initf = false;
	}
	if (!AfxSocketInit())
	{
		CLogger::createInstance()->Log(eTipMessage,"WindowSocket initial failed!");
		initf = false;
	}
	*/
	SocketThreadInit();
#endif
	m_OnConnect = false;
	m_OnConnecting = false;
	m_ConnectONLog = true;
	m_log_Interval = static_cast<unsigned int>(time(NULL));
}
 
MySocketClient::~MySocketClient(void)
{
	disConnect();
}
 
int MySocketClient::onConnect()
{
	if (m_OnConnect) //
	{
		CLogger::createInstance()->Log(eTipMessage,
			"it is on connecting,Please disconnect!, [%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
	//防止链接冲突调用
	if (m_OnConnecting) 
	{
		return 0;
	}
	try {
		m_OnConnecting = true;
#ifdef WIN32
		sock_fd = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
		SOCKADDR_IN ser_addr;
		memset(&ser_addr, 0, sizeof(ser_addr));
		ser_addr.sin_family = AF_INET;
		ser_addr.sin_addr.s_addr = inet_addr(m_IpAddress.c_str());
		ser_addr.sin_port = htons(static_cast<unsigned short>(m_Port));
		if (connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
		{
			//printf("%s:%d, connect socket failed,%s:%d \r\n", __FILE__, __LINE__,m_IpAddress.c_str(),m_Port); 
			if (m_ConnectONLog|| m_log_Interval < static_cast<unsigned int>(time(NULL))) 
			{
				m_ConnectONLog = false;
				m_log_Interval = static_cast<unsigned int>(time(NULL)) + 3600;
				CLogger::createInstance()->Log(eConfigError,
					"connect socket failed,%s:%d, [%s %s %d]"
					, m_IpAddress.c_str(), m_Port
					, __FILE__, __FUNCTION__, __LINE__);
			}
			m_OnConnecting = false;
			return -1;
		}
		printf("connect socket %s:%d  !\r\n", m_IpAddress.c_str(), m_Port);
		CLogger::createInstance()->Log(eTipMessage,
			"connect socket %s:%d, [%s %s %d]!"
			, m_IpAddress.c_str(), m_Port
			, __FILE__, __FUNCTION__, __LINE__);
		int nNetTimeout = 10; //10毫秒
		setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
		setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
		//KeepAlive
		bool bKeepAlive = true;
		int nRet = setsockopt(sock_fd, SOL_SOCKET, SO_KEEPALIVE,(char*)&bKeepAlive, sizeof(bKeepAlive));
		if (nRet == SOCKET_ERROR)
		{
			CLogger::createInstance()->Log(eTipMessage
				, "connect socket %s:%d and setsockopt(SO_KEEPALIVE=true) fail!"
				, m_IpAddress.c_str(), m_Port);
		}
		// set KeepAlive parameter  
		tcp_keepalive alive_in;
		tcp_keepalive alive_out;
		alive_in.keepalivetime = 1000;  // 1s  
		alive_in.keepaliveinterval = 3000; //3s  
		alive_in.onoff = true;
		unsigned long ulBytesReturn = 0;
		nRet = WSAIoctl(sock_fd, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in),
			&alive_out, sizeof(alive_out), &ulBytesReturn, NULL, NULL);
		if (nRet == SOCKET_ERROR)
		{
			CLogger::createInstance()->Log(eTipMessage
				, "connect socket %s:%d and setsockopt(tcp_keepalive) fail!"
				, m_IpAddress.c_str(), m_Port);
		}
		m_OnConnect = true;
		m_OnConnecting = false;
		m_ConnectONLog = true;
		return 1;
#else
		sock_fd = socket(PF_INET, SOCK_STREAM, 0);
		//sock_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (-1 == sock_fd)
		{
			CLogger::createInstance()->Log(eTipMessage,
				"socket fail!, [%s %s %d]!"
				, __FILE__, __FUNCTION__, __LINE__);
			m_OnConnecting = false;
			return -1;
		}
		//printf("socket ok !\r\n");
		CLogger::createInstance()->Log(eTipMessage,
			"socket ok !, [%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		struct sockaddr_in s_add;
		bzero(&s_add, sizeof(struct sockaddr_in));
		s_add.sin_family = PF_INET;
		s_add.sin_addr.s_addr = inet_addr(m_IpAddress.c_str());
		s_add.sin_port = htons(m_Port);
		printf("s_addr = %#x ,port : %#x\r\n", s_add.sin_addr.s_addr, s_add.sin_port);
		CLogger::createInstance()->Log(eTipMessage,
			"s_addr = %#x ,port : %#x, [%s %s %d]"
			, s_add.sin_addr.s_addr, s_add.sin_port
			, __FILE__, __FUNCTION__, __LINE__);
 
		//int  x=fcntl(sock_fd,F_GETFL,0);  
		//fcntl(sock_fd,F_SETFL,x | O_NONBLOCK);  
		if (-1 == connect(sock_fd, (struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
		{
			if (m_ConnectONLog) 
			{
				m_ConnectONLog = false;
				CLogger::createInstance()->Log(eConfigError,
					"connect fail !, [%s %s %d]!"
					, __FILE__, __FUNCTION__, __LINE__);
			}
			m_OnConnecting = false;
			return -1;
		}
		int  x = fcntl(sock_fd, F_GETFL, 0);
		fcntl(sock_fd, F_SETFL, x | O_NONBLOCK);
		//signal(SIGCHLD, SIG_IGN);
		//FD_ZERO(&read_flags); // Zero the flags ready for using  
		//FD_ZERO(&write_flags);  
		//FD_SET(sock_fd, &read_flags); 
		//FD_SET(sock_fd, &write_flags);
		/*
		struct timeval timeout = {0,100};
		setsockopt(sock_fd,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(struct timeval));
		int tSet = setsockopt(sock_fd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));
		socklen_t len=sizeof(timeout);
		getsockopt(sock_fd,SOL_SOCKET,SO_RCVTIMEO,&timeout,&len);
		printf("setsockopt(%d),socklen_t(%d)!\r\n",tSet,len);
		KeepAlive实现，单位秒
		//下面代码要求有ACE,如果没有包含ACE,则请把用到的ACE函数改成linux相应的接口
		int keepAlive = 1;//设定KeepAlive
		int keepIdle = 5;//开始首次KeepAlive探测前的TCP空闭时间
		int keepInterval = 5;//两次KeepAlive探测间的时间间隔
		int keepCount = 3;//判定断开前的KeepAlive探测次数
		if(setsockopt(s,SOL_SOCKET,SO_KEEPALIVE,(void*)&keepAlive,sizeof(keepAlive)) == -1)
		{
			CLogger::createInstance()->Log(eTipMessage,"setsockopt SO_KEEPALIVE error!");
		}
		if(setsockopt(s,SOL_TCP,TCP_KEEPIDLE,(void *)&keepIdle,sizeof(keepIdle)) == -1)
		{
			CLogger::createInstance()->Log(eTipMessage,"setsockopt TCP_KEEPIDLE error!");
		}
		if(setsockopt(s,SOL_TCP,TCP_KEEPINTVL,(void *)&keepInterval,sizeof(keepInterval)) == -1)
		{
			CLogger::createInstance()->Log(eTipMessage,setsockopt TCP_KEEPINTVL error!");
		}
		if(setsockopt(s,SOL_TCP,TCP_KEEPCNT,(void *)&keepCount,sizeof(keepCount)) == -1)
		{
			CLogger::createInstance()->Log(eTipMessage,setsockopt TCP_KEEPCNT error!");
		}
		*/
		CLogger::createInstance()->Log(eTipMessage,
			"connect ok !, [%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		m_OnConnect = true;
		m_OnConnecting = false;
		return 1;
#endif
	}
	catch (...) {
#ifdef WIN32
		CLogger::createInstance()->Log(eSoftError,
			"ClientSocket::onConnect error: %d.[%s %s %d]", static_cast<int>(GetLastError())
			, __FILE__, __FUNCTION__, __LINE__);
#else
		CLogger::createInstance()->Log(eSoftError,
			"ClientSocket::onConnect error: %s. [%s %s %d]", strerror(errno)
			, __FILE__, __FUNCTION__, __LINE__);
#endif
		m_OnConnecting = false;
		return -2;
	}
}
 
void MySocketClient::disConnect()
{
	m_OnConnect = false;
 
	if (-1 != sock_fd) 
	{
		#ifdef WIN32
		closesocket(sock_fd);
		#else
		close(sock_fd);
		#endif
		sock_fd = -1;
	}
}
 
int MySocketClient::reSetSocket()
{
	disConnect();
	return onConnect();
}
 
int MySocketClient::Read(RDClient &bufs)
{
	try {
		if (m_OnConnect) 
		{
			char buf[256] = { 0 };
#ifdef WIN32		
			int re = recv(sock_fd, buf, 256, 0);
			if (re <= 0) 
			{
				int _error = GetLastError();
				if (_error != 10060 && 0 != _error)
				//if (_error != 10060) 
				{
					CLogger::createInstance()->Log(eReadError,
						"Read Datas Failed! ret(%d) error(%d)! [%s %s %d]"
						, re, _error
						, __FILE__, __FUNCTION__, __LINE__);
					disConnect();
				}
				else
				 {
					re = 0;
				}
			}
#else
			//int re = read(sock_fd, buf, 256);
			int re = recv(sock_fd, buf, 256, MSG_DONTWAIT);
			if (re <= 0)
			{
				if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
				{
					usleep(10);
					re = 0;
				}
				else
				{
					CLogger::createInstance()->Log(eReadError,
						"Read Data Failed! error(%d,%d,%s)! [%s %s %d]"
						, re, errno, strerror(errno)
						, __FILE__, __FUNCTION__, __LINE__);
					disConnect();
				}
				//static int index = 0;
				//printf("..%d..%d,%s\n",index++,errno,strerror(errno));
			}
#endif
			if (re > 0) 
			{
				/*
				for(int j=0; j<re; j++){
					printf("%02X ",buf[j]);
				}
				printf("\n");
				*/
				bufs.add((unsigned char*)buf, re);
				return bufs.len;
			}
			return re;
		}
		else 
		{
			printf("Read Data Failed!unconnect!");
			return -2;
		}
	}
	catch (...) 
	{
		disConnect();
#ifdef WIN32
		CLogger::createInstance()->Log(eSoftError,
			"Read Data Failed!unknown error: %d! [%s %s %d]", static_cast<int>(GetLastError())
			, __FILE__, __FUNCTION__, __LINE__);
#else
		CLogger::createInstance()->Log(eSoftError,
			"Read Data Failed!unknown error: %s! [%s %s %d]", strerror(errno)
			, __FILE__, __FUNCTION__, __LINE__);
#endif
 
		return -3;
	}
};
 
int MySocketClient::Read(char* buf, int size)//读入数据到缓存器中
{
	try {
		if (m_OnConnect) 
		{
#ifdef WIN32
			//int re = m_CSocket->Receive(buf, size);
			int re = recv(sock_fd, buf, size, 0);
			if (re <= 0) 
			{
				int _error = GetLastError();
				if (_error != 10060 && 0 != _error)
				//if (_error != 10060) 
				{
					CLogger::createInstance()->Log(eReadError,
						"Read Data Failed!ret(%d),error(%d)!  [%s %s %d]"
						, re, _error
						, __FILE__, __FUNCTION__, __LINE__);
					disConnect();
				}
				else 
				{
					re = 0;
				}
			}
#else
			//int re = read(sock_fd, buf, size);
			int re = recv(sock_fd, buf, size, MSG_DONTWAIT);
			if (re <= 0)
			{
				if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
				{
					usleep(10);
					re = 0;
				}
				else
				{
					CLogger::createInstance()->Log(eReadError,
						"Read Data Failed! error(%d,%d,%s)! [%s %s %d]"
						,re , errno, strerror(errno)
						, __FILE__, __FUNCTION__, __LINE__);
					disConnect();
				}
			}
#endif
			return re;
		}
		else
		 {
			printf("Read Data Failed! unconnect! \n");
			return -2;
		}
	}
	catch (...) 
	{
		disConnect();
#ifdef WIN32
		CLogger::createInstance()->Log(eSoftError,
			"Read Data Failed!unknown error: %d! [%s %s %d]", static_cast<int>(GetLastError())
			, __FILE__, __FUNCTION__, __LINE__);
#else
		CLogger::createInstance()->Log(eSoftError,
			"Read Data Failed!unknown error: %s! [%s %s %d]", strerror(errno)
			, __FILE__, __FUNCTION__, __LINE__);
#endif
 
		return -3;
	}
}
 
int MySocketClient::Write(const char* buf, int size)//给服务端发送数据
{
	try {
		if (m_OnConnect) 
		{
#ifdef WIN32
			int re = send(sock_fd, buf, size, 0);
			if (re <= 0) 
			{
				int _error = GetLastError();
				if (_error != 10060 && 0 != _error)
				{
					CLogger::createInstance()->Log(eWriteError,
						"Write Data Failed! ret(%d)! error(%d)! [%s %s %d]"
						, re, _error
						, __FILE__, __FUNCTION__, __LINE__);
					disConnect();
				}
			}
#else
			//int re = write(sock_fd, buf, size);
			int re = send(sock_fd, buf, size, MSG_DONTWAIT);
			if (re <= 0) 
			{
				if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
				{
					usleep(10);
					re = 0;
				}
				else
				{
					CLogger::createInstance()->Log(eWriteError,
						"Write Data Failed! error(%d,%d,%s)! [%s %s %d]"
						, re, errno, strerror(errno)
						, __FILE__, __FUNCTION__, __LINE__);
					disConnect();
				}
			}
#endif
			return re;
		}
		else {
			//CLogger::createInstance()->Log(eWriteError,
			//	"Write Data Failed! unconnect! [%s %s %d]\r\n"
			//	, __FILE__, __FUNCTION__, __LINE__);
			printf("Write Data Failed! unconnect!");
			if (!m_OnConnecting)
			{
				reSetSocket();
			}
			return -2;
		}
	}
	catch (...) 
	{
		disConnect();
#ifdef WIN32
		CLogger::createInstance()->Log(eSoftError,
			"Write Data Failed! unknown error: %d! [%s %s %d]", static_cast<int>(GetLastError())
			, __FILE__, __FUNCTION__, __LINE__);
#else
		CLogger::createInstance()->Log(eSoftError,
			"Write Data Failed! unknown error: %d! [%s %s %d]", strerror(errno)
			, __FILE__, __FUNCTION__, __LINE__);
#endif
		return -3;
	}
}