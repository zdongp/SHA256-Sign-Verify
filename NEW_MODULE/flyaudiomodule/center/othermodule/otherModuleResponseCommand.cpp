#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len)
{
	switch(sendModuleId){
		case MODULE_ID_BT:
			moduleToCenter_FromBT_Message(param, len);
			break;
		case MODULE_ID_SYSTEM:
			moduleToCenter_FromSystem_Message(param, len);
			break;
		case MODULE_ID_TPMS:
			moduleToCenter_FromTPMS_Message(param, len);
			break;
		case MODULE_ID_EXTCAR:
			moduleToCenter_FromExtCar_Message(param, len);
			break;
		case MODULE_ID_SYNC:
			moduleToCenter_FromSYNC_Message(param, len);
			break;
		case MODULE_ID_DNV:
			moduleToCenter_FromDNV_Message(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToCenter_FromAutomate(param,len);
		    break;
		default:break;
	}
}

void analyseTimerHandleMessage(u8 *p, u8 len)
{
}


