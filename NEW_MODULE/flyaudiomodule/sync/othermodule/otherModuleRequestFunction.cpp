#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "paramID.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "param.h"


void syncToModule_NotifySystem_JumpPage(u16 pageId)
{
	u8 buf[] = {0x82, 0x00, 0x00};
	memcpy(&buf[1], &pageId, 2);
	makeAndSendMessageToModule(MODULE_ID_SYNC, MODULE_ID_SYSTEM, buf, 3);

}

void syncToModule_NotifySystem_jumpPrePage(void){
	u8 buf[] = {0x83, 0x00};
	makeAndSendMessageToModule(MODULE_ID_SYNC, MODULE_ID_SYSTEM, buf, 2);
}

void syncToModule_NotifyOtherModule_BtCallState(unsigned char toModule, int state){
	u8 buff[] = {0x00,(char)state};
	makeAndSendMessageToModule(MODULE_ID_SYNC, toModule, buff, 2);
}

void Set_Sound_PreChannel(){
	u8 iOldSound = 0;
	u8 iOldSoundLen = 0;
	getOtherModuleParam(MODULE_ID_AUDIOVIDEO,OLD_SOUND_CHANNEL,&iOldSound,&iOldSoundLen);
	u8 buff[] = {0x00, iOldSound};
	makeAndSendMessageToModule(MODULE_ID_SYNC, MODULE_ID_AUDIOVIDEO, buff, 2);
}

void SendSYNCInfoToOSDDebug(void)
{
	u8 buf[256]={0};
	buf[0]=0x07;
	char strSound[128]={0};
	
	sprintf(strSound,"SYNC_Speech:%d,  SYNC_MediaState:%d,  SYNC_BtCallState:%d",
		pLocalParam->m_bSpeech_ButtonValue,pLocalParam->c_ByMediaState,pLocalParam->b_BtCallState);
	memcpy(&buf[1],strSound,strlen(strSound));
	u8 len=strlen(strSound)+2;
	makeAndSendMessageToModule(MODULE_ID_OSD, MODULE_ID_SYSTEM, buf,len);
}

void syncToModule_NotifyCenter_SyncState(u8 state)
{
	u8 param[]={0x00,state};
	makeAndSendMessageToModule(MODULE_ID_SYNC, MODULE_ID_CENTER, param,2);
}

