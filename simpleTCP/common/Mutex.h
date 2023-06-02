#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef PYMUTEX_H
#define PYMUTEX_H
 
#ifdef WIN32
//#include <windows.h>
#else
#include <pthread.h>
#endif
 
typedef void *HANDLE;
 
class IMutex
{
public:
	virtual ~IMutex() {}
 
	virtual void Lock() const = 0;
	virtual bool TryLock() const = 0;
	virtual void Unlock() const = 0;
};
 
class PYMutex : public IMutex
{
public:
	PYMutex();
	~PYMutex();
 
	virtual void Lock() const;
	virtual bool TryLock() const;
	virtual void Unlock() const;
private:
#ifdef _WIN32
	HANDLE m_mutex;
#else
	mutable pthread_mutex_t m_mutex;
#endif
};
 
#endif //PYMUTEX_H