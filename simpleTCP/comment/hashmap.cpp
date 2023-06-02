#include "hashmap.h"
 
#ifdef WIN32
#include <Winsock2.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
 
#include "myFunc.h"
#include "Log.h"
 
 
KeyObj_Client::KeyObj_Client(std::string  _ipStr, int _port)
	: m_ipStr(_ipStr), m_port(_port), linkFlag(0)
{
	m_ip = PFunc::ipToInt(_ipStr);
};
//
long KeyObj_Client::cmp_Key(const KeyObj_Client &obj1, const KeyObj_Client &obj2)
{
	long diff = obj1.m_ip - obj2.m_ip;
	if (diff != 0) 		return diff;
	diff = obj1.m_port - obj2.m_port;
	if (diff != 0) 		return diff;
	return 0;
};