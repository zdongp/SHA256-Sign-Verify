#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#include "global.h"
#include "otherModuleResponseCommand.h"
#include "otherModuleResponseFunction.h"

extern moduleid_t locale_module_mid();
#include "halRequestFunction.h"


#define TIMER_MAX	2048
#define MY_INVALID_TIMER_ID	0xFFFFFFFF

typedef struct timer_id_list
{
	timer_t id;
	unsigned char moduleID;
	unsigned int index;
	int repeate_cnt;
	int nElaspe_ms;
}timer_id_list_t;


timer_id_list_t timerId[256] = {0};
static int number=0;

timer_t SetTimer(timer_id_list_t *pTimerId, int nElaspe_ms);
int DeleteTimer(timer_id_list_t *pTimerId);

void TimerHandleThread(union sigval v){
	timer_id_list_t *pTimerId = (timer_id_list_t *)v.sival_ptr;

	DeleteTimer(pTimerId);

	TimerModuleToTimerMessage(locale_module_mid(), pTimerId->moduleID, pTimerId->index);

	if(pTimerId->repeate_cnt > 1)
	{
		pTimerId->repeate_cnt--;
		SetTimer(pTimerId, pTimerId->nElaspe_ms);
	}
	else if(pTimerId->repeate_cnt == 0)
	{
		SetTimer(pTimerId, pTimerId->nElaspe_ms);
	}
}


timer_t SetTimer(timer_id_list_t *pTimerId, int nElaspe_ms){
	struct sigevent evp;

	pTimerId->id = (timer_t)MY_INVALID_TIMER_ID;

	memset(&evp, 0, sizeof(struct sigevent));
	evp.sigev_notify = SIGEV_THREAD;
	evp.sigev_notify_function = TimerHandleThread;
	evp.sigev_value.sival_ptr = pTimerId;

	int nCreate = timer_create(CLOCK_MONOTONIC, &evp, &(pTimerId->id));

	if (nCreate == 0){ //success
		struct itimerspec value;

		value.it_value.tv_sec = nElaspe_ms / 1000;
		value.it_value.tv_nsec = (nElaspe_ms % 1000) * (1000 * 1000);
		value.it_interval.tv_sec = 0;
		value.it_interval.tv_nsec = 0;

		if (timer_settime(pTimerId->id, 0, &value, NULL) != 0){ //success
			LOGD("[%s] timer_settime fail pTimerId->id = [%x] ", __FUNCTION__, pTimerId->id);
		}
	}
	else {
		LOGD("create timer error");
		return (timer_t)MY_INVALID_TIMER_ID;
	}

	return pTimerId->id;
}


int DeleteTimer(timer_id_list_t *pTimerId){

	if (NULL == pTimerId)
		return -1;

	int ret = -1;
    LOGD("[%s] pTimerId->id:%x pTimerId->moduleID:%x",__FUNCTION__,pTimerId->id,pTimerId->moduleID);

	if (pTimerId->id == (timer_t)MY_INVALID_TIMER_ID)
		return -1;

	ret = timer_delete(pTimerId->id);

	if(!ret){
		pTimerId->id = (timer_t)MY_INVALID_TIMER_ID;
	}

	return ret;
}


void SetTimerCenter(unsigned char moduleId, unsigned int index, int nElaspe_ms, int repeate_cnt){
	int i;
	for(i = 0; i < number; i++){
		if((moduleId == timerId[i].moduleID) && (index == timerId[i].index)){
			DeleteTimer(&timerId[i]);
			timerId[i].repeate_cnt = repeate_cnt;
			timerId[i].nElaspe_ms = nElaspe_ms;
			SetTimer(&timerId[i], nElaspe_ms);
			return;
		}
	}
	
	if(number < TIMER_MAX - 1)
	{
		timerId[number].moduleID = moduleId;
		timerId[number].index = index;
		timerId[number].repeate_cnt = repeate_cnt;
		timerId[i].nElaspe_ms = nElaspe_ms;

		timerId[number].id = (timer_t)MY_INVALID_TIMER_ID;

		SetTimer(&timerId[number], nElaspe_ms);

		number++;
	}
}

void DeleteTimerCenter(unsigned char moduleId, unsigned int index){
	int i;

	for(i = 0; i < number; i++){
		if((moduleId == timerId[i].moduleID) && (index == timerId[i].index)){
			DeleteTimer(&timerId[i]);
			return;
		}

	}
	LOGD("[%s] delete error! Do not find the timer id", __FUNCTION__);
}


void otherModuleInit(void){

}

void otherModuleDeInit(void){

}

void analyseOtherModuleMessage(moduleid_t sendModuleId, u8 *param, u8 len){


	unsigned char cmd = param[0];
	LOGI("Module_timer cmd:%x sendModuleId:%x",cmd,sendModuleId);
	
	switch(cmd){
		case 0x20:	// SetTimer
			{
				unsigned int index = 0;
				index += (param[1] << 24) & 0xFF000000;
				index += (param[2] << 16) & 0x00FF0000;
				index += (param[3] << 8) & 0x0000FF00;
				index += param[4] & 0xFF;

				int mstimer = 0;
				int repeate_cnt=0;
				mstimer += (param[5] << 24) & 0xFF000000;
				mstimer += (param[6] << 16) & 0x00FF0000;
				mstimer += (param[7] << 8) & 0x0000FF00;
				mstimer += param[8] & 0xFF;

				repeate_cnt = param[9];

				LOGD("settimer:timerId:%d, ms:%d repeate_cnt:%d", index, mstimer,repeate_cnt);
				SetTimerCenter(sendModuleId, index, mstimer, repeate_cnt);
			}
			break;
		case 0x30:	// DeleteTimer
			{
				unsigned int index = 0;
				index += (param[1] << 24) & 0xFF000000;
				index += (param[2] << 16) & 0x00FF0000;
				index += (param[3] << 8) & 0x0000FF00;
				index += param[4] & 0xFF;
				LOGD("deleteTimer:timer:%d", index);
				DeleteTimerCenter(sendModuleId, index);
			}
			break;
		default:break;
	}


}
