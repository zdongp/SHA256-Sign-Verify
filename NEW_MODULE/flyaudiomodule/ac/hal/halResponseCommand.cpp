#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#include "flytypes.h"
#include "hal.h"
#include "halResponseFunction.h" 
#include "halResponseCommand.h"


void halInit(void){

}

void halDeInit(void){

}

void analyseHalMessage(halid_t halId, u8 cmd, u8 *param, u8 len)
{
	switch(halId){
		
		case HAL_ID_GLOBAL:break;
		case HAL_ID_SYSTEM:break;
		case HAL_ID_AUDIO:break;
		case HAL_ID_VIDEO:break;
		case HAL_ID_KEY:break;
		case HAL_ID_EXDISPLAY:break;
		case HAL_ID_RADIO:break;
		case HAL_ID_DVD:break;
		case HAL_ID_BT:break;
		case HAL_ID_XMRADIO:break;
		case HAL_ID_TPMS:break;
		case HAL_ID_TV:break;
		case HAL_ID_AC:
			analyseHalMessage_AIRCONDITION(cmd, param, len);
			break;
		
		default:break;
	}
}

