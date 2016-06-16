// des.cpp : Defines the entry point for the console application.
//
#include "stdio.h"
#include "memory.h"
#include "des.h"

#define IP_TABLE	0
#define IP_1_TABLE	1
#define E_TABLE		2
#define P_TABLE		3
#define PC1_TABLE	4
#define PC2_TABLE	5

////////////////////////////////////////////////////////
// g_nOut: number of output bits from each table
int g_nOut[6] = {64,64,48,32,56,48};

////////////////////////////////////////////////////////
// TABLE_ip: INITIAL PERMUTATION
int TABLE_ip[64] = {  
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7
		} ;
////////////////////////////////////////////////////////
// TABLE_ip_1: INVERSE INITIAL PERMUTATION
int TABLE_ip_1[64] = {
		40,8,48,16,56,24,64,32,
		39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41,9,49,17,57,25
		} ;
////////////////////////////////////////////////////////
// TABLE_e: Expansion Function
int TABLE_ePro[48] = {   
		32,	5,	1,	2,	3,	4,
		4,	9,	5,	6,	7,	8,
		8,	13,	9,	10,	11,	12,
		12,	17,	13,	14,	15,	16,
		16,	21,	17,	18,	19,	20,
		20,	25,	21,	22,	23,	24,
		24,	29,	25,	26,	27,	28,
		28,	1,	29,	30,	31,	32
		} ;
////////////////////////////////////////////////////////
// p: Permutation Function P
int TABLE_p[32] = {   
		16,7,20,21,
		29,12,28,17,
		1,15,23,26,
		5,18,31,10,
		2,8,24,14,
		32,27,3,9,
		19,13,30,6,
		22,11,4,25
		} ;
////////////////////////////////////////////////////////
// pc_1: Permuted Choice1
int TABLE_pc_1[56] = {
		57,49,41,33,25,17,9,
		1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,
		19,11,3,60,52,44,36,
		63,55,47,39,31,23,15,
		7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,
		21,13,5,28,20,12,4} ;
////////////////////////////////////////////////////////
// pc_2: Permuted Choice2
int TABLE_pc_2Pro[48] = {
		14,	5,	17,	11,	24,	1,	
		3,	10,	28,	15,	6,	21,	
		23,	8,	19,	12,	4,	26,	
		16,	2,	7,	27,	20,	13,	
		41,	55,	52,	31,	37,	47,	
		30,	48,	40,	51,	45,	33,	
		44,	53,	49,	39,	56,	34,	
		46,	32,	42,	50,	36,	29
} ;
////////////////////////////////////////////////////////
// s: Selection Function (s1...s8)
BYTE TABLE_s[8][64] = 
{
	// S1
	{
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
	} ,
	// S2
	{	
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
	},
	// S3
	{	
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
	},
	// S4
	{
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
	},
	// S5
	{	
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
	},
	// S6
	{
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
	},
	// S7
	{
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
	},
	// S8
	{
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
	}
};
////////////////////////////////////////////////////////
// TABLE_shift: Left SHifts of C and D blocks
int TABLE_shift[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1} ;


//void DES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst);
//void DeDES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst);
void TDES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst)
{
	unsigned char key1[8],src[8],dst[8],key2[8];

	memcpy(key1,pbyKey,8);
	memcpy(key2,pbyKey+8,8);
	memset(src,0x00,sizeof(src));
	memset(dst,0x00,sizeof(dst));
    
	DES(key1,pbySrc,dst);
	DeDES(key2,dst,src);
	memset(dst,0x00,sizeof(dst));
	DES(key1,src,dst);
	memcpy(pbyDst,dst,8);
}

void TDeDES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst)
{
	unsigned char key1[8],src[8],dst[8],key2[8];
	
	memcpy(key1,pbyKey,8);
	memcpy(key2,pbyKey+8,8);
	memset(src,0x00,sizeof(src));
	memset(dst,0x00,sizeof(dst));
    
	DeDES(key1,pbySrc,dst);
	DES(key2,dst,src);
	memset(dst,0x00,sizeof(dst));
	DeDES(key1,src,dst);
	memcpy(pbyDst,dst,8);
}
void DES_GO(char *pbyKey, char *pbySrc,char *pbyDst)
{
	unsigned char key[16],src[8],dst[8];
	
	memset(key,0x00,16);
	memset(src,0x00,8);
	memset(dst,0x00,8);

    asctobcd((char*)key,pbyKey,32);
	asctobcd((char*)src,pbySrc,16);
	TDES(key,src,dst);
	for(int i = 0;i<8;i++)
	{
		sprintf(pbyDst,"%02X",dst[i]);
		pbyDst += 2;
	}
}

void DeDES_GO(char *pbyKey, char *pbySrc,char *pbyDst)
{
	unsigned char key[16],src[8],dst[8];
	
	memset(key,0x00,16);
	memset(src,0x00,8);
	memset(dst,0x00,8);
	
    asctobcd((char*)key,pbyKey,32);
	asctobcd((char*)src,pbySrc,16);
	TDeDES(key,src,dst);
	for(int i = 0;i<8;i++)
	{
		sprintf(pbyDst,"%02X",dst[i]);
		pbyDst += 2;
	}
}

