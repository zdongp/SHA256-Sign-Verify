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

	LOGD("GPS analyseAppMessage ctrlId:%x ctrlType:%x paramLen:%d",ctrlId,ctrlType,paramLen);
	if(ctrlId == CONTROLID_NAVI_DEDICATE_INFORMATION && ctrlType == 0xFE)
	{
		appToGPS_Navi_DedicateInformation(param,paramLen);
	}
	else if(ctrlId == CONTROLID_NAVI_GAODE_MAP_INFORMATION && ctrlType == 0xFE)
	{
		appToGPS_Navi_GaodeMap_Information(param,paramLen);
	}
	
	switch(ctrlId){
  		case CONTROLID_MENU_NAVI:
  			if(ctrlType == UIACTION_MOUSEUP)
    			appToGPS_MenuGPS_MouseUp();
    			break;
		default:break;
	}
}
