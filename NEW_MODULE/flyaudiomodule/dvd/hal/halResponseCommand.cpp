#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "flytypes.h"
#include "hal.h"
#include "halResponseFunction.h"
#include "halResponseCommand.h"
#include "halRequestFunction.h"

void halInit(void){
	//halInit_ResponseDVD();

}

void halDeInit(void){

}

void analyseHalMessage(halid_t halId, u8 msgResCmd, u8 *param, u8 len){
	switch(halId){
		case HAL_ID_GLOBAL:break;
		case HAL_ID_SYSTEM:break;
		case HAL_ID_AUDIO:break;
		case HAL_ID_VIDEO:break;
		case HAL_ID_KEY:break;
		case HAL_ID_EXDISPLAY:break;
		case HAL_ID_RADIO:break;
		case HAL_ID_DVD:
			analyseHalMessage_DVD(msgResCmd, param, len);
			break;
		case HAL_ID_BT:break;
		case HAL_ID_XMRADIO:break;
		case HAL_ID_TPMS:break;
		case HAL_ID_TV:break;
		default:break;
	}
}

