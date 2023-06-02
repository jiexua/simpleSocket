#include "MySocketRD.h"
 
#include "MySocketPrivate.h"
#include "myFunc.h"
#include "Log.h"
 
MySocketRD::MySocketRD( MySocketPrivate* myPDataPrt_, int netType_)
	: running(true)
	, netType(netType_)
	, myPDataPrt(myPDataPrt_)
{
 
}
 
MySocketRD::~MySocketRD(void)
{
	running = false;
};
 
int MySocketRD::Run()
{
	if (NULL == myPDataPrt ) 
	{
		CLogger::createInstance()->Log(eSoftError,
			"MySocketRD start fail for myPDataPrt is NULL,[%s %s %d]!"
			, __FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
	std::map<KeyObj_Client, RDClient> bufs;
	RDS rdataGx;
	while (running)
	{
		int re = myPDataPrt->Read(bufs);
		if (re <= 0) 
		{
#ifdef _DEBUG
			printf_s("Read Data Failed or NULL\n!");
#else
			;
#endif
		}else {
			switch (netType)
			{
				case 1:
				{
					try {
						std::map<KeyObj_Client, RDClient>::iterator it = bufs.begin();
						while (it != bufs.end())
						{
							if (it->second.len > 0) 
							{
								RDS rdata(TCP_Data(it->second.Buf, it->second.len), it->first.m_ipStr);
								ReadData.add(rdata);
							}
							it++;
						}
						bufs.clear();
					}
					catch (const std::exception& e)
					{
						CLogger::createInstance()->Log(eSoftError,
							"Exception for Reading and Parsing Error[%s],NetType(%d), [%s %s %d]"
							, e.what()
							, netType
							, __FILE__, __FUNCTION__, __LINE__);
					}
					catch (...) {
						CLogger::createInstance()->Log(eSoftError,
							"Exception for Reading and Parsing Error,NetType(%d),[%s %s %d]!"
							, netType
							, __FILE__, __FUNCTION__, __LINE__);
					}
					while (ReadData.getFirst(rdataGx))
					{
						this->AddFrame(rdataGx.flag, rdataGx.data.Buf, rdataGx.data.len);
						ReadData.removeFirst();
					}
					break;
				}
				case 2:
				{
					try {
						std::map<KeyObj_Client, RDClient>::iterator it = bufs.begin();
						while (it != bufs.end())
						{
							unsigned char * buff = it->second.Buf;
							int start_frame = 0;
							unsigned char ctype = 0;
							for (int i = 0; i < it->second.len; i++)
							{
								//printf_s("%02X ",buff[i]);
								if (buff[i] > 0xf0) {
									if (buff[i] == 0xff) 
									{
										if (ctype) 
										{
											ctype = 0;
											int re_len = i - start_frame + 1;
											// RDS rdata(TCP_Data(buff + start_frame, i - start_frame + 1), it->first.m_ipStr);
											unsigned char * pBuf = new unsigned char[re_len];
											//
											int nLen = PFunc::uncode(buff + start_frame, re_len, pBuf);
											RDS rdata(TCP_Data(pBuf, nLen), it->first.m_ipStr);
											// printf("rev01:%s\r\n",(char*)pBuf);
											printf("rev01:%d\r\n",nLen);
											ReadData.add(rdata);
											start_frame = i + 1;
											delete[] pBuf;
											pBuf = NULL;
										}
									}
									else {
										ctype = buff[i];
										start_frame = i;
									}
								}
							}
							buff = NULL;
							if (start_frame < it->second.len)
							{
								RDClient _newrd(it->second.Buf + start_frame, it->second.len - start_frame);
								it->second = _newrd;
								it++;
							}
							else {
								#ifdef WIN32
								it = bufs.erase(it);
								#else
								std::map<KeyObj_Client, RDClient>::iterator ittemp = it++;
								bufs.erase(ittemp);
								#endif
							}
						}
					}
					catch (const std::exception& e)
					{
						CLogger::createInstance()->Log(eSoftError,
							"Data Deserialize false[%s],[%s %s %d]"
							, e.what()
							, __FILE__, __FUNCTION__, __LINE__);
					}
					catch (...) {
						CLogger::createInstance()->Log(eSoftError,
							"Data Deserialize false,[%s %s %d]!"
							, __FILE__, __FUNCTION__, __LINE__);
					}
					while (ReadData.getFirst(rdataGx))
					{
						this->AddFrame(rdataGx.flag, rdataGx.data.Buf, rdataGx.data.len);
						ReadData.removeFirst();
					}
					break;
				}
				default:
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
 
int MySocketRD::AddFrame(const std::string link, const unsigned char *buf, int len)
{
	if(NULL == buf)
		return 0;
	printf("rev:%s\r\n",(char*)buf);
	// TcpSocket ts;
	// memcpy(&ts,buf,len);
	// printf("rev:%u,%d,%0.2f,%s\r\n",ts.type,ts.len,ts.val,ts.desc);
	return 0;
};