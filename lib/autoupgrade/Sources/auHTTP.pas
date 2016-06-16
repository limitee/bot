{*******************************************************************************

  Advanced Application Controls v2.4
  FILE: auHTTP.pas - auHTTP component. Used as base class for acAutoUpgrader
          in the AppControls v2.3 and later

  Copyright (c) 1998-2002 UtilMind Solutions
  All rights reserved.
  E-Mail: info@utilmind.com
  WWW: http://www.utilmind.com, http://www.appcontrols.com

  The entire contents of this file is protected by International Copyright
Laws. Unauthorized reproduction, reverse-engineering, and distribution of all
or any portion of the code contained in this file is strictly prohibited and
may result in severe civil and criminal penalties and will be prosecuted to
the maximum extent possible under the law.

*******************************************************************************}
{$I auDefines.inc}

unit auHTTP;

interface

uses
  Windows, Classes, WinInet,
  auThread;

const
  auDefaultProxyPort = 8080;

type
  { TauLoginComponent }
  TauLoginComponent = class(TComponent)
  private
    procedure ReadData(Stream: TStream);
    procedure WriteData(Stream: TStream);
  protected
    FLoginUsername, FLoginPassword: String;
      
    procedure DefineProperties(Filer: TFiler); override;
  end;

  { TauHTTP }
  TauHTTPProgressEvent = procedure(Sender: TObject; const ContentType: String;
                                   DataSize, BytesRead,
                                   ElapsedTime, EstimatedTimeLeft: Integer;
                                   PercentsDone: Byte; TransferRate: Single;
                                   Stream: TStream) of object;
{$IFNDEF IE3}
  TauHTTPUploadProgressEvent  = procedure(Sender: TObject;
                                   DataSize, BytesTransferred,
                                   ElapsedTime, EstimatedTimeLeft: Integer;
                                   PercentsDone: Byte; TransferRate: Single) of object;
  TauHTTPUploadFieldRequest   = procedure(Sender: TObject; FileIndex: Word; UploadStream: TStream; var FieldName, FileName: String) of object;
{$ENDIF}
  TauHTTPHeaderInfoEvent      = procedure(Sender: TObject; const RawHeadersCRLF, ContentType, ContentLanguage, ContentEncoding, Location: String;
                                   ContentLength: Integer; Date, LastModified, Expires: TDateTime; var ContinueDownload: Boolean) of object;
  TauHTTPStatusChanged        = procedure(Sender: TObject; StatusID: Cardinal; const StatusStr: String) of object;
  TauHTTPRedirected           = procedure(Sender: TObject; const NewURL: String) of object;
  TauHTTPDoneEvent            = procedure(Sender: TObject; const ContentType: String; FileSize: Integer; Stream: TStream) of object;
  TauHTTPConnLostEvent        = procedure(Sender: TObject; const ContentType: String; FileSize, BytesRead: Integer; Stream: TStream) of object;
  TauHTTPErrorEvent           = procedure(Sender: TObject; ErrorCode: Integer; Stream: TStream) of object;
  TauHTTPPasswordRequestEvent = procedure(Sender: TObject; const Realm: String; var TryAgain: Boolean) of object;
  TauHTTPProxyAuthenticationEvent = procedure(Sender: TObject; var ProxyUsername, ProxyPassword: String; var TryAgain: Boolean) of object;

