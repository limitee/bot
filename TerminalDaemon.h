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

	int intervalReconnectSecond;		//����������ʱ����

protected:
	void __fastcall Execute();

public:
	__fastcall CTerminalDaemon(CTerminal *term, bool CreateSuspended);

	long timeoutResetTimestamp;			//���Ը�λ�ĳ�ʱʱ�������Ч״̬Ϊ-1
	long suspendTimestamp; 			    //�����ʱ������ǹ���״̬Ϊ-1

	bool stubFromFileReady;
};
//---------------------------------------------------------------------------
#endif