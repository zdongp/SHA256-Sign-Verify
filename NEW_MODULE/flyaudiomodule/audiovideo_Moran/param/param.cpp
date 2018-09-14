#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <commonFunc.h>
#include <ctype.h>
#include <string.h>

#include "global.h"
#include "param.h"
#include "moduleParamResponse.h"
#include "appRequestFunction.h"
#include "moduleParamRequest.h"

audiovideo_local_param_t localParam;
audiovideo_local_param_t *pLocalParam = (audiovideo_local_param_t*)&localParam;

//moupeng 2015/7/25
CNotifyAndResponseFlyJniSdk g_clsAudiovideo;

#define FLY_MODULE_IS_T123 "fly.module.is.T123"

#define FLY_AV_SOUNDMODE    		"fly.av.soundMode"
#define FLY_AV_VOLUME				"fly.av.volume"
#define FLY_AV_BALANCE      		"fly.av.balance"
#define FLY_AV_FADER        		"fly.av.fader"
#define FLY_AV_SOUNDPOS				"fly.av.soundPos"

#define FLY_AV_TREB  				"fly.av.treb"
#define FLY_AV_MID					"fly.av.mid"
#define FLY_AV_BASS					"fly.av.bass"
#define FLY_AV_LOUDNESS				"fly.av.loudness"

#define FLY_AV_TREBPOS				"fly.av.trebPos"
#define FLY_AV_MIDPOS				"fly.av.midPos"
#define FLY_AV_BASSPOS				"fly.av.bassPos"
#define FLY_AV_LOUDNESSPOS 			"fly.av.loudnessPos"

#define PROPERTY_DEFAULT_VALUE	    "UNKNOW"
#define FLY_MODULECONFIG_TREB       "fly.audio.treb" 
#define FLY_MODULECONFIG_MID        "fly.audio.mid" 
#define FLY_MODULECONFIG_BASS       "fly.audio.bass" 
#define FLY_MODULECONFIG_TREDPOS    "fly.audio.trebPos" 
#define FLY_MODULECONFIG_MIDPOS     "fly.audio.midPos" 
#define FLY_MODULECONFIG_BASSPOS    "fly.audio.bassPos" 

#define FLY_AV_IMEQ					"fly.av.EQ"
#define FLY_AV_EQVALUE				"fly.av.EQValue"
#define FLY_AV_EQUSER1				"fly.av.EQUser1"
#define FLY_AV_EQUSER2				"fly.av.EQUser2"
#define FLY_AV_EQUSER3				"fly.av.EQUser3"
#define FLY_AV_FINETURNINGVALUE 	"fly.av.fineTurningValue"

#define FLY_AV_PREIMEQCONTROL       "fly.av.preEQControl"
#define FLY_HAL_MAXVOLUME           "fly.HAL.MaxVolume"

#define FLY_TPYE_VERSION 			"fly.tpye.version"
#define FLY_SET_CHANNEL  			"fly.set.channel"
#define FLY_VOL_MAX                 "fly.vol.startup.max"
#define FLY_AV_ZENGYI               "fly.av.zengyi"

//#define FLY_MODULE_AUDIO_VIDEO_LOUDNESS_SWITCH	"fly.module.audio.video.loudness.switch"
#define FLY_MODULE_AUDIO_VIDEO_LOUDNESS_SWITCH	"fly.loudness.switch"

#define FLY_MIXING_SWITCH  "fly.mixing.switch"

#define FLY_AV_PRADO_ASL		"fly.av.prado.asl"
#define FLY_AV_PRADO_SURROUND	"fly.av.prado.surround"

#define FLY_MODULE_WHICH_PROJECT 	"fly.module.whichProject"

char __intToChar(char value){
	if(value >= 0 && value <= 9){
		return (value+0x30);
	}
	else if(value >= 10 && value <=15){
		return (value + 0x37);
	}
	else{
		return '\0';
	}
}

char __charToInt(char ch){
	if(ch >= '0' && ch <= '9'){
		return (ch-0x30);
	}
	else if(ch >= 'A' && ch <= 'F'){
		return (ch-0x37);
	}
	else{
		return 0;
	}
}

