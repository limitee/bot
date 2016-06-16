
// ************************************************************************** //
//                                                                          
//                             XML Data Binding                             
//                                                                          
//         Generated on: 2016-05-17 21:03:04                                
//       Generated from: D:\LottChina\TicketCenterNode\TerminalConfig.xsd   
//   Settings stored in: D:\LottChina\TicketCenterNode\TerminalConfig.xdb   
//                                                                          
// ************************************************************************** //

#include <System.hpp>
#pragma hdrstop

#include "TerminalConfig.h"


// Global Functions 

_di_IXMLDataCenterType __fastcall GetDataCenter(Xml::Xmlintf::_di_IXMLDocument Doc)
{
  return (_di_IXMLDataCenterType) Doc->GetDocBinding("DataCenter", __classid(TXMLDataCenterType), TargetNamespace);
};

_di_IXMLDataCenterType __fastcall GetDataCenter(Xml::Xmldoc::TXMLDocument *Doc)
{
  Xml::Xmlintf::_di_IXMLDocument DocIntf;
  Doc->GetInterface(DocIntf);
  return GetDataCenter(DocIntf);
};

_di_IXMLDataCenterType __fastcall LoadDataCenter(const System::UnicodeString& FileName)
{
  return (_di_IXMLDataCenterType) Xml::Xmldoc::LoadXMLDocument(FileName)->GetDocBinding("DataCenter", __classid(TXMLDataCenterType), TargetNamespace);
};

_di_IXMLDataCenterType __fastcall  NewDataCenter()
{
  return (_di_IXMLDataCenterType) Xml::Xmldoc::NewXMLDocument()->GetDocBinding("DataCenter", __classid(TXMLDataCenterType), TargetNamespace);
};

// TXMLDataCenterType 

void __fastcall TXMLDataCenterType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("Terminal"), __classid(TXMLTerminalType));
  ItemTag = "Terminal";
  ItemInterface = __uuidof(IXMLTerminalType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLDataCenterType::Get_CenterCode()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("CenterCode")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLDataCenterType::Set_CenterCode(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("CenterCode"), Value);
};

System::UnicodeString __fastcall TXMLDataCenterType::Get_ServerHost()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("ServerHost")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLDataCenterType::Set_ServerHost(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("ServerHost"), Value);
};

int __fastcall TXMLDataCenterType::Get_ServerPort()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("ServerPort")]->NodeValue.operator int();
};

void __fastcall TXMLDataCenterType::Set_ServerPort(int Value)
{
  SetAttribute(System::UnicodeString("ServerPort"), Value);
};

System::UnicodeString __fastcall TXMLDataCenterType::Get_BinFileDir()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("BinFileDir")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLDataCenterType::Set_BinFileDir(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("BinFileDir"), Value);
};

System::UnicodeString __fastcall TXMLDataCenterType::Get_HexFileDir()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("HexFileDir")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLDataCenterType::Set_HexFileDir(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("HexFileDir"), Value);
};

System::UnicodeString __fastcall TXMLDataCenterType::Get_PrinterCom()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("PrinterCom")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLDataCenterType::Set_PrinterCom(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("PrinterCom"), Value);
};

System::UnicodeString __fastcall TXMLDataCenterType::Get_PrinterComParam()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("PrinterComParam")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLDataCenterType::Set_PrinterComParam(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("PrinterComParam"), Value);
};

System::UnicodeString __fastcall TXMLDataCenterType::Get_Desc()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("Desc")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLDataCenterType::Set_Desc(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("Desc"), Value);
};

_di_IXMLTerminalType __fastcall TXMLDataCenterType::Get_Terminal(int Index)
{
  return (_di_IXMLTerminalType) List->Nodes[Index];
};

_di_IXMLTerminalType __fastcall TXMLDataCenterType::Add()
{
  return (_di_IXMLTerminalType) AddItem(-1);
};

_di_IXMLTerminalType __fastcall TXMLDataCenterType::Insert(const int Index)
{
  return (_di_IXMLTerminalType) AddItem(Index);
};

// TXMLTerminalType 

void __fastcall TXMLTerminalType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("Keyboard"), __classid(TXMLKeyboardType));
  RegisterChildNode(System::UnicodeString("CategoryReport"), __classid(TXMLCategoryReportType));
  RegisterChildNode(System::UnicodeString("LotteryPos"), __classid(TXMLLotteryPosType));
  Xml::Xmldoc::TXMLNode::AfterConstruction();
};

