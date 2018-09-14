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
	
	if (ctrlType == 0xFE && ctrlId == CONTROLID_MEDIA_DEDICATE_INFORMATION)
	{
		analyseAppDataInfo(param,paramLen);
		return;	
	}

	LOGD("Media analyseAppMessage:ctrlId=0x%x,ctrlType=0x%x",ctrlId,ctrlType);
	switch(ctrlId){
		case CONTROLID_MENU_MEDIA:
		case CONTROLID_MENU_JUMP_MEDIA_PAGE:
			appToMedia_MenuMedia_MouseUp();
			break;
		case CONTROLID_MEDIA_MAIN_BACK:
			if(ctrlType == UIACTION_MOUSEUP){
				appToMedia_MainBack_MouseUp();
			}
			break;
		case CONTROLID_MEDIA_MAIN_SONGSTORE:
			break;
		default:break;
	}
}
void analyseAppDataInfo(u8* param,int len)
{
	//LOGD("[%s] param[0] = [0x%x]", __FUNCTION__, param[0]);

	switch(param[0])
	{
		case 0x01:
			appToMedia_GetMediaPlayState(param[1]);
			break;
		case 0x02:
			appToMedia_GetMediaPlayAndTotalTime(&param[1],len);
			break;
		case 0x03:
			appToMedia_GetMediaPlaySongName(&param[1],len - 1);
			break;
		case 0x04:
			appToMedia_GetMediaPlaySongtrack(&param[1],len);
			break;
		case 0x05:
			appToMedia_GetMediaPlaySongArtist(&param[1],len - 1);
			break;
		case 0x06:
			appToMedia_GetMediaPlaySongAlbum(&param[1],len - 1);
			break;
		case 0x10:
			appToMedia_GetMediaUsbState(&param[1],len - 1);
			break;
		case 0x11:
			appToMedia_GetUSBDeviceName(&param[1],len - 1);
			break;
		default:break;
	}
}


