#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef WIN32THREAD_H
#define WIN32THREAD_H
 
#include <process.h>
#include <iostream>
 
typedef void *HANDLE;
class MyThread
{
public:
	MyThread();
	~MyThread();
	void start();
	virtual int Run();
	HANDLE getThread();
private:
	HANDLE hThread;
	static void agent(void *p);
};
#endif