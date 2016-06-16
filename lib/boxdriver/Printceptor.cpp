//---------------------------------------------------------------------------

#pragma hdrstop

#include "Printceptor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Printceptor::Printceptor()
{
	printReceiptFlag = true;
	interceptFlag = true;
    firmwareUpdateIng = FIRMWARE_UPDATE_FAIL;
	connection =new Connection(this);
}

void Printceptor::handleMessagesFromBox(BoxMessage* message)
{
	switch(message->command)
	{
		case message->BOX_POS_DATA:
			triggerBOX_POS_DATA(message);
			break;
		case message->BOX_RESPONSE:
            break;
        case message->BOX_HEART_BEAT:
            break;
        case message->BOX_CPU_FIRM:
            //triggerBOX_CPU_FIRM(message);
            return;
        case message->BOX_PRINTER_DATA:
            //triggerAPP_PRINTER_DATA(message);
            break;
        case message->BOX_STATUS_REPORT:
            //triggerStatusReport(message);
            break;
        case message->BOX_NOTIFY_PAPERLESS_RESPONSE:
            //triggerSwitchPaperless(message);
            break;
        case message->BOX_NOTIFY_UPDATE_STATUS:
            triggerUpdateFirmStatus(message);
            break;
        case message->BOX_NOTIFY_AP_REPORT:
            //triggerAPReport(message);
            break;
        case message->BOX_NOTIFY_QR_REQUEST:
            //triggerQRRequest(message);
            break;
	}
}

void Printceptor::startIntercept(int connStringType, char* connString)
{
	connection->open(connStringType, connString);
}

void Printceptor::endIntercept()
{
	connection->close();
}

void Printceptor::sendData(BoxMessage::BoxMessageEnum _command, Array<BYTE> _data)
{
	BoxMessage boxMessage = BoxMessage(_command, _data);
    sendMessage(&boxMessage);
}

void Printceptor::pressKeyboard(BYTE keys[], int keys_len)
{
	Array<BYTE> temp_array = Array<BYTE>(keys_len,0);
	memcpy(temp_array.GetPt(),keys,keys_len);
	sendData(BoxMessage::APP_KEYBOARD, temp_array);
}

void Printceptor::sendMessage(BoxMessage* message)
{
    connection->sendMessage(message);
}

void Printceptor::onConnectChanged(bool isConnected)
{
	if (PF_ConnChanged)
	{
		PF_ConnChanged(isConnected);
	}
}

void Printceptor::triggerBOX_POS_DATA(BoxMessage* message)
{
	if (PF_CommReceived)
	{
		PF_CommReceived(message->data.GetPt(),message->data.GetSize());
	}
}

void Printceptor::sendPrinterData(BYTE data[], int len)
{
	Array<BYTE> temp_array = Array<BYTE>(len,0);
	memcpy(temp_array.GetPt(),data,len);
	sendData(BoxMessage::APP_SIMULATE_PRINTER, temp_array);
}

void Printceptor::setKeyDelay(BYTE delay)
{
    Array<BYTE> temp_array = Array<BYTE>(1,0);
	memcpy(temp_array.GetPt(),&delay,1);
	sendData(BoxMessage::APP_KEY_DELAY, temp_array);
}

void Printceptor::savePrinterConfig(char* config)
{
	int baud = atoi(config);
	BYTE baudIndex = 0;
	switch (baud)
	{
		case 110:
			baudIndex = 0;
			break;
		case 300:
			baudIndex = 1;
			break;
		case 600:
			baudIndex = 2;
			break;
		case 1200:
			baudIndex = 3;
			break;
		case 2400:
			baudIndex = 4;
			break;
		case 4800:
			baudIndex = 5;
			break;
		case 9600:
			baudIndex = 6;
			break;
		case 14400:
			baudIndex = 7;
			break;
		case 19200:
			baudIndex = 8;
			break;
		case 38400:
			baudIndex = 9;
			break;
		case 43000:
			baudIndex = 0x0A;
			break;
		case 56000:
			baudIndex = 0x0B;
			break;
		case 57600:
			baudIndex = 0x0C;
			break;
		case 115200:
			baudIndex = 0x0D;
			break;
		case 128000:
			baudIndex = 0x0E;
			break;
		case 256000:
			baudIndex = 0x0F;
			break;
		default:                                //USB
			baudIndex = 0xFF;
			break;
	}
    Array<BYTE> temp_array = Array<BYTE>(1,0);
	memcpy(temp_array.GetPt(),&baudIndex,1);
	sendData(BoxMessage::APP_CONFIG, temp_array);
}

BYTE Printceptor::getFirmwareUpdateIng()
{
	return firmwareUpdateIng;
}

void Printceptor::updateFirmware()
{
    Array<BYTE> temp_array = Array<BYTE>();
    sendData(BoxMessage::APP_UPDATE_FIRM, temp_array);
}

void Printceptor::sendFirmware(BYTE firm_data[], int len)
{
    //将固件数据暂存
	firmData =  Array<BYTE>(len,0);
	firmDataSum = Array<BYTE>(3,0);
    BYTE temp_data_sum[3] = {0};
	BYTE xor_result = 0;
	for (int i = 0; i < len;i++){
		xor_result ^= (firm_data[i]);
	}
	memcpy(firmData.GetPt(),firm_data,len);
	temp_data_sum[0] = (BYTE)(len / 256);
	temp_data_sum[1] = (BYTE)(len % 256);
	temp_data_sum[2] = xor_result;
	memcpy(firmDataSum.GetPt(),temp_data_sum,3);
	updateFirmware();
	firmwareUpdateIng = FIRMWARE_UPDATE_WAIT;
}

void Printceptor::triggerUpdateFirmStatus(BoxMessage* message)
{
	firmwareUpdateIng = message->data[0];
	if (firmwareUpdateIng == FIRMWARE_UPDATE_START)
	{
		sendData(BoxMessage::APP_FIRM_DATA_SUM, firmDataSum);
		sendData(BoxMessage::APP_FIRM_DATA, firmData);
	}
	if ((firmwareUpdateIng == FIRMWARE_UPDATE_SUCCESS)
		|| (firmwareUpdateIng == FIRMWARE_UPDATE_FAIL))
	{
		//onFirmUpdateNotify(firmwareUpdateIng);
		if (PF_FirmUpdateStatus) {
			if (firmwareUpdateIng == FIRMWARE_UPDATE_SUCCESS) {
                PF_FirmUpdateStatus(true);
			}
			else
			{
                PF_FirmUpdateStatus(false);
            }
		}
	}
	if (firmwareUpdateIng == FIRMWARE_UPDATE_SUCCESS)
	{
		firmwareUpdateIng = FIRMWARE_UPDATE_FAIL;
    }
}

