#ifndef __DES_H__
#define __DES_H__

typedef unsigned char BYTE;

typedef struct
{
	BYTE L[32];
	BYTE R[32];
}LRStruct;

typedef struct
{
	BYTE C[28];
	BYTE D[28];
}CDStruct;


typedef struct
{
	BYTE b0 :	1;
	BYTE b1 :	1;
	BYTE b2 :	1;
	BYTE b3 :	1;
	BYTE b4 :	1;
	BYTE b5 :	1;
	BYTE b6 :	1;
	BYTE b7 :	1;
}BYTEStruct;

void DesAlgo(BYTE *src, BYTE *key, BYTE *dst, BYTE bEncrypt);
void Decrypt(BYTE * src, BYTE * key, BYTE * dst);
void Encrypt(BYTE* src, BYTE* key, BYTE* dst);

void BitToByte(BYTE * src, BYTE * dst, int n);
void ByteToBit(BYTE * src, BYTE * dst, int n);
void Shift(CDStruct * pCD, int iCircle, BYTE bEncrypt);
void RShift(BYTE *buf28, int nShift);
void LShift(BYTE *buf28, int nShift);
void fFunction(BYTE* R, BYTE* K, BYTE* result);
void EOR(BYTE * src, BYTE* dst, int n);
void S_Change(BYTE* src, BYTE* result);
void SelectExchangeFromTable(int nTable, BYTE * src, BYTE * dst);
void DES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst);
void DeDES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst);
void TDES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst);
void TDeDES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst);
void asctobcd(char *, char *, int);
void bcdtoasc(char *, char *, int);
void DES_GO(char *pbyKey, char *pbySrc,char *pbyDst);
void DeDES_GO(char *pbyKey, char *pbySrc,char *pbyDst);


#endif