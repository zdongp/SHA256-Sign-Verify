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

extern moduleid_t locale_module_mid();

void RemoteToModule_NotifySystem_ChangeLightness(u8 lightness)
{

	LOGD("[%s] brightness:%d",__FUNCTION__,lightness);
	u8 buf[] = {0xF2, lightness};
	if(lightness >=4)
		return;

	makeAndSendMessageToModule(MODULE_ID_FLYJNISDK, MODULE_ID_SYSTEM, buf, 2);
}

void RemoteToModule_NotifySystem_RemoteOnlineControlPowerOff(u8 uParam)
{
	LOGD("[%s] uParam:%d",__FUNCTION__,uParam);
	u8 buf[] = {0x01, uParam};
	makeAndSendMessageToModule(MODULE_ID_REMOTEONLINE, MODULE_ID_SYSTEM, buf, 2);
}

