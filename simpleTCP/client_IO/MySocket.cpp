#include "MySocket.h"
 
#include "MySocketClient.h"
#include "MySocketWD.h"
#include "MySocketRD.h"
#include "Log.h"
 
MySocket::MySocket(int _tranid, NetArg _netarg)
	: tranid(_tranid)
	, netarg(_netarg)
{
	try {//防止构造时异常出现内存泄漏
		//TCP/IP客户端,连接监控服务或其他平台
		my_PrivateData = new MySocketClient(netarg.ipStr, netarg.port);
		if (my_PrivateData->onConnect() <= 0)
		{
			CLogger::createInstance()->Log(eSoftError,
				"connect server[%s,%d] error,please check it,[%s %s %d]!"
				, netarg.ipStr.c_str(), netarg.port
				, __FILE__, __FUNCTION__, __LINE__);
		}
		//数据协议编码解码 序列化及反序列化
		//数据发送线程
		m_MySocketWD = new MySocketWD();
		m_MySocketWD->setPrivateDataPtr(my_PrivateData, netarg.type);
		m_MySocketWD->start();
		//数据接收线程
		m_MySocketRD = new MySocketRD();
		m_MySocketRD->setPrivateDataPtr(my_PrivateData, netarg.type);
		m_MySocketRD->start();
	}
	catch (...) 
	{
		delete m_MySocketRD;
		m_MySocketRD = NULL;
		delete m_MySocketWD;
		m_MySocketWD = NULL;
		delete my_PrivateData;
		my_PrivateData = NULL;
		CLogger::createInstance()->Log(eSoftError,
			"MySocket init error,please check it,[%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
	}
}
 
MySocket::~MySocket(void)
{
	if(NULL!= m_MySocketRD)
	{
		delete m_MySocketRD;
		m_MySocketRD = NULL;
	}
	if (NULL != m_MySocketWD) 
	{
		delete m_MySocketWD;
		m_MySocketWD = NULL;
	}
	if (NULL != my_PrivateData) 
	{
		delete my_PrivateData;
		my_PrivateData = NULL;
	}
};
 
 
int MySocket::Write(const char* buf, int size)
{
	if (size <= 0)
	{
		return -1;
	}
	if (NULL != m_MySocketWD && NULL != buf) 
	{
		return m_MySocketWD->add_data(buf, size);
	}
	else 
	{
		return -1;
	}
};