int bufferToString(char *buffer, int len, char *str)
	{
		int n;
		int i , j;
		if(len <= 0 || len >= (PROPERTY_VALUE_MAX/2)){
			return -1;
		}

		for(i = 0, j=0; i < len; i++,j+=2){
			str[j] = __intToChar((buffer[i]&0xF0)>>4);
			str[j+1] = __intToChar((buffer[i]&0x0F));
		}
		str[2*len] = '\0';

		return (2*len+1);
	}

int stringToBuffer(char *str, char *buffer)
{
	int str_len = strlen(str);
	if(str_len <= 0)
		return 0;
	int i , j;
	for(i = 0, j=0; j < str_len; i++, j+=2){
		buffer[i] = __charToInt(str[j])<<4;
		buffer[i] += __charToInt(str[j+1]);
	}

	return (str_len/2);
}


void readParameter(void){
	LOGD("*************readParameter*****************");
	int value = 0;
	setDefaultParam();

	char property[PROPERTY_VALUE_MAX];

	property_get(FLY_MODULE_IS_T123,property,"0");
	sscanf(property,"%hhd",&pLocalParam->uModuleAudio_is_T123);

   	property_get(FLY_MODULE_WHICH_PROJECT,property,"0");
	sscanf(property,"%s",pLocalParam->str_WhichProject);

	property_get(FLY_TPYE_VERSION,property,"0");
	sscanf(property,"%d",&pLocalParam->Car_type_version);

	property_get(FLY_SET_CHANNEL,property,"0");
	sscanf(property,"%d",&pLocalParam->Default_channel);

	property_get(FLY_AV_SOUNDMODE,property,NULL);
	sscanf(property,"%d", &pLocalParam->savemode);
    LOGD("[%s] pLocalParam->savemode:%d",__FUNCTION__,pLocalParam->savemode);
	property_get(FLY_AV_VOLUME,property,"256");
	sscanf(property,"%d", &pLocalParam->readVolTemp);
	LOGD("[%s] pLocalParam->readVolTemp:%d",__FUNCTION__,pLocalParam->readVolTemp);

	property_get(FLY_AV_BALANCE,property,"10");
	sscanf(property,"%d", &pLocalParam->balance);

	property_get(FLY_AV_FADER,property,"10");
	sscanf(property,"%d", &pLocalParam->fader);

	property_get(FLY_AV_SOUNDPOS,property,"0");
	sscanf(property,"%d", &pLocalParam->soundPos);

    ////////////////////////////////////////////////////////////////////////////
        int nTempTreb=0;
        property_get(FLY_MODULECONFIG_TREB,property,"0");
        sscanf(property,"%d", &nTempTreb);
        LOGD("[%s] nTempTreb:%d",__FUNCTION__,nTempTreb);
        property_get(FLY_AV_TREB,property,"255");
        sscanf(property,"%d", &pLocalParam->treb);
        LOGD("[%s] pLocalParam->treb:%d",__FUNCTION__,pLocalParam->treb);
        if(pLocalParam->treb == 255)
        {
            pLocalParam->treb=nTempTreb;
        }
    
        int nTempMid=0;
        property_get(FLY_MODULECONFIG_MID,property,"0");
        sscanf(property,"%d", &nTempMid);
        LOGD("[%s] nTempMid:%d",__FUNCTION__,nTempMid);
        property_get(FLY_AV_MID,property,"255");
        sscanf(property,"%d", &pLocalParam->mid);
        if(pLocalParam->mid == 255)
        {
            pLocalParam->mid = nTempMid;
        }
    
        int nTempBass=0;
        property_get(FLY_MODULECONFIG_BASS,property,"0");
        sscanf(property,"%d", &nTempBass);
        property_get(FLY_AV_BASS,property,"255");
        sscanf(property,"%d", &pLocalParam->bass);
        if(pLocalParam->bass == 255)
        {
            pLocalParam->bass = nTempBass;
        }
        ////////////////////////////////////////////////////////////////////////////






	property_get(FLY_AV_LOUDNESS,property,"0");
	sscanf(property,"%d", &pLocalParam->loudness);





    ////////////////////////////////////////////////////////////////////////////
    int nTempTredPos=5;
    property_get(FLY_MODULECONFIG_TREDPOS,property,"5");
    sscanf(property,"%d", &nTempTredPos);
    LOGD("[%s] nTempTredPos:%d",__FUNCTION__,nTempTredPos);
	property_get(FLY_AV_TREBPOS,property,"255");
	sscanf(property,"%d", &pLocalParam->trebPos);
	LOGD("[%s] pLocalParam->trebPos:%d",__FUNCTION__,pLocalParam->trebPos);
	if(pLocalParam->trebPos == 255)
	{
	    pLocalParam->trebPos = nTempTredPos;
	}


    int nTempMidPos=5;
    property_get(FLY_MODULECONFIG_MIDPOS,property,"5");
    sscanf(property,"%d", &nTempMidPos);
	property_get(FLY_AV_MIDPOS,property,"255");
	sscanf(property,"%d", &pLocalParam->midPos);
	if(pLocalParam->midPos == 255)
	{
	    pLocalParam->midPos = nTempMidPos;
	}

    int nTempBassPos=5;
    property_get(FLY_MODULECONFIG_BASSPOS,property,"5");
    sscanf(property,"%d", &nTempBassPos);
	property_get(FLY_AV_BASSPOS,property,"255");
	sscanf(property,"%d", &pLocalParam->bassPos);
	if(pLocalParam->bassPos == 255)
	{
	    pLocalParam->bassPos = nTempBassPos;
	}
    ////////////////////////////////////////////////////////////////////////////

	property_get(FLY_AV_LOUDNESSPOS,property,"0");
	sscanf(property,"%d", &pLocalParam->loudnessPos);

	property_get(FLY_AV_IMEQ,property,"3");
	sscanf(property,"%d", &pLocalParam->readPowerOnEQTemp);
	pLocalParam->settingIndex = pLocalParam->readPowerOnEQTemp;

	property_get(FLY_AV_PREIMEQCONTROL,property,NULL);
	sscanf(property,"%d", &pLocalParam->preSettingIndexControl);

	
	property_get(FLY_MODULE_AUDIO_VIDEO_LOUDNESS_SWITCH,property,"1");  //default EQ Loundess on
	sscanf(property,"%d", &value);
	pLocalParam->bIsLoudnessOn = (0 == value) ? 0 : 1;
	LOGD("[%s] pLocalParam->bIsLoudnessOn:%d", __FUNCTION__,pLocalParam->bIsLoudnessOn);

	char buffer[16];

	property_get(FLY_AV_EQVALUE, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->EQValue, buffer, 16);
	}

	property_get(FLY_AV_EQUSER1, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->EQUser1, buffer, 16);
	}

	property_get(FLY_AV_EQUSER2, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->EQUser2, buffer, 16);
	}

	property_get(FLY_AV_EQUSER3, property, NULL);
	value = stringToBuffer(property, buffer);
	if(value > 0){
		memcpy(pLocalParam->EQUser3, buffer, 16);
	}

	property_get(FLY_MIXING_SWITCH,property,0);
	sscanf(property,"%hhd", &pLocalParam->bIsMixingSwitch);

	property_get(FLY_AV_ZENGYI,property,"10");
	sscanf(property,"%d", &pLocalParam->AvAmplitude);
    LOGD("[%s] pLocalParam->AvAmplitude=%d",__FUNCTION__,pLocalParam->AvAmplitude);
    readHalProperty_aboutMaxVolumeVal();

	//prado
	property_get(FLY_AV_PRADO_ASL,property,0);
	sscanf(property,"%d", &pLocalParam->m_nPradoAsl);

	property_get(FLY_AV_PRADO_SURROUND,property,0);
	sscanf(property,"%d", &pLocalParam->m_nPradoSurround);

}

