//---------------------------------------------------------------------------

#ifndef FtdiChannelH
#define FtdiChannelH
//---------------------------------------------------------------------------

#include "IDeviceChannel.h"
#include "RingBytesBuffer.h"
#include "Array.h"

class FtdiChannel:public IDeviceChannel
{
private:
	int baud;
	HANDLE hCom;
	char connString[25];

public:
	FtdiChannel();

	void init(int connStringType,char* connString);

	void openDevice();

	bool isDeviceOpened();

	void closeDevice();

	int read(RingBytesBuffer* buffer);

	int write(Array<BYTE> data);
};

#endif
