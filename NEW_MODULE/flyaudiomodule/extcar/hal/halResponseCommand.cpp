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
		case HAL_ID_EXTCAR:
			analyseHalMessage_EXTCAR(msgResCmd, param, len);
			break;
		default:break;
	}
}
