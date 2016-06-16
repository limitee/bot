//---------------------------------------------------------------------------

#ifndef SendThreadH
#define SendThreadH
//---------------------------------------------------------------------------

#include "Connection.h"
#include "Printceptor.h"
#include "HeartBeatMessage.h"
#include "BoxMessage.h"
#include "Array.h"
#include "RingBytesBuffer.h"

class SendThread{
private:
	Printceptor* printceptor;

	Connection* connection;

	static DWORD WINAPI run(LPVOID lpParamter);

	void ensureDeviceOpen();

	void write(BoxMessage* message);

	void writeInternal(Array<BYTE> data);

	void handleMessageToBox();

	void handleOtherToBox();

	int heartCnt;

	RingBytesBuffer* bigDataBuffer;

public:
	SendThread(Printceptor* printceptor);
};

#endif
