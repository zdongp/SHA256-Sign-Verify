#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "timer_interface.h"
#include "TimerModuleResponseCommand.h"


void analyseTimerHandleMessage(u8 *p, u8 len)
{
	LOGD("[%s] p[0]:%x,p[1]:%x",__FUNCTION__,p[0],p[1]);
	switch(p[0])
	{
		case MODULE_ID_TIMER:
			TimerHandlerCenter((timer_t)p[1]);
			break;
	}
}

