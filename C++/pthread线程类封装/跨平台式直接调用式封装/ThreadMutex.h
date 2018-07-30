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
	//�ֶ��������ֶ�����
    ThreadMutex();
	//�������Ϊtrueʱ���Զ�������������Ϊfalseʱ����Ĭ�Ϲ��캯��������ͬ��
	ThreadMutex(bool isLocker);

    ~ThreadMutex();
    void ThreadLock();
    void UnThreadLock();
private:
	bool m_isLocker; //�Ƿ��Ѿ�����
};

#else
class ThreadMutex
{
private:
    CRITICAL_SECTION m_mutex;
	
public:
	//�ֶ��������ֶ�����
    ThreadMutex()
    {
        ::InitializeCriticalSection(&m_mutex);
    };

	//�������Ϊtrueʱ���Զ�������������Ϊfalseʱ����Ĭ�Ϲ��캯��������ͬ��
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
	bool m_isLocker; //�Ƿ��Ѿ�����
};
#endif

#endif  //_THREADSYNC_H