
// ************************************************************************** //
//                                                                          
//                             XML Data Binding                             
//                                                                          
//         Generated on: 2016-05-17 21:03:04                                
//       Generated from: D:\LottChina\TicketCenterNode\TerminalConfig.xsd   
//   Settings stored in: D:\LottChina\TicketCenterNode\TerminalConfig.xdb   
//                                                                          
// ************************************************************************** //

#ifndef   TerminalConfigH
#define   TerminalConfigH

#include <System.hpp>
#include <Xml.Xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <XMLNodeImp.h>


// Forward Decls 

__interface IXMLDataCenterType;
typedef System::DelphiInterface<IXMLDataCenterType> _di_IXMLDataCenterType;
__interface IXMLTerminalType;
typedef System::DelphiInterface<IXMLTerminalType> _di_IXMLTerminalType;
__interface IXMLKeyboardType;
typedef System::DelphiInterface<IXMLKeyboardType> _di_IXMLKeyboardType;
__interface IXMLKeyboardCodeType;
typedef System::DelphiInterface<IXMLKeyboardCodeType> _di_IXMLKeyboardCodeType;
__interface IXMLCategoryReportType;
typedef System::DelphiInterface<IXMLCategoryReportType> _di_IXMLCategoryReportType;
__interface IXMLReportMenuType;
typedef System::DelphiInterface<IXMLReportMenuType> _di_IXMLReportMenuType;
__interface IXMLLotteryPosType;
typedef System::DelphiInterface<IXMLLotteryPosType> _di_IXMLLotteryPosType;
__interface IXMLGameType;
typedef System::DelphiInterface<IXMLGameType> _di_IXMLGameType;
__interface IXMLStakeType;
typedef System::DelphiInterface<IXMLStakeType> _di_IXMLStakeType;
__interface IXMLChoiceType;
typedef System::DelphiInterface<IXMLChoiceType> _di_IXMLChoiceType;
__interface IXMLInnerKeyStringType;
typedef System::DelphiInterface<IXMLInnerKeyStringType> _di_IXMLInnerKeyStringType;

// IXMLDataCenterType 

