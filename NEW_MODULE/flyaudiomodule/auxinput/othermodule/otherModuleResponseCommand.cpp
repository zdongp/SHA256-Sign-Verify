#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}


void analyseOtherModuleMessage(unsigned char sendModuleId, unsigned char *param, unsigned char len){
	LOGD("<<<++analyseOtherModuleMessage++>>++sendModuleId===%x", sendModuleId);
	LOGD("<<<++analyseOtherModuleMessage++>>+param[0]=%x+param[1]=%x", param[0], param[1]);
	switch(sendModuleId){
		case MODULE_ID_AUDIOVIDEO:
			moduleToAux_FromAudio_AnalyseMsg(param, len);
			break;
		case MODULE_ID_SYSTEM:
			moduleToAux_FromSystem_AnalyseMsg(param, len);
			break;
		case MODULE_ID_KEY:
			moduleToAux_FromKey_AnalyseMsg(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToAux_FromExternalCtrl_AnalyseMsg(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToAux_FromAutomate_AnalyseMsg(param, len);
		    break;
		default:break;
	}
}

