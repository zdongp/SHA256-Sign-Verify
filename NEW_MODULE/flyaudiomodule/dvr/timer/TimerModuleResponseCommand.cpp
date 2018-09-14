#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "timer_interface.h"
#include "TimerModuleResponseCommand.h"


void analyseTimerHandleMessage(u8 *p, u8 len)
{
	timer_t tId = (timer_t)0xFFFFFF;
	memcpy(&tId,p+3,sizeof(timer_t));

	TimerHandlerCenter(tId);
}

