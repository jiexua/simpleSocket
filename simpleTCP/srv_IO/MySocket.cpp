#include "MySocket.h"
 
#include "MySocketPrivate.h"
#include "MySocketSrv.h"
#include "MySocketRD.h"
#include "MySocketWD.h"
#include "Log.h"

 
MySocket::MySocket(unsigned int port,int netType_)
{
	try {
		my_PrivateData = new MySocketPrivate(port);
		if (my_PrivateData->onConnect() > 0)
		{
			my_SocketSrv = new MySocketSrv();
			my_SocketSrv->setPDataPtr(my_PrivateData);
			my_SocketSrv->start();
 
			m_MySocketRD = new MySocketRD(my_PrivateData,netType_);
			m_MySocketRD->start();
 
			m_MySocketWD = new MySocketWD( my_PrivateData,netType_);
			m_MySocketWD->start();
 
		}
		else {
			my_SocketSrv = NULL;
			m_MySocketRD = NULL;
			m_MySocketWD = NULL;
			CLogger::createInstance()->Log(eSoftError,
				"listen port(%u) error, [%s %s %d]"
				, port
				, __FILE__, __FUNCTION__, __LINE__);
		}
	}
	catch (...) {
		delete my_SocketSrv;
		my_SocketSrv = NULL;
		delete m_MySocketRD;
		m_MySocketRD = NULL;
		delete m_MySocketWD;
		m_MySocketWD = NULL;
		delete my_PrivateData;
		my_PrivateData = NULL;
		CLogger::createInstance()->Log(eSoftError,
			"MySocketGx init error, [%s %s %d]"
			, __FILE__, __FUNCTION__, __LINE__);
	}
};
 
MySocket::~MySocket(void)
{
	if (NULL != my_SocketSrv) 
	{
		delete my_SocketSrv;
		my_SocketSrv = NULL;
	}
	if (NULL != m_MySocketRD) 
	{
		delete m_MySocketRD;
		m_MySocketRD = NULL;
	}
	if (NULL != m_MySocketWD) 
	{
		delete m_MySocketWD;
		m_MySocketWD = NULL;
	}
	if(NULL!=my_PrivateData)
	{
		delete my_PrivateData;
		my_PrivateData = NULL;
	}
};
 
int MySocket::Write(const char* buf, int size)
{
	if (NULL != m_MySocketWD&&NULL!=buf) 
	{
		return m_MySocketWD->AddData(buf, size);
	}
	else {
		return -1;
	}
}