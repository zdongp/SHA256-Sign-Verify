#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>

void auxToHal_QueryVideo(void){
	unsigned char buf[] = {0x28,0x00};
	makeAndSendMessageToHal(HAL_ID_SYSTEM,buf,2);
}

void auxToHal_MenuControl(unsigned char funUI){
	unsigned char buff[2]={0x40,0x00};
	buff[1] = funUI;
	makeAndSendMessageToHal(HAL_ID_AUDIO,buff,2);
}

void auxToHal_ColorControl(unsigned char funUI){
	unsigned char buff[2]={0x90,0x00};
	buff[1] = funUI;
	makeAndSendMessageToHal(HAL_ID_AUDIO,buff,2);
}
