#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"
#include "halRequestFunction.h"
#include "param.h"
#include "pageID.h"

void otherModuleInit(void){

}

void otherModuleDeInit(void){

}


void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){
	char cCmdType = param[0];

	//LOGD("Module_system  sendModuleId %x  cCmdType %x  ",sendModuleId,cCmdType);
	switch(cCmdType)
	{
	case 0x81:
	case 0x82:
	case 0x83:
	case 0x30:
	case 0x31:
		anyModuleToSysModue_Dispatch_Msg(sendModuleId,(char*)param, len);
		return;
		break;
	default:break;
	}

	LOGD("Module_system  sendModuleId %x  cCmdType %x  ",sendModuleId,cCmdType);

	switch(sendModuleId){
		case MODULE_ID_BACK: //BackCar Msg
			BackCarModuleToSysModule_Dispatch_Msg((char*)param, len);
			break;
		case MODULE_ID_KEY: //Key Msg
			KeyModuleToSysModule_Dispatch_Msg((char*)param, len);
			break;
		case MODULE_ID_CENTER: //Center Msg
			CenterModuleToSysModule_Dispatch_Msg((char*)param, len);
			break;
		case MODULE_ID_BT:
            BlueModuleToSysModule_Dispatch_Msg(param, len);
			break;
		case MODULE_ID_EXTCAR:
			ExtcarModuleToSysModule_Dispatch_Msg(param,len);
			break;
		case MODULE_ID_OSD:
			OsdModuleToSysModule_Dispatch_Msg(param ,len);
			break;
		case MODULE_ID_EXTERNALCTRL:
			ExternalCtrlModuleToSysModule_Dispatch_Msg(param, len);
			break;
        case MODULE_ID_AUTOMATE:
            moduleToSystem_FromAutomate(param,len);
            break;
		case MODULE_ID_FLYJNISDK:
            g_clsSystem.moduleToSystem_FromFlyJniSdk(param,len);
            break;
		case MODULE_ID_AUDIOVIDEO:
			moduleToSystem_FromAudiovideo(param,len);
			break;
		case MODULE_ID_REMOTEONLINE:
			moduleToSystem_FromRemoteOnline(param,len);
			break;
		case MODULE_ID_DVR:
			moduleToSystem_FromDVR(param,len);
			break;
		case MODULE_ID_RADIO:
			moduleToSystem_FromRadio(param,len);
			break;
		default:break;

	}
}
