#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 

#include "global.h"
#include "timer_interface.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"
#include "appRequestFunction.h"
#include "halRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "moduleParamResponse.h"

int TimerHandlerCenter(timer_t timerId){
	//LOGD("IPOD timer handler");
	switch((s64)timerId)
	{
		case IPOD_CONNECT_TIMER:{
			LOGD("IPOD_CONNECT_TIMER");

			//ipodToHal_SetConnectPing();
			StartConnectIpod();
			ipodToHal_SetConnectPing();
			////DeleteTimer(IPOD_CONNECT_TIMER);
			////SetTimer(5000,0,IPOD_CONNECT_TIMER);
		}break;
		case IPOD_PING_TIMER:{
			if(pLocalParam->pingIpodSuccess){
					////DeleteTimer(IPOD_PING_TIMER);
					////SetTimer(5000,0,IPOD_PING_TIMER);
					pLocalParam->pingIpodSuccess=0;
					ipodToHal_SetConnectPing();
				}
			else {
					LOGD("IPOD_PING_TIMER CLEAR");
					////DeleteTimer(IPOD_PING_TIMER);
					ClearIPODMessage();
				}
		}break;
		case IPOD_PREVNEXTSONG_TIMER:{
			
			//ipodToHal_QueryTypeListIndex();
			//ipodToHal_QueryCurPlayListSongSum();
			ipodToHal_QueryCurrentPositionMusicName(pLocalParam->curTrack);	
			
			//ipodToHal_SetCurrentPositionPlay(pLocalParam->curTrack);
			ipodToHal_SetTimeState();
			////DeleteTimer(IPOD_PREVNEXTSONG_TIMER);
			
		}break;
		case IPOD_GETSONGNAME_TIMER:{
			ipodToHal_QueryCurrentPositionMusicName(pLocalParam->curTrack);	
			////DeleteTimer(IPOD_GETSONGNAME_TIMER);
		}break;
		//case THEBUG_TIMER:{
			//LOGE("THEBUG_TIMER hander");
			//SetTimer(1000,0,THEBUG_TIMER);
		//}break;
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

    
    makeAndSendMessageToModule(MODULE_ID_IPOD,MODULE_ID_TIMER,buf,5);
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
    
    makeAndSendMessageToModule(MODULE_ID_IPOD,MODULE_ID_TIMER,buf,10);

    
    return 0;
}

int DeleteTimer(int timerId){
	u8 buf[5];
	
	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    makeAndSendMessageToModule(MODULE_ID_IPOD,MODULE_ID_TIMER,buf,5);
    
    return 0;
}


