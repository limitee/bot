// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'auHTTP.pas' rev: 6.00

#ifndef auHTTPHPP
#define auHTTPHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <auThread.hpp>	// Pascal unit
#include <WinInet.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Auhttp
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TauLoginComponent;
class PASCALIMPLEMENTATION TauLoginComponent : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	void __fastcall ReadData(Classes::TStream* Stream);
	void __fastcall WriteData(Classes::TStream* Stream);
	
protected:
	AnsiString FLoginUsername;
	AnsiString FLoginPassword;
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
public:
	#pragma option push -w-inl
	/* TComponent.Create */ inline __fastcall virtual TauLoginComponent(Classes::TComponent* AOwner) : Classes::TComponent(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TauLoginComponent(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TauHTTPProgressEvent)(System::TObject* Sender, const AnsiString ContentType, int DataSize, int BytesRead, int ElapsedTime, int EstimatedTimeLeft, Byte PercentsDone, float TransferRate, Classes::TStream* Stream);

typedef void __fastcall (__closure *TauHTTPUploadProgressEvent)(System::TObject* Sender, int DataSize, int BytesTransferred, int ElapsedTime, int EstimatedTimeLeft, Byte PercentsDone, float TransferRate);

typedef void __fastcall (__closure *TauHTTPUploadFieldRequest)(System::TObject* Sender, Word FileIndex, Classes::TStream* UploadStream, AnsiString &FieldName, AnsiString &FileName);

typedef void __fastcall (__closure *TauHTTPHeaderInfoEvent)(System::TObject* Sender, const AnsiString RawHeadersCRLF, const AnsiString ContentType, const AnsiString ContentLanguage, const AnsiString ContentEncoding, const AnsiString Location, int ContentLength, System::TDateTime Date, System::TDateTime LastModified, System::TDateTime Expires, bool &ContinueDownload);

typedef void __fastcall (__closure *TauHTTPStatusChanged)(System::TObject* Sender, unsigned StatusID, const AnsiString StatusStr);

typedef void __fastcall (__closure *TauHTTPRedirected)(System::TObject* Sender, const AnsiString NewURL);

typedef void __fastcall (__closure *TauHTTPDoneEvent)(System::TObject* Sender, const AnsiString ContentType, int FileSize, Classes::TStream* Stream);

typedef void __fastcall (__closure *TauHTTPConnLostEvent)(System::TObject* Sender, const AnsiString ContentType, int FileSize, int BytesRead, Classes::TStream* Stream);

typedef void __fastcall (__closure *TauHTTPErrorEvent)(System::TObject* Sender, int ErrorCode, Classes::TStream* Stream);

typedef void __fastcall (__closure *TauHTTPPasswordRequestEvent)(System::TObject* Sender, const AnsiString Realm, bool &TryAgain);

typedef void __fastcall (__closure *TauHTTPProxyAuthenticationEvent)(System::TObject* Sender, AnsiString &ProxyUsername, AnsiString &ProxyPassword, bool &TryAgain);

#pragma option push -b-
enum TauHTTPPOSTMethod { pmFormURLEncoded, pmMultipartFormData };
#pragma option pop

#pragma option push -b-
enum TauHTTPRequestMethod { rmAutoDetect, rmGET, rmPOST };
#pragma option pop

#pragma option push -b-
enum TauHTTPAccessType { atPreconfig, atDirect, atUseProxy };
#pragma option pop

class DELPHICLASS TauHTTPProxy;
class PASCALIMPLEMENTATION TauHTTPProxy : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TauHTTPAccessType FAccessType;
	int FProxyPort;
	AnsiString FProxyServer;
	AnsiString FProxyBypass;
	bool __fastcall IsUseProxy(void);
	
public:
	__fastcall TauHTTPProxy(void);
	
__published:
	__property TauHTTPAccessType AccessType = {read=FAccessType, write=FAccessType, default=0};
	__property int ProxyPort = {read=FProxyPort, write=FProxyPort, default=8080};
	__property AnsiString ProxyServer = {read=FProxyServer, write=FProxyServer, stored=IsUseProxy};
	__property AnsiString ProxyBypass = {read=FProxyBypass, write=FProxyBypass, stored=IsUseProxy};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TauHTTPProxy(void) { }
	#pragma option pop
	
};