{$IFNDEF IE3}
  TauHTTPPOSTMethod = (pmFormURLEncoded, pmMultipartFormData);
{$ENDIF}
  TauHTTPRequestMethod = (rmAutoDetect, rmGET, rmPOST);
  TauHTTPAccessType = (atPreconfig, atDirect, atUseProxy);
  TauHTTPProxy = class(TPersistent)
  private
    FAccessType: TauHTTPAccessType;
    FProxyPort: Integer;
    FProxyServer: String;
    FProxyBypass: String;

    function IsUseProxy: Boolean;
  public
    constructor Create;
  published
    property AccessType: TauHTTPAccessType read FAccessType write FAccessType default atPreconfig;
    property ProxyPort: Integer read FProxyPort write FProxyPort default auDefaultProxyPort;
    property ProxyServer: String read FProxyServer write FProxyServer stored IsUseProxy;
    property ProxyBypass: String read FProxyBypass write FProxyBypass stored IsUseProxy;
  end;

  TauHTTPRange = class(TPersistent)
  private
    FStartRange, FEndRange: Integer;
  published
    property StartRange: Integer read FStartRange write FStartRange default 0;
    property EndRange: Integer read FEndRange write FEndRange default 0;
  end;

  TauHTTPTimeouts = class(TPersistent)
  private
    FConnectTimeout, FReceiveTimeout, FSendTimeout: DWord;
  published
    property ConnectTimeout: DWord read FConnectTimeout write FConnectTimeout default 0;
    property ReceiveTimeout: DWord read FReceiveTimeout write FReceiveTimeout default 0;
    property SendTimeout: DWord read FSendTimeout write FSendTimeout default 0;
  end;

  TauBufferSize = 255..MaxInt;  
  TauCustomHTTP = class(TauLoginComponent)
  private
    FAddHeaders: TStrings;
    FAcceptTypes, FAgent,
    FOutputFileName: String;
    FHideOutputFile: Boolean;
    FURL, FPostData, FReferer: String;
    FRange: TauHTTPRange;
    FTimeouts: TauHTTPTimeouts;
    FTransferBufferSize: TauBufferSize;
{$IFNDEF IE3}
    FPOSTMethod: TauHTTPPOSTMethod;
{$ENDIF}
    FRequestMethod: TauHTTPRequestMethod;
    FProxy: TauHTTPProxy;
    FUseCache, FUseCookies,
    FWorkOffline: Boolean;

    // success events
    FOnHeaderInfo: TauHTTPHeaderInfoEvent;
    FOnDone: TauHTTPDoneEvent;
    FOnDoneInterrupted: TNotifyEvent;
    FOnProgress: TauHTTPProgressEvent;
    FOnStatusChanged: TauHTTPStatusChanged;
    FOnRedirected: TauHTTPRedirected;
{$IFNDEF IE3}
    FOnUploadProgress: TauHTTPUploadProgressEvent;
    FOnUploadFieldRequest: TauHTTPUploadFieldRequest;
{$ENDIF}
    // error events
    FOnAnyError: TNotifyEvent;
    FOnAborted: TNotifyEvent;
    FOnConnLost: TauHTTPConnLostEvent;
    FOnHostUnreachable: TNotifyEvent;      // no connection
    FOnHTTPError: TauHTTPErrorEvent;       // read error
    FOnPasswordRequest: TauHTTPPasswordRequestEvent;
    FOnProxyAuthenticationRequest: TauHTTPProxyAuthenticationEvent;
    FOnWaitTimeoutExpired: TNotifyEvent; 

    // internal variables
    FThread: TauCustomThread;
    HTTPStream: TStream;
    HTTPErrorCode: Integer;
    HTTPSuccess, HTTPTryAgain, HTTPContinueDownload: Boolean;
    HTTPRawHeadersCRLF, HTTPContentType,
    HTTPContentLanguage, HTTPContentEncoding, HTTPLocation: String;
    HTTPDate, HTTPLastModified, HTTPExpires: TDateTime;
    HTTPData: Pointer; // read buffer
    HTTPProxyUsername, HTTPProxyPassword: String;
    HTTPFileSize, HTTPBytesTransferred, HTTPStartTime: Cardinal;
{$IFNDEF IE3}
    HTTPUploadRequestHeader: String;
{$ENDIF}
    // for OnProgres/OnUploadProgress events
    ProgressPercentsDone: Byte;
    ProgressElapsedTime, ProgressEstimatedTime: Cardinal;
    ProgressTransferRate: Single;

    // WinInet handles
    hSession, hConnect, hRequest: hInternet;
    hFile: hFile;

    procedure SetAddHeaders(Value: TStrings);
    function  GetSuspended: Boolean;
    procedure SetSuspended(Value: Boolean);
    function  GetThreadPriority: TThreadPriority;
    procedure SetThreadPriority(Value: TThreadPriority);
    function  GetWaitThread: Boolean;
    procedure SetWaitThread(Value: Boolean);
    function  GetWaitTimeout: Integer;
    procedure SetWaitTimeout(Value: Integer);
    function  GetBusy: Boolean;
    function  GetFreeOnTerminate: Boolean;
    procedure SetFreeOnTerminate(Value: Boolean);
    function  GetFileName: String;
    function  GetHostName: String;

    function  IsNotDefaultAcceptTypes: Boolean;

    procedure PrepareProgressParams;
    procedure CloseHTTPHandles;
    procedure ReleaseHTTPStream;

    // thread management
    procedure ThreadExecute(Sender: TObject);
    procedure ThreadException(Sender: TObject);
    procedure ThreadDone(Sender: TObject);
    procedure ThreadWaitTimeoutExpired(Sender: TObject);

    // synchronized methods
    procedure CallHeaderInfo;
    procedure CallProgress;
{$IFNDEF IE3}
    procedure CallUploadProgress;
{$ENDIF}
    procedure CallPasswordRequest;
    procedure CallProxyAuthenticationRequest;
  protected
    procedure DoAnyError;
  public
    constructor Create(aOwner: TComponent); override;
    destructor Destroy; override;

    // public methods
    function  Read: Boolean;
{$IFNDEF IE3}
    function  Upload(NumberOfFields: Word): Boolean;
{$ENDIF}
    procedure Abort;

    // from TauLoginComponent
    property Username: String read FLoginUsername write FLoginUsername stored False;
    property Password: String read FLoginPassword write FLoginPassword stored False;

    // optional properties
    property Busy: Boolean read GetBusy;
    property FreeOnTerminate: Boolean read GetFreeOnTerminate write SetFreeOnTerminate;
    property FileName: String read GetFileName;
    property HostName: String read GetHostName;
    property Thread: TauCustomThread read FThread;

    // public properties
    property AcceptTypes: String read FAcceptTypes write FAcceptTypes stored IsNotDefaultAcceptTypes;
    property AddHeaders: TStrings read FAddHeaders write SetAddHeaders;
    property Agent: String read FAgent write FAgent;
    property Proxy: TauHTTPProxy read FProxy write FProxy;
    property OutputFileName: String read FOutputFileName write FOutputFileName;
    property HideOutputFile: Boolean read FHideOutputFile write FHideOutputFile default False;
    property URL: String read FURL write FURL;
    property UseCache: Boolean read FUseCache write FUseCache default True;
    property UseCookies: Boolean read FUseCookies write FUseCookies default True;
    property POSTData: String read FPOSTData write FPOSTData;
    property Range: TauHTTPRange read FRange write FRange;
    property Referer: String read FReferer write FReferer;
    property RequestMethod: TauHTTPRequestMethod read FRequestMethod write FRequestMethod default rmAutoDetect;
    property Timeouts: TauHTTPTimeouts read FTimeouts write FTimeouts;
    property TransferBufferSize: TauBufferSize read FTransferBufferSize write FTransferBufferSize default 4096;
    property WorkOffline: Boolean read FWorkOffline write FWorkOffline default False;

    // thread properties
    property Suspended: Boolean read GetSuspended write SetSuspended;
    property ThreadPriority: TThreadPriority read GetThreadPriority write SetThreadPriority default tpNormal;
    property WaitThread: Boolean read GetWaitThread write SetWaitThread default False;
    property WaitTimeout: Integer read GetWaitTimeout write SetWaitTimeout default 0;

    // public events
    property OnHeaderInfo: TauHTTPHeaderInfoEvent read FOnHeaderInfo write FOnHeaderInfo;    
    property OnDone: TauHTTPDoneEvent read FOnDone write FOnDone;
    property OnProgress: TauHTTPProgressEvent read FOnProgress write FOnProgress;
    property OnStatusChanged: TauHTTPStatusChanged read FOnStatusChanged write FOnStatusChanged;
    property OnRedirected: TauHTTPRedirected read FOnRedirected write FOnRedirected;
{$IFNDEF IE3}
    property OnUploadProgress: TauHTTPUploadProgressEvent read FOnUploadProgress write FOnUploadProgress;
    property OnUploadFieldRequest: TauHTTPUploadFieldRequest read FOnUploadFieldRequest write FOnUploadFieldRequest;
{$ENDIF}

    property OnAnyError: TNotifyEvent read FOnAnyError write FOnAnyError;
    property OnAborted: TNotifyEvent read FOnAborted write FOnAborted;
    property OnConnLost: TauHTTPConnLostEvent read FOnConnLost write FOnConnLost;
    property OnDoneInterrupted: TNotifyEvent read FOnDoneInterrupted write FOnDoneInterrupted;
    property OnPasswordRequest: TauHTTPPasswordRequestEvent read FOnPasswordRequest write FOnPasswordRequest;
    property OnProxyAuthenticationRequest: TauHTTPProxyAuthenticationEvent read FOnProxyAuthenticationRequest write FOnProxyAuthenticationRequest;
    property OnHostUnreachable: TNotifyEvent read FOnHostUnreachable write FOnHostUnreachable;
    property OnHTTPError: TauHTTPErrorEvent read FOnHTTPError write FOnHTTPError;
    property OnWaitTimeoutExpired: TNotifyEvent read FOnWaitTimeoutExpired write FOnWaitTimeoutExpired;
  end;

  TauHTTP = class(TauCustomHTTP)
  published
    property AcceptTypes;
    property AddHeaders;
    property Agent;
    property Proxy;
    property URL;
    property UseCache;
    property UseCookies;
    property Username;
    property OutputFileName;
    property HideOutputFile;
    property Password;
    property POSTData;
    property Range;
    property Referer;
    property RequestMethod;
