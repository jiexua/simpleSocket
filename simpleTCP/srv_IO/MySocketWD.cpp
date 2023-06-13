#include "MySocketWD.h"
 
#include "MySocketPrivate.h"
#include "myFunc.h"
#include "Log.h"
 
#include <set>
#ifdef __linux__
#include <stdexcept>
#endif
 
MySocketWD::MySocketWD( MySocketPrivate* myPDataPrt_,int netType_)
	: running(true)
	, netType(netType_)
	, myPDataPrt(myPDataPrt_)
{
}
 
MySocketWD::~MySocketWD(void)
{
	running = false;
}
 
int MySocketWD::Run()
{
	if (NULL == myPDataPrt) 
	{
		CLogger::createInstance()->Log(eSoftError,
			"MySocketWD start fail for myPDataPrt is NULL,[%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
	while(running)
	{
		try {
			unsigned long long _ipInt = 0;
			unsigned char buf[512] = { 0 };
			int len = this->getBuffer(_ipInt, buf);
 
			if (len > 0) 
			{
				int ret = -1;
				switch (netType)
				{
					case 1:
					{
						ret = myPDataPrt->Write(_ipInt, (const char*)buf, len);
						break;
					}
					case 2:
					{
						// printf("send data: %s\r\n",buf);
						unsigned char* _buf = new unsigned char[2 * len + 1];
						memset(_buf, 0, 2 * len + 1);
						len = PFunc::code(buf, len, _buf);//序列化处理
						// printf("send data: %d\r\n",len);
						ret = myPDataPrt->Write(_ipInt, (const char*)_buf, len);
						delete[] _buf;
						_buf = NULL;
						break;
					}
					default:
					{
						char warBuf[128] = { 0 };
						sprintf(warBuf, "MySocketWD::Run For Unkown NetType(%02X)", netType);
						#ifdef WIN32
						throw std::exception(warBuf);
						#else
						throw std::domain_error(warBuf);
						#endif
						break;
					}
				}
				
				if (ret <=0) 
				{
					//printf("send data: %d, buf %d\n",len,ret);
					CLogger::createInstance()->Log(eTipMessage,
						"MySocketWD send data(%s,%d) fail. [%s %s %d]"
						,buf,len
						, __FILE__, __FUNCTION__, __LINE__);
				}
				//else{
				//	printf("send data: %d, and real send %d\n",len,ret);
				//}
			}
		}
		catch (const std::exception& e)
		{
			CLogger::createInstance()->Log(eSoftError,
				"MySocketWD Run for data writing exception[%s],[%s %s %d]"
				, e.what()
				, __FILE__, __FUNCTION__, __LINE__);
		}
		catch (...) {
			CLogger::createInstance()->Log(eSoftError,
				"MySocketWD Run for data writing exception, [%s %s %d]!"
				, __FILE__, __FUNCTION__, __LINE__);
		}
#ifdef WIN32
		Sleep(10);
#else
		usleep(10000);
#endif
	}
	return 0;
};
 
int MySocketWD::AddData(const char* buf, int len)//给所有已连接客户端的写入缓存器加入数据
{
	if(len>0&&NULL!=buf){
		if(len>=512){
			printf("buf len is >=512!\r\n");
		}else{
			std::set<long> ipintlist;
			if(!myPDataPrt->get_ipInt_list(ipintlist))
			{
				return 0;
			}
			std::set<long>::iterator it = ipintlist.begin();
			while (it != ipintlist.end())
			{
				/* code */
				WDS wdata(*it,TCP_Data((unsigned char*)buf, len));
				WriteData.add(wdata);
				it++;
			}
			return len;
		}
	}
	return 0;
}
 
int MySocketWD::getBuffer(unsigned long long &_ipInt, unsigned char* _buf)//从缓存器中取数据
{
	if(NULL == _buf)
		return 0;
	int ret = 0;
	WDS wdata;
 
	if(WriteData.getFirst(wdata))
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
			_ipInt = wdata.ipInt;
			memcpy(_buf,wdata.data.Buf,wdata.data.len);
			ret = wdata.data.len;
		}
		catch (const std::exception& e)
		{
			CLogger::createInstance()->Log(eSoftError,
				"write item info to socket failed! have error[%s]. [%s %s %d]"
				, e.what()
				, __FILE__, __FUNCTION__, __LINE__);
			ret = -1;
		}
		catch (...) {
			//printf_s("write item info to socket failed! have error. \r\n");
			CLogger::createInstance()->Log(eSoftError,
				"write item info to socket failed! have error. [%s %s %d]"
				, __FILE__, __FUNCTION__, __LINE__);
			ret = -2;
		}
	}
	return ret;
}