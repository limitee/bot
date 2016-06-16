//---------------------------------------------------------------------------
#pragma hdrstop

#include "Terminal.h"
#include "TerminalBox.h"
#include "TerminalConfig.h"
#include "TerminalPanel.h"
#include "TerminalCategory.h"
#include "TerminalConnection.h"
#include "TerminalRobotTyper.h"

#include "TicketCenterNodeApp.h"

#include "DefineStruct.h"
#include "Controller.h"
#include "LogSupport.h"

#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

//*********************************************************************************
__fastcall CTerminalBox::CTerminalBox(CTerminal *term) : Printceptor(){
	terminal =term;
	connected =false;

	memset(stubBuffer, 0, sizeof(stubBuffer)); // ��ʼ��������
	stubDataLength = 0;
}

//----------------------------------------------------------------------------------
bool CTerminalBox::Init(AnsiString port){

	PF_ConnChanged =ConnectionChanged;
	PF_CommReceived =RecieveTerminalStub;
	PF_FirmUpdateStatus = UpdateStatusOk;

    AnsiString comPort ="\\\\.\\" +port;
	startIntercept(0, comPort.c_str());
}

//----------------------------------------------------------------------------------
void CTerminalBox::Close(){
    this->endIntercept();
}

//----------------------------------------------------------------------------------
//��ӡ�������룬�˴�ת��Ϊ��׼�����룬�·���BOX
int CTerminalBox::TypeInnerString(AnsiString str){
	if (str =="") return 0;
//	controller->logSupport->WriteLogWithTime("SEND: " +str);      //��ӡ����־�У�DEBUG��
	char keys[256] ={0};
	int j =0;                                                       //ֻ��ӡ��ʶ���ת�������밴��
	for (int i=1;i<=str.Length();i++){
		_di_IXMLKeyboardCodeType keyItem =terminal->findKeyboardCodeByInnerCode(AnsiString(str[i]));
		if (keyItem !=NULL){
			AnsiString asciiCode =keyItem->KeyboardValue;
			if (asciiCode =="Nop" || asciiCode=="NOP") {			//��ϵͳ�����ӵ��Զ�������룬��������ʱһ����ʱ��
				keys[j++] ='~';
			}else{
				keys[j++] =TransAsciiCode(asciiCode);
			}
		}
	}
	pressKeyboard(keys, j);                                         //�·���BOX
    return j;
}

//----------------------------------------------------------------------------------
void CTerminalBox::ConnectionChanged(bool isConnected){
	connected =isConnected;        //����״̬�仯ָʾ�ã������ն�BOX״̬�ȼ����ߣ�����Socket�Ƿ���Խӵ�
	if (connected) {
		terminal->panel->ChangeBoxConnected();
		terminal->status =WorkStatus::LOGON;                    //�ȴ��ն˻���¼���˹�����
		terminal->box->SetKeyInterval(50);                      //�̶�������������¼��Ҫʱ�䳤һЩ�����밴һ��
	}else{
		terminal->connection->DisConnect();		                //�Ͽ����磬���޸��Զ�����������
		terminal->status =WorkStatus::ERR;
		terminal->panel->ChangeBoxDisconnected();
	}
}

//----------------------------------------------------------------------------------
void CTerminalBox::RecieveTerminalStub(BYTE *data, int len) {
	// ���Ƶ�Ʊ�滺����	//ǿ��ע�⣺��Ҫ�����������־�ȸ������������Ӱ���ӡ�ٶȣ�������ʧ����
	for (int k = 0; k < len; k++) stubBuffer[stubDataLength ++] = data[k];
	// ���ˣ�Ӧ��
	int cutPaper = 0; 		// �Ƿ��Ѿ���������ֽ����
	int respLen = 0; 		// ÿ�λش��źų��ȣ�+1
	char resp[256] = {0}; 	// �ش����ն˵��ź�
	// ȫ���������ֻ���˱��εļ����ֽڣ�����Ϊ��ʱ��ᶪʧ״̬��ִ�����ܲ���һ�δ�������N�ֽڶ��ǲ�ɼ���
	terminal->FilterResponse(stubBuffer, stubDataLength, resp, respLen, cutPaper);
	// ���ʹ�ӡ��״̬��������
	if (respLen){
		SendData2Terminal(resp, respLen);
	}
	// �������ָֽ��˵������һ��Ʊ����ʾ���������һ����Զ���е�ֽ��̰�Ʊ����
	if (cutPaper) { 	  //��ֽ��������ָֽ������ݳ�ʱ��
		SaveStubToFile();                                       // ��Stub���������ȴ�������˵
		char stubTxt[BUFFERSIZE] ={0};
		int money =terminal->ParserVerifyStub(stubDataLength, stubBuffer, stubTxt);
		terminal->NotifyStub(money, AnsiString(stubTxt).Trim());
		//memset(stubBuffer, 0, sizeof(stubBuffer));            //����������
		stubDataLength = 0;
	}
}

