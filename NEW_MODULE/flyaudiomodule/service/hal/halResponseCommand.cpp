#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "flytypes.h"
#include "hal.h"
#include "halResponseCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"


void analyseHalMessage(moduleid_t halId, u8 msgResCmd, u8 *param, u8 len){
	switch(halId){
		case HAL_ID_SERVICE:
			analyseHalMessage_service(msgResCmd, param, len);
			break;
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

