//---------------------------------------------------------------------------
#ifndef TerminalRobotTyperH
#define TerminalRobotTyperH
//---------------------------------------------------------------------------
#include <vcl.h>

#include "DefineStruct.h"

class CTerminal;

class CTerminalRobotTyper : TThread
{
	public:
		__fastcall CTerminalRobotTyper(CTerminal *term, bool CreateSuspended);

		//自动处理线程任务
		void __fastcall Execute();

		void Notify();    			//唤醒
		void Stop();

		//
		bool SetCurrentRequest(Request *request);

	private:
		CTerminal *terminal;

		void SendKeys();			//处理按键
		void HandleStub();			//处理票根

		int SendTicketKeys();		//出票按键
		int SendBonusKeys();		//兑奖按键
		int SendQueryKeys();		//查询按键

		void HandleBonusStub();		//处理中奖票的票根
		void HandleTicketStub();	//处理彩票票根
		void HandleQueryStub();		//处理查询结果

		bool keyIntervalRestored;
		void __fastcall RestoreKeyInterval();	//成功处理了第一单后，重设按键为默认值

		void LoadStubFromFile(AnsiString file);
};

#endif

