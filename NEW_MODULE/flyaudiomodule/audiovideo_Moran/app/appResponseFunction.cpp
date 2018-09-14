#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "controlID.h"
#include "pageID.h"
#include "param.h"
#include "appRequestCommand.h"
#include "appResponseCommand.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "otherModuleRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleResponseFunction.h"

bool bScrBlVisible = true;
bool bScrFdVisible = true;
int Balance = 0;
int Fader = 0;

void appToAudioVideo_EQ_Gauge_MouseUp(char index, unsigned char *param, unsigned char len){
	int pos = 0;
	unsigned char nIndex = (unsigned char)index;
	pos += (int)((param[0] << 24) & 0xFF000000);
	pos += (int)((param[1] << 16) & 0xFF0000);
	pos += (int)((param[2] << 8) & 0xFF00);
	pos += (int)(param[3] & 0xFF);

	if(pLocalParam->EQValue[nIndex] == (unsigned char)pos)
		return;
		
	pLocalParam->EQValue[nIndex] = (unsigned char)pos;
	appToAudioVideo_cancelEQSeleted();
	LOGD("---appToAudioVideo_EQ_Gauge_MouseUp  -nIndex %x---%d-",nIndex,pLocalParam->EQValue[nIndex]);
	audioToHal_SetSingleEQValue(nIndex,pLocalParam->EQValue[nIndex]);
}

void appToAudio_SurroundIndex_MouseUp(int ctrlID){
	switch(ctrlID)
		{
			case CONTROLID_EQ_CALSSICAL:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_CLASS)
					audioToHal_SetInnerEQSetting(EQ_CLASS);
				break;
			case CONTROLID_EQ_POP:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_POP)
					audioToHal_SetInnerEQSetting(EQ_POP);
				break;
			case CONTROLID_EQ_RESET:
				if(pLocalParam->settingIndex != -1)
				{
					audioToHal_SetInnerEQSetting(EQ_NOCLASS);
					appToAudioVideo_EQ_Reset();
				}
				break;
			case CONTROLID_EQ_ROCK:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_ROCK)
					audioToHal_SetInnerEQSetting(EQ_ROCK);
				break;
			case CONTROLID_EQ_JAZZ:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_JAZZ)
					audioToHal_SetInnerEQSetting(EQ_JAZZ);
				break;
			case CONTROLID_EQ_TURNOFF:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_DEFAULT)
					audioToHal_SetInnerEQSetting(EQ_DEFAULT);
				break;
			case CONTROLID_EQ_RECORD_1:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_RECORD1)
					audioToHal_SetInnerEQSetting(EQ_RECORD1);
			break;
			case CONTROLID_EQ_RECORD_2:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_RECORD2)
					audioToHal_SetInnerEQSetting(EQ_RECORD2);
			break;
			case CONTROLID_EQ_RECORD_3:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_RECORD3)
					audioToHal_SetInnerEQSetting(EQ_RECORD3);
			break;
			default:break;
		}
	
}

void appToAudioVideo_EQ_SaveUser(char user){
	switch(user){
		case 0x01:{
			if(pLocalParam->imEQ == EQ_RECORD1)
				return;

			appToAudioVideo_displayEQType(EQ_RECORD1);
			audioToHal_SaveUserEQSetting(0x00);
			audioToHal_SetInnerEQSetting(EQ_RECORD1);

			//memcpy(pLocalParam->EQUser1,pLocalParam->EQValue,10);
			//audioToHal_SetEQAll(pLocalParam->EQUser1,10);
		}
		break;
		case 0x02:{
			if(pLocalParam->imEQ == EQ_RECORD2)
				return;
				
			appToAudioVideo_displayEQType(EQ_RECORD2);
			audioToHal_SaveUserEQSetting(0x01);
			audioToHal_SetInnerEQSetting(EQ_RECORD2);

			//memcpy(pLocalParam->EQUser2,pLocalParam->EQValue,10);
			//audioToHal_SetEQAll(pLocalParam->EQUser2,10);
		}
		break;
		case 0x03:{
			if(pLocalParam->imEQ == EQ_RECORD3)
				return;
				
			appToAudioVideo_displayEQType(EQ_RECORD3);
			audioToHal_SaveUserEQSetting(0x02);
			audioToHal_SetInnerEQSetting(EQ_RECORD3);

			//memcpy(pLocalParam->EQUser3,pLocalParam->EQValue,10);
			//audioToHal_SetEQAll(pLocalParam->EQUser3,10);
		}	
		break;
		default:break;
	}
}


