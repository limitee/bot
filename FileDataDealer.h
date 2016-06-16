//---------------------------------------------------------------------------

#ifndef FileDataDealerH
#define FileDataDealerH
//---------------------------------------------------------------------------
#include <vcl.h>


class CController;
class CTerminal;

class CFileDataDealer : TThread
{
	public:
		__fastcall CFileDataDealer(CController *c, bool CreateSuspended);

		//自动处理线程任务
		void __fastcall Execute();

		void NotifyPrint(CTerminal *term);

		void Stop();

		int lineIndex;

	private:
		CController *controller;
		CTerminal *terminal;

		void DispatchTicket();

};

#endif
