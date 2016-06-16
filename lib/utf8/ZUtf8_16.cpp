//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "ZUtf8_16.h"

#pragma package(smart_init)
__fastcall ZUtf8_16::ZUtf8_16()
{
    m_unicodeMode = uni8Bit;
}
//---------------------------------------------------------------------------
__fastcall ZUtf8_16::~ZUtf8_16()
{
}
//---------------------------------------------------------------------------
int ZUtf8_16::isUTF8_16(const char *s, unsigned int len, unsigned *cchUnused)
{
    int rv = 1;
    int ASCII7only = 1;
    const unsigned char *sx = (unsigned char *)s, *endx = sx+len;
    while(sx < endx)
    {
        if(!*sx)
        {
           // For detection, we'll say that NUL means not UTF8
            ASCII7only = 0;
            rv = 0;
            break;
        }
        else if (*sx < 0x80)
        {
            // 0nnnnnnn If the byte's first hex code begins with 0-7, it is an ASCII character.
            sx++;
        }
        else if (*sx < (0x80 + 0x40))
        {
           // 10nnnnnn 8 through B cannot be first hex codes
            ASCII7only = 0;
            rv = 0;
            break;
        }
        else if(*sx < (0x80 + 0x40 + 0x20))
        {
            // 110xxxvv 10nnnnnn  If it begins with C or D, it is an 11 bit character
            ASCII7only = 0;
            if(sx >= endx-1) break;
            if(!(*sx & 0x1F) || (sx[1]&(0x80+0x40)) != 0x80) { rv = 0; break; }
            sx += 2;
        }
        else if (*sx < (0x80 + 0x40 + 0x20 + 0x10))
        {
            // 1110qqqq 10xxxxvv 10nnnnnn If it begins with E, it is 16 bit
            ASCII7only = 0;
            if(sx >= endx-2) break;
            if(!(*sx & 0xF) || (sx[1]&(0x80+0x40)) != 0x80 || (sx[2]&(0x80+0x40)) != 0x80)
            { rv = 0; break; }
            sx += 3;
        }
        else
        {
            /* more than 16 bits are not allowed here */
            ASCII7only = 0;
            rv = 0;
            break;
        }
    }
    if(cchUnused) *cchUnused = endx-sx;
    return(ASCII7only?0:rv);
}
//---------------------------------------------------------------------------
EncodingType __fastcall ZUtf8_16::DetermineEncoding(unsigned char *data, size_t iLen)
{
    // TODO:�жϵ�ǰ�ļ��ı������͡�
    m_unicodeMode = uni8Bit; // Ĭ��ASCII
    if(data[0] == 0xFE && data[1] == 0xFF) // Big endian == UNICODE-BIG   UTF16
    {
        m_unicodeMode = uni16BE;
    }
    else if(data[0] == 0xFF && data[1] == 0xFE) // Little endian == UNICODE  UTF16
    {
        m_unicodeMode = uni16LE; // Unicode
    }
    else if(data[0] == 0xEF && data[1] == 0xBB && data[2] == 0xBF) // UTF8
    {
        m_unicodeMode = uniUTF8;
    }
    else if(isUTF8_16(data, iLen, NULL) == 1)
    {
        m_unicodeMode = uniUTF8NOBOM;
    }
    return  m_unicodeMode;
}
//---------------------------------------------------------------------------
bool __fastcall ZUtf8_16::LoadFromStream(TMemoryStream *pSourceStream, AnsiString &DestText)
{
    // TODO:�����ж�ȡ����
    // ���ж��ַ�����
    pSourceStream->Position = 0;
    if(pSourceStream->Size == 0) return true;
    m_unicodeMode = DetermineEncoding((char*)pSourceStream->Memory, pSourceStream->Size);

    pSourceStream->Position = 0;

    // �ٸ����Ӧ�ı�������Ӧ���¡�
    switch(m_unicodeMode)
    {
        case uni8Bit:
        {
            // ʲô���������Ա�֤��һЩ����ļ�ʱ�ٶȿ�һЩ��
            // ���Ե�������Ҫ�Լ��ڵ���֮���ж��ַ����룬
            // �����uni8Bit������Ҫ�Լ�����
//            int iLength = pSourceStream->Size ;
//            char  *szUnicode = new char[iLength+1];
//            memset(szUnicode, 0x00, iLength+1);
//            pSourceStream->Read(szUnicode, iLength);
//            DestText = AnsiString(szUnicode);
//            delete []szUnicode;
//            szUnicode = NULL;
            break;
        }
        case uni16BE: 
        {
           // UC Big endian
            pSourceStream->Position = 2;
            int iLength = pSourceStream->Size-2 ;
            char temp;
            char *szUnicode = new char[iLength+2];
            memset(szUnicode, 0x00, iLength+2);
            pSourceStream->Read(szUnicode, iLength);
           // ֻҪ��ÿ�����ֽڵ�λ�ý���һ�£�����UNICODE LE�ˡ�So...
            for(int i = 0; i<iLength; i += 2)
            {
                temp = szUnicode[i];
                szUnicode[i] = szUnicode[i+1];
                szUnicode[i+1] = temp;
                Application->ProcessMessages();
            }

            DestText = WideCharLenToString ((wchar_t*)(szUnicode), iLength/2);

            delete []szUnicode;
            szUnicode = NULL;

            break;
        }
        case uni16LE:
        {
           // UNICODE  Little endian
            pSourceStream->Position = 2;
            int iLength = pSourceStream->Size-2 ;

            wchar_t  *szUnicode = new wchar_t[iLength+2];
            memset(szUnicode, 0x00, iLength+2);
            pSourceStream->Read(szUnicode, iLength);
            WideString WideStr = WideString(szUnicode);
            DestText = WideStr;

            delete []szUnicode;
            szUnicode = NULL;

            break;
        }
        case uniUTF8:
        {
           // UTF8
            pSourceStream->Position = 3;
            int iLength = pSourceStream->Size-3 ;
            char *szUTF8 = new char[iLength+3];
            memset(szUTF8, 0x00, iLength+3);
            pSourceStream->Read(szUTF8, iLength);

            AnsiString Utf8Str = Utf8ToAnsi(szUTF8);
// ����ת�� C++Builder�о� - http://www.ccrun.com/article.asp?i=1023&d=cbj0f7
            if(Utf8Str == "")
                DestText = AnsiString((char*)pSourceStream->Memory);
            else
                DestText = Utf8Str;
            delete []szUTF8;
            szUTF8 = NULL;
            break;
        }
        case uniUTF8NOBOM:
        {
           // UTF8 û��ͷ��ʶ�������
            int iLength = pSourceStream->Size;
            char *szUTF8 = new char[iLength+3];
            memset(szUTF8, 0x00, iLength+3);
            pSourceStream->Read(szUTF8, iLength);

            AnsiString Utf8Str = Utf8ToAnsi(szUTF8);
            if(Utf8Str == "")
                DestText = AnsiString((char*)pSourceStream->Memory);
            else
                DestText = Utf8Str;
            delete []szUTF8;
            szUTF8 = NULL;
            break;
        }

    }
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall ZUtf8_16::StreamSaveToFile(TMemoryStream *pStream, 
        AnsiString FileNameA, EncodingType unicodeMode)
{
    // TODO:�������ݰ�ָ���ĸ�ʽ���浽�ļ��С�
    try
    {
        pStream->Position = 0;
        switch(unicodeMode)
        {
            case uni8Bit:
            {
               // ʲô��������ֱ�ӱ��档
                pStream->SaveToFile(FileNameA);
                break;
            }
            case uni16BE:
            {
                // UC Big endian
                int iLength = pStream->Size ;
                char temp;
                char *pSource = new char[iLength+2];
                memset(pSource, 0x00, iLength+2);
                pStream->Read(pSource, iLength);

                // �ȿ���ת�ɵĿ��ֽ�������nLen
                int nLen = MultiByteToWideChar( CP_ACP, 0, pSource, iLength, NULL, NULL );
                LPWSTR lpwsz = new WCHAR[nLen];
                MultiByteToWideChar( CP_ACP, 0, pSource, -1, lpwsz, nLen );

                int iNewLen = lstrlenW(lpwsz) * sizeof(WCHAR);
                char *pDest = new char[iNewLen];
                memcpy(pDest, lpwsz, iNewLen);
                
                // ֻҪ��ÿ�����ֽڵ�λ�ý���һ�£�����UNICODE Big�ˡ�So...
                for(int i = 0; i<iNewLen; i += 2)
                {
                    temp = pDest[i];
                    pDest[i] = pDest[i+1];
                    pDest[i+1] = temp;
                    Application->ProcessMessages();
                }

                FILE *f = fopen(FileNameA.c_str(), "wb");
                // дUnicode Bigͷ
                fputc(0xFE, f);
                fputc(0xFF, f);
                fwrite(pDest, 1, iNewLen, f);
                fclose(f);

                delete []pDest;
                pDest = NULL;
                delete []lpwsz;
                lpwsz = NULL;
                delete []pSource;
                pSource = NULL;

                break;
            }
            case uni16LE:
            {
                // UNICODE  Little endian
                int iLength = pStream->Size ;
                char *pSource = new char[iLength+2];
                memset(pSource, 0x00, iLength+2);
                pStream->Read(pSource, iLength);

                // �ȿ���ת�ɵĿ��ֽ�������nLen
                int nLen = MultiByteToWideChar( CP_ACP, 0, pSource, iLength, NULL, NULL );
                LPWSTR lpwsz = new WCHAR[nLen];
                MultiByteToWideChar( CP_ACP, 0, pSource, -1, lpwsz, nLen );

                FILE *f = fopen(FileNameA.c_str(), "wb");
                // дUnicodeͷ
                fputc(0xFF, f);
                fputc(0xFE, f);
                // һ�����ֽ�ռ�����ֽ�
                fwrite(lpwsz, 1, lstrlenW(lpwsz) * sizeof(WCHAR), f);
                fclose(f);

                delete []lpwsz;
                lpwsz = NULL;
                delete []pSource;
                pSource = NULL;
                break;
            }
            case uniUTF8:
            {
                // UTF8
                int iLen = pStream->Size;
                char *pSource = new char[iLen+3];
                memset(pSource, 0x00, iLen+3);
                pStream->Read(pSource, iLen);

                AnsiString Utf8Str = AnsiToUtf8(pSource);

                delete []pSource;
                pSource = NULL;
                FILE *f = fopen(FileNameA.c_str(), "wb");
                // дUTF8ͷ
                fputc(0xEF, f);
                fputc(0xBB, f);
                fputc(0xBF, f);
                // һ�����ֽ�ռ�����ֽ�
                fwrite(Utf8Str.c_str(), 1, Utf8Str.Length(), f);
                fclose(f);
                break;
            }
            case uniUTF8NOBOM:
            {
                // UTF8û�б�ʶͷ�������
                int iLen = pStream->Size;
                char *pSource = new char[iLen+3];
                memset(pSource, 0x00, iLen+3);
                pStream->Read(pSource, iLen);

                AnsiString Utf8Str = AnsiToUtf8(pSource);

                delete []pSource;
                pSource = NULL;
                FILE *f = fopen(FileNameA.c_str(), "wb");
                // һ�����ֽ�ռ�����ֽ�
                fwrite(Utf8Str.c_str(), 1, Utf8Str.Length(), f);
                fclose(f);
                break;
            }
        } // end of switch
    }
    catch(...)
    {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
// ���þ�����
#include "ZUtf8_16.h"
bool __fastcall LoadFile(AnsiString strFileName, TStrings *pList)
{
    EncodingType unicodeMode;
    // TODO:װ���ļ���
    // ���װ��ɹ����򷵻�true
    AnsiString ErrMsg;
    bool bReturn = true;
    ErrMsg.sprintf("װ�� %s �ĵ�ʱ����\n\n���ĵ�������"
                   "���߱����������Զ�ռ��ʽ�򿪣�", strFileName);

    if(!FileExists(strFileName))
    {
        MessageBox(0,  ErrMsg.c_str(), "����", MB_OK|MB_ICONERROR);
        return false;
    }
    AnsiString ReturnTxt;
    ZUtf8_16 zutf8_16;

    TMemoryStream *ReadStream = new TMemoryStream();
    ReadStream->LoadFromFile(strFileName);
    bReturn = zutf8_16.LoadFromStream(ReadStream, ReturnTxt);
    if(bReturn)
    {
        unicodeMode = zutf8_16.GetEncodingType();
        if(unicodeMode==uni8Bit)
           pList->LoadFromStream(ReadStream);
        else
            pList->Text = ReturnTxt;
    }
    else
    {
        MessageBox(0,  ErrMsg.c_str(), "����", MB_OK|MB_ICONERROR);
    }
    delete ReadStream;
    ReadStream = NULL;

    return bReturn;
}