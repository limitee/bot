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
	logSize = 2048;    //Ĭ��2048KB,2M
	handleFile = CreateFile(strFileName.c_str(), GENERIC_ALL, FILE_SHARE_WRITE, NULL,  OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handleFile == INVALID_HANDLE_VALUE){
		//������־����Ӧ����ʾ�쳣
		initOK =false;
		return;
	}
	::InitializeCriticalSection(& m_cs);    //��ʼ���ٽ���
	initOK =true;
}

CLogSupport::~CLogSupport(void){
    CloseHandle(handleFile);
}

//----------------------------------------------------------------------------
void CLogSupport::WriteLog(AnsiString content){
	DWORD dwFileLenHigh;
	DWORD dwFileLen = GetFileSize(handleFile , &dwFileLenHigh);
	if (dwFileLen > (DWORD)logSize * 1024){    //�ļ����� ����ļ�
		SetFilePointer(handleFile , 0 , NULL , FILE_BEGIN);    //�ƶ��ļ�ָ��
		SetEndOfFile(handleFile);//����ļ�
	}
	AnsiString strContent =content +"\r\n";
	::EnterCriticalSection(&m_cs);
	SetFilePointer(handleFile , 0 , NULL , FILE_END);    //�ƶ����ļ�ĩβ
	DWORD dwWriteLen;
	WriteFile(handleFile, strContent.c_str(), (DWORD)strContent.Length(), &dwWriteLen, NULL);
	::LeaveCriticalSection(&m_cs);	//�ͷ��ٽ���
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