void DES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst)
{
	DesAlgo(pbySrc, pbyKey, pbyDst, 1);
}

void DeDES(unsigned char * pbyKey, unsigned char * pbySrc, unsigned char * pbyDst)
{
	DesAlgo(pbySrc, pbyKey, pbyDst, 0);
}



void DesAlgo(BYTE *src, BYTE *key, BYTE *dst, BYTE bEncrypt)
{
	BYTE input[64];			// store input data
	BYTE output[64];		// store output data
	BYTE KEY[64];			// store key
	
	LRStruct LR;			// store L[i],R[i] --- temp data after every circle
	CDStruct CD;			// store C[i],D[i] --- temp Result of Shift()

	BitToByte(src, input, 8); // src (64 bits) ==>input (64 Bytes)
	SelectExchangeFromTable(IP_TABLE,input,(BYTE*)&LR);  // INPUT ==> IP ==> L0,R0

	BitToByte(key, KEY, 8); // key (64 bits) ==>KEY (64 Bytes)
	SelectExchangeFromTable(PC1_TABLE,KEY,(BYTE*)&CD);  // KEY ==> PC_1 ==> C0,D0

	for (int i=0; i<16; i++)
	{
		BYTE K[48];		// store subkey --- K[n], n=1,2,...16
		BYTE fResult[32];	// store result of fFunction(),
							// then store result of L[i].EOR.f[i].
		
		// get K(i+1)
		Shift(&CD, i, bEncrypt);	// C[i],D[i] ==> shifting ==> C[i+1],D[i+1]
{
	BYTE temp[7];
	ByteToBit((BYTE*)&CD,temp,7);
}
		SelectExchangeFromTable(PC2_TABLE,(BYTE*)&CD, K);  //  C[i+1],D[i+1] ==> PC_2 ==> K[i+1]
{
	BYTE temp[64];
	for(int i=0; i<8; i++)
	{
		temp[i*8+0]=0;
		temp[i*8+1]=0;
		for (int j=0; j<6; j++)
		{
			temp[i*8+(j+2)]=K[i*6+j];
		}
	}
	BYTE temp2[8];
	ByteToBit(temp,temp2,8);
}

		// fResult[i] <== f( R[i], K[i+1] )
		fFunction(LR.R, K, fResult);

		// fResult[i] <== L[i] .EOR. f[i]
		EOR(LR.L, fResult, 32);

		// L(i+1) <== R[i]
		memcpy(LR.L, LR.R, sizeof(BYTE)*32);

		// R(i+1) <== fResult[i]
		memcpy(LR.R, fResult, sizeof(BYTE)*32);
	}
	// LR <== RL
	BYTE temp[32];
	memcpy(temp, LR.L,sizeof(BYTE)*32);
	memcpy(LR.L, LR.R,sizeof(BYTE)*32);
	memcpy(LR.R, temp,sizeof(BYTE)*32);

	SelectExchangeFromTable(IP_1_TABLE, (BYTE*)&LR, output);  // L16R16 ==> IP_1 ==> output
	ByteToBit(output, dst, 8);// dst (64 bits) <==  output (64 Bytes)
}

void BitToByte(BYTE *src, BYTE *dst, int n)
{
	for (int i=0; i<n; i++)
	{
		BYTEStruct &BS = (BYTEStruct& )src[i];

		dst[i*8+7] = BS.b0;
		dst[i*8+6] = BS.b1;
		dst[i*8+5] = BS.b2;
		dst[i*8+4] = BS.b3;
		dst[i*8+3] = BS.b4;
		dst[i*8+2] = BS.b5;
		dst[i*8+1] = BS.b6;
		dst[i*8+0] = BS.b7;
	}
}

void ByteToBit(BYTE *src, BYTE *dst, int n)
{
	for (int i=0; i<n; i++)
	{
		BYTEStruct &BS = (BYTEStruct& )dst[i];

		BS.b0 = src[i*8+7];
		BS.b1 = src[i*8+6];
		BS.b2 = src[i*8+5];
		BS.b3 = src[i*8+4];
		BS.b4 = src[i*8+3];
		BS.b5 = src[i*8+2];
		BS.b6 = src[i*8+1];
		BS.b7 = src[i*8+0];
	}
}

// 
void SelectExchangeFromTable(int nTable, BYTE *src, BYTE *dst)
{
	static int * table[6] = {TABLE_ip, TABLE_ip_1, TABLE_ePro, TABLE_p, TABLE_pc_1, TABLE_pc_2Pro};

	int nOut;
	int *pTable;
	
	nOut = g_nOut[nTable];
	pTable = table[nTable];
	
	for (int i=0; i< nOut; i++)
	{
		dst[i] = src[pTable[i]-1];
	}

}

