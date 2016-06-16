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
    // TODO:判断当前文件的编码类型。
    m_unicodeMode = uni8Bit; // 默认ASCII
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
    // TODO:从流中读取数据
    // 先判断字符编码
    pSourceStream->Position = 0;
    if(pSourceStream->Size == 0) return true;
    m_unicodeMode = DetermineEncoding((char*)pSourceStream->Memory, pSourceStream->Size);

    pSourceStream->Position = 0;

    // 再根椐相应的编码做相应的事。
    switch(m_unicodeMode)
    {
        case uni8Bit:
        {
            // 什么都不做。以保证打开一些大的文件时速度快一些。
            // 所以调用者需要自己在调的之后判断字符编码，
            // 如果是uni8Bit，则需要自己处理。
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
           // 只要把每两个字节的位置交换一下，就是UNICODE LE了。So...
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
// 本文转自 C++Builder研究 - http://www.ccrun.com/article.asp?i=1023&d=cbj0f7
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
           // UTF8 没有头标识的情况。
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
    // TODO:把流内容按指定的格式保存到文件中。
    try
    {
        pStream->Position = 0;
        switch(unicodeMode)
        {
            case uni8Bit:
            {
               // 什么都不做。直接保存。
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

                // 先看看转成的宽字节数返到nLen
                int nLen = MultiByteToWideChar( CP_ACP, 0, pSource, iLength, NULL, NULL );
                LPWSTR lpwsz = new WCHAR[nLen];
                MultiByteToWideChar( CP_ACP, 0, pSource, -1, lpwsz, nLen );

                int iNewLen = lstrlenW(lpwsz) * sizeof(WCHAR);
                char *pDest = new char[iNewLen];
                memcpy(pDest, lpwsz, iNewLen);
                
                // 只要把每两个字节的位置交换一下，就是UNICODE Big了。So...
                for(int i = 0; i<iNewLen; i += 2)
                {
                    temp = pDest[i];
                    pDest[i] = pDest[i+1];
                    pDest[i+1] = temp;
                    Application->ProcessMessages();
                }

                FILE *f = fopen(FileNameA.c_str(), "wb");
                // 写Unicode Big头
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

                // 先看看转成的宽字节数返到nLen
                int nLen = MultiByteToWideChar( CP_ACP, 0, pSource, iLength, NULL, NULL );
                LPWSTR lpwsz = new WCHAR[nLen];
                MultiByteToWideChar( CP_ACP, 0, pSource, -1, lpwsz, nLen );

                FILE *f = fopen(FileNameA.c_str(), "wb");
                // 写Unicode头
                fputc(0xFF, f);
                fputc(0xFE, f);
                // 一个宽字节占两个字节
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
                // 写UTF8头
                fputc(0xEF, f);
                fputc(0xBB, f);
                fputc(0xBF, f);
                // 一个宽字节占两个字节
                fwrite(Utf8Str.c_str(), 1, Utf8Str.Length(), f);
                fclose(f);
                break;
            }
            case uniUTF8NOBOM:
            {
                // UTF8没有标识头的情况。
                int iLen = pStream->Size;
                char *pSource = new char[iLen+3];
                memset(pSource, 0x00, iLen+3);
                pStream->Read(pSource, iLen);

                AnsiString Utf8Str = AnsiToUtf8(pSource);

                delete []pSource;
                pSource = NULL;
                FILE *f = fopen(FileNameA.c_str(), "wb");
                // 一个宽字节占两个字节
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
// 试用举例：
#include "ZUtf8_16.h"
bool __fastcall LoadFile(AnsiString strFileName, TStrings *pList)
{
    EncodingType unicodeMode;
    // TODO:装入文件。
    // 如果装入成功，则返回true
    AnsiString ErrMsg;
    bool bReturn = true;
    ErrMsg.sprintf("装入 %s 文档时出错，\n\n该文档不存在"
                   "或者被其它程序以独占方式打开！", strFileName);

    if(!FileExists(strFileName))
    {
        MessageBox(0,  ErrMsg.c_str(), "错误", MB_OK|MB_ICONERROR);
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
        MessageBox(0,  ErrMsg.c_str(), "错误", MB_OK|MB_ICONERROR);
    }
    delete ReadStream;
    ReadStream = NULL;

    return bReturn;
}