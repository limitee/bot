//---------------------------------------------------------------------------
#pragma hdrstop

#include "Terminal.h"
#include "TerminalCategory.h"
#include "TerminalPanel.h"

#include "Controller.h"

#include "TicketCenterNodeApp.h"
#include "FrameMonitorGroup.h"

#include "MediaSupport.h"
#include "LogSupport.h"
#include "FileDataDealer.h"
#include "PrinterCommPort.h"

#include <System.Zip.hpp>
#pragma package(smart_init)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CController::CController(){
	logSupport =new CLogSupport(LOG_FILE_NAME, this);
	mediaSupport =new CMediaSupport();
    fileDataDealer =new CFileDataDealer(this, true);                        //�������𣬵ȵ����ż���
	printer =new CPrinterCommPort(true);
	//������
	terminalGroup =new TStringList();
	terminalGameGroup =new TStringList();
	terminalGameAdapterGroup =new TStringList();
	//MAPs
	gameMap =new TStringList();
	gameMap->Duplicates =System::Classes::dupIgnore;						//���ò��ظ�
	playBetMap =new TStringList();
	playBetMap->Duplicates =System::Classes::dupIgnore;						//���ò��ظ�
	//
	errorMessageBox =new TStringList();
	config =NULL;
}

CController::~CController(){
	if (config !=NULL) delete config; config =NULL;
	if (mediaSupport !=NULL) delete mediaSupport; mediaSupport =NULL;
	if (logSupport !=NULL) delete logSupport; logSupport =NULL;
	if (fileDataDealer !=NULL) delete fileDataDealer; fileDataDealer =NULL;
	if (printer !=NULL) delete printer; printer =NULL;
	delete terminalGroup;
	delete terminalGameGroup;
	delete terminalGameAdapterGroup;
	delete gameMap;
	delete playBetMap;
    delete errorMessageBox;
}

//---------------------------------------------------------------------------
bool CController::Init(){
	//��ʼ����־
	logSupport->SetLogSize(512);
	logSupport->WriteLogWithTime("��Ʊ��������APP����...");

	//��ʼ�������ļ�
	if (!InitConfigXML()) return false;
	if (!DirectoryExists(config->BinFileDir)) CreateDir(config->BinFileDir);
	if (!DirectoryExists(config->HexFileDir)) CreateDir(config->HexFileDir);
	logSupport->WriteLogWithTime("���������ļ�����...");

	//��̬���������ն˻����󣬰������ļ�ɨ��һ�飬�ֱ���뵽TStringList��MAP�У��������ʹ�ò�ѯ��λ
	for (int i =0; i < config->Count; i++) {
		_di_IXMLTerminalType terminalXML =config->operator [](i);
		CTerminal *terminal =new CTerminal(terminalXML);
		terminalGroup->AddObject(terminalXML->TerminalID, (TObject *)terminal);								//Terminal

		for (int j= 0; j < terminalXML->LotteryPos->Count; j++) {
			IXMLGameType *game =(_di_IXMLGameType)terminalXML->LotteryPos->Get_Game(j);
			terminalGameGroup->AddObject(terminalXML->TerminalID +":" +game->GameID, (TObject *)game);		//Game����ID
			terminalGameGroup->AddObject(terminalXML->TerminalID +":" +game->GameName, (TObject *)game);	//Game��������
			gameMap->Values[game->GameID] =game->GameName;			//�淨ID�����Ƶ�MAP��һЩ�ط���ҽ��ȵط�������Ҫ�����ѯ�ģ������ظ�

			for (int k =0; k < game->Count; k++) {
				IXMLStakeType *stake =(_di_IXMLStakeType)game->Get_Stake(k);
				terminalGameAdapterGroup->AddObject(terminalXML->TerminalID +":" +stake->StakeNode, (TObject *)stake);			//Stake����Node
				if (stake->HasAttribute("PlayBetId") && stake->PlayBetId !="") {
					terminalGameAdapterGroup->AddObject(terminalXML->TerminalID +":" +game->GameID +":" +stake->PlayBetId, (TObject *)stake);	//Stake����ID
					terminalGameAdapterGroup->AddObject(terminalXML->TerminalID +":" +game->GameName+":" +stake->StakeName, (TObject *)stake);		//Stake��������
					playBetMap->Values[game->GameID +":" +stake->PlayBetId] =game->GameName +stake->StakeName;			//�淨Ͷע��ʽID�����Ƶ�MAP��һЩ�ط�������Ҫ�����ѯ�ģ������ظ���
				}
			}
		}
		terminal->monitor->SetTerminalActive();											//��ѯ��ʾһ�飬���Զ�����������˿�
		MainForm->ComboBoxTxtTerminal->Items->Add(terminal->xmlConfig->TerminalID);		//���ɼ��뵽�ı���ӡ��Ʊ���ն��б�
	}
	logSupport->WriteLogWithTime("�ն˻����ý�������...");

	if (!printer->Init(controller->config->PrinterCom , controller->config->PrinterComParam)){
		delete printer;
		return false;
	}
	logSupport->WriteLogWithTime("��ӡ����ʼ�����...");

	return true;
}

