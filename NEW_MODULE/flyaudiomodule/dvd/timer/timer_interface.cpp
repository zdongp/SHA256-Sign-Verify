#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 

#include "global.h"
#include "pageID.h"
#include "timer_interface.h"

#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "moduleParamRequest.h"
#include "halRequestFunction.h"
#include "param.h"



int TimerHandlerCenter(timer_t timerId){
	LOGI("DVD timer handler");
	switch((s64)timerId)
	{
		case DVD_OSD_TIMER_HIDDEN_DISPLAY:
		{
			u16 curPage = 0;
			u8 curPageLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE, (u8 *)&curPage,&curPageLen);
			if(curPage == PAGE_DVD_VIDEO_CONTROL || curPage == PAGE_DVD_VIDEO_SET){
				dvdToModule_NotifySystem_jumpPage(PAGE_DVD_VIDEO);
			}
		}
		break;
		case DVD_DELAY_PLAY:
		{
			if(pLocalParam->playStatus != 0x01)
				dvdToHal_IR(DVDTOHAL_IR_PLAY);
		}
		break;
		case DVD_DELAY_STOP:
		{
			if(pLocalParam->playStatus != 0x00)
			{
				dvdToHal_IR(DVDTOHAL_IR_STOP);
				dvdToHal_IR(DVDTOHAL_IR_STOP);
				dvdToHal_IR(DVDTOHAL_IR_STOP);
			}
		}
		break;
		default:break;
	}
	
	return 0;
}

void initTimerCenter(timer_handler_function func){
	LOGI("pFunc:%x", func);
	u8 buf[] = {0x10,0x00,0x00,0x00,0x00};
    
    buf[1] = ((u64)func >> 24) & 0xFF;
    buf[2] = ((u64)func >> 16) & 0xFF;
    buf[3] = ((u64)func >> 8) & 0xFF;
    buf[4] = (u64)func & 0xFF;

    
    makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_TIMER,buf,5);
}

int SetTimer(int nElaspe_ms, int nMode, int timerId){
	if(timerId == DVD_OSD_TIMER_HIDDEN_DISPLAY)
	{
		nMode = 1;
	}
	
	u8 buf[10];

	buf[0] = 0x20;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    buf[5] = (nElaspe_ms >> 24) & 0xFF;
    buf[6] = (nElaspe_ms >> 16) & 0xFF;
    buf[7] = (nElaspe_ms >> 8) & 0xFF;
    buf[8] = nElaspe_ms & 0xFF;

	buf[9] = (u8)nMode;
    
    makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_TIMER,buf,10);

    
    return 0;
}

int DeleteTimer(int timerId){
	u8 buf[5];
	
	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    makeAndSendMessageToModule(MODULE_ID_DVD,MODULE_ID_TIMER,buf,5);
    
    return 0;
}

