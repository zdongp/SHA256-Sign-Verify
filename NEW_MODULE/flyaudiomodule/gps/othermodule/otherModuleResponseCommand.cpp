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
	LOGD("sendModuleID:%x, param:%x %x", sendModuleId, param[0], param[1]);
	switch(sendModuleId){

		case MODULE_ID_KEY:
			moduleToGps_FromKey_Message(param, len);
			break;
		case MODULE_ID_SYSTEM:
			moduleToGps_FromSystem_Message(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToGps_FromExternalCtrl_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToGps_FromAutomate(param,len);
		    break;
		default:break;
	}
}


