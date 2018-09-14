#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"

#include "appResponseCommand.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"

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
	
	LOGD("Module_center analyseAppMessage ctrlType %x ctrlId %x",ctrlType,ctrlId);
	switch(ctrlId){
		case 0x00000000:
			if(ctrlType == (char)UIACTION_PARAMETER){
				appToCenter_Parameter(param, paramLen);
			}			
			else if(ctrlType == (char)UIACTION_MOUSEUP)
			{
				LOGD("SetThirdChannel param[0]:%d",param[0]);
				if(param[0] == 0x4a){
					//centerToModule_NotifyAudiovideo_SetThirdChannel();
				}
			}
			break;
		case 0x00000001:
			if(ctrlType == (char)UIACTION_MOUSEUP){
				centerToModule_NotifySystem_BrightnessBlackPageClick();
			}
			break;
		default:break;
	}
}