//    property Suspended;
    property Timeouts;
    property ThreadPriority;
    property TransferBufferSize;
    property WaitThread;
    property WaitTimeout;
    property WorkOffline;

    // success
    property OnHeaderInfo;
    property OnDone;
    property OnDoneInterrupted;
    property OnProgress;
//    property OnStatusChanged;
    property OnRedirected;
{$IFNDEF IE3}
    property OnUploadProgress;
    property OnUploadFieldRequest;
{$ENDIF}
    // errors
    property OnAnyError;
    property OnAborted;
    property OnConnLost;
    property OnHTTPError;
    property OnHostUnreachable;
    property OnPasswordRequest;
    property OnProxyAuthenticationRequest;
    property OnWaitTimeoutExpired;    
  end;

function HTTPReadString(const URL: String; Timeout: Integer {$IFDEF D4} = 0 {$ENDIF}): String;

{$IFDEF USEINTERNAL}
// routines to hide the HTTP username and password in the DFM
procedure EncryptUP(Stream: TStream; const U, P: String); // encrypts username/password and puts to stream
procedure DecryptUP(Stream: TStream; var U, P: String); // retrieves username/password from stream and decrypts them
{$ENDIF}

implementation

uses {$IFDEF TRIAL} Forms, {$ENDIF} SysUtils, auUtils;

{$IFDEF TRIAL}
var
  NotifyDone: Boolean = False;
{$ENDIF}

const
  DEF_ACCEPT_TYPES = 'text/html, */*';
  DEF_CONTENT_TYPE = 'Content-Type: application/x-www-form-urlencoded';
  DEF_CONTENT_TYPE_SIZE = 47;
  {$IFNDEF D4}
  INTERNET_FLAG_PRAGMA_NOCACHE           = $00000100;
  INTERNET_FLAG_NO_COOKIES               = $00080000;
  INTERNET_OPTION_PROXY_USERNAME         = 43;
  INTERNET_OPTION_PROXY_PASSWORD         = 44;
  INTERNET_STATUS_INTERMEDIATE_RESPONSE  = 120;
  INTERNET_STATUS_STATE_CHANGE           = 200;
  {$IFNDEF IE3}
  HSR_INITIATE    = $00000008;
  {$ENDIF}
  {$ENDIF}

  HostUnreachableCode = -1;

{$IFNDEF IE3}
{$IFNDEF D5}
{ INTERNET_BUFFERS - combines headers and data. May be chained for e.g. file }
{ upload or scatter/gather operations. For chunked read/write, lpcszHeader }
{ contains the chunked-ext }
type
  PInternetBuffers = ^INTERNET_BUFFERS;
  INTERNET_BUFFERS = record
    dwStructSize: DWORD;      { used for API versioning. Set to sizeof(INTERNET_BUFFERS) }
    Next: PInternetBuffers;   { chain of buffers }
    lpcszHeader: PAnsiChar;   { pointer to headers (may be NULL) }
    dwHeadersLength: DWORD;   { length of headers if not NULL }
    dwHeadersTotal: DWORD;    { size of headers if not enough buffer }
    lpvBuffer: Pointer;       { pointer to data buffer (may be NULL) }
    dwBufferLength: DWORD;    { length of data buffer if not NULL }
    dwBufferTotal: DWORD;     { total size of chunk, or content-length if not chunked }
    dwOffsetLow: DWORD;       { used for read-ranges (only used in HttpSendRequest2) }
    dwOffsetHigh: DWORD;
  end;

function HttpSendRequestEx(hRequest: HINTERNET; lpBuffersIn: PInternetBuffers;
    lpBuffersOut: PInternetBuffers;
    dwFlags: DWORD; dwContext: DWORD): BOOL; stdcall external 'wininet.dll' name 'HttpSendRequestExA';
function HttpEndRequest(hRequest: HINTERNET;
  lpBuffersOut: PInternetBuffers; dwFlags: DWORD;
  dwContext: DWORD): BOOL; stdcall external 'wininet.dll' name 'HttpEndRequestA';
{$ENDIF D5}
{$ENDIF IE3}


// HTTP Status Callback
procedure GetURLStatusCallback(InternetSession: hInternet; Context, InternetStatus: DWord;
  StatusInformation: Pointer; StatusInformationLength: DWord); stdcall;
var
  NewURL, StatusStr: String;
begin
  with TauHTTP(Context) do
   begin
    if Assigned(FOnStatusChanged) then
     begin
      case InternetStatus of
        INTERNET_STATUS_RESOLVING_NAME: StatusStr := 'Resolving name';
        INTERNET_STATUS_NAME_RESOLVED: StatusStr := 'Name resolved';
        INTERNET_STATUS_CONNECTING_TO_SERVER: StatusStr := 'Connecting to server';
        INTERNET_STATUS_CONNECTED_TO_SERVER: StatusStr := 'Connected';
        INTERNET_STATUS_SENDING_REQUEST: StatusStr := 'Sending Request';
        INTERNET_STATUS_REQUEST_SENT: StatusStr := 'Request sent';
        INTERNET_STATUS_RECEIVING_RESPONSE: StatusStr := 'Receiving response';
        INTERNET_STATUS_RESPONSE_RECEIVED: StatusStr := 'Response received';
        INTERNET_STATUS_CTL_RESPONSE_RECEIVED: StatusStr := 'CTL Response received';
        INTERNET_STATUS_PREFETCH: StatusStr := 'Prefetch';
        INTERNET_STATUS_CLOSING_CONNECTION: StatusStr := 'Closing connection';
        INTERNET_STATUS_CONNECTION_CLOSED: StatusStr := 'Connection closed';
        INTERNET_STATUS_HANDLE_CREATED: StatusStr := 'Handle created';
        INTERNET_STATUS_HANDLE_CLOSING: StatusStr := 'Handle closing';
        INTERNET_STATUS_REQUEST_COMPLETE: StatusStr := 'Request complete';
        INTERNET_STATUS_REDIRECT: StatusStr := 'Redirect';
        INTERNET_STATUS_INTERMEDIATE_RESPONSE: StatusStr := 'Intermediate response';
        INTERNET_STATUS_STATE_CHANGE: StatusStr := 'State change';
        else
          StatusStr := 'Unknown status';
       end;

      FOnStatusChanged(TauHTTP(Context), InternetStatus, StatusStr);
     end;

    if InternetStatus = INTERNET_STATUS_REDIRECT then
     begin
      SetLength(NewURL, StatusInformationLength - 1);
      Move(StatusInformation^, NewURL[1], StatusInformationLength - 1);

      if Assigned(FOnRedirected) then
        FOnRedirected(TauHTTP(Context), NewURL);
     end;
   end;