void appToAudio_SurroundIndex_MouseDown(int ctrlID){
	setUpdateUI(false);
	pLocalParam->firstDisplayEQFlag = 0;
	LOGD("******************pLocalParam->preSettingIndexControl:%x;",pLocalParam->preSettingIndexControl);
	switch(ctrlID)
		{
			case CONTROLID_EQ_CALSSICAL:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_CLASS)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,1);
					setDigitalData(CONTROLID_EQ_POP,0);
					setDigitalData(CONTROLID_EQ_RESET,0);
					setDigitalData(CONTROLID_EQ_ROCK,0);
					setDigitalData(CONTROLID_EQ_JAZZ,0);
					setDigitalData(CONTROLID_EQ_TURNOFF,0);

					setDigitalData(CONTROLID_EQ_RECORD_1,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,0);
				}
				break;
			case CONTROLID_EQ_POP:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_POP)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,0);
					setDigitalData(CONTROLID_EQ_POP,1);
					setDigitalData(CONTROLID_EQ_RESET,0);
					setDigitalData(CONTROLID_EQ_ROCK,0);
					setDigitalData(CONTROLID_EQ_JAZZ,0);
					setDigitalData(CONTROLID_EQ_TURNOFF,0);

					setDigitalData(CONTROLID_EQ_RECORD_1,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,0);
				}
				break;
			case CONTROLID_EQ_RESET:
				if(pLocalParam->settingIndex != -1)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,0);
					setDigitalData(CONTROLID_EQ_POP,0);
					setDigitalData(CONTROLID_EQ_RESET,1);
					setDigitalData(CONTROLID_EQ_ROCK,0);
					setDigitalData(CONTROLID_EQ_JAZZ,0);
					setDigitalData(CONTROLID_EQ_TURNOFF,0);

					setDigitalData(CONTROLID_EQ_RECORD_1,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,0);
				}
				break;
			case CONTROLID_EQ_ROCK:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_ROCK)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,0);
					setDigitalData(CONTROLID_EQ_POP,0);
					setDigitalData(CONTROLID_EQ_RESET,0);
					setDigitalData(CONTROLID_EQ_ROCK,1);
					setDigitalData(CONTROLID_EQ_JAZZ,0);
					setDigitalData(CONTROLID_EQ_TURNOFF,0);

					setDigitalData(CONTROLID_EQ_RECORD_1,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,0);
				}
				break;
			case CONTROLID_EQ_JAZZ:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_JAZZ)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
				    setDigitalData(CONTROLID_EQ_CALSSICAL,0);
					setDigitalData(CONTROLID_EQ_POP,0);
					setDigitalData(CONTROLID_EQ_RESET,0);
					setDigitalData(CONTROLID_EQ_ROCK,0);
					setDigitalData(CONTROLID_EQ_JAZZ,1);
					setDigitalData(CONTROLID_EQ_TURNOFF,0);

					setDigitalData(CONTROLID_EQ_RECORD_1,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,0);
				}
				break;
			case CONTROLID_EQ_TURNOFF:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_DEFAULT)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,0);
					setDigitalData(CONTROLID_EQ_POP,0);
					setDigitalData(CONTROLID_EQ_RESET,0);
					setDigitalData(CONTROLID_EQ_ROCK,0);
					setDigitalData(CONTROLID_EQ_JAZZ,0);
				    setDigitalData(CONTROLID_EQ_TURNOFF,1);

				   	setDigitalData(CONTROLID_EQ_RECORD_1,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,0);
				}
				break;
			case CONTROLID_EQ_RECORD_1:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_RECORD1)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,0);
					setDigitalData(CONTROLID_EQ_POP,0);
					setDigitalData(CONTROLID_EQ_RESET,0);
					setDigitalData(CONTROLID_EQ_ROCK,0);
					setDigitalData(CONTROLID_EQ_JAZZ,0);
				    setDigitalData(CONTROLID_EQ_TURNOFF,0);

				   	setDigitalData(CONTROLID_EQ_RECORD_1,1);
					setDigitalData(CONTROLID_EQ_RECORD_2,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,0);
				}
				break;
			case CONTROLID_EQ_RECORD_2:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_RECORD2)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,0);
					setDigitalData(CONTROLID_EQ_POP,0);
					setDigitalData(CONTROLID_EQ_RESET,0);
					setDigitalData(CONTROLID_EQ_ROCK,0);
					setDigitalData(CONTROLID_EQ_JAZZ,0);
				    setDigitalData(CONTROLID_EQ_TURNOFF,0);

				   	setDigitalData(CONTROLID_EQ_RECORD_1,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,1);
					setDigitalData(CONTROLID_EQ_RECORD_3,0);
				}
				break;
			case CONTROLID_EQ_RECORD_3:
				if(pLocalParam->settingIndex != -1 && pLocalParam->settingIndex != EQ_RECORD3)
				{
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,0);
					setDigitalData(CONTROLID_EQ_POP,0);
					setDigitalData(CONTROLID_EQ_RESET,0);
					setDigitalData(CONTROLID_EQ_ROCK,0);
					setDigitalData(CONTROLID_EQ_JAZZ,0);
				    setDigitalData(CONTROLID_EQ_TURNOFF,0);

				   	setDigitalData(CONTROLID_EQ_RECORD_1,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,1);
				}
				break;
			default:break;
		}
	setUpdateUI(true);
}


