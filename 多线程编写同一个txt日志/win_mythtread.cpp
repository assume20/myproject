// win_mythtread.cpp : �������̨Ӧ�ó������ڵ㡣
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
		d.Info("��ͨ%s%s%s","����"," ","����������");
        i++;
		Sleep(500);
	}
	Sleep(3000);
	return 0;
}

