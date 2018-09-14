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
#define SIG_TPMS    0x08

#define TIME_5S			5000
#define TIME_TPMS_RING_FRE_15S		15000

#define SIGMYTIMER (SIGRTMAX-SIG_TPMS) 

#define TPMS_TIMER_HIDDEN   		0x00
#define TPMS_TIMER_CTRL_ALARM_FRE		0x01
#define TPMS_TIMER_TEXTALARM        0x02
#define TPMS_TIMER_RINGALARM        0x03
/*<<<<<<<<<------------[BEN] add---use to simulate send the data of tmps-----------*/
#define TIME_500MS		500
#define TPMS_TIMER_SEND_THE_DATA_OF_TMPS	0X04
/*----------------------------------END----------------------->>>>>>>>>>>>*/
void sendTmpsData(void);
typedef int (*timer_handler_function)(timer_t timerId);
void  initTimerCenter(timer_handler_function func);

int TimerHandlerCenter(timer_t timerId);

int SetTimer(int nElaspe_ms, int nMode, int timerId);

int DeleteTimer(int timerId);

