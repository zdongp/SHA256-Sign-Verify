#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 

#include "global.h"

#define TIMERID_FLY_EXTERNALCTRL_END_SPEECH   0x01
#define TIMERS_FLY_EXTERNALCTRL_END_SPEECH   500


typedef int (*timer_handler_function)(timer_t timerId);
void initTimerCenter(timer_handler_function func);
int TimerHandlerCenter(timer_t timerId);

int SetTimer(int nElaspe_ms, int nMode, int timerId);

int DeleteTimer(int timerId);
