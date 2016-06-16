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
	RowCount =101;				//�̶�101�����ݣ�����ʱ�ټ���ѭ��
	FixedRows =1;
	FixedCols =1;
	DefaultRowHeight =18;
	BevelInner =bvRaised;
	BevelOuter =bvLowered;
	ScrollBars =ssVertical;
	Options >> goRangeSelect;	//���������ѡ��>>  ���� <<  ����ѡ�������
	Cursor =crHandPoint;        //Ĭ�����͹��
	//
	Cells[0][0]="��";
	Cells[1][0]="Ʊ��";
	Cells[0][1]="now";
	for (int i = 2; i < RowCount; i++)	Cells[0][i]= IntToStr(i-1);
	Cells[4][0]="�淨ID";       //������ϣ��м��-
	Cells[6][0]="ע��";
	Cells[7][0]="���";
	//����
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
	for (int i =0; i <ColCount; i++) Cells[i][RowCount-1] ="";		//�ȰѶ�β������գ�Ȼ��Ų��ָ���У�ƭ�˵ļ��ɣ��Ǻ�
	MoveRow(RowCount-1, row);
	this->Row =row;
	for (int i =row; i < RowCount; i++) Cells[0][i]= IntToStr(i -1);   //������Ŵӱ�����������
}

//---------------------------------------------------------------------------
void CTicketGrid::DeleteTicket(int row){
	for (int i =0; i <ColCount; i++) Cells[i][row] ="";           	//����գ���������⣬ɾ�����ظ���ӡ
	MoveRow(row, RowCount-1);										//ֱ�Ӱ�ָ����Ų����β��Ȼ��Ѷ�β������ֵ���ɾ��֮
	for (int i =0; i <ColCount; i++) Cells[i][RowCount-1] ="";
	this->Row =row;
	for (int i =row; i < RowCount; i++) Cells[0][i]= IntToStr(i -1);	//������Ŵӱ�����������
}

void CTicketGrid::ClearAll(){       //��ʾģʽ�л��������������
	for (int i =2; i <RowCount; i++)
		for (int j =1;j <8; j ++)
			Cells[j][i] ="";
}