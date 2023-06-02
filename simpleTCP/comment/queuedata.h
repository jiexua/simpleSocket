#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#ifndef _QUEUE_DATA_H_
#define _QUEUE_DATA_H_
 
#include <deque>
#include <stdio.h>
#include <string.h>
 
#include "Mutex.h"
#include "Log.h"
 
template <class T>
class QueueData
{
public:
	QueueData(std::string desc = "thread_queue");
	~QueueData();
	//
	/**
	 * 获取队列大小
	 * @return {int } 队列大小
	 */
	int size();
	/**
	 * 判定队列是否为空
	 * @return {bool } 是否为空队列
	 */
	bool isEmpty();
	/**
	 * 获取队列头元素
	 * @param it {T&} 头元素
	 * @return {bool } 是否成功
	 */
	bool getFirst(T &it);
	/**
	 * 删除元素
	 * @return {bool } 是否成功
	 */
	bool removeFirst();
	/**
	 * 获取队列头元素，并从队列终删除
	 * @param it {T&} 头元素
	 * @return {bool } 是否成功
	 */
	bool pop(T &it);
	/**
	 * 从队列头开始逐步获取多个元素，并剔除
	 * @param its {queue<T>&} 获取到的元素集
	 * @param sizel {int} 一次获取多少个
	 * @return {bool } 至少获取一个元素以上则成功
	 */
	bool getList(std::queue<T> &its,unsigned int sizel=5);
	/**
	 * 从队列尾部添加元素
	 * @param it {T} 被添加元素
	 * @return {void } 无返回
	 */
	void add(T it);
	/**
	 * 从队列头部添加元素
	 * @param it {T} 被添加元素
	 * @return {void } 无返回
	 */
	void add_front(T it);
	/**
	 * 清空元素
	 * @return {void }
	 */
	void clear();
private:
	void init();
	QueueData& operator=(const QueueData&) {return this;};
protected:
	std::string queue_desc;
private:
	/点集转发
	
	//协议解析结果缓存
	std::deque<T> datacache_queue;	//队列容器
	PYMutex m_Mutex;				//线程锁,或者如果更彻底采用acl库,采用acl::thread_mutex替代
	//
	static unsigned int QSize;		//队列大小约束,超出是会从队列头剔除旧数据腾出空位在对末添加数据
	//
	int queue_overS;				//队列溢出次数计数
};
template <class T>
unsigned int  QueueData<T>::QSize = 100;
 
template <class T>
QueueData<T>::QueueData(std::string desc)
	: queue_desc(desc)
{
	init();
};
 
template <class T>
void QueueData<T>::init() 
{
	queue_overS = 0;
};
 
template <class T>
QueueData<T>::~QueueData()
{
 
}
 
//
template <class T>
int QueueData<T>::size()
{
	int ret = 0;
	m_Mutex.Lock();
	ret = static_cast<int>(datacache_queue.size());
	m_Mutex.Unlock();
	return ret;
}
 
template <class T>
bool QueueData<T>::isEmpty()
{
	bool ret = false;
	m_Mutex.Lock();
	ret = datacache_queue.empty();
	m_Mutex.Unlock();
	return ret;
}
 
template <class T>
bool QueueData<T>::getFirst(T &it) 
{
	bool ret = false;
	m_Mutex.Lock();
	if (!datacache_queue.empty()) 
	{
		it = datacache_queue.front();
		ret = true;
	}
	m_Mutex.Unlock();
	return ret;
}
 
template <class T>
bool QueueData<T>::removeFirst() 
{
	bool ret = false;
	m_Mutex.Lock();
	if (!datacache_queue.empty()) 
	{
		datacache_queue.pop_front();
		ret = true;
	}
	m_Mutex.Unlock();
	return ret;
}
 
template <class T>
bool QueueData<T>::pop(T &it)
{
	bool ret = false;
	m_Mutex.Lock();
	if (!datacache_queue.empty()) 
	{
		it = datacache_queue.front();
		datacache_queue.pop_front();
		ret = true;
	}
	m_Mutex.Unlock();
	return ret;
};
 
template <class T>
bool QueueData<T>::getList(std::queue<T> &its,unsigned int sizel)
{
	m_Mutex.Lock();
	while (!datacache_queue.empty())
	{
		its.push(datacache_queue.front());
		datacache_queue.pop_front();
		if (its.size() >= sizel)
		{
			break;
		}
	}
	m_Mutex.Unlock();
	return !its.empty();
};
 
template <class T>
void QueueData<T>::add(T it) 
{
	m_Mutex.Lock();
	if (datacache_queue.size() > QSize) 
	{
		queue_overS++;
		datacache_queue.pop_front();
	}
	datacache_queue.push_back(it);
	m_Mutex.Unlock();
	if (queue_overS >= 10) 
	{
		//每溢出10次，报告一次
		CLogger::createInstance()->Log(eSoftError
			,"add item to queue %s at end,but the size of QueueData is up to limmit size: %d.\n"
			, queue_desc.c_str(), QSize);
		queue_overS = 0;
	}
}
 
template <class T>
void QueueData<T>::add_front(T it)
{
	m_Mutex.Lock();
	if (datacache_queue.size() > QSize) 
	{
		queue_overS++;
		datacache_queue.pop_front();
	}
	datacache_queue.push_front(it);
	m_Mutex.Unlock();
	if (queue_overS >= 10) 
	{
		//每溢出10次，报告一次
		CLogger::createInstance()->Log(eSoftError,
			"add item to queue %s at first,but the size of QueueData is up to limmit size: %d.\n"
			, queue_desc.c_str(), QSize);
		queue_overS = 0;
	}
}
 
template <class T>
void QueueData<T>::clear()
{
	m_Mutex.Lock();
	datacache_queue.clear();
	m_Mutex.Unlock();
	queue_overS = 0;
}
 
#endif //_QUEUE_DATA_H_