class DELPHICLASS TauHTTPRange;
class PASCALIMPLEMENTATION TauHTTPRange : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FStartRange;
	int FEndRange;
	
__published:
	__property int StartRange = {read=FStartRange, write=FStartRange, default=0};
	__property int EndRange = {read=FEndRange, write=FEndRange, default=0};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TauHTTPRange(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TauHTTPRange(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class DELPHICLASS TauHTTPTimeouts;
class PASCALIMPLEMENTATION TauHTTPTimeouts : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	unsigned FConnectTimeout;
	unsigned FReceiveTimeout;
	unsigned FSendTimeout;
	
__published:
	__property unsigned ConnectTimeout = {read=FConnectTimeout, write=FConnectTimeout, default=0};
	__property unsigned ReceiveTimeout = {read=FReceiveTimeout, write=FReceiveTimeout, default=0};
	__property unsigned SendTimeout = {read=FSendTimeout, write=FSendTimeout, default=0};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TauHTTPTimeouts(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TauHTTPTimeouts(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


typedef int TauBufferSize;

class DELPHICLASS TauCustomHTTP;
class PASCALIMPLEMENTATION TauCustomHTTP : public TauLoginComponent 
{
	typedef TauLoginComponent inherited;
	
private:
	Classes::TStrings* FAddHeaders;
	AnsiString FAcceptTypes;
	AnsiString FAgent;
	AnsiString FOutputFileName;
	bool FHideOutputFile;
	AnsiString FURL;
	AnsiString FPostData;
	AnsiString FReferer;
	TauHTTPRange* FRange;
	TauHTTPTimeouts* FTimeouts;
	TauBufferSize FTransferBufferSize;
	TauHTTPPOSTMethod FPOSTMethod;
	TauHTTPRequestMethod FRequestMethod;
	TauHTTPProxy* FProxy;
	bool FUseCache;
	bool FUseCookies;
	bool FWorkOffline;
	TauHTTPHeaderInfoEvent FOnHeaderInfo;
	TauHTTPDoneEvent FOnDone;
	Classes::TNotifyEvent FOnDoneInterrupted;
	TauHTTPProgressEvent FOnProgress;
	TauHTTPStatusChanged FOnStatusChanged;
	TauHTTPRedirected FOnRedirected;
	TauHTTPUploadProgressEvent FOnUploadProgress;
	TauHTTPUploadFieldRequest FOnUploadFieldRequest;
	Classes::TNotifyEvent FOnAnyError;
	Classes::TNotifyEvent FOnAborted;
	TauHTTPConnLostEvent FOnConnLost;
	Classes::TNotifyEvent FOnHostUnreachable;
	TauHTTPErrorEvent FOnHTTPError;
	TauHTTPPasswordRequestEvent FOnPasswordRequest;
	TauHTTPProxyAuthenticationEvent FOnProxyAuthenticationRequest;
	Classes::TNotifyEvent FOnWaitTimeoutExpired;
	Authread::TauCustomThread* FThread;
	Classes::TStream* HTTPStream;
	int HTTPErrorCode;
	bool HTTPSuccess;
	bool HTTPTryAgain;
	bool HTTPContinueDownload;
	AnsiString HTTPRawHeadersCRLF;
	AnsiString HTTPContentType;
	AnsiString HTTPContentLanguage;
	AnsiString HTTPContentEncoding;
	AnsiString HTTPLocation;
	System::TDateTime HTTPDate;
	System::TDateTime HTTPLastModified;
	System::TDateTime HTTPExpires;
	void *HTTPData;
	AnsiString HTTPProxyUsername;
	AnsiString HTTPProxyPassword;
	unsigned HTTPFileSize;
	unsigned HTTPBytesTransferred;
	unsigned HTTPStartTime;
	AnsiString HTTPUploadRequestHeader;
	Byte ProgressPercentsDone;
	unsigned ProgressElapsedTime;
	unsigned ProgressEstimatedTime;
	float ProgressTransferRate;
	void *hSession;
	void *hConnect;
	void *hRequest;
	unsigned hFile;
	void __fastcall SetAddHeaders(Classes::TStrings* Value);
	bool __fastcall GetSuspended(void);
	void __fastcall SetSuspended(bool Value);
	Classes::TThreadPriority __fastcall GetThreadPriority(void);
	void __fastcall SetThreadPriority(Classes::TThreadPriority Value);
	bool __fastcall GetWaitThread(void);
	void __fastcall SetWaitThread(bool Value);
	int __fastcall GetWaitTimeout(void);
	void __fastcall SetWaitTimeout(int Value);
	bool __fastcall GetBusy(void);
	bool __fastcall GetFreeOnTerminate(void);
	void __fastcall SetFreeOnTerminate(bool Value);
	AnsiString __fastcall GetFileName();
	AnsiString __fastcall GetHostName();
	bool __fastcall IsNotDefaultAcceptTypes(void);
	void __fastcall PrepareProgressParams(void);
	void __fastcall CloseHTTPHandles(void);
	void __fastcall ReleaseHTTPStream(void);
	void __fastcall ThreadExecute(System::TObject* Sender);
	void __fastcall ThreadException(System::TObject* Sender);
	void __fastcall ThreadDone(System::TObject* Sender);
	void __fastcall ThreadWaitTimeoutExpired(System::TObject* Sender);
	void __fastcall CallHeaderInfo(void);
	void __fastcall CallProgress(void);
	void __fastcall CallUploadProgress(void);
	void __fastcall CallPasswordRequest(void);
	void __fastcall CallProxyAuthenticationRequest(void);
	
protected:
	void __fastcall DoAnyError(void);
	
public:
	__fastcall virtual TauCustomHTTP(Classes::TComponent* aOwner);
	__fastcall virtual ~TauCustomHTTP(void);
	bool __fastcall Read(void);
	bool __fastcall Upload(Word NumberOfFields);
	void __fastcall Abort(void);
	__property AnsiString Username = {read=FLoginUsername, write=FLoginUsername, stored=false};
	__property AnsiString Password = {read=FLoginPassword, write=FLoginPassword, stored=false};
	__property bool Busy = {read=GetBusy, nodefault};
	__property bool FreeOnTerminate = {read=GetFreeOnTerminate, write=SetFreeOnTerminate, nodefault};
	__property AnsiString FileName = {read=GetFileName};
	__property AnsiString HostName = {read=GetHostName};
	__property Authread::TauCustomThread* Thread = {read=FThread};
	__property AnsiString AcceptTypes = {read=FAcceptTypes, write=FAcceptTypes, stored=IsNotDefaultAcceptTypes};
	__property Classes::TStrings* AddHeaders = {read=FAddHeaders, write=SetAddHeaders};
	__property AnsiString Agent = {read=FAgent, write=FAgent};
	__property TauHTTPProxy* Proxy = {read=FProxy, write=FProxy};
	__property AnsiString OutputFileName = {read=FOutputFileName, write=FOutputFileName};
	__property bool HideOutputFile = {read=FHideOutputFile, write=FHideOutputFile, default=0};
	__property AnsiString URL = {read=FURL, write=FURL};
	__property bool UseCache = {read=FUseCache, write=FUseCache, default=1};
	__property bool UseCookies = {read=FUseCookies, write=FUseCookies, default=1};
	__property AnsiString POSTData = {read=FPostData, write=FPostData};
	__property TauHTTPRange* Range = {read=FRange, write=FRange};
	__property AnsiString Referer = {read=FReferer, write=FReferer};
	__property TauHTTPRequestMethod RequestMethod = {read=FRequestMethod, write=FRequestMethod, default=0};
	__property TauHTTPTimeouts* Timeouts = {read=FTimeouts, write=FTimeouts};
	__property TauBufferSize TransferBufferSize = {read=FTransferBufferSize, write=FTransferBufferSize, default=4096};
	__property bool WorkOffline = {read=FWorkOffline, write=FWorkOffline, default=0};
	__property bool Suspended = {read=GetSuspended, write=SetSuspended, nodefault};
	__property Classes::TThreadPriority ThreadPriority = {read=GetThreadPriority, write=SetThreadPriority, default=3};
	__property bool WaitThread = {read=GetWaitThread, write=SetWaitThread, default=0};
	__property int WaitTimeout = {read=GetWaitTimeout, write=SetWaitTimeout, default=0};
	__property TauHTTPHeaderInfoEvent OnHeaderInfo = {read=FOnHeaderInfo, write=FOnHeaderInfo};
	__property TauHTTPDoneEvent OnDone = {read=FOnDone, write=FOnDone};
	__property TauHTTPProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	__property TauHTTPStatusChanged OnStatusChanged = {read=FOnStatusChanged, write=FOnStatusChanged};
	__property TauHTTPRedirected OnRedirected = {read=FOnRedirected, write=FOnRedirected};
	__property TauHTTPUploadProgressEvent OnUploadProgress = {read=FOnUploadProgress, write=FOnUploadProgress};
	__property TauHTTPUploadFieldRequest OnUploadFieldRequest = {read=FOnUploadFieldRequest, write=FOnUploadFieldRequest};
	__property Classes::TNotifyEvent OnAnyError = {read=FOnAnyError, write=FOnAnyError};
	__property Classes::TNotifyEvent OnAborted = {read=FOnAborted, write=FOnAborted};
	__property TauHTTPConnLostEvent OnConnLost = {read=FOnConnLost, write=FOnConnLost};
	__property Classes::TNotifyEvent OnDoneInterrupted = {read=FOnDoneInterrupted, write=FOnDoneInterrupted};
	__property TauHTTPPasswordRequestEvent OnPasswordRequest = {read=FOnPasswordRequest, write=FOnPasswordRequest};
	__property TauHTTPProxyAuthenticationEvent OnProxyAuthenticationRequest = {read=FOnProxyAuthenticationRequest, write=FOnProxyAuthenticationRequest};
	__property Classes::TNotifyEvent OnHostUnreachable = {read=FOnHostUnreachable, write=FOnHostUnreachable};
	__property TauHTTPErrorEvent OnHTTPError = {read=FOnHTTPError, write=FOnHTTPError};
	__property Classes::TNotifyEvent OnWaitTimeoutExpired = {read=FOnWaitTimeoutExpired, write=FOnWaitTimeoutExpired};
};


class DELPHICLASS TauHTTP;
class PASCALIMPLEMENTATION TauHTTP : public TauCustomHTTP 
{
	typedef TauCustomHTTP inherited;
	
__published:
	__property AcceptTypes ;
	__property AddHeaders ;
	__property Agent ;
	__property Proxy ;
	__property URL ;
	__property UseCache  = {default=1};
	__property UseCookies  = {default=1};
	__property Username ;
	__property OutputFileName ;
	__property HideOutputFile  = {default=0};
	__property Password ;
	__property POSTData ;
	__property Range ;
	__property Referer ;
	__property RequestMethod  = {default=0};
	__property Timeouts ;
	__property ThreadPriority  = {default=3};
	__property TransferBufferSize  = {default=4096};
	__property WaitThread  = {default=0};
	__property WaitTimeout  = {default=0};
	__property WorkOffline  = {default=0};
	__property OnHeaderInfo ;
	__property OnDone ;
	__property OnDoneInterrupted ;
	__property OnProgress ;
	__property OnRedirected ;
	__property OnUploadProgress ;
	__property OnUploadFieldRequest ;
	__property OnAnyError ;
	__property OnAborted ;
	__property OnConnLost ;
	__property OnHTTPError ;
	__property OnHostUnreachable ;
	__property OnPasswordRequest ;
	__property OnProxyAuthenticationRequest ;
	__property OnWaitTimeoutExpired ;
public:
	#pragma option push -w-inl
	/* TauCustomHTTP.Create */ inline __fastcall virtual TauHTTP(Classes::TComponent* aOwner) : TauCustomHTTP(aOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TauCustomHTTP.Destroy */ inline __fastcall virtual ~TauHTTP(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word auDefaultProxyPort = 0x1f90;
extern PACKAGE AnsiString __fastcall HTTPReadString(const AnsiString URL, int Timeout = 0x0);

}	/* namespace Auhttp */
using namespace Auhttp;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// auHTTP
