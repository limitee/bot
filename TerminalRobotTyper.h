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

		//�Զ������߳�����
		void __fastcall Execute();

		void Notify();    			//����
		void Stop();

		//
		bool SetCurrentRequest(Request *request);

	private:
		CTerminal *terminal;

		void SendKeys();			//��������
		void HandleStub();			//����Ʊ��

		int SendTicketKeys();		//��Ʊ����
		int SendBonusKeys();		//�ҽ�����
		int SendQueryKeys();		//��ѯ����

		void HandleBonusStub();		//�����н�Ʊ��Ʊ��
		void HandleTicketStub();	//������ƱƱ��
		void HandleQueryStub();		//������ѯ���

		bool keyIntervalRestored;
		void __fastcall RestoreKeyInterval();	//�ɹ������˵�һ�������谴��ΪĬ��ֵ

		void LoadStubFromFile(AnsiString file);
};

#endif
