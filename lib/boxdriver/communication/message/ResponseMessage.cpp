//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>
#include"ResponseMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

ResponseMessage::ResponseMessage(BoxMessage* message):BoxMessage(BoxMessage::APP_RESPONSE)
{
    seq= message->seq;
    data = Array<BYTE>();
    length= 0;
}