#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#include "hal.h"
#include "halResponseCommand.h"
#include "halResponseFunction.h"


void analyseHalMessage(halid_t hid, u8 cmd, u8 *param, u8 len){
	switch(hid){
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
		default:break;
	}
}
