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
#define SIG_BT		0x05
#define SIG_TV		0x07
#define SIG_AUX		0x09


#define TIME_5S			5000

#define SIGMYTIMER (SIGRTMAX-SIG_AUX) 
#define OSD_TIMER_VOL_DROP_DOWN_DISPLAY		0x02

#define OSD_TIMER_BARCODE_SYS_DISPLAY       0x04
#define DVD_SWITCH_TIMERID                  0x05
#define AUX_TIME_DISPLAY                    0x06
#define STANDY_TIMER                        0x07
#define SYNC_PAGE                           0x08
#define APP_TIMER                           0x09

#define ACCON_STOP_DYNAMICLOGO				0x0a

//#define SYSTEM_JUMP_TIMER					0x10
//#define SYSTEM_ACC_ON						0x11
#define MCU_CLOSING_BOX						0x12
#define TIMES_MCU_CLOSING_BOX				3000
#define MCU_PAGE_TIMEOUT					0x13
#define TIMES_MCU_PAGE_TIMEOUT				15000


#define FLY_SET_NEEDLAUNCH			"fly.set.needlaunch" //是否是在第三方休眠下去

typedef int (*timer_handler_function)(timer_t timerId);
void initTimerCenter(timer_handler_function func);
int TimerHandlerCenter(timer_t timerId);

//mode: 0: oneshot timer; 1: periodicity timer 
int SetTimer(int nElaspe_ms, int nMode, int timerId);

int DeleteTimer(int timerId);
#endif

