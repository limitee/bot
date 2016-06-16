//---------------------------------------------------------------------------

#ifndef ResponseMessageH
#define ResponseMessageH
//---------------------------------------------------------------------------

#include "BoxMessage.h"

class ResponseMessage:public BoxMessage
{
public:
	ResponseMessage(BoxMessage* message);
};

#endif
