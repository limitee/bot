//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FrameMonitorGroup.h"
#include "TicketCenterNodeApp.h"

#include "Terminal.h"
#include "TerminalBox.h"
#include "TerminalPanel.h"
#include "TerminalCategory.h"
#include "TerminalConnection.h"
#include "TerminalRobotTyper.h"

#include "MediaSupport.h"
#include "Controller.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrameMonitor *FrameMonitor;
//---------------------------------------------------------------------------
__fastcall TFrameMonitor::TFrameMonitor(TComponent* Owner) : TFrame(Owner){
	echoErrIndex =0;
	currentTerminal =NULL;
	PanelCurrentTerminal =NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFrameMonitor::FrameMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled){
	if (WheelDelta >0) {	//向上滚动，好像不管用，以后再看吧
		FrameMonitor->VertScrollBar->Position -=FrameMonitor->VertScrollBar->Increment;
	}else{
		FrameMonitor->VertScrollBar->Position +=FrameMonitor->VertScrollBar->Increment;
	}
	Handled =true;
}
//---------------------------------------------------------------------------
void __fastcall TFrameMonitor::FrameResize(TObject *Sender){
	CategoryPanelGroup->Height =this->Height;
	if (PanelCurrentTerminal !=NULL) {		//当前面板的位置和大小调整
		PanelCurrentTerminal->Width =this->Width -200;
		PanelCurrentTerminal->Height =this->Height;
	}
}
//---------------------------------------------------------------------------


