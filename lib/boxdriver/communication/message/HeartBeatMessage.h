//---------------------------------------------------------------------------

#ifndef HeartBeatMessageH
#define HeartBeatMessageH

//---------------------------------------------------------------------------
#include "BoxMessage.h"

class HeartBeatMessage:public BoxMessage
{
public:
	HeartBeatMessage();

	static HeartBeatMessage* instance;

	static HeartBeatMessage* getInstance();
};

#endif
