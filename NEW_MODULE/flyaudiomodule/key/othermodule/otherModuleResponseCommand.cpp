#include <stdio.h>
#include <stdlib.h>

#include "flytypes.h"
#include "global.h"
#include "moduleID.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"

#include "appResponseCommand.h"

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){

	LOGD("Key: analyseOtherModuleMessage: sendModuleId = 0x%02X, param[0] = 0x%02X, ", sendModuleId, param[0]);
	
	switch(sendModuleId){
	case MODULE_ID_SYSTEM:
		moduleToKey_AnalyseModuleCommand_System(param,len);
		break;
	case MODULE_ID_AUDIOVIDEO: //Sound Mode
		moduleToKey_AnalyseModuleCommand_Sound(param,len);
		break;
	case MODULE_ID_SYNC:
		moduleToKey_AnalyseModuleCommand_Sync(param,len);
		break;
	case MODULE_ID_EXTCAR:
		moduleToKey_AnalyseModuleCommand_Key(param, len);
		break;
	case MODULE_ID_EXTERNALCTRL:
		moduleToKey_AnalyseModuleCommand_ExternalCtrl(param, len);
		break;
	case MODULE_ID_FLYJNISDK:
		analyseSdkToKeyDedicate_information(param, len);
		break;
	default:break;
	}
}
