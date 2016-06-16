// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'auExtAssociation.pas' rev: 6.00

#ifndef auExtAssociationHPP
#define auExtAssociationHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Auextassociation
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TauShellExtAccessMode { amReadOnly, amReadWrite };
#pragma option pop

class DELPHICLASS TauExtAssociation;
class PASCALIMPLEMENTATION TauExtAssociation : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TauShellExtAccessMode FAccessMode;
	AnsiString FExtension;
	AnsiString FExecutableFile;
	AnsiString FExtDescription;
	AnsiString FFileDescription;
	AnsiString FParamString;
	AnsiString FIconFile;
	int FIconIndex;
	Graphics::TIcon* FLargeIcon;
	Graphics::TIcon* FSmallIcon;
	void __fastcall SetExtension(AnsiString Value);
	void __fastcall SetExecutableFile(AnsiString Value);
	void __fastcall SetExtDescription(AnsiString Value);
	void __fastcall SetFileDescription(AnsiString Value);
	void __fastcall SetParamString(AnsiString Value);
	void __fastcall SetIconFile(AnsiString Value);
	void __fastcall SetIconIndex(int Value);
	void __fastcall SetIcon(Graphics::TIcon* Value);
	bool __fastcall CheckAccessMode(void);
	void __fastcall GetExtensionInfo(void);
	void __fastcall DoInstallExtension(void);
	
public:
	__fastcall virtual TauExtAssociation(Classes::TComponent* aOwner);
	__fastcall virtual ~TauExtAssociation(void);
	bool __fastcall InstallExtension(AnsiString Extension, AnsiString ExecutableFile, AnsiString ParamString, AnsiString ExtDescription, AnsiString FileDescription, AnsiString IconFile, int IconIndex);
	bool __fastcall UninstallExtension(AnsiString Ext);
	
__published:
	__property TauShellExtAccessMode AccessMode = {read=FAccessMode, write=FAccessMode, nodefault};
	__property AnsiString EXTENSION = {read=FExtension, write=SetExtension};
	__property AnsiString ExecutableFile = {read=FExecutableFile, write=SetExecutableFile};
	__property AnsiString ExtDescription = {read=FExtDescription, write=SetExtDescription};
	__property AnsiString FileDescription = {read=FFileDescription, write=SetFileDescription};
	__property AnsiString ParamString = {read=FParamString, write=SetParamString};
	__property AnsiString IconFile = {read=FIconFile, write=SetIconFile};
	__property int IconIndex = {read=FIconIndex, write=SetIconIndex, nodefault};
	__property Graphics::TIcon* LargeIcon = {read=FLargeIcon, write=SetIcon};
	__property Graphics::TIcon* SmallIcon = {read=FSmallIcon, write=SetIcon};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Auextassociation */
using namespace Auextassociation;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// auExtAssociation