System::UnicodeString __fastcall TXMLTerminalType::Get_TerminalID()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("TerminalID")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLTerminalType::Set_TerminalID(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("TerminalID"), Value);
};

System::UnicodeString __fastcall TXMLTerminalType::Get_TerminalType()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("TerminalType")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLTerminalType::Set_TerminalType(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("TerminalType"), Value);
};

System::UnicodeString __fastcall TXMLTerminalType::Get_ConnectionKey()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("ConnectionKey")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLTerminalType::Set_ConnectionKey(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("ConnectionKey"), Value);
};

System::UnicodeString __fastcall TXMLTerminalType::Get_BoxComParam()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("BoxComParam")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLTerminalType::Set_BoxComParam(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("BoxComParam"), Value);
};

bool __fastcall TXMLTerminalType::Get_EnableAutoRun()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("EnableAutoRun")]->NodeValue.operator bool();
};

void __fastcall TXMLTerminalType::Set_EnableAutoRun(bool Value)
{
  SetAttribute(System::UnicodeString("EnableAutoRun"), Value);
};

System::UnicodeString __fastcall TXMLTerminalType::Get_Desc()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("Desc")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLTerminalType::Set_Desc(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("Desc"), Value);
};

_di_IXMLKeyboardType __fastcall TXMLTerminalType::Get_Keyboard()
{
  return (_di_IXMLKeyboardType) GetChildNodes()->Nodes[System::UnicodeString("Keyboard")];
};

_di_IXMLCategoryReportType __fastcall TXMLTerminalType::Get_CategoryReport()
{
  return (_di_IXMLCategoryReportType) GetChildNodes()->Nodes[System::UnicodeString("CategoryReport")];
};

_di_IXMLLotteryPosType __fastcall TXMLTerminalType::Get_LotteryPos()
{
  return (_di_IXMLLotteryPosType) GetChildNodes()->Nodes[System::UnicodeString("LotteryPos")];
};

// TXMLKeyboardType 

void __fastcall TXMLKeyboardType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("KeyboardCode"), __classid(TXMLKeyboardCodeType));
  ItemTag = "KeyboardCode";
  ItemInterface = __uuidof(IXMLKeyboardCodeType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLKeyboardType::Get_Login()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("Login")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardType::Set_Login(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("Login"), Value);
};

System::UnicodeString __fastcall TXMLKeyboardType::Get_Shutdown()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("Shutdown")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardType::Set_Shutdown(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("Shutdown"), Value);
};

System::UnicodeString __fastcall TXMLKeyboardType::Get_DefaultBackRoot()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("DefaultBackRoot")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardType::Set_DefaultBackRoot(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("DefaultBackRoot"), Value);
};

System::UnicodeString __fastcall TXMLKeyboardType::Get_PrintConfirm()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("PrintConfirm")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardType::Set_PrintConfirm(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("PrintConfirm"), Value);
};

System::UnicodeString __fastcall TXMLKeyboardType::Get_BobusPrefix()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("BobusPrefix")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardType::Set_BobusPrefix(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("BobusPrefix"), Value);
};

System::UnicodeString __fastcall TXMLKeyboardType::Get_BobusPostfix()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("BobusPostfix")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardType::Set_BobusPostfix(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("BobusPostfix"), Value);
};

_di_IXMLKeyboardCodeType __fastcall TXMLKeyboardType::Get_KeyboardCode(int Index)
{
  return (_di_IXMLKeyboardCodeType) List->Nodes[Index];
};

_di_IXMLKeyboardCodeType __fastcall TXMLKeyboardType::Add()
{
  return (_di_IXMLKeyboardCodeType) AddItem(-1);
};

_di_IXMLKeyboardCodeType __fastcall TXMLKeyboardType::Insert(const int Index)
{
  return (_di_IXMLKeyboardCodeType) AddItem(Index);
};

// TXMLKeyboardCodeType 

System::UnicodeString __fastcall TXMLKeyboardCodeType::Get_InnerCode()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("InnerCode")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardCodeType::Set_InnerCode(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("InnerCode"), Value);
};

System::UnicodeString __fastcall TXMLKeyboardCodeType::Get_KeyboardName()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("KeyboardName")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardCodeType::Set_KeyboardName(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("KeyboardName"), Value);
};

System::UnicodeString __fastcall TXMLKeyboardCodeType::Get_KeyboardValue()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("KeyboardValue")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLKeyboardCodeType::Set_KeyboardValue(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("KeyboardValue"), Value);
};

// TXMLCategoryReportType 

