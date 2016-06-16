//---------------------------------------------------------------------------

#pragma hdrstop

#include "HeartBeatMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

HeartBeatMessage* HeartBeatMessage::instance = NULL;

HeartBeatMessage::HeartBeatMessage():BoxMessage(BoxMessage::APP_HEART_BEAT)
{
	command = BoxMessage::APP_HEART_BEAT;
	data = Array<BYTE>();
    length= 0;
	seq = 0;
}

HeartBeatMessage* HeartBeatMessage::getInstance()
{
    if(NULL == instance)
    {
		instance = new HeartBeatMessage();
    }
    return instance;
}