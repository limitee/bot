//---------------------------------------------------------------------------
#pragma hdrstop

#include <MMSystem.hpp>
#include "IdHTTP.hpp"
#include "DefineStruct.h"
#include "MediaSupport.h"
#include "TicketCenterNodeApp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

CMediaSupport::CMediaSupport(){}

CMediaSupport::~CMediaSupport(){}

//*****************************************************************************
void CMediaSupport::SoundRemind(){
	PlaySound("SystemExclamation", 0, SND_ASYNC);  	//系统操作提醒等适用
}

//*****************************************************************************
void CMediaSupport::SoundErrorNet(){
	PlaySound("SystemHand", 0, SND_ASYNC);			//网络出错适用
}

//*****************************************************************************
void CMediaSupport::SoundErrorLocal(){
	PlaySound("SystemAsterisk", 0, SND_ASYNC); 		//加载或硬件出错适用
}

//*****************************************************************************
void CMediaSupport::SoundOK(){
	PlaySound("SystemExit", 0, SND_ASYNC);			//出票完毕适用
}

//*****************************************************************************
void CMediaSupport::LoadNodeImage(TImage *image, AnsiString terminalType, AnsiString node){
	//先检查本地文件
	AnsiString fileName =terminalType +"-" +node +".jpg";
	try{
		image->Picture->LoadFromFile(fileName);
	}catch(...){
	}
}

void CMediaSupport::DownLoadResource(AnsiString URL, AnsiString fileName){
	try{
		TMemoryStream *stream =new TMemoryStream();
		MainForm->IdHTTP->Get(URL, stream);
		stream->SaveToFile(fileName);
		stream->Clear();
		delete stream;
	}catch(...){
	}
}

