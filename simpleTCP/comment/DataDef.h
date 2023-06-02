#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _DATA_DEF_H_
#define _DATA_DEF_H_
 
#include <string>
#ifdef __linux__
#include <string.h>
#include <stdio.h>
#endif
 
struct NetArg
{
	NetArg() 
		: ipStr("127.0.0.1"),port(70001),type(1)
	{
	};
	std::string ipStr;	//
	int port;			//
	int type;			//Protocol
};
 
#define RDCSIZE 1024
struct RDClient
{
	RDClient() 
		: len(0)
	{
		memset(Buf,0,RDCSIZE);
	};
	RDClient(unsigned char *buf,int nlen) 
	{
		memset(Buf,0,RDCSIZE);
		memcpy(Buf,buf,nlen);
		len = nlen;
	};
	~RDClient()
	{
	};
	RDClient& operator=(const RDClient &rval)
	{
		if (this!=&rval)
		{
			memset(Buf,0,RDCSIZE);
			memcpy(Buf,rval.Buf,rval.len);
			len = rval.len;		
		}
		return *this;
	};
	int add(unsigned char *buf,int nlen)
	{
		try{
		memset(Buf+len,0,RDCSIZE-len);
		memcpy(Buf+len,buf,nlen);
		len += nlen;
		}catch(...)
		{
			printf("RDClient::add error \r\n");
		}
		return len;
	};
	unsigned char Buf[RDCSIZE];
	int len;
};
 
typedef struct TCP_Data_Model
{
	unsigned type;
	int len;
	float val;
	char desc[32];
}TcpSocket,*PTcpSocket;
 
 
struct TCP_Data
{
	TCP_Data() : len(0)
	{
		memset(Buf, 0, 512);
	};
	TCP_Data(unsigned char *buf, int nlen)
	{
		memset(Buf, 0, 512);
		memcpy(Buf, buf, nlen);
		len = nlen;
	};
	TCP_Data& operator=(const TCP_Data &rval)
	{
		if (this != &rval) {
			memset(Buf, 0, 512);
			if (rval.len < 512) {
				memcpy(Buf, rval.Buf, rval.len);
				len = rval.len;
			}
			else {
				memcpy(Buf, rval.Buf, 512);
				len = 512;
			}
		}
		return *this;
	};
	unsigned char Buf[512];
	int len;
};
 
 
struct RDS
{
	RDS() : data(),flag("")
	{
 
	};
	RDS(TCP_Data _data,std::string _f = "")
		: data(_data),flag(_f)
	{
	};
	RDS& operator=(const RDS &rval)
	{
		if (this == &rval) {
			return *this;
		}
		data = rval.data;
		flag = rval.flag;
		return *this;
	};
	TCP_Data data;
	std::string flag;
};
 
struct WDS
{
	WDS() : ipInt(0), data()
	{
 
	};
	WDS(unsigned long long _ipInt,TCP_Data _data)
		: ipInt(_ipInt), data(_data)
	{
	};
	WDS& operator=(const WDS &rval)
	{
		if (this == &rval) {
			return *this;
		}
		ipInt = rval.ipInt;
		data = rval.data;
		return *this;
	};
	unsigned long long ipInt;
	TCP_Data data;
};
 
#endif