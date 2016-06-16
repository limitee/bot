//---------------------------------------------------------------------------
#pragma hdrstop

#include "TerminalRobotTyper.h"

#include "Terminal.h"
#include "TerminalPanel.h"
#include "TerminalCategory.h"
#include "TerminalConfig.h"
#include "TerminalConnection.h"
#include "TerminalBox.h"
#include "TerminalDaemon.h"

#include "MediaSupport.h"
#include "Controller.h"
#include "TicketCenterNodeApp.h"
#include "FileDataDealer.h"

#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall CTerminalRobotTyper::CTerminalRobotTyper(CTerminal *term, bool CreateSuspended): TThread(CreateSuspended){
	terminal =term;
    keyIntervalRestored =false;
}

//---------------------------------------------------------------------------
void __fastcall CTerminalRobotTyper::Execute(){
	while (! Terminated){
		//��������İ�������
        SendKeys();
		//����ֱ�Ӱѱ��̹߳��𣬵ȴ��������ݵ�������֪ͨ
		this->Suspended =true;
		Sleep(20);	//��ʱ�����̷߳�����Դ��ͻ�������ǻ��Ѻ�������ʱ������Դ��ͻ������Ҳ��Ϊ��ָֽ���ļ����ֽ�����ʱ��
		//����Ʊ��
		HandleStub();
		//�ն˸�λ����ʾ����
		terminal->ResetTerminalContext();
		Synchronize(& terminal->panel->ResetPanelRequestEcho);   //���������߳�ȥ����ֹ���߳�������Դ��ͻ
		//���𣬵��´�
		Suspended =true;
		Sleep(50);
	}
}

//---------------------------------------------------------------------------
bool CTerminalRobotTyper::SetCurrentRequest(Request *request){
	if (terminal->status !=WorkStatus::IDLE) return false;
	terminal->currentRequest =request;
	if (request->reqType ==RequestTypeEnum::TICKET) {
		terminal->status =WorkStatus::PRINT;
	}else if (request->reqType ==RequestTypeEnum::BONUS) {
		terminal->status =WorkStatus::AWARD;
	}else if (request->reqType ==RequestTypeEnum::QUERY) {
		terminal->status =WorkStatus::REPORT;
	}
	Synchronize(& terminal->panel->RequestChangePanelUI);
	Suspended =false;
	return true;
}

//---------------------------------------------------------------------------
void CTerminalRobotTyper::SendKeys(){
    int keysCount =0;
	if (terminal->status ==WorkStatus::PRINT) keysCount =SendTicketKeys();
	else if (terminal->status ==WorkStatus::AWARD) keysCount =SendBonusKeys();
	else if (terminal->status ==WorkStatus::REPORT) keysCount =SendQueryKeys();
	//�ȴ�BOX�·����̵����
	long delay =keysCount *8 *(terminal->panel->TrackBarKey->Min +terminal->panel->TrackBarKey->Max -terminal->panel->TrackBarKey->Position);
    Sleep(delay);       //�ȴ��������
	//����ʱ������ж�����Ʊʱ��ĳ�ʱ����
	terminal->daemon->suspendTimestamp =GetTickCount();
}

//---------------------------------------------------------------------------
void CTerminalRobotTyper::HandleStub(){
	//����������ն˵ȴ���״̬������߳����ȴ�����Ҫ״̬���ã�����������
	if (terminal->needReset) return;
	if (terminal->status ==WorkStatus::PRINT) HandleTicketStub();
	else if (terminal->status ==WorkStatus::AWARD) HandleBonusStub();
	else if (terminal->status ==WorkStatus::REPORT) HandleQueryStub();
    //��һ�Ŷ����������������ð����������
	if (! keyIntervalRestored) Synchronize(&RestoreKeyInterval);
	//����OK
	if (terminal->panel->CheckBoxSound->Checked) controller->mediaSupport->SoundOK();
}

//---------------------------------------------------------------------------
void CTerminalRobotTyper::Notify(){
	Suspended =false;
}

//---------------------------------------------------------------------------
void CTerminalRobotTyper::Stop(){
    this->Terminate();
}

