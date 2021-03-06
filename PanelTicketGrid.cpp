//------------------------------------------------------------------------
#pragma hdrstop

#include "PanelTicketGrid.h"
#include "Terminal.h"
#include "TerminalCategory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
__fastcall CTicketGrid::CTicketGrid(TComponent* Owner, CTerminal *term) : TStringGrid(Owner){
	terminal =term;
	//
	ColCount =8;
	RowCount =101;				//固定101行数据，处理时少几次循环
	FixedRows =1;
	FixedCols =1;
	DefaultRowHeight =18;
	BevelInner =bvRaised;
	BevelOuter =bvLowered;
	ScrollBars =ssVertical;
	Options >> goRangeSelect;	//屏蔽区域多选，>>  或者 <<  就是选择和屏蔽
	Cursor =crHandPoint;        //默认手型光标
	//
	Cells[0][0]="序";
	Cells[1][0]="票号";
	Cells[0][1]="now";
	for (int i = 2; i < RowCount; i++)	Cells[0][i]= IntToStr(i-1);
	Cells[4][0]="玩法ID";       //三层组合，中间加-
	Cells[6][0]="注数";
	Cells[7][0]="金额";
	//宽度
	ColWidths[0] =32;
	ColWidths[1] =68;
	ColWidths[3] =62;
	ColWidths[4] =0;
	ColWidths[5] =93;
	ColWidths[6] =0;
	ColWidths[7] =0;
}

//---------------------------------------------------------------------------
void CTicketGrid::InsertBlankRow(int row){
	for (int i =0; i <ColCount; i++) Cells[i][RowCount-1] ="";		//先把队尾那行清空，然后挪到指定行，骗人的技巧，呵呵
	MoveRow(RowCount-1, row);
	this->Row =row;
	for (int i =row; i < RowCount; i++) Cells[0][i]= IntToStr(i -1);   //首列序号从本行往下重排
}

//---------------------------------------------------------------------------
void CTicketGrid::DeleteTicket(int row){
	for (int i =0; i <ColCount; i++) Cells[i][row] ="";           	//先清空，免得有问题，删不掉重复打印
	MoveRow(row, RowCount-1);										//直接把指定行挪到队尾，然后把队尾这行数值清空删除之
	for (int i =0; i <ColCount; i++) Cells[i][RowCount-1] ="";
	this->Row =row;
	for (int i =row; i < RowCount; i++) Cells[0][i]= IntToStr(i -1);	//首列序号从本行往下重排
}

void CTicketGrid::ClearAll(){       //显示模式切换后，清空所有内容
	for (int i =2; i <RowCount; i++)
		for (int j =1;j <8; j ++)
			Cells[j][i] ="";
}
