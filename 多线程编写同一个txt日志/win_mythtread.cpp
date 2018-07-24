// win_mythtread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "my_obiect_Thtread.h"
#include "MyLog.h"
void test(int i)
{
   my_obiect_Thtread a(1),b(2),c(3);
   Sleep(1000*i);
//    a.stopThread();
//    b.stopThread();
//    c.stopThread();
//    Sleep(1000*i);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i=0;
	CLog d;
	d.Initial("mylog1.txt","log");
	my_obiect_Thtread e(4);
	
	test(2);
	e.stopThread();
	while(i<5)
	{
		d.Info("普通%s%s%s","测试"," ","主函数测试");
        i++;
		Sleep(500);
	}
	Sleep(3000);
	return 0;
}

