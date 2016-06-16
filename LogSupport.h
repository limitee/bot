//---------------------------------------------------------------------------
#ifndef LogSupportH
#define LogSupportH
//---------------------------------------------------------------------------
#pragma once

#include <vcl.h>

class CController;

class CLogSupport
{
public:
	CLogSupport(AnsiString strFileName, CController *p);
	~CLogSupport();

	void WriteLog(AnsiString pContent);
	void WriteLogWithTime(AnsiString pContent);        //ÿ��дһ�� �Ҵ�ʱ��

	void SetLogSize(int logSize);		//��KΪ��λ���ļ���С

private:
	CController *controller;

	HANDLE handleFile;

	bool initOK;

	CRITICAL_SECTION m_cs;                //�ٽ������߳��Ŷӵ��õĻ������
    int logSize;                          //�ļ���С    -- KB����

};

#endif