end;


// INTERNAL
type
  TauSimpleHTTPLoader = class(TObject)
  private
     FHTTP: TauCustomHTTP;
     FResult: String;     
     procedure HTTPDone(Sender: TObject; const ContentType: String; FileSize: Integer; Stream: TStream);
  public
     constructor Create(const URL: String; Timeout: DWord);
     destructor Destroy; override;
     function Read: String;
  end;

constructor TauSimpleHTTPLoader.Create(const URL: String; Timeout: DWord);
begin
  inherited Create;
  FHTTP := TauCustomHTTP.Create(nil);
  FHTTP.FURL := URL;
  with FHTTP do
   begin
    with FTimeouts do
     begin
      FConnectTimeout := Timeout;
      FReceiveTimeout := Timeout;
      FSendTimeout := Timeout;
     end; 
    WaitThread := True;
    WaitTimeout := Timeout;
    FOnDone := HTTPDone;
   end; 
end;

destructor TauSimpleHTTPLoader.Destroy;
begin
  FHTTP.Free;
  inherited;
end;

function TauSimpleHTTPLoader.Read: String;
begin
  FResult := '';
  FHTTP.Read;
  Result := FResult;
end;

procedure TauSimpleHTTPLoader.HTTPDone(Sender: TObject; const ContentType: String; FileSize: Integer; Stream: TStream);
var
  Len: DWord;
begin
  with Stream do
   begin
    Len := Size - Position;
    SetLength(FResult, Len);
    Read(FResult[1], Len);
   end;
end;

function HTTPReadString(const URL: String; Timeout: Integer {$IFDEF D4} = 0 {$ENDIF}): String;
begin
  with TauSimpleHTTPLoader.Create(URL, Timeout) do
   try
     Result := Read;
   finally
     Free;
   end;
end;


// routines to hide the HTTP username and password in the DFM
procedure EncryptUP(Stream: TStream; const U, P: String); // encrypts username/password and puts to stream
var
  Buffer: ShortString;
begin
  asm
        push    esi
        push    edi

        mov     esi, ECX   // "P"
        
        // -- determinating the length of Password
        mov     eax, esi
        test    eax, eax
        jz      @@z1
        mov     eax, [esi - 4] // length of Password, if not empty
@@z1:   // -------

        push    eax       // saving length of Password
        push    esi
        mov     esi, EDX   // "U"

        // -- determinating the length of Username
        mov     ecx, esi
        test    ecx, ecx
        jz      @@z2
        mov     ecx, [esi - 4] // length of Username, if not empty
@@z2:   // -------

        add     al, cl    // total length of Username and Password
        inc     eax

        lea     edi, Buffer
        mov     edx, eax  // save the total length for future use
        stosb             // store the total length in Buffer
        mov     al, cl    // total length
        stosb             // store the length of Username
rep     movsb             // copying the Username, including the length of username

        pop     esi
        pop     ecx       // restoring length of Password
rep     movsb             // copying the Password
        mov     ecx, edx  // restoring total length

        // Encrypt it
        std
        dec     edi
        mov     esi, edi
        xor     dl, 0EBh
@@XOR:
        lodsb
        xor     al, dl
        stosb
        loop    @@XOR
        cld

        pop     edi
        pop     esi
  end;
  Stream.Write(Buffer, Byte(Buffer[0]) + 1);
end;

procedure DecryptUP(Stream: TStream; var U, P: String); // retrieves username/password from stream and decrypts them
var
  User, Pass, Buffer: String[$7F]; // hope this enough
begin
  Stream.Read(Buffer, 1);
  Stream.Read(Buffer[1], Byte(Buffer[0]));

  asm
        push    esi
        push    edi

        xor     eax, eax

        lea     esi, Buffer
        lodsb             // retrieve length of encrypted string
        push    esi
        push    eax

        // Decrypt it
        mov     ecx, eax
        mov     edx, eax
        mov     edi, esi

        xor     dl, 0EBh
@@XOR:
        lodsb
        xor     al, dl
        stosb
        loop    @@XOR

        pop     eax
        pop     esi

        lea     edi, User
        mov     cl, [esi] // length of Username
        inc     ecx
        sub     eax, ecx  // length of Password
rep     movsb             // restoring Username
        lea     edi, Pass
        stosb             // restoring length of Password
        mov     ecx, eax
rep     movsb             // restoring Password

        pop     edi
        pop     esi
  end;

  U := User;
  P := Pass;
end;


{ TauLoginComponent }
procedure TauLoginComponent.ReadData(Stream: TStream);
begin
  DecryptUP(Stream, FLoginUsername, FLoginPassword);
end;

procedure TauLoginComponent.WriteData(Stream: TStream);
begin
  EncryptUP(Stream, FLoginUsername, FLoginPassword);
end;

procedure TauLoginComponent.DefineProperties(Filer: TFiler);
begin
  inherited;
  Filer.DefineBinaryProperty('LInfo', ReadData, WriteData, (Length(FLoginUsername) <> 0) or (Length(FLoginPassword) <> 0));
end;


{ TauHTTPProxy }
constructor TauHTTPProxy.Create;
begin
  inherited;
  FProxyPort := auDefaultProxyPort;
  FProxyBypass := '127.0.0.1;';
end;

function TauHTTPProxy.IsUseProxy: Boolean;
begin
  Result := FAccessType = atUseProxy;
end;


{ TauHTTP }
constructor TauCustomHTTP.Create(aOwner: TComponent);
begin
  inherited;
  FThread := TauCustomThread.Create(Self);
  FThread.OnExecute := ThreadExecute;
  FThread.OnException := ThreadException;
  FThread.OnTerminate := ThreadDone;
  FThread.OnWaitTimeoutExpired := ThreadWaitTimeoutExpired;

  FAddHeaders := TStringList.Create;
  FProxy := TauHTTPProxy.Create;
  FRange := TauHTTPRange.Create;
  FTimeouts := TauHTTPTimeouts.Create;

  FAcceptTypes := DEF_ACCEPT_TYPES;
  FAgent := 'acHTTP component (AppControls.com)';
  FTransferBufferSize := 4096;
  FUseCookies := True;
  FUseCache := True;