void appToAudioVideo_EQ_Sound(void){
	audioVideoToModule_NotifySystem_JumpPage(PAGE_SOUND);
}

void appToAudioVideo_EQ_Eq(void){
	audioVideoToModule_NotifySystem_JumpPage(PAGE_EQ);
}

void appToAudioVideo_EQ_Back(void){
	audioVideoToModule_NotifySystem_JumpPrePage();
}
void appToAudioVideo_EQ_Reset(void)
{
	for(int i=0;i<=9;i++)
	{
		audioToHal_SetSingleEQValue(i,12);
	}
}


void appToAudioVideo_Audio_LoudDec_MouseUp(void){
	//KillMyTimer(TIMER_LOUD_DEC);
	LoudSub();

	//setDigitalData(CONTROLID_AUDIO_LOUD_DEC,0);
}

void appToAudioVideo_Audio_LoudDec_MouseDown(void){
	//LoudSub();
	//SetMyTimer(TIMER_LOUD_DEC, 300); 
	//setDigitalData(CONTROLID_AUDIO_LOUD_DEC,1);


}

void appToAudioVideo_Audio_LoudInc_MouseUp(void){
	//KillMyTimer(TIMER_LOUD_INC);
	LoudAdd();
	
	//setDigitalData(CONTROLID_AUDIO_LOUD_INC,0);

}

void appToAudioVideo_Audio_LoudInc_MouseDown(void){
	//LoudAdd();
	//SetMyTimer(TIMER_LOUD_INC,300);
	//setDigitalData(CONTROLID_AUDIO_LOUD_INC,1);

}

void appToAudioVideo_Audio_TrebDec_MouseUp(void){
	//KillMyTimer(TIMER_TREB_DEC);
	TrebSub();
	//setDigitalData(CONTROLID_AUDIO_TREB_DEC,0);

}

void appToAudioVideo_Audio_TrebDec_MouseDown(void){
	//TrebSub();
	//SetMyTimer(TIMER_TREB_DEC, 300);
	//setDigitalData(CONTROLID_AUDIO_TREB_DEC,1);
}

void appToAudioVideo_Audio_TrebInc_MouseUp(void){
	// KillMyTimer(TIMER_TREB_INC);
	TrebAdd();
	//pLocalParam->treb++;
	//setDigitalData(CONTROLID_AUDIO_TREB_INC,0);
	//setAnalogData(CONTROLID_AUDIO_TREB_INC,pLocalParam->treb)
}

void appToAudioVideo_Audio_TrebInc_MouseDown(void){
	//TrebAdd();
	//SetMyTimer(TIMER_TREB_INC, 300);
	//setDigitalData(CONTROLID_AUDIO_TREB_INC,1);
}

void appToAudioVideo_Audio_MidDec_MouseUp(void){
	//KillMyTimer(TIMER_MID_DEC);
	MidSub();
	//setDigitalData(CONTROLID_AUDIO_MID_DEC,0);
}

