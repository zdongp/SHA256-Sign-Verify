#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"


#include <flymoduleApi_internal.h>


void blcdToHal_Init(char param){
	unsigned char buf[2] = { 0x01, 0x00};

	if(param){
		buf[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_BLCD, buf, 2);
}


void blcdToHal_SetSoundChannel(unsigned char soundChannel){
	unsigned char buf[2] = { 0x10, soundChannel};

	makeAndSendMessageToHal(HAL_ID_BLCD, buf, 2);
}

void blcdToHal_SetVideoChannel(u8 ch){
	u8 param[] = {0x11, ch};

	makeAndSendMessageToHal(HAL_ID_BLCD, param, 2);
}
