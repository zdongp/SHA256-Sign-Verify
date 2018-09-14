#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#include "hal.h"
#include "halResponseCommand.h"
#include "halResponseFunction.h"
#include "flytypes.h"
void halInit(void){

}

void halDeInit(void){

}

void analyseHalMessage(halid_t halId, u8 cmd, u8 *param, u8 len){
	
	if(halId != HAL_ID_EXDISPLAY)
		return;
	
	switch(cmd){
		case 0x01:
		   
			break;
		case 0x02:
			
			break;
		case 0x10:
			
			break;
		default:
			break;
	}
}

