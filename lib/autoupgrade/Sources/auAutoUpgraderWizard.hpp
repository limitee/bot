// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'auAutoUpgraderWizard.pas' rev: 6.00

#ifndef auAutoUpgraderWizardHPP
#define auAutoUpgraderWizardHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Graphics.hpp>	// Pascal unit
#include <auAutoUpgrader.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Auautoupgraderwizard
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TauAutoUpgraderWizardForm;
class PASCALIMPLEMENTATION TauAutoUpgraderWizardForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TPanel* Panel1;
	Extctrls::TImage* Image1;
	Extctrls::TBevel* Bevel1;
	Stdctrls::TLabel* WizardTitle;
	Stdctrls::TGroupBox* LCurrentFile;
	Stdctrls::TGroupBox* LAllFiles;
	Stdctrls::TLabel* LDownloadingFileFrom;
	Stdctrls::TLabel* EstimatedTimeLeftLab;
	Stdctrls::TLabel* TransferRateLab;
	Comctrls::TProgressBar* ProgressCurrentFile;
	Comctrls::TProgressBar* ProgressAllFiles;
	Stdctrls::TButton* FinishBtn;
	Stdctrls::TButton* CancelBtn;
	Stdctrls::TLabel* AllDownloading;
	Stdctrls::TLabel* AboutShadow;
	Stdctrls::TLabel* AboutLabel;
	Stdctrls::TEdit* FileURL;
	Stdctrls::TLabel* AfterNote;
	Stdctrls::TLabel* FileSizeLab;
	void __fastcall FormClose(System::TObject* Sender, Forms::TCloseAction &Action);
	void __fastcall FileURLKeyPress(System::TObject* Sender, char &Key);
	void __fastcall FinishBtnClick(System::TObject* Sender);
	void __fastcall CancelBtnClick(System::TObject* Sender);
	
private:
	Auautoupgrader::TauAutoUpgrader* AutoUpgrader;
	HIDESBASE MESSAGE void __fastcall WMSysCommand(Messages::TWMSysCommand &Message);
	
public:
	void __fastcall Finish(void);
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TauAutoUpgraderWizardForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TauAutoUpgraderWizardForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TauAutoUpgraderWizardForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TauAutoUpgraderWizardForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TauAutoUpgraderWizardForm* WizardForm;
extern PACKAGE void __fastcall ShowAutoUpgraderWizard(Auautoupgrader::TauAutoUpgrader* aAutoUpgrader);

}	/* namespace Auautoupgraderwizard */
using namespace Auautoupgraderwizard;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// auAutoUpgraderWizard
