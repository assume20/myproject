/**
*	@defgrou		日志工具类
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
*	普通写日志工具类
*	@note			内部队列不断接收消息,起线程处理.试验时候记得main中sleep.
*	@par 实例
*	@code
		#include "stdafx.h"
		#include "Log.h"
		int main(int argc, char* argv[])
		{	
			CLog* g_pLog;
			g_pLog = new CLog();

			g_pLog->Initial("test.log","LOG");
			g_pLog->Info("信息%d%s",2,"试一试哦");
			g_pLog->Warn("警告%d%s",123,"试一试哦");
			g_pLog->Erro("错误%d%s",456,"试一试哦");
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
	*	初始化
	*	@param[in]	fileName		日志文件名.log.log或log.txt
	*	@param[in]	directoryName	相对目录名,若为NULL则当前文件夹
	*	@return						返回初始化是否成功
	*	@note						若返回失败,立即调用GetErrorMessage获得详细信息.
	*	@see						GetErrorMessage
	*/
	BOOL		Initial(string fileName, string directoryName = "");
	/**
	*	普通日志信息
	*	@para[in] message			日志信息 
	*	@para[in] ...				变参,实现格式化
	*	@note						类似printf函数
	*	@par
	*	@code
	*		class.Info("普通%s%d","信息",2);
	*	@endcode
	*	@see						Warn,Erro
	*/
	 VOID		Info(string message,...);
	/**
	*	警告日志信息
	*	@para[in] message			日志信息 
	*	@para[in] ...				变参,实现格式化
	*	@note						类似printf函数
	*	@par
	*	@code
	*		class.Warn("警告%s%d","信息",2);
	*	@endcode
	*	@see						Info,Erro
	*/
	static VOID		Warn(string message,...);
	/**
	*	错误日志信息
	*	@para[in] message			日志信息 
	*	@para[in] ...				变参,实现格式化
	*	@note						类似printf函数
	*	@par
	*	@code
	*		class.Erro("警告%s%d","信息",2);
	*	@endcode
	*	@see						Info,Warn
	*/
	static VOID		Erro(string message,...);
	/**
	*	关闭文件
	*	@return						返回是否成功
	*	@note						若返回失败,立即调用GetErrorMessage获得详细信息.
	*	@see						立即调用GetErrorMessage获得详细信息
	*/
	static BOOL		CloseFile(VOID);
	/**
	*	获得错误信息
	*	@return						返回错误信息
	*	@note						任何表示成功与否的操作失败后立刻调用即可返回
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
