// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'auAutoUpgrader.pas' rev: 6.00

#ifndef auAutoUpgraderHPP
#define auAutoUpgraderHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <auHTTP.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Auautoupgrader
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TauAutoUpgraderLanguage { wlAuto, wlEnglish, wlRussian, wlGerman, wlFrench, wlSpanish, wlPortuguese, wlPortugueseBrazilian, wlItalian, wlDutch, wlDanish, wlSwedish, wlFinnish, wlEstonian, wlUkrainian, wlCzech, wlHungarian, wlRomanian, wlCatalan, wlBasque, wlAfrikaans, wlChineseTraditional, wlChineseSimplified, wlIndonesian, wlMalay, wlIcelandic };
#pragma option pop

#pragma option push -b-
enum TacMiscFilesUpgradeBehavior { mfuAlwaysDownload, mfuOnlyIfSizeDifferent };
#pragma option pop

#pragma option push -b-
enum TauAutoUpgraderVersionControl { byDate, byNumber };
#pragma option pop

#pragma option push -b-
enum TacUpgradeMethod { umSelfUpgrade, umUseExternalSetup, umRedirectToURL };
#pragma option pop

class DELPHICLASS TauAutoUpgraderInfo;
class PASCALIMPLEMENTATION TauAutoUpgraderInfo : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	Classes::TStrings* FFiles;
	TacUpgradeMethod FUpgradeMethod;
	AnsiString FUpgradeMsg;
	void __fastcall SetFiles(const Classes::TStrings* Value);
	
public:
	__fastcall TauAutoUpgraderInfo(void);
	__fastcall virtual ~TauAutoUpgraderInfo(void);
	
__published:
	__property Classes::TStrings* Files = {read=FFiles, write=SetFiles};
	__property TacUpgradeMethod UpgradeMethod = {read=FUpgradeMethod, write=FUpgradeMethod, default=0};
	__property AnsiString UpgradeMsg = {read=FUpgradeMsg, write=FUpgradeMsg};
};


#pragma option push -b-
enum auAutoUpgrader__2 { mAskUpgrade, mConnLost, mHostUnreachable, mLostFile, mNoInfoFile, mNoUpdateAvailable, mPasswordRequest };
#pragma option pop

typedef Set<auAutoUpgrader__2, mAskUpgrade, mPasswordRequest>  TauAutoUpgraderShowMessages;

class DELPHICLASS TauAutoUpgraderWizard;
class PASCALIMPLEMENTATION TauAutoUpgraderWizard : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	bool FEnabled;
	Graphics::TPicture* FPicture;
	TauAutoUpgraderLanguage FLanguage;
	bool FStayOnTop;
	void __fastcall SetPicture(const Graphics::TPicture* Value);
	void __fastcall SetLanguage(TauAutoUpgraderLanguage Value);
	
public:
	__fastcall TauAutoUpgraderWizard(Classes::TComponent* aOwner);
	__fastcall virtual ~TauAutoUpgraderWizard(void);
	
__published:
	__property bool Enabled = {read=FEnabled, write=FEnabled, default=1};
	__property Graphics::TPicture* Pic118x218 = {read=FPicture, write=SetPicture};
	__property TauAutoUpgraderLanguage Language = {read=FLanguage, write=SetLanguage, default=0};
	__property bool StayOnTop = {read=FStayOnTop, write=FStayOnTop, default=1};
};


typedef void __fastcall (__closure *TAUBeginUpgradeEvent)(System::TObject* Sender, const AnsiString UpgradeMsg, TacUpgradeMethod UpgradeMethod, Classes::TStringList* Files, bool &CanUpgrade);

typedef void __fastcall (__closure *TAUFileStartEvent)(System::TObject* Sender, const AnsiString FileURL, int FileSize, System::TDateTime FileTime, bool &CanUpgrade);

typedef void __fastcall (__closure *TAUFileDoneEvent)(System::TObject* Sender, const AnsiString FileName);

typedef void __fastcall (__closure *TAUHostUnreachableEvent)(System::TObject* Sender, const AnsiString URL, const AnsiString Hostname);

typedef void __fastcall (__closure *TAULostFileEvent)(System::TObject* Sender, const AnsiString FileURL, int ErrorCode, bool &ContinueUpgrade);

typedef void __fastcall (__closure *TAUProgressEvent)(System::TObject* Sender, const AnsiString FileURL, int FileSize, int BytesRead, int ElapsedTime, int EstimatedTimeLeft, Byte PercentsDone, Byte TotalPercentsDone, float TransferRate);

