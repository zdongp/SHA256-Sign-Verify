#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <cutils/properties.h>

#include "global.h"
#include "hal.h"
#include "param.h"

#include "appRequestFunction.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "halRequestFunction.h"
#include "appRequestCommand.h"
#include "moduleParamResponse.h"

#include <flymoduleApi_internal.h>

extern bool bAccOnOrInit_State;

void combineSoundVideoChannel(void){

	int newSoundVideoChannel = 0;
	short iSound = pLocalParam->soundChannel; //TV
	short iVideo = pLocalParam->videoChannel; //������TV����Ƶͨ����
	
	int bIsRealChannel = 0;
	bIsRealChannel = findCombineSoundVideoChannel(iSound,iVideo,&newSoundVideoChannel);
	if (!bIsRealChannel){
	    LOGD("bIsRealChannel=%d",bIsRealChannel);
	    return;
	}

	short oldChannel = pLocalParam->soundVideoChannel;

	LOGD("[%s] oldChannel=0x%x,newSoundVideoChannel=0x%x",__FUNCTION__,oldChannel,newSoundVideoChannel);
    //����Ƶ״̬����UI
	setSoundChannelState_ToApp((u8)newSoundVideoChannel);

	if(newSoundVideoChannel != 0x05 && newSoundVideoChannel != 0x06){
		pLocalParam->b_autoJumpAux = true;/*��������������AUXҳ��*/
	}
	
	//**************************************************ͨ��û�仯**********************************************//
	//���ߺ�������������ʱ��DVD��MP3��MP3��������(ͨ������MP3)
	if(oldChannel != CHANNEL_MP3 && newSoundVideoChannel != CHANNEL_MP3)
		audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(CHANNEL_MP3,newSoundVideoChannel);

    LOGD("[%s] bAccOnOrInit_State:%x",__FUNCTION__,bAccOnOrInit_State);
    if(bAccOnOrInit_State)
	    audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_AUXSCREEN,newSoundVideoChannel);

	bAccOnOrInit_State=false;

	//�������������Ϊͨ��û�仯����û��RADIOͨ����Ϣ��������
	if (oldChannel == newSoundVideoChannel && newSoundVideoChannel == CHANNEL_RADIO)
		audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(newSoundVideoChannel,newSoundVideoChannel);
	//*********************************************************************************************************//

	if (oldChannel == newSoundVideoChannel) return;
	
	pLocalParam->oldsoundVideoChannel = oldChannel;
	pLocalParam->soundVideoChannel = newSoundVideoChannel;
	
	audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_AUXSCREEN,newSoundVideoChannel);
	
	audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(oldChannel,pLocalParam->soundVideoChannel);
	audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(newSoundVideoChannel,pLocalParam->soundVideoChannel);

	audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_KEY,newSoundVideoChannel);
	audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_BLCD,newSoundVideoChannel);
	
	if((newSoundVideoChannel == CHANNEL_THREECHANNEL) ||
		(newSoundVideoChannel == CHANNEL_MP3) ||
		(newSoundVideoChannel == CHANNEL_BACK_VIDEO))
		setRingerCtrl(0xFE);	// Stop
	else
		setRingerCtrl(0xFF);	// Play
}


