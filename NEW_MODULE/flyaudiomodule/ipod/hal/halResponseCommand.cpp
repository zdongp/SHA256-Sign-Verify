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

	//LOGD("analyseHalMessage:FF.55.%x.%x.%x.%x.%x.+++++++\n",param[2],param[3],param[4],param[5],param[6]);
	//LOGD("analyseHalMessage:len:%d",len);
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
		case HAL_ID_IPOD:{
			analyseHalMessage_IPOD(param, len);
		}
		break;
		default:break;
	}
}

