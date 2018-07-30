// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Log.h"
#include "MyLog.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HANDLE CLog::m_hFile = NULL;
string CLog::m_sErrorMessage = "";
queue<string> CLog::m_qMessage;
CRITICAL_SECTION CLog::m_lock;
ostringstream CLog::m_stringstream;
BOOL CLog::m_bIsWorking = FALSE;
HANDLE  CLog::hThread =NULL;
string  CLog::moduleNameString="";
CLog::CLog()
{
  
}

CLog::~CLog()
{
  // CloseFile();
   m_bIsWorking=FALSE;
   
}

BOOL CLog::Initial(string fileName, string directoryName /* = "" */)
{
	//如果文件不存在****************************************************
	if (moduleNameString=="")
	{
		char moduleNameChar[MAX_PATH];
		if ( !GetCurrentDirectory(MAX_PATH,moduleNameChar) )
		{
			DWORD i = GetLastError();
			char message[1024];
			FormatMessage(	FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				i,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				message,
				1024,
				NULL);
			m_sErrorMessage = message;
			return FALSE;
		}
		moduleNameString = moduleNameChar;
		if ( directoryName != "" )
		{
			moduleNameString = moduleNameString + "\\" + directoryName;
			//	create directory
			if ( !CreateDirectory(moduleNameString.c_str(),NULL) )
			{
				DWORD i = GetLastError();
				if ( 183 == i)
				{	// 文件夹存在
				} 
				else
				{
					DWORD i = GetLastError();
					char message[1024];
					FormatMessage(	FORMAT_MESSAGE_FROM_SYSTEM,
						NULL,
						i,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						message,
						1024,
						NULL);
					m_sErrorMessage = message;
					return FALSE;
				}
			}
		}
		moduleNameString = moduleNameString + "\\" + fileName;



		if ( (m_hFile = CreateFile(	moduleNameString.c_str(),
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL)) == INVALID_HANDLE_VALUE )
		{	
			DWORD i = GetLastError();
			char message[1024];
			FormatMessage(	FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				i,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				message,
				1024,
				NULL);
			m_sErrorMessage = message;
			return FALSE;
		}
	}

    //创建线程**********************************************************
	if ( hThread == NULL)
	{   
		InitializeCriticalSection(&m_lock);
		m_bIsWorking = TRUE;            

	    hThread = CreateThread(	NULL,
			0,
			WriteFileThread,
			NULL,
			0,
			NULL);
        if(hThread == NULL)
		{
			m_bIsWorking = FALSE;
			DWORD i = GetLastError();
			char message[1024];
			FormatMessage(	FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				i,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				message,
				1024,
				NULL);
			m_sErrorMessage = message;
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CLog::CloseFile()
{
	m_bIsWorking = FALSE;
	if ( !CloseHandle((HANDLE)m_hFile) )
	{
		DWORD i = GetLastError();
		char message[1024];
		FormatMessage(	FORMAT_MESSAGE_FROM_SYSTEM,
						NULL,
						i,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						message,
						1024,
						NULL);
		m_sErrorMessage = message;
		return FALSE;
	}
	return TRUE;
}

string CLog::GetCurTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	m_stringstream.str("");
	CString str;
	str.Format("%02d:%02d:%02d:%02d:%02d:%02d-%04d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	m_stringstream.str(str.GetBuffer());
	return m_stringstream.str();
}

VOID CLog::Info(string message,...)
{
    printf("log开始Info加锁\n");
	
	char buf[1024];
	va_list ptr;
	va_start( ptr, message );
	vsprintf( buf, message.c_str(), ptr);
	va_end( ptr );

	message = buf;
	EnterCriticalSection(&m_lock);
	if (m_qMessage.size()<40)
	{
		m_qMessage.push("\r\nINFO "+GetCurTime()+message);
	}
	LeaveCriticalSection(&m_lock);
	printf("m_qMessage.size()>40\n");
}

VOID CLog::Warn(string message,...)
{
	char buf[1024];
	va_list ptr;
	va_start( ptr, message );
	vsprintf( buf, message.c_str(), ptr);
	va_end( ptr );
	
	message = buf;

	EnterCriticalSection(&m_lock);
	m_qMessage.push("\r\nWARN "+GetCurTime()+message);
	LeaveCriticalSection(&m_lock);
}

VOID CLog::Erro(string message,...)
{
	char buf[1024];
	va_list ptr;
	va_start( ptr, message );
	vsprintf( buf, message.c_str(), ptr);
	va_end( ptr );
	
	message = buf;

	EnterCriticalSection(&m_lock);
	m_qMessage.push("\r\nERRO "+GetCurTime()+message);
	LeaveCriticalSection(&m_lock);
}

string CLog::GetErrorMessage()
{
	return m_sErrorMessage;
}

DWORD WINAPI CLog::WriteFileThread(LPVOID lp)
{
	string tempMessage;
	printf("log开始写入\n");
	while (m_bIsWorking)
	{
		tempMessage = "";
		EnterCriticalSection(&m_lock);
		if (m_qMessage.size() != 0 )
		{
			tempMessage = m_qMessage.front();
			m_qMessage.pop();
		}
		LeaveCriticalSection(&m_lock);
		
		if ( m_hFile != INVALID_HANDLE_VALUE && tempMessage != "" )
		{
			SetFilePointer(m_hFile, 0, NULL, FILE_END); 
			DWORD out;
			BOOL flag = WriteFile(	m_hFile,
				tempMessage.c_str(),
				tempMessage.size(),
				&out,
				NULL);
		}
		else
         printf("log开始写入失败\n");
		Sleep(10);
	}
	printf("log线程退出\n");
	//CloseFile();
	return 0;
}
