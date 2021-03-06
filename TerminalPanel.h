//---------------------------------------------------------------------------
#ifndef TerminalPanelH
#define TerminalPanelH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.OleCtrls.hpp>
#include <SHDocVw.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <Vcl.Buttons.hpp>

#include "PanelTicketGrid.h"
#include "TerminalConfig.h"

class CTerminal;

class CTerminalPanel : public TPanel
{
__published:	// IDE-managed Components
	CTicketGrid *TicketGrid;
	void __fastcall TicketGridContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall TicketGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);

	TLabel *LabelGrid;
	TButton *ButtonConfig;
	void __fastcall ButtonConfigClick(TObject *Sender);

	TLabel *LabelTicket;
	TRichEdit *RichEditTicket;
	TLabel *LabelStub;
	TRichEdit *PanelStub;
	void __fastcall PanelStubDblClick(TObject *Sender);

	TPanel *PanelInterval;
	TTrackBar *TrackBarKey;
	void __fastcall TrackBarKeyChange(TObject *Sender);
	TLabel *LabelIntervalKey;

	//键盘
	TLabel *LabelKeyBoard;
	TButtonGroup *ButtonGroupKeyBoard;
	void __fastcall KeyActionExecute(TObject *Sender);

	//报表
	TLabel *LabelReport;
	TCategoryButtons *CategoryButtonsReport;
	void __fastcall CategoryButtonsSelectedCategoryChange(TObject *Sender, TButtonCategory * const Category);

	TPanel *PanelControl;
	TCheckBox *CheckBoxAutoRun;
	TCheckBox *CheckBoxSound;

	TBitBtn *BitBtnPrint;
	void __fastcall BitBtnPrintClick(TObject *Sender);

	void __fastcall CTerminalPanelResize(TObject *Sender);

	TStringList *topLineContent;
	void __fastcall FillTopLineContent();
	void EchoOrderString(int row);

private:	// User declarations

	bool WarnedPressKey;					//已经提醒过了

	bool bonusMode;							//0出票模式，1兑奖模式
	void SetTicketMode();	   //出票模式
	void SetPrizeMode();        //兑奖模式
	void SetQueryMode();        //查询模式

public:		// User declarations
	CTerminal *terminal;
	__fastcall CTerminalPanel(TFrame *Owner, CTerminal *term);

	void __fastcall RequestChangePanelUI();  //配合新请求，改变UI界面

	void __fastcall SetLoginStatus();        //网络登录OK
	void __fastcall SetDisconnectStatus();   //网络断开

	void __fastcall ChangeBoxConnected();
	void __fastcall ChangeBoxDisconnected();

	void __fastcall UpdateBtnPrintConnectionStatus();
	void __fastcall UpdateBtnPrintLoginStatus();

	void __fastcall GridInsertNewDataLine();
	void __fastcall ResetPanelRequestEcho();

};

//---------------------------------------------------------------------------
#endif
