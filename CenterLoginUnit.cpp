//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <inifiles.hpp>

#include "CenterLoginUnit.h"
#include "TicketCenterNodeApp.h"
#include "Controller.h"

#include "LogSupport.h"
#include "MD5.h"
#include "json.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoginForm *LoginForm;
//---------------------------------------------------------------------------
__fastcall TLoginForm::TLoginForm(TComponent* Owner): TForm(Owner){}

//---------------------------------------------------------------------------
void __fastcall TLoginForm::BitBtn1Click(TObject *Sender){
	AnsiString account =EditAccount->Text;
	AnsiString passwd =MaskEditPasswd->Text;
	if (account =="" || passwd ==""){
        ShowMessage("请填写出票中心的登录账号和密码。");
        return;
	}
	AnsiString resp =CenterLogin(account, passwd);

	controller->logSupport->WriteLogWithTime(resp);

	if (resp.Pos("操作成功") >=0) {		//解析结果，记录秘钥
		if (CheckBoxRemenber->Checked){
			Json::Reader reader;
			Json::Value result;
			if (reader.parse(resp.c_str(), result)) {
				AnsiString bodyString =result["body"].asCString();  //body是字符串，不是对象
				Json::Value body;
				reader.parse(bodyString.c_str(), body);
				int userId =body["userId"].asInt();
				AnsiString st =body["st"].asCString();
				TIniFile *ini = new TIniFile(GetCurrentDir() + "\\app.ini");
				ini->WriteInteger("Center", "UserId", userId);
				ini->WriteString("Center", "ST", st);
				delete ini;
                //
				controller->centerId =userId;
				controller->centerSt =st;
			}
		}
        LoginForm->Close();
	}
}
//-------------------------------------------------------------------------------------------------------
AnsiString TLoginForm::CenterLogin(AnsiString account, AnsiString passwd){
	AnsiString body ="{\"uuid\":\"" +controller->GetGUID() +"\"}";
	TStringList *strs = new TStringList();
	strs->Add("head=" +PackageHeadJson(CMD_CENTER_LOGIN, body, account, passwd));
	strs->Add("body=" +body);
	//请求并获得应答
	TStringStream *resp = new TStringStream();
	try{
		IdHTTP->Post(GATE_WAY, strs, resp);
	}catch(...){
	}
	delete strs;
	AnsiString responseStr =Utf8ToAnsi(resp->DataString);     	//UTF8需转换

	return responseStr;
}

//-------------------------------------------------------------------------------------------------------
AnsiString TLoginForm::PackageHeadJson(AnsiString cmd, AnsiString jsonBody, AnsiString account, AnsiString passwd){
	AnsiString timeStamp =FormatDateTime("yyyy-mm-dd", Now()) +" "+FormatDateTime("hh:nn:ss.zzz000 +08:00", Now());
	AnsiString key =MD5_CodeString(passwd);
	AnsiString md5degist =MD5_CodeString(AnsiStringToUtf8(key +jsonBody +timeStamp));
	AnsiString head ="{\"cmd\":\"" +cmd +"\",\"digest\":\"" +md5degist +"\",\"digestType\":\"md5\",\"timeStamp\":\"" +timeStamp +"\",\"userId\":\"" +account +"\",\"userType\":\"center\"}";
	return head;
}

//---------------------------------------------------------------------------
