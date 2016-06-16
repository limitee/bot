// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'auThread.pas' rev: 6.00

#ifndef auThreadHPP
#define auThreadHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Authread
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TauEventThread;
class DELPHICLASS TauCustomThread;
class PASCALIMPLEMENTATION TauCustomThread : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TauEventThread* FThread;
	bool FDesignSuspended;
	bool FHandleExceptions;
	bool FFreeOwnerOnTerminate;
	bool FWaitThread;
	unsigned FWaitTimeout;
	Classes::TNotifyEvent FOnWaitTimeoutExpired;
	Classes::TNotifyEvent FSyncMethod;
	void *FSyncParams;
	void __fastcall InternalSynchronization(void);
	Classes::TThreadPriority __fastcall GetPriority(void);
	void __fastcall SetPriority(Classes::TThreadPriority Value);
	bool __fastcall GetSuspended(void);
	void __fastcall SetSuspended(bool Value);
	bool __fastcall GetRunning(void);
	bool __fastcall GetTerminated(void);
	unsigned __fastcall GetThreadID(void);
	Classes::TNotifyEvent __fastcall GetOnException();
	void __fastcall SetOnException(Classes::TNotifyEvent Value);
	Classes::TNotifyEvent __fastcall GetOnExecute();
	void __fastcall SetOnExecute(Classes::TNotifyEvent Value);
	Classes::TNotifyEvent __fastcall GetOnTerminate();
	void __fastcall SetOnTerminate(Classes::TNotifyEvent Value);
	unsigned __fastcall GetHandle(void);
	int __fastcall GetReturnValue(void);
	void __fastcall SetReturnValue(int Value);
	
protected:
	virtual void __fastcall Loaded(void);
	void __fastcall DoWaitTimeoutExpired(void);
	
public:
	__fastcall virtual TauCustomThread(Classes::TComponent* aOwner);
	__fastcall virtual ~TauCustomThread(void);
	bool __fastcall Execute(void);
	void __fastcall Synchronize(Classes::TThreadMethod Method);
	void __fastcall SynchronizeEx(Classes::TNotifyEvent Method, void * Params);
	void __fastcall Suspend(void);
	void __fastcall Resume(void);
	void __fastcall Terminate(bool Imediately);
	unsigned __fastcall WaitFor(void);
	__property unsigned Handle = {read=GetHandle, nodefault};
	__property bool Running = {read=GetRunning, nodefault};
	__property bool Terminated = {read=GetTerminated, nodefault};
	__property unsigned ThreadID = {read=GetThreadID, nodefault};
	__property int ReturnValue = {read=GetReturnValue, write=SetReturnValue, nodefault};
	__property bool FreeOwnerOnTerminate = {read=FFreeOwnerOnTerminate, write=FFreeOwnerOnTerminate, default=0};
	__property bool HandleExceptions = {read=FHandleExceptions, write=FHandleExceptions, default=1};
	__property Classes::TThreadPriority Priority = {read=GetPriority, write=SetPriority, default=3};
	__property bool Suspended = {read=GetSuspended, write=SetSuspended, default=1};
	__property bool WaitThread = {read=FWaitThread, write=FWaitThread, default=0};
	__property unsigned WaitTimeout = {read=FWaitTimeout, write=FWaitTimeout, default=0};
	__property Classes::TNotifyEvent OnException = {read=GetOnException, write=SetOnException};
	__property Classes::TNotifyEvent OnExecute = {read=GetOnExecute, write=SetOnExecute};
	__property Classes::TNotifyEvent OnTerminate = {read=GetOnTerminate, write=SetOnTerminate};
	__property Classes::TNotifyEvent OnWaitTimeoutExpired = {read=FOnWaitTimeoutExpired, write=FOnWaitTimeoutExpired};
};


class PASCALIMPLEMENTATION TauEventThread : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	unsigned FHandle;
	unsigned FThreadID;
	bool FTerminated;
	bool FSuspended;
	bool FFreeOnTerminate;
	int FReturnValue;
	bool FRunning;
	Classes::TThreadMethod FMethod;
	System::TObject* FSynchronizeException;
	Classes::TNotifyEvent FOnExecute;
	Classes::TNotifyEvent FOnException;
	Classes::TNotifyEvent FOnTerminate;
	TauCustomThread* Owner;
	Classes::TThreadPriority __fastcall GetPriority(void);
	void __fastcall SetPriority(Classes::TThreadPriority Value);
	void __fastcall SetSuspended(bool Value);
	void __fastcall CallTerminate(void);
	void __fastcall CallException(void);
	
protected:
	void __fastcall DoTerminate(void);
	void __fastcall Execute(void);
	void __fastcall Synchronize(Classes::TThreadMethod Method);
	__property int ReturnValue = {read=FReturnValue, write=FReturnValue, nodefault};
	__property bool Terminated = {read=FTerminated, nodefault};
	TauEventThread* __fastcall CreateThread(void);
	TauEventThread* __fastcall RecreateThread(void);
	
public:
	__fastcall TauEventThread(TauCustomThread* aOwner);
	__fastcall virtual ~TauEventThread(void);
	void __fastcall Resume(void);
	void __fastcall Suspend(void);
	void __fastcall Terminate(void);
	unsigned __fastcall WaitFor(void);
	__property bool FreeOnTerminate = {read=FFreeOnTerminate, write=FFreeOnTerminate, nodefault};
	__property unsigned Handle = {read=FHandle, nodefault};
	__property Classes::TThreadPriority Priority = {read=GetPriority, write=SetPriority, nodefault};
	__property bool Suspended = {read=FSuspended, write=SetSuspended, nodefault};
	__property unsigned ThreadID = {read=FThreadID, nodefault};
	__property Classes::TNotifyEvent OnExecute = {read=FOnExecute, write=FOnExecute};
	__property Classes::TNotifyEvent OnException = {read=FOnException, write=FOnException};
	__property Classes::TNotifyEvent OnTerminate = {read=FOnTerminate, write=FOnTerminate};
};


class DELPHICLASS TauThread;
class PASCALIMPLEMENTATION TauThread : public TauCustomThread 
{
	typedef TauCustomThread inherited;
	
__published:
	__property HandleExceptions  = {default=1};
	__property Priority  = {default=3};
	__property Suspended  = {default=1};
	__property WaitThread  = {default=0};
	__property WaitTimeout  = {default=0};
	__property OnException ;
	__property OnExecute ;
	__property OnTerminate ;
	__property OnWaitTimeoutExpired ;
public:
	#pragma option push -w-inl
	/* TauCustomThread.Create */ inline __fastcall virtual TauThread(Classes::TComponent* aOwner) : TauCustomThread(aOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TauCustomThread.Destroy */ inline __fastcall virtual ~TauThread(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Authread */
using namespace Authread;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// auThread
