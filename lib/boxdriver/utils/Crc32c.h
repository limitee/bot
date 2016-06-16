//---------------------------------------------------------------------------

#ifndef Crc32cH
#define Crc32cH
//---------------------------------------------------------------------------
#include <windows.h>


class Crc32c{
public:
	static const int NULL_CRC = ~0;

	static const int BYTE_MASK = 0xFF;

	static int crc32c(int crc, int b);

	static int crc32(BYTE* buffer, int offset, int length);
};

#endif
