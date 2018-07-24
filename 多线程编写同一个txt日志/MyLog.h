/**
*	@defgrou		��־������
*	@author			Koven.z@gmail.com
*	@data			2010.12.17
*	@version		0.1

*/

#if !defined(AFX_LOG_H__2A74F79C_57DD_494F_A4B3_ACB208DBE9C5__INCLUDED_)
#define AFX_LOG_H__2A74F79C_57DD_494F_A4B3_ACB208DBE9C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)	

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <windows.h>
#include <stdarg.h>

using namespace std;

/**
*	��ͨд��־������
*	@note			�ڲ����в��Ͻ�����Ϣ,���̴߳���.����ʱ��ǵ�main��sleep.
*	@par ʵ��
*	@code
		#include "stdafx.h"
		#include "Log.h"
		int main(int argc, char* argv[])
		{	
			CLog* g_pLog;
			g_pLog = new CLog();

			g_pLog->Initial("test.log","LOG");
			g_pLog->Info("��Ϣ%d%s",2,"��һ��Ŷ");
			g_pLog->Warn("����%d%s",123,"��һ��Ŷ");
			g_pLog->Erro("����%d%s",456,"��һ��Ŷ");
			Sleep(1000*60);
			g_pLog->CloseFile();
			delete g_pLog;
			return 1;
}
*	@endcode
*/
class CLog  
{
public:
	CLog();
	virtual ~CLog();
	static BOOL				m_bIsWorking;
	static string moduleNameString;
	/**
	*	��ʼ��
	*	@param[in]	fileName		��־�ļ���.log.log��log.txt
	*	@param[in]	directoryName	���Ŀ¼��,��ΪNULL��ǰ�ļ���
	*	@return						���س�ʼ���Ƿ�ɹ�
	*	@note						������ʧ��,��������GetErrorMessage�����ϸ��Ϣ.
	*	@see						GetErrorMessage
	*/
	BOOL		Initial(string fileName, string directoryName = "");
	/**
	*	��ͨ��־��Ϣ
	*	@para[in] message			��־��Ϣ 
	*	@para[in] ...				���,ʵ�ָ�ʽ��
	*	@note						����printf����
	*	@par
	*	@code
	*		class.Info("��ͨ%s%d","��Ϣ",2);
	*	@endcode
	*	@see						Warn,Erro
	*/
	 VOID		Info(string message,...);
	/**
	*	������־��Ϣ
	*	@para[in] message			��־��Ϣ 
	*	@para[in] ...				���,ʵ�ָ�ʽ��
	*	@note						����printf����
	*	@par
	*	@code
	*		class.Warn("����%s%d","��Ϣ",2);
	*	@endcode
	*	@see						Info,Erro
	*/
	static VOID		Warn(string message,...);
	/**
	*	������־��Ϣ
	*	@para[in] message			��־��Ϣ 
	*	@para[in] ...				���,ʵ�ָ�ʽ��
	*	@note						����printf����
	*	@par
	*	@code
	*		class.Erro("����%s%d","��Ϣ",2);
	*	@endcode
	*	@see						Info,Warn
	*/
	static VOID		Erro(string message,...);
	/**
	*	�ر��ļ�
	*	@return						�����Ƿ�ɹ�
	*	@note						������ʧ��,��������GetErrorMessage�����ϸ��Ϣ.
	*	@see						��������GetErrorMessage�����ϸ��Ϣ
	*/
	static BOOL		CloseFile(VOID);
	/**
	*	��ô�����Ϣ
	*	@return						���ش�����Ϣ
	*	@note						�κα�ʾ�ɹ����Ĳ���ʧ�ܺ����̵��ü��ɷ���
	*	@see
	*/
	static string			GetErrorMessage(VOID);
private:
	static string			m_sErrorMessage;
	static HANDLE			m_hFile;
	static queue<string>	m_qMessage;
	static CRITICAL_SECTION	m_lock;
	static ostringstream	m_stringstream;	
	
	static string			GetCurTime(VOID);

    static HANDLE hThread;
	static DWORD WINAPI		WriteFileThread(LPVOID lp);
};

#endif // !defined(AFX_LOG_H__2A74F79C_57DD_494F_A4B3_ACB208DBE9C5__INCLUDED_)
