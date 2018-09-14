#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"

#include "appResponseFunction.h"

#include "appResponseCommand.h"




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

	LOGD("BLCD analyseAppMessage ctrlId:%x ctrlType:%x",ctrlId,ctrlType);
	switch(ctrlId){
		case CONTROLID_BLCD_MAIN_BACK://
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Blcd_Back_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_Blcd_Back_MouseDown();
			}
			break;
		case CONTROLID_MENU_BLCD ://
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_MENUBLCD_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_MENUBLCD_MouseDown();
			}
			break;
		case CONTROLID_BLCD_MAIN_PLAYPAUSE://
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_PLAYPAUSE_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_PLAYPAUSE_MouseDown();
			}
			break;
		case CONTROLID_BLCD_MAIN_STOP: //
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_STOP_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_STOP_MouseDown();
			}
			break;
		case CONTROLID_BLCD_MAIN_PREV://
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_PRE_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_PRE_MouseDown();
			}
			break;
		case CONTROLID_BLCD_MAIN_NEXT://
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_NEXT_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_NEXT_MouseDown();
			}
			break;
		case CONTROLID_BLCD_MAIN_DVD:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_MAINDVD_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_MAINDVD_MouseDown();
			}
			break;
		case CONTROLID_BLCD_MAIN_CDC_TV:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_MAINCDCTV_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_MAINCDCTV_MouseDown();
			}
			break;
		default:
			break;
	}
}
