//---------------------------------------------------------------------------

#ifndef FuncUtilsH
#define FuncUtilsH
//---------------------------------------------------------------------------
#include "Array.h"

class FuncUtils{
public:
	static Array<BYTE> intToBytes(int number);

	static Array<BYTE> shortToBytes(short number);

	static short bytesToShort(BYTE b0,BYTE b1);

	static int bytes2Int(Array<BYTE> bytes);
};

#endif
