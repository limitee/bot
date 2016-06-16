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
		Application->Title = "中彩乐投 LottChina 彩票机器人";
		Application->MainFormOnTaskBar = true;
		HANDLE hMutex =CreateMutex(NULL, true, "LottChina");		//相同进程的互斥
		if (GetLastError() ==ERROR_ALREADY_EXISTS){
			CloseHandle(hMutex);
			MessageBox(Application->Handle, "彩票机器人程序已经在运行中，不能重复启动！", "错误提示", MB_OK +MB_ICONWARNING);
			Application->Terminate();
			return 0;
		}
		ReleaseMutex(hMutex);
		//启动程序主界面
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

