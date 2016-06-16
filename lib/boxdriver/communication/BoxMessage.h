//---------------------------------------------------------------------------

#ifndef BoxMessageH
#define BoxMessageH
//---------------------------------------------------------------------------

#include <windows.h>
#include "Array.h"

class BoxMessage{
public:
	enum BoxMessageEnum{
		BOX_POS_DATA = 0X01, //"���ص�POS����"
		BOX_RESPONSE = 0x02, // "Box����ȷ����Ϣ"),
		BOX_HEART_BEAT = 0x03, // "��App��������Ϣһһ��Ӧ��Ӧ��ʹ��"),
		BOX_CPU_FIRM = 0x04, //"Ӳ����Ϣ"),
		BOX_PRINTER_DATA = 0x05,// "���صĴ�ӡ������"),
		BOX_STATUS_REPORT = 0x06, // "BOX״̬���棬����ʼ����"),
		BOX_NOTIFY_PAPERLESS_RESPONSE = 0X07,// "Box��Ӧ�л���ֽ��ֽ"),
		BOX_NOTIFY_UPDATE_STATUS = 0X08,//"Box�̼�����״̬"),
		BOX_NOTIFY_AP_REPORT = 0X09,// "Box�����ռ�MAC��Ϣ"),
		BOX_NOTIFY_QR_REQUEST = 0X10,// "Box��APP�����µĶ�ά��"),

		APP_HANDSHAKE = 0x80, // "����,ͨѶ�Ŀ�ʼ"),
		APP_RESPONSE = 0x81, // "App����ȷ����Ϣ"),
		APP_POS_DATA = 0x82, //true, "�˵걦ת��POS����ӡ��������"),
		APP_KEYBOARD = 0x83, //"ģ��ļ��̰���"),
		APP_QUERY_INFO = 0x84,// "Ӳ����Ϣ��ѯ��CPU��ID���̼���Ϣ"),
		APP_CONFIG = 0x85,// "�·����ô�ӡ���Ĳ���"),
		APP_HEART_BEAT = 0x86, //"��������"),
		APP_UPDATE_FIRM = 0x87,// "���¹̼�"),
		APP_RESET = 0x88,// "BOX��λ"),
		APP_PRINTER_DATA = 0x89,// "�·��Ĵ�ӡ��ģ��ظ�ָ��"),
		APP_INSERT_DATA = 0x90,// true, "�˵걦���뵽��ӡ��������"),
		APP_STATUS_RESPONSE = 0x91,// "��BOX״̬�����Ӧ��ͬ�⿪ʼ����"),
		APP_SWITCH_PAPERLESS = 0X92,// "֪ͨbox�л���ֽ��ֽ"),
		APP_CHANGE_BT_NAME = 0X93, //"�޸���������"),
		APP_FIRM_DATA = 0X94,// "�̼�����"),
		APP_FIRM_DATA_SUM = 0X95,// "�̼�У������"),
		APP_QR_CODE_INFO = 0X96,// "��ά����Ϣ"),
		APP_QR_CODE_DATA = 0X97, //"��ά������"),
		APP_MATRIX_TRIGGER = 0X98, //, "ͼ��Ʊ�ݴ�����");
		APP_SIMULATE_PRINTER = 0X99,  //��λģ���ӡ��
		APP_KEY_DELAY = 0X9A    //������ʱ
	};

	BoxMessage(BoxMessageEnum _command,char _seq, Array<BYTE> _data);
	BoxMessage(BoxMessageEnum _command);
	BoxMessage(BoxMessageEnum _command, Array<BYTE> _data);
	BoxMessage();

	Array<BYTE> marshal();

	static int crc32(Array<BYTE> bytes);

	static bool isBoxCommand(BYTE command);

	static bool checkCrc32(Array<BYTE> bytes, int c);

	bool isReady();

	BoxMessageEnum command;

	static const int MESSAGE_MIN_LENGTH = 9;
	static const int PACKAGE_MAX_LENGTH =1024;
	static const BYTE FLAG_HEAD = (BYTE)0xFE;
	static const char ZERO_CHAR = (char)0;
	static const BYTE BYTE_ZERO = (BYTE)0;

	short length;
    Array<BYTE> data;
	char seq;
};

#endif
