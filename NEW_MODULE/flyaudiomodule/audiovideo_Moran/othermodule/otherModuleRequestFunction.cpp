#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"
#include "halRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleID.h"
#include "moduleParamRequest.h"
#include "appRequestFunction.h"
#include "moduleParamResponse.h"
#include "timer_interface.h"
#include <android/log.h>
#include <commonFunc.h>
#include <ctype.h>
#include <string.h>


//��ָ��ҳ
void audioVideoToModule_NotifySystem_JumpPage(u16 nPageId){
     u8 buf[] = {0x82,0x00,0x00};
     memcpy(&buf[1],&nPageId,2);
	 LOGD("audioVideoToModule_NotifySystem_JumpPage:%x",nPageId);
     makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_SYSTEM,buf,3);
}
//��ǰһҳ
void audioVideoToModule_NotifySystem_JumpPrePage(void){
     u8 buf[] = {0x83,0x00};
     makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_SYSTEM,buf,3);
}

void audioVideoToHal_NotifyAux_EnterAux(void){
	unsigned char buff[] = {0x80, 0x00};

	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_AUX, buff, 2);
}

void audioVideoToModule_NotifyAuxscreen_SetVolume(unsigned char volume){
	unsigned char buff[] = {0x80, volume};

	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_AUXSCREEN, buff, 2);
}

void audioVideoToModule_NotifyOtherModule_SetNoticeMode(unsigned char toModule, int newSoundVideoChannel){
	u8 buff[2] = {0x00,(char)newSoundVideoChannel};
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, toModule, buff, 2);
}

void audioVideoToModule_NotifyMediaModule_IsNormalToMediaChannel(u8 p){
	u8 buff[2] = {0x01,(char)p};
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_MEDIA, buff, 2);
}

void audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(int oldSoundVideoChannel,int curSoundVideoChannel){

	switch(oldSoundVideoChannel)//Ҫ֪ͨ��ģ��
    {
    case CHANNEL_DVD_CTRL://dvd ctrl
	case CHANNEL_DVD_VIDEO://dvd video
        audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_DVD,curSoundVideoChannel);
        break;
    case CHANNEL_CDC_CTRL://cdc ctrl
	case CHANNEL_CDC_VIDEO://CDC video
        break;
    case CHANNEL_RADIO://radio
        audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_RADIO,curSoundVideoChannel);
        break;
    case CHANNEL_AUX_CTRL://aux ctrl
	case CHANNEL_AUX_VIDEO://aux video
	{
		u8 n_IsAux = 0;
		u8 n_IsAuxLen = 0;
		getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
		if(n_IsAux == 1){
        	audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_AUX,curSoundVideoChannel);
        }
        else{
        	audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_SYNC,curSoundVideoChannel);
        }

    }
    break;
    case CHANNEL_IPOD_CTRL://ipod
	case CHANNEL_IPOD_VIDEO:
        audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_IPOD,curSoundVideoChannel);
        break;
    case CHANNEL_TV_CTRL://tv
	case CHANNEL_TV_VIDEO:
        audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_TV,curSoundVideoChannel);
        break;
    case CHANNEL_MP3://media
        audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_MEDIA,curSoundVideoChannel);
        break;
	case CHANNEL_BT:
		audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_BT,curSoundVideoChannel);
		break;
	case CHANNEL_DVR_CTRL:
	case CHANNEL_DVR_VIDEO:
		audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_DVR,curSoundVideoChannel);
		break;
	case CHANNEL_DNV_CTRL:
	case CHANNEL_DNV_VIDEO:
		audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_DNV,curSoundVideoChannel);
		break;
    default://
        break;
    }
	audioVideoToModule_NotifyOSD_SendOsdDebugInfo();
}



