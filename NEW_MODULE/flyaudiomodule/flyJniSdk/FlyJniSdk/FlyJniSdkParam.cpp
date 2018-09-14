#include "FlyJniSdkParam.h"
#include "FlyJniSdkModuleBt.h"
#include "FlyJniSdkModuleRadio.h"
#include "FlyJniSdkModuleAudioVideo.h"
#include "FlyJniSdkModuleDvd.h"
#include "FlyJniSdkModuleSystem.h"
#include "FlyJniSdkModuleKey.h"
#include "FlyJniSdkModuleExtcar.h"
#include "FlyJniSdkModuleFlyJniSdk.h"
#include "FlyJniSdkModuleAc.h"
#include "FlyJniSdkModuleMedia.h"
#include "FlyJniSdkModuleAudioCtrl.h"
#include "FlyJniSdkModuleExtcarHondaTsu.h"
#include "FlyJniSdkModuleExternalCtrl.h"

extern CFlyModule *g_pFlyModule;
CFlyJniSdkModuleBt g_clsFlyJniSdkModuleBt;
CFlyJniSdkModuleRadio g_clsFlyJniSdkModuleRadio;
CFlyJniSdkModuleAudioVideo g_clsFlyJniSdkModuleAudioVideo;
CFlyJniSdkModuleDvd  g_clsFlyJniSdkModuleDvd;
CFlyJniSdkModuleSystem g_clsFlyJniSdkModuleSystem;
CFlyJniSdkModuleKey g_clsFlyJniSdkModuleKey;
CFlyJniSdkModuleExtcar g_clsFlyJniSdkModuleExtcar;
CFlyJniSdkModuleFlyJniSdk g_clsFlyJniSdkModuleFlyJniSdk;
CFlyJniSdkModuleAc g_clsFlyJniSdkModuleAc;
CFlyJniSdkModuleMedia g_clsFlyJniSdkModuleMedia;
CFlyJniSdkModuleAudioCtrl g_clsFlyJniSdkModuleAudioCtrl;
CFlyJniSdkModuleExtcarHondaTsu g_clsFlyJniSdkModuleExtcarHondaTsu;
CFlyJniSdkModuleExternalCtrl g_clsFlyJniSdkModuleExternalCtrl;



CFlyJniSdkParam::CFlyJniSdkParam(void)
{
}

CFlyJniSdkParam::~CFlyJniSdkParam(void)
{
}

void CFlyJniSdkParam::init(void)
{
	//≥ı ºªØ≤Œ ˝(init param), ¿‰∆Ù∂Ø≥ı ºªØ module µƒ µ⁄“ª¬÷œ˚œ¢
	LOGD("[%s] [%s]", __FILE__ , __FUNCTION__);

}

void CFlyJniSdkParam::initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam)
{
	m_pFlyJniSdkApp	 = (CFlyJniSdkApp *)pFlyApp; 
	m_pFlyJniSdkModule = (CFlyJniSdkModule *)pFlyModule; 
	m_pFlyJniSdkHal	 = (CFlyJniSdkHal *)pFlyHal; 
	m_pFlyJniSdkParam  = (CFlyJniSdkParam *)pFlyParam; 

	m_pFlyApp    = pFlyApp;
	m_pFlyModule = pFlyModule;
	m_pFlyHal    = pFlyHal;
	m_pFlyParam  = pFlyParam;

	m_pFlyJniSdkModuleBt = &g_clsFlyJniSdkModuleBt;
	m_pFlyJniModuleRadio = &g_clsFlyJniSdkModuleRadio;
	//moupeng 2015/7/25
	m_pFlyJniModuleAudioVideo=&g_clsFlyJniSdkModuleAudioVideo;
	//moupeng 2015/7/31
	m_pFlyJniModuleDvd=&g_clsFlyJniSdkModuleDvd;
	m_pFlyJniModuleSystem=&g_clsFlyJniSdkModuleSystem;
	m_pFlyJniModuleKey=&g_clsFlyJniSdkModuleKey;
	m_pFlyJniModuleExtcar=&g_clsFlyJniSdkModuleExtcar;
	m_pFlyJniModuleFlyJniSdk=&g_clsFlyJniSdkModuleFlyJniSdk;
	m_pFlyJniSdkModuleAc=&g_clsFlyJniSdkModuleAc;
	m_pFlyJniSdkModuleMedia=&g_clsFlyJniSdkModuleMedia;
	m_pFlyJniSdkModuleAudioCtrl=&g_clsFlyJniSdkModuleAudioCtrl;
	m_pFlyJniSdkModuleExtcarHondaTsu=&g_clsFlyJniSdkModuleExtcarHondaTsu;
	m_pFlyJnisdkModuleExternalCtrl=&g_clsFlyJniSdkModuleExternalCtrl;

}

