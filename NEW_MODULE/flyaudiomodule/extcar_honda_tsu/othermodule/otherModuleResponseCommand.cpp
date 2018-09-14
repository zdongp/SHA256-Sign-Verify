#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}


void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	switch(sendModuleId)
	{
		case MODULE_ID_FLYJNISDK:
	    	g_clsExtcarHondaTsu.analyseFromFlyJniSdkMessage(param, len);
	    break;
	}
}

