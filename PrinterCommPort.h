//---------------------------------------------------------------------------
#ifndef PrinterCommPortH
#define PrinterCommPortH
//---------------------------------------------------------------------------
#include <vcl.h>

#define BUFFSIZE 4096

class CPrinterCommPort : public TThread
{
	public:
		CPrinterCommPort(bool CreateSuspended);

		//�������� COM1	19200,8,N,0
		bool Init(AnsiString commPort, AnsiString comParam);

		bool Close();

		int GetReceivedCount();
		int ReadComm(void* ReadBuffer,int Length);

		int SendData(void* SendData,int Length);
		bool FlushCommBuffer(bool TxBuffer,bool RxBuffer);

		int (__closure *fCommReceived)(CPrinterCommPort *);

	protected:
		void __fastcall Execute();

	private:
		bool	CommOpen;

		HWND__ *HWND;
		unsigned int CommMsgId;			//��������Ϣ��

		OVERLAPPED	osW,osR;
		HANDLE	hCom;
		COMSTAT CommStat;
		DCB dcb;
		COMMTIMEOUTS CommTimeOuts;

		void __fastcall MessageProc(TMessage &Message);

		int SendData(void* SendData,int Length,bool Wait);
};

#endif