void appToAudioVideo_Audio_MidDec_MouseDown(void){
	//MidSub();
	//SetMyTimer(TIMER_MID_DEC, 300);
	//setDigitalData(CONTROLID_AUDIO_MID_DEC,1);
}

void appToAudioVideo_Audio_MidInc_MouseUp(void){
	//KillMyTimer(TIMER_MID_INC);
	MidAdd();
	//setDigitalData(CONTROLID_AUDIO_MID_INC,false);
}

void appToAudioVideo_Audio_MidInc_MouseDown(void){
	//MidAdd();
	//SetMyTimer(TIMER_MID_INC, 300);
	//setDigitalData(CONTROLID_AUDIO_MID_INC,true);
}

void appToAudioVideo_Audio_BassDec_MouseUp(void){
	//KillMyTimer(TIMER_BASS_DEC);
	BassSub();
	//setDigitalData(CONTROLID_AUDIO_BASS_DEC,0);
}

void appToAudioVideo_Audio_BassDec_MouseDown(void){
	//BassSub();
	//SetMyTimer(TIMER_BASS_DEC, 300);
	//setDigitalData(CONTROLID_AUDIO_BASS_DEC,1);
}

void appToAudioVideo_Audio_BassInc_MouseUp(void){
	//KillMyTimer(TIMER_BASS_INC);
	BassAdd();
	//setDigitalData(CONTROLID_AUDIO_BASS_INC,false);
}

void appToAudioVideo_Audio_BassInc_MouseDown(void){
	//SetMyTimer(TIMER_BASS_INC, 300);
	//setDigitalData(CONTROLID_AUDIO_BASS_INC,1);
}

//wen
void appToAudioVideo_Audio_TrebDec_MouseTimer(void){
	TrebSub();
}
void appToAudioVideo_Audio_TrebInc_MouseTimer(void){
	TrebAdd();
}
void appToAudioVideo_Audio_MidDec_MouseTimer(void){
	MidSub();
}
void appToAudioVideo_Audio_MidInc_MouseTimer(void){
	MidAdd();
}
void appToAudioVideo_Audio_BassDec_MouseTimer(void){
	BassSub();
}
void appToAudioVideo_Audio_BassInc_MouseTimer(void){
	BassAdd();
}
void appToAudioVideo_Audio_Left_MouseTimer(void){
	BalanceSub();
}
void appToAudioVideo_Audio_Right_MouseTimer(void){
	BalanceAdd();
}
void appToAudioVideo_Audio_Front_MouseTimer(void){
	FaderSub();
}
void appToAudioVideo_Audio_Rear_MouseTmier(void){
	FaderAdd();
}



void appToAudioVideo_Audio_Left_MouseUp(void){
	//KillMyTimer(TIMER_BALANCE_DEC);
	//setDigitalData(CONTROLID_AUDIO_LEFT,0);
	BalanceSub();
}

void appToAudioVideo_Audio_Left_MouseDown(void){
	//SetMyTimer(TIMER_BALANCE_DEC,300);  
	//setDigitalData(CONTROLID_AUDIO_LEFT,1);

}

void appToAudioVideo_Audio_Right_MouseUp(void){
	//KillMyTimer(TIMER_BALANCE_INC);
	//setDigitalData(CONTROLID_AUDIO_RIGHT,0);
	BalanceAdd();
}

void appToAudioVideo_Audio_Right_MouseDown(void){
	//SetMyTimer(TIMER_BALANCE_INC,300);
	//setDigitalData(CONTROLID_AUDIO_RIGHT,1);

}

void appToAudioVideo_Audio_Front_MouseUp(void){
	//KillMyTimer(TIMER_FADER_DEC);
	//setDigitalData(CONTROLID_AUDIO_FRONT,0);
	FaderSub();
}

void appToAudioVideo_Audio_Front_MouseDown(void){
	//SetMyTimer(TIMER_FADER_DEC, 300);
	//setDigitalData(CONTROLID_AUDIO_FRONT,1);
}

void appToAudioVideo_Audio_Rear_MouseUp(void){
	//KillMyTimer(TIMER_FADER_INC);
	//setDigitalData(CONTROLID_AUDIO_REAR,false);
	FaderAdd();
}

