#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "param.h"

void otherModuleInit(void){
}

void otherModuleDeInit(void){
}



void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	LOGD("[%s] sendModuleId:%x",__FUNCTION__,sendModuleId);
	switch(sendModuleId){
		case MODULE_ID_SYSTEM:
			moduleToAudioVideo_FromSystem_Message(param, len);
			break;
		case MODULE_ID_KEY:
			moduleToAudioVideo_FromKey_Message(param, len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToAudioVideo_FromAudioVideo_Message(param, len);
			break;
		case MODULE_ID_CENTER:
			moduleToAudiovideo_FromCenter_Message(param, len);
			break;
		case MODULE_ID_DVD:	
		case MODULE_ID_TV:
		case MODULE_ID_AUX:
		case MODULE_ID_BACK:
			pLocalParam->OSDSetToModule = sendModuleId;
			moduleToAudioVideo_FromTVOrDvd_Message(param, len);
			break;
		case MODULE_ID_BT:
			moduleToAudioVideo_FromBlueTooth_Message(param, len);
			break;
		case MODULE_ID_TPMS:
			moduleToAudioVideo_FromTmps_Message(param, len);
		case MODULE_ID_MEDIA:
			moduleToAudioVideo_FromMedia_Message(param,len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToAudioVideo_FromExternalCtrl_Message(param,len);
			break;
		case MODULE_ID_EXTCAR:
			moduleToAudioVideo_FromExtcar_Message(param, len);
			break;
		case MODULE_ID_SYNC:
			moduleToAudioVideo_FromSync_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToAudioVideo_FromAutomate_Message(param, len);
		    break;
		case MODULE_ID_FLYJNISDK:
		    g_clsAudiovideo.analyseFromFlyJniSdkMessage(param, len);
		    break;
		default:break;
	}
}