void audioVideoToModule_NotifySystem_FirstEnterSoundMode(void ){
	u16 targetPageID = 0;
	LOGD("first enter--pLocalParam->savemode:%x",pLocalParam->savemode);

	u16 curPageId = 0;
	u8 curpageLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curPageId,&curpageLen);
	LOGD("[%s] curpageID=%x",__FUNCTION__,curPageId);
	
	char property[PROPERTY_VALUE_MAX];
    bool bTemState = false;
	property_get("fly.boot.jump.whichpage",property,"0");
	sscanf(property,"%hhd",&bTemState);
	LOGD("first enter--bTemState:%d",bTemState);
	if(bTemState)
	{
		//if(curPageId == PAGE_THIRD_PAGE || curPageId == 0xFFFC)
		//{
		//	return;
		//}
		
	    targetPageID = PAGE_MENU;
	    audioVideoToModule_NotifySystem_JumpPage(targetPageID);
	    return;
	}
	
	switch(pLocalParam->savemode){
		case CHANNEL_DVD_CTRL:
		case CHANNEL_DVD_VIDEO:
			targetPageID = PAGE_DVD_MAIN;
			break;

		//case CHANNEL_CDC_CTRL:
		//	targetPageID = PAGE_CDC;
		//	break;

		//case CHANNEL_CDC_VIDEO://CDC video
		//	targetPageID = PAGE_OSD_CDC_BG;
		//	break;
		case CHANNEL_RADIO://RADIO
			targetPageID = PAGE_RADIO_MAIN;
			break;

		case CHANNEL_AUX_CTRL://AUX ctrl
		case CHANNEL_AUX_VIDEO://Aux video
			{
				u8 n_IsAux = 0;
				u8 n_IsAuxLen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
				if(n_IsAux == 1){
					targetPageID = PAGE_MENU;/*��������������Ƶ*/
				}
				else{
					targetPageID = PAGE_SYNV_MENU;
				}
			}
			break;

		case CHANNEL_IPOD_CTRL://ipod ctrl
		case CHANNEL_IPOD_VIDEO://ipod video
			targetPageID = PAGE_IPOD;
			break;
		case CHANNEL_TV_CTRL://TV ctrl
		case CHANNEL_TV_VIDEO://TV video
		{
			targetPageID = PAGE_MENU;//��������������Ƶ
		}
			break;
		case CHANNEL_MP3://MEDIA
			targetPageID = PAGE_MEDIA;
			break;
	    case CHANNEL_BT://a2dp
	    {
            u8 u8_A2DP_State = 0;
		    u8 u8_A2DP_StateLen = 0;
		    getOtherModuleParam(MODULE_ID_BT,BT_A2DP_SUPPORT,(u8*)&u8_A2DP_State,&u8_A2DP_StateLen);//edit by chenbohong 0407
		    LOGD("u8_A2DP_State:%d",u8_A2DP_State);
	    	if(u8_A2DP_State == 1)
	    	{
	    	    targetPageID = PAGE_BLUETOOTH_A2DP;
	    	}
	    	else
	    	{
	    	    targetPageID = PAGE_BLUETOOTH_NO_A2DP;
	    	}
	    }
			break;
		case CHANNEL_THREECHANNEL:
			targetPageID = PAGE_MENU;
			break;
		case CHANNEL_DVR_VIDEO:
		case CHANNEL_DVR_CTRL:
			targetPageID = PAGE_MENU;
			break;
		case 0x80://RGB  ������
			break;
		default://Main Menu  unkown sound chnnel
			if(!GetPageByChannel(&targetPageID,pLocalParam->savemode))
				targetPageID = PAGE_MENU;
			break;
	}
	if(0 != targetPageID){
		if(PAGE_MATCHING_MODELS == curPageId || PAGE_BLACK == curPageId){
			return ;
		}

		if(targetPageID == PAGE_MENU)
		{
			if(curPageId == PAGE_THIRD_PAGE  || curPageId == 0xFFFC)
			{
				return;
			}
		}
		
		audioVideoToModule_NotifySystem_JumpPage(targetPageID);
	}
}



void audioVideoToModule_NotifyOsd_DisplayOSDVolume(unsigned char vol){
	u8 buf[] = {0x10, vol};
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_OSD,buf,2);
}

