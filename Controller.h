//---------------------------------------------------------------------------
#ifndef ControllerH
#define ControllerH
//---------------------------------------------------------------------------
#include "DefineStruct.h"
#include "TerminalConfig.h"

/****************************************************************************
* 后台各类组件间的共享控制器，顶层对象
*****************************************************************************/

class CTerminal;
class CMediaSupport;
class CLogSupport;
class CFileDataDealer;
class CPrinterCommPort;

class CController
{
	public:
		CController();
		virtual ~CController();

		//登录以后的后台账号和秘钥
		int centerId;
		AnsiString centerSt;

		//共享之各功能对象
		_di_IXMLDataCenterType config;

		//终端对象组，不使用动态的泛型容器了，还是不如TStringList做MAP维护更方便，还要多引入一些包
		//vector<CTerminal> terminalGroup;
		TStringList *terminalGroup;                	//终端对象组
		TStringList *terminalGameGroup;             //终端玩法组
		TStringList *terminalGameAdapterGroup;      //终端玩法投注方式组
		TStringList *gameMap;						//玩法的MAP，对象不可重复
		TStringList *playBetMap;					//玩法投注方式的MAP，对象不可重复

		//声音、图片辅助对象
		CMediaSupport *mediaSupport;

		//日志对象
		CLogSupport *logSupport;

		//本地数据加载发票任务
		CFileDataDealer *fileDataDealer;

		CPrinterCommPort *printer;

	public:
		bool Init();	//初始化

		//加解密函数，票根信息加解密
		void Encrypt(const char *src, int len, char *dest); 	//加密后dest长度加一，首字节保存原始src[0]作为首尾解密用
		void Decrypt(const char *src, int len, char *dest);		//解密后dest长度减一

		//生成GUID，使用系统的类ID生成方式，也32位
		AnsiString GetGUID(void);

		AnsiString BytesToHexString(BYTE *data, int len);

		void TransAppConfigFile();

		//错误消息盒
		TStringList *errorMessageBox;
		void AddErrorMessage(AnsiString errMsg);

		AnsiString GetTimeStr();

		void BackupDateFile(AnsiString dataFileDir);

	private:
		bool InitConfigXML();
};

#endif
