#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"

#include "param.h"
#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "appRequestFunction.h"
#include "otherModuleResponseFunction.h"



void appInit(void){

}

void appDeInit(void){

}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);

	ctrlType = buffer[4];
	paramLen = len - 5;
	param = &buffer[5];
	
	LOGD("[%s] ctrlType %x ctrlId %x paramLen:%x",__FUNCTION__,ctrlType,ctrlId,paramLen);
	
	switch(ctrlId)
	{
			case CONTROLID_EXTERNALCTRL_VOICE_INFORMATION:
				if(ctrlType == 0xFE){
					analyseSpeechCtrlCmdToFlyaudio(param,paramLen-1);
				}
				break;
			case CONTROLID_EXTERNALCTRL_VOICE_LANUCHER_BUTTON:
				if(ctrlType == 0x10)
				{
					ExternalctrlModule_IsJumpPrePage();
					externalctrlToModule_NotifySystem_jumpPage(PAGE_SPEECH_APP_MEDIA);
					externalCtrlToSpeechApp_RequestCtrlCmd(0x01);
				}
				break;
			case CONTROLID_EXTERNALCTRL_REMOTE_INFORS:
				if(ctrlType == 0xFE){
					analyseRemoteAppInfors(param,paramLen-1);
				}
				break;
			default:break;
	}
}
