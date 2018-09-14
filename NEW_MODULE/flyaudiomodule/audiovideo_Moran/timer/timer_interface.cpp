#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#include "global.h"
#include "timer_interface.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"
#include "appRequestFunction.h"
#include "appRequestCommand.h"

#include "moduleParamRequest.h"
#include "halRequestFunction.h"

#include "otherModuleRequestFunction.h"
#include "otherModuleRequestCommand.h"

#include "otherModuleResponseFunction.h"
#include <commonFunc.h>


int TimerHandlerCenter(timer_t timerId){

		switch((s64)timerId)
		{
			case GPS_SOUND_TIMER:
			{
				pLocalParam->preGpsSoundState = 0;
	
				u16 curpage = 0;
				u16 prepage = 0;
				u8 curpagelen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&curpage,&curpagelen);
	
				if(!pLocalParam->gpsSoundState){
					pLocalParam->canNotSetMixedNaviVoice = pLocalParam->canNotSetMixedNaviVoice & ~MIXED_NAVI_VOICE_STATE_GPS;
					if(!pLocalParam->canNotSetMixedNaviVoice) {
						//audioToHal_SetMixedNaviVoice(0);//
					}
						
					LOGD("soundcardSoundState:%x curpage:%x b_MediaPlaying:%x pLocalParam->b_mixsound=%d",pLocalParam->soundcardSoundState,curpage,pLocalParam->b_MediaPlaying,pLocalParam->b_mixsound);
					if(pLocalParam->soundcardSoundState && curpage == (u16)PAGE_THIRD_PAGE && !pLocalParam->b_MediaPlaying
					&& (pLocalParam->b_mixsound==false)){
						audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(pLocalParam->soundChannel, CHANNEL_THREECHANNEL);
	
						u8 c3G_DIAL = 0;
						u8	c3G_DIALLen = 0;
						getOtherModuleParam(MODULE_ID_SYSTEM,DIALIN_3G,(u8*)&c3G_DIAL,&c3G_DIALLen);
						LOGD("c3G_DIAL %x",c3G_DIAL);
						if(!c3G_DIAL && !pLocalParam->b_IsRequestvoice_state)
							moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_THREECHANNEL);
	
					}
					else if(pLocalParam->soundcardSoundState &&
						pLocalParam->soundVideoChannel != CHANNEL_THREECHANNEL &&
						pLocalParam->soundVideoChannel != CHANNEL_MP3 ){
						setRingerCtrl(0xFF);	// play
					}
				}		
				else
				{
				}
				pLocalParam->gpsSoundTimerING = 0;
			}
			break;
			case SOUND_DELAY_TIMER:
			{
				//audioToHal_SetMixedNaviVoice(0); //
			}
			break;
			case TIMER_ID_DELAY_CLOSE_VIDEO:
			{
				LOGD("[%s] TIMER_CYCLE_DELAY_CLOSE_VIDEO", __FUNCTION__);
				moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(pLocalParam->soundVideoChannel);
			}
			break;
			case TIMER_ID_ENABLE_MIXVOICE:
			{
				LOGD("[%s] TIMER_ID_ENABLE_MIXVOICE", __FUNCTION__);
				audioToHal_EnableMixVoice(1);
				audioVideoToModule_NotifyOSD_SendOsdDebugInfo();
			}
			break;
			case TIMER_ID_IS_SUPPORT_USB_CAMERA_TIMEOUT:
			{
				DeleteTimer(TIMER_ID_IS_SUPPORT_USB_CAMERA);
				DeleteTimer(TIMER_ID_IS_SUPPORT_USB_CAMERA_TIMEOUT);
			}
			break;
			case TIMER_ID_IS_SUPPORT_USB_CAMERA:
			{
				if(pLocalParam->bIsSupportUsbCamera)
				{

					DeleteTimer(TIMER_ID_IS_SUPPORT_USB_CAMERA);
					audioVideoToModule_NotifySystem_StartGPS();
					if(pLocalParam->savemode == CHANNEL_MP3){
						usleep(1500*1000);
					}
					
					char property[PROPERTY_VALUE_MAX];
					property_set(LIDBG_HOLD_HOOTANIM,"false");
				}
			}
			break;
			case TIMER_ID_STOP_DUEROS:
			{
				u16 wPageId = 0;
				u8 curpagelen = 0;
				getOtherModuleParam(MODULE_ID_SYSTEM,CUR_PAGE,(u8*)&wPageId,&curpagelen);
				if(wPageId != PAGE_SPEECH_APP_MEDIA && pLocalParam->soundVideoChannel == CHANNEL_SPEECH_MEDIA_CTRL)
				{
					if (isInThePageWithSoundChannel(wPageId))
					{
						LOGD("[%s] 20150406 page id = [%x]", __FUNCTION__, wPageId);
						audioVideoToModule_NotifySystem_JumpPage(PAGE_MENU);
					}
						
					u8 ucBackMode = 0;
					int paramLen=0;
					getOtherModuleParam(MODULE_ID_BACK,BACK_CAR_STATE,&ucBackMode,(u8*)&paramLen);
					if(ucBackMode != 0x01)
					{
						if (pLocalParam->soundVideoChannel != CHANNEL_THREECHANNEL)
							moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_THREECHANNEL);
					
						int nRet = isInThePageOfDnvOrDvr(wPageId);
						
						if (nRet == 1)//dnv
						{
							moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DNV_VIDEO);
						}
						else if(nRet == 2)//dvr
						{
							moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(CHANNEL_DVR_VIDEO);
						}
					}
				}
			}
			break;
			case TIMER_ID_IS_SET_LOGO_DISAPPEARS:
			{
				char property[PROPERTY_VALUE_MAX];
				property_set(LIDBG_HOLD_HOOTANIM,"false");
				LOGD("[ACCON_Set LOGO Hide!!]");
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


    makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_TIMER,buf,5);
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
    
    makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_TIMER,buf,10);


    return 0;
}

int DeleteTimer(int timerId){
	u8 buf[5];

	buf[0] = 0x30;
	buf[1] = (timerId >> 24) & 0xFF;
    buf[2] = (timerId >> 16) & 0xFF;
    buf[3] = (timerId >> 8) & 0xFF;
    buf[4] = timerId & 0xFF;

    makeAndSendMessageToModule(MODULE_ID_AUDIOVIDEO,MODULE_ID_TIMER,buf,5);

    return 0;
}
