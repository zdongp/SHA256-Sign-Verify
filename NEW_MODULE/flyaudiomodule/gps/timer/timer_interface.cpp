#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 

#include "global.h"
#include "timer_interface.h"


timer_t timerIDList[20]; //use to save timer id;

void TimerHandler(int signo, siginfo_t* info, void* context){
	LOGD("+++++++++++++++++Timer arrived++++++++++++++TimerID%d", *(int*)(info->si_value.sival_ptr));
	if (signo != SIGMYTIMER) 
		return; 
	int nTimerID = *(int*)info->si_value.sival_ptr;
}
void initTimer(TimerRoutine timerRoutine){
	struct sigaction sysact; 
	memset(timerIDList, -1, 20);
	
	//setup signal handler 
	sigemptyset(&sysact.sa_mask); 
	sysact.sa_flags = SA_SIGINFO; 
	sysact.sa_sigaction = timerRoutine ; 
	sigaction(SIGMYTIMER, &sysact, NULL); 
}


//mode: 0: oneshot timer; 1: periodicity timer
int SetTimer(int nElaspe_ms, int nMode, int timerId)
{ 
	struct sigevent evp; 
	
	timer_delete(timerIDList[timerId]);

	timerIDList[timerId] = (timer_t)-1;
	
	evp.sigev_notify = SIGEV_SIGNAL; 
	evp.sigev_signo = SIGMYTIMER; 
	evp.sigev_value.sival_ptr = &timerIDList[timerId]; 
	int nCreate = timer_create(CLOCK_REALTIME, &evp, &timerIDList[timerId]); 
	
	if (nCreate == 0){ //success 
		struct itimerspec value; 
		struct itimerspec ovalue; 

		value.it_value.tv_sec = nElaspe_ms / 1000; 
		value.it_value.tv_nsec = (nElaspe_ms % 1000) * (1000 * 1000); 

		if (nMode == 1) { 
			value.it_interval.tv_sec = value.it_value.tv_sec; 
			value.it_interval.tv_nsec = value.it_value.tv_nsec; 
		} 
		else{ 
			value.it_interval.tv_sec = 0; 
			value.it_interval.tv_nsec = 0; 
		} 

		if (timer_settime(timerIDList[timerId], 0, &value, &ovalue) == 0){ //success 
			LOGD("timerID:%d, nElaspe_ms:%d", timerIDList[timerId], nElaspe_ms);
		} 
	} 
	else {
		LOGD("create timer error");
		
		return -1;
	} 

	return (s64)timerIDList[timerId];

	//return timerIDList[nTimerIndex++]; 
}

int DeleteTimer(int timerId){
	LOGD("+++++++++++++++++++++++++++DeleteTimer+++++++++++++++++");
	int ret = -1;

	ret = timer_delete(timerIDList[timerId]);

	timerIDList[timerId] = (timer_t)-1;
	
	return ret;
}
