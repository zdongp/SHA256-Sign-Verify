#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 

#include "global.h"
#include "appResponseFunction.h"
#include "appRequestFunction.h"
#include "timer_interface.h"
#include "pageID.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "param.h"
#include "halResponseFunction.h"
#include "moduleParamRequest.h"

void setTimerAcDataTimeToOSD(void)
{
	SetTimer(GOLF_AC_TIMER_CYCLE_AC_DATA_TIMER_TO_OSD, 1, GOLF_AC_TIMER_ID_AC_DATA_TIMER_TO_OSD);
}

void killTimerAcDataTimeToOSD(void)
{
	DeleteTimer(GOLF_AC_TIMER_ID_AC_DATA_TIMER_TO_OSD);
}

void  select_sleep(int s, int us)
{
	struct timeval timeout;
	timeout.tv_sec = s;
	timeout.tv_usec = us;

	select(0, NULL, NULL, NULL, &timeout);
}

int TimerHandlerCenter(timer_t timerId)
{
		switch((s64)timerId)
		{
			case AC_TIMER_ID_BYD_AC_DO_NOT_SHOW:
			{
				pLocalParam->bACCanShow = false;
			}
			break;
			case AC_TIMER_ID_TEST_CAN_RUN:
			{
				appRequest_byd_refreshLeftTemprature(100);
			}
			break;
			case GOLF_AC_TIMER_ID_AC_DATA_TIMER_TO_OSD:
			{
				pLocalParam->golf_timer_state = true;
				
				LOGD("GOLF_TIMER SHOW THE 1ST OSD!");
				golf_ac_msg_to_osd(pLocalParam->e_golf_ac_cold_mode, pLocalParam->e_golf_ac_degree_unit, pLocalParam->u8_golf_degree_left, \
					pLocalParam->u8_golf_degree_right,pLocalParam->u8_golf_wind_level , pLocalParam->e_golf_ac_ac_mode);
				
			}
			break;
			default:
			break;
		}
	

	return 0;
}

void  initTimerCenter(timer_handler_function func){
	
	u8 buf[] = {0x10,0x00,0x00,0x00,0x00};
    
    buf[1] = ((u64)func >> 24) & 0xFF;
    buf[2] = ((u64)func >> 16) & 0xFF;
    buf[3] = ((u64)func >> 8) & 0xFF;
    buf[4] = (u64)func & 0xFF;

    
    makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_TIMER,buf,5);
	LOGD("-----------initTimerCenter Success-----------");
	
}

int SetTimer(int nElaspe_ms, int nMode, int timerId){
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
    
    makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_TIMER,buf,10);
    LOGD("SetTimer Success!");
    return 0;
}

int DeleteTimer(int timerId){
	
	u8 buf[5];
	
	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    makeAndSendMessageToModule(MODULE_ID_AC,MODULE_ID_TIMER,buf,5);
	LOGD("DeleteTimer Success!");
    return 0;
}