//---------------------------------------------------------------------------
int CTerminalRobotTyper::SendTicketKeys(){
    int keysCount =0;
	//�ѵ�ǰ����Ʊ�����б���һ��
    Ticket *currentTicket =(Ticket *)terminal->currentRequest;
	AnsiString id =IntToStr(currentTicket->id);
	AnsiString tickstr =currentTicket->number;
	int times =currentTicket->multiple;
	AnsiString gameAdapter =currentTicket->playType +"-" +currentTicket->betType; 	//��������ι�ϵ��ͬ�����ã�����-
	AnsiString echoName =terminal->GetStakeNameById(currentTicket->gameId, gameAdapter);
	if (echoName ==""){     //�ն�����Ϸ����������
		terminal->daemon->suspendTimestamp =GetTickCount();
		controller->AddErrorMessage("�ն�" +terminal->xmlConfig->TerminalID +"��֧�ִ�����Ϸ��Ʊ�����������ļ����Ժ��ն˻��Զ���λ��");
        return 0;
	}
	//���ò�ˢ���ն˼����Ϣ
    TStringList *line =new TStringList();
	line->Add(id);
	line->Add(tickstr);
	line->Add(IntToStr(times));
	line->Add(gameAdapter);
	line->Add(echoName);
	line->Add(IntToStr(currentTicket->icount));
	line->Add(IntToStr(currentTicket->amount));
    terminal->panel->topLineContent =line;
    Synchronize(&terminal->panel->FillTopLineContent);
    delete line;
	//���ҵ�ǰƱ�ڵ�
	terminal->currentStake =terminal->findStakeById(currentTicket->gameId, gameAdapter);
	//���չ������Գ�Ʊ����ᷢ��ͬһ̨�նˣ�����������ļ���ֱ�ӷ����ļ�Ʊ��
	AnsiString binFile =controller->config->BinFileDir +"ticket\\" +id +".bin";
	if (FileExists(binFile)){
		LoadStubFromFile(binFile);
		return 0;		//ֱ�ӷ��أ����õȴ�����ʱ�䣬����Ҫ�ȴ���Ʊ��ʱ������
	}
	//����������ͬ���͵Ĳ�Ʊ���м������ת��Ҫ�İ���������ӡ��ת
	AnsiString jumpStr =terminal->getJumpInnerCodeString(terminal->lastStake, terminal->currentStake);
	keysCount +=terminal->box->TypeInnerString(jumpStr +"~");
	//���ö�̬�⺯�������ɴ�ӡ����İ������У�����������ȷ�ϣ�
	char keys[256] ={0};
	terminal->GeneralTicketKeyStr((currentTicket->gameId +"-" +gameAdapter), tickstr, times, keys);
	keysCount +=terminal->box->TypeInnerString(AnsiString(keys));
	//������Ʊ����������ʾȷ�ϣ�����δ����
	if (terminal->xmlConfig->LotteryPos->HasAttribute("NeedConfirmAmount")) {
		if (currentTicket->amount >=terminal->xmlConfig->LotteryPos->NeedConfirmAmount && currentTicket->amount < terminal->xmlConfig->LotteryPos->NeedPasswordAmount) {
			keysCount +=terminal->box->TypeInnerString(terminal->xmlConfig->Keyboard->PrintConfirm);  //һ��Ϊ200���ٴ�ȷ��
		}else if (currentTicket->amount >=terminal->xmlConfig->LotteryPos->NeedPasswordAmount) {
			keysCount +=terminal->box->TypeInnerString(terminal->xmlConfig->Keyboard->PrintConfirm);
			keysCount +=terminal->box->TypeInnerString("~~~~~~");            //����������
			keysCount +=terminal->box->TypeInnerString(terminal->xmlConfig->LotteryPos->SalesPassword);         //����500��������ȷ�ϳ�Ʊ
		}
	}
	//ȷ�ϳ�Ʊ��
	keysCount +=terminal->box->TypeInnerString(terminal->xmlConfig->Keyboard->PrintConfirm);
	return keysCount;
}

//---------------------------------------------------------------------------
int CTerminalRobotTyper::SendBonusKeys(){
	int keysCount =0;
	//���ò�ˢ���ն˼����Ϣ
	Bonus *currentBonus =(Bonus *)terminal->currentRequest;
    TStringList *line =new TStringList();
	line->Add(IntToStr(currentBonus->id));
	line->Add(currentBonus->seq);
	line->Add(FloatToStr(currentBonus->bonus/100));
	terminal->panel->topLineContent =line;
	Synchronize(&terminal->panel->FillTopLineContent);
	delete line;
	//���������밴��
	keysCount +=terminal->box->TypeInnerString(terminal->xmlConfig->Keyboard->BobusPrefix);		//�ҽ�����ǰ׺
	//���ö�̬�⺯�������ɴ�ӡ����İ������У�����������ȷ�ϣ�
	char keys[256] ={0};
	terminal->GeneralBonusKeyStr(currentBonus->seq, keys);
	keysCount +=terminal->box->TypeInnerString(AnsiString(keys));
	keysCount +=terminal->box->TypeInnerString(terminal->xmlConfig->Keyboard->BobusPostfix);	//�ҽ�������׺�������F1��ӡ�ҽ���ִ
	return keysCount;
}