//----------------------------------------------------------------------------------
void CTerminalBox::UpdateStatusOk(bool isUpdatedOk){
	if (isUpdatedOk) {
		controller->AddErrorMessage(terminal->xmlConfig->TerminalID +" �Ĺ̼����³ɹ���");
	}else{
		controller->AddErrorMessage(terminal->xmlConfig->TerminalID +" �Ĺ̼�����ʧ�ܣ�");
    }
}

//----------------------------------------------------------------------------------
//�ڲ�ʵ��Ϊ�첽�̣߳������е����ѣ��첽���Ҳû֪ͨ��ֻ���ж�����״̬
void CTerminalBox::SendData2Terminal(BYTE *data, int len){
	if (len >0)	this->sendPrinterData(data, len);
}

//----------------------------------------------------------------------------------
void CTerminalBox::SendFirmware(BYTE *firm_data, int len){
	sendFirmware(firm_data,len);
}

//*********************************************************************************
void CTerminalBox::SaveStubToFile(){
	//����Ʊ�����ļ�
	AnsiString subDir ="";
	AnsiString ticketId =controller->GetGUID();
	if (terminal->status ==WorkStatus::PRINT){
		Ticket *currentTicket =(Ticket *)terminal->currentRequest;
		if (currentTicket->fileData){
			subDir ="file\\"; //�����ļ�����
		}else{
			subDir ="ticket\\";
			ticketId =IntToStr(currentTicket->id);
		}
	}else if (terminal->status ==WorkStatus::AWARD){
		subDir ="bonus\\";
		Bonus *currentBonus =(Bonus *)terminal->currentRequest;
		ticketId =IntToStr(currentBonus->id);
	}else if (terminal->status ==WorkStatus::REPORT){
		subDir ="report\\";
	}else{
		subDir ="extra\\";                      		//���������õĲ�Ʊ�����߱�����
	}
	AnsiString binFileDir =controller->config->BinFileDir +subDir;
	if (!DirectoryExists(binFileDir)) CreateDir(binFileDir);
	char *cryptBin = new char[stubDataLength + 1]; 	// ���ܱ���
	controller->Encrypt(stubBuffer, stubDataLength, cryptBin);
	AnsiString binFileName = binFileDir + ticketId + ".bin";
	int hBinFile = FileCreate(binFileName);
	FileWrite(hBinFile, cryptBin, stubDataLength +1);
	FileClose(hBinFile);
	delete cryptBin;
	//ת����ʮ�����ƣ������ļ�
	AnsiString hexString =controller->BytesToHexString(cryptBin, stubDataLength +1);
	AnsiString hexFileDir =controller->config->HexFileDir +subDir;
	if (!DirectoryExists(hexFileDir)) CreateDir(hexFileDir);
	AnsiString hexFileStr = hexFileDir +ticketId + ".lot";
	int hHexFile =FileCreate(hexFileStr);
	FileWrite(hHexFile, hexString.c_str(), stubDataLength *2 +2);
	FileClose(hHexFile);
}

//----------------------------------------------------------------------------------
void CTerminalBox::SetKeyInterval(int interval){
    this->setKeyDelay(interval);
}

//----------------------------------------------------------------------------------
void CTerminalBox::TypeAsciiCode(AnsiString asciiCode){
	BYTE key =TransAsciiCode(asciiCode);
	pressKeyboard(&key, 1);
}

//----------------------------------------------------------------------------------
BYTE CTerminalBox::TransAsciiCode(AnsiString asciiCode){
	//BOX���̱�����������ַ���Ҫת���������ַ�ֱ����ASCIIֵ����ʼֵ0xFF��������
	BYTE key =0xFF;

	if (asciiCode =="F1") key =0x80;
	if (asciiCode =="F2") key =0x81;
	if (asciiCode =="F3") key =0x82;
	if (asciiCode =="F4") key =0x83;
	if (asciiCode =="F5") key =0x84;
	if (asciiCode =="F6") key =0x85;
	if (asciiCode =="F7") key =0x86;
	if (asciiCode =="F8") key =0x87;
	if (asciiCode =="F9") key =0x88;
	if (asciiCode =="F10") key =0x89;
	if (asciiCode =="F11") key =0x8a;
	if (asciiCode =="F12") key =0x8b;

	if (asciiCode =="Up") key =0x8c;
	if (asciiCode =="Down") key =0x8d;
	if (asciiCode =="Left") key =0x8e;
	if (asciiCode =="Right") key =0x8f;

	if (asciiCode =="Enter") key =0x0d;
	if (asciiCode =="Esc") key =0x1b;
	if (asciiCode =="Backspace") key =0x08;
	if (asciiCode =="Tab") key =0x09;
	if (asciiCode =="Shift") key =0x10;
	if (asciiCode =="Ctrl") key =0x11;
	if (asciiCode =="Alt") key =0x12;

	if (asciiCode ==" " || asciiCode=="Space") key =0x20;

	if (asciiCode =="Nop") return 0x00;

    //����ɼ��ַ���ֱ���ñ�ֵ�·��ͺ���
	if (key ==0xFF) return asciiCode.LowerCase().operator [](1);

	return key;
}