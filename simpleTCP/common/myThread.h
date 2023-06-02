#ifndef _MYTHREAD_H
 
#define _MYTHREAD_H
 
#include <pthread.h>
 
#include <unistd.h>
 
class MyThread
{
private:
    //current thread ID
    pthread_t tid;
    //thread status
    int threadStatus;
    //get manner pointer of execution 
    static void* run0(void* pVoid);
    //manner of execution inside
    void* run1();
public:
    //threadStatus-new create
    static const int THREAD_STATUS_NEW = 0;
    //threadStatus-running
    static const int THREAD_STATUS_RUNNING = 1;
    //threadStatus-end
    static const int THREAD_STATUS_EXIT = -1;
    // constructed function
    MyThread();
    ~MyThread();
    //the entity for thread running
    virtual int Run()=0;
    //start thread
    bool start();
    //gte thread ID
    pthread_t getThreadID();
    //get thread status
    int getState();
    //wait for thread end
    void join();
    //wait for thread end in limit time
    void join(unsigned long millisTime);
};
 
#endif /* _MYTHREAD_H */