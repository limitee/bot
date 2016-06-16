//---------------------------------------------------------------------------
#ifndef TerminalDaemonH
#define TerminalDaemonH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class CTerminal;

class CTerminalDaemon : public TThread
{
private:
	CTerminal *terminal;

	int intervalReconnectSecond;		//网络重连的时间间隔

protected:
	void __fastcall Execute();

public:
	__fastcall CTerminalDaemon(CTerminal *term, bool CreateSuspended);

	long timeoutResetTimestamp;			//尝试复位的超时时间戳，无效状态为-1
	long suspendTimestamp; 			    //挂起的时间戳，非挂起状态为-1

	bool stubFromFileReady;
};
//---------------------------------------------------------------------------
#endif
