//---------------------------------------------------------------------------
#ifndef DatabaseSupportH
#define DatabaseSupportH
//---------------------------------------------------------------------------
#include <vector>
#include <algorithm>
#include <vcl.h>
#include "Controller.h"

using namespace std;

class CSQLite;
class CTerminal;

class CDatabaseSupport
{
	public:
		//��ʼ��ʱע�����֮ǰ���ݿ������
		CDatabaseSupport(CController *p);
		~CDatabaseSupport();

		bool InitDB(AnsiString dbName);

		//���浥��Ʊ���������
		int SaveTicket2DB(Ticket *ticket);

		//ȡ��Ʊ���ݣ�ͬʱ����ǣ���ɾ���������ۼ���ͳ����
		int FetchTicket(CTerminal *terminal, AnsiString gameId, AnsiString betCode, int count);

		//��ӡ��ɱ��
		int PrintComplete(AnsiString ticketId, AnsiString terminalId, AnsiString stub, int money);

		//��ӡ��ɱ��
		int ReturnTicket(AnsiString ticketId);

		//����Ticket
        bool FindTicket(AnsiString ticketId, Ticket &ticket);

		//��ѯ��������
		int QueryPendingCount();

        bool connected;

	private:
		CController *controller;
		CSQLite *SQLite;			//���ݿ�Ĳ�������
		CRITICAL_SECTION m_cs;		//�ٽ������߳��Ŷӵ��õĻ������

};

#endif

