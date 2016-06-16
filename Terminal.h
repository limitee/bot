//---------------------------------------------------------------------------
#ifndef TerminalH
#define TerminalH

#include "TerminalConfig.h"

#include "DefineStruct.h"
//---------------------------------------------------------------------------

class CTerminalBox;
class CTerminalConnection;
class CTerminalRobotTyper;
class CTerminalDaemon;

class CTerminalPanel;
class CTerminalCategory;

class CTerminal
{
	public:
		//��һ������XML�ṹ������ĳ�ʼ������
		CTerminal(_di_IXMLTerminalType terminalXML);

		bool Init();		//��ʼ������������ͼ���ӳ������
		bool Logon();		//��¼
		void Shutdown();	//ֹͣ������

		void NotifyStub(int money, AnsiString stub);

		//���ն˵ĸ�����������ǩҳ���桢�Զ���Ʊ�ҽ�����Ա���񡢵���Ʊ�����񡢴�ӡ�������Զ����������Ķ�̬�����
		_di_IXMLTerminalType xmlConfig;

		CTerminalPanel *panel;
		CTerminalCategory *monitor;

		CTerminalRobotTyper *robotTyper;
		CTerminalDaemon *daemon;

		CTerminalConnection *connection;
		CTerminalBox *box;

		//���¼����������Ƕ�̬���еĺ�������
		HINSTANCE terminalDriver;		//Ӳ���ն˻���������̬��
		//���˽��յ����ݲ������Ƿ�Ӧ��result��resp���ǳ��ڲ�����������ı�����result��ע�����retLenƫ�������������֮ǰ���յĲ������ݣ�Ӧ��ı�����resp��
		void __stdcall(*FilterResponse)(BYTE *src, int &srcLen, char *resp, int &rspLen, int &cutPaper);
		//��֤����ȡƱ����Ϣ���ݣ�����Ʊ��˶ԣ�����ֵΪƱ��� <=0����ʧ��
		int __stdcall(*ParserVerifyStub)(int dataLen, BYTE *data, char *stubBytes);

		//��������ϵͳ�����䶯̬��
		HINSTANCE posDriver;
		//�����Ʊ���ͺ��뱶����ԭʼ��Ϣ����������Ʊ�Ĵ�ӡ�������У��Ա㲻ͬ����������
		void __stdcall(*GeneralTicketKeyStr)(AnsiString gameKind, AnsiString number, int times, char *keys);
		//�����н����кţ��������
		void __stdcall(*GeneralBonusKeyStr)(AnsiString seq, char *keys);

		//���Ҷ�λ�ͼ��㰴��ֵ���ĸ�������
		AnsiString getJumpInnerCodeString(_di_IXMLStakeType last, _di_IXMLStakeType current);

		_di_IXMLStakeType findStakeById(AnsiString gameId, AnsiString betId);
		AnsiString GetStakeNameById(AnsiString gameId, AnsiString betId);
		_di_IXMLStakeType findStakeByNode(AnsiString node);
		_di_IXMLKeyboardCodeType findKeyboardCodeByInnerCode(AnsiString innerCode);

		_di_IXMLStakeType lastStake;        //��һ�Ų�Ʊ�ڵ�
		_di_IXMLStakeType currentStake;     //��ǰ���Ų�Ʊ�ڵ�

		//�Ƿ���Ҫ����
		bool needReset;

		//��ǰ�Ĵ��������Ʊ��
		Request *currentRequest;
		Stub *currentStub;

		//���õ�״̬�����
		WorkStatus status;

		void ResetTerminalContext();		 //�ն������ĸ�λ��ֻ���������߳�

	private:
		//���Ҷ�λ�ͼ��㲻ͬͶע������ת����ֵ���ĸ�����������ͬ�淨�е�
		AnsiString getGameJumpInnerCodeString(_di_IXMLStakeType last, _di_IXMLStakeType current);

		TCriticalSection *lock;
};

#endif