void __fastcall TXMLCategoryReportType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("ReportMenu"), __classid(TXMLReportMenuType));
  ItemTag = "ReportMenu";
  ItemInterface = __uuidof(IXMLReportMenuType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLCategoryReportType::Get_FinishKeys()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("FinishKeys")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLCategoryReportType::Set_FinishKeys(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("FinishKeys"), Value);
};

_di_IXMLReportMenuType __fastcall TXMLCategoryReportType::Get_ReportMenu(int Index)
{
  return (_di_IXMLReportMenuType) List->Nodes[Index];
};

_di_IXMLReportMenuType __fastcall TXMLCategoryReportType::Add()
{
  return (_di_IXMLReportMenuType) AddItem(-1);
};

_di_IXMLReportMenuType __fastcall TXMLCategoryReportType::Insert(const int Index)
{
  return (_di_IXMLReportMenuType) AddItem(Index);
};

// TXMLReportMenuType 

System::UnicodeString __fastcall TXMLReportMenuType::Get_Caption()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("Caption")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLReportMenuType::Set_Caption(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("Caption"), Value);
};

System::UnicodeString __fastcall TXMLReportMenuType::Get_QueryID()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("QueryID")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLReportMenuType::Set_QueryID(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("QueryID"), Value);
};

System::UnicodeString __fastcall TXMLReportMenuType::Get_InnerKeys()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("InnerKeys")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLReportMenuType::Set_InnerKeys(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("InnerKeys"), Value);
};

bool __fastcall TXMLReportMenuType::Get_HaveStub()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("HaveStub")]->NodeValue.operator bool();
};

void __fastcall TXMLReportMenuType::Set_HaveStub(bool Value)
{
  SetAttribute(System::UnicodeString("HaveStub"), Value);
};

// TXMLLotteryPosType 

void __fastcall TXMLLotteryPosType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("Game"), __classid(TXMLGameType));
  ItemTag = "Game";
  ItemInterface = __uuidof(IXMLGameType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLLotteryPosType::Get_PosType()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("PosType")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLLotteryPosType::Set_PosType(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("PosType"), Value);
};

System::UnicodeString __fastcall TXMLLotteryPosType::Get_UKeyPassword()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("UKeyPassword")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLLotteryPosType::Set_UKeyPassword(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("UKeyPassword"), Value);
};

System::UnicodeString __fastcall TXMLLotteryPosType::Get_SalesAccount()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("SalesAccount")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLLotteryPosType::Set_SalesAccount(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("SalesAccount"), Value);
};

System::UnicodeString __fastcall TXMLLotteryPosType::Get_SalesPassword()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("SalesPassword")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLLotteryPosType::Set_SalesPassword(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("SalesPassword"), Value);
};

int __fastcall TXMLLotteryPosType::Get_NeedConfirmAmount()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("NeedConfirmAmount")]->NodeValue.operator int();
};

void __fastcall TXMLLotteryPosType::Set_NeedConfirmAmount(int Value)
{
  SetAttribute(System::UnicodeString("NeedConfirmAmount"), Value);
};

int __fastcall TXMLLotteryPosType::Get_NeedPasswordAmount()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("NeedPasswordAmount")]->NodeValue.operator int();
};

void __fastcall TXMLLotteryPosType::Set_NeedPasswordAmount(int Value)
{
  SetAttribute(System::UnicodeString("NeedPasswordAmount"), Value);
};

System::UnicodeString __fastcall TXMLLotteryPosType::Get_Desc()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("Desc")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLLotteryPosType::Set_Desc(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("Desc"), Value);
};

_di_IXMLGameType __fastcall TXMLLotteryPosType::Get_Game(int Index)
{
  return (_di_IXMLGameType) List->Nodes[Index];
};

_di_IXMLGameType __fastcall TXMLLotteryPosType::Add()
{
  return (_di_IXMLGameType) AddItem(-1);
};

_di_IXMLGameType __fastcall TXMLLotteryPosType::Insert(const int Index)
{
  return (_di_IXMLGameType) AddItem(Index);
};

// TXMLGameType 

void __fastcall TXMLGameType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("Stake"), __classid(TXMLStakeType));
  ItemTag = "Stake";
  ItemInterface = __uuidof(IXMLStakeType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLGameType::Get_GameNode()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("GameNode")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLGameType::Set_GameNode(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("GameNode"), Value);
};

System::UnicodeString __fastcall TXMLGameType::Get_GameID()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("GameID")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLGameType::Set_GameID(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("GameID"), Value);
};

