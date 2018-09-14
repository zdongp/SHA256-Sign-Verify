#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "halResponseFunction.h"
#include "hal.h"
#include "halResponseCommand.h"
#include "flytypes.h"
void halInit(void){

}

void halDeInit(void){

}
void analyseHalMessage(halid_t halId, u8 msgResCmd, u8 *param, u8 len){
	
	LOGI("AUXSCREEN: analyseHalMessage halId = 0X%02X, msgResCmd = 0X%02X , param = 0X%02X \n", halId, msgResCmd, param[0]);

	if(halId != HAL_ID_EXDISPLAY)
		return;
	
	if(msgResCmd >= 0x30 && msgResCmd <=0x3f)
	{
		halToAuxScreenSetRadioStatusMessage(msgResCmd,param,len);
		return;
	}
	
	switch(msgResCmd){
		case 0x01:
		       halToAuxScreen_InitParam(param[0]);
			break;
		case 0x02:
				halToAuxScreen_InitState(param[0]);
			break;
		case 0x10:
				halToAuxScreen_IsAuxScreenDeviceExited(param[0]);
			break;
		case 0x11:
				analyseHalSetJumpMediaPageMessage(param,len);
			break;
		case 0x73:
				halToAuxScreen_Control(param[0]);
			break;
		case 0x74:
				halToAuxScreen_Request_GetCallLogList(param[0],param[1]);
			break;
		case 0x75:
				halToAuxScreen_ReturnPhoneDialOperating(param[0],param[1]);
			break;
		case 0xB0:
            	analyseHalSetGpsStatusMessage(param,len);
            break;
		default:
			break;
	}
}

