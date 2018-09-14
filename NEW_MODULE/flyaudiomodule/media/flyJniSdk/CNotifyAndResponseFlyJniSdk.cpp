
#include <stdio.h>
#include <stdlib.h>

#include "CNotifyAndResponseFlyJniSdk.h"
#include "otherModuleRequestCommand.h"
#include "moduleID.h"
#include "appRequestCommand.h"

CNotifyAndResponseFlyJniSdk:: CNotifyAndResponseFlyJniSdk(void)
{
}

CNotifyAndResponseFlyJniSdk:: ~CNotifyAndResponseFlyJniSdk(void)
{
}

void CNotifyAndResponseFlyJniSdk::sendToFlyJniSdkMusicSongName(unsigned char* songName,int len)
{
	LOGD(" [%s],songName:%s",__FUNCTION__ , songName);
	u8 buf[129] = {0};
	buf[0] = 0x00;
	memcpy(&buf[1],songName,len);
	makeAndSendMessageToModule(MODULE_ID_MEDIA,MODULE_ID_FLYJNISDK,buf,len+1);
}




