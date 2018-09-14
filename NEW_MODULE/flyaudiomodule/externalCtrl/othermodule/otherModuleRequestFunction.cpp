#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "pageID.h"

void externalctrlToModule_NotifySystem_SwitchModule(void)
{
	unsigned char buff[] =  {0x81,MODULE_ID_MEDIA};
	makeAndSendMessageToModule(MODULE_ID_MEDIA,MODULE_ID_SYSTEM,buff,2);
}

void externalctrlToModule_NotifySystem_jumpPage(u16 pageId){
	u8 buf[] = {0x82, 0x00, 0x00};
	
	memcpy(&buf[1], &pageId, 2);
	
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_SYSTEM, buf, 3);
}

void externalctrlToModule_NotifySystem_jumpPrePage(void){
	u8 buf[] = {0x83, 0x00};
	
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_SYSTEM, buf, 2);
}


void ExternalCtrlToAudiovideo_SetVol(u8 *cmd,u8 len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x00;
	memcpy(&pBuf[1],cmd,len);
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_AUDIOVIDEO,pBuf,len+1);
}

void ExternalCtrlToAudiovideo_aboutSpeechState(u8 cmd)
{
	u8 pBuf[2] = {0x01,cmd};
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_AUDIOVIDEO,pBuf,2);
}

void ExternalCtrlToAudiovideo_aboutSpeechApp_MediaState(u8 cmd)
{
	u8 pBuf[2] = {0x02,cmd};
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_AUDIOVIDEO,pBuf,2);
}

void ExternalCtrlToRadio_SetRadio(u8 *cmd,u8 len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x00;
	memcpy(&pBuf[1],cmd,len);
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_RADIO,pBuf,len+1);
}

void ExternalCtrlToOtherModule_SetPlayState(u8 cmd)
{
		short cur_Sound = 0;
		unsigned char soundLen=2;
		getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&cur_Sound,(u8 *)&soundLen);
		unsigned char To_Module = 0x00;
        unsigned char cur_SoundMode = cur_Sound;
		LOGD("ExternalCtrlToOtherModule_SoundHandle_SetPlay---cur_SoundMode:%x ",cur_SoundMode);
		
        switch(cur_SoundMode){
        	case 0x00://DVD ctrl
        	case 0x01://DVD video
            	To_Module = MODULE_ID_DVD;
            	break;
        	case 0x05://AUX ctrl
        	case 0x06://aux video
            	To_Module = MODULE_ID_AUX;
            	break;
        	case 0x07: //IPOD ctrl
        	case 0x08://ipod video
            	To_Module = MODULE_ID_IPOD;
            	break;
        	case 0x09://TV ctrl
        	case 0x0A://tv video
          		To_Module = MODULE_ID_TV;
            	break;
        	case 0x0B: //MEDIA
				To_Module = MODULE_ID_MEDIA;
            	break;
        	default:break;
        	}


	LOGD("ExternalCtrlToOtherModule_SoundHandle_SetPlay111111:To_Module:%x, cmd:%x", To_Module, cmd);
    u8 buff[2]={0x00,cmd};
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,To_Module,buff,2);

}

void ExternalCtrlToSysModule_MicUsingState(u8 param)
{
	u8 pBuf[] = {0x00,0x00};
	pBuf[1] = param;
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_SYSTEM,pBuf,sizeof(pBuf));
}


void ExternalCtrlToKeyModule(u8 *param,u8 len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x00;
	memcpy(&pBuf[1],param,len);
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_KEY,pBuf,len+1);
}


