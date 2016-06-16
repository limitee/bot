//---------------------------------------------------------------------------
#pragma hdrstop

#include <assert.h>
#include <stdio.h>
#include "LogSupport.h"
#include "Controller.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


CLogSupport::CLogSupport(AnsiString strFileName, CController *p){
	controller =p;
	logSize = 2048;    //默认2048KB,2M
	handleFile = CreateFile(strFileName.c_str(), GENERIC_ALL, FILE_SHARE_WRITE, NULL,  OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handleFile == INVALID_HANDLE_VALUE){
		//创建日志错误，应该提示异常
		initOK =false;
		return;
	}
	::InitializeCriticalSection(& m_cs);    //初始化临界区
	initOK =true;
}

CLogSupport::~CLogSupport(void){
    CloseHandle(handleFile);
}

//----------------------------------------------------------------------------
void CLogSupport::WriteLog(AnsiString content){
	DWORD dwFileLenHigh;
	DWORD dwFileLen = GetFileSize(handleFile , &dwFileLenHigh);
	if (dwFileLen > (DWORD)logSize * 1024){    //文件过大 清空文件
		SetFilePointer(handleFile , 0 , NULL , FILE_BEGIN);    //移动文件指针
		SetEndOfFile(handleFile);//清空文件
	}
	AnsiString strContent =content +"\r\n";
	::EnterCriticalSection(&m_cs);
	SetFilePointer(handleFile , 0 , NULL , FILE_END);    //移动到文件末尾
	DWORD dwWriteLen;
	WriteFile(handleFile, strContent.c_str(), (DWORD)strContent.Length(), &dwWriteLen, NULL);
	::LeaveCriticalSection(&m_cs);	//释放临界区
}

//----------------------------------------------------------------------------
void CLogSupport::WriteLogWithTime(AnsiString content){
	AnsiString timeContent =controller->GetTimeStr() +content;
	WriteLog(timeContent);
}

//----------------------------------------------------------------------------
void CLogSupport::SetLogSize(int iSize){
	logSize = iSize;
}


