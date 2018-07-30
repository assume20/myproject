#pragma once
#include "stdafx.h"
#include "MyLog.h"
class my_obiect_Thtread
{
public:
	my_obiect_Thtread(void);
	my_obiect_Thtread(int i);
	~my_obiect_Thtread(void);
public:
	int object_name ;
 	HANDLE  m_Thread;
    DWORD  dwThread;
	/*unsigned  m_Thread;
    unsigned  dwThread;*/
	CLog  sd;
	bool  quit;
	bool CreactmyThtread(void);
	int stopThread(void);
};
