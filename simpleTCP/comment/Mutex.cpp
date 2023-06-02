#include "Mutex.h"
 
#ifdef WIN32
#include <windows.h>
#endif
//#include <iostream>
#include <stdio.h>
 
PYMutex::PYMutex()
{
#ifdef _WIN32
	m_mutex = ::CreateMutex(NULL, FALSE, NULL);
#else
	pthread_mutex_init(&m_mutex, NULL);
#endif
}
 
 
PYMutex::~PYMutex()
{
#ifdef _WIN32
	::CloseHandle(m_mutex);
#else
	pthread_mutex_destroy(&m_mutex);
#endif
}
 
 
void PYMutex::Lock() const
{
#ifdef _WIN32
	//DWORD d = WaitForSingleObject(m_mutex, INFINITE);
	WaitForSingleObject(m_mutex, INFINITE);
	/// \todo check 'd' for result
#else
	pthread_mutex_lock(&m_mutex);
#endif
}
 
bool PYMutex::TryLock() const
{
#ifdef _WIN32
    DWORD dwWaitResult = WaitForSingleObject(m_mutex, 0);  
	if (dwWaitResult != WAIT_OBJECT_0 && dwWaitResult != WAIT_TIMEOUT) {
		printf("thread WARNING: bad result from try-locking mutex\n");
	}
    return (dwWaitResult == WAIT_OBJECT_0) ? true : false; 
#else
	return (0==pthread_mutex_trylock(&m_mutex))?true:false;
#endif	
};
 
void PYMutex::Unlock() const
{
#ifdef _WIN32
	::ReleaseMutex(m_mutex);
#else
	pthread_mutex_unlock(&m_mutex);
#endif
}