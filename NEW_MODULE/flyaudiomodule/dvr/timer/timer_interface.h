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


#define TIME_5S			5000

#define SIGMYTIMER (SIGRTMAX-SIG_TV) 
#define DVR_OSD_TIMER_HIDDEN_DISPLAY   		0x00
#define OSD_TIMER_VOL_DROP_DOWN_DISPLAY		0x02
#define TIMER_ID_SYNC_TIME_TO_DVR			3


#define TIMER_CYCLE_SYNC_TIME_TO_DVR		2000		//ms

#define SYNC_DNV_TIME_CYCLE				15		//s

#define SYNC_DVR_TIME_TIMES						4
#define DVR_USB_CAMERY_NO_SDCARD		5

#define DVR_USB_CAMERY_NO_SURPORTS_DOUBLE_RECORDING 7

typedef int (*timer_handler_function)(timer_t timerId);
void initTimerCenter(timer_handler_function func);
int TimerHandlerCenter(timer_t timerId);

int SetTimer(int nElaspe_ms, int nMode, int timerId);

int DeleteTimer(int timerId);

