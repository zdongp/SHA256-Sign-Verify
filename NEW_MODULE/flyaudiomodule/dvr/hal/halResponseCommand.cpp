#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halResponseFunction.h"
#include "halResponseCommand.h"



void halInit(void){

}

void halDeInit(void){

}

void analyseHalMessage(halid_t halId, u8 msgResCmd, u8 *param, u8 len){
	switch(halId){
		case HAL_ID_DVR:
			analyseHalMessage_DVR(msgResCmd,param,len);
			break;
		default:break;
	}


}

