#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"

#include "moduleParamResponse.h"
#include "timer_interface.h"



void moduleParameterInit(void){
	pLocalParam->n_DispatchBySoundMode = true;
	pLocalParam->u_bSync_BTCall = false;
	pLocalParam->bKeyAction_DropDownOSD = false;
	//initTimerCenter(&TimerHandlerCenter);
}

void moduleParameterDeInit(void){
	pLocalParam->n_DispatchBySoundMode = true;
	pLocalParam->u_bSync_BTCall = false;
	pLocalParam->bKeyAction_DropDownOSD = false;
}

void getMyModuleParam(char paramId, unsigned char *param, unsigned char *paramLen){
	switch(paramId){
	    case KEYACTION_DROPDOWNOSD:
	        *param = (u8)pLocalParam->bKeyAction_DropDownOSD;
	        *paramLen = 1;
	    break;
		default:break;
	}
}

void moduleParameterReInit(void){
	LOGD("&&&&&&&&&&&&&&&&&&&& Ipod moduleParameterReInit");
	moduleParameterInit();
}

int module_extendInterface(char *buffer, int len){
	LOGV("******************key module_extendInterface:%x,%x",buffer[0],buffer[1]);
	return 1;
}


