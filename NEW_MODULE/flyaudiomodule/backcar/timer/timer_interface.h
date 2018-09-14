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

#define TIME_5S			5000

#define BACK_OSD_TIMER_HIDDEN_DISPLAY   		0x06


#if 0 

typedef void (*TimerRoutine)(int signo, siginfo_t* info, void* context);

//timer_t getTimerID(int timerIDindex);

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