class DELPHICLASS TauAutoUpgrader;
class PASCALIMPLEMENTATION TauAutoUpgrader : public Auhttp::TauCustomHTTP 
{
	typedef Auhttp::TauCustomHTTP inherited;
	
private:
	bool FAutoCheck;
	TauAutoUpgraderInfo* FInfoFile;
	AnsiString FInfoFileURL;
	TauAutoUpgraderVersionControl FVersionControl;
	AnsiString FVersionDate;
	bool FVersionDateAutoSet;
	AnsiString FVersionNumber;
	TacMiscFilesUpgradeBehavior FMiscFilesUpgrade;
	AnsiString FRestartParams;
	TauAutoUpgraderShowMessages FShowMessages;
	TauAutoUpgraderWizard* FWizard;
	TAUBeginUpgradeEvent FOnBeginUpgrade;
	Classes::TNotifyEvent FOnEndUpgrade;
	Classes::TNotifyEvent FOnLaterUpgrade;
	TAUProgressEvent FOnProgress;
	TAUFileStartEvent FOnFileStart;
	TAUFileDoneEvent FOnFileDone;
	Classes::TNotifyEvent FOnDoOwnCloseAppMethod;
	Classes::TNotifyEvent FOnAfterRestart;
	Classes::TNotifyEvent FOnAborted;
	Classes::TNotifyEvent FOnConnLost;
	TAUHostUnreachableEvent FOnHostUnreachable;
	Classes::TNotifyEvent FOnNoUpdateAvailable;
	Classes::TNotifyEvent FOnNoInfoFile;
	TAULostFileEvent FOnLostFile;
	Auhttp::TauHTTPPasswordRequestEvent FOnPasswordRequest;
	unsigned FHandle;
	bool FAborted;
	bool FAutoCheckDone;
	bool FIsAutoCheck;
	bool FQueryInfoStage;
	TacUpgradeMethod FUpdateMethod;
	Classes::TStringList* FDownloadQueue;
	AnsiString FCurrentFileName;
	System::TDateTime FCurrentFileTime;
	int FCurrentFileIndex;
	bool FRestarting;
	void __fastcall SetAutoCheck(bool Value);
	void __fastcall SetQueryInfoStage(bool Value);
	void __fastcall SetRestartParams(const AnsiString Value);
	void __fastcall SetVersionDateAutoSet(bool Value);
	bool __fastcall IsDefaultParams(void);
	void __fastcall HTTPHeaderInfo(System::TObject* Sender, const AnsiString RawHeadersCRLF, const AnsiString ContentType, const AnsiString ContentLanguage, const AnsiString ContentEncoding, const AnsiString Location, int ContentLength, System::TDateTime Date, System::TDateTime LastModified, System::TDateTime Expires, bool &ContinueDownload);
	void __fastcall HTTPDone(System::TObject* Sender, const AnsiString ContentType, int FileSize, Classes::TStream* Stream);
	void __fastcall HTTPDoneInterrupted(System::TObject* Sender);
	void __fastcall HTTPProgress(System::TObject* Sender, const AnsiString ContentType, int FileSize, int BytesRead, int ElapsedTime, int EstimatedTimeLeft, Byte PercentsDone, float TransferRate, Classes::TStream* Stream);
	void __fastcall HTTPConnLost(System::TObject* Sender, const AnsiString ContentType, int FileSize, int BytesRead, Classes::TStream* Stream);
	void __fastcall HTTPError(System::TObject* Sender, int ErrorCode, Classes::TStream* Stream);
	void __fastcall HTTPHostUnreachable(System::TObject* Sender);
	void __fastcall HTTPPasswordRequest(System::TObject* Sender, const AnsiString Realm, bool &TryAgain);
	void __fastcall ParseInfoFile(Classes::TStream* Stream);
	void __fastcall DoUpgrade(bool FirstFile);
	void __fastcall SafeTerminate(void);
	void __fastcall Relaunch(const AnsiString ParamStr);
	void __fastcall UpdateTimer(void);
	void __fastcall DeleteTemporaryFiles(void);
	
protected:
	virtual void __fastcall WndProc(Messages::TMessage &Message);
	
public:
	__fastcall virtual TauAutoUpgrader(Classes::TComponent* aOwner);
	__fastcall virtual ~TauAutoUpgrader(void);
	virtual void __fastcall Loaded(void);
	void __fastcall CheckUpdate(void);
	HIDESBASE void __fastcall Abort(void);
	void __fastcall RestartApplication(const AnsiString Params = "");
	__property bool QInfoStage = {read=FQueryInfoStage, write=SetQueryInfoStage, nodefault};
	__property bool Restarting = {read=FRestarting, nodefault};
	
__published:
	__property Proxy ;
	__property ThreadPriority  = {default=3};
	__property TransferBufferSize  = {default=4096};
	__property AnsiString HTTPUsername = {read=FLoginUsername, write=FLoginUsername, stored=false};
	__property AnsiString HTTPPassword = {read=FLoginPassword, write=FLoginPassword, stored=false};
	__property OnProxyAuthenticationRequest ;
	__property bool AutoCheck = {read=FAutoCheck, write=SetAutoCheck, default=0};
	__property TauAutoUpgraderInfo* InfoFile = {read=FInfoFile, write=FInfoFile};
	__property AnsiString InfoFileURL = {read=FInfoFileURL, write=FInfoFileURL};
	__property AnsiString RestartParams = {read=FRestartParams, write=SetRestartParams, stored=IsDefaultParams};
	__property TacMiscFilesUpgradeBehavior MiscFilesUpgrade = {read=FMiscFilesUpgrade, write=FMiscFilesUpgrade, default=0};
	__property TauAutoUpgraderVersionControl VersionControl = {read=FVersionControl, write=FVersionControl, default=0};
	__property AnsiString VersionDate = {read=FVersionDate, write=FVersionDate};
	__property bool VersionDateAutoSet = {read=FVersionDateAutoSet, write=SetVersionDateAutoSet, nodefault};
	__property AnsiString VersionNumber = {read=FVersionNumber, write=FVersionNumber};
	__property TauAutoUpgraderShowMessages ShowMessages = {read=FShowMessages, write=FShowMessages, default=75};
	__property TauAutoUpgraderWizard* Wizard = {read=FWizard, write=FWizard};
	__property TAUBeginUpgradeEvent OnBeginUpgrade = {read=FOnBeginUpgrade, write=FOnBeginUpgrade};
	__property Classes::TNotifyEvent OnEndUpgrade = {read=FOnEndUpgrade, write=FOnEndUpgrade};
	__property Classes::TNotifyEvent OnLaterUpgrade = {read=FOnLaterUpgrade, write=FOnLaterUpgrade};
	__property TAUProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	__property TAUFileStartEvent OnFileStart = {read=FOnFileStart, write=FOnFileStart};
	__property TAUFileDoneEvent OnFileDone = {read=FOnFileDone, write=FOnFileDone};
	__property Classes::TNotifyEvent OnDoOwnCloseAppMethod = {read=FOnDoOwnCloseAppMethod, write=FOnDoOwnCloseAppMethod};
	__property Classes::TNotifyEvent OnAfterRestart = {read=FOnAfterRestart, write=FOnAfterRestart};
	__property Classes::TNotifyEvent OnAborted = {read=FOnAborted, write=FOnAborted};
	__property Classes::TNotifyEvent OnConnLost = {read=FOnConnLost, write=FOnConnLost};
	__property TAUHostUnreachableEvent OnHostUnreachable = {read=FOnHostUnreachable, write=FOnHostUnreachable};
	__property Classes::TNotifyEvent OnNoUpdateAvailable = {read=FOnNoUpdateAvailable, write=FOnNoUpdateAvailable};
	__property Classes::TNotifyEvent OnNoInfoFile = {read=FOnNoInfoFile, write=FOnNoInfoFile};
	__property TAULostFileEvent OnLostFile = {read=FOnLostFile, write=FOnLostFile};
	__property Auhttp::TauHTTPPasswordRequestEvent OnPasswordRequest = {read=FOnPasswordRequest, write=FOnPasswordRequest};
};


