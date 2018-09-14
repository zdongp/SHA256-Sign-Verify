#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"


void appToCenter_Parameter(unsigned char *param, unsigned char paramLen){

    LOGD("param[0]:0x%x--param[1]:0x%x",param[0],param[1]);
    
	unsigned char ucLCDBrightNess = 0;
    unsigned char ucLCDBrightNessLen = 0;
    getOtherModuleParam(MODULE_ID_SYSTEM,LCD_STATE,&ucLCDBrightNess,&ucLCDBrightNessLen);
    
	switch(param[0]){
		case 0x00:
			centerToModule_NotifySystem_Hardware_JumpPrePage();	// 0x84 0x00 ǰһҳ
			break;
		case 0x01:
			LOGD("appToCenter_Parameter-param[1]:0x%x",param[1]);
			if(param[1] == 0x00){	// 1 0
				centerToModule_NotifySystem_EnterThreePartyApp();	// 0x85 0x00
			}
			else if(param[1] == 0x01){				// 1 1
				centerToModule_NotifySystem_EnterHomePage();
			}
			else if(param[1] == 0x02){
				centerToModule_NotifySystem_EnterGpsPage();
			}
			else if(param[1] == 0x03){
				centerToModule_NotifySystem_EnterNonHomePage();
			}
			break;
		case 0x02:
			centerToModule_NotifyOSD_SetOSDHidden();
			break;
		case 0x03:
			centerToModule_NotifyAudiovideo_GpsSoundState(param[1]);
			break;
		case 0x04:
			{
				centerToModule_NotifySystem_ReturnToPage(&param[1], 2);
			}
			break;
		case 0x10://TCU FinalActiveStatus
			centerToModule_NotifyExtcar_FordTCU_Request(param[1]);
			break;
		case 0x69://To deal with the drop-down warning indicates page can not be displayed OSD issue.
		    AppNotifyCenterModule_aboutWarningDescriptionPageDisappearStatus(param[1]);
		    break;
		case 0x70:
			centerToModule_NotifyAudiovideo_AppRequestMixedVoice(param[1]);
			break;
		case 0x71:
			centerToModule_NotifyAudiovideo_SimulationOfGPS_Process_RequestMixedVoice(param[1]);
			break;
		case 0x81:
			centerToModule_NotifySystem_DisplayBarCode();
			break;
		case 0x82:
			centerToModule_NotifySystem_SysTimeFormat(param[1]);
			break;
		case 0x88:
			centerToModule_NotifyBT_SIMPhoneStatus(param[1]);
			centerToModule_NotifySystem_SIMPhoneStatus(param[1]);
			break;
		case 0xF0:
			{
				centerToModule_NotifySystem_DebugPanelType(param[1]);
			}
			break;
		case 0xF2:
			centerToModule_NotifySystem_Brightness(param[1]);
			break;
		case 0xF3:
			centerToModule_NotifySystem_ScreenOff_Brightness(param[1]);
			break;
//		case 0x88:
//			LOGD("centerToModule_NotifyBT_HelpSet");
//			centerToModule_NotifyBT_HelpSet();
//			break;
//		case 0x89:
//			centerToModule_NotifyBT_HelpPhone(param[1]);
//			break;
//		case 0x8A:
//			centerToModule_NotifyBT_State();
			break;
		case 0xf9:
			centerToModule_NotifyAudiovideo_AndroidIntentAction_MediaPlay_States(param[1]);
			break;
		case 0x3a:
			GetAndroid_Power_OnOrOff_0s(param[1]);
			break;
		case 0x3c:
			centerToModule_NotifyService_FromAndroid_Acc_OnOrOff_30s(param[1]);
			break;
		case 0x3d:
			centerToModule_NotifyService_FromAndroid_FastToSwitichMachine_60s(param[1]);
			centerToModule_NotifyFlyRemoteOnline_FromAndroid_FastToSwitichMachine_60s(param[1]);
			break;
		case 0x3f:
			 centerToModule_NotifyService_FromAndroid_PingLoop(param[1]);
			break;
		case 0xe0:
			centerToModule_NotifyService_FromAndroid_15DaysReset(&param[1],4);
			break;
		default:
			break;
	}
}


void AppNotifyCenterModule_aboutWarningDescriptionPageDisappearStatus(u8 uState)
{
    if(uState == 0x01)
    {
        pLocalParam->uIsAgreePageHide = 1;
    }
}

void GetAndroid_Power_OnOrOff_0s(u8 p)
{
	centerToModule_NotifyOtherModule_FromAndroid_Power_OnOrOff_0s(p);
}

