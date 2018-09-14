#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"
#include "param.h"


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}


void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	LOGD("AirCondition_Module_analyseOtherModuleMessage()  _____sendModuleId =  %x", sendModuleId);
	switch(sendModuleId){
		case MODULE_ID_SYSTEM:
			moduleToAIRCONDITION_FromSystem_Message(param, len);
			break;
		case MODULE_ID_EXTCAR:
			moduleToAIRCONDITION_FromExtcar_Message(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToAIRCONDITION_FromExternalCtrl_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToAIRCONDITION_FromAutomate_Message(param, len);
		    break;
		case MODULE_ID_KEY:
			moduleToAIRCONDITION_FromKey_Message(param, len);
			break;
		case MODULE_ID_FLYJNISDK:
			//moduleToAIRCONDITION_FromJniSdk_Message(param,len);
			g_pClsAcJniSdk.getSdkToModuleAcMessage(param,len);
			break;
		default:break;
	}
}

