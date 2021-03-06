//---------------------------------------------------------------------------

#ifndef PanelTicketGridH
#define PanelTicketGridH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Grids.hpp>

class CTerminal;

class CTicketGrid : public TStringGrid		//直接继承下来，方便操作，否则还要低效的循环挪数据
{
__published:	// IDE-managed Components

private:	// User declarations
	CTerminal *terminal;

public:		// User declarations
	__fastcall CTicketGrid(TComponent* Owner, CTerminal *term);

	void InsertBlankRow(int row);	//在Row处插入一空行
	void DeleteTicket(int row);	//为了高效率的删除不出错，费劲继承了这个控件，就为这个方法

	void ClearAll();

};


#endif
