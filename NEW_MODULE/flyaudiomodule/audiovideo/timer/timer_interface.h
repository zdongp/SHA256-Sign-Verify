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

#define SIGMYTIMER (SIGRTMAX-SIG_AV) 


#define GPS_SOUND_TIMER			0x00
#define SOUND_DELAY_TIMER			0x01
#define TIMER_ID_DELAY_CLOSE_VIDEO	0x02


#define TIMER_CYCLE_DELAY_CLOSE_VIDEO	1000

#define TIMER_ID_ENABLE_MIXVOICE	0x03
#define TIMES_ENABLE_MIXVOICE	3500

#define TIMER_ID_IS_SUPPORT_USB_CAMERA	0x04

#define TIMES_IS_SUPPORT_USB_CAMERA	200
#define TIMER_ID_IS_SUPPORT_USB_CAMERA_TIMEOUT	0x05
#define TIMES_IS_SUPPORT_USB_CAMERA_TIMEOUT 4000

#define TIMER_ID_STOP_DUEROS	0x06
#define TIMES_IS_STOP_DUEROS 800

#define TIMER_ID_IS_SET_LOGO_DISAPPEARS	0x07
#define TIMER_ID_IS_SET_LOGO_DISAPPEARS_TIME	3500
#if 0

typedef void (*TimerRoutine)(int signo, siginfo_t* info, void* context);

void TimerHandler(int signo, siginfo_t* info, void* context);
void initTimer(TimerRoutine timerRoutine);

#else
typedef int (*timer_handler_function)(timer_t timerId);
void initTimerCenter(timer_handler_function func);
int TimerHandlerCenter(timer_t timerId);
#endif 

//mode: 0: oneshot timer; 1: periodicity timer 
int SetTimer(int nElaspe_ms, int nMode, int timerId);

int DeleteTimer(int timerId);