//-- var, const, procedure ---------------------------------------------------
static const Word LanguageResEntryPoint = 0xa028;
static const Shortint auWizardTitle = 0x0;
static const Shortint auDownloadingFiles = 0x1;
static const Shortint auUpdateCompleted = 0x2;
static const Shortint auCurrentFile = 0x3;
static const Shortint auAllFiles = 0x4;
static const Shortint auDownloadingFrom = 0x5;
static const Shortint auFileSize = 0x6;
static const Shortint auTransferRate = 0x7;
static const Shortint auEstimatedTime = 0x8;
static const Shortint auDownloadingOf = 0x9;
static const Shortint auSuccessUpdate = 0xa;
static const Shortint auEnterPassword = 0xb;
static const Shortint auUsername = 0xc;
static const Shortint auPassword = 0xd;
static const Shortint auYes = 0xe;
static const Shortint auNo = 0xf;
static const Shortint auOK = 0x10;
static const Shortint auCancel = 0x11;
static const Shortint auNext = 0x12;
static const Shortint auLater = 0x13;
static const Shortint auWarning = 0x14;
static const Shortint auError = 0x15;
static const Shortint auPreparing = 0x16;
static const Shortint auWelcome = 0x17;
static const Shortint auNoUpdate = 0x18;
static const Shortint auNoInfoFile = 0x19;
static const Shortint auHostUnreachable = 0x1a;
static const Shortint auInterrupt = 0x1b;
static const Shortint auLostFile = 0x1c;
static const Shortint auPasswordRequired = 0x1d;
static const Shortint auConnectionLost = 0x1e;
static const Word auAutoUpgraderStr = 0xa027;
static const Word auDelphiStr = 0xa026;
static const Word auAppTitle = 0xa025;
extern PACKAGE System::TDateTime __fastcall AUDateToDate(const AnsiString AUDate);
extern PACKAGE AnsiString __fastcall DateToAUDate(const System::TDateTime Date);
extern PACKAGE AnsiString __fastcall AULangStr(int Ident);
extern PACKAGE AnsiString __fastcall AUFmtLangStr(int Ident, const System::TVarRec * Args, const int Args_Size);

}	/* namespace Auautoupgrader */
using namespace Auautoupgrader;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// auAutoUpgrader
