#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "moduleParamResponse.h"
#include "timer_interface.h"
#include "appRequestCommand.h"
#include "param.h"

void moduleParameterInit(void){
}

void moduleParameterDeInit(void){

}

void moduleParameterReInit(void){
}

int module_extendInterface(char *buffer, int len){
	LOGD("**********************GPS module_extendInterface:%x,%x",buffer[0],buffer[1]);
	u8 cmd = buffer[0];
	switch(cmd){
		case 0x2C:
			if(buffer[1]==0x00){//accoff
				setPanelKeyToAndroid(0xF8);
			}
			else if(buffer[1] == 0x01){//
			}
			else if(buffer[1] == 0x02){//
			}
			break;
		case 0x2D:
			if(buffer[1]==0x00){//accon
				setPanelKeyToAndroid(0xF9);
			}
			break;
		case 0xFD:
			pLocalParam->m_nLanguageId = -1;
			break;
		default:break;
	}
	
	return 0;
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
		case 0x00:
			{
				*(int*)param = pLocalParam->m_nLanguageId;
				*paramLen = 4;
			}
			break;
		default:break;
	}
}

