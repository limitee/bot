//---------------------------------------------------------------------------
#ifndef ConfigUnitH
#define ConfigUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <Vcl.Dialogs.hpp>

class CTerminal;

class TConfigForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TButton *ButtonSaveConfig;
	TEdit *EditNo;
	TComboBox *ComboBoxTerminalType;
	TComboBox *ComboBoxLotteryKind;
	TCheckBox *CheckBoxManager;
	TComboBox *ComboBoxCom;
	TEdit *EditAccount;
	TEdit *EditPasswd;
	TEdit *EditUKey;
	TLabel *Label8;
	TValueListEditor *ValueListEditor;
	TButton *ButtonUpdateFirmware;
	TOpenDialog *OpenDialogFirmware;
	void __fastcall ButtonUpdateFirmwareClick(TObject *Sender);
private:	// User declarations
	CTerminal *terminal;
	void __fastcall GetComPortList(TStrings *lstComm);

public:		// User declarations
	__fastcall TConfigForm(TComponent* Owner);

	void SetTerminal(CTerminal *term);

};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
