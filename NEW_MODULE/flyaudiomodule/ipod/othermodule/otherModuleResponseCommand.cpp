#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}


void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	switch(sendModuleId){
		case MODULE_ID_AUDIOVIDEO:
			moduleToIpod_FromAudiovideo_Message(param, len);
			break;
		case MODULE_ID_KEY:
			moduleToIpod_FromKey_Message(param, len);
			break;
		case MODULE_ID_SYSTEM:
			moduleToIpod_FromSystem_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToIpod_FromAutomate(param,len);
		    break;
		default:break;
	}
}

