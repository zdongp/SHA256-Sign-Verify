#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "hal.h"
#include "halRequestFunction.h"

#include <flymoduleApi_internal.h>

void TimerModuleToTimerMessage(unsigned char sendModuleId, unsigned char arrivedModuleId, unsigned int index)
{
	LOGD("[%s] arrivedModuleId:%x index:%d",__FUNCTION__,arrivedModuleId,index);
	makeAndSendTimerHandleMessage(sendModuleId, arrivedModuleId, index);
}


