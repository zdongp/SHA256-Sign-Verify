#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "param.h"
void moduleParameterInit(void){//参数初始化
	LOGD("ModuleParameterInit");
	pLocalParam->currenTrack=0;
	pLocalParam->totalTrack=0;
	pLocalParam->mediaPlayState=0;
	pLocalParam->mediaVoiceState = false;
	memset(pLocalParam->curSongName,0,128);
	memset(pLocalParam->curSongArtist,0,128);
	memset(pLocalParam->curSongAlbum,0,128);
	memset(pLocalParam->usbDeviceName,0,sizeof(pLocalParam->usbDeviceName));
}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& Media moduleParameterReInit");
}
int module_extendInterface(char *buffer, int len){
	LOGD("*****************media module_extendInterface:%x,%x",buffer[0],buffer[1]);
	char extenCmd = buffer[0];
	char extenParam = buffer[1];
	LOGD("********************AC module_extendInterface:%x %x",extenCmd,extenParam);
	switch(extenCmd)
	{
		case 0x2C: //ACC Off Or Reset Or Default
		break;
		case 0x2D: //ACC On
		{
			//Automate_getUSBState(1);
			memcpy(pLocalParam->usbDeviceName,"Media",5);
		}
		break;
		case 0xFD:
			memcpy(pLocalParam->usbDeviceName,"Media",5);
		break;
		default:break;
	}
	return 0;
}

void moduleParameterDeInit(void){	
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
	    case MEDIA_PLAY_STATUS:
	        *(u8*)param = (u8)pLocalParam->mediaPlayState;
			*paramLen = sizeof(u8);
	    break;
        case MEDIA_CUR_TRACK:
            *(u8*)param = (u8)pLocalParam->currenTrack;
			*paramLen = sizeof(u8);
        break;
		case MEDIA_USB1_STATUS:
			*(u8*)param = pLocalParam->usb1state;
			*paramLen = sizeof(u8);
		break;	
		default:break;
	}
}