__interface INTERFACE_UUID("{6EF29BF4-3FE2-4376-8102-2228F48A2E71}") IXMLDataCenterType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_CenterCode() = 0;
  virtual System::UnicodeString __fastcall Get_ServerHost() = 0;
  virtual int __fastcall Get_ServerPort() = 0;
  virtual System::UnicodeString __fastcall Get_BinFileDir() = 0;
  virtual System::UnicodeString __fastcall Get_HexFileDir() = 0;
  virtual System::UnicodeString __fastcall Get_PrinterCom() = 0;
  virtual System::UnicodeString __fastcall Get_PrinterComParam() = 0;
  virtual System::UnicodeString __fastcall Get_Desc() = 0;
  virtual _di_IXMLTerminalType __fastcall Get_Terminal(int Index) = 0;
  virtual void __fastcall Set_CenterCode(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_ServerHost(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_ServerPort(int Value) = 0;
  virtual void __fastcall Set_BinFileDir(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_HexFileDir(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_PrinterCom(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_PrinterComParam(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_Desc(System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual _di_IXMLTerminalType __fastcall Add() = 0;
  virtual _di_IXMLTerminalType __fastcall Insert(const int Index) = 0;
  __property System::UnicodeString CenterCode = { read=Get_CenterCode, write=Set_CenterCode };
  __property System::UnicodeString ServerHost = { read=Get_ServerHost, write=Set_ServerHost };
  __property int ServerPort = { read=Get_ServerPort, write=Set_ServerPort };
  __property System::UnicodeString BinFileDir = { read=Get_BinFileDir, write=Set_BinFileDir };
  __property System::UnicodeString HexFileDir = { read=Get_HexFileDir, write=Set_HexFileDir };
  __property System::UnicodeString PrinterCom = { read=Get_PrinterCom, write=Set_PrinterCom };
  __property System::UnicodeString PrinterComParam = { read=Get_PrinterComParam, write=Set_PrinterComParam };
  __property System::UnicodeString Desc = { read=Get_Desc, write=Set_Desc };
  __property _di_IXMLTerminalType Terminal[int Index] = { read=Get_Terminal };/* default */
};

// IXMLTerminalType 

__interface INTERFACE_UUID("{CCEDE376-45E0-4E9C-AE17-C1B344F20CFA}") IXMLTerminalType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_TerminalID() = 0;
  virtual System::UnicodeString __fastcall Get_TerminalType() = 0;
  virtual System::UnicodeString __fastcall Get_ConnectionKey() = 0;
  virtual System::UnicodeString __fastcall Get_BoxComParam() = 0;
  virtual bool __fastcall Get_EnableAutoRun() = 0;
  virtual System::UnicodeString __fastcall Get_Desc() = 0;
  virtual _di_IXMLKeyboardType __fastcall Get_Keyboard() = 0;
  virtual _di_IXMLCategoryReportType __fastcall Get_CategoryReport() = 0;
  virtual _di_IXMLLotteryPosType __fastcall Get_LotteryPos() = 0;
  virtual void __fastcall Set_TerminalID(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_TerminalType(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_ConnectionKey(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_BoxComParam(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_EnableAutoRun(bool Value) = 0;
  virtual void __fastcall Set_Desc(System::UnicodeString Value) = 0;
  // Methods & Properties 
  __property System::UnicodeString TerminalID = { read=Get_TerminalID, write=Set_TerminalID };
  __property System::UnicodeString TerminalType = { read=Get_TerminalType, write=Set_TerminalType };
  __property System::UnicodeString ConnectionKey = { read=Get_ConnectionKey, write=Set_ConnectionKey };
  __property System::UnicodeString BoxComParam = { read=Get_BoxComParam, write=Set_BoxComParam };
  __property bool EnableAutoRun = { read=Get_EnableAutoRun, write=Set_EnableAutoRun };
  __property System::UnicodeString Desc = { read=Get_Desc, write=Set_Desc };
  __property _di_IXMLKeyboardType Keyboard = { read=Get_Keyboard };
  __property _di_IXMLCategoryReportType CategoryReport = { read=Get_CategoryReport };
  __property _di_IXMLLotteryPosType LotteryPos = { read=Get_LotteryPos };
};

// IXMLKeyboardType 

__interface INTERFACE_UUID("{0392B949-3F83-457E-93AA-61D9BD845346}") IXMLKeyboardType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_Login() = 0;
  virtual System::UnicodeString __fastcall Get_Shutdown() = 0;
  virtual System::UnicodeString __fastcall Get_DefaultBackRoot() = 0;
  virtual System::UnicodeString __fastcall Get_PrintConfirm() = 0;
  virtual System::UnicodeString __fastcall Get_BobusPrefix() = 0;
  virtual System::UnicodeString __fastcall Get_BobusPostfix() = 0;
  virtual _di_IXMLKeyboardCodeType __fastcall Get_KeyboardCode(int Index) = 0;
  virtual void __fastcall Set_Login(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_Shutdown(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_DefaultBackRoot(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_PrintConfirm(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_BobusPrefix(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_BobusPostfix(System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual _di_IXMLKeyboardCodeType __fastcall Add() = 0;
  virtual _di_IXMLKeyboardCodeType __fastcall Insert(const int Index) = 0;
  __property System::UnicodeString Login = { read=Get_Login, write=Set_Login };
  __property System::UnicodeString Shutdown = { read=Get_Shutdown, write=Set_Shutdown };
  __property System::UnicodeString DefaultBackRoot = { read=Get_DefaultBackRoot, write=Set_DefaultBackRoot };
  __property System::UnicodeString PrintConfirm = { read=Get_PrintConfirm, write=Set_PrintConfirm };
  __property System::UnicodeString BobusPrefix = { read=Get_BobusPrefix, write=Set_BobusPrefix };
  __property System::UnicodeString BobusPostfix = { read=Get_BobusPostfix, write=Set_BobusPostfix };
  __property _di_IXMLKeyboardCodeType KeyboardCode[int Index] = { read=Get_KeyboardCode };/* default */
};

// IXMLKeyboardCodeType 

__interface INTERFACE_UUID("{E92CB58F-B36A-411F-9392-453D00394B14}") IXMLKeyboardCodeType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_InnerCode() = 0;
  virtual System::UnicodeString __fastcall Get_KeyboardName() = 0;
  virtual System::UnicodeString __fastcall Get_KeyboardValue() = 0;
  virtual void __fastcall Set_InnerCode(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_KeyboardName(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_KeyboardValue(System::UnicodeString Value) = 0;
  // Methods & Properties 
  __property System::UnicodeString InnerCode = { read=Get_InnerCode, write=Set_InnerCode };
  __property System::UnicodeString KeyboardName = { read=Get_KeyboardName, write=Set_KeyboardName };
  __property System::UnicodeString KeyboardValue = { read=Get_KeyboardValue, write=Set_KeyboardValue };
};

// IXMLCategoryReportType 

__interface INTERFACE_UUID("{B9F5675D-F446-4E7C-98C2-4EA0A04A18A0}") IXMLCategoryReportType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_FinishKeys() = 0;
  virtual _di_IXMLReportMenuType __fastcall Get_ReportMenu(int Index) = 0;
  virtual void __fastcall Set_FinishKeys(System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual _di_IXMLReportMenuType __fastcall Add() = 0;
  virtual _di_IXMLReportMenuType __fastcall Insert(const int Index) = 0;
  __property System::UnicodeString FinishKeys = { read=Get_FinishKeys, write=Set_FinishKeys };
  __property _di_IXMLReportMenuType ReportMenu[int Index] = { read=Get_ReportMenu };/* default */
};

// IXMLReportMenuType 

__interface INTERFACE_UUID("{5103D00C-2F88-4316-9AF0-CCCD1EAC08C4}") IXMLReportMenuType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_Caption() = 0;
  virtual System::UnicodeString __fastcall Get_QueryID() = 0;
  virtual System::UnicodeString __fastcall Get_InnerKeys() = 0;
  virtual bool __fastcall Get_HaveStub() = 0;
  virtual void __fastcall Set_Caption(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_QueryID(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_InnerKeys(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_HaveStub(bool Value) = 0;
  // Methods & Properties 
  __property System::UnicodeString Caption = { read=Get_Caption, write=Set_Caption };
  __property System::UnicodeString QueryID = { read=Get_QueryID, write=Set_QueryID };
  __property System::UnicodeString InnerKeys = { read=Get_InnerKeys, write=Set_InnerKeys };
  __property bool HaveStub = { read=Get_HaveStub, write=Set_HaveStub };
};

// IXMLLotteryPosType 

__interface INTERFACE_UUID("{89E3A1DF-2C25-4F4B-8089-C7244768E866}") IXMLLotteryPosType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_PosType() = 0;
  virtual System::UnicodeString __fastcall Get_UKeyPassword() = 0;
  virtual System::UnicodeString __fastcall Get_SalesAccount() = 0;
  virtual System::UnicodeString __fastcall Get_SalesPassword() = 0;
  virtual int __fastcall Get_NeedConfirmAmount() = 0;
  virtual int __fastcall Get_NeedPasswordAmount() = 0;
  virtual System::UnicodeString __fastcall Get_Desc() = 0;
  virtual _di_IXMLGameType __fastcall Get_Game(int Index) = 0;
  virtual void __fastcall Set_PosType(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_UKeyPassword(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_SalesAccount(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_SalesPassword(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_NeedConfirmAmount(int Value) = 0;
  virtual void __fastcall Set_NeedPasswordAmount(int Value) = 0;
  virtual void __fastcall Set_Desc(System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual _di_IXMLGameType __fastcall Add() = 0;
  virtual _di_IXMLGameType __fastcall Insert(const int Index) = 0;
  __property System::UnicodeString PosType = { read=Get_PosType, write=Set_PosType };
  __property System::UnicodeString UKeyPassword = { read=Get_UKeyPassword, write=Set_UKeyPassword };
  __property System::UnicodeString SalesAccount = { read=Get_SalesAccount, write=Set_SalesAccount };
  __property System::UnicodeString SalesPassword = { read=Get_SalesPassword, write=Set_SalesPassword };
  __property int NeedConfirmAmount = { read=Get_NeedConfirmAmount, write=Set_NeedConfirmAmount };
  __property int NeedPasswordAmount = { read=Get_NeedPasswordAmount, write=Set_NeedPasswordAmount };
  __property System::UnicodeString Desc = { read=Get_Desc, write=Set_Desc };
  __property _di_IXMLGameType Game[int Index] = { read=Get_Game };/* default */
};

// IXMLGameType 

__interface INTERFACE_UUID("{906DE578-0D38-4309-8009-406649C947C3}") IXMLGameType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_GameNode() = 0;
  virtual System::UnicodeString __fastcall Get_GameID() = 0;
  virtual System::UnicodeString __fastcall Get_GameName() = 0;
  virtual System::UnicodeString __fastcall Get_EnterKey() = 0;
  virtual System::UnicodeString __fastcall Get_StakeToRootKey() = 0;
  virtual System::UnicodeString __fastcall Get_DefaultStakeNode() = 0;
  virtual _di_IXMLStakeType __fastcall Get_Stake(int Index) = 0;
  virtual void __fastcall Set_GameNode(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_GameID(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_GameName(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_EnterKey(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_StakeToRootKey(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_DefaultStakeNode(System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual _di_IXMLStakeType __fastcall Add() = 0;
  virtual _di_IXMLStakeType __fastcall Insert(const int Index) = 0;
  __property System::UnicodeString GameNode = { read=Get_GameNode, write=Set_GameNode };
  __property System::UnicodeString GameID = { read=Get_GameID, write=Set_GameID };
  __property System::UnicodeString GameName = { read=Get_GameName, write=Set_GameName };
  __property System::UnicodeString EnterKey = { read=Get_EnterKey, write=Set_EnterKey };
  __property System::UnicodeString StakeToRootKey = { read=Get_StakeToRootKey, write=Set_StakeToRootKey };
  __property System::UnicodeString DefaultStakeNode = { read=Get_DefaultStakeNode, write=Set_DefaultStakeNode };
  __property _di_IXMLStakeType Stake[int Index] = { read=Get_Stake };/* default */
};

// IXMLStakeType 

__interface INTERFACE_UUID("{9D4C7F42-140F-4DAA-A7D8-357C91D0B53A}") IXMLStakeType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_StakeNode() = 0;
  virtual System::UnicodeString __fastcall Get_StakeName() = 0;
  virtual System::UnicodeString __fastcall Get_PlayBetId() = 0;
  virtual System::UnicodeString __fastcall Get_FinishedNode() = 0;
  virtual System::UnicodeString __fastcall Get_Desc() = 0;
  virtual _di_IXMLChoiceType __fastcall Get_Choice(int Index) = 0;
  virtual void __fastcall Set_StakeNode(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_StakeName(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_PlayBetId(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_FinishedNode(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_Desc(System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual _di_IXMLChoiceType __fastcall Add() = 0;
  virtual _di_IXMLChoiceType __fastcall Insert(const int Index) = 0;
  __property System::UnicodeString StakeNode = { read=Get_StakeNode, write=Set_StakeNode };
  __property System::UnicodeString StakeName = { read=Get_StakeName, write=Set_StakeName };
  __property System::UnicodeString PlayBetId = { read=Get_PlayBetId, write=Set_PlayBetId };
  __property System::UnicodeString FinishedNode = { read=Get_FinishedNode, write=Set_FinishedNode };
  __property System::UnicodeString Desc = { read=Get_Desc, write=Set_Desc };
  __property _di_IXMLChoiceType Choice[int Index] = { read=Get_Choice };/* default */
};

// IXMLChoiceType 

__interface INTERFACE_UUID("{ED815189-9A7D-4FD9-B3BD-9D69A98AC60B}") IXMLChoiceType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_ChoiceKey() = 0;
  virtual System::UnicodeString __fastcall Get_JumpTo() = 0;
  virtual void __fastcall Set_ChoiceKey(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_JumpTo(System::UnicodeString Value) = 0;
  // Methods & Properties 
  __property System::UnicodeString ChoiceKey = { read=Get_ChoiceKey, write=Set_ChoiceKey };
  __property System::UnicodeString JumpTo = { read=Get_JumpTo, write=Set_JumpTo };
};

// IXMLInnerKeyStringType 

__interface INTERFACE_UUID("{F1D818A1-5C31-49A5-BBBD-B571BB7D4F47}") IXMLInnerKeyStringType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_Desc() = 0;
  virtual System::UnicodeString __fastcall Get_InnerKeyCode(int Index) = 0;
  virtual void __fastcall Set_Desc(System::UnicodeString Value) = 0;
  // Methods & Properties 
  virtual Xml::Xmlintf::_di_IXMLNode __fastcall Add(const System::UnicodeString InnerKeyCode) = 0;
  virtual Xml::Xmlintf::_di_IXMLNode __fastcall Insert(const int Index, const System::UnicodeString InnerKeyCode) = 0;
  __property System::UnicodeString Desc = { read=Get_Desc, write=Set_Desc };
  __property System::UnicodeString InnerKeyCode[int Index] = { read=Get_InnerKeyCode };/* default */
};

// Forward Decls 

class TXMLDataCenterType;
class TXMLTerminalType;
class TXMLKeyboardType;
class TXMLKeyboardCodeType;
class TXMLCategoryReportType;
class TXMLReportMenuType;
class TXMLLotteryPosType;
class TXMLGameType;
class TXMLStakeType;
class TXMLChoiceType;
class TXMLInnerKeyStringType;

// TXMLDataCenterType 

class TXMLDataCenterType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLDataCenterType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLDataCenterType 
  virtual System::UnicodeString __fastcall Get_CenterCode();
  virtual System::UnicodeString __fastcall Get_ServerHost();
  virtual int __fastcall Get_ServerPort();
  virtual System::UnicodeString __fastcall Get_BinFileDir();
  virtual System::UnicodeString __fastcall Get_HexFileDir();
  virtual System::UnicodeString __fastcall Get_PrinterCom();
  virtual System::UnicodeString __fastcall Get_PrinterComParam();
  virtual System::UnicodeString __fastcall Get_Desc();
  virtual _di_IXMLTerminalType __fastcall Get_Terminal(int Index);
  virtual void __fastcall Set_CenterCode(System::UnicodeString Value);
  virtual void __fastcall Set_ServerHost(System::UnicodeString Value);
  virtual void __fastcall Set_ServerPort(int Value);
  virtual void __fastcall Set_BinFileDir(System::UnicodeString Value);
  virtual void __fastcall Set_HexFileDir(System::UnicodeString Value);
  virtual void __fastcall Set_PrinterCom(System::UnicodeString Value);
  virtual void __fastcall Set_PrinterComParam(System::UnicodeString Value);
  virtual void __fastcall Set_Desc(System::UnicodeString Value);
  virtual _di_IXMLTerminalType __fastcall Add();
  virtual _di_IXMLTerminalType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLTerminalType 

class TXMLTerminalType : public Xml::Xmldoc::TXMLNode, public IXMLTerminalType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLTerminalType 
  virtual System::UnicodeString __fastcall Get_TerminalID();
  virtual System::UnicodeString __fastcall Get_TerminalType();
  virtual System::UnicodeString __fastcall Get_ConnectionKey();
  virtual System::UnicodeString __fastcall Get_BoxComParam();
  virtual bool __fastcall Get_EnableAutoRun();
  virtual System::UnicodeString __fastcall Get_Desc();
  virtual _di_IXMLKeyboardType __fastcall Get_Keyboard();
  virtual _di_IXMLCategoryReportType __fastcall Get_CategoryReport();
  virtual _di_IXMLLotteryPosType __fastcall Get_LotteryPos();
  virtual void __fastcall Set_TerminalID(System::UnicodeString Value);
  virtual void __fastcall Set_TerminalType(System::UnicodeString Value);
  virtual void __fastcall Set_ConnectionKey(System::UnicodeString Value);
  virtual void __fastcall Set_BoxComParam(System::UnicodeString Value);
  virtual void __fastcall Set_EnableAutoRun(bool Value);
  virtual void __fastcall Set_Desc(System::UnicodeString Value);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLKeyboardType 

class TXMLKeyboardType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLKeyboardType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLKeyboardType 
  virtual System::UnicodeString __fastcall Get_Login();
  virtual System::UnicodeString __fastcall Get_Shutdown();
  virtual System::UnicodeString __fastcall Get_DefaultBackRoot();
  virtual System::UnicodeString __fastcall Get_PrintConfirm();
  virtual System::UnicodeString __fastcall Get_BobusPrefix();
  virtual System::UnicodeString __fastcall Get_BobusPostfix();
  virtual _di_IXMLKeyboardCodeType __fastcall Get_KeyboardCode(int Index);
  virtual void __fastcall Set_Login(System::UnicodeString Value);
  virtual void __fastcall Set_Shutdown(System::UnicodeString Value);
  virtual void __fastcall Set_DefaultBackRoot(System::UnicodeString Value);
  virtual void __fastcall Set_PrintConfirm(System::UnicodeString Value);
  virtual void __fastcall Set_BobusPrefix(System::UnicodeString Value);
  virtual void __fastcall Set_BobusPostfix(System::UnicodeString Value);
  virtual _di_IXMLKeyboardCodeType __fastcall Add();
  virtual _di_IXMLKeyboardCodeType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLKeyboardCodeType 

class TXMLKeyboardCodeType : public Xml::Xmldoc::TXMLNode, public IXMLKeyboardCodeType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLKeyboardCodeType 
  virtual System::UnicodeString __fastcall Get_InnerCode();
  virtual System::UnicodeString __fastcall Get_KeyboardName();
  virtual System::UnicodeString __fastcall Get_KeyboardValue();
  virtual void __fastcall Set_InnerCode(System::UnicodeString Value);
  virtual void __fastcall Set_KeyboardName(System::UnicodeString Value);
  virtual void __fastcall Set_KeyboardValue(System::UnicodeString Value);
};

// TXMLCategoryReportType 

class TXMLCategoryReportType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLCategoryReportType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLCategoryReportType 
  virtual System::UnicodeString __fastcall Get_FinishKeys();
  virtual _di_IXMLReportMenuType __fastcall Get_ReportMenu(int Index);
  virtual void __fastcall Set_FinishKeys(System::UnicodeString Value);
  virtual _di_IXMLReportMenuType __fastcall Add();
  virtual _di_IXMLReportMenuType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLReportMenuType 

class TXMLReportMenuType : public Xml::Xmldoc::TXMLNode, public IXMLReportMenuType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLReportMenuType 
  virtual System::UnicodeString __fastcall Get_Caption();
  virtual System::UnicodeString __fastcall Get_QueryID();
  virtual System::UnicodeString __fastcall Get_InnerKeys();
  virtual bool __fastcall Get_HaveStub();
  virtual void __fastcall Set_Caption(System::UnicodeString Value);
  virtual void __fastcall Set_QueryID(System::UnicodeString Value);
  virtual void __fastcall Set_InnerKeys(System::UnicodeString Value);
  virtual void __fastcall Set_HaveStub(bool Value);
};

// TXMLLotteryPosType 

class TXMLLotteryPosType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLLotteryPosType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLLotteryPosType 
  virtual System::UnicodeString __fastcall Get_PosType();
  virtual System::UnicodeString __fastcall Get_UKeyPassword();
  virtual System::UnicodeString __fastcall Get_SalesAccount();
  virtual System::UnicodeString __fastcall Get_SalesPassword();
  virtual int __fastcall Get_NeedConfirmAmount();
  virtual int __fastcall Get_NeedPasswordAmount();
  virtual System::UnicodeString __fastcall Get_Desc();
  virtual _di_IXMLGameType __fastcall Get_Game(int Index);
  virtual void __fastcall Set_PosType(System::UnicodeString Value);
  virtual void __fastcall Set_UKeyPassword(System::UnicodeString Value);
  virtual void __fastcall Set_SalesAccount(System::UnicodeString Value);
  virtual void __fastcall Set_SalesPassword(System::UnicodeString Value);
  virtual void __fastcall Set_NeedConfirmAmount(int Value);
  virtual void __fastcall Set_NeedPasswordAmount(int Value);
  virtual void __fastcall Set_Desc(System::UnicodeString Value);
  virtual _di_IXMLGameType __fastcall Add();
  virtual _di_IXMLGameType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLGameType 

class TXMLGameType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLGameType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLGameType 
  virtual System::UnicodeString __fastcall Get_GameNode();
  virtual System::UnicodeString __fastcall Get_GameID();
  virtual System::UnicodeString __fastcall Get_GameName();
  virtual System::UnicodeString __fastcall Get_EnterKey();
  virtual System::UnicodeString __fastcall Get_StakeToRootKey();
  virtual System::UnicodeString __fastcall Get_DefaultStakeNode();
  virtual _di_IXMLStakeType __fastcall Get_Stake(int Index);
  virtual void __fastcall Set_GameNode(System::UnicodeString Value);
  virtual void __fastcall Set_GameID(System::UnicodeString Value);
  virtual void __fastcall Set_GameName(System::UnicodeString Value);
  virtual void __fastcall Set_EnterKey(System::UnicodeString Value);
  virtual void __fastcall Set_StakeToRootKey(System::UnicodeString Value);
  virtual void __fastcall Set_DefaultStakeNode(System::UnicodeString Value);
  virtual _di_IXMLStakeType __fastcall Add();
  virtual _di_IXMLStakeType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLStakeType 

class TXMLStakeType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLStakeType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLStakeType 
  virtual System::UnicodeString __fastcall Get_StakeNode();
  virtual System::UnicodeString __fastcall Get_StakeName();
  virtual System::UnicodeString __fastcall Get_PlayBetId();
  virtual System::UnicodeString __fastcall Get_FinishedNode();
  virtual System::UnicodeString __fastcall Get_Desc();
  virtual _di_IXMLChoiceType __fastcall Get_Choice(int Index);
  virtual void __fastcall Set_StakeNode(System::UnicodeString Value);
  virtual void __fastcall Set_StakeName(System::UnicodeString Value);
  virtual void __fastcall Set_PlayBetId(System::UnicodeString Value);
  virtual void __fastcall Set_FinishedNode(System::UnicodeString Value);
  virtual void __fastcall Set_Desc(System::UnicodeString Value);
  virtual _di_IXMLChoiceType __fastcall Add();
  virtual _di_IXMLChoiceType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLChoiceType 

class TXMLChoiceType : public Xml::Xmldoc::TXMLNode, public IXMLChoiceType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLChoiceType 
  virtual System::UnicodeString __fastcall Get_ChoiceKey();
  virtual System::UnicodeString __fastcall Get_JumpTo();
  virtual void __fastcall Set_ChoiceKey(System::UnicodeString Value);
  virtual void __fastcall Set_JumpTo(System::UnicodeString Value);
};

// TXMLInnerKeyStringType 

class TXMLInnerKeyStringType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLInnerKeyStringType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLInnerKeyStringType 
  virtual System::UnicodeString __fastcall Get_Desc();
  virtual System::UnicodeString __fastcall Get_InnerKeyCode(int Index);
  virtual void __fastcall Set_Desc(System::UnicodeString Value);
  virtual Xml::Xmlintf::_di_IXMLNode __fastcall Add(const System::UnicodeString InnerKeyCode);
  virtual Xml::Xmlintf::_di_IXMLNode __fastcall Insert(const int Index, const System::UnicodeString InnerKeyCode);
public:
  virtual void __fastcall AfterConstruction(void);
};

// Global Functions 

_di_IXMLDataCenterType __fastcall GetDataCenter(Xml::Xmlintf::_di_IXMLDocument Doc);
_di_IXMLDataCenterType __fastcall GetDataCenter(Xml::Xmldoc::TXMLDocument *Doc);
_di_IXMLDataCenterType __fastcall LoadDataCenter(const System::UnicodeString& FileName);
_di_IXMLDataCenterType __fastcall  NewDataCenter();

#define TargetNamespace ""

#endif