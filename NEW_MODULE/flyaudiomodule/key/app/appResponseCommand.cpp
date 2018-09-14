#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"

#include "appResponseCommand.h"
#include "halResponseFunction.h"
#include "otherModuleRequestFunction.h"


void appInit(void){

}

void appDeInit(void){

}

void analyseAppToKeyDedicate_information(u8 *param,int len)
{
	LOGD("***key***%x %x******",param[0],param[1]);
	switch(param[0])
	{
		case 0x01:
		{
			if(param[1]==0x00)
			halToKey_analyseKeyValue(HALTOKEY_KEYVAL_AV);
		}
		break;
		case 0x02:
		{
			if(param[1]==0x00)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_SEEK_INC);
			else if(param[1]==0x01)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_SEEK_DEC);
		}
		break;
		case 0x03:
		{
			if(param[1]==0x00)
			halToKey_analyseKeyValue(HALTOKEY_KEYVAL_NAVI);
		}
		break;
		case 0x04:
		{
			if(param[1]==0x00)
			halToKey_analyseKeyValue(HALTOKEY_KEYVAL_DEST);
		}
		break;
		case 0x05:
		{
			if(param[1]==0x00)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_VOL_INC);
			else if(param[1]==0x01)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_VOL_DEC);
			else if(param[1]==0x02)
				halToKey_analyseKeyValue(HALTOKEY_KEYVAL_MUTE);
		}
		break;
		case 0x06:
			keyToSystemModule_About_SmartFan_Telecontrol(param[1]);
		break;
		case 0x07:
			keyToSystemModule_About_LCD_Telecontrol(param[1]);
		break;
		case 0x08:
		    keyToSystemModule_About_FanMode_PerformanceSwitch(param[1]);
		break;
		case 0x09:
		    keyToSystemModule_About_AntotoItsOpen(param[1]);
		break;
		default:break;
	}
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

	LOGD("Key analyseAppMessage:ctrlId=0x%x,ctrlType=0x%x",ctrlId,ctrlType);
	if (ctrlType == 0xFE && ctrlId == CONTROLID_KEY_DEDICATE_INFORMATION)
	{
		analyseAppToKeyDedicate_information(param,len);
	}

	switch(ctrlId){
		default:break;
	}
	
}