void audioToHal_Init(char param){
	unsigned char buf[2] = { 0x01, 0x00};

	if(param){
		buf[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioTohal_InitParamCmd(u8 *param,int len)
{
	LOGD("notify  hal Paraminit");
	u8 buf[64];
	memset(buf,0,sizeof(buf));
	buf[0] = 0x02;
	memcpy(buf+1,param,len);
	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, len+1);
}//��ʼ������

void  audioToHal_SimulateKey(unsigned char key){
	unsigned char buf[2] = { 0x03, key};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetSoundChannel(unsigned char soundChannel){
	unsigned char buf[2] = { 0x10, soundChannel};
	LOGD("[%s] souundChannel:0x%x", __FUNCTION__,soundChannel);
	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetMute(char mute){
	unsigned char buf[2] = { 0x11, 0x00};

	if(mute){
		buf[1] = 0x01;
	}
	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetVolume(unsigned char volume){
	LOGD("audioToHal set volume");
	unsigned char buf[2] = { 0x12,volume};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_Balance(unsigned char balance){
	unsigned char buf[2] = { 0x13, balance};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_Fader(unsigned char fader){
	unsigned char buf[2] = { 0x14, fader};

	LOGD("audioToHal_Fader:%d",fader);
	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}


void audioToHal_SetTrebFreq(unsigned char TredFreq){
	unsigned char buf[2] = { 0x15, TredFreq};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetTredLevel(unsigned char TredLevel){
	unsigned char buf[2] = { 0x16, TredLevel};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetMidFreq(unsigned char MidFreq){
	unsigned char buf[2] = { 0x17, MidFreq};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetMidLevel(unsigned char MidLevel){
	unsigned char buf[2] = { 0x18, MidLevel};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetBassFreq(unsigned char BassFreq){
	unsigned char buf[2] = { 0x19, BassFreq};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetBassLevel(unsigned char BassLevel){
	unsigned char buf[2] = { 0x1A, BassLevel};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetLoudnessFreq(unsigned char LoudnessFreq){
	unsigned char buf[2] = { 0x1B, LoudnessFreq};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetLoudnessLevel(unsigned char LoudnessLevel){
	unsigned char buf[2] = { 0x1C, LoudnessLevel};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetEQAll(unsigned char *Eqs, int len){
	if((Eqs == NULL) || (len <= 0)){
		return;
	}

	unsigned char buffer[len+1];

	buffer[0] = 0x1D;
	memcpy((void*)&buffer[1], Eqs, len);
	LOGD("buffer[0]:%d,buffer[9]:%d,len:%d",buffer[0],buffer[9],len+1);
	makeAndSendMessageToHal(HAL_ID_AUDIO, buffer, len+1);
}

void audioToHal_SetSingleEQValue(unsigned char EqFreq, unsigned char EqValue){
	unsigned char buffer[3] = {0x1E, EqFreq, EqValue};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buffer, 3);
}

void audioToHal_SetSingleEQKey(unsigned char EqFreq, unsigned char EqKey){
	unsigned char buffer[3] = {0x20, EqFreq, EqKey};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buffer, 3);
}

void audioToHal_SetInnerEQSetting(unsigned char eqType){
	unsigned char buf[2] = { 0x21, eqType};
	LOGD("audioToHal_SetInnerEQSetting:%d",eqType);
	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SaveUserEQSetting(unsigned char userEQ){
	unsigned char buf[2] = { 0x22, userEQ};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetPOSValue(unsigned char posValue){
	unsigned char buf[2] = { 0x23, posValue};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetMixedNaviVoice(char mixedNaviVoice){
	unsigned char buf[2] = { 0x24, 0x00};
    LOGD("audioToHal_SetMixedNaviVoice  mixedNaviVoice= %d",mixedNaviVoice);
	if(mixedNaviVoice){
		buf[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_NotifyAmplitude(u8 cAmplitude){
	unsigned char buf[2] = { 0x25, cAmplitude};
    LOGD("audioToHal_NotifyAmplitude   ZENGYI=%d",cAmplitude);
	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_NotifySpeechState(u8 p){
	unsigned char buf[2] = { 0x26, p};
	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_NotifySpeechState_New(u8 p){
	unsigned char buf[2] = { 0x27, p};
	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}
void audioToHal_SetLoudnessSwitch(bool switchOn){
	unsigned char buf[2] = { 0x30, 0x00};

	if(switchOn){
		buf[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetSubSwitch(char switchOn){
	unsigned char buf[2] = { 0x31, 0x00};

	if(switchOn){
		buf[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetSubFilter(unsigned char subFilter){
	unsigned char buf[2] = { 0x32, subFilter};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_SetSubLevel(unsigned char subLevel){
	unsigned char buf[2] = { 0x34, subLevel};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}

void audioToHal_EnableMixVoice(u8 state)
{
	u8 param[] = {0x35, 0x01};
	param[1]=state;
	LOGD("audioToHal_EnableMixVoice,state:%d",state);
	pLocalParam->uEnableMixVoiceState = state;
	makeAndSendMessageToHal(HAL_ID_AUDIO, param, 2);
}

void audioToHal_soundFunctionParamSet(u8 uP)
{
	u8 param[] = {0x36, 0x00};
	param[1]=uP;
	makeAndSendMessageToHal(HAL_ID_AUDIO, param, 2);
}

/**********************************************************************/
void videoToHal_Init(u8 param){
	u8 buff[] = {0x01, 0x00};

	if(param){
		buff[1] = 0x01;
	}

	makeAndSendMessageToHal(HAL_ID_VIDEO, buff, 2);
}

#include <commonFunc.h>

void SetVideoChannel_videoToHal_enterOrExitVideoPreProcess(u8 ch,u8 videoState,int nTimes)
{
	u8 param[7] = {0};
	param[0] = 0x10;
	param[1] = ch;
	param[2] = videoState;
	memcpy(param + 3,&nTimes,sizeof(nTimes));
	LOGD("[%s] souundChannel:0x%x videoState:0x%x nTimes:%d", __FUNCTION__,ch,  videoState,nTimes);
	makeAndSendMessageToHal(HAL_ID_VIDEO, param, sizeof(param));
}

void videoToHal_SetVideoChannel(u8 ch,u8 videoState){
	u8 param[] = {0x10, ch , videoState};
	LOGD("[%s] souundChannel:0x%x videoState:0x%x", __FUNCTION__,ch,  videoState);
	makeAndSendMessageToHal(HAL_ID_VIDEO, param, 3);
}

void videoToHal_ColorStepRegulate(u8 state){
	u8 param[] = {0x11, state};
	LOGD("[%s] state:%d",__FUNCTION__,state);
	makeAndSendMessageToHal(HAL_ID_VIDEO, param, 2);
}

//发送到 video
void setToHalBackCarMode(u8 p)
{
	LOGD("[%s] p = [0x%x]", __FUNCTION__, p);

	u8 szMsg[2] = {0x2B, 0x00};

	szMsg[1] = p;

	makeAndSendMessageToHal(HAL_ID_OSD_BUTTEN , szMsg, sizeof(szMsg));
}

void setToHalSystemLcd(unsigned char p, int t)
{
	LOGD("[%s] p = [0x%x]", __FUNCTION__, p);

	u8 szMsg[6] = {0};

	szMsg[0] = 0x70;
	szMsg[1] = p;

	memcpy(szMsg + 2, &t, sizeof(t));

	makeAndSendMessageToHal(HAL_ID_SYSTEM, szMsg, sizeof(szMsg));
}

void audioToHal_SetStartVolume(unsigned char volume)
{
	unsigned char buf[2] = { 0x37,volume};

	makeAndSendMessageToHal(HAL_ID_AUDIO, buf, 2);
}