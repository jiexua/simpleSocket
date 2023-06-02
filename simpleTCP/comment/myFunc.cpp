#include "myFunc.h"
 
#include <stdlib.h>
#ifdef WIN32
#include <Winsock2.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#endif
#include <time.h>
#include "Log.h"
 
bool PFunc::string_divide(std::vector<std::string> &_strlist, const std::string src, const std::string div)
{
	std::string _src = src;
	std::string::size_type _pos = _src.find(div);
	while (std::string::npos != _pos)
	{
		std::string _buf = "";
		_buf = _src.substr(0, _pos);
		_strlist.push_back(_buf);
		_src = _src.erase(0, _pos + div.size());
		_pos = _src.find(div.c_str());
	}
	if (!_src.empty()) 
	{
		_strlist.push_back(_src);
	}
	return true;
};
 
int PFunc::string2bytes(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	for (int i = 0; i < nSrcLength; i += 2)
	{
		if (*pSrc >= '0' && *pSrc <= '9')
			*pDst = (*pSrc - '0') << 4;
		else
			*pDst = (*pSrc - 'A' + 10) << 4;
		pSrc++;
		// 输出低4位
		if (*pSrc >= '0' && *pSrc <= '9')
			*pDst |= *pSrc - '0';
		else
			*pDst |= *pSrc - 'A' + 10;
		pSrc++;
		pDst++;
	}
	return (nSrcLength / 2);
};
 
 
int PFunc::bytes2string(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	const char tab[] = "0123456789ABCDEF";    // 0x0-0xf的字符查找表
	for (int i = 0; i < nSrcLength; i++)
	{
		*pDst++ = tab[*pSrc >> 4];
		*pDst++ = tab[*pSrc & 0x0f];
		pSrc++;
	}
	*pDst = '\0';
	return nSrcLength * 2;
};
 
int PFunc::code(const unsigned char *buff, const int len, unsigned char *outbuf)
{
	char ch = 0;
	int nLen = 0;
	unsigned char * buf = (unsigned char *)buff;
	*outbuf++ = 0XF1;//头字节
	nLen+=1;
	for (int i = 0; i < len; i++, nLen++)
	{
		ch = buf[i];
		if ((buf[i] | 0x0f) == 0xff && i > 0 && i < (len - 1))
		{
			*outbuf++ = 0xf0 & buf[i];
			*outbuf++ = 0x0f & buf[i];
			nLen += 1;
		}
		else {
			*outbuf++ = ch;
		}
	}
	*outbuf++ = 0XFF;//末字节
	nLen+=1;
	buf = NULL;
	return nLen;
}
 
int PFunc::uncode(const unsigned char *buff, int len, unsigned char *outbuf)
{
	char ch = 0;
	int nLen = 0;
	unsigned char * buf = (unsigned char *)buff;
	//头、末尾字节判断
	if(len<=2&&0XF1!=buf[0]&&0XFF!=buf[len-1]){
		printf("uncode func, start bit or end bit Error!\r\n");
		return 0;
	}
	for (int i = 1; i < (len-1); i++, nLen++)
	{
		ch = buf[i];
		if (buf[i] == 0xf0)
		{
#ifdef _DEBUG
			if (i > len - 2)
				printf("Error!\r\n");
			if (buf[i + 1] > 0x0f)
				printf("Error!\r\n");
#endif
			ch = 0xf0 | buf[++i];
		}
		*outbuf++ = ch;
	}
	buf = NULL;
	return nLen;
}
 
bool PFunc::ipCheck(std::string ip_str)
{
	if (INADDR_NONE != inet_addr(ip_str.c_str())) 
	{
		return true;
	}
	return false;
};
 
long PFunc::ipToInt(std::string ip_str)
{
	if (INADDR_NONE != inet_addr(ip_str.c_str())) 
	{
		return ntohl(inet_addr(ip_str.c_str()));
	}
	else {
		CLogger::createInstance()->Log(eConfigError
			, "ip format [%s] error: %s %s %d,please check the file format and code!"
			, ip_str.c_str(), __FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
};
std::string PFunc::intToIp(long ip_int)
{
	char ip[64] = { 0 };
#ifdef WIN32
	strcpy_s(ip, inet_ntoa(*(in_addr*)&ip_int));
#else
	strcpy(ip, inet_ntoa(*(in_addr*)&ip_int));
#endif
	return std::string(ip);
};
 
//CRC校验
unsigned int  PFunc::crc16(unsigned char *ptr, unsigned int len)
{
	unsigned int wcrc = 0XFFFF;//预置16位crc寄存器，初值全部为1
	unsigned char temp;//定义中间变量
	unsigned int i = 0, j = 0;//定义计数
 
	for (i = 0; i < len; i++)//循环计算每个数据
	{
		temp = *ptr & 0X00FF;//将八位数据与crc寄存器亦或
		ptr++;//指针地址增加，指向下个数据
		wcrc ^= temp;//将数据存入crc寄存器
		for (j = 0; j < 8; j++)//循环计算数据的
		{
			if (wcrc & 0X0001)//判断右移出的是不是1，如果是1则与多项式进行异或。
			{
				wcrc >>= 1;//先将数据右移一位
				wcrc ^= 0XA001;//与上面的多项式进行异或
			}
			else//如果不是1，则直接移出
			{
				wcrc >>= 1;//直接移出
			}
		}
	}
	temp = wcrc;//crc的值
	return wcrc;
};
 
std::string PFunc::getCurrentTime()
{
	time_t _t = time(NULL);
	struct tm _tt;
#ifdef WIN32
	localtime_s(&_tt, &_t);
#else
	localtime_r(&_t, &_tt);
#endif
	_tt.tm_year += 1900;
	_tt.tm_mon += 1;
	char buf[32] = { 0 };
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d"
		, _tt.tm_year, _tt.tm_mon, _tt.tm_mday, _tt.tm_hour, _tt.tm_min, _tt.tm_sec);
	return std::string(buf);
}