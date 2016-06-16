//---------------------------------------------------------------------------
#pragma hdrstop

#include "DatabaseSupport.h"
#include "SqliteHelper.h"
#include "Terminal.h"
#include "TerminalPanel.h"
#include "TicketGrid.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
CDatabaseSupport::CDatabaseSupport(CController *p)
{
	controller =p;
	SQLite =new CSQLite();
	::InitializeCriticalSection(& m_cs);    //初始化临界区
	connected =false;
}

CDatabaseSupport::~CDatabaseSupport()
{
	SQLite->Close();
	if (SQLite !=NULL) delete SQLite;
}

//---------------------------------------------------------------------------
bool CDatabaseSupport::InitDB(AnsiString dbName)
{
	//DeleteFile(dbName);	//删除数据库文件
	bool ret =SQLite->Open(dbName.c_str(), false);
	if (!ret) return ret;
	if (SQLite->TableExists("TicketLib")==DEF_TABLEEXIST) {
		AnsiString expireTime =DateTimeToStr(Now() +controller->timeStampOffset -60);	//前60天过了兑奖期
		//初始化时删除已经取过来但是还没处理的单子，和后台同步
		if (SQLite->ExecDML("delete from TicketLib where status!=2;") ==SQLITE_OK){
		//if (SQLite->ExecDML("delete from TicketLib;") ==SQLITE_OK){	//每次清空算了
		//if (SQLite->ExecDML("update TicketLib set terminalId=null, status=0 where status!=2;") ==SQLITE_OK){
			connected =true;
			return true;
		}else{
			ShowMessage(SQLite->GetLastError());
			return false;
        }
	}else{			//没有的话创建表
		AnsiString createTableSql ="create table TicketLib(";
		createTableSql +="ticketId varchar(32) not null,";
		createTableSql +="stakeLen int not null,";
		createTableSql +="ticketNumbers varchar(128) not null,";
		createTableSql +="multiple int not null,";
		createTableSql +="gameId varchar(8),";
		createTableSql +="gameAdapterId varchar(8),";
		createTableSql +="money int,";
		createTableSql +="terminalId varchar(12),";
		createTableSql +="status int not null,";
		createTableSql +="stub varchar(512),";
		createTableSql +="PRIMARY KEY (ticketId));";
		if (SQLite->ExecDML(createTableSql.c_str()) ==SQLITE_OK){
			connected =true;
			return true;
		}else{
			ShowMessage(SQLite->GetLastError());
			return false;	//没有的话创建表
        }
	}
}

