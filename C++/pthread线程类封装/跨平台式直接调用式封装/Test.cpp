#include "AllOSThread.h"
#include "ThreadMutex.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int iCount = 0;
ThreadMutex mutex;


THFNRETURN STDCALL ThreadFunc1(void* pParam)
{
	while(1){
		mutex.ThreadLock();
		printf("ThreadFunc1 Running::%d !\n", iCount);
		iCount++;
		mutex.UnThreadLock();
		printf("ThreadFunc1 sleep 2 second ===========================================================================>>>>\n");
		Sleep(2);
	}
	return NULL;
}

THFNRETURN STDCALL ThreadFunc2(void* pParam)
{
	while(1){
		mutex.ThreadLock();
		printf("ThreadFunc2 Running::%d !\n", iCount);
		iCount++;
		mutex.UnThreadLock();
	//	printf("ThreadFunc2 sleep 2 second \n");
		Sleep(1);
	}
	return NULL;
}
int main(int argc, char* argv[])
{
	AllOSThread* pThread = new AllOSThread;
	if(pThread != NULL)
	{
		pThread->CreateThread(ThreadFunc1, NULL);
	}
	if(pThread != NULL)
	{
		pThread->CreateThread(ThreadFunc2, NULL);
	}
	while(1);
	if(pThread != NULL)
		delete pThread;
	pThread = NULL;
}