//---------------------------------------------------------------------------
int CTerminalRobotTyper::SendQueryKeys(){
	int keysCount =0;
	//�������ѯID���ڱ����в��Ҷ�Ӧ�İ���
	Query *query =(Query *)terminal->currentRequest;
	AnsiString queryId =query->queryCmdType;                                        //�����ѯID: ������-����-��������
	if (query->queryCmdType ==CMD_QUERY_TERM){      		//�齱��
		queryId +="-" +query->gameId +"-" +IntToStr(query->type);
	}else if (query->queryCmdType ==CMD_QUERY_RECEIPT){    	//��ɿ�
		queryId +="-" +IntToStr(query->type);
	}
	int index =0;
	for (; index <terminal->xmlConfig->CategoryReport->Count; index++) {
		if (terminal->xmlConfig->CategoryReport->Get_ReportMenu(index)->HasAttribute("QueryID")
			&& terminal->xmlConfig->CategoryReport->Get_ReportMenu(index)->QueryID ==queryId) break;
	}
	if (index ==terminal->xmlConfig->CategoryReport->Count){
		controller->AddErrorMessage("�ն�" +terminal->xmlConfig->TerminalID +"��̨����Ĳ�ѯID����" +queryId +"���������û��ն˻�������");
		return 0;
	}
	_di_IXMLReportMenuType menu =terminal->xmlConfig->CategoryReport->Get_ReportMenu(index);
	//���������밴��
	keysCount +=terminal->box->TypeInnerString(terminal->xmlConfig->Keyboard->DefaultBackRoot);
	keysCount +=terminal->box->TypeInnerString(menu->InnerKeys);
	return keysCount;
}

//---------------------------------------------------------------------------
void CTerminalRobotTyper::HandleTicketStub(){
	//���������̨�ύ�޸ı���Ʊ�Ĵ�ӡ״̬���Ǳ����ļ���Ʊ���ϴ���̨
	Ticket *currentTicket =(Ticket *)terminal->currentRequest;
	if (currentTicket->fileData){
		//��Ʊ������Ҫ�ȴ�һ�ᣬ���ն˻���λ���߽����л���Ҳ�����±ߵĴ���ִ����
		controller->fileDataDealer->NotifyPrint(terminal);
	}else{
		bool success =terminal->connection->ReplyStub(terminal->currentStub);
		if (!success) {
			controller->AddErrorMessage("�ն�" +terminal->xmlConfig->TerminalID +"��������Ʊ�������̨�ύƱ��ʱ�������Ʊ�ţ�" +IntToStr(currentTicket->id) +"����ע���Ʊ�Ƿ�������");
			terminal->connection->DisConnect();     //�ȴ��´����·���������Ʊ���ļ����ϴ���
		}
	}
	//ͳ�����ݸ��£��������ߵĺͱ��ص�
	terminal->monitor->ticketCount ++;
	terminal->monitor->ticketMoney +=currentTicket->amount;
	//�л���ǰ����һע��¼
	terminal->lastStake =terminal->currentStake;	//Ĭ���л�
	//����ӡ���Ľ��棬�Ƿ��Զ�ת����һͶע��ʽ����ʼλ�ã�����ǵĻ����Զ�ת��ȥ
	if (terminal->currentStake->HasAttribute("FinishedNode") && terminal->currentStake->FinishedNode!="") {
		terminal->lastStake =terminal->findStakeByNode(terminal->currentStake->FinishedNode);
	}
	//����Ųһ��
	Synchronize(& terminal->panel->GridInsertNewDataLine);
}

//---------------------------------------------------------------------------
void CTerminalRobotTyper::HandleBonusStub(){
	Bonus *bonus =(Bonus *)terminal->currentRequest;
	//�ϴ���̨�ҽ���ִ��
	if (!terminal->connection->ReplyStub(terminal->currentStub)){
		controller->AddErrorMessage("�ն�" +terminal->xmlConfig->TerminalID +"�������ҽ�����ִ��δ�ɹ��ϴ���Ʊ�ţ�" +IntToStr(bonus->id) +"����ע��ҽ��Ƿ�������");
		terminal->connection->DisConnect();     //�ȴ��´����·���������Ʊ���ļ����ϴ���
	}
	//�޸ļ���ۼ�����
	terminal->monitor->prizeCount ++;
	terminal->monitor->prizeMoney +=bonus->bonus;
	//����Ųһ��
	Synchronize(& terminal->panel->GridInsertNewDataLine);
}

//---------------------------------------------------------------------------
void CTerminalRobotTyper::HandleQueryStub(){
	//�ϴ���ѯ�������ת����Ŀ¼
	terminal->connection->ReplyStub(terminal->currentStub);
	terminal->box->TypeInnerString(terminal->xmlConfig->CategoryReport->FinishKeys);
}

//---------------------------------------------------------------------------
void __fastcall CTerminalRobotTyper::RestoreKeyInterval(){
   	TIniFile *ini = new TIniFile(GetCurrentDir() + "\\app.ini");
	int keyInterval = ini->ReadInteger(terminal->xmlConfig->TerminalID , "KeyboardInterval", terminal->panel->TrackBarKey->Position);
    delete ini;
	terminal->panel->TrackBarKey->Position =keyInterval;
    keyIntervalRestored =true;
}

//---------------------------------------------------------------------------
void CTerminalRobotTyper::LoadStubFromFile(AnsiString file){
	int hBinFile = FileOpen(file, fmOpenRead);
	char bin[16384] ={0};
	int nRead =FileRead(hBinFile, bin, sizeof(bin));
	//�����ļ�
	controller->Decrypt(bin, nRead, terminal->box->stubBuffer);
	terminal->box->stubDataLength =nRead +1;
	FileClose(hBinFile);
	//������߳������źţ���׼����
	terminal->daemon->stubFromFileReady =true;
}

