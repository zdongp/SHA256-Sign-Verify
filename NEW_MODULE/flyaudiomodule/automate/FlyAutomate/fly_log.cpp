#include "fly_log.h"

char g_cOutput[OUTPUT_MAX_LEN];

void TransformIntegerToAcsii(u8* pDest, u32 iSrc, u8 ucStep, u8 ucLen)
{
	u8* pTmp = new u8[ucLen];
	memset(pTmp, '0', ucLen);
	u8 ucIndex = ucLen;
	if (10 == ucStep)
	{
		while ((iSrc > 0) && (ucIndex > 0))
		{
			ucIndex--;
			pTmp[ucIndex] = (iSrc%10) + '0';
			iSrc = iSrc/10;
		}
	}
	else if (16 == ucStep)
	{
		while ((iSrc > 0) && (ucIndex > 0))
		{
			ucIndex--;
			if ((iSrc%16)<10)
				pTmp[ucIndex] = (iSrc%16) + '0';
			else
				pTmp[ucIndex] = (iSrc%16) - 10 + 'A';

			iSrc = iSrc/16;
		}
	}
	memcpy(pDest, pTmp, ucLen);
	delete[] pTmp;
	pTmp = NULL;
}

int TransformAcsiiToInteger(u8* pSrc, u8 ucLen)
{
	//u8* pTmp = new u8[ucLen];
	//memset(pTmp, '0', ucLen);
	//memcpy(pTmp, pSrc, ucLen);
	//return atoi((char*)pTmp);
	//delete[] pTmp;
	//pTmp = NULL;

	static u8 pTmp[50] = {0};
	memset(pTmp, 0, sizeof(pTmp));
	
	if(ucLen > 50){
		ucLen = 50;
	}
	
	memcpy(pTmp, pSrc, ucLen);
	return atoi((char*)pTmp);
}