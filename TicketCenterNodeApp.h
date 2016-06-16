//---------------------------------------------------------------------------

#ifndef TicketCenterNodeAppH
#define TicketCenterNodeAppH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
#include <SHDocVw.hpp>
#include <Grids.hpp>
#include "trayicon.h"
#include <pngimage.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include "IdHTTP.hpp"
#include <Buttons.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Dialogs.hpp>
#include "SHDocVw_OCX.h"

#include <gdiplus.h>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------

class CController;

class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl;
	TTabSheet *TabSheetManage;
	TImageList *ImageListTab;
	TTabSheet *TabSheetConfig;
	TStatusBar *StatusBar;
	TTabSheet *TabSheetMonitor;
	TStringGrid *StringGridTxt;
	TLabel *LabelLoadTxt;
	TSpeedButton *SpeedButtonTxtLoad;
	TPanel *PanelTxt;
	TImageList *ImageListBtn;
	TLabel *LabelTxtTerminal;
	TComboBox *ComboBoxTxtTerminal;
	TSpeedButton *SpeedButtonTxtPrint;
	TOpenDialog *OpenDialogTxt;
	TPanel *PanelMonitorGroup;
	TButton *ButtonTxtClear;
	TCppWebBrowser *WebBrowser;
	TImageList *ImageListMenu;
	TLabel *LabelTerminalMsg;
	TLinkLabel *LinkLabel;
	TIdHTTP *IdHTTP;
	TLabel *LabelFileBatch;
	TLabel *LabelPrinter;
	TPanel *PanelPrinter;
	TSpeedButton *SpeedButtonPrinterPrint;
	TRichEdit *RichEditPrintTicket;
	TPopupMenu *PopupMenu;
	TMenuItem *N1;
	TMenuItem *Quit;
	TCTrayIcon *CTrayIcon;
	TMenuItem *N2;
	TButton *ButtonGroupStart;
	TTimer *TimerTask;
	TLabeledEdit *LabeledEdit;
	TDateTimePicker *DateTimePicker;
	TSpeedButton *NextSpeedButton;
	TSpeedButton *DeleteSpeedButton;
	void __fastcall FormResize(TObject *Sender);
	void __fastcall TabSheetMonitorResize(TObject *Sender);
	void __fastcall SpeedButtonTxtLoadClick(TObject *Sender);
	void __fastcall TabSheetConfigResize(TObject *Sender);
	void __fastcall ButtonTxtClearClick(TObject *Sender);
	void __fastcall SpeedButtonTxtPrintClick(TObject *Sender);
	void __fastcall LinkLabelLinkClick(TObject *Sender, const UnicodeString Link, TSysLinkType LinkType);
	void __fastcall SpeedButtonPrinterPrintClick(TObject *Sender);
	void __fastcall RichEditPrintTicketDblClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall QuitClick(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonGroupStartClick(TObject *Sender);
	void __fastcall LabelLoadTxtDblClick(TObject *Sender);
	void __fastcall TimerTaskTimer(TObject *Sender);
	void __fastcall LabeledEditClick(TObject *Sender);
	void __fastcall LabeledEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall NextSpeedButtonClick(TObject *Sender);
	void __fastcall DeleteSpeedButtonClick(TObject *Sender);

private:	// User declarations
	int echoLoopTimes, indexErrMsg;
	void __fastcall ShowErrMessage();

	bool dateFileBakup;		//每日数据文件备份

	void ShutDown(bool allTerminal);

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);

	TActionList *actionList;

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
extern PACKAGE CController *controller;
//---------------------------------------------------------------------------
#endif
