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
			moduleToTPMS_FromSystem_Message(param, len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			//moduleToTPMS_FromAudiovideo_Message(param, len);
			break;
		case MODULE_ID_KEY:
			//moduleToTPMS_FromKey_Message(param, len);
			break;
		case MODULE_ID_BLCD:
			//moduleToDvd_FromBlcd_Message(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToTPMS_FromExternalCtrl_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		        moduleToTpms_FromAutomate(param,len);
		        break;
		case MODULE_ID_EXTCAR:
			moduleToTpms_FromExtcar(param, len);
			break;
		default:break;
	}
}