bool CController::InitConfigXML(){
	try{
		//�Ƚ�ѹ���ٽ���
		TZipFile *zip =new TZipFile();
		zip->ExtractZipFile("app.cfg", ".");
		delete zip;
        //��ѹ��XML�����ļ�������ɾ��
		int cfgFile = FileOpen("app.lottchina", fmOpenRead);
		char cfgBin[1024 *512] ={0};
		int nRead =FileRead(cfgFile, cfgBin, sizeof(cfgBin));
		FileClose(cfgFile);
        DeleteFile("app.lottchina");
		//���ܲ���ȡ����XML�ַ���
		char *xml =new char[nRead]; memset(xml, 0, sizeof(xml));
		Decrypt(cfgBin, nRead, xml);
		AnsiString xmlString =AnsiString(xml);
		delete xml;
		//���������������ö���
		TXMLDocument *doc =new TXMLDocument(MainForm);
		doc->LoadFromXML(xmlString);
		config =GetDataCenter(doc);
	}catch(...){
		return false;
	}
	return true;
}

//*********************************************************************************
//�����㷨��ǰһλ���һλ�������βһλ���һλ��򣬽�����ĵ�һλ�����ʼλ��ȡ��
void CController::Encrypt(const char *src, int len, char *dest) {
	int i =len;
	for (i = 0; i < len - 1; i++) dest[i +1] = src[i] ^ src[i + 1];
	dest[i +1] = src[i] ^ src[0];				//���
	dest[0] =0xFF -src[0];                      //ȡ��
	dest[len +1] = 0;
}
//�����㷨�������ܷ�ʽ��������һ�ξ����ˣ�Ӧ��Ҳ�Ƚ���ȷ����ȫ�˰ɣ���Ȼǿ�Ȳ���
void CController::Decrypt(const char *src, int len, char *dest) {
	dest[len -1] = 0;
	dest[len - 2] = src[len -1] ^ (0xFF -src[0]);
	for (int i = len - 3; i >= 0; i--)	dest[i] = src[i +1] ^ dest[i + 1];
}

//*********************************************************************************
AnsiString CController::BytesToHexString(BYTE *data, int len) {
	char *hex =new char[len *2 +1];
	for (int i=0;i<len;i++){
		 unsigned char ch =data[i];             //HEX
		 sprintf(hex +i*2, "%02X ", ch);
	}
	hex[len *2] =0x00;
	AnsiString hexString =AnsiString(hex);
	delete hex;
	return hexString;
}

