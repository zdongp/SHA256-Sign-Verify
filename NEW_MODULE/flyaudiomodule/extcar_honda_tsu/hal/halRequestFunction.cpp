#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"
#include <flymoduleApi_internal.h>

void extcarToHal_Init(char param){
	unsigned char buf[2] = { 0x01, 0x00};

	if(param){
		buf[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_EXTCAR_HONDA_RSU, buf, 2);
}

void extcarToHal_HondaTsu_Data(u8 *buf,int len)
{
	u8 szMsg[256] = {0};
	szMsg[0] = 0x10;
	
	if(len > 256)
		len = 255;
	memcpy(szMsg+1, buf, len);

	makeAndSendMessageToHal(HAL_ID_EXTCAR_HONDA_RSU, szMsg, len + 1);
}

