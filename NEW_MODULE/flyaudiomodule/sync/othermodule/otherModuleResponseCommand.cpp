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
	LOGD("Module_sync analyseOtherModuleMessage sendModuleId:%x param[0] param[1] param[2]:%x %x %x",sendModuleId,param[0], param[1],param[2]);
	switch(sendModuleId){
		case MODULE_ID_SYSTEM:
			moduleToSYNC_FromSystem_Message(param, len);
		case MODULE_ID_EXTCAR:
			moduleToSYNC_FromEXTCAR_Message(param,len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToSYNC_FromAudiovideo_Message(param,len);
			break;
		case MODULE_ID_KEY:
			moduleToSYNC_FromKey_Message(param,len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToSYNC_FromExternalCtrl_Message(param,len);
			break;
		case MODULE_ID_CENTER:
			moduleToSYNC_FromCenter_Message(param,len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToSync_FromAutomate(param,len);
		    break;
		default:break;
	}
}

