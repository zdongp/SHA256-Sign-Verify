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
#define OPEN_VOICE_ALARM_TIME_CUT				8000
#define EXTCAR_TIMER_TIME_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE		(60 * 1000)
#define EXTCAR_TIMER_TIME_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT		2000 //INSTANT_OIL_CONSUME_PLUS_TIMES

#define PLAY_ONE_AUDIO_FILE_NEED_TIME			3		//��SEC��

#define EXTCAR_TIMER_ID_CAR_SPEED_CHECK							0x01
#define EXTCAR_TIMER_ID_CAR_SPEED_CHECK_FINISH					0x02
#define EXTCAR_TIMER_ID_TEST									0x03
#define EXTCAR_TIMER_ID_AUTO_JUMP_TO_EXTCAR_PAGE_PROCESS		0x04
#define EXTCAR_TIMER_ID_PLAY_BACK_DOOR_AUDIO					0x05
#define EXTCAR_TIMER_ID_OPEN_VOICE_ALARM						0x06
#define EXTCAR_TIMER_ID_TOYOTA_PRADO_AVERAGE_OIL_CONSUME_UPDATE				0x07
#define EXTCAR_TIMER_ID_TOYOTA_PRADO_INSTANT_OIL_CONSUME_COUNT				0x08

#define TIME_3S_ 3000
#define EXTCAR_TIMER_ID_TOYOTA_CAMRY_SAVECARSETTINGPARAM_SHOWBOMBBOX				0x0a

#define TIME_MODE_FIRST_GOTO_MODE_PAGE 9000
#define TIME_MODE_GOTO_MODE_PAGE 4000
#define EXTCAR_TIMER_ID_GOLF_MODE_HIDEBOX				0x0b

#define EXTCAR_TIMER_ID_CORNERING_LAMP_TK			0x0c
#define TIME_EXTCAR_CORNERING_LAMP_TK 				400

#define EXTCAR_TIMER_ID_DANGER_WARNING_LAMP_TK	0x0d
#define TIME_EXTCAR_DANGER_WARNING_LAMP_TK 		400


typedef int (*timer_handler_function)(timer_t timerId);
void  initTimerCenter(timer_handler_function func);

void processCarSpeedCheck(void);

int TimerHandlerCenter(timer_t timerId);

int SetTimer(int nElaspe_ms, int nMode, int timerId);

int DeleteTimer(int timerId);

