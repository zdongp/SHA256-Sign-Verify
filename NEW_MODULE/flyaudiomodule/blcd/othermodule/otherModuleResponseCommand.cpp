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
		case MODULE_ID_SYSTEM:
			moduleToBlcd_FromSystem_Message(param, len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToBlcd_FromAudiovideo_Message(param, len);
			break;
		case MODULE_ID_KEY:
			moduleToBlcd_FromKey_Message(param, len);
			break;
		case MODULE_ID_DVD:
			moduleToBlcd_FromDvd_Message(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToBlcd_FromExternalCtrl_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToBlcd_FromAutomate_Message(param, len);
		    break;
		default:break;
	}
}

void analyseTimerHandleMessage(u8 *p, u8 len)
{
}


