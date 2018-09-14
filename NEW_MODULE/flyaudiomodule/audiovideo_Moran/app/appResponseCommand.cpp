#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "param.h"
#include "halRequestFunction.h"

#include "appResponseFunction.h"
#include "appResponseCommand.h"


void appInit(void){

}

void appDeInit(void){

}

void analyseAppMessage(unsigned char *buffer, unsigned char len){
	int ctrlId = 0;
	char ctrlType;
	unsigned char paramLen;
	unsigned char *param;
	
	static int mute_flag = 1;

	ctrlId += (int)((buffer[0] << 24) & 0xFF000000);
	ctrlId += (int)((buffer[1] << 16) & 0xFF0000);
	ctrlId += (int)((buffer[2] << 8) & 0xFF00);
	ctrlId += (int)(buffer[3] & 0xFF);

	ctrlType = buffer[4];
	paramLen = len - 5;
	param = &buffer[5];

	LOGD(" Module_audiovideo analyseAppMessage ctrlType %x ctrlId %x ",ctrlType,ctrlId);
	switch(ctrlId){
	///////////////////////////////////AUDIOVIDE EQ PAGE////////////////////////////////////////////////
 		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 0:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 1:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 2:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 3:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 4:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 5:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 6:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 7:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 8:
		case CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + 9: 
			if(ctrlType == UIACTION_MOUSEUP){
				int index = ctrlId - CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN;
				appToAudioVideo_EQ_Gauge_MouseUp(index,param, paramLen);
			}
			break;

		case CONTROLID_EQ_CALSSICAL:
		case CONTROLID_EQ_POP:
		case CONTROLID_EQ_RESET:
		case CONTROLID_EQ_ROCK:
		case CONTROLID_EQ_JAZZ:
		case CONTROLID_EQ_TURNOFF:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudio_SurroundIndex_MouseUp(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudio_SurroundIndex_MouseDown(ctrlId);
			}
			break;
			
		case CONTROLID_EQ_RECORD_1:
		case CONTROLID_EQ_RECORD_2:
		case CONTROLID_EQ_RECORD_3:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudio_SurroundIndex_MouseUp(ctrlId);
				appToAudio_SurroundIndex_MouseDown(ctrlId);
			}
			else if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_EQ_SaveUser(ctrlId - CONTROLID_EQ_RECORD_1 + 1);
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				//appToAudio_SurroundIndex_MouseDown(ctrlId);
			}
			break;
		case CONTROLID_EQ_SOUND:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_EQ_Sound();
			}
			break;
		//case CONTROLID_EQ_EQ:
		//	if(ctrlType == UIACTION_MOUSEUP){
		//		appToAudioVideo_EQ_Eq();
		//	}
		//	break;
		case CONTROLID_EQ_BACK:{
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_EQ_Back();
			}
			}
			break;
			
	///////////////////////////////////AUDIOVIDEO SOUND PAGE////////////////////////////////////////////		
		case CONTROLID_AUDIO_LOUD_DEC:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Audio_LoudDec_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_Audio_LoudDec_MouseDown();
			}
			
			break;
		case CONTROLID_AUDIO_LOUD_INC:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Audio_LoudInc_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_Audio_LoudInc_MouseDown();
			}
			
			break;
			
		case CONTROLID_AUDIO_TREB_DEC:
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_TrebDec_MouseTimer();
			}else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_TrebDec_MouseUp();
				}else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_TrebDec_MouseDown();
				}
			}
			break;
		case CONTROLID_AUDIO_TREB_INC:
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_TrebInc_MouseTimer();
			}else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_TrebInc_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_TrebInc_MouseDown();
				}
			}
			break;
			
		case CONTROLID_AUDIO_MID_DEC:
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_MidDec_MouseTimer();
			}else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_MidDec_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_MidDec_MouseDown();
				} 
			}
			break;
		case CONTROLID_AUDIO_MID_INC:
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_MidInc_MouseTimer();
			}else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_MidInc_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_MidInc_MouseDown();
				}
			}
			break;
			
		case CONTROLID_AUDIO_BASS_DEC:
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_BassDec_MouseTimer();
			}
			else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_BassDec_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_BassDec_MouseDown();
				}
			}
			break;
		case CONTROLID_AUDIO_BASS_INC:
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_BassInc_MouseTimer();
			}else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_BassInc_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_BassInc_MouseDown();
				}
			}
			break;
			
		case CONTROLID_AUDIO_LEFT:
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_Left_MouseTimer();
			}else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_Left_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_Left_MouseDown();
				}
			}
			break;
		case CONTROLID_AUDIO_RIGHT: 
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_Right_MouseTimer();
			}else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_Right_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_Right_MouseDown();
				}
			}
			break;
		case CONTROLID_AUDIO_FRONT:
			if(ctrlType == UIACTION_MOUSETIMER){
				appToAudioVideo_Audio_Front_MouseTimer();
			}else{
				if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_Front_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_Front_MouseDown();
				}
			}
			break;
		case CONTROLID_AUDIO_REAR:
			{
				if(ctrlType == UIACTION_MOUSETIMER){
					appToAudioVideo_Audio_Rear_MouseTmier();
				}
				else if(ctrlType == UIACTION_MOUSEUP){
					appToAudioVideo_Audio_Rear_MouseUp();
				}
				else if(ctrlType == UIACTION_MOUSEDOWN){
					appToAudioVideo_Audio_Rear_MouseDown();
				}
			}
			break;
		case CONTROLID_AUDIO_LISTENPOS:	
			appToAudioVideo_Audio_TouchListen(param, paramLen);
			break;
		case CONTROLID_AUDIO_SCROLLBAR_LISTENPOS:
			{
				if(ctrlType == UIACTION_MOUSETIMER || ctrlType == UIACTION_MOUSEDOWN){
					appToAudio_Scrollbar_faderBalance(param, paramLen);
				}
				else if(ctrlType == UIACTION_MOUSEUP)
				{
					UI_Scrollbar_faderBalanceValue();
				}
			}
			break;
		case CONTROLID_AUDIO_PARAM_RESET:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Audio_Param_Reset();
			}
			break;
		case CONTROLID_AUDIO_TREB_GAUGE:		// TEXT
		case CONTROLID_AUDIO_MID_GAUGE:			// TEXT
		case CONTROLID_AUDIO_LOUD_GAUGE:		// TEXT
		case CONTROLID_AUDIO_BASS_GAUGE:		// TEXT
			break;

		////////////////左边的五个选择频率的按钮///////////////
		case CONTROLID_AUDIO_LOUD_FREQ:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Audio_LoudFreq_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_Audio_LoudFreq_MouseDown();
			}

			break;
		case CONTROLID_AUDIO_TREB_FREQ:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Audio_TrebFreq_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_Audio_TrebFreq_MouseDown();
			}
			break;
		case CONTROLID_AUDIO_MID_FREQ:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Audio_MidFreq_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_Audio_MidFreq_MouseDown();
			}

			break;
		case CONTROLID_AUDIO_BASS_FREQ:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Audio_BassFreq_MouseUp();
			}
			else if(ctrlType == UIACTION_MOUSEDOWN){
				appToAudioVideo_Audio_BassFreq_MouseDown();
			}

			break;
		case CONTROLID_AUDIO_EQ:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudioVideo_Audio_Eq();
			}
			break;
		case CONTROLID_AUDIO_BACK:
			if(ctrlType == UIACTION_MOUSEUP)
				appToAudioVideo_Audio_Back();
			break;
		case CONTROLID_MENU_AUDIO:
			if(ctrlType == UIACTION_MOUSEUP)
				appToAudioVideo_MENUAudio();
			break;
		//case CONTROLID_DVD_MAIN_MUTE:
		//case CONTROLID_AUDIO_RADIO_MUTE:
		case CONTROLID_AUDIO_DVD_MUTE:
			if(ctrlType == UIACTION_MOUSEUP)
				if(pLocalParam->mute){
					audioToHal_SetMute(0);
				}
				else{
					audioToHal_SetMute(1);
				}
			break;
		case CONTROLID_AUDIO_EQUAL_LOUDNESS_ON_OFF:
			appToAudio_SetLoudnessSwith();
			break;
		case CONTROLID_AUDIO_MEDIA_MIX_ON_OFF:
			appToAudio_SetMix_On_Off();
			break;

		case CONTROLID_AUDIO_ASL:
			clickPradoAsl(ctrlType);
			break;
		case CONTROLID_AUDIO_PARK_SURROUND:
			clickPradoSurround(ctrlType);
			break;
		case CONTROLID_AUDIO_SET:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudio_Eq_Set();
			}
			break;
		case CONTROLID_AUDIO_SET_BOX:
			if(ctrlType == UIACTION_MOUSEUP){
				appToAudio_Eq_Set_box();
			}
			break;
		case CONTROLID_AUDIO_SET_PARAM_UP:
		case CONTROLID_AUDIO_SET_PARAM_DOWN:
			if(ctrlType == UIACTION_MOUSEUP)
			{
				clickAudioDataSet(ctrlId - CONTROLID_AUDIO_SET_PARAM_UP);
			}
			break;
		case CONTROLID_AUDIO_SET_PARAM_BACK:
			audioVideoToModule_NotifySystem_JumpPrePage();
			break;
		case CONTROLID_AUDIO_JUMP_CUR_MEDIA:
			audioVideoToModule_NotifySystem_JumpToCurMediaPage();
			break;
		default:break;
	}
}
