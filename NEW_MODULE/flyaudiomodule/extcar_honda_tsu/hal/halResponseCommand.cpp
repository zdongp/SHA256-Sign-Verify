#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#include "hal.h"
#include "halResponseCommand.h"
#include "halResponseFunction.h"

void halInit(void){

}

void halDeInit(void){

}

void analyseHalMessage(halid_t halId, u8 msgResCmd, u8 *param, u8 len){
	switch(halId){
		case HAL_ID_EXTCAR_HONDA_RSU:
			analyseHalMessage_EXTCAR_HONDA_TSU(msgResCmd, param, len);
			LOGD("[%s] %x %x %x %x","(HONDA TSU):",msgResCmd,param[0],param[1],param[2]);
		break;
		default:break;
	}
}
