#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>

void acToHal_Init(void){
	u8 buf[] = {0x01 ,0x01};

	makeAndSendMessageToHal(HAL_ID_AC,buf ,2);
}
