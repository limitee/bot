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

	memset(stubBuffer, 0, sizeof(stubBuffer)); // 初始化缓冲区
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
//打印键盘内码，此处转换为标准键盘码，下发到BOX
int CTerminalBox::TypeInnerString(AnsiString str){
	if (str =="") return 0;
//	controller->logSupport->WriteLogWithTime("SEND: " +str);      //打印到日志中，DEBUG用
	char keys[256] ={0};
	int j =0;                                                       //只打印能识别可转换的内码按键
	for (int i=1;i<=str.Length();i++){
		_di_IXMLKeyboardCodeType keyItem =terminal->findKeyboardCodeByInnerCode(AnsiString(str[i]));
		if (keyItem !=NULL){
			AnsiString asciiCode =keyItem->KeyboardValue;
			if (asciiCode =="Nop" || asciiCode=="NOP") {			//本系统中添加的自定义键盘码，仅用于延时一键的时间
				keys[j++] ='~';
			}else{
				keys[j++] =TransAsciiCode(asciiCode);
			}
		}
	}
	pressKeyboard(keys, j);                                         //下发到BOX
    return j;
}

//----------------------------------------------------------------------------------
void CTerminalBox::ConnectionChanged(bool isConnected){
	connected =isConnected;        //连接状态变化指示用，本地终端BOX状态等级更高，决定Socket是否可以接单
	if (connected) {
		terminal->panel->ChangeBoxConnected();
		terminal->status =WorkStatus::LOGON;                    //等待终端机登录，人工操作
		terminal->box->SetKeyInterval(50);                      //固定最慢按键，登录需要时间长一些，半秒按一键
	}else{
		terminal->connection->DisConnect();		                //断开网络，不修改自动重连的配置
		terminal->status =WorkStatus::ERR;
		terminal->panel->ChangeBoxDisconnected();
	}
}

//----------------------------------------------------------------------------------
void CTerminalBox::RecieveTerminalStub(BYTE *data, int len) {
	// 复制到票面缓冲区	//强烈注意：不要在这里边有日志等各类输出，否则影响打印速度，甚至丢失数据
	for (int k = 0; k < len; k++) stubBuffer[stubDataLength ++] = data[k];
	// 过滤，应答
	int cutPaper = 0; 		// 是否已经包含了切纸动作
	int respLen = 0; 		// 每次回传信号长度，+1
	char resp[256] = {0}; 	// 回传给终端的信号
	// 全面检测而不是只过滤本次的几个字节，是因为有时候会丢失状态回执，可能不是一次传过来的N字节而是拆成几段
	terminal->FilterResponse(stubBuffer, stubDataLength, resp, respLen, cutPaper);
	// 回送打印机状态返回数据
	if (respLen){
		SendData2Terminal(resp, respLen);
	}
	// 如果有切纸指令说明出了一张票，显示出来，并且唤醒自动机械手进程把票拿走
	if (cutPaper) { 	  //切纸，或无切纸指令的数据超时了
		SaveStubToFile();                                       // 对Stub做处理，先存起来再说
		char stubTxt[BUFFERSIZE] ={0};
		int money =terminal->ParserVerifyStub(stubDataLength, stubBuffer, stubTxt);
		terminal->NotifyStub(money, AnsiString(stubTxt).Trim());
		//memset(stubBuffer, 0, sizeof(stubBuffer));            //清理缓冲区
		stubDataLength = 0;
	}
}

//----------------------------------------------------------------------------------
void CTerminalBox::UpdateStatusOk(bool isUpdatedOk){
	if (isUpdatedOk) {
		controller->AddErrorMessage(terminal->xmlConfig->TerminalID +" 的固件更新成功。");
	}else{
		controller->AddErrorMessage(terminal->xmlConfig->TerminalID +" 的固件更新失败！");
    }
}

//----------------------------------------------------------------------------------
//内部实现为异步线程，调测有点困难，异步结果也没通知，只能判断连接状态
void CTerminalBox::SendData2Terminal(BYTE *data, int len){
	if (len >0)	this->sendPrinterData(data, len);
}

//----------------------------------------------------------------------------------
void CTerminalBox::SendFirmware(BYTE *firm_data, int len){
	sendFirmware(firm_data,len);
}

//*********************************************************************************
void CTerminalBox::SaveStubToFile(){
	//保存票根成文件
	AnsiString subDir ="";
	AnsiString ticketId =controller->GetGUID();
	if (terminal->status ==WorkStatus::PRINT){
		Ticket *currentTicket =(Ticket *)terminal->currentRequest;
		if (currentTicket->fileData){
			subDir ="file\\"; //本地文件数据
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
		subDir ="extra\\";                      		//可能是手敲的彩票，或者报表等
	}
	AnsiString binFileDir =controller->config->BinFileDir +subDir;
	if (!DirectoryExists(binFileDir)) CreateDir(binFileDir);
	char *cryptBin = new char[stubDataLength + 1]; 	// 加密保存
	controller->Encrypt(stubBuffer, stubDataLength, cryptBin);
	AnsiString binFileName = binFileDir + ticketId + ".bin";
	int hBinFile = FileCreate(binFileName);
	FileWrite(hBinFile, cryptBin, stubDataLength +1);
	FileClose(hBinFile);
	delete cryptBin;
	//转换成十六进制，保存文件
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
	//BOX键盘编码表，特殊字符需要转换，其他字符直接用ASCII值，初始值0xFF保留不用
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

    //其余可见字符，直接用本值下发就好了
	if (key ==0xFF) return asciiCode.LowerCase().operator [](1);

	return key;
}
