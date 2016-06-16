//---------------------------------------------------------------------------

#ifndef TerminalBoxH
#define TerminalBoxH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "Printceptor.h"

#define BUFFERSIZE  16384

class CTerminal;

class CTerminalBox : Printceptor
{
	public:
		__fastcall CTerminalBox(CTerminal *term);

		bool connected;

		bool Init(AnsiString port);
		void Close();

		void ConnectionChanged(bool isConnected);			//连接状态变化通知
		void RecieveTerminalStub(BYTE *data, int len);		//接收票根的处理
		void UpdateStatusOk(bool isUpdatedOk);              //固件更新完成通知

		void SendData2Terminal(BYTE *, int len);			//向终端机发送打印机状态数据
		void SendFirmware(BYTE *firm_data, int len);    	//更新固件

		//内部编码字符串打字
		int TypeInnerString(AnsiString str);

		//字符串打字
		void TypeAsciiCode(AnsiString asciiCode);

		//设置间隔时间
		void SetKeyInterval(int interval);

		char stubBuffer[BUFFERSIZE];		//保存每张票的票根数据
		int stubDataLength;                 //票根数据长度

		void SaveStubToFile(); 				//保存票根成文件

	private:
		CTerminal *terminal;

		//键盘内码转ASCII码串
		BYTE TransAsciiCode(AnsiString asciiCode);

};

#endif