void ExternalCtrl_FlyauidioApp_Management(u8 *param,u8 len)
{
	u16 CurPageID = 0;
	u8  CurPageIDLen = 0;
	getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&CurPageID,&CurPageIDLen);

	if(param[0]==0x16){
		u8 buffer[]={0,0};
		buffer[0]=0x16;
		buffer[1]=param[1];
		makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_OSD,buffer,2);
	}

	u8 ucBackMode = 0;
	u8 ucBackModeLen = 0;
	getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,&ucBackModeLen);
	LOGD("externalctrl_FlyaudioApp ucBackMode:%x CurPageID:%x",ucBackMode,CurPageID);
	if(ucBackMode == 1 || CurPageID == PAGE_BLACK || CurPageID == PAGE_BACK_NOVIDEO || CurPageID == PAGE_BACK_VIDEO || CurPageID == PAGE_BACK_RADAR || CurPageID == PAGE_BACK_FULL_VIDEO || CurPageID == PAGE_BACK_FULL_VIDEO_CONTROL)
	{
		return;
	}
	
	u8 To_Module = 0x00;
	u8 cmd = 0x00;
	switch(param[0])
	{
		case 0x00:
			To_Module = MODULE_ID_GPS;
		 	break;
       	case 0x01:
       		To_Module = MODULE_ID_DVD;
            break;
        case 0x02:
        	To_Module = MODULE_ID_RADIO;
        	break;
        case 0x03:
        	To_Module = MODULE_ID_MEDIA;
        	break;
        case 0x04:
        	To_Module = MODULE_ID_BT;
        	break;
        case 0x05:
        	To_Module = MODULE_ID_SYNC;
            break;
        case 0x06:
        	To_Module = MODULE_ID_DVR;
            break;
        case 0x07:
        	To_Module = MODULE_ID_TV;
            break;
        case 0x08:
        	To_Module = MODULE_ID_TPMS;
            break;
        case 0x09:
        	To_Module = MODULE_ID_BT;
        	cmd = 0x01;
            break;
        case 0x10:
        	To_Module = MODULE_ID_SYSTEM;
            break;
        case 0x11:
        	To_Module = MODULE_ID_BLCD;
            break;
        case 0x12:
        	To_Module = MODULE_ID_AUX;
            break;
        case 0x13:
            break;
        case 0x14:
            To_Module = MODULE_ID_AC;
            break;
        case 0x15:
            To_Module = MODULE_ID_EXTCAR;
            break;
        case 0x16:
            break;
		default:break;
	}

	u8 buff[]={0x01,0x00,0x00};
	buff[1]=param[1];
	buff[2]= cmd;
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,To_Module,buff,3);
}

void ExternalCtrlToAC_Message(u8 *param,u8 len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x00;
	memcpy(&pBuf[1],param,len);
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_AC,pBuf,len+1);

}

void ExternalCtrlToBt_Message(u8 *param,u8 len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x02;
	memcpy(&pBuf[1],param,len);
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_BT,pBuf,len+1);
}

void ExternalCtrlToSystem_Message(u8 *param,u8 len)
{
	u8 pBuf[len+1];
	memset(pBuf,0,sizeof(pBuf));
	pBuf[0]=0x02;
	memcpy(&pBuf[1],param,len);
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_SYSTEM,pBuf,len+1);
}

void ExternalCtrlToSystem_about_JumpPageMessage(u8 *param,u8 len)
{
    if(param[0] == 0x82)
    {
        u8 buf[]={0x82,0x00,0x00};
        u16 TempPageId=0;
        TempPageId += (u16)((param[1] << 8)  & 0xFF00);
	    TempPageId += (u16)(param[2] & 0xFF);
        memcpy(&buf[1],&TempPageId,2);
        LOGD("TempPageId:%x",TempPageId);
        makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_SYSTEM,buf,3);
    }
    else if(param[0] == 0x83)
    {
        makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_SYSTEM,param,len);
    }
	
}

void ExternalCtrlToAudiovideo_SetChannel(u8 cmd)
{
	u8 buff[3]={0x00,0x06,0x00};
	buff[2] = cmd;
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_AUDIOVIDEO,buff,3);
}

void ExternalCtrlToAudiovideo_EndSpeechToThelastAudioChannel(u8 cmd)
{
	u8 buff[]={0x03,0x00};
	buff[1] = cmd;
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_AUDIOVIDEO,buff,2);
}

void ExternalCtrlToAudiovideo_aboutSpeechState_New(u8 cmd)
{
	u8 pBuf[2] = {0x04,cmd};
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL, MODULE_ID_AUDIOVIDEO,pBuf,2);
}

void externalctrlToMediaModule_VoiceStatus(u8 ToMode,u8 param)
{
	u8 buf[3] = {0xFF,param};
	makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,ToMode,buf,2);
}

