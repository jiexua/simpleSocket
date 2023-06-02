#include "MySocketWD.h"
 
#include "MySocketClient.h"
#include "myFunc.h"
#include "Log.h"
 
#ifdef __linux__
#include <stdexcept>
#endif
 
#define heartBeat_interval 10
 
MySocketWD::MySocketWD(void)
	: running(true)
	, netType(1)
	, heartBeatWrite(static_cast<unsigned int>(time(NULL)))
	, myPDataPrt(NULL)
{
}
 
MySocketWD::~MySocketWD(void)
{
	running = false;
}
 
void MySocketWD::setPrivateDataPtr(MySocketClient *myPData, int _netType)
{
	netType = _netType;
	if (NULL != myPData)
	{
		myPDataPrt = myPData;
	}
}
 
int MySocketWD::Run()
{
	if (NULL == myPDataPrt ) 
	{
		CLogger::createInstance()->Log(eSoftError,
			"MySocketWD start fail for myPDataPrt or m_MonitorData is NULL"
			",[%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
	while(running)
	{
		if (!myPDataPrt->isConnect())
		{
			myPDataPrt->reSetSocket();//read or write thread do it
			if (!myPDataPrt->isConnect())
			{
#ifdef WIN32
				Sleep(1000);
#else
				usleep(1000000);
#endif
			}
		}
		else {
			//由读取进程去重新建立链接,写入线程只判定链接状态,进行数据写入
			unsigned char buf[512] = { 0 };
			int len = this->getBuffer(buf);
			if (len <= 0 && (heartBeatWrite+heartBeat_interval)<static_cast<unsigned int>(time(NULL))) 
			{
				len = this->getHeartBeatBuffer(buf);
			}
			if (len > 0) {
				switch (netType)
				{
				case 1:
				{
					int ret = myPDataPrt->Write((const char*)buf, len);
					if (ret != len) {
						//printf("send data: %d, buf %d\n",len,ret);
						CLogger::createInstance()->Log(eTipMessage,
							"send point data: %d, buf %d. [%s %s %d]"
							, len, ret
							, __FILE__, __FUNCTION__, __LINE__);
					}
					else {
						heartBeatWrite = static_cast<unsigned int>(time(NULL));
					}
				}
				break;
				case 2:
				{
					int cacheLen = 2 * len + 1;
					unsigned char* _buf = new unsigned char[cacheLen];
					memset(_buf, 0, cacheLen);
					int nLen = PFunc::code(buf, len, _buf);//序列化处理
					int ret = myPDataPrt->Write((const char*)_buf, nLen);
					if (ret != nLen) {
						//printf("send data: %d, buf %d\n",len,ret);
						CLogger::createInstance()->Log(eTipMessage,
							"send point data: %d, buf %d. [%s %s %d]"
							, nLen, ret
							, __FILE__, __FUNCTION__, __LINE__);
					}
					else {
						heartBeatWrite = static_cast<unsigned int>(time(NULL));
					}
					delete[] _buf;
					_buf = NULL;
				}
				break;
				default:
					CLogger::createInstance()->Log(eConfigError,
						"Exception for Write data and unkown NetType(%d),[%s %s %d]!"
						, netType
						, __FILE__, __FUNCTION__, __LINE__);
					break;
				}
 
			}
		}
		#ifdef WIN32
		Sleep(1);
		#else
		usleep(1000);
		#endif
	}
	return 0;
}
 
int MySocketWD::add_data(const char* buf, int len)
{
	if(len>0&&NULL!=buf){
		if(len>=512){
			printf("buf len is >=512!\r\n");
		}
		else
		{
			TCP_Data rdata((unsigned char*)buf, len);
			WriteData.add(rdata);
			return len;
		}
	}
	return 0;
}
 
int MySocketWD::getBuffer(unsigned char * _buf)
{
	int ret = 0;
	TCP_Data data;
	if(WriteData.getFirst(data))
	{
		try{
			if (!WriteData.removeFirst())
			{
				#ifdef WIN32
				throw std::exception("removeFirst WData failed!");
				#else
				throw std::logic_error("removeFirst WData failed!");
				#endif
			}
			memcpy(_buf,data.Buf,data.len);
			ret = data.len;
			printf("send:%s\r\n",_buf);
		}
		catch (const std::exception& e)
		{
			CLogger::createInstance()->Log(eSoftError,
				"write item info to socket failed! have error[%s]. [%s %s %d]"
				, e.what()
				, __FILE__, __FUNCTION__, __LINE__);
			ret = -1;
		}
		catch (...) 
		{
			//printf_s("write item info to socket failed! have error. \r\n");
			CLogger::createInstance()->Log(eSoftError,
				"write item info to socket failed! have error. [%s %s %d]"
				, __FILE__, __FUNCTION__, __LINE__);
			ret = -2;
		}
	}
	return ret;
};
 
int MySocketWD::getHeartBeatBuffer(unsigned char * buf)
{
	if (NULL != buf) 
	{
		int idx = 0;
		std::string cur_time_str = PFunc::getCurrentTime();
		char buf_[64]={0};
		sprintf(buf_,"HeartBeat:%s",cur_time_str.c_str());
		idx = (int)strlen(buf_);
		memcpy(buf,buf_,idx);
		return idx;
	}
	else 
	{
		return 0;
	}
};