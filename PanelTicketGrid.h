//---------------------------------------------------------------------------

#ifndef PanelTicketGridH
#define PanelTicketGridH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Grids.hpp>

class CTerminal;

class CTicketGrid : public TStringGrid		//ֱ�Ӽ̳��������������������Ҫ��Ч��ѭ��Ų����
{
__published:	// IDE-managed Components

private:	// User declarations
	CTerminal *terminal;

public:		// User declarations
	__fastcall CTicketGrid(TComponent* Owner, CTerminal *term);

	void InsertBlankRow(int row);	//��Row������һ����
	void DeleteTicket(int row);	//Ϊ�˸�Ч�ʵ�ɾ�����������Ѿ��̳�������ؼ�����Ϊ�������

	void ClearAll();

};


#endif