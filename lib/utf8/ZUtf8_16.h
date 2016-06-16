//---------------------------------------------------------------------------
#ifndef ZUtf8_16H
#define ZUtf8_16H
//---------------------------------------------------------------------------
/*
  支持UNICODE，UNICODE BE ，UTF8，ASCII之间的转换的类。
*/

enum EncodingType
{
	uni8Bit = 0, // 默认ASCII
	uni16BE = 1,
	uni16LE = 2, // Windows 默认的编码，也就是UNICODE
	uniUTF8 = 3,
	uniUTF8NOBOM = 4 // 没有UTF8标识头的UTF8文件
};

class ZUtf8_16
{
private:
	EncodingType m_unicodeMode; // 编码方式
	int isUTF8_16(const char *s, unsigned int len, unsigned *cchUnused);
	EncodingType __fastcall DetermineEncoding(unsigned char *data, size_t iLen);

public:
	__fastcall ZUtf8_16();
	__fastcall ~ZUtf8_16();
	EncodingType __fastcall GetEncodingType(void){return m_unicodeMode;};
	bool __fastcall LoadFromStream(TMemoryStream *pStream, AnsiString &DestText);
	bool __fastcall StreamSaveToFile(TMemoryStream *pStream, AnsiString FileNameA, EncodingType unicodeMode);
};

#endif

