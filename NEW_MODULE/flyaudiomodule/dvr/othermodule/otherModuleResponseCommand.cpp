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
	LOGD("dvr analyseOtherModuleMessage  sendModuleId:%x  param[0]:%x  param[1]:%x",sendModuleId,param[0],param[1]);
	switch(sendModuleId){		
		case MODULE_ID_SYSTEM:
			moduleToDVR_FromSystem_Message(param, len);
		break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToDVR_FromAudiovideo_Message(param, len);
		break;
		case MODULE_ID_KEY:
			moduleToDVR_FromKey_Message(param, len);
		break;
		case MODULE_ID_BT:
			moduleToDVR_FromBT_Message(param, len);
		break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToDvr_FromExternalCtrl_Message(param, len);
		break;
		case MODULE_ID_AUTOMATE:
		    moduleToDvr_FromAutomate(param,len);
		break;
		case MODULE_ID_CENTER:
		    moduleToDvr_FromCenter(param,len);
		break;
		default:break;
	}
}



