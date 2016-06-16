//---------------------------------------------------------------------------

#ifndef PrintceptorH
#define PrintceptorH
//---------------------------------------------------------------------------

#include "Connection.h"
#include "BoxMessage.h"
#include "Array.h"


class Printceptor {

	private:
		bool printReceiptFlag;

		bool interceptFlag;

		void sendData(BoxMessage::BoxMessageEnum _command, Array<BYTE> _data);

		void sendMessage(BoxMessage* message);

		Array<BYTE> firmData;

		Array<BYTE> firmDataSum;

		BYTE firmwareUpdateIng;

		void triggerUpdateFirmStatus(BoxMessage* message);

	public:
		Printceptor();

		void startIntercept(int connStringType, char* connString);

		void endIntercept();

		void pressKeyboard(BYTE keys[], int keys_len);

		void sendPrinterData(BYTE data[], int len);

		void setKeyDelay(BYTE delay);

        void savePrinterConfig(char* config);

		void (__closure *PF_CommReceived)(BYTE* data, int len);

		void (__closure *PF_ConnChanged)(bool isConnected);

		void (__closure *PF_FirmUpdateStatus)(bool isUpdatedOk);

		//
		Connection* connection;

		void onConnectChanged(bool isConnected);

		void handleMessagesFromBox(BoxMessage* message);

		void triggerBOX_POS_DATA(BoxMessage* message);

		void sendFirmware(BYTE firm_data[], int len);

		BYTE getFirmwareUpdateIng();

		void updateFirmware();

		static const BYTE FIRMWARE_UPDATE_FAIL = 0;

		static const BYTE FIRMWARE_UPDATE_WAIT = 1;

		static const BYTE FIRMWARE_UPDATE_START = 2;

    	static const BYTE FIRMWARE_UPDATE_SUCCESS = 3;
};


#endif
