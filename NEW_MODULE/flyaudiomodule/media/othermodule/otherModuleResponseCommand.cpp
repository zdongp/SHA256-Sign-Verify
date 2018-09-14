#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}

void analyseTimerHandleMessage(u8 *p, u8 len)
{
}

void analyseOtherModuleMessage(unsigned char sendModuleId, unsigned char *param, unsigned char len)
{
		switch(sendModuleId){
		case MODULE_ID_KEY:
			LOGD("Media message from Key Module");
			moduleToMedia_FromKey_Message(param, len);
			break;
		case MODULE_ID_SYSTEM:
			moduleToMedia_FromSystemMessage(param, len);
			break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToMedia_FromAudioVideoMessage(param, len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			moduleToMedia_FromExternalCtrlMessage(param, len);
			break;
		case MODULE_ID_AUTOMATE:
		    moduleToMedia_FromAutomate(param,len);
		    break;
		case MODULE_ID_FLYJNISDK:
		    moduleToMedia_FromJniSdk(param,len);
		    break;
		default:
			break;
	}
}

