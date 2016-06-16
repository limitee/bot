//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>
#include "FuncUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


Array<BYTE> FuncUtils::intToBytes(int number)
{
    int temp = number;
    BYTE* b = new BYTE[4];
    b[0] = (BYTE) (temp >> 24);
    b[1] = (BYTE) (temp >> 16);
    b[2] = (BYTE) (temp >> 8);
    b[3] = (BYTE) temp;
	Array<BYTE> return_array = Array<BYTE>(4,0);
	memcpy(return_array.GetPt(),b,4);
	delete []b;
    return return_array;
}

Array<BYTE> FuncUtils::shortToBytes(short number)
{
    int temp = number;
    BYTE* b = new BYTE[2];
    b[0] = (BYTE) (temp >> 8);
    b[1] = (BYTE) temp;
	Array<BYTE> return_array = Array<BYTE>(2,0);
	memcpy(return_array.GetPt(),b,2);
	delete []b;
    return return_array;
}

short FuncUtils::bytesToShort(BYTE b0,BYTE b1)
{
	short h = (short) ((b0 < 0 ? b0 + 256 : b0) * 256);
    short l = (short) (b1 < 0 ? b1 + 256 : b1);
    return (short) (h + l);
}

int FuncUtils::bytes2Int(Array<BYTE> bytes)
{
	return bytes[3] & 0xFF |
            (bytes[2] & 0xFF) << 8 |
            (bytes[1] & 0xFF) << 16 |
            (bytes[0] & 0xFF) << 24;
}