void CFlyJniSdkParam::readParameter(void)
{
	LOGD("[%s]", __FUNCTION__);

	
}

void CFlyJniSdkParam::saveParameter(void)
{
	LOGD("[%s]", __FUNCTION__);

	
}


int enc_get_utf8_size(const unsigned char pInput)
{
	unsigned char c = pInput;
	if(c < 0x80) return 1;
	if(c >= 0x80 && c < 0xC0) return -1;
	if(c >= 0xC0 && c < 0xE0) return 2;
	if(c >= 0xE0 && c < 0xF0) return 3;
	if(c >= 0xF0 && c < 0xF8) return 4;
	if(c >= 0xF8 && c < 0xFC) return 5;
	if(c >= 0xFC) return 6;

	return -1;
}

int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
    char b1, b2, b3, b4, b5, b6;

    *Unic = 0x0; // 
    int utfbytes = enc_get_utf8_size(*pInput);
    unsigned char *pOutput = (unsigned char *)Unic;

    switch(utfbytes)
    {
    case 1:
        *pOutput = *pInput;
        break;
    case 2:
        b1 = *pInput;
        b2 = *(pInput + 1);
        if ( (b2 & 0xC0) != 0x80 )
            return 0;
        *pOutput     = (b1 << 6) + (b2 & 0x3F);
        *(pOutput+1) = (b1 >> 2) & 0x07;
        break;
    case 3:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b2 << 6) + (b3 & 0x3F);
        *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
        break;
    case 4:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b3 << 6) + (b4 & 0x3F);
        *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
        *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
        break;
    case 5:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b4 << 6) + (b5 & 0x3F);
        *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
        *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);
        *(pOutput+3) = (b1 << 6);
        break;
    case 6:
        b1 = *pInput;
        b2 = *(pInput + 1);
        b3 = *(pInput + 2);
        b4 = *(pInput + 3);
        b5 = *(pInput + 4);
        b6 = *(pInput + 5);
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
                || ((b6 & 0xC0) != 0x80) )
            return 0;
        *pOutput     = (b5 << 6) + (b6 & 0x3F);
        *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
        *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);
        *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
        break;
    default:
        return 0;
        break;
    }//switch(utfbytes)

    return utfbytes;
}


int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize)
{
	int nSrcLen = 0;
	int nDstLen = 0;
	u8 *pUtf8 = pInput;
	u8 *pUnic = pOutput;
	int nOneUtf8Len = 0;

	nOneUtf8Len = enc_get_utf8_size(*pUtf8);

	while(-1 != nOneUtf8Len)
	{
		unsigned long oneUnic = 0;
		enc_utf8_to_unicode_one(pUtf8, &oneUnic);

		nDstLen += 2;
		if (nOutputSize < nDstLen)//Ë£Ö‰∏ç‰∏ãÔºåÂõûÈÄÄ
		{
			nDstLen -= 2;
			break;
		}
		else
			memcpy(pUnic, &oneUnic, 2);

		nSrcLen += nOneUtf8Len;
		if (nSrcLen >= nInputLen)//Ëß£ÊûêÂÆå‰∫ÜÔºåÈÄÄÂá∫
		{
			break;
		}

		pUtf8 += nOneUtf8Len;
		pUnic += 2;

		nOneUtf8Len = enc_get_utf8_size(*pUtf8);
	}

	return nDstLen;
}

uni16_size_t CFlyJniSdkParam::uni16_strlen(const unicode16_t *uni16)
{
	return 0;
}
unicode16_t CFlyJniSdkParam::ansi_to_unicode16(const unsigned char ansi)
{
	return 0;
}
uni16_size_t CFlyJniSdkParam::ansi_str_to_unicode16(const unsigned char *ansi, unicode16_t *uni16)
{
	return 0;
}
unicode16_t *CFlyJniSdkParam::uni16_strcpy(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
unicode16_t *CFlyJniSdkParam::uni16_strcat(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
uni16_size_t CFlyJniSdkParam::utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16)
{
	return 0;
}


