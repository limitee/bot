// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'auAutoUpgraderAddURL.pas' rev: 6.00

#ifndef auAutoUpgraderAddURLHPP
#define auAutoUpgraderAddURLHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Auautoupgraderaddurl
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TauAddURLForm;
class PASCALIMPLEMENTATION TauAddURLForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* GroupBox1;
	Stdctrls::TButton* OKBtn;
	Stdctrls::TButton* CancelBtn;
	Stdctrls::TEdit* URLEdit;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TauAddURLForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TauAddURLForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TauAddURLForm(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TauAddURLForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Auautoupgraderaddurl */
using namespace Auautoupgraderaddurl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// auAutoUpgraderAddURL
