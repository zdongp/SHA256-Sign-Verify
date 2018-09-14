#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"
#include "moduleParamStruct.h"

void otherModuleInit(void){

}

void otherModuleDeInit(void){

}

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	switch(sendModuleId){
		case MODULE_ID_SYSTEM:
			moduleToTV_FromSystem_Message(param, len);
			break;
		case MODULE_ID_KEY:
			moduleToTV_FromKey_Message(param, len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToTV_FromAudiovideo_Message(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToTV_FromExternalCtrl_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToTv_FromAutomate(param,len);
		    break;
		default:break;
	}
}

