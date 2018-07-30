#include "stdafx.h"
#include "my_obiect_Thtread.h"

my_obiect_Thtread::my_obiect_Thtread(void)
{
	m_Thread=NULL;
	object_name=0;
	quit =1;
    CreactmyThtread();
}

my_obiect_Thtread::my_obiect_Thtread(int i)
{
	m_Thread=NULL;
	object_name=i;	
	quit =1;
	CreactmyThtread();
}

my_obiect_Thtread::~my_obiect_Thtread(void)
{
    /*::PostThreadMessage(dwThread,WM_QUIT,0,0);
	::WaitForSingleObject(m_Thread, 0);
    CloseHandle(m_Thread);*/

     quit =0;
     Sleep(3000);	
}
// 
//   __stdcall是函数调用约定的一种，函数调用约定主要约束了两件事： 　　
//   1.参数传递顺序 　　
//   2.调用堆栈由谁（调用函数或被调用函数）清理 　　
//   常见的函数调用约定：
//   stdcall cdecl fastcall thiscall naked call 　　
//   __stdcall表示 　　
//   1.参数从右向左压入堆栈 　　
//   2.函数被调用者修改堆栈 　　
//   3.函数名(在编译器这个层次)自动加前导的下划线，后面紧跟一个@符号，其后紧跟着参数的尺寸 　　
//   在win32应用程序里,宏APIENTRY，WINAPI，都表示_stdcall，非常常见。

DWORD __stdcall mystar(LPVOID p)
//unsigned int __stdcall mystar(LPVOID p)
{

    my_obiect_Thtread *LP=(my_obiect_Thtread *)p;
	int i=0;
	SYSTEMTIME sy;
	LP->sd.Initial("mylog1.txt","log");
	while (LP->quit)
	{
	  printf("对象%d   所在线程句柄为%d     所在线程ID为%d     i=%d\n",LP->object_name,
															 LP->m_Thread,
															 LP->dwThread,
															 i++);
	 
	  GetLocalTime(&sy);
	  CString str,str2;
	  str2.Format("     对象%d   所在线程句柄为%d     所在线程ID为%d 自增i=%d",LP->object_name,
		  LP->m_Thread,
		  LP->dwThread,
		  i);
	  str.Format("%d:%d:%d:%d  %s",sy.wHour,sy.wMinute,sy.wSecond,sy.wMilliseconds,str2);
	  LP->sd.Info("%s%s"," ",str2.GetBuffer());
	  Sleep(10);
	}
//	LP->sd.Info("普通%s%s%s","测试"," ""对象退出");
	printf("%d对象退出\n",LP->object_name);
	return 0;
}

bool my_obiect_Thtread::CreactmyThtread(void)
{
    if (m_Thread==0)
    {   
		m_Thread=CreateThread(NULL,0,mystar,this,0,&dwThread);

	    //m_Thread=_beginthreadex(NULL,0,mystar,this,0,&dwThread);
    }
	return true;
}

int my_obiect_Thtread::stopThread(void)
{
	quit=0;
	return 0;
}
