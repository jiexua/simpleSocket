#include "MySocketRD.h"
 
#include "MySocketClient.h"
#include "myFunc.h"
#include "Log.h"
 
MySocketRD::MySocketRD(void)
	: running(true)
	, netType(1)
	, myPDataPrt(NULL)
{
}
 
MySocketRD::~MySocketRD(void)
{
	running = false;
}
 
void MySocketRD::setPrivateDataPtr(MySocketClient *myPData, int _netType)
{
	netType = _netType;
	if (NULL != myPData)
	{
		myPDataPrt = myPData;
	}
}
 
int MySocketRD::Run()
{
	if (NULL == myPDataPrt )
	{
		CLogger::createInstance()->Log(eSoftError,
			"MySocketRD start fail for myPDataPrt is NULL"
			",[%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
	RDClient rdc_data;
	TCP_Data rddata;
	while (running)
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
		else 
		{
			//读取帧数据
			switch (netType)
			{
			case 1:
			{
				//直接读取,不用做分帧处理,ACSII字段
				char buf[256] = { 0 };
				int len = myPDataPrt->Read(buf, 256);
				if (len > 0) 
				{
					TCP_Data rdata((unsigned char*)buf, len);
					ReadData.add(rdata);
				}
				//数据帧解析
				if (ReadData.getFirst(rddata))
				{
					this->AddFrame(rddata.Buf, rddata.len);
					ReadData.removeFirst();
				}
			}
			break;
			case 2:
			{
				//数据有特定帧头和结尾,做分帧处理
				int ret = myPDataPrt->Read(rdc_data);
				if (ret > 0)
				{
					//printf("read(%d) from pcs_server\n",ret);
					unsigned char * buff = rdc_data.Buf;
					int frame_start = 0;
					unsigned char ctype = 0;
					for (int i = 0; i < rdc_data.len; ++i)
					{
						//printf("%02X ",buff[i]);
						if (buff[i] > 0xf0) 
						{
							if (buff[i] == 0xff) 
							{
								if (ctype) 
								{
									ctype = 0;
									// TCP_Data rdata(buff + frame_start, i - frame_start + 1);
									unsigned char * pBuf = new unsigned char[i - frame_start + 1];
									int nLen = PFunc::uncode(buff + frame_start, i - frame_start + 1, pBuf);//反序列化处理
									TCP_Data rdata(pBuf, nLen);
									ReadData.add(rdata);
									frame_start = i + 1;
									delete[] pBuf;
									pBuf = NULL;
								}
							}
							else 
							{
								ctype = buff[i];
								frame_start = i;
							}
						}
					}
					buff = NULL;
					if (frame_start < rdc_data.len)
					{
						RDClient _newrd(rdc_data.Buf + frame_start, rdc_data.len - frame_start);
						rdc_data = _newrd;
					}
					else 
					{
						rdc_data.len = 0;
					}
				}
 
				//数据帧解析
				while (ReadData.getFirst(rddata))
				{
					this->AddFrame(rddata.Buf, rddata.len);
					ReadData.removeFirst();
				}
			}
			break;
			default:
				CLogger::createInstance()->Log(eSoftError,
					"Exception for Reading and Parsing is undef NetType(%d),[%s %s %d]!"
					, netType
					, __FILE__, __FUNCTION__, __LINE__);
				break;
			}
		}
#ifdef WIN32
		Sleep(10);
#else
		usleep(10000);
#endif
	}
	return 0;
};
 
int MySocketRD::AddFrame(const unsigned char *buf, int len)
{
	if(NULL==buf)
		return 0;
	printf("rev:%s\r\n",(char*)buf);
	// TcpSocket ts;
	// memcpy(&ts,buf,len);
	// printf("rev:%u,%d,%0.2f,%s\r\n",ts.type,ts.len,ts.val,ts.desc);
	return 0;
};