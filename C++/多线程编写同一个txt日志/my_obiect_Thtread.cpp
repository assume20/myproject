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
//   __stdcall�Ǻ�������Լ����һ�֣���������Լ����ҪԼ���������£� ����
//   1.��������˳�� ����
//   2.���ö�ջ��˭�����ú����򱻵��ú��������� ����
//   �����ĺ�������Լ����
//   stdcall cdecl fastcall thiscall naked call ����
//   __stdcall��ʾ ����
//   1.������������ѹ���ջ ����
//   2.�������������޸Ķ�ջ ����
//   3.������(�ڱ�����������)�Զ���ǰ�����»��ߣ��������һ��@���ţ��������Ų����ĳߴ� ����
//   ��win32Ӧ�ó�����,��APIENTRY��WINAPI������ʾ_stdcall���ǳ�������

DWORD __stdcall mystar(LPVOID p)
//unsigned int __stdcall mystar(LPVOID p)
{

    my_obiect_Thtread *LP=(my_obiect_Thtread *)p;
	int i=0;
	SYSTEMTIME sy;
	LP->sd.Initial("mylog1.txt","log");
	while (LP->quit)
	{
	  printf("����%d   �����߳̾��Ϊ%d     �����߳�IDΪ%d     i=%d\n",LP->object_name,
															 LP->m_Thread,
															 LP->dwThread,
															 i++);
	 
	  GetLocalTime(&sy);
	  CString str,str2;
	  str2.Format("     ����%d   �����߳̾��Ϊ%d     �����߳�IDΪ%d ����i=%d",LP->object_name,
		  LP->m_Thread,
		  LP->dwThread,
		  i);
	  str.Format("%d:%d:%d:%d  %s",sy.wHour,sy.wMinute,sy.wSecond,sy.wMilliseconds,str2);
	  LP->sd.Info("%s%s"," ",str2.GetBuffer());
	  Sleep(10);
	}
//	LP->sd.Info("��ͨ%s%s%s","����"," ""�����˳�");
	printf("%d�����˳�\n",LP->object_name);
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
