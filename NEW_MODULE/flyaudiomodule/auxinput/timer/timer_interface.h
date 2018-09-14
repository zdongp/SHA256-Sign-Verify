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
#define SIG_BT		0x05
#define SIG_TV		0x07
#define SIG_AUX		0x09


#define TIME_5S			5000

#define SIGMYTIMER (SIGRTMAX-SIG_AUX) 
#define OSD_TIMER_VOL_DROP_DOWN_DISPLAY		0x02



#define AUX_OSD_TIMER_HIDDEN_DISPLAY   		0x00

typedef int (*timer_handler_function)(timer_t timerId);
void initTimerCenter(timer_handler_function func);
int TimerHandlerCenter(timer_t timerId);

//mode: 0: oneshot timer; 1: periodicity timer 
int SetTimer(int nElaspe_ms, int nMode, int timerId);

int DeleteTimer(int timerId);