void readHalProperty_aboutMaxVolumeVal()
{
    char property[PROPERTY_VALUE_MAX];
    property_get(FLY_HAL_MAXVOLUME,property,"40");
	sscanf(property,"%hhd",&pLocalParam->uMaxVol);
	LOGD("[%s] pLocalParam->uMaxVol:%d",__FUNCTION__,pLocalParam->uMaxVol);
}

void saveParameter(void){
	LOGD("*************saveParameter*****************");

	char property[PROPERTY_VALUE_MAX];
	LOGD("[%s] soundvideochannel 1:%x",__FUNCTION__,pLocalParam->soundVideoChannel);
	if((pLocalParam->soundVideoChannel >= CHANNEL_DVD_CTRL) && (pLocalParam->soundVideoChannel <= CHANNEL_MAX)){
			sprintf(property,"%d", pLocalParam->soundVideoChannel);
			LOGD("[%s] soundvideochannel 2:%x",__FUNCTION__,pLocalParam->soundVideoChannel);
	}
	else {
		sprintf(property,"%d", CHANNEL_NOCHANNEL);
	}

	property_set(FLY_AV_SOUNDMODE,property);

	u8 startVol=0;
	u8 startVolLen=0;
	getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_SET_STARTUPVOL, &startVol, &startVolLen);
    LOGD("[%s] startVol:%d pLocalParam->volume:%d",__FUNCTION__,startVol,pLocalParam->volume);
	if(startVol == 0xFF ){
		pLocalParam->readVolTemp = pLocalParam->volume;
	}
	else
	{
	    pLocalParam->readVolTemp = startVol;
	}

	sprintf(property,"%d", pLocalParam->readVolTemp);
	property_set(FLY_AV_VOLUME,property);

	sprintf(property,"%d", pLocalParam->balance);
	property_set(FLY_AV_BALANCE,property);

	sprintf(property,"%d", pLocalParam->fader);
	property_set(FLY_AV_FADER,property);

	sprintf(property,"%d", pLocalParam->soundPos);
	property_set(FLY_AV_SOUNDPOS,property);

	sprintf(property,"%d", pLocalParam->treb);
	property_set(FLY_AV_TREB,property);

	sprintf(property,"%d", pLocalParam->mid);
	property_set(FLY_AV_MID,property);

	sprintf(property,"%d", pLocalParam->bass);
	property_set(FLY_AV_BASS,property);

	sprintf(property,"%d", pLocalParam->loudness);
	property_set(FLY_AV_LOUDNESS,property);

	sprintf(property,"%d", pLocalParam->trebPos);
	property_set(FLY_AV_TREBPOS,property);

	sprintf(property,"%d", pLocalParam->midPos);
	property_set(FLY_AV_MIDPOS,property);

	sprintf(property,"%d", pLocalParam->bassPos);
	property_set(FLY_AV_BASSPOS,property);

	sprintf(property,"%d", pLocalParam->loudnessPos);
	property_set(FLY_AV_LOUDNESSPOS,property);

	bufferToString((char *)pLocalParam->EQValue, 16, property);
	property_set(FLY_AV_EQVALUE, property);

	bufferToString((char *)pLocalParam->EQUser1, 16, property);
	property_set(FLY_AV_EQUSER1, property);

	bufferToString((char *)pLocalParam->EQUser2, 16, property);
	property_set(FLY_AV_EQUSER2, property);

	bufferToString((char *)pLocalParam->EQUser3, 16, property);
	property_set(FLY_AV_EQUSER3, property);

	sprintf(property,"%d", pLocalParam->settingIndex);
	property_set(FLY_AV_IMEQ,property);

	sprintf(property,"%d", pLocalParam->preSettingIndexControl);
	property_set(FLY_AV_PREIMEQCONTROL,property);

	sprintf(property, "%hhd", pLocalParam->bIsLoudnessOn ? 1 : 0);
	property_set(FLY_MODULE_AUDIO_VIDEO_LOUDNESS_SWITCH,property);
	LOGD("[%s] pLocalParam->bIsLoudnessOn:%d",__FUNCTION__,pLocalParam->bIsLoudnessOn ? 1 : 0);
	
	sprintf(property,"%hhd", pLocalParam->bIsMixingSwitch);
	property_set(FLY_MIXING_SWITCH,property);

	sprintf(property,"%d", pLocalParam->AvAmplitude);
	property_set(FLY_AV_ZENGYI,property);

	//prado
	sprintf(property,"%d", pLocalParam->m_nPradoAsl);
	property_set(FLY_AV_PRADO_ASL,property);

	sprintf(property,"%d", pLocalParam->m_nPradoSurround);
	property_set(FLY_AV_PRADO_SURROUND,property);

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

// ����׼�ַ�ת����unicode16���ַ�
unicode16_t ansi_to_unicode16(const unsigned char ansi)
{
	return 0;
}

// ����׼�ַ���ת����unicode16���ַ���
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