void  appToAudioVideo_Audio_Rear_MouseDown(void){
	//SetMyTimer(TIMER_FADER_INC,300);
	//setDigitalData(CONTROLID_AUDIO_REAR,1);
}

void appToAudioVideo_Audio_TouchListen(u8 *param, u8 len)
{
	u8 pos_x=0;
	u8 pos_y=0;
	pos_y=param[3];
	pos_x=param[7];
	LOGD("pos_x:%d pos_y:%d",pos_x,pos_y);

	if(pos_x >= 0 && pos_x <= 20)
	{
		audioToHal_Balance(pos_x);
	}
	
	if( pos_y >=0 && pos_y <= 20)
	{
		audioToHal_Fader(pos_y);
	}
	
}

void appToAudio_Scrollbar_faderBalance(u8 *param, u8 len)
{
	Balance = 0;
	Fader = 0;
	
	Balance += (int)((param[0] << 8) & 0xFF00);
	Balance += (int)(param[1] & 0xFF);
	
	Fader += (int)((param[2] << 8) & 0xFF00);
	Fader += (int)(param[3] & 0xFF);

	if(Balance >= 0 && Balance <= 20)
	{
		bScrBlVisible = false;
		audioToHal_Balance(Balance);
	}
	
	if(Fader >=0 && Fader <= 20)
	{
		bScrFdVisible = false;
		audioToHal_Fader(Fader);
	}
}

void UI_Scrollbar_faderBalanceValue()
{
	setExProgressSingleOnePos(CONTROLID_AUDIO_SCROLLBAR_LISTENPOS,(short)Balance,(short)Fader);
}

void appToAudioVideo_Audio_Param_Reset()
{
	audioToHal_Balance(10);
	audioToHal_Fader(10);
}

void appToAudioVideo_Audio_LoudFreq_MouseUp(void){
	audioToHal_SimulateKey(0x0F);
	return;
	//int iTmpLoudPos = pLocalParam->loudnessPos;
	int iTmpLoudPos = pLocalParam->loudness;
	iTmpLoudPos ++;
	if (iTmpLoudPos>2)
	iTmpLoudPos = 0;
	audioToHal_SetLoudnessFreq(iTmpLoudPos);
}

void appToAudioVideo_Audio_LoudFreq_MouseDown(void){
	LOGI("*************");
	setDigitalData(CONTROLID_AUDIO_LOUD_FREQ, 1);
}

void appToAudioVideo_Audio_TrebFreq_MouseUp(void){
	 audioToHal_SimulateKey(0x06);
	 return;
	//int iTmpTrebPos = pLocalParam->trebPos;
	int iTmpTrebPos = pLocalParam->treb;
	iTmpTrebPos ++;
	if (iTmpTrebPos>1)
	iTmpTrebPos = 0;
	audioToHal_SetTrebFreq(iTmpTrebPos);

}

void appToAudioVideo_Audio_TrebFreq_MouseDown(void){
	LOGI("*************");
}

void appToAudioVideo_Audio_MidFreq_MouseUp(void){
	 audioToHal_SimulateKey(0x09);
	return;
	//int iTmpMidPos = pLocalParam->midPos;
	int iTmpMidPos = pLocalParam->mid;
	iTmpMidPos++;
	if (iTmpMidPos>2)
	iTmpMidPos = 0;
	audioToHal_SetMidFreq(iTmpMidPos);

}

void appToAudioVideo_Audio_MidFreq_MouseDown(void){
	LOGI("*************");
}



void appToAudioVideo_Audio_BassFreq_MouseUp(void){
	 audioToHal_SimulateKey(0x0C);
	return;
	//int iTmpBassPos = pLocalParam->bassPos;
	int iTmpBassPos = pLocalParam->bass;
	iTmpBassPos++;
	if(iTmpBassPos>2)
		iTmpBassPos = 0;
	audioToHal_SetBassFreq(iTmpBassPos);
	

}

void appToAudioVideo_Audio_BassFreq_MouseDown(void){
	LOGI("*************");
}


void appToAudioVideo_Audio_Sound(void){
	audioVideoToModule_NotifySystem_JumpPage(PAGE_SOUND);
}


