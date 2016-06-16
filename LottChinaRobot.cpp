//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>

USEFORM("TicketCenterNodeApp.cpp", MainForm);
USEFORM("FrameMonitorGroup.cpp", FrameMonitor); /* TFrame: File Type */
USEFORM("ConfigUnit.cpp", ConfigForm);
USEFORM("CenterLoginUnit.cpp", LoginForm);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int){
	try{
		Application->Initialize();
		Application->Title = "�в���Ͷ LottChina ��Ʊ������";
		Application->MainFormOnTaskBar = true;
		HANDLE hMutex =CreateMutex(NULL, true, "LottChina");		//��ͬ���̵Ļ���
		if (GetLastError() ==ERROR_ALREADY_EXISTS){
			CloseHandle(hMutex);
			MessageBox(Application->Handle, "��Ʊ�����˳����Ѿ��������У������ظ�������", "������ʾ", MB_OK +MB_ICONWARNING);
			Application->Terminate();
			return 0;
		}
		ReleaseMutex(hMutex);
		//��������������
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TLoginForm), &LoginForm);
		Application->CreateForm(__classid(TConfigForm), &ConfigForm);
		Application->Run();
	}catch (Exception &exception){
		Application->ShowException(&exception);
	}catch (...){
		try{
			throw Exception("");
		}catch (Exception &exception){
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
