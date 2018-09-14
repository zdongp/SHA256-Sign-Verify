#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#include "hal.h"
#include "halResponseCommand.h"
#include "halResponseFunction.h"


void halInit(void){
	halInit_audio();
}

void halDeInit(void){
	halInit_audio();
}

void analyseHalMessage(halid_t halId, u8 msgResCmd, u8 *param, u8 len){
	switch(halId){
		case HAL_ID_GLOBAL:break;
		case HAL_ID_SYSTEM:break;
		case HAL_ID_AUDIO:
			analyseHalMessage_AUDIO(msgResCmd, param, len);
			break;
		case HAL_ID_VIDEO:
			analyseHalMessage_VIDEO(msgResCmd, param, len);
			break;
		case HAL_ID_KEY:break;
		case HAL_ID_EXDISPLAY:break;
		case HAL_ID_RADIO:break;
		case HAL_ID_DVD:break;
		case HAL_ID_BT:break;
		case HAL_ID_XMRADIO:break;
		case HAL_ID_TPMS:break;
		case HAL_ID_TV:break;
		default:break;
	}
}