{$IFDEF TRIAL}
  if not NotifyDone and not (csDesigning in ComponentState) then
   begin
    NotifyDone := True;
    Application.MessageBox('This program built with AutoUpgrader Pro'#13#10 +
                           '(c) by UtilMind Solutions 1999-2003'#13#10#10 +
                           'To register AutoUpgrader Professional -'#13#10 +
                           'follow instructions in "readme.txt" file.', 'UNREGISTERED', mb_Ok or mb_IconInformation);
   end;
{$ENDIF}
end;

destructor TauCustomHTTP.Destroy;
begin
  FThread.Suspend; // we've used Abort method previously, but thread
                   // will be destroyed anyway in FThread.Free method
                   // we don't need to recreate it twice... 

  FTimeouts.Free;
  FRange.Free;
  FProxy.Free;
  FAddHeaders.Free;
  FThread.Free;
  inherited;
end;


// PROTECTED
procedure TauCustomHTTP.DoAnyError;
begin
  if Assigned(FOnAnyError) then
    FOnAnyError(Self);
end;


// PUBLIC METHODS
function TauCustomHTTP.Read: Boolean;
begin
  Result := not Busy;
  if Result then
{$IFDEF IE3}
    FThread.Execute;
{$ELSE}
   begin
    FPOSTMethod := pmFormURLEncoded;
    Result := FThread.Execute;
   end;
{$ENDIF}
end;

{$IFNDEF IE3}
function  TauCustomHTTP.Upload(NumberOfFields: Word): Boolean;
var
  I: Word;
  UploadStream: TMemoryStream;
  UploadFieldName, UploadFileName, Boundary, FieldHeader: String;
begin
  Result := not Busy;
  if Result and Assigned(FOnUploadFieldRequest) then
   begin
    // prepare request header and boundary BEFORE execute thread
    Boundary := GenerateAttachBoundary('0');
    HTTPUploadRequestHeader := 'Content-Type: multipart/form-data, boundary=' + Boundary;
    Boundary := '--' + Boundary;

    // create stream for uploading (will released on completion or on error)
    HTTPStream := TMemoryStream.Create;

    // create temporary stream to put files to main HTTPStream
    UploadStream := TMemoryStream.Create;
    try
      // put files to stream
      for I := 0 to NumberOfFields - 1 do
       begin
        // ask for data and field name
        UploadFieldName := '';
        UploadFileName := '';
        UploadStream.Clear;
        FOnUploadFieldRequest(Self, I, UploadStream, UploadFieldName, UploadFileName);

        // put boundary and field identifiers to stream
        FieldHeader := Boundary + CRLF +
            'Content-Disposition: form-data; name="' + UploadFieldName + '"';
        HTTPStream.Write(FieldHeader[1], Length(FieldHeader));
        // add filename and content-type of the file, if it's not empty
        if UploadFileName <> '' then
         begin
          FieldHeader := '; filename="' + UploadFileName + '"' + CRLF +
              'Content-Type: ' + GetMIMEType(ExtractFileExt(UploadFileName));
          HTTPStream.Write(FieldHeader[1], Length(FieldHeader));
         end;
        // finish header with double CRLF
        HTTPStream.Write(D_CRLF, 4);
        
        // put data to stream, after boundary
        HTTPStream.Write(UploadStream.Memory^, UploadStream.Size);
        HTTPStream.Write(CRLF, 2);
       end;
    finally
      UploadStream.Free;
    end;
    // finish it with boundary line
    Boundary := Boundary + '--' + CRLF;
    HTTPStream.Write(Boundary[1], Length(Boundary));

    FPOSTMethod := pmMultipartFormData;
    FThread.Execute;
   end;
end;
{$ENDIF}

procedure TauCustomHTTP.Abort;
begin
  CloseHTTPHandles; // close handles first... this could return OnAnyError though...
  if Busy then
   begin
    FThread.Terminate(True);
    if Assigned(FOnAborted) and not (csDestroying in ComponentState) then
      FOnAborted(Self);
   end;
  ReleaseHTTPStream;
end;


// ENGINE
procedure TauCustomHTTP.PrepareProgressParams;
begin
  ProgressPercentsDone := PercentsOf(HTTPFileSize, HTTPBytesTransferred);

  ProgressElapsedTime := (GetTickCount - HTTPStartTime) div 1000;
  ProgressEstimatedTime := Round(HTTPFileSize / HTTPBytesTransferred * ProgressElapsedTime)
                   { ^- This is total time for download} - ProgressElapsedTime;
  ProgressTransferRate := HTTPBytesTransferred / 1024;
  if ProgressElapsedTime <> 0 then
    ProgressTransferRate := ProgressTransferRate / ProgressElapsedTime;
end;

procedure TauCustomHTTP.CloseHTTPHandles;
begin
  if hFile <> 0 then
   begin
    CloseHandle(hFile);
    hFile := 0;
   end;
  if hRequest <> nil then
   begin
    InternetCloseHandle(hRequest);
    hRequest := nil;
   end;
  if hConnect <> nil then
   begin
    InternetCloseHandle(hConnect);
    hConnect := nil;
   end;
  if hSession <> nil then
   begin
    InternetCloseHandle(hSession);
    hSession := nil;
   end;
end;

procedure TauCustomHTTP.ReleaseHTTPStream;
begin
  if HTTPData <> nil then
   begin
    FreeMem(HTTPData);
    HTTPData := nil;
   end;

  if HTTPStream <> nil then
   begin
    HTTPStream.Free;
    HTTPStream := nil;
   end;
end;


// THREAD MANAGEMENT
procedure TauCustomHTTP.ThreadExecute;
const
  HEADER_BUFFER_SIZE = 4096;
  CookieFlags: Array[Boolean] of DWord = (INTERNET_FLAG_NO_COOKIES, 0);
  CacheFlags: Array[Boolean] of DWord = (INTERNET_FLAG_RELOAD or INTERNET_FLAG_NO_CACHE_WRITE or INTERNET_FLAG_PRAGMA_NOCACHE, 0);
  SecureFlags: Array[Boolean] of DWord = (0, INTERNET_FLAG_SECURE);
  OfflineFlags: Array[Boolean] of DWord = (0, INTERNET_FLAG_OFFLINE);
  ProxyFlags: Array[TauHTTPAccessType] of DWord = (INTERNET_OPEN_TYPE_PRECONFIG, INTERNET_OPEN_TYPE_DIRECT, INTERNET_OPEN_TYPE_PROXY);
  RequestMethods: Array[Boolean] of PChar = ('GET', 'POST');
