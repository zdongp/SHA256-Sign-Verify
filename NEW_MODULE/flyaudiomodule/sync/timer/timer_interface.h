#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <string.h> 
#include <time.h> 

#include "global.h"


#define SIG_OSD		0x00
#define SIG_DVD		0x01
#define SIG_SYS		0x02
#define SIG_AV		0x03
#define	SIG_RADIO	0x04

#define SIGMYTIMER (SIGRTMAX-SIG_DVD) 

#define sync_time 1


typedef int (*timer_handler_function)(timer_t timerId);
void initTimerCenter(timer_handler_function func);
int TimerHandlerCenter(timer_t timerId);
int SetTimer(int nElaspe_ms, int nMode, int timerId);
int DeleteTimer(int timerId);