void appToAudioVideo_Audio_Eq(void){
	audioVideoToModule_NotifySystem_JumpPage(PAGE_EQ);
}

void appToAudioVideo_Audio_Back(void){
	audioVideoToModule_NotifySystem_JumpPrePage();
}

void appToAudioVideo_MENUAudio(void){
	audioVideoToModule_NotifySystem_JumpPage(PAGE_SOUND);
}




////////////////////////////////////////////////////////////
//Bass+
void BassAdd(void)
{
	int iBass = pLocalParam->bassPos;
    if(iBass<0)
	{
		audioToHal_SetBassLevel(0);
		pLocalParam->bassPos = 0;
	}
	else if(iBass>10)
	{
		audioToHal_SetBassLevel(10);
		pLocalParam->bassPos = 10;
	}
	else if(iBass<10)
	{
		audioToHal_SetBassLevel(iBass+1);

		pLocalParam->bassPos = iBass + 1; 
	}

	requestPradoAudio();
}
//Bass-
void BassSub(void)
{
	int iBass = pLocalParam->bassPos;
	if(iBass<0)
	{
		audioToHal_SetBassLevel(0);
		pLocalParam->bassPos = 0;
	}
	else if(iBass>10)
	{
		audioToHal_SetBassLevel(10);
		pLocalParam->bassPos = 10;
	}
	else if(iBass>0)
	{
		audioToHal_SetBassLevel(iBass-1);

		pLocalParam->bassPos = iBass - 1;
	}

	requestPradoAudio();
}
//Treb+
void TrebAdd(void)
{
	int iTreb = pLocalParam->trebPos;
	if(iTreb<0)
	{
		audioToHal_SetTredLevel(0);
		pLocalParam->trebPos = 0;
	}
	else if(iTreb>10)
	{
		audioToHal_SetTredLevel(10);
		pLocalParam->trebPos = 10;
	}
	else if(iTreb<10)
	{
		audioToHal_SetTredLevel(iTreb+1); 

		pLocalParam->trebPos = iTreb + 1;
	}

	requestPradoAudio();
}
//Treb-
void TrebSub(void)
{
	int iTreb = pLocalParam->trebPos;
	if(iTreb<0)
	{
		audioToHal_SetTredLevel(0);
		pLocalParam->trebPos = 0;
	}
	else if(iTreb>10)
	{
		audioToHal_SetTredLevel(10);
		pLocalParam->trebPos = 10;
	}
	else if(iTreb>0)
	{
		audioToHal_SetTredLevel(iTreb-1);
		
		pLocalParam->trebPos = iTreb - 1;
	}

	requestPradoAudio();
}

//Loud+
void LoudAdd(void)
{
	int iLoud = pLocalParam->loudnessPos;
	if(iLoud<0)
		audioToHal_SetLoudnessLevel(0);
	else if(iLoud>10)
		audioToHal_SetLoudnessLevel(10);
	else if(iLoud<10)
	{
		audioToHal_SetLoudnessLevel(iLoud+1);
	}
}
//Loud-
void LoudSub(void)
{
	int iLoud = pLocalParam->loudnessPos;
	if(iLoud<0)
		audioToHal_SetLoudnessLevel(0);
	else if(iLoud>10)
		audioToHal_SetLoudnessLevel(10);
	else if(iLoud>0)
	{
		audioToHal_SetLoudnessLevel(iLoud-1);
	}
}
//Mid+
void MidAdd(void)
{
	int iMid = pLocalParam->midPos;
	if(iMid<0)
	{
		audioToHal_SetMidLevel(0);
		pLocalParam->midPos = 0;
	}
	else if(iMid>10)
	{
		audioToHal_SetMidLevel(10);
		pLocalParam->midPos = 10; 
	}
	else if(iMid<10)
	{
		audioToHal_SetMidLevel(iMid+1);

		pLocalParam->midPos = iMid + 1;
	}

	requestPradoAudio();
}
//Mid-
void MidSub(void)
{
	int iMid = pLocalParam->midPos;
	if(iMid<0)
	{
		audioToHal_SetMidLevel(0);
		pLocalParam->midPos = 0;
	}
	else if(iMid>10)
	{
		audioToHal_SetMidLevel(10);
		pLocalParam->midPos = 10; 
	}
	else if(iMid>0)
	{
		audioToHal_SetMidLevel(iMid-1);

		pLocalParam->midPos = iMid - 1;
	}

	requestPradoAudio();
	
}
//Front
void FaderSub(void)
{
	int iFader = pLocalParam->fader-1;
	
	if(iFader >= 0 && iFader <= 20){
		audioToHal_Fader(iFader);

		pLocalParam->fader = iFader;
		requestPradoAudio();
	}
}
//Rear
void FaderAdd(void)
{
	int iFader = pLocalParam->fader+1;

	if(iFader >= 0 && iFader <= 20){
		audioToHal_Fader(iFader);

		pLocalParam->fader = iFader;
		requestPradoAudio();
	}

}
//Left
void BalanceSub(void)
{
	int iBalance = pLocalParam->balance-1;

	if(iBalance >= 0 && iBalance <= 20){
		audioToHal_Balance(iBalance);

		pLocalParam->balance = iBalance;
		requestPradoAudio();
	}
	

}
//Right;
void BalanceAdd(void)
{
	int iBalance = pLocalParam->balance+1;
	
	if(iBalance >= 0 && iBalance <= 20){
		audioToHal_Balance(iBalance);

		pLocalParam->balance = iBalance;
		requestPradoAudio();
	}

}



