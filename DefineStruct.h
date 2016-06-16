//---------------------------------------------------------------------------
#ifndef LotteryStructH
#define LotteryStructH

#include <vcl.h>

#define LOG_FILE_NAME	"log.txt"

#define LOGIN_URL		"http://121.42.197.2:4000/center_login.html"
#define GATE_WAY		"http://121.42.197.2:4000/api/data"

#define	CMD_CENTER_LOGIN	"CR01"

#define	CMD_TERMINAL_LOGIN	"T01"
#define	CMD_TICKET			"T02"
#define CMD_BONUS 			"T03"
#define CMD_QUERY_TERM		"T04"
#define CMD_QUERY_RECEIPT	"T05"

#define CMD_HEART_BEAT 		"T10"
#define CMD_TICKET_RESET 	"T11"
#define CMD_STUB_REPAIR 	"T12"
#define CMD_STUB_REPORT 	"T13"

enum WorkStatus{
	ERR =-1, 	      	//����
	INIT =0,            //��ʼ����
	LOGON =1,           //�ն˻���¼��
	IDLE =5,            //����
	PRINT =6,           //æ�����ڴ�ӡ��Ʊ
	AWARD =7,           //æ������ˢƱ�ҽ�
	REPORT =8           //æ�����ڲ�ѯ�򱨱�ͳ��
};

//��������ͨ������ĸ������ݽṹ
enum RequestTypeEnum{ TICKET =1, BONUS =2, QUERY =3 };

class Request{
	public:
		virtual ~Request(){};	//����������������Ϊ�麯��������delete���������ʱ�ڴ�й©��

		RequestTypeEnum reqType;
};

class Ticket :Request{
	public:
		Ticket(){
			reqType =TICKET;
			fileData =false;
		}

		int id;				//Ʊ��
		AnsiString number;	//Ͷע����
		int multiple;		//��Ͷ��
		int icount;			//ע��
		int amount;			//���
		AnsiString gameId;  //��Ϸ
		AnsiString playType;
		AnsiString betType;

		bool fileData;		//�Ƿ�Ϊ�����ļ���Ʊʱ��
};

class Bonus :Request{
	public:
		Bonus(){ reqType =BONUS; }

		int id;					//Ʊ��
		AnsiString seq;			//������
		double bonus;			//�н����
		double bonus_after_tax;	//˰�󽱽�
};

class Query :Request{
	public:
		Query(){ reqType =QUERY; }
		AnsiString queryCmdType;	//�����ѯ���������ͣ��������ֲ�ͬ�Ĳ�ѯ����ֱ��ʹ��������

		AnsiString gameId;  //��ѯ������Ϣ
		int type;			//���ͣ�0Ϊ��ѯ��ǰ�ڣ�1Ϊ����
};

struct Stub{
	Request *request;       //��Ӧ�������ĵ�ַ������ɾ��
	int status;				//״̬��1�ɹ���0ʧ��
	int money;				//Ʊ���Ͻ������Ľ��
	AnsiString stub;		//Ʊ���ı�
};

#endif
