#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}


void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	switch(sendModuleId){
		case MODULE_ID_BT:
		    moduleToExtcar_FromBT_Message(param, len);
			break;
		case MODULE_ID_SYSTEM:
			moduleToExtcar_FromSystem_Message(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToExtcar_FromExternalCtrl_Message(param, len);
		break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToExtcar_FromAudioVideo(param, len);
			break;
		case MODULE_ID_BACK:
			moduleToExtcar_FromBackCar_Message(param,len);
			break;
		case MODULE_ID_KEY:
			moduleToExtcar_FromKey_Message(param,len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToExtcar_FromAutomate(param,len);
		    break;
		case MODULE_ID_AC:
			 moduleToExtcar_From_Public_AC_Message(param, len);
			break;
		case MODULE_ID_SYNC:
			 moduleToExtcar_From_Public_SYNC_Message(param, len);
			break;
		case MODULE_ID_CENTER:
			moduleToExtcar_From_Public_Center_Message(param, len);
		case MODULE_ID_GPS:
			 moduleToExtcar_FromGPS(param, len);
			break;
		case MODULE_ID_FLYJNISDK:
			g_clsExtcar.analyseFlyJniSdkMessage(param,len);
			break;
		default:break;
	}
}

