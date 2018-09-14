#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>
#include "otherModuleRequestCommand.h"



void syncToHal_Command(u8 uMode,u8 uCmd,u8 u8Param)
{
	unsigned char buf[] = {uMode,uCmd, u8Param};
	makeAndSendMessageToHal(HAL_ID_EXTCAR,buf,3);
	makeAndSendMessageToModule(MODULE_ID_SYNC,MODULE_ID_EXTCAR,buf,3);
}

