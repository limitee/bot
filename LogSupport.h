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
	void WriteLogWithTime(AnsiString pContent);        //每次写一行 且带时间

	void SetLogSize(int logSize);		//以K为单位的文件大小

private:
	CController *controller;

	HANDLE handleFile;

	bool initOK;

	CRITICAL_SECTION m_cs;                //临界区，线程排队调用的互斥机制
    int logSize;                          //文件大小    -- KB计算

};

#endif
