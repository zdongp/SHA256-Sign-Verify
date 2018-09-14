#include "FlyJniSdkModuleAudioVideo.h"


CFlyJniSdkModuleAudioVideo::CFlyJniSdkModuleAudioVideo(void)
{

}

CFlyJniSdkModuleAudioVideo::~CFlyJniSdkModuleAudioVideo(void)
{

}

void CFlyJniSdkModuleAudioVideo::SetAudioVideo_Channel(u8 p)
{
	LOGD("%s] p:%x",__FUNCTION__,p);
	u8 buf[2] = {0x00,0x00};
	buf[0] = 0x00;
	buf[1] = p;
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK,MODULE_ID_AUDIOVIDEO,buf,2);
}
	
void CFlyJniSdkModuleAudioVideo::getAppCtrlMessage(u8 *p, u8 len)
{
	LOGD("[%s] Module_audiovideo p[0]:%x", __FUNCTION__,p[0]);
	switch(p[0])
	{
		case 0x0B:
			SetAudioVideo_Channel(p[1]);
			break;
		case 0x0C:
			break;
		default:break;
	}
}

void CFlyJniSdkModuleAudioVideo::getAudioVideoMessage(u8 *p, u8 len)
{
    LOGD("[%s] p[0]:%x",__FUNCTION__,p[0]);
	switch(p[0])
	{
       case 0x00:
			onAudioVideoSoundVideoChannel(p[1]);
			break;
		case 0x01:
			onAudioVideoSoundIsMute(p[1]);
			break;
		case 0x02:
			onAudioVideoIsAndroidChannel(p[1]);
			break;
		case 0x03:
			sendToAppCurVolumeValue(p+1,len -1);
			break;
		default:break;
	}	   
}
void CFlyJniSdkModuleAudioVideo::onAudioVideoSoundVideoChannel(u8 p)
{
    LOGD("[%s] AudioVideo:%x",__FUNCTION__,p);
	u8 szMsg[2] = {0x05, p};
	setToFlyJniSdkService(MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleAudioVideo::onAudioVideoSoundIsMute(u8 p)
{
	u8 szMsg[2] = {0x06, p};
	setToFlyJniSdkService(MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
}

void CFlyJniSdkModuleAudioVideo::onAudioVideoIsAndroidChannel(u8 p)
{
	u8 szMsg[2] = {0x07, p};
	setToFlyJniSdkService(MODULE_ID_AUDIOVIDEO, szMsg, sizeof(szMsg));
}

/******************new pro*********************/
void CFlyJniSdkModuleAudioVideo::analyseAudioVideoAppMessageType(u8 *p, u8 len)
{
	LOGD("[%s]	p[0]:%x --p[1]:%x len:%x",__FUNCTION__,p[0],p[1],len);
	switch(p[0])
	{
		case RESPONE_CHANGE_STATE:
			analyseReturnAudioStatusMassage(p+1, len - 1);
			break;
		case CONTROL_MESSAGE:
			analyseAudioVideoControlAudioOperationMassage(p+1, len - 1);
			break;
		default:break;
	}
}
void CFlyJniSdkModuleAudioVideo::analyseAudioVideoControlAudioOperationMassage(u8 *buf ,u8 len)
{
	switch(buf[0])
	{
		case 0x01:
			if(buf[1] == 0x01 || buf[1] == 0x00)
			{
				sendToAudioSetMute(buf[1]);
			}
			break;
		case 0x02:
			if(buf[1] == 0x01 || buf[1] == 0x00)
			{
				sendToAudioSetMute_NoOSD(buf[1]);
			}
			break;
		case 0x03:
			{
				if(buf[1] == 0x00||buf[1] == 0x01)
				{
					sendToAudioSetVolume(buf+1,2);
				}
			}
			break;
		case 0x04:
			{
				sendToAudioSetSpecificVolume(buf[1]);
			}
			break;
		case 0x05:
			sendToAudioSetChangeAudioChannel(buf[1]);
			break;
		case 0x06:
			{
				if(buf[1] >= 0x00 &&buf[1] <= 0x09)
				{
					if(buf[2] >= 0x00 &&buf[1] <= 0x18)
					sendToAudioSetEQFreqPointValue(buf[1],buf[2]);
				}
			}
			break;
		case 0x07:
			{
				sendToAudioSetEQPresetValue(buf[1]);
			}
			break;
		case 0x08:
			{
				sendToAudioSetSaveEQCustomValue(buf[1]);
			}
			break;
		case 0x09:
			{
				if(buf[1] >= 0x00 &&buf[1] <= 0x02)
				{
					if(buf[2] >= 0x00 &&buf[1] <= 0x0a)
						sendToAudioSetHighSchoolBassValue(buf[1],buf[2]);
				}
			}
			break;
		case 0x0a:
			{
				if(buf[1] >= 0x00 &&buf[1] <= 0x02)
				{
					sendToAudioSetHighSchoolBassFreqSwitch(buf[1],buf[2]);
				}
			}
			break;
		case 0x0b:
			{
				if(buf[1] >= 0x00 &&buf[1] <= 0x01)
				{
					if(buf[2] >= 0x00 &&buf[1] <= 0x14)
						sendToAudioSetSoundBalance(buf[1],buf[2]);
				}
			}
			break;
		case 0x0c:
			{
				sendToAudioSetLoudnessSwitch(buf[1]);
			}
			break;
		case 0x0d:
			sendToAudioSetVolumeAddOrRed(buf+1,len -1);
			break;
		default:break;
	}
}

void CFlyJniSdkModuleAudioVideo::analyseReturnAudioStatusMassage(u8 *buf ,u8 len)
{
	switch(buf[0])
	{
		case 0x01:
		{
			if(buf[1] == 0x01)
				sendToAudiogetCurVolumeValue(buf[1]);	
		}
		break;
		case 0x02:
		{
			if(buf[1] == 0x01)
				sendToAudiogetCurAudioChannel(buf[1]);
		}
			break;
		case 0x03:
			sendToAudiogetCurEQFreqPointValue(buf[1]);
			break;
		case 0x04:
			sendToAudiogetCurEQPresetValue(buf[1]);
			break;
		case 0x05:
		{
			if(buf[1] == 0x01 ||buf[1] == 0x02)
				sendToAudiogetCurHighSchoolBassValue(buf[1],buf[2]);
		}
			break;
		case 0x06:
		{
			if(buf[1] == 0x01)
				sendToAudiogetCurSoundBalanceValue(buf[1]);
		}
			break;
		case 0x07:
			sendToAudiogetCurLoudnessValue(buf[1]);
			break;
		case 0x08:
				sendToAudiogetCurChannelVolume(buf+1,len - 1);
			break;
		default:break;
	}
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetMute(u8 param)
{
	u8 buf[] = {0xfe,0x01, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetMute_NoOSD(u8 param)
{
	u8 buf[] = {0xfe,0x02, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetVolume(u8 *param,int len)
{
	u8 buf[4] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x03;
	memcpy(buf+2,param,2);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 4);
}
void CFlyJniSdkModuleAudioVideo::sendToAudiogetCurVolumeValue(u8 param)
{
	u8 buf[] = {0xfe,0x04, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}

void CFlyJniSdkModuleAudioVideo::sendToAudioSetSpecificVolume(u8 param)
{
	u8 buf[] = {0xfe,0x05, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}

void CFlyJniSdkModuleAudioVideo::sendToAudiogetCurAudioChannel(u8 param)
{
	u8 buf[] = {0xfe,0x06, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetChangeAudioChannel(u8 param)
{
	u8 buf[] = {0xfe,0x07, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudiogetCurEQFreqPointValue(u8 param)
{
	u8 buf[] = {0xfe,0x08, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudiogetCurEQPresetValue(u8 param)
{
	u8 buf[] = {0xfe,0x09, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudiogetCurHighSchoolBassValue(u8 param,u8 param1)
{
	u8 buf[] = {0xfe,0x0a, param,param1};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 4);
}
void CFlyJniSdkModuleAudioVideo::sendToAudiogetCurSoundBalanceValue(u8 param)
{
	u8 buf[] = {0xfe,0x0b, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudiogetCurLoudnessValue(u8 param)
{
	u8 buf[] = {0xfe,0x0c, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}

void CFlyJniSdkModuleAudioVideo::sendToAudioSetEQFreqPointValue(u8 param,u8 param1)
{
	u8 buf[] = {0xfe,0x0d, param,param1};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 4);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetEQPresetValue(u8 param)
{
	u8 buf[] = {0xfe,0x0e, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetSaveEQCustomValue(u8 param)
{
	u8 buf[] = {0xfe,0x0f, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetHighSchoolBassValue(u8 param,u8 param1)
{
	u8 buf[] = {0xfe,0x10, param,param1};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 4);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetHighSchoolBassFreqSwitch(u8 param,u8 param1)
{
	u8 buf[] = {0xfe,0x11, param,param1};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 4);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetSoundBalance(u8 param,u8 param1)
{
	u8 buf[] = {0xfe,0x12, param,param1};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 4);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetLoudnessSwitch(u8 param)
{
	u8 buf[] = {0xfe,0x13, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 3);
}
void CFlyJniSdkModuleAudioVideo::sendToAudiogetCurChannelVolume(u8 *buf,int len)
{
	u8 buff[4] = {0};
	buff[0] = 0xfe;
	buff[1] = 0x14;
	memcpy(buff+2,buf,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buff, len+2);
}
void CFlyJniSdkModuleAudioVideo::sendToAudioSetVolumeAddOrRed(u8 *param,int len)
{
	u8 buf[10] = {0};
	buf[0] = 0xfe;
	buf[1] = 0x15;
	memcpy(buf+2,param,len);
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, len +2);
}
/****************send To App*****************/
void CFlyJniSdkModuleAudioVideo::sendToAppCurVolumeValue(u8 *param,int len)
{
	LOGD("[%s] max:%x   value:%x", __FUNCTION__,param[0],param[2]);
	u8 szMsg[16] = {0x00};
	szMsg[0] = 0x00;
	szMsg[1] = 0x01;
	szMsg[2] = 0x00;
	if(len > 13)
		len =13;
	memcpy(szMsg+3,param,len);
	sendToFlyJniSdkService(MODULE_SDK_AUDIOVIDEO, szMsg, len+3);
}

void CFlyJniSdkModuleAudioVideo::sendToAudioRequestFocus(u8 param)
{
	u8 buf[] = {0x01, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 2);
}

void CFlyJniSdkModuleAudioVideo::sendToAudioRequestMuteOrUnMute(u8 param)
{
	u8 buf[] = {0x02, param};
	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_AUDIOVIDEO, buf, 2);
}