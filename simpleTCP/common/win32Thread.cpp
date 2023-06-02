#include "win32Thread.h"
 
#include <windows.h>
 
MyThread::MyThread()
{
}
 
MyThread::~MyThread()
{
	WaitForSingleObject(hThread, INFINITE);
}
 
void MyThread::start()
{
    hThread =(HANDLE)_beginthread(agent, 0, (void *)this);
}
int MyThread::Run()
{
	printf("Base Thread\n");
	return 0;
}
void MyThread::agent(void *p)
{
    MyThread *agt = (MyThread *)p;
    agt->Run();
}
HANDLE MyThread::getThread()
{
    return hThread;
}