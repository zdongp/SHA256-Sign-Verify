#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "param.h"

#include "voiceLogic.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestFunction.h"


void getVoiceStatus(u8 *param,int len)
{
	switch(param[0])
	{
		case 0x00://speech status
		{
				if(param[1] == 0x00){//speech play
					ExternalCtrlToAudiovideo_aboutSpeechState(0x01);
				}
				else if(param[1] == 0x01){//speech Recognition
					ExternalCtrlToAudiovideo_aboutSpeechState(0x02);
				}
				else if(param[1] == 0x02){//speech end
					ExternalCtrlToAudiovideo_aboutSpeechState(0x00);
				}
		}
		break;
		case 0x01://speech-app media paly status
		{
			if(param[1] == 0x01)
				pLocalParam->bIsAutoJumpPrePage = false;
			ExternalCtrlToAudiovideo_aboutSpeechApp_MediaState(param[1]);
		}
		break;
		case 0x02:
		break;
		case 0x03:
			analyseVoiceStatus(param+1,len -1);
		break;
		default:break;
	}
}

void analyseVoiceStatus(u8 *p,int len)
{
	LOGD("[%s] voice status:%x",__FUNCTION__,p[0]);
	u8 ucBackMode = 0;
	int ucBackModeLen = 0;
	getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&ucBackModeLen);
	if(ucBackMode == 0x01)
		return;
	pLocalParam->uCurSpeechState = p[0];
	switch(p[0])
	{
		case 0x00://out
		{
			getVoiceForQuitStatus();
		}
		break;
		case 0x01:
		{
			getVoiceForStartStatus();
		}
		break;
		default:break;
	}
	 quitVoiceCtrlMediaPlay(p[0]);
}

void getVoiceForStartStatus()
{
	ExternalCtrlToSysModule_MicUsingState(0x01);
	 ExternalCtrlToAudiovideo_aboutSpeechState_New(0x01);
}

void getVoiceForQuitStatus()
{
	ExternalCtrlToSysModule_MicUsingState(0x00);
	ExternalCtrlToAudiovideo_aboutSpeechState_New(0x00);
}

void quitVoiceCtrlMediaPlay(u8 param)
{
	unsigned short icurSound = 0;
	u8 icurSoundLen = 0;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&icurSound,&icurSoundLen);
	u8 ToModeID = 0;
    	switch(icurSound)
	{
	    	case CHANNEL_DVD_CTRL://DVD ctrl
	    	case CHANNEL_DVD_VIDEO://DVD video
	        	ToModeID = MODULE_ID_DVD;
	        	break;
	    	case CHANNEL_RADIO: //RADIO
	        	ToModeID = MODULE_ID_RADIO;
	        	break;
	    	case CHANNEL_AUX_CTRL://AUX ctrl
	    	case CHANNEL_AUX_VIDEO://aux video
	        	ToModeID = MODULE_ID_AUX;
	        	break;
	    	case CHANNEL_IPOD_CTRL: //IPOD ctrl
	    	case CHANNEL_IPOD_VIDEO://ipod video
	        	ToModeID = MODULE_ID_IPOD;
	        	break;
	    	case CHANNEL_TV_CTRL://TV ctrl
	    	case CHANNEL_TV_VIDEO://tv video
	      		ToModeID = MODULE_ID_TV;
	        	break;
	    	case CHANNEL_MP3: //MEDIA
				ToModeID = MODULE_ID_MEDIA;
        	break;
		case CHANNEL_BT:
			ToModeID = MODULE_ID_BT;
			break;
		case CHANNEL_DVR_CTRL:
		case CHANNEL_DVR_VIDEO:
			ToModeID = MODULE_ID_DVR;
			break;
    	default:break;
	}
	LOGD("[%s] ModuleID:%x",__FUNCTION__,ToModeID);
	if(ToModeID != 0)
	{
		externalctrlToMediaModule_VoiceStatus(ToModeID,param);
	}
}


