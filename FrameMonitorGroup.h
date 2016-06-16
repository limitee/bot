//---------------------------------------------------------------------------

#ifndef FrameMonitorGroupH
#define FrameMonitorGroupH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <System.ImageList.hpp>

class CTerminal;

//---------------------------------------------------------------------------
class TFrameMonitor : public TFrame
{
__published:	// IDE-managed Components
	TCategoryPanelGroup *CategoryPanelGroup;
	TImageList *ImageListTerminal;

	void __fastcall FrameMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall FrameResize(TObject *Sender);

private:	// User declarations
	int echoErrIndex;		//������ʾ����ѯID����Ӧ�д�����Ϣ���ն˵��±�

public:		// User declarations
	__fastcall TFrameMonitor(TComponent* Owner);

	CTerminal *currentTerminal;
	TPanel *PanelCurrentTerminal;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrameMonitor *FrameMonitor;
//---------------------------------------------------------------------------
#endif