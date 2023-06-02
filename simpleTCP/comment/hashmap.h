#pragma once
#ifndef HASH_MAP_H
#define HASH_MAP_H
/*
*自定义map容器的Key
*/
#include <map>
#include <iostream> 
//
class KeyObj_Client
{
public:
	KeyObj_Client(std::string  _ipStr, int _port);
	//
	static long cmp_Key(const KeyObj_Client &obj1, const KeyObj_Client &obj2);
 
	std::string m_ipStr;
	int	m_port;
	int linkFlag;
	long	m_ip;	//网络地址整型表述
private:
};
inline bool operator==(const KeyObj_Client& obj1, const KeyObj_Client& obj2) { return KeyObj_Client::cmp_Key(obj1, obj2) == 0; }
inline bool operator!=(const KeyObj_Client& obj1, const KeyObj_Client& obj2) { return KeyObj_Client::cmp_Key(obj1, obj2) != 0; }
inline bool operator>=(const KeyObj_Client& obj1, const KeyObj_Client& obj2) { return KeyObj_Client::cmp_Key(obj1, obj2) >= 0; }
inline bool operator<=(const KeyObj_Client& obj1, const KeyObj_Client& obj2) { return KeyObj_Client::cmp_Key(obj1, obj2) <= 0; }
inline bool operator>(const KeyObj_Client& obj1, const KeyObj_Client& obj2) { return KeyObj_Client::cmp_Key(obj1, obj2) > 0; }
inline bool operator<(const KeyObj_Client& obj1, const KeyObj_Client& obj2) { return KeyObj_Client::cmp_Key(obj1, obj2) < 0; }
 
#endif //HASH_MAP_H