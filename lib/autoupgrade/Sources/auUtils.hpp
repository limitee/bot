// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'auUtils.pas' rev: 6.00

#ifndef auUtilsHPP
#define auUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Auutils
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TacSplitStrSide { LEFT, RIGHT };
#pragma option pop

typedef Set<TacSplitStrSide, LEFT, RIGHT>  TacSplitStrSides;

#pragma pack(push, 1)
struct TDoubleWord
{
	
	union
	{
		struct 
		{
			unsigned DWord;
			
		};
		struct 
		{
			Word LoWord;
			Word HiWord;
			
		};
		
	};
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#define CRLF "\r\n"
#define D_CRLF "\r\n\r\n"
#define HTTPPrefix "http://"
extern PACKAGE bool __fastcall IsOnline(void);
extern PACKAGE Byte __fastcall PercentsOf(Extended Entire, Extended Part);
extern PACKAGE AnsiString __fastcall GetExecutableByExtension(const AnsiString Extension);
extern PACKAGE void __fastcall OpenURL(AnsiString URL, bool InNewWindow);
extern PACKAGE AnsiString __fastcall GetTempDir();
extern PACKAGE AnsiString __fastcall GetSystemDir();
extern PACKAGE bool __fastcall DirectoryExists(const AnsiString DirName);
extern PACKAGE AnsiString __fastcall Base64Encode(const AnsiString Value);
extern PACKAGE AnsiString __fastcall GenerateAttachBoundary(char Salt);
extern PACKAGE AnsiString __fastcall GetMIMEType(AnsiString EXT);
extern PACKAGE void __fastcall SplitStr(AnsiString SubStr, AnsiString Str, AnsiString &FirstPart, AnsiString &SecondPart, TacSplitStrSide MainSide, TacSplitStrSides LeaveSeparatorOn);
extern PACKAGE void __fastcall SplitFilenameAndParams(AnsiString &FileName, AnsiString &Params);
extern PACKAGE bool __fastcall ParseURL(AnsiString URL, AnsiString &Protocol, AnsiString &HostName, AnsiString &URLPath, AnsiString &Username, AnsiString &Password, AnsiString &ExtraInfo, Word &Port);
extern PACKAGE AnsiString __fastcall URLToHostName(const AnsiString URL);
extern PACKAGE AnsiString __fastcall URLToFileName(const AnsiString URL);
extern PACKAGE Shortint __fastcall VersionCheck(const AnsiString NewVersion, const AnsiString OldVersion);
extern PACKAGE System::TDateTime __fastcall GMTToLocalTime(System::TDateTime GMTTime);
extern PACKAGE System::TDateTime __fastcall InternetTimeToDateTime(AnsiString InternetTime);
extern PACKAGE _FILETIME __fastcall DateTimeToFileTime(System::TDateTime Time);
extern PACKAGE System::TDateTime __fastcall FileTimeToDateTime(const _FILETIME &Time);
extern PACKAGE bool __fastcall SetFileTimes(const AnsiString FileName, const System::TDateTime Created = -1.000000E+00, System::TDateTime Modified = -1.000000E+00, System::TDateTime Accessed = -1.000000E+00);
extern PACKAGE __int64 __fastcall Int2x32ToInt64(const unsigned IntHi, const unsigned IntLo);
extern PACKAGE __int64 __fastcall ExtractFileSize(const AnsiString FileName);
extern PACKAGE bool __fastcall LoadResourceToStream(unsigned Instance, char * ResName, char * ResType, Classes::TStream* Stream);
extern PACKAGE void __fastcall ShutdownApplication(void);
extern PACKAGE void __fastcall InitMSRecord(void *Rec, int Size);

}	/* namespace Auutils */
using namespace Auutils;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// auUtils
