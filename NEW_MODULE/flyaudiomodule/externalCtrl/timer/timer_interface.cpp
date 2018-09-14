
#include <stdlib.h>
#include "global.h"
#include "timer_interface.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "otherModuleRequestCommand.h"


int TimerHandlerCenter(timer_t timerId)
{
	switch((s64)timerId)
	{
		case TIMERID_FLY_EXTERNALCTRL_END_SPEECH:
		{
			unsigned short icurSound = 0;
			u8 icurSoundLen = 0;
			getOtherModuleParam(MODULE_ID_AUDIOVIDEO,SOUND_CHANNEL,(u8 *)&icurSound,&icurSoundLen);
			LOGD("[%s] icurSound = [%x]", __FUNCTION__, icurSound);
			if(icurSound == CHANNEL_SPEECH_MEDIA_CTRL)
			{
				ExternalCtrlToAudiovideo_EndSpeechToThelastAudioChannel(0x01);
			}
		}
		break;
		default:break;
	}

	return 0;
}

void initTimerCenter(timer_handler_function func){
	u8 buf[] = {0x10,0x00,0x00,0x00,0x00};

    buf[1] = ((u64)func >> 24) & 0xFF;
    buf[2] = ((u64)func >> 16) & 0xFF;
    buf[3] = ((u64)func >> 8) & 0xFF;
    buf[4] = (u64)func & 0xFF;


    makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_TIMER,buf,5);
}

int SetTimer(int nElaspe_ms, int nMode, int timerId){
	u8 buf[10];

	buf[0] = 0x20;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;
    
    buf[5] = (nElaspe_ms >> 24) & 0xFF;
    buf[6] = (nElaspe_ms >> 16) & 0xFF;
    buf[7] = (nElaspe_ms >> 8) & 0xFF;
    buf[8] = nElaspe_ms & 0xFF;

	buf[9] = (u8)nMode;
    
    makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_TIMER,buf,10);


    return 0;
}

int DeleteTimer(int timerId){
	u8 buf[5];

	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;

    makeAndSendMessageToModule(MODULE_ID_EXTERNALCTRL,MODULE_ID_TIMER,buf,5);

    return 0;
}
