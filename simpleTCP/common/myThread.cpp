#include "myThread.h"
 
#include <stdio.h>
 
void* MyThread::run0(void* pVoid)
{
    MyThread* p = (MyThread*) pVoid;
    p->run1();
    return p;
}
 
void* MyThread::run1()
{
    threadStatus = THREAD_STATUS_RUNNING;
    tid = pthread_self();
    Run();
    threadStatus = THREAD_STATUS_EXIT;
    tid = 0;
    pthread_exit(NULL);
}
 
MyThread::MyThread()
{
    tid = 0;
    threadStatus = THREAD_STATUS_NEW;
}
 
MyThread::~MyThread()
{
	join(10);
}
 
int MyThread::Run()
{
    while(true){
        printf("thread is running!\n");
        sleep(100);
    }
    return 0;
}
 
bool MyThread::start()
{
    return pthread_create(&tid, NULL, run0, this) == 0;
}
 
pthread_t MyThread::getThreadID()
{
    return tid;
}
 
int MyThread::getState()
{
    return threadStatus;
}
 
void MyThread::join()
{
    if (tid > 0)
    {
        pthread_join(tid, NULL);
    }
}
 
void MyThread::join(unsigned long millisTime)
{
    if (tid == 0)
    {
        return;
    }
    if (millisTime == 0)
    {
        join();
    }else
    {
        unsigned long k = 0;
        while (threadStatus != THREAD_STATUS_EXIT && k <= millisTime)
        {
            usleep(100);
            k++;
        }
    }
}
 