var
  I: DWord;
  IsPOST: Boolean;
  PortNumber: Word;
  HTTPBlockSize: TauBufferSize;
  ProtocolName, HostName, ObjectName,
  URLUsername, URLPassword, URLExtraInfo: String;
  HeaderData: Array[0..HEADER_BUFFER_SIZE - 1] of Char;
  AcceptTypes: Array[0..1] of PChar;
  Headers: String;
{$IFNDEF IE3}
  UploadBuffer: INTERNET_BUFFERS;
{$ENDIF}
  IsLocalFile: Boolean;

  function QueryHTTPHeader(Flags: DWord): Boolean;
  var
    dwBufLen, dwIndex: DWord;
  begin
    dwIndex := 0;
    dwBufLen := HEADER_BUFFER_SIZE;
    Result := HttpQueryInfo(hRequest, Flags, @HeaderData, dwBufLen, dwIndex);
  end;

  procedure SetStringOption(Option: DWord; const Value: String);
  begin
    InternetSetOption(hRequest, Option, PChar(Value), Length(Value));
  end;

  procedure SetDWOption(Option: DWord; Value: DWord);
  begin
    InternetSetOption(hRequest, Option, @Value, SizeOf(Value));
  end;

  function ReadRemoteData: Boolean;
  begin
    if IsLocalFile then
      Result := ReadFile(hFile, HTTPData^, HTTPBlockSize, I, nil)
    else
      Result := InternetReadFile(hRequest, HTTPData, HTTPBlockSize, I);
  end;

