//---------------------------------------------------------------------------

#ifndef TerminalBoxH
#define TerminalBoxH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "Printceptor.h"

#define BUFFERSIZE  16384

class CTerminal;

class CTerminalBox : Printceptor
{
	public:
		__fastcall CTerminalBox(CTerminal *term);

		bool connected;

		bool Init(AnsiString port);
		void Close();

		void ConnectionChanged(bool isConnected);			//����״̬�仯֪ͨ
		void RecieveTerminalStub(BYTE *data, int len);		//����Ʊ���Ĵ���
		void UpdateStatusOk(bool isUpdatedOk);              //�̼��������֪ͨ

		void SendData2Terminal(BYTE *, int len);			//���ն˻����ʹ�ӡ��״̬����
		void SendFirmware(BYTE *firm_data, int len);    	//���¹̼�

		//�ڲ������ַ�������
		int TypeInnerString(AnsiString str);

		//�ַ�������
		void TypeAsciiCode(AnsiString asciiCode);

		//���ü��ʱ��
		void SetKeyInterval(int interval);

		char stubBuffer[BUFFERSIZE];		//����ÿ��Ʊ��Ʊ������
		int stubDataLength;                 //Ʊ�����ݳ���

		void SaveStubToFile(); 				//����Ʊ�����ļ�

	private:
		CTerminal *terminal;

		//��������תASCII�봮
		BYTE TransAsciiCode(AnsiString asciiCode);

};

#endif