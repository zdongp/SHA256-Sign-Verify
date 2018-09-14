#include <stdio.h>
#include <stdlib.h>
//#include <cutils/properties.h>
#include "types_def.h"
#include "commonFunc.h"

#include <ctype.h>
#include <string.h>

#include "global.h"
#include "param.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "controlID.h"


#define  TPMS_MAX_ALARM_TEMPERATRUE   "fly.tpms.max_alarm_temperatrue"
#define  TPMS_MAX_ALARM_TIRE_PRESSURE "fly.tpms.max_alarm_tirpre"
#define  TPMS_MIN_ALARM_TIRE_PRESSURE "fly.tpms.min_alarm_tirpre"
#define  TPMS_TEMPERATRUE_UINT        "fly.tpms.temperatrue_uint"
#define  TPMS_PRESSURE_UINT           "fly.tpms.pressure_uint"
#define  TPMS_ALARM_TYPE              "fly.tpms.alarm_trpe"
#define  TPMS_SWAP_TIRE_ARR0           "fly.tpms.swaptirearr0"
#define  TPMS_SWAP_TIRE_ARR1           "fly.tpms.swaptirearr1"
#define  TPMS_SWAP_TIRE_ARR2           "fly.tpms.swaptirearr2"
#define  TPMS_SWAP_TIRE_ARR3           "fly.tpms.swaptirearr3"




tpms_local_param_t localParam;
tpms_local_param_t *pLocalParam = (tpms_local_param_t*)&localParam;
TPMS_Data local_TPMS_Data[4];

tpms_global_param_t globalParam;
tpms_global_param_t *pGlobalParam = (tpms_global_param_t*)&globalParam;

CNotifyAndResponseFlyJniSdk g_clsTpms;

void readParameter(void){

	LOGD("-------------readParameter--------------");

	char property[PROPERTY_VALUE_MAX];

	property_get(TPMS_MAX_ALARM_TEMPERATRUE,property,"70");
	sscanf(property,"%d", &pLocalParam->u32_tpms_max_alarm_temperature);

	property_get(TPMS_MAX_ALARM_TIRE_PRESSURE,property,"450");
	sscanf(property,"%d", &pLocalParam->u32_tpms_max_alarm_tire_pressure);

	property_get(TPMS_MIN_ALARM_TIRE_PRESSURE,property,"260");
	sscanf(property,"%d", &pLocalParam->u32_tpms_min_alarm_tire_pressure);

	property_get(TPMS_TEMPERATRUE_UINT,property,"0");
	sscanf(property,"%d", &pLocalParam->u8_tpms_termerature_uint);

	property_get(TPMS_PRESSURE_UINT,property,"0");
	sscanf(property,"%d", &pLocalParam->u8_tpms_tire_pressure_uint);


	property_get(TPMS_ALARM_TYPE,property,"0");
	sscanf(property,"%d", &pLocalParam->u8_tpms_alarm_type);

	property_get(TPMS_SWAP_TIRE_ARR0,property,"0");
	sscanf(property,"%d", &pLocalParam->tireSignIDArr[0]);
	property_get(TPMS_SWAP_TIRE_ARR1,property,"0");
	sscanf(property,"%d", &pLocalParam->tireSignIDArr[1]);
	property_get(TPMS_SWAP_TIRE_ARR2,property,"0");
	sscanf(property,"%d", &pLocalParam->tireSignIDArr[2]);
	property_get(TPMS_SWAP_TIRE_ARR3,property,"0");
	sscanf(property,"%d", &pLocalParam->tireSignIDArr[3]);
	if(pLocalParam->tireSignIDArr[0] == 0)
	{
		localParam.tireSignIDArr[0]=CONTROLID_TPMS_FL_SIGN;
		localParam.tireSignIDArr[1]=CONTROLID_TPMS_FR_SIGN;
		localParam.tireSignIDArr[2]=CONTROLID_TPMS_RL_SIGN;
		localParam.tireSignIDArr[3]=CONTROLID_TPMS_RR_SIGN;
	}
    Clean_TireData(emTire_FL);
 	Clean_TireData(emTire_FR);
	Clean_TireData(emTire_RL);
 	Clean_TireData(emTire_RR);

}

void saveParameter(void){

	LOGD("---------saveParameter-----------------");

	char property[PROPERTY_VALUE_MAX];

	sprintf(property,"%d", pLocalParam->u8_tpms_alarm_type);
	property_set(TPMS_ALARM_TYPE,property);

	sprintf(property,"%d", pLocalParam->u8_tpms_tire_pressure_uint);
	property_set(TPMS_PRESSURE_UINT,property);

	sprintf(property,"%d", pLocalParam->u8_tpms_termerature_uint);
	property_set(TPMS_TEMPERATRUE_UINT,property);

	sprintf(property,"%d",pLocalParam->u32_tpms_min_alarm_tire_pressure);
	property_set(TPMS_MIN_ALARM_TIRE_PRESSURE,property);

	sprintf(property,"%d", pLocalParam->u32_tpms_max_alarm_tire_pressure);
	property_set(TPMS_MAX_ALARM_TIRE_PRESSURE,property);

	sprintf(property,"%d", pLocalParam->u32_tpms_max_alarm_temperature);
	property_set(TPMS_MAX_ALARM_TEMPERATRUE,property);

	sprintf(property,"%d", pLocalParam->tireSignIDArr[0]);
	property_set(TPMS_SWAP_TIRE_ARR0,property);
	sprintf(property,"%d", pLocalParam->tireSignIDArr[1]);
	property_set(TPMS_SWAP_TIRE_ARR1,property);
	sprintf(property,"%d", pLocalParam->tireSignIDArr[2]);
	property_set(TPMS_SWAP_TIRE_ARR2,property);
	sprintf(property,"%d", pLocalParam->tireSignIDArr[3]);
	property_set(TPMS_SWAP_TIRE_ARR3,property);

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
		if (nOutputSize < nDstLen)//装不下，回退
		{
			nDstLen -= 2;
			break;
		}
		else
			memcpy(pUnic, &oneUnic, 2);

		nSrcLen += nOneUtf8Len;
		if (nSrcLen >= nInputLen)//解析完了，退出
		{
			break;
		}

		pUtf8 += nOneUtf8Len;
		pUnic += 2;

		nOneUtf8Len = enc_get_utf8_size(*pUtf8);
	}

	return nDstLen;
}

uni16_size_t uni16_strlen(const unicode16_t *uni16)
{
	return 0;
}
unicode16_t ansi_to_unicode16(const unsigned char ansi)
{
	return 0;
}
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16)
{
	int nSrcLen = strlen((char*)ansi);
	int nUni16Len = nSrcLen*2+2;
	int nRetLen = utf8_2_ucs2(ansi, nSrcLen, (u8*)uni16, nUni16Len);
	
	return (nRetLen/2);
}
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src)
{
	return 0;
}
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16)
{
	return 0;
}

