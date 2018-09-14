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
    LOGD("[%s] sendModuleId:%x,param[0]:%d,param[1]:%d",__FUNCTION__,sendModuleId,param[0],param[1]);
	switch(sendModuleId){
		case MODULE_ID_KEY:
			moduleToExternalCtrl_AnalyseModuleCommand_key(param,len);
			break;
		case MODULE_ID_BT:
			moduleToExternalCtrl_AnalyseModuleCommand_Bt(param,len);
			break;
		case MODULE_ID_BACK:
			moduleToExternalCtrl_AnalyseModuleCommand_backcar(param,len);
			break;
		case MODULE_ID_SYSTEM:
			moduleToExternalCtrl_AnalyseModuleCommand_system(param,len);
			break;
		case MODULE_ID_CENTER:
			moduleToExternalCtrl_AnalyseModuleCommand_center(param,len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToExternalCtrl_AnalyseModuleCommand_Audiovideo(param,len);
			break;
		case MODULE_ID_FLYJNISDK:
			pLocalParam->g_pClsExternalJniSdk.getSdkToModuleExternalMessage(param,len);
			break;
		default:break;
	}
}