//---------------------------------------------------------------------------
int CDatabaseSupport::SaveTicket2DB(Ticket *ticket)
{
	AnsiString insertSQL ="insert into TicketLib values(";
	insertSQL +="'" +ticket->ticketId +"', ";
	insertSQL +=AnsiString(ticket->stakeLen) +", ";
	insertSQL +="'" +ticket->ticketNumbers +"', ";
	insertSQL +=AnsiString(ticket->multiple) +", ";
	insertSQL +="'" +ticket->gameId +"', ";
	insertSQL +="'" +ticket->gameAdapterId +"', 0, null, 0, null);";
	SQLite->BeginTrans();
	if (SQLite->ExecDML(insertSQL.c_str()) !=SQLITE_OK){		//错误的话，还是要返回去的
		SQLite->RollbackTrans();
		return false;
	}
	if (SQLite->CommitTrnas() !=SQLITE_OK){
		SQLite->RollbackTrans();
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
int CDatabaseSupport::FetchTicket(CTerminal *terminal, AnsiString gameId, AnsiString betPlayType, int count)
{
	::EnterCriticalSection(&m_cs);	//设置线程临界区，防止多个终端线程并发抢票重复
	AnsiString sql ="select ticketId, stakeLen, ticketNumbers, multiple, gameId, gameAdapterId from TicketLib where status=0";
	if (gameId !=""){				//指定了游戏ID的
		sql +=" and gameId='" +gameId +"'";
		if (betPlayType !="") sql +=" and gameAdapterId='" +betPlayType +"'";		//也又指定了类型的
	}else{							//没有指定游戏的，必须加载本终端上已有的玩法，否则会乱套的
		AnsiString gamesList =controller->terminalSqlLoadGames->Values[terminal->xmlConfig->TerminalID];
		sql +=" and gameId in " +gamesList;
	}
	sql +=" order by gameId, gameAdapterId, ticketId;";
	int retCount =0;
	SQLite->ExecQuery(sql.c_str());
	vector <string> strs;
	while (SQLite->Fetch(strs) ==SQLITE_ROW){
		AnsiString ticketId =AnsiString(strs[0].c_str());
		int stakeLen =StrToInt(AnsiString(strs[1].c_str()));
		AnsiString ticketNumbers =AnsiString(strs[2].c_str());
		int multiple =StrToInt(AnsiString(strs[3].c_str()));
		AnsiString gameId =AnsiString(strs[4].c_str());
		AnsiString betTypeCode =AnsiString(strs[5].c_str());
		//修改状态
		AnsiString updateSql ="update TicketLib set status=1, terminalId='" +terminal->xmlConfig->TerminalID +"' where ticketId='" +ticketId +"';";
		SQLite->BeginTrans();
		if (SQLite->ExecDML(updateSql.c_str()) !=SQLITE_OK){		//错误的话，还是要返回去的
			SQLite->RollbackTrans();
			break;
		}
		if (SQLite->CommitTrnas() !=SQLITE_OK){
			SQLite->RollbackTrans();
			break;
		}
		//放在表格中直接做容器
		CTicketGrid *grid =terminal->panel->GridPending;
		grid->InsertBlankRow(1);		//插入一新空行
		grid->Cells[1][1] =ticketId;
		grid->Cells[2][1] =ticketNumbers;
		grid->Cells[3][1] =IntToStr(multiple);
		grid->Cells[4][1] =terminal->GetStakeNameById(gameId ,betTypeCode);    //计算出来的彩种显示列
		grid->Cells[5][1] =gameId +"-" +betTypeCode;
		grid->Cells[6][1] =stakeLen;
		grid->Cells[7][1] ="1";		//线上的单子
		//继续
		retCount ++;
		if (retCount >=count) break;
	}
	::LeaveCriticalSection(&m_cs);
	return retCount;
}

//---------------------------------------------------------------------------
int CDatabaseSupport::PrintComplete(AnsiString ticketId, AnsiString terminalId, AnsiString stub, int money)
{
	AnsiString updateSQL ="update TicketLib ";
	updateSQL +="set status=2, ";
	updateSQL +="terminalId='" +terminalId +"', ";
	updateSQL +="stub='" +stub +"', ";
	updateSQL +="money=" +AnsiString(money);
	updateSQL += +" where ticketId='" +ticketId +"';";
	::EnterCriticalSection(&m_cs);	//设置线程临界区，防止多个终端线程并发抢票重复
	SQLite->BeginTrans();
	if (SQLite->ExecDML(updateSQL.c_str()) !=SQLITE_OK){		//错误的话，还是要返回去的
		SQLite->RollbackTrans();
		::LeaveCriticalSection(&m_cs);
		return false;
	}
	if (SQLite->CommitTrnas() !=SQLITE_OK){
		SQLite->RollbackTrans();
		::LeaveCriticalSection(&m_cs);
		return false;
	}
	::LeaveCriticalSection(&m_cs);
	return true;
}

//---------------------------------------------------------------------------
bool CDatabaseSupport::FindTicket(AnsiString ticketId, Ticket &ticket)
{
	AnsiString sql ="select ticketId, stakeLen, ticketNumbers, multiple, gameId, gameAdapterId, stub from TicketLib";
	sql += +" where ticketId='" +ticketId +"';";
	SQLite->ExecQuery(sql.c_str());
	vector <string> strs;
	if (SQLite->Fetch(strs) ==SQLITE_ROW){
		ticket.ticketId =AnsiString(strs[0].c_str());
		ticket.stakeLen =StrToInt(AnsiString(strs[1].c_str()));
		ticket.ticketNumbers =AnsiString(strs[2].c_str());
		ticket.multiple =StrToInt(AnsiString(strs[3].c_str()));
		ticket.gameId =AnsiString(strs[4].c_str());
		ticket.gameAdapterId =AnsiString(strs[5].c_str());
		ticket.stub =AnsiString(strs[6].c_str());
		return true;
	}else return false;
}

//---------------------------------------------------------------------------
int CDatabaseSupport::ReturnTicket(AnsiString ticketId)
{
	AnsiString updateSQL ="update TicketLib set status=0, terminalId=null, money=0 where ticketId='" +ticketId +"';";
	::EnterCriticalSection(&m_cs);	//设置线程临界区，防止多个终端线程并发抢票重复
	SQLite->BeginTrans();
	if (SQLite->ExecDML(updateSQL.c_str()) !=SQLITE_OK){		//错误的话，还是要返回去的
		SQLite->RollbackTrans();
		::LeaveCriticalSection(&m_cs);
		return false;
	}
	if (SQLite->CommitTrnas() !=SQLITE_OK){
		SQLite->RollbackTrans();
		::LeaveCriticalSection(&m_cs);
		return false;
	}
	::LeaveCriticalSection(&m_cs);
	return true;
}

//---------------------------------------------------------------------------
int CDatabaseSupport::QueryPendingCount()
{
	//查询实时统计待处理票的张数
	SQLite->ExecQuery("select count(ticketId) from TicketLib where status=0;");
	vector <string> strs;
	if (SQLite->Fetch(strs) ==SQLITE_ROW){
		return StrToInt(AnsiString(strs[0].c_str()));
	}
	return 0;
}

