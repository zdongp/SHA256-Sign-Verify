#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 

#include "global.h"
#include "appResponseFunction.h"
#include "timer_interface.h"
#include "pageID.h"
#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "param.h"
#include "halResponseFunction.h"


void produceSimulativeData(int num, unsigned char *param)
{
	/*hight-lower not warming altermate*/
	/*if (num%2 == 0)
		param[1] = 0xAB;
	else 
		param[1] = 0x1A;*/
	/*-------------------------*/
	
	/*hight-normal-lower not warming altermate*/
	/*if (num%3 == 0)
		param[1] = 0xAB;
	else if (num%3 == 1)
		param[1] = 0x4B;
	else if (num%3 == 2)
		param[1] = 0x1B;*/
	/*-------------------------*/

	/*hight-lower warming altermate*/
	/*num = num%6;
	if (num <= 2 )
		param[1] = 0xAB;
	else if (num > 2 && num <= 5)
		param[1] = 0x1B;*/
	/*-------------------------*/
	
	/*hight-normal-lower warming altermate*/
/*	num = num%9;
	if (num <= 2 )
		param[1] = 0xAB;
	else if (num > 2 && num <= 5)
		param[1] = 0x4B;
	else if (num > 5 && num <= 8)
		param[1] = 0x1B;*/

	num = num%6;
	if (num <= 2 || num > 3)
		param[1] = 0x00;
	else  if (num > 2 && num <= 3)
		param[1] = 0x01;
	

}

void sendTmpsData(void)
{
	static char resCmd = 0x20;
	unsigned char param[2] = {0};
	unsigned char len = 0;
	param[0] = 0x01;
	static int i = 0, m = 0, n = 0, j = 0;
	
	switch(resCmd)
	{
		case HALTOTPMS_FL_UPDATA:
			LOGD("[%s] i  ==========  [%d]", __FUNCTION__, i);
 			produceSimulativeData(i, param);
			i++;
			if (i >100)
				i = 0;
			break;
		case HALTOTPMS_FR_UPDATA: 
			LOGD("[%s] j  ==========  [%d]", __FUNCTION__, j);
			produceSimulativeData(j, param);
			j++;
			if (j >100)
				j = 0;
			break;
		case HALTOTPMS_RL_UPDATA:
			LOGD("[%s] m  ==========  [%d]", __FUNCTION__, m);
			produceSimulativeData(m, param);
			m++;
			if (m >100)
				m = 0;
			break;
		case HALTOTPMS_RR_UPDATA: 
			LOGD("[%s] n  ==========  [%d]", __FUNCTION__, n);
			produceSimulativeData(n, param);
			n++;
			if (n >100)
				n = 0;
			break;
		default:
			break;
	}
	//halToTPMS_TireSwapDispose(resCmd, param, len);
	analyseHalMessage_TPMS(resCmd, param, len);

	resCmd++;
	if (resCmd > 0x23)
		resCmd = 0x20;
}

int TimerHandlerCenter(timer_t timerId){

	switch((s64)timerId)
	{
		case TPMS_TIMER_HIDDEN:
			StopRing();
			break;
		case TPMS_TIMER_CTRL_ALARM_FRE:
			LOGD("TPMS_TIMER_CTRL_ALARM_FRE");
			localParam.bCanRing = true;
			break;
		case TPMS_TIMER_TEXTALARM:
			popAlarmTextIdToQueue();
			break;
		case TPMS_TIMER_RINGALARM:
			popAlarmRingIdToQueue();
			break;
		case TPMS_TIMER_SEND_THE_DATA_OF_TMPS:
			sendTmpsData();
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

    
    makeAndSendMessageToModule(MODULE_ID_TPMS,MODULE_ID_TIMER,buf,5);
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
    
    makeAndSendMessageToModule(MODULE_ID_TPMS,MODULE_ID_TIMER,buf,10);

    return 0;
}

int DeleteTimer(int timerId){
	
	u8 buf[5];
	
	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    makeAndSendMessageToModule(MODULE_ID_TPMS,MODULE_ID_TIMER,buf,5);
	//LOGD("DeleteTimer Success!");
    return 0;
}



