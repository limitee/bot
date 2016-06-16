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

	//����
	TLabel *LabelKeyBoard;
	TButtonGroup *ButtonGroupKeyBoard;
	void __fastcall KeyActionExecute(TObject *Sender);

	//����
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

	bool WarnedPressKey;					//�Ѿ����ѹ���

	bool bonusMode;							//0��Ʊģʽ��1�ҽ�ģʽ
	void SetTicketMode();	   //��Ʊģʽ
	void SetPrizeMode();        //�ҽ�ģʽ
	void SetQueryMode();        //��ѯģʽ

public:		// User declarations
	CTerminal *terminal;
	__fastcall CTerminalPanel(TFrame *Owner, CTerminal *term);

	void __fastcall RequestChangePanelUI();  //��������󣬸ı�UI����

	void __fastcall SetLoginStatus();        //�����¼OK
	void __fastcall SetDisconnectStatus();   //����Ͽ�

	void __fastcall ChangeBoxConnected();
	void __fastcall ChangeBoxDisconnected();

	void __fastcall UpdateBtnPrintConnectionStatus();
	void __fastcall UpdateBtnPrintLoginStatus();

	void __fastcall GridInsertNewDataLine();
	void __fastcall ResetPanelRequestEcho();

};

//---------------------------------------------------------------------------
#endif