begin
  HTTPErrorCode := HostUnreachableCode;
  HTTPContentType := '';
  HTTPBlockSize := FTransferBufferSize;
  HTTPStartTime := GetTickCount;
  HTTPContinueDownload := True;

  ParseURL(FURL, ProtocolName, HostName, ObjectName,
           URLUsername, URLPassword, URLExtraInfo, PortNumber);
  if URLUsername = '' then
    URLUsername := FLoginUsername;
  if URLPassword = '' then
    URLPassword := FLoginPassword;

  IsLocalFile := ProtocolName = 'file';
  if not IsLocalFile then
   begin
    // Opening the session
    with FProxy do
     if FAccessType = atUseProxy then
      if FProxyBypass = '' then
        // We should not use empty string for ProxyBypass because
        // InternetOpen will use it as the proxy bypass list
        hSession := InternetOpen(PChar(FAgent), ProxyFlags[FAccessType],
           PChar(ProxyServer + ':' + IntToStr(FProxyPort)), nil, OfflineFlags[FWorkOffline])
      else
        hSession := InternetOpen(PChar(FAgent), ProxyFlags[FAccessType],
           PChar(ProxyServer + ':' + IntToStr(FProxyPort)), PChar(FProxyBypass), OfflineFlags[FWorkOffline])
     else
       hSession := InternetOpen(PChar(FAgent), ProxyFlags[FAccessType],
          nil, nil, OfflineFlags[FWorkOffline]);

    // Registering the Callback function
    InternetSetStatusCallback(hSession, @GetURLStatusCallback);

    // check success
    HTTPSuccess := hSession <> nil;
    if not HTTPSuccess then Exit; // No connection or host unreachable

    // Estabilishing connection
    hConnect := InternetConnect(hSession, PChar(HostName), PortNumber,
       PChar(URLUsername), PChar(URLPassword), INTERNET_SERVICE_HTTP, 0, DWord(Self));
    // check success
    HTTPSuccess := hConnect <> nil;
    if not HTTPSuccess then Exit; // No connection or host unreachable

    // Preparing the request
    AcceptTypes[0] := PChar(FAcceptTypes);
    AcceptTypes[1] := nil;
    if FRequestMethod = rmAutoDetect then
      IsPOST := (FPOSTData <> '') {$IFNDEF IE3} or (FPOSTMethod = pmMultipartFormData){$ENDIF}
    else
      IsPOST := Boolean(Byte(FRequestMethod) - 1);
    hRequest := HttpOpenRequest(hConnect,
         PChar(RequestMethods[IsPOST]),
         PChar(ObjectName + URLExtraInfo), nil,
         PChar(FReferer), @AcceptTypes,
         CacheFlags[FUseCache] or CookieFlags[FUseCookies] or
         SecureFlags[ProtocolName = 'https'], 0);
    // check success
    HTTPSuccess := hRequest <> nil;
    if not HTTPSuccess then Exit; // No connection or host unreachable

    // Set timeouts
    with FTimeouts do
     begin
      if FConnectTimeout <> 0 then
        SetDWOption(INTERNET_OPTION_CONNECT_TIMEOUT, FConnectTimeout);
      if FReceiveTimeout <> 0 then
        SetDWOption(INTERNET_OPTION_RECEIVE_TIMEOUT, FReceiveTimeout);
     if FSendTimeout <> 0 then
        SetDWOption(INTERNET_OPTION_SEND_TIMEOUT, FSendTimeout);
     end;

    // Generate additional header
    I := FAddHeaders.Count;
    if I <> 0 then
     for I := 0 to I - 1 do
      Headers := Headers + FAddHeaders[I] + CRLF;

    // Generate content RANGE
    with FRange do
     if (FStartRange <> 0) or (FEndRange <> 0) then
      begin
       Headers := Headers + 'RANGE: bytes=' + IntToStr(FStartRange) + '-';
       if FEndRange <> 0 then
         Headers := Headers + IntToStr(FEndRange);
       Headers := Headers + CRLF;
      end;

    if Length(Headers) <> 0 then
     begin
      HTTPSuccess := HttpAddRequestHeaders(hRequest, PChar(Headers), Length(Headers), HTTP_ADDREQ_FLAG_ADD);
      if not HTTPSuccess then Exit; // No connection or host unreachable
     end;

    repeat
      HTTPTryAgain := False;

      // SENDING the request! Returns False if fails
      if IsPOST then
       {$IFNDEF IE3}
        if FPOSTMethod = pmFormURLEncoded then
       {$ENDIF}
          HTTPSuccess := HttpSendRequest(hRequest, DEF_CONTENT_TYPE, DEF_CONTENT_TYPE_SIZE,
              PChar(FPOSTData), Length(FPOSTData))
       {$IFNDEF IE3}
        else // multipart/form-data
         begin
          HTTPFileSize := HTTPStream.Size;

          // prepare BufferIn structure
          InitMSRecord(UploadBuffer, SizeOf(UploadBuffer));
          with UploadBuffer do
           begin
            lpcszHeader := PChar(HTTPUploadRequestHeader);
            dwHeadersLength := Length(HTTPUploadRequestHeader);
            dwHeadersTotal := dwHeadersLength;
            dwBufferTotal := HTTPFileSize;
           end;
          // start upload request
          HTTPSuccess := HttpSendRequestEx(hRequest,
               @UploadBuffer, nil, HSR_INITIATE, 0);

          // request and upload data
          if HTTPSuccess then
           begin
            // upload the data
            HTTPStream.Position := 0;
            HTTPBytesTransferred := 0;
            // UPLOADING DATA
            while True do
             with TMemoryStream(HTTPStream) do
              begin
               // determinate the size of block to upload
               if HTTPBytesTransferred + HTTPBlockSize > HTTPFileSize then
                 I := HTTPFileSize - HTTPBytesTransferred
               else
                 I := HTTPBlockSize;
               // upload block
               if not InternetWriteFile(hRequest,
                   Pointer(Cardinal(Memory) + HTTPBytesTransferred),
                   I, I) or (I = 0) then Break;
               inc(HTTPBytesTransferred, I);
               if Assigned(FOnUploadProgress) then
                 FThread.Synchronize(CallUploadProgress);
             end;

            HTTPStream.Free;
            HTTPStream := nil;

            // finish uploading
            HTTPEndRequest(hRequest, nil, 0, 0);
           end;
         end
       {$ENDIF}
      else // GET
        HTTPSuccess := HttpSendRequest(hRequest, nil, 0, nil, 0);

      if not HTTPSuccess then Exit; // No connection or host unreachable

      // get status code
      HTTPSuccess := QueryHTTPHeader(HTTP_QUERY_STATUS_CODE);
      if HTTPSuccess then HTTPErrorCode := StrToIntDef(HeaderData, 0);

      // trigger WWW and Proxy authentication requests
      if (HTTPErrorCode = HTTP_STATUS_DENIED) and
         Assigned(FOnPasswordRequest) then
       begin
        HTTPSuccess := QueryHTTPHeader(HTTP_QUERY_WWW_AUTHENTICATE);
        if HTTPSuccess then
         begin
          HTTPContentType := HeaderData; // this originally looks like 'Basic realm="REALM NAME"'
          I := Pos('="', HTTPContentType);
          if I <> 0 then
           begin
            inc(I, 2);
            HTTPContentType := Copy(HTTPContentType, I, Length(HTTPContentType) - Integer(I));
           end;

          // ...the code block above can be replaced by this:...
          //  HTTPContentType := LeftPart('"', RightPart('="', HTTPContentType));
         end
        else HTTPContentType := '';
        FThread.Synchronize(CallPasswordRequest);
        SetStringOption(INTERNET_OPTION_USERNAME, FLoginUsername);
        SetStringOption(INTERNET_OPTION_PASSWORD, FLoginPassword);
       end
      else
       if (HTTPErrorCode = HTTP_STATUS_PROXY_AUTH_REQ) and Assigned(FOnProxyAuthenticationRequest) then
        begin
         FThread.Synchronize(CallProxyAuthenticationRequest);
         with FProxy do
          begin
           SetStringOption(INTERNET_OPTION_PROXY_USERNAME, HTTPProxyUsername);
           SetStringOption(INTERNET_OPTION_PROXY_PASSWORD, HTTPProxyPassword);
          end;
        end;
    until not HTTPTryAgain;

    // PROCESS HEADERS
    if QueryHTTPHeader(HTTP_QUERY_CONTENT_TYPE) then
      HTTPContentType := HeaderData;
    HTTPSuccess := QueryHTTPHeader(HTTP_QUERY_CONTENT_LENGTH);
    if HTTPSuccess then
      HTTPFileSize := StrToIntDef(HeaderData, 0)
    else
      HTTPFileSize := 0;
    // if we need some additional headers -- process them
    if Assigned(FOnHeaderInfo) then
     begin
      if QueryHTTPHeader(HTTP_QUERY_RAW_HEADERS_CRLF) then
        HTTPRawHeadersCRLF := HeaderData
      else
        HTTPRawHeadersCRLF := '';
      if QueryHTTPHeader(HTTP_QUERY_CONTENT_LANGUAGE) then
        HTTPContentLanguage := HeaderData
      else
        HTTPContentLanguage := '';
      if QueryHTTPHeader(HTTP_QUERY_CONTENT_ENCODING) then
        HTTPContentEncoding := HeaderData
      else
        HTTPContentEncoding := '';
      if QueryHTTPHeader(HTTP_QUERY_LOCATION) then
        HTTPLocation := HeaderData
      else
        HTTPLocation := '';
      if QueryHTTPHeader(HTTP_QUERY_DATE) then
        HTTPDate := InternetTimeToDateTime(HeaderData)
      else
        HTTPDate := 0;
      if QueryHTTPHeader(HTTP_QUERY_LAST_MODIFIED) then
        HTTPLastModified := InternetTimeToDateTime(HeaderData)
      else
        HTTPLastModified := 0;
      if QueryHTTPHeader(HTTP_QUERY_EXPIRES) then
        HTTPExpires := InternetTimeToDateTime(HeaderData)
      else
        HTTPExpires := 0;

      FThread.Synchronize(CallHeaderInfo);
      if not HTTPContinueDownload then Exit; // we don't want to download data

     end;
   end
  else // if LocalFile
   begin
    hFile := CreateFile(PChar(ObjectName), GENERIC_READ, FILE_SHARE_READ or FILE_SHARE_WRITE, nil,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    HTTPFileSize := GetFileSize(hFile, @I);                              
    if hFile = INVALID_HANDLE_VALUE then
      HTTPErrorCode := HTTP_STATUS_NOT_FOUND
    else
      HTTPErrorCode := HTTP_STATUS_OK;  
   end;

  // PREPARING THE STREAM TO DOWNLOAD
  // determinating the filesize and creating the stream
  if HTTPSuccess then
   if FOutputFileName <> '' then // AK:13-NOV-2001 - support of FileStream if the OutputFileName specified
    try
      DeleteFile(FOutputFileName);
      HTTPStream := TFileStream.Create(FOutputFileName, fmCreate);
      if FHideOutputFile then
        Windows.SetFileAttributes(PChar(FOutputFileName), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_TEMPORARY);
    except
      HTTPStream := nil;
      Exit;
    end
   else
    begin
     HTTPStream := TMemoryStream.Create;
     // AK:13-NOV-2001. Fix to avoid expanding of the TMemoryStream over 4MB
     TMemoryStream(HTTPStream).SetSize(HTTPFileSize);
    end
  else
    HTTPStream := TMemoryStream.Create; // ASCII document. Stream will expanded dynamically

  // READING THE DATA FROM THE WEB
  HTTPBytesTransferred := 0;
  GetMem(HTTPData, HTTPBlockSize);
  while ReadRemoteData do
   begin
    if I = 0 then Break;
    HTTPStream.Write(HTTPData^, I);
    inc(HTTPBytesTransferred, I);
    if Assigned(FOnProgress) then
      FThread.Synchronize(CallProgress);
   end;

  HTTPSuccess := HTTPErrorCode = HTTP_STATUS_OK;

  // if the data size has been determinated -- check, maybe connection was lost
  // and only part of data has been downloaded
  if HTTPSuccess and (HTTPFileSize <> 0) and (HTTPStream <> nil) then
    HTTPSuccess := HTTPFileSize = Cardinal(HTTPBytesTransferred);
end;

procedure TauCustomHTTP.ThreadDone(Sender: TObject);
var
  DeleteOutputFile: Boolean;
begin
  CloseHTTPHandles;
  DeleteOutputFile := False;
  // move stream position to beginning of stream
  if HTTPStream <> nil then
    HTTPStream.Position := 0;

  if HTTPContinueDownload then
   with FThread do
    if HTTPSuccess then
     begin
      if HTTPStream = nil then
       begin
        DoAnyError;
        Exit;
       end;

      if HTTPStream is TFileStream then // this happends when the OutputFileName specified
        ReleaseHTTPStream; // release it before usage in OnDone handler. OnDone should work only with MemoryStreams

      if Assigned(FOnDone) then // note, HTTPStream can be NIL !!
        FOnDone(Self, HTTPContentType, HTTPBytesTransferred, HTTPStream);
     end
    else
     begin
      DoAnyError;
      if HTTPErrorCode = HTTP_STATUS_OK then // Connection lost
       if Assigned(FOnConnLost) then
          FOnConnLost(Self, HTTPContentType,
              HTTPFileSize, HTTPBytesTransferred, HTTPStream)
        else
      else
       // fire OnHostUnreachable
       if HTTPErrorCode = HostUnreachableCode then
         if Assigned(FOnHostUnreachable) then
           FOnHostUnreachable(Self)
         else
       else
        // fire OnError if occurred
        if Assigned(FOnHTTPError) then
          FOnHTTPError(Self, HTTPErrorCode, HTTPStream);

       if HTTPStream is TFileStream then
         DeleteOutputFile := True;
     end;

  ReleaseHTTPStream;

  if DeleteOutputFile then
    DeleteFile(OutputFileName);

  if not HTTPContinueDownload and Assigned(FOnDoneInterrupted) then
    FOnDoneInterrupted(Self);
end;

procedure TauCustomHTTP.ThreadException;
begin
  DoAnyError;
end;

procedure TauCustomHTTP.ThreadWaitTimeoutExpired(Sender: TObject);
begin
  CloseHTTPHandles;
  ReleaseHTTPStream;
  if Assigned(FOnWaitTimeoutExpired) then
    FOnWaitTimeoutExpired(Self);
end;


// SYNCHRONIZED METHODS
procedure TauCustomHTTP.CallHeaderInfo;
begin
  if Assigned(FOnHeaderInfo) then
    FOnHeaderInfo(Self, HTTPRawHeadersCRLF,
                        HTTPContentType, HTTPContentLanguage, HTTPContentEncoding,
                        HTTPLocation, HTTPFileSize, HTTPDate, HTTPLastModified, HTTPExpires,
                        HTTPContinueDownload);
end;

procedure TauCustomHTTP.CallProgress;
begin
  PrepareProgressParams;
  if Assigned(FOnProgress) then
    FOnProgress(Self, HTTPContentType, HTTPFileSize, HTTPBytesTransferred,
                ProgressElapsedTime, ProgressEstimatedTime,
                ProgressPercentsDone, ProgressTransferRate, HTTPStream);
end;

{$IFNDEF IE3}
procedure TauCustomHTTP.CallUploadProgress;
begin
  PrepareProgressParams;
  if Assigned(FOnUploadProgress) then
    FOnUploadProgress(Self, HTTPFileSize, HTTPBytesTransferred,
                ProgressElapsedTime, ProgressEstimatedTime,
                ProgressPercentsDone, ProgressTransferRate);
end;
{$ENDIF}

procedure TauCustomHTTP.CallPasswordRequest; // error 401
begin
  if Assigned(FOnPasswordRequest) then
    FOnPasswordRequest(Self, HTTPContentType, HTTPTryAgain);
end;

procedure TauCustomHTTP.CallProxyAuthenticationRequest; // error 407
begin
  if Assigned(FOnProxyAuthenticationRequest) then
    FOnProxyAuthenticationRequest(Self, HTTPProxyUsername, HTTPProxyPassword, HTTPTryAgain);
end;


// PROPERTIES
procedure TauCustomHTTP.SetAddHeaders(Value: TStrings);
begin
  FAddHeaders.Assign(Value);
end;

function  TauCustomHTTP.GetSuspended: Boolean;
begin
  Result := FThread.Suspended;
end;

procedure TauCustomHTTP.SetSuspended(Value: Boolean);
begin
  FThread.Suspended := Value;
end;

function  TauCustomHTTP.GetThreadPriority: TThreadPriority;
begin
  Result := FThread.Priority;
end;

procedure TauCustomHTTP.SetThreadPriority(Value: TThreadPriority);
begin
  FThread.Priority := Value;
end;

function  TauCustomHTTP.GetWaitTimeout: Integer;
begin
  Result := FThread.WaitTimeout;
end;

procedure TauCustomHTTP.SetWaitTimeout(Value: Integer);
begin
  FThread.WaitTimeout := Value;
end;

function  TauCustomHTTP.GetWaitThread: Boolean;
begin
  Result := FThread.WaitThread;
end;

procedure TauCustomHTTP.SetWaitThread(Value: Boolean);
begin
  FThread.WaitThread := Value;
end;

function TauCustomHTTP.GetBusy: Boolean;
begin
  Result := FThread.Running;
end;

function  TauCustomHTTP.GetFreeOnTerminate: Boolean;
begin
  Result := FThread.FreeOwnerOnTerminate;
end;

procedure TauCustomHTTP.SetFreeOnTerminate(Value: Boolean);
begin
  FThread.FreeOwnerOnTerminate := Value;
end;

function TauCustomHTTP.GetFileName: String;
begin
  Result := URLToFileName(FURL);
end;

function TauCustomHTTP.GetHostName: String;
begin
  Result := URLToHostName(FURL);
end;

function TauCustomHTTP.IsNotDefaultAcceptTypes: Boolean;
begin
  Result := FAcceptTypes <> DEF_ACCEPT_TYPES;
end;

end.
