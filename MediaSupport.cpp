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
	PlaySound("SystemExclamation", 0, SND_ASYNC);  	//ϵͳ�������ѵ�����
}

//*****************************************************************************
void CMediaSupport::SoundErrorNet(){
	PlaySound("SystemHand", 0, SND_ASYNC);			//�����������
}

//*****************************************************************************
void CMediaSupport::SoundErrorLocal(){
	PlaySound("SystemAsterisk", 0, SND_ASYNC); 		//���ػ�Ӳ����������
}

//*****************************************************************************
void CMediaSupport::SoundOK(){
	PlaySound("SystemExit", 0, SND_ASYNC);			//��Ʊ�������
}

//*****************************************************************************
void CMediaSupport::LoadNodeImage(TImage *image, AnsiString terminalType, AnsiString node){
	//�ȼ�鱾���ļ�
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