///////////////11-9/////////////////
void appToAudioVideo_cancelEQSeleted(void){
	switch(pLocalParam->imEQ){
		case EQ_DEFAULT:
		case EQ_JAZZ:
		case EQ_ROCK:
		case EQ_CLASS:
		case EQ_POP:{
			pLocalParam->imEQ = EQ_NOCLASS;
			appToAudioVideo_displayEQType(EQ_NOCLASS);
		}
		break;
	}
}


void appToAudioVideo_displayEQType(int classtype){
	LOGD("******************DisplayBegin:%d",pLocalParam->firstDisplayEQFlag);
	setUpdateUI(false);
	switch(classtype){
	
		case EQ_NOCLASS:
			{
				if(pLocalParam->firstDisplayEQFlag){
					
					//setDigitalData(CONTROLID_EQ_RESET,1);
					}
				setDigitalData(CONTROLID_EQ_RESET,0);
				setDigitalData(pLocalParam->preSettingIndexControl,0);
			    pLocalParam->preSettingIndexControl = CONTROLID_EQ_RESET;
			}
			break;
		case EQ_DEFAULT:
			{
				if(pLocalParam->firstDisplayEQFlag){
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_TURNOFF,1);
					}
			    pLocalParam->preSettingIndexControl = CONTROLID_EQ_TURNOFF;
				}
			break;
		case EQ_CLASS:
			{
			if(pLocalParam->firstDisplayEQFlag){
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_CALSSICAL,1);
					}
			    pLocalParam->preSettingIndexControl = CONTROLID_EQ_CALSSICAL;
				}
			break;
		case EQ_POP:
			{
				if(pLocalParam->firstDisplayEQFlag){
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_POP,1);
					}
				pLocalParam->preSettingIndexControl = CONTROLID_EQ_POP;
				}
			break;
		case EQ_JAZZ:
			{
			if(pLocalParam->firstDisplayEQFlag){
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_JAZZ,1);
					}
				pLocalParam->preSettingIndexControl = CONTROLID_EQ_JAZZ;
				}
			
			break;
		case EQ_ROCK:
			{
			if(pLocalParam->firstDisplayEQFlag){
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_ROCK,1);
					}
				pLocalParam->preSettingIndexControl = CONTROLID_EQ_ROCK;
				}
			break;
		case EQ_RECORD1:
			{
			if(pLocalParam->firstDisplayEQFlag){
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_RECORD_1,1);
					}
				pLocalParam->preSettingIndexControl = CONTROLID_EQ_RECORD_1;
				}
			break;
		case EQ_RECORD2:
			{
			if(pLocalParam->firstDisplayEQFlag){
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_RECORD_2,1);
					}
				pLocalParam->preSettingIndexControl = CONTROLID_EQ_RECORD_2;
				}
			break;
		case EQ_RECORD3:
			{
			if(pLocalParam->firstDisplayEQFlag){
					setDigitalData(pLocalParam->preSettingIndexControl,0);
					setDigitalData(CONTROLID_EQ_RECORD_3,1);
					}
				pLocalParam->preSettingIndexControl = CONTROLID_EQ_RECORD_3;
				}
			break;
		default:break;
	}
	setUpdateUI(true);
}

