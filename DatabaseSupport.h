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
		//初始化时注意清空之前数据库的数据
		CDatabaseSupport(CController *p);
		~CDatabaseSupport();

		bool InitDB(AnsiString dbName);

		//保存单张票的数据入库
		int SaveTicket2DB(Ticket *ticket);

		//取彩票数据，同时做标记，不删除，本次累计数统计用
		int FetchTicket(CTerminal *terminal, AnsiString gameId, AnsiString betCode, int count);

		//打印完成标记
		int PrintComplete(AnsiString ticketId, AnsiString terminalId, AnsiString stub, int money);

		//打印完成标记
		int ReturnTicket(AnsiString ticketId);

		//查找Ticket
        bool FindTicket(AnsiString ticketId, Ticket &ticket);

		//查询待打张数
		int QueryPendingCount();

        bool connected;

	private:
		CController *controller;
		CSQLite *SQLite;			//数据库的操作对象
		CRITICAL_SECTION m_cs;		//临界区，线程排队调用的互斥机制

};

#endif

