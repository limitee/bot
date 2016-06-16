//---------------------------------------------------------------------------

#ifndef ReceiveThreadH
#define ReceiveThreadH
//---------------------------------------------------------------------------

#include <windows.h>
#include "RingBytesBuffer.h"

#include "Connection.h"
#include "BoxMessage.h"


class ReceiveThread{
private:
	static const int readInterval = 50;
	static const long read_timeout = Connection::HEART_BEAT_INTERNAL * 3;

	Connection* connection;

	static DWORD WINAPI run(LPVOID lpParamter);

	void readFromDevice();

	void readMessage();

	void handleResponseMessage();

public:
	ReceiveThread(Connection* connection);

	RingBytesBuffer* buffer;

	BoxMessage* message;
};

#endif