void Shift(CDStruct * pCD, int iCircle, BYTE bEncrypt)
{
	if ( 0 == bEncrypt)
	{
		// When decprypting, the shift direction is opposite to 
		// encrypting , but the shift value is the same as 
		// encprypting except the first time.
		// The first time Decprypting needn't shift.
		if ( iCircle != 0)
		{
			RShift(pCD->C, TABLE_shift[iCircle]);
			RShift(pCD->D, TABLE_shift[iCircle]);
		}
	}
	else
	{
		LShift(pCD->C, TABLE_shift[iCircle]);
		LShift(pCD->D, TABLE_shift[iCircle]);
	}
}

// 28 bytes Right shift nShift time(s)
void RShift(BYTE *buf28, int nShift)
{
	int i;
	BYTE temp[2];

	for (i=0; i<nShift; i++)
	{
		temp[nShift-1-i] = buf28[28-1-i];
	}

	for (i=28-1; i>=nShift; i--)
	{
		buf28[i] = buf28[i-nShift];
	}

	for (i=0; i<nShift; i++)
	{
		buf28[i] = temp[i];
	}
}

// 28 bytes Left shift nShift time(s)
void LShift(BYTE *buf28, int nShift)
{
	int i;
	BYTE temp[2];

	for (i=0; i<nShift; i++)
	{
		temp[i] = buf28[i];
	}

	for (i=nShift; i<28; i++)
	{
		buf28[i-nShift] = buf28[i];
	}

	for (i=0; i<nShift; i++)
	{
		buf28[28-nShift+i] = temp[i] ;
	}
}

// result <== f( R, K )
void fFunction(BYTE* R, BYTE* K, BYTE* result)
{
	BYTE temp[48];	// store temp data 
	BYTE SResult[32];	// store result of S_Change
	
	// R ==> E_TABLE ==> temp
	SelectExchangeFromTable(E_TABLE, R, temp);

	// temp .EOR. K ==> temp
	EOR(K, temp, 48);

	// temp ==> S_Change ==> SResult
	S_Change(temp, SResult);

	// SResult ==> P_TABLE ==> result
	SelectExchangeFromTable(P_TABLE, SResult, result);
}

// dst <== src .EOR. dst
void EOR(BYTE * src, BYTE* dst, int n)
{
	for (int i=0; i<n; i++)
	{
		dst[i] = (src[i] + dst[i])%2 ;
	}
}

// src ==> S_Change ==> src
void S_Change(BYTE* src, BYTE* result)
{
	BYTE sTemp;
	for (int i=0; i<8; i++)
	{
		BYTE nPos;
		BYTEStruct& rBSPos = (BYTEStruct&)nPos ;
		
		nPos = 0;

		rBSPos.b0 = src[i*6+5];
		rBSPos.b1 = src[i*6+4];
		rBSPos.b2 = src[i*6+3];
		rBSPos.b3 = src[i*6+2];
		rBSPos.b4 = src[i*6+1];
		rBSPos.b5 = src[i*6+0];
		if (i%2==0)
		{
			// S Table Result ==> High 4 bits of sTemp
			sTemp= TABLE_s[i][nPos]*16;
		}
		else
		{
			// S Table Result ==> Low 4 bits of sTemp
			sTemp += TABLE_s[i][nPos];

			// sTemp Expand to 8 bytes
			BitToByte(&sTemp, &result[i/2*8], 1);
		}
	}

}

void asctobcd(char *bcd, char *asc, int len)
{
	char	p[1024];
	int	i, j;
	
	for(i = 0; i < len; i++) {
		if( (asc[i] >= '0') && (asc[i] <= '9') )
			p[i] = asc[i] - '0';
		else if( (asc[i] >= 'a') && (asc[i] <= 'f') )
			p[i] = asc[i] - 'a' + 10;
		else if( (asc[i] >= 'A') && (asc[i] <= 'F') )
			p[i] = asc[i] - 'A' + 10;
		
		else {
			p[i] = 0;
		}
	}
	
	j = (len + len%2) / 2;
	if( len%2 ) p[len+1] = 0;
	
	for (i=0; i<j; i++) {
		bcd[i] = (p[2*i] & 0x0f)<<4;
		bcd[i] |= (p[2*i+1] & 0x0f);
	}
	return;
}

/*-------------------------------------------
entry:	bcd
len	---  the length of asc
return:	asc
---------------------------------------------*/
void bcdtoasc(char *asc, char *bcd, int len)
{
	int	i, j;
	
	j = (len + len%2) / 2;
	for(i=0; i<j; i++) {
		asc[2*i] = (bcd[i] >> 4) & 0x0f;
		asc[2*i+1] = bcd[i] & 0x0f;
	}
	for(i=0; i<len; i++) {
		if( asc[i] > 0x09)
			asc[i] = 'A' + asc[i] - 0x0a;
		else	asc[i] += '0';
	}
	
	asc[len] = 0;
}