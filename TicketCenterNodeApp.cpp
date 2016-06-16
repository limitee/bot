//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <inifiles.hpp>
#include <System.Zip.hpp>
#include <Vcl.Themes.hpp>

#include "Terminal.h"
#include "TerminalPanel.h"
#include "TerminalBox.h"
#include "TerminalCategory.h"
#include "TerminalRobotTyper.h"
#include "TerminalConfig.h"
#include "TerminalConnection.h"

#include "Controller.h"
#include "TicketCenterNodeApp.h"
#include "MediaSupport.h"
#include "FrameMonitorGroup.h"
#include "FileDataDealer.h"
#include "PrinterCommPort.h"
#include "ConfigUnit.h"
#include "CenterLoginUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"

TMainForm *MainForm;
CController *controller;
// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner){
	//总控制器初始化
	controller = new CController();
	echoLoopTimes =0;
	indexErrMsg =0;
    dateFileBakup =false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender){
	// 读取本地的一些设置，或是上次的配置参数
	TIniFile *ini = new TIniFile(GetCurrentDir() + "\\app.ini");
	int userId = ini->ReadInteger("Center", "UserId", 0);
	AnsiString st = ini->ReadString("Center", "ST", "");
	DateTimePicker->Time = ini->ReadTime("Center", "ShutdownTime", StrToTime("23:45:00"));
	//是否跳过登录界面
	if (userId ==0 || st ==""){
		LoginForm->ShowModal();
	}else{
		controller->centerId =userId;
		controller->centerSt =st;
	}
    TimerTask->Enabled =true;
	// 创建一个ActionList用于动态保存各个标签页的Action
	actionList = new TActionList(MainForm);
	// 读取本地的一些设置，或是上次的配置参数
	MainForm->Width = ini->ReadInteger("FormSize", "Width", 1024);
	MainForm->Height = ini->ReadInteger("FormSize", "Height", 768);
	delete ini;
	//
	FrameMonitor =new TFrameMonitor(this); 		   //用这个Frame，主要是用来加竖滚动条的，并且支持鼠标滑轮滚动
	FrameMonitor->Parent =PanelMonitorGroup;
	//文件打印内容明细
	StringGridTxt->Cells[0][0] ="行数";
	StringGridTxt->Cells[1][0] ="游戏ID";
	StringGridTxt->Cells[2][0] ="玩法类型";
	StringGridTxt->Cells[3][0] ="投注方式";
	StringGridTxt->Cells[4][0] ="彩票号码";
	StringGridTxt->Cells[5][0] ="倍";
	StringGridTxt->Cells[6][0] ="金额分";
	for (int i =0; i <StringGridTxt->RowCount; i++)	StringGridTxt->Cells[0][i+1] =IntToStr(i +1);
	//后台管理浏览器加载，防止Document设置Cookie时为空
	WideString HomePage =LOGIN_URL;
	WebBrowser->Navigate(HomePage.c_bstr());
	//显示登录页并且最大化窗口
	PageControl->ActivePageIndex =1;
	//总控制器初始化
	controller->Init();
	//调整位置
	FormResize(this);
    ShowErrMessage();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender) {
	LinkLabel->Left =MainForm->Width -LinkLabel->Width -23;
	DateTimePicker->Left = LinkLabel->Left -DateTimePicker->Width -3;
	if (MainForm->ClientWidth < 1024) {	// 窗口最小
		MainForm->ClientWidth = 1024;
	}
	if (MainForm->ClientHeight < 768) {	// 窗口最小
		MainForm->ClientHeight = 768;
	}
    TabSheetConfigResize(this);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TabSheetMonitorResize(TObject *Sender){
	//对各个终端监控调整位置
	DeleteSpeedButton->Left =TabSheetMonitor->Width -DeleteSpeedButton->Width -5;
    NextSpeedButton->Left =DeleteSpeedButton->Left -NextSpeedButton->Width -2;
	LabelTerminalMsg->Width =TabSheetMonitor->Width -ButtonGroupStart->Width -196;
	LabelTerminalMsg->Left =(TabSheetMonitor->Width -LabelTerminalMsg->Width) /2 +49;
	PanelMonitorGroup->Left =0;
	PanelMonitorGroup->Width =TabSheetMonitor->Width;
	PanelMonitorGroup->Height =TabSheetMonitor->Height -PanelMonitorGroup->Top;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SpeedButtonTxtLoadClick(TObject *Sender){
	if (ComboBoxTxtTerminal->Text =="") {
		ShowMessage("请先选好出票终端，请确认文件游戏玩法数据此终端可以出票。");
		return;
	}
	//打开彩票号码的文本文件，简单的校验一下，导入表格中
	if (OpenDialogTxt->Execute()){
		TStringList *lines =new TStringList();
		lines->LoadFromFile(OpenDialogTxt->FileName);
		if (lines->Count >=999) {
			ShowMessage("每次文本出票张数不能超过1000张，请分次导入出票！");
			delete lines;
			return;
		}
		for (int i =0, lineIdx=1; i <lines->Count; i++) {
			AnsiString line =lines->operator [](i);
			if (line[1] =='#') continue;        //忽略注释行
			char *lineChars =line.c_str();
			char *delim ="\t";
			char *item;
			int itemIndex =1;
			item =strtok(lineChars, delim);
			StringGridTxt->Cells[itemIndex++][lineIdx] =item;
			while(item =strtok(NULL, delim)){
				StringGridTxt->Cells[itemIndex++][lineIdx] =item;
				if (itemIndex >7) break;
			}
			lineIdx ++;
		}
		if (lines->Count >0) {
			ComboBoxTxtTerminal->Enabled =false;
            SpeedButtonTxtPrint->Enabled =true;
		}
		delete lines;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ButtonTxtClearClick(TObject *Sender){
	//清空加载的彩票号码文本框
	for (int i =0; i <StringGridTxt->RowCount; i++)
		for (int j =1; j <6; j++) StringGridTxt->Cells[j][i+1] ="";
	ComboBoxTxtTerminal->Enabled =true;
	SpeedButtonTxtPrint->Enabled =false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SpeedButtonTxtPrintClick(TObject *Sender){
	//从文本框导出到终端出票
	int idx =controller->terminalGroup->IndexOf(ComboBoxTxtTerminal->Text);
	if (idx <0) return;
	CTerminal *terminal =(CTerminal *)controller->terminalGroup->Objects[idx];
	if (terminal->status !=IDLE){
		ShowMessage("此终端机状态异常，可能连接错误或任务忙，请确认后重试。");
		return;
	}
	//转到终端监控页面
	PageControl->ActivePageIndex =1;
	FrameMonitor->currentTerminal =terminal;	//转到终端页
	//启动本地发票任务
    terminal->lastStake =NULL;
	controller->fileDataDealer->lineIndex =1;   //重新归位
	controller->fileDataDealer->NotifyPrint(terminal);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TabSheetConfigResize(TObject *Sender){
	//调整位置和大小
	StringGridTxt->Width =TabSheetConfig->ClientWidth -PanelTxt->Width -12;
	StringGridTxt->ColWidths[4] =StringGridTxt->Width -337;
	StringGridTxt->Height =TabSheetConfig->ClientHeight -21;
	//
	int left =TabSheetConfig->ClientWidth -PanelTxt->Width -5;
	LabelFileBatch->Left =left;
	PanelTxt->Left =left;
	LabelPrinter->Left =left;
	PanelPrinter->Left =left;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LabeledEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift){
	if (Key !=0x0D) return;
	RichEditPrintTicket->Clear();
	LabeledEdit->ReadOnly =true;
	AnsiString binFileStr =controller->config->BinFileDir +"ticket\\" +LabeledEdit->Text +".bin";
	if (!FileExists(binFileStr)){
        ShowMessage("票号搞错了吧，没有找到这张票的数据，重新输入吧！");
		return;
	}
	int hBinFile = FileOpen(binFileStr, fmOpenRead);
	char bin[16384] ={0};
	int nRead =FileRead(hBinFile, bin, sizeof(bin));
	//解密文件
	char *srcBin =new char[nRead];
	controller->Decrypt(bin, nRead, srcBin);
	FileClose(hBinFile);
	char stubTxt[16384] ={0};
	//借用个对象，计算一下
	if (controller->terminalGroup->Count ==0) return;
	CTerminal *terminal =(CTerminal *)controller->terminalGroup->Objects[0];
	terminal->ParserVerifyStub(nRead, srcBin, stubTxt);
	delete srcBin;
	//显示票根，转换一下，避免单行超过1024字节，控件限制的错误
	TStringList *text =new TStringList();
	text->Text =AnsiString(stubTxt);
	RichEditPrintTicket->Clear();
	RichEditPrintTicket->Lines->AddStrings(text);
	RichEditPrintTicket->Perform(WM_VSCROLL, SB_TOP, 0); //光标归位，免得滚下去难看
	delete text;
	SpeedButtonPrinterPrint->Enabled =true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SpeedButtonPrinterPrintClick(TObject *Sender){
	AnsiString binFileStr =controller->config->BinFileDir +"ticket\\" +LabeledEdit->Text +".bin";
	int hBinFile = FileOpen(binFileStr, fmOpenRead);
	char bin[16384] ={0};
	int nRead =FileRead(hBinFile, bin, sizeof(bin));
	//解密文件
	char *srcBin =new char[nRead];
	controller->Decrypt(bin, nRead, srcBin);
	FileClose(hBinFile);
	//下发到打印机
	controller->printer->SendData(srcBin, nRead);
	delete srcBin;
    SpeedButtonPrinterPrint->Enabled =false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::RichEditPrintTicketDblClick(TObject *Sender) {
	RichEditPrintTicket->Clear();   //清空票根
	SpeedButtonPrinterPrint->Enabled =false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LinkLabelLinkClick(TObject *Sender, const UnicodeString Link, TSysLinkType LinkType){
	ShellExecute (0, NULL, "www.LottChina.com", NULL, NULL, SW_SHOWNORMAL);		//导航到公司主页
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ButtonGroupStartClick(TObject *Sender){
	if (MessageDlg("请确认所有终端机全部就位，等待机器人按键登录吗？", mtConfirmation ,mbOKCancel ,0) ==1){
		for (int i = 0; i <controller->terminalGroup->Count; i++) {
			CTerminal *terminal =(CTerminal *)controller->terminalGroup->Objects[i];
			if (!terminal->box->connected || terminal->status !=WorkStatus::LOGON) continue;
            terminal->Logon();
		}
	}
    ButtonGroupStart->Caption ="彩票终端机列表";
    ButtonGroupStart->Enabled =false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose){
	CTrayIcon->Minimize();
	if (MessageDlg("请确认要退出系统吗？或是取消可转到后台运行。", mtConfirmation ,mbOKCancel ,0) ==1){
		controller->fileDataDealer->Stop();
		//if (MessageDlg("要将所有彩票机全部自动关机吗？", mtConfirmation ,mbOKCancel ,0) ==1) ShutDown(true);
		try{// 保存一些设置到本地配置文件，如窗口大小等
			TIniFile *ini = new TIniFile(GetCurrentDir() + "\\app.ini");
			ini->WriteTime("Center", "ShutdownTime", DateTimePicker->Time);
			ini->WriteString("FormSize", "Width", MainForm->Width);
			ini->WriteString("FormSize", "Height", MainForm->Height);
			for (int i = 0; i <controller->terminalGroup->Count; i++) {
				CTerminal *terminal =(CTerminal *)controller->terminalGroup->Objects[i];
				ini->WriteInteger(terminal->xmlConfig->TerminalID , "KeyboardInterval", terminal->panel->TrackBarKey->Position);
			}
			delete ini;
		}catch(...){}
		//关闭窗口
		CanClose =true;
	}else CanClose =false;
}

//---------------------------------------------------------------------------
void TMainForm::ShutDown(bool shutDownTerminal){
	for (int i = 0; i <controller->terminalGroup->Count; i++) {
		CTerminal *terminal =(CTerminal *)controller->terminalGroup->Objects[i];
		//各个终端强行尝试自动关机
		if (shutDownTerminal) terminal->Shutdown();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::N2Click(TObject *Sender){
	Application->BringToFront();
	Application->Restore();
	CTrayIcon->Restore();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TimerTaskTimer(TObject *Sender){
	StatusBar->Panels->operator [](0)->Text =DateTimeToStr(Now());
	if (DateTimePicker->Checked){           //自动关机设置
		TDateTime time =DateTimePicker->Time;
		if (TimeToStr(time) ==TimeToStr(Now())){
			ShutDown(true);                 //关终端机
			system("shutdown -s -t 30");    //30秒后关电脑，直接运行系统命令算了
		}
	}
	echoLoopTimes ++;
	if (echoLoopTimes >20){     //每16秒变换一次错误提示
		echoLoopTimes =0;
		ShowErrMessage();
		indexErrMsg ++;
	}
	if (! dateFileBakup){         //备份文件的程序执行一次
        dateFileBakup =true;
		controller->BackupDateFile(controller->config->BinFileDir);     //bin文件
		controller->BackupDateFile(controller->config->HexFileDir);     //hex文件
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NextSpeedButtonClick(TObject *Sender){
	indexErrMsg ++;
	ShowErrMessage();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowErrMessage(){
	if (controller->errorMessageBox->Count ==0) {
        LabelTerminalMsg->Caption = "";
		NextSpeedButton->Visible =false;
		DeleteSpeedButton->Visible =false;
        return;
	}
	NextSpeedButton->Visible =true;
	DeleteSpeedButton->Visible =true;
	if (indexErrMsg >=controller->errorMessageBox->Count) indexErrMsg =0;
	LabelTerminalMsg->Caption =controller->errorMessageBox->operator [](indexErrMsg);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteSpeedButtonClick(TObject *Sender){
	if (indexErrMsg <controller->errorMessageBox->Count){
		controller->errorMessageBox->Delete(indexErrMsg);
	}
	ShowErrMessage();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LabelLoadTxtDblClick(TObject *Sender){
	controller->TransAppConfigFile();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LabeledEditClick(TObject *Sender){
    LabeledEdit->ReadOnly =false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::QuitClick(TObject *Sender){
	MainForm->Close();
	Application->Terminate();
}

//---------------------------------------------------------------------------

