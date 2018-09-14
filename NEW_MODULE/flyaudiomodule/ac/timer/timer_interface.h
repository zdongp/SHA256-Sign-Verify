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

#define CAR_SPEED_CHECK_TIME_CUT				1000
#define CAR_SPEED_CHECK_FINISH_TIME_CUT			15000
#define AUTO_JUMP_TO_EXTCAR_PAGE_STATE_TIME		10000
#define OPEN_VOICE_ALARM_TIME_CUT					15000

#define PLAY_ONE_AUDIO_FILE_NEED_TIME			3		//£¨SEC£©

//byd
#define AC_TIMER_ID_BYD_AC_DO_NOT_SHOW							0x07
#define AC_TIMER_ID_TEST_CAN_RUN								0x08

//golf
#define GOLF_AC_TIMER_ID_AC_DATA_TIMER_TO_OSD			0x09	
#define GOLF_AC_TIMER_CYCLE_AC_DATA_TIMER_TO_OSD		5000	//ms

void setTimerAcDataTimeToOSD(void);
void killTimerAcDataTimeToOSD(void);

typedef int (*timer_handler_function)(timer_t timerId);
void  initTimerCenter(timer_handler_function func);
int TimerHandlerCenter(timer_t timerId);
int SetTimer(int nElaspe_ms, int nMode, int timerId);
int DeleteTimer(int timerId);

