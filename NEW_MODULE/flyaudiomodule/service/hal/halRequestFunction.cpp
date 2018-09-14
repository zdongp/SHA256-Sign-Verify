#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"
#include "pageID.h"
#include "param.h"

#include <flymoduleApi_internal.h>

void service_to_hal_for_suspends(u8 mode)
{
	u8 param[] = {0x2C, 0x00};
	param[1] = mode;
	makeAndSendMessageToHal(HAL_ID_SERVICE, param, 2);
}

void service_to_hal_TheNewStructure(u8 param)
{
	u8 buff[] = {0x30,0x00};
	buff[1] = param;
	makeAndSendMessageToHal(HAL_ID_SERVICE, buff, 2);
}

void service_to_hal_ACCOff_30s_TheNewStructure(u8 param)
{
	u8 buff[] = {0x31,0x00};
	buff[1] = param;
	makeAndSendMessageToHal(HAL_ID_SERVICE, buff, 2);
}

void service_to_hal_FastToSwitchMachine_60s_TheNewStructure(u8 param)
{
	u8 buff[] = {0x32,0x00};
	buff[1] = param;
	makeAndSendMessageToHal(HAL_ID_SERVICE, buff, 2);
}

void service_to_hal_15Days_reset(u8* param)
{
	u8 buff[] = {0x00,0x00,0x00,0x00,0x00};
	buff[0] =(u8)0xe0;
	buff[1] = param[0];
	buff[2] = param[1];
	buff[3] = param[2];
	buff[4] = param[3];
	LOGD("service_to_hal_15Days_reset,%x,%x,%x,%x",buff[1],buff[2],buff[3],buff[4]);
	makeAndSendMessageToHal(HAL_ID_SERVICE, buff, 5);
}

void service_to_hal_SetGeneralKnobPassword(u8 *param,u8 len)
{
	u8 buff[len+1];
	memset(buff,0,sizeof(buff));
	buff[0] = 0xF0;
	memcpy(&buff[1],param,len);
	
	for(int i=0;i<len+1;i++)
	{
		LOGD("%x",buff[i]);
	}
	makeAndSendMessageToHal(HAL_ID_SERVICE, buff, len+1);
}

