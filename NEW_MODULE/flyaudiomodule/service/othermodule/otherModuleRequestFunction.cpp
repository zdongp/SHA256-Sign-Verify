#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include"moduleID.h"
#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "pageID.h"
#include "param.h"
#include "flytypes.h"
#include "flymoduleApi.h"

extern moduleid_t locale_module_mid();

void service_property_parameter(char isSave)
{
	u8 param[] = {MESSAGETYPE_BROADCAST, 0x01, 0x00};
	
	if(isSave)
		param[1] = 0x01;

	makeAndSendMessageToBroadcast(param, 3);

}

void service_all_startup(void)
{
	u8 param[] = {MESSAGETYPE_BROADCAST, 0x2D, 0x00};
	makeAndSendMessageToBroadcast(param, 3);
}

void service_all_suspend_info(char type)
{
	u8 param[] = {MESSAGETYPE_BROADCAST, 0x2C, 0x00};
	
	param[2] = type;
	
	makeAndSendMessageToBroadcast(param, 3);
}

void serviceToModule_setAllModuleLogOpen(u8 p)
{
	u8 param[] = {MESSAGETYPE_BROADCAST, 0x2E, p};
	makeAndSendMessageToBroadcast(param, 3);
	
}

void service_all_standby_info(char type)
{
    u8 param[] = {MESSAGETYPE_BROADCAST, 0x1D, 0x00};
    param[2] = type;
	makeAndSendMessageToBroadcast(param, 3);
}

