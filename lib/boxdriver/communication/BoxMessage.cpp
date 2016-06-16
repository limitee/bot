//---------------------------------------------------------------------------

#pragma hdrstop

#include "BoxMessage.h"
#include "Crc32c.h"
#include "FuncUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

BoxMessage::BoxMessage(BoxMessageEnum _command,char _seq, Array<BYTE> _data)
{
	command = _command;
    seq = _seq;
    data = _data;
	if (data.GetPt() == NULL) {
        length = 0;
    } else {
		length = data.GetSize();
    }
}

BoxMessage::BoxMessage(BoxMessageEnum _command)
{
	Array<BYTE> nil = Array<BYTE>();
	command = _command;
    seq = ZERO_CHAR;
    data = nil;
	if (data.GetPt() == NULL) {
        length = 0;
    } else {
		length = data.GetSize();
    }
}

BoxMessage::BoxMessage(BoxMessageEnum _command, Array<BYTE> _data)
{
	command = _command;
    seq = ZERO_CHAR;
    data = _data;
	if (data.GetPt() == NULL) {
        length = 0;
    } else {
		length = data.GetSize();
    }
}

BoxMessage::BoxMessage()
{
	command = (BoxMessageEnum)0;
}

Array<BYTE> BoxMessage::marshal()
{
	if (data.GetPt() != NULL) {
		length = data.GetSize();
    } else {
        length=0;
    }
    int bytesLen = length + MESSAGE_MIN_LENGTH;
    BYTE* bytes = new BYTE[bytesLen];
    bytes[0] = FLAG_HEAD;
    bytes[1] = command;
    bytes[2] = (BYTE) seq;

	Array<BYTE> crc32Bytes = FuncUtils::intToBytes(crc32(data));

    if (length >0) {
		Array<BYTE> lenBytes = FuncUtils::shortToBytes(length);
		bytes[3] = lenBytes[0];
        bytes[4] = lenBytes[1];
		memcpy(&bytes[5],data.GetPt(), length);
    }else {
        bytes[3] = BYTE_ZERO;
        bytes[4] = BYTE_ZERO;
    }
    bytes[bytesLen - 4] = crc32Bytes[0];
    bytes[bytesLen - 3] = crc32Bytes[1];
    bytes[bytesLen - 2] = crc32Bytes[2];
    bytes[bytesLen - 1] = crc32Bytes[3];
	Array<BYTE> return_array = Array<BYTE>(bytesLen,0);
	memcpy(return_array.GetPt(),bytes,bytesLen);
	delete []bytes;
    return return_array;
}

int BoxMessage::crc32(Array<BYTE> bytes)
{
	if (bytes.GetPt() == NULL || bytes.GetSize() == 0)
	{
        return Crc32c::NULL_CRC;
    } else {
		return Crc32c::crc32(bytes.GetPt(), 0, bytes.GetSize());
    }
}

bool BoxMessage::isBoxCommand(BYTE command)
{
    return command >= BOX_POS_DATA && command <= BOX_NOTIFY_QR_REQUEST;
}

bool BoxMessage::checkCrc32(Array<BYTE> bytes, int c)
{
        return crc32(bytes) == c;
}

bool BoxMessage::isReady()
{
	return length==0 || (data.GetPt()!=NULL && data.GetSize()==length);
}
