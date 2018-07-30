#ifndef   _THREADSYNC_H
#define   _THREADSYNC_H

#ifdef _WIN32
#include<windows.h>
#else
#include <pthread.h>
#endif

#ifndef _WIN32
class ThreadMutex
{
private:
    pthread_mutex_t m_mutex;
	
public:
	//手动上锁，手动解锁
    ThreadMutex();
	//传入参数为true时，自动上锁、解锁；为false时，跟默认构造函数意义相同，
	ThreadMutex(bool isLocker);

    ~ThreadMutex();
    void ThreadLock();
    void UnThreadLock();
private:
	bool m_isLocker; //是否已经上锁
};

#else
class ThreadMutex
{
private:
    CRITICAL_SECTION m_mutex;
	
public:
	//手动上锁，手动解锁
    ThreadMutex()
    {
        ::InitializeCriticalSection(&m_mutex);
    };

	//传入参数为true时，自动上锁、解锁；为false时，跟默认构造函数意义相同，
	ThreadMutex(bool isLocker)
	{
		ThreadMutex();
		if(isLocker)
			ThreadLock();
		m_isLocker = isLocker;
	}
    ~ThreadMutex()
    {
		if(m_isLocker)
			UnThreadLock();
        ::DeleteCriticalSection(&m_mutex);
    };
    void ThreadLock()
    {
		if(!m_isLocker)
			::EnterCriticalSection(&m_mutex);        
    };
    void UnThreadLock()
    {
        ::LeaveCriticalSection(&m_mutex);        
    };
private:
	bool m_isLocker; //是否已经上锁
};
#endif

#endif  //_THREADSYNC_H