//*********************************************************************************
AnsiString CController::GetGUID(void) {
	::CoInitialize(NULL);
	char buf[64] = {0};
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid)) {
		_snprintf(buf, sizeof(buf),
			//"{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid.Data1,		//ע�͵���ȥ����-���ӷ�
			"%08X%04X%04x%02X%02X%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	}
	::CoUninitialize();
	return AnsiString(buf);
}

//*********************************************************************************
//���صĹ��ܣ���ԭ����app.xml�ļ���ת���ɼ���ѹ����app.cfg�����ļ�
void CController::TransAppConfigFile(){
	if (!FileExists("app.xml")) return;
	int xmlFile = FileOpen("app.xml", fmOpenRead);
	char xml[1024 *512] ={0};
	int nRead =FileRead(xmlFile, xml, sizeof(xml));
	FileClose(xmlFile);
	//���ܣ������app.lotchina�м��ļ�
	char *crypt =new char[nRead +1]; memset(crypt, 0, sizeof(crypt));
	Encrypt(xml, nRead, crypt);
	int hHexFile =FileCreate("app.lottchina");
	FileWrite(hHexFile, crypt, nRead +1);
	FileClose(hHexFile);
	delete crypt;
	//ѹ����app.cfg��zip�ļ�
	TZipFile *zip =new TZipFile();
	zip->Open("app.cfg", zmWrite);
	zip->Add("app.lottchina");
	zip->Close();
	delete zip;
	DeleteFile("app.lottchina");
}

//*********************************************************************************
void CController::AddErrorMessage(AnsiString errMsg){
	errorMessageBox->Add(GetTimeStr() +errMsg);
}

//----------------------------------------------------------------------------
AnsiString CController::GetTimeStr(){
	//���ظ�ʽ����ʱ���ַ���
	SYSTEMTIME sys;
	::GetLocalTime(&sys);    //��ȡ��ǰϵͳʱ��
	char szTime[64];	memset(szTime , 0 , 64);
	sprintf(szTime, "%02d:%02d:%02d.%03d  ", sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	return AnsiString(szTime);
}

//----------------------------------------------------------------------------
void CController::BackupDateFile(AnsiString dataFileDir){
	//������Ʊ���ļ�Ǩ�ƣ�7��ǰ���ļ������ڴ���Ŀ¼����Ų��ȥ��ֻ��Ʊ���ļ����в���
	AnsiString depotFileDir =dataFileDir +"depot\\";
	if (!DirectoryExists(depotFileDir)) CreateDir(depotFileDir);
	AnsiString dataStrNowFormat = DateTimeToStr(Now()-8);
    dataStrNowFormat = dataStrNowFormat.SubString(0,dataStrNowFormat.Pos(' '));
	AnsiString dataStr = FormatDateTime("yyyy-mm-dd hh:mm:ss",Now()-8);
    dataStr	 = dataStr.SubString(0,10);
	AnsiString dateFileDir =dataFileDir +"depot\\"+dataStr+"\\";
	if (!DirectoryExists(dateFileDir)) CreateDir(dateFileDir);
	WIN32_FIND_DATA wfd;
	TSystemTime tSt;
	TDateTime tDt,tLim;
	AnsiString fileFileDir =dataFileDir +"ticket\\";
	if (DirectoryExists(fileFileDir)){
		AnsiString hexFileDir =dataFileDir +"ticket\\"+ "*.*";
		HANDLE hFind = ::FindFirstFile(hexFileDir.c_str(), &wfd);
		tLim = TDateTime(dataStrNowFormat+"23:59:59");
		if(INVALID_HANDLE_VALUE != hFind){
			do{
				if (strcmp(wfd.cFileName, ".") !=0 && strcmp(wfd.cFileName, "..") != 0){
					FileTimeToSystemTime(&wfd.ftLastWriteTime,&tSt);
					tDt = SystemTimeToDateTime(tSt);
					if (tDt <= tLim) {
						MoveFile((fileFileDir+wfd.cFileName).c_str(), (dateFileDir+wfd.cFileName).c_str());
					}
				}
			}while(::FindNextFile(hFind, &wfd));
		}
		::FindClose(hFind);
	}
}

