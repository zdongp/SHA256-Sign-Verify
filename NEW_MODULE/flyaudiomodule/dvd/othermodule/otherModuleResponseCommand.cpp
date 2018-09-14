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
	LOGD("dvd analyseOtherModuleMessage sendModuleId:%x param[0]:%x param[1]:%x",sendModuleId,param[0],param[1]);
	switch(sendModuleId){
		case MODULE_ID_SYSTEM:
			moduleToDvd_FromSystem_Message(param, len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToDvd_FromAudiovideo_Message(param, len);
			break;
		case MODULE_ID_KEY:
			moduleToDvd_FromKey_Message(param, len);
			break;
		case MODULE_ID_BLCD:
			moduleToDvd_FromBlcd_Message(param, len);
			break;
		case MODULE_ID_GPS:
			moduleToDvd_FromGps_Message(param, len);			
			break;
		case MODULE_ID_CENTER:
			moduleToDvd_FromCenter_Message(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToDvd_FromExternalCtrl_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToDVD_FromAutomate(param, len);
		    break;
		case MODULE_ID_FLYJNISDK:
		    g_clsDvd.analyseFlyJniSdkMessage(param, len);
		    break;
		default:break;
	}
}

