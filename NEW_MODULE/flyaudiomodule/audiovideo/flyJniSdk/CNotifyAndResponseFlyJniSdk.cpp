//moupeng  2015/7/25
#include "CNotifyAndResponseFlyJniSdk.h"
#include "otherModuleResponseFunction.h"
#include "halRequestFunction.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "appResponseFunction.h"

#include "param.h"


CNotifyAndResponseFlyJniSdk:: CNotifyAndResponseFlyJniSdk()
{

}

CNotifyAndResponseFlyJniSdk:: ~CNotifyAndResponseFlyJniSdk()
{

}


void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkSoundVideoChannel(u8 soundVideoChannel)
{
    LOGD("[%s] gsoundVideoChannel:%x",__FUNCTION__,soundVideoChannel);
    u8 buf[] = {0x00,0x00};
	buf[0] = 0x00;
	buf[1] = soundVideoChannel;
	makeAndSendMessageToModule( MODULE_ID_AUDIOVIDEO,MODULE_ID_FLYJNISDK,buf,2);    
}

void CNotifyAndResponseFlyJniSdk::analyseFromFlyJniSdkMessage(unsigned char *p,int len)
{
	LOGD("[%s] p[0]:%x p[1]:%x",__FUNCTION__,p[0],p[1]);
	switch(p[0])
	{
		case 0x00:
		{
			u8 ucBackMode = 0;
			int paramLen=0;
			getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
			if(ucBackMode != 0x01)
			{
				moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(p[1]);
			}
		}
		break;
		case 0x01:
			RequestAudioFocus(p[1]);
		break;
		case 0x02:
			RequestAudioMuteOrUnMute(p[1]);
		break;
		case 0xFE:
			analyseFormSdkMessageAudio(p+1,len - 1);
		break;
		default:break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseFormSdkMessageAudio(u8 *param, int len)
{
	switch(param[0])
	{
		case 0x01:
			if(param[1] == 0x00 || param[1] == 0x01)
				audioToHal_SetMute(param[1]);
			break;
		case 0x02:
			if(param[1] == 0x00 || param[1] == 0x01)
			{
				pLocalParam->bMuteIsOsd = false;
				audioToHal_SetMute(param[1]);
			}
			break;
		case 0x03:
			{
				sdkToAudioVideoSetVolumeAddOrDec(param[1],param[2],pLocalParam->volume,pLocalParam->uMaxVol);
			}
			break;
		case 0x04:
			sendToFlyJniSdkCurVolumeValue(pLocalParam->uMaxVol,0,pLocalParam->volume);
			break;
		case 0x05:
			sdkToAudioVideoSetVolumeSpecificValue(param[1],pLocalParam->uMaxVol);
			break;
		case 0x06:
			if(param[1] == 0x01)
				sendToApp_AudioChannelChange(pLocalParam->soundVideoChannel);
			break;
		case 0x07:
			moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(param[1]);
			break;
		case 0x08:
		if(param[1] == 0x01)
		{
			for(int i = 0x00;i <0x0a;i++)
				sendToApp_EQFreqValue(i, pLocalParam->EQValue[i]);
		}
			break;
		case 0x09:
		{
			sendToApp_EQPresetValue(pLocalParam->settingIndex);
		}
			break;
		case 0x0a:
		{
			analyseSdkGetHighSchoolBassInfo(param + 1);
		}
			break;
		case 0x0b:
		{
			if(param[1] == 0x00)
				sendToApp_SoundBalanceValue(0x00,pLocalParam->balance);
			else if(param[1] == 0x01)
				sendToApp_SoundBalanceValue(0x01,pLocalParam->fader);
		}
			break;
		case 0x0c:
		{
			if(param[1] == 0x01)
				sendToApp_LoudnessSwitchStatus(pLocalParam->bIsLoudnessOn);
		}
			break;
		case 0x0d:
		{
			if(param[1] >= 0x00 && param[1] <= 0x09)
			{
				if(param[2] >= 0x00 &&param[2] <= 0x18)
					audioToHal_SetSingleEQValue(param[1],param[2]);	
			}
		}
			break;
		case 0x0e:
		{
			if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != param[1])
				audioToHal_SetInnerEQSetting(param[1]);
		}
			break;
		case 0x0f:
		{
			if(param[1] >= 0x00 && param[1] <= 0x02)
			{
				param[1] = param[1] +1;
				appToAudioVideo_EQ_SaveUser(param[1]);
			}
		}
			break;
		case 0x10:
		{
			if(param[1] == 0x00)
				audioToHal_SetBassLevel(param[2]);
			else if(param[1] == 0x01)
				audioToHal_SetMidLevel(param[2]);
			else if(param[1] == 0x02)
				audioToHal_SetTredLevel(param[2]);
		}
			break;
		case 0x11:
		{
			if(param[1] == 0x00)
				audioToHal_SetBassFreq(param[2]);
			else if(param[1] == 0x01)
				audioToHal_SetMidFreq(param[2]);
			else if(param[1] == 0x02)
				audioToHal_SetTrebFreq(param[2]);
		}
			break;
		case 0x12:
		{
			if(param[1] == 0x00)
			{
				audioToHal_Balance(param[2]);
			}
			else if(param[1] == 0x01)
			{
				audioToHal_Fader(param[2]);
			}
		}
			break;
		case 0x13:
		{
			if(param[1] == 0x00||param[1] == 0x01)
				audioToHal_SetLoudnessSwitch(param[1]);
		}
			break;
		case 0x14:			
			analyseFromFlyJniSdkGetChannelVolume(param+1,len-1);
			break;
		case 0x15:
			analyseFromFlyJniSdkSetVolumeAddOrRed(param+1,len-1);
			break;
		default:break;
	}
}
void CNotifyAndResponseFlyJniSdk::analyseSdkGetHighSchoolBassInfo(u8 *param)
{
	switch(param[0])
	{
		case 0x01:
		{
			if(param[1] == 0x02)
				sendToApp_HighSchoolBassLevelValue(param[1],pLocalParam->trebPos);
			else if(param[1] == 0x01)
				sendToApp_HighSchoolBassLevelValue(param[1],pLocalParam->midPos);
			else if(param[1] == 0x00)
				sendToApp_HighSchoolBassLevelValue(param[1],pLocalParam->bassPos);
		}
		break;
		case 0x02:
		{
			if(param[1] == 0x00)
				sendToApp_HighSchoolBassFreqValue(param[1],pLocalParam->bass);
			else if(param[1] == 0x01)
				sendToApp_HighSchoolBassFreqValue(param[1],pLocalParam->mid);
			else if(param[1] == 0x02)
				sendToApp_HighSchoolBassFreqValue(param[1],pLocalParam->treb);
		}
	}
}
void CNotifyAndResponseFlyJniSdk::analyseFromFlyJniSdkGetChannelVolume(unsigned char *p,int len)
{
	LOGD("[%s] p[0]:%x p[1]:%x",__FUNCTION__,p[0],p[1]);
	switch(p[0])
	{
		case 0x00:
			sendToSdk_AudioCurChannelVolume(0x00,pLocalParam->sdkMediaVolume);
		break;
		case 0x01:
			sendToSdk_AudioCurChannelVolume(0x01,pLocalParam->sdkCallingVolume);
		break;
		default:break;
	}
}

void CNotifyAndResponseFlyJniSdk::analyseFromFlyJniSdkSetVolumeAddOrRed(u8 *buf,int len)
{
	int volume = 0xff;
	int step = 0;
	switch(buf[0])
	{
		case 0x00:
		{
			step = pLocalParam->uMaxVol/5;
			if(buf[1] == 0x00)
				volume = pLocalParam->volume - step;
			else if(buf[1] == 0x01)
				volume = pLocalParam->volume + step;
		}
		break;
		case 0x01:
			if(buf[1] == 0x00)
				volume = 0;
			else if(buf[1] == 0x01)
				volume = pLocalParam->uMaxVol;
		break;
		default:break;
	}
	if(volume != 0xff)
	{
		if(volume < 0)
			volume = 0;
		if(volume > pLocalParam->uMaxVol)
			volume = pLocalParam->uMaxVol;
		audioToHal_SetVolume(volume);
	}
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkCurCDIsMute(u8 p)
{
    u8 buf[] = {0x00,0x00};
	buf[0] = 0x01;
	buf[1] = p;
	makeAndSendMessageToModule( MODULE_ID_AUDIOVIDEO,MODULE_ID_FLYJNISDK,buf,2);    
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkCurAudioIsAndroidChannel(u8 p)
{
    u8 buf[] = {0x00,0x00};
	buf[0] = 0x02;
	buf[1] = p;
	makeAndSendMessageToModule( MODULE_ID_AUDIOVIDEO,MODULE_ID_FLYJNISDK,buf,2);    
}
void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkCurVolumeValue(u8 max,u8 min ,u8 param)
{
    u8 buf[4] = {0x00};
	buf[0] = 0x03;
	buf[1] = max;
	buf[2] = min;
	buf[3] = param;
	makeAndSendMessageToModule( MODULE_ID_AUDIOVIDEO,MODULE_ID_FLYJNISDK,buf,4);    
}

void CNotifyAndResponseFlyJniSdk::sdkToAudioVideoSetVolumeSpecificValue(u8 param , u8 MaxValue)
{
	u8 tempValue = -1;
	if(param < 0x00)
		tempValue = 0;
	else if(param > MaxValue)
		tempValue = MaxValue;
	else
		tempValue = param;
	audioToHal_SetVolume(tempValue);
}

/************************sendToAppBasicFunction*******************************/
void CNotifyAndResponseFlyJniSdk::sendToAppAudioStatusInfo(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = MESSAGETYPE_STATUS;
	if(len > 256)
		len = 256;
	memcpy(szMsg+1, buf, len);
	sendToAudioFlyJniSdkService(MODULE_SDK_AUDIOVIDEO, szMsg,len+1);
}
void CNotifyAndResponseFlyJniSdk::sdkToAudioVideoSetVolumeAddOrDec(u8 param,u8 value,u8 curValue,u8 MaxValue)
{
	u8 tempValue = -1;
	if(param == 0x00)
	{
		tempValue = curValue - value;
		if(tempValue < 0)
			tempValue = 0;
		audioToHal_SetVolume(tempValue);
	}
	else if(param == 0x01)
		{
			tempValue = curValue + value;
			if(tempValue > MaxValue)
				tempValue = MaxValue;
			audioToHal_SetVolume(tempValue);
		}
}
/*****************************sendToAppFunction*****************************/
void CNotifyAndResponseFlyJniSdk::sendToApp_AudioChannelChange(u8 param)
{
	u8 buf[] = {0x02,param};
	sendToAppAudioStatusInfo(buf,2);
}
void CNotifyAndResponseFlyJniSdk::sendToApp_EQFreqValue(u8 num, u8 Freq)
{
	u8 buf[] = {0x03,num,Freq};
	sendToAppAudioStatusInfo(buf,3);
}

void CNotifyAndResponseFlyJniSdk::sendToApp_EQPresetValue(u8 num)
{
	u8 buf[] = {0x04,num};
	sendToAppAudioStatusInfo(buf,2);
}

void CNotifyAndResponseFlyJniSdk::sendToApp_HighSchoolBassLevelValue(u8 num,u8 Freq)
{
	u8 buf[] = {0x05,num,Freq};
	sendToAppAudioStatusInfo(buf,3);
}

void CNotifyAndResponseFlyJniSdk::sendToApp_SoundBalanceValue(u8 num,u8 Freq)
{
	u8 buf[] = {0x06,num,Freq};
	sendToAppAudioStatusInfo(buf,3);
}

void CNotifyAndResponseFlyJniSdk::sendToApp_HighSchoolBassFreqValue(u8 num,u8 Freq)
{
	u8 buf[] = {0x07,num,Freq};
	sendToAppAudioStatusInfo(buf,3);
}

void CNotifyAndResponseFlyJniSdk::sendToApp_LoudnessSwitchStatus(u8 status)
{
	u8 buf[] = {0x08,status};
	sendToAppAudioStatusInfo(buf,3);
}
void CNotifyAndResponseFlyJniSdk::sendToSdk_AudioCurChannelVolume(u8 sdkSoundChannel,u8 sdkVolume)
{
	u8 buf[] = {0x09,sdkSoundChannel,sdkVolume};
	sendToAppAudioStatusInfo(buf,sizeof(buf));
}