System::UnicodeString __fastcall TXMLGameType::Get_GameName()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("GameName")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLGameType::Set_GameName(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("GameName"), Value);
};

System::UnicodeString __fastcall TXMLGameType::Get_EnterKey()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("EnterKey")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLGameType::Set_EnterKey(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("EnterKey"), Value);
};

System::UnicodeString __fastcall TXMLGameType::Get_StakeToRootKey()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("StakeToRootKey")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLGameType::Set_StakeToRootKey(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("StakeToRootKey"), Value);
};

System::UnicodeString __fastcall TXMLGameType::Get_DefaultStakeNode()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("DefaultStakeNode")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLGameType::Set_DefaultStakeNode(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("DefaultStakeNode"), Value);
};

_di_IXMLStakeType __fastcall TXMLGameType::Get_Stake(int Index)
{
  return (_di_IXMLStakeType) List->Nodes[Index];
};

_di_IXMLStakeType __fastcall TXMLGameType::Add()
{
  return (_di_IXMLStakeType) AddItem(-1);
};

_di_IXMLStakeType __fastcall TXMLGameType::Insert(const int Index)
{
  return (_di_IXMLStakeType) AddItem(Index);
};

// TXMLStakeType 

void __fastcall TXMLStakeType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("Choice"), __classid(TXMLChoiceType));
  ItemTag = "Choice";
  ItemInterface = __uuidof(IXMLChoiceType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLStakeType::Get_StakeNode()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("StakeNode")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLStakeType::Set_StakeNode(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("StakeNode"), Value);
};

System::UnicodeString __fastcall TXMLStakeType::Get_StakeName()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("StakeName")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLStakeType::Set_StakeName(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("StakeName"), Value);
};

System::UnicodeString __fastcall TXMLStakeType::Get_PlayBetId()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("PlayBetId")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLStakeType::Set_PlayBetId(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("PlayBetId"), Value);
};

System::UnicodeString __fastcall TXMLStakeType::Get_FinishedNode()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("FinishedNode")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLStakeType::Set_FinishedNode(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("FinishedNode"), Value);
};

System::UnicodeString __fastcall TXMLStakeType::Get_Desc()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("Desc")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLStakeType::Set_Desc(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("Desc"), Value);
};

_di_IXMLChoiceType __fastcall TXMLStakeType::Get_Choice(int Index)
{
  return (_di_IXMLChoiceType) List->Nodes[Index];
};

_di_IXMLChoiceType __fastcall TXMLStakeType::Add()
{
  return (_di_IXMLChoiceType) AddItem(-1);
};

_di_IXMLChoiceType __fastcall TXMLStakeType::Insert(const int Index)
{
  return (_di_IXMLChoiceType) AddItem(Index);
};

// TXMLChoiceType 

System::UnicodeString __fastcall TXMLChoiceType::Get_ChoiceKey()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("ChoiceKey")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLChoiceType::Set_ChoiceKey(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("ChoiceKey"), Value);
};

System::UnicodeString __fastcall TXMLChoiceType::Get_JumpTo()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("JumpTo")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLChoiceType::Set_JumpTo(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("JumpTo"), Value);
};

// TXMLInnerKeyStringType 

void __fastcall TXMLInnerKeyStringType::AfterConstruction(void)
{
  ItemTag = "InnerKeyCode";
  ItemInterface = __uuidof(Xml::Xmlintf::IXMLNode);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLInnerKeyStringType::Get_Desc()
{
  return GetAttributeNodes()->Nodes[System::UnicodeString("Desc")]->NodeValue.operator System::UnicodeString();
};

void __fastcall TXMLInnerKeyStringType::Set_Desc(System::UnicodeString Value)
{
  SetAttribute(System::UnicodeString("Desc"), Value);
};

System::UnicodeString __fastcall TXMLInnerKeyStringType::Get_InnerKeyCode(int Index)
{
  return List->Nodes[Index]->NodeValue.operator System::UnicodeString();
};

Xml::Xmlintf::_di_IXMLNode __fastcall TXMLInnerKeyStringType::Add(const System::UnicodeString InnerKeyCode)
{
  Xml::Xmlintf::_di_IXMLNode item = AddItem(-1);
  item->NodeValue = InnerKeyCode;
  return item;
};

Xml::Xmlintf::_di_IXMLNode __fastcall TXMLInnerKeyStringType::Insert(const int Index, const System::UnicodeString InnerKeyCode)
{
  Xml::Xmlintf::_di_IXMLNode item = AddItem(Index);
  item->NodeValue = InnerKeyCode;
  return item;
};