void audioVideoToModule_NotifyOsdModule_ViewSwitch(unsigned char param){
//	u8 buf[] = {0x03,param};
//
//	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_OSD,buf,2);
}

void audioVideoToModule_NotifyOsdModule_OSDPage(unsigned char param){
//	u8 buf[] = {0x04,param};
//
//	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_OSD,buf,2);
}

void audioVideoToModule_NotifyOSD_ShowVolumeOsd(void){
	u8 buf[] = {0x01, 0x10};
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_OSD, buf, 2);
}

void audioVideoToModule_NotifyDvd_SetOsdVideSetting(unsigned char type, unsigned char value){
	u8 buf[] = {0x11, type, value};
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_DVD, buf, 3);
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_TV, buf, 3);
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_AUX, buf, 3);
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO, MODULE_ID_BACK, buf, 3);
}
void audioVideoToModule_NotifyOSD_SendOsdDebugInfo(void)
{
	u8 buf[256]={0};
	u8 buf1[256]={0};
	buf[0]=0x02;
	buf1[0]=0x03;
	char strSound[128]={0};
	char strSound1[128]={0};
	sprintf(strSound,"oldsound:%d ,sound:%d ,soundcard:%d ,EnableMixVoiceState:%d",
		pLocalParam->oldsoundVideoChannel,pLocalParam->soundVideoChannel,pLocalParam->soundcardSoundState,pLocalParam->uEnableMixVoiceState);
	sprintf(strSound1,"MediaPlaying:%d ,IsRequestvoice:%d ,gpsSoundState:%d",
		pLocalParam->b_MediaPlaying,pLocalParam->b_IsRequestvoice_state,pLocalParam->gpsSoundState);
	memcpy(&buf[1],strSound,strlen(strSound));
	memcpy(&buf1[1],strSound1,strlen(strSound1));
	u8 len=strlen(strSound)+2;
	u8 len1=strlen(strSound1)+2;
	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_SYSTEM, buf,len);
	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_SYSTEM, buf1,len1);
}

void setTimerCloseVideo(void)
{
	SetTimer(TIMER_CYCLE_DELAY_CLOSE_VIDEO, 1, TIMER_ID_DELAY_CLOSE_VIDEO);

	LOGD("[%s]", __FUNCTION__);
}

void audioVideoToModule_NotifySystem_StartGPS(void){
     u8 buf[] = {0x00,0x01};
     makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_SYSTEM,buf,2);
}

void audioVideoToModule_NotifyRadio_Init(u8 p)
{
	u8 buf[2] = {0x02,0x00};
	buf[1] = p;
   	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_RADIO,buf,2);
}

void NotifySystem_StartGPS(u8 p)
{
   	u8 buf[2] = {0x01,0x00};
	buf[1] = p;
   	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_SYSTEM,buf,2);
}

void audioVideoToModule_NotifyExternalctrl_EndTheVoice()
{
	u8 buf[] = {0x00, 0x00};
	makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_EXTERNALCTRL,buf,2);
}

void audioVideoToModule_NotifySystem_JumpToCurMediaPage()
{
	u16 targetPageID = PAGE_RADIO_MAIN;
	switch(pLocalParam->lastMediaChannel)
	{
		case CHANNEL_RADIO:
			targetPageID = PAGE_RADIO_MAIN;
		break;
		case CHANNEL_MP3://MEDIA
			targetPageID = PAGE_MEDIA;
		break;
		case CHANNEL_BT://a2dp
		{
			u8 u8_A2DP_State = 0;
			u8 u8_A2DP_StateLen = 0;
			getOtherModuleParam(MODULE_ID_BT,BT_A2DP_SUPPORT,(u8*)&u8_A2DP_State,&u8_A2DP_StateLen);
			if(u8_A2DP_State == 1)
			{
				targetPageID = PAGE_BLUETOOTH_A2DP;
			}
			else
			{
				targetPageID = PAGE_BLUETOOTH_NO_A2DP;
			}	
		}
		break;
		default:break;
	}
	audioVideoToModule_NotifySystem_JumpPage(targetPageID);
}