void Display_LoudNessOnOFF(void){
	
	if(pLocalParam->bIsLoudnessOn)
	{
		setDigitalData(CONTROLID_AUDIO_EQUAL_LOUDNESS_ON_OFF, 1);
	}
	else
	{
		setDigitalData(CONTROLID_AUDIO_EQUAL_LOUDNESS_ON_OFF, 0);
	}
	
}
void appToAudio_setBalanceAdd(void){

}
void appToAudio_setBalanceSub(void){

}
void appToAudio_setFaderAdd(void){

}
void appToAudio_setFaderSub(void){

}

void appToAudio_DisPlayMuteState(int mute){
	setDigitalData(CONTROLID_AUDIO_DVD_MUTE,mute);//DVD\BE\B2\D2\F4	\BE\B2\D2\F4\B0\B4ť
	//setDigitalData(FUNCID_SOUND_RADIO_BTN_MUTE,mute);//RADIO\BE\B2\D2\F4	
	//setDigitalData(FUNCID_SOUND_IPOD_BTN_MUTE,mute);//IPOD\BE\B2\D2\F4	
	//setDigitalData(FUNCID_SOUND_USB_BTN_MUTE,mute);//USB\BE\B2\D2\F4
	//setDigitalData(FUNCID_SOUND_XM_RADIO_BTN_MUTE,mute);//XMRADIO\BE\B2\D2\F4

}

void appToAudio_SetLoudnessSwith()
{
	LOGD("CONTROLID_AUDIO_EQUAL_LOUDNESS_ON_OFF NEW A 87 dyb");

	if ( pLocalParam->bIsLoudnessOn)
	{
		 pLocalParam->bIsLoudnessOn = false;
		 setDigitalData(CONTROLID_AUDIO_EQUAL_LOUDNESS_ON_OFF, 0);
		 audioToHal_SetLoudnessSwitch(pLocalParam->bIsLoudnessOn);
		 
	}
	else
	{
		 pLocalParam->bIsLoudnessOn = true;
		 setDigitalData(CONTROLID_AUDIO_EQUAL_LOUDNESS_ON_OFF, 1);
		 audioToHal_SetLoudnessSwitch(pLocalParam->bIsLoudnessOn);
	}
		
}

void appToAudio_SetMix_On_Off()
{
	LOGD("appToAudio_SetMix_On_Off pLocalParam->bIsMixingSwitch:%x",pLocalParam->bIsMixingSwitch);
	if (pLocalParam->bIsMixingSwitch)
	{
		 pLocalParam->bIsMixingSwitch = false;
		 setDigitalData(CONTROLID_AUDIO_MEDIA_MIX_ON_OFF, 0);
		 
	}
	else
	{
		 pLocalParam->bIsMixingSwitch = true;
		 setDigitalData(CONTROLID_AUDIO_MEDIA_MIX_ON_OFF, 1);
	}
}

void clickPradoAsl(u8 mouseEvent)
{
	switch(mouseEvent)
	{
	case UIACTION_MOUSEUP:
		{
			pLocalParam->m_nPradoAsl = (pLocalParam->m_nPradoAsl == 1) ? 0 : 1;

			requestPradoAudio();
		}
		break;
	default:
		break;
	}
}

void clickPradoSurround(u8 mouseEvent)
{
	switch(mouseEvent)
	{
	case UIACTION_MOUSEUP:
		{
			pLocalParam->m_nPradoSurround = (pLocalParam->m_nPradoSurround == 1) ? 0 : 1;

			requestPradoAudio();
		}
		break;
	default:
		break;
	}
}

void appToAudio_Eq_Set()
{
	audioVideoToModule_NotifySystem_JumpPage(PAGE_AUDIO_SET);
}

void appToAudio_Eq_Set_box()
{
	audioVideoToModule_NotifySystem_JumpPage(PAGE_AUDIO_SET_BOX);
}

void clickAudioDataSet(u8 param)
{
	u8 P = (param == 0) ? 1 : 0; 
	audioToHal_soundFunctionParamSet(P);
}