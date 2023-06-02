#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _MYFUNC_H_
#define _MYFUNC_H_
/*
public function
*/
#include <string>
#include <vector>
 
namespace PFunc
{
	//字符串分割
	bool string_divide(std::vector<std::string> &_strlist, const std::string src, const std::string div);
	//hex to ascii
	int string2bytes(const char* pSrc, unsigned char* pDst, int nSrcLength);
	//ascii to hex
	int bytes2string(const unsigned char* pSrc, char* pDst, int nSrcLength);
	//frame code
	int code(const unsigned char *buff, const int len, unsigned char *outbuf);
	//frame uncode
	int uncode(const unsigned char *buff, int len, unsigned char *outbuf);
	//
	bool ipCheck(std::string ip_str);
	long ipToInt(std::string ip_str);
	std::string intToIp(long ip_int);
	//crc
	unsigned int  crc16(unsigned char *ptr, unsigned int len);
	//年-月-日 时:分:秒
	std::string getCurrentTime();
};
 
#endif