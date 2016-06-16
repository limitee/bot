//---------------------------------------------------------------------------

#ifndef BoxMessageH
#define BoxMessageH
//---------------------------------------------------------------------------

#include <windows.h>
#include "Array.h"

class BoxMessage{
public:
	enum BoxMessageEnum{
		BOX_POS_DATA = 0X01, //"拦截的POS数据"
		BOX_RESPONSE = 0x02, // "Box报文确认消息"),
		BOX_HEART_BEAT = 0x03, // "与App的心跳消息一一对应，应答使用"),
		BOX_CPU_FIRM = 0x04, //"硬件信息"),
		BOX_PRINTER_DATA = 0x05,// "拦截的打印机数据"),
		BOX_STATUS_REPORT = 0x06, // "BOX状态报告，请求开始拦截"),
		BOX_NOTIFY_PAPERLESS_RESPONSE = 0X07,// "Box响应切换有纸无纸"),
		BOX_NOTIFY_UPDATE_STATUS = 0X08,//"Box固件更新状态"),
		BOX_NOTIFY_AP_REPORT = 0X09,// "Box报告收集MAC信息"),
		BOX_NOTIFY_QR_REQUEST = 0X10,// "Box向APP申请新的二维码"),

		APP_HANDSHAKE = 0x80, // "握手,通讯的开始"),
		APP_RESPONSE = 0x81, // "App报文确认消息"),
		APP_POS_DATA = 0x82, //true, "兴店宝转发POS到打印机的数据"),
		APP_KEYBOARD = 0x83, //"模拟的键盘按键"),
		APP_QUERY_INFO = 0x84,// "硬件信息查询，CPU的ID，固件信息"),
		APP_CONFIG = 0x85,// "下发配置打印机的参数"),
		APP_HEART_BEAT = 0x86, //"发起心跳"),
		APP_UPDATE_FIRM = 0x87,// "更新固件"),
		APP_RESET = 0x88,// "BOX复位"),
		APP_PRINTER_DATA = 0x89,// "下发的打印机模拟回复指令"),
		APP_INSERT_DATA = 0x90,// true, "兴店宝插入到打印机的数据"),
		APP_STATUS_RESPONSE = 0x91,// "对BOX状态报告的应答，同意开始拦截"),
		APP_SWITCH_PAPERLESS = 0X92,// "通知box切换有纸无纸"),
		APP_CHANGE_BT_NAME = 0X93, //"修改蓝牙名称"),
		APP_FIRM_DATA = 0X94,// "固件数据"),
		APP_FIRM_DATA_SUM = 0X95,// "固件校验数据"),
		APP_QR_CODE_INFO = 0X96,// "二维码信息"),
		APP_QR_CODE_DATA = 0X97, //"二维码数据"),
		APP_MATRIX_TRIGGER = 0X98, //, "图文票据触发器");
		APP_SIMULATE_PRINTER = 0X99,  //上位模拟打印机
		APP_KEY_DELAY = 0X9A    //键盘延时
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
