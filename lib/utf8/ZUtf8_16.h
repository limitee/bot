//---------------------------------------------------------------------------
#ifndef ZUtf8_16H
#define ZUtf8_16H
//---------------------------------------------------------------------------
/*
  ֧��UNICODE��UNICODE BE ��UTF8��ASCII֮���ת�����ࡣ
*/

enum EncodingType
{
	uni8Bit = 0, // Ĭ��ASCII
	uni16BE = 1,
	uni16LE = 2, // Windows Ĭ�ϵı��룬Ҳ����UNICODE
	uniUTF8 = 3,
	uniUTF8NOBOM = 4 // û��UTF8��ʶͷ��UTF8�ļ�
};

class ZUtf8_16
{
private:
	EncodingType m_unicodeMode; // ���뷽ʽ
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

