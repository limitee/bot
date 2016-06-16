//---------------------------------------------------------------------------
#pragma hdrstop

#include "FileDataDealer.h"
#include "Controller.h"
#include "TicketCenterNodeApp.h"

#include "DefineStruct.h"
#include "Terminal.h"
#include "TerminalRobotTyper.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall CFileDataDealer::CFileDataDealer(CController *c, bool CreateSuspended): TThread(CreateSuspended){
	controller =c;
    lineIndex =1;
}

void __fastcall CFileDataDealer::Execute(){
	while (! Terminated){
        //������
		if (MainForm->StringGridTxt->Cells[4][lineIndex] ==""){
			MainForm->SpeedButtonTxtPrint->Caption ="�������ն˳�Ʊ";
            MainForm->SpeedButtonTxtPrint->Enabled =true;
	        MainForm->ButtonTxtClear->Enabled =true;
			MainForm->SpeedButtonTxtLoad->Enabled =true;
			Suspended =true;
			Sleep(50);
		}
		MainForm->SpeedButtonTxtPrint->Enabled =false;
		MainForm->ButtonTxtClear->Enabled =false;
		MainForm->SpeedButtonTxtLoad->Enabled =false;
		MainForm->SpeedButtonTxtPrint->Caption ="��  " +IntToStr(lineIndex) + "  ��";
		//��һ��Ʊ
		DispatchTicket();
        lineIndex ++;
		//����
        Suspended =true;
		//���ն˻���λ
		Sleep(100);
	}
}

//---------------------------------------------------------------------------
void CFileDataDealer::Stop(){
	this->Terminate();
}

//---------------------------------------------------------------------------
void CFileDataDealer::DispatchTicket(){
	Ticket *ticket =new Ticket();
	ticket->id =0;
	ticket->gameId =StrToInt(MainForm->StringGridTxt->Cells[1][lineIndex]);
	ticket->playType =MainForm->StringGridTxt->Cells[2][lineIndex];
	ticket->betType =MainForm->StringGridTxt->Cells[3][lineIndex];
	ticket->number =MainForm->StringGridTxt->Cells[4][lineIndex];
	ticket->multiple =StrToInt(MainForm->StringGridTxt->Cells[5][lineIndex]);
	ticket->amount =StrToInt(MainForm->StringGridTxt->Cells[6][lineIndex]);

	ticket->fileData =true;

	terminal->robotTyper->SetCurrentRequest((Request *)ticket);
}

//---------------------------------------------------------------------------
void CFileDataDealer::NotifyPrint(CTerminal *term){
    terminal =term;
	Suspended =false;
}

