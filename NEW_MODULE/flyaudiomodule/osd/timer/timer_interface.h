#ifndef __TIMER_INTERFACE_H__
#define __TIMER_INTERFACE_H__

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


#define SIGMYTIMER (SIGRTMAX-SIG_OSD) 
//////////////////////////////////
#define OSD_TIMER_DROP_DOWN_DISPLAY   		0x01
#define OSD_TIMER_OSD_PAGE_DISPLAY          0x02
#define OSD_TIMER_SETTING_VIDEO             0x03
#define OSD_TIMER_COME_IN_BACK_CAR          0x04

#define OSD_TIMER_DROP_DOWN_SWITCH          0xff




#define  TIMEOUT_HIDE_SUBTITLE   2000//��������osd�ļ��ʱ��
#define  TIMEOUT_HIDE_OSDPAGE    5000//����osdҳ�ļ��ʱ��
#define  OSDTIME_DROP_DOWN_SWITCH 13000
///////////////////////////////////
//#define OSD_TIMER_VOL_DROP_DOWN_DISPLAY		0x01
//#define OSD_TIMER_BARCODE_DISPLAY           0x03
//
//
//
//#define OSD_TIMER_LOWBETTERY_CHICK           0x04  // jing  2013-8-12 bettery state chick
//#define OSD_TIMER_LOWBETTERY_DISPLAY           0x05  // jing  2013-8-12 low bettery osd
//#define OSD_TIMER_LOWBETTERY_OSD_CLOSE           0x06  // jing  2013-8-12 close low bettery osd
//#define OSD_TIMER_PAGE_DISPLAY              0x07

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




#endif
