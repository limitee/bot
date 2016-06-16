//---------------------------------------------------------------------------
#ifndef TerminalCategoryH
#define TerminalCategoryH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>

class CTerminal;

class CTerminalCategory : TCategoryPanel
{
__published:	// IDE-managed Components
	TShape *ShapeStatus;
	TEdit *EchoDescribe;
	TEdit *EchoSum;
	//��������Ϊ��ǰ�ն�
	void __fastcall MonitorPanelClick(TObject *Sender);

private:	// User declarations
	CTerminal *terminal;

	bool onlineStatus, onlineStatusChanged, stubTextChanged;
	AnsiString stubText;						//Ҳ�������ʱ��ˢ��Ʊ������

public:		// User declarations
	__fastcall CTerminalCategory(TCategoryPanelGroup *Owner, CTerminal *term);

	void __fastcall SetTerminalActive();		//���ñ��ն˳�Ϊ��ǰ�ļ����նˣ���Ҫ�ǽ����ϵĴ���
	void __fastcall RefreshInfo();

	void SetConnectionStatus(bool online);

	int ticketCount;
	int ticketMoney;

	int prizeCount;
	double prizeMoney;

	void SetStubEchoText(AnsiString stub);
};

#endif