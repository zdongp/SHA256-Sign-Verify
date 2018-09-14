#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "param.h"
#include "paramID.h"
#include "pageID.h"
#include "controlID.h"
#include "appRequestCommand.h"
#include "appRequestFunction.h"
#include "appResponseFunction.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"
#include "moduleParamResponse.h"
#include "halResponseFunction.h"
#include "halRequestFunction.h"
#include "otherModuleResponseFunction.h"
#include "timer_interface.h"

extern bool bDoSpecial_ChanceSpeechBack;
extern bool bAccOnOrInit_State;
extern bool bScrBlVisible;
extern bool bScrFdVisible;

extern "C"{
#include "unicodestring.h"
};

///////////////////////////audio////////////////////////////////
void halToAudio_InitCmd(unsigned char param){
	LOGD("Get audio Init cmd param");
}

void halToAudio_InitState(unsigned char state){
	LOGD("Get audio Init state");
	if(state == 0x01)
	{
		//The first audio init,the second radio!!!
		//audioVideoToModule_NotifyRadio_Init(0x01);
	}
}

void halToAudio_SoundCardState(unsigned char state){
	LOGD("halToAudi:soundcard, gpsSoundState:%d,%d  pLocalParam->soundVideoChannel:%x", state, pLocalParam->gpsSoundState,pLocalParam->soundVideoChannel);
	pLocalParam->soundcardSoundState = state;
	
	
	if(state == 0x01 && pLocalParam->soundVideoChannel != CHANNEL_THREECHANNEL && pLocalParam->soundVideoChannel != CHANNEL_MP3)
    {//������Ϊ1:���� 0:������
    	LOGD("halToAudi pLocalParam->bTimeKeeperState:%d",pLocalParam->bTimeKeeperState);
    	if(pLocalParam->bTimeKeeperState)
    	{
    		audioToHal_SetMixedNaviVoice(1); 
    	}
    	else if(!(!pLocalParam->gpsSoundOn && pLocalParam->gpsSoundState && pLocalParam->soundVideoChannel != CHANNEL_THREECHANNEL && pLocalParam->soundVideoChannel != CHANNEL_MP3))
    	{
   	 		audioToHal_SetMixedNaviVoice(1); 
   	 	}
   	}
	else{
		audioToHal_SetMixedNaviVoice(0); 
	}

	audioVideoToModule_NotifyOSD_SendOsdDebugInfo();
	
}


void halToAudio_SoundChannel(unsigned char soundChannel){
	LOGD("[%s] soundChannel:%x",__FUNCTION__, soundChannel);
	
	
	bDoSpecial_ChanceSpeechBack = false;
	pLocalParam->soundChannel = soundChannel;
    
    /********************************************������*****************************************************/
	int newSoundVideoChannel = 0;
	short iSound = pLocalParam->soundChannel; 
	short iVideo = 0;
	
	int bIsRealChannel = 0;
	bIsRealChannel = findCombineSoundVideoChannel(iSound,iVideo,&newSoundVideoChannel);
	if (!bIsRealChannel) 
	{
	    LOGD("bIsRealChannel=%d",bIsRealChannel);
	    return;
	}

	short oldChannel = pLocalParam->soundVideoChannel;
	pLocalParam->soundVideoChannel = newSoundVideoChannel;
	
	//moupeng 2015/7/25
	g_clsAudiovideo.sendToFlyJniSdkSoundVideoChannel(newSoundVideoChannel);
	g_clsAudiovideo.sendToApp_AudioChannelChange(newSoundVideoChannel);
	
	g_clsAudiovideo.sendToFlyJniSdkCurAudioIsAndroidChannel(findCombineIsAndroidAudioChannel(iSound,iVideo));

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

    if(bAccOnOrInit_State)
    {
        LOGD("bAccOnOrInit_State:%x",bAccOnOrInit_State);

		if (oldChannel == newSoundVideoChannel){
			audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_AUXSCREEN,newSoundVideoChannel);
		}

		if(newSoundVideoChannel != CHANNEL_AUX_CTRL)
    	{
    		u8 n_IsAux = 0;
    		u8 n_IsAuxLen = 0;
    		getOtherModuleParam(MODULE_ID_SYSTEM,SYSTEM_IS_AUX,(u8*)&n_IsAux,&n_IsAuxLen);
    		if(n_IsAux == 0)
    			 audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_SYNC,newSoundVideoChannel);
    	}
	 }

    bAccOnOrInit_State=0;

	//�������������Ϊͨ��û�仯����û��RADIOͨ����Ϣ��������
	if (oldChannel == newSoundVideoChannel && newSoundVideoChannel == CHANNEL_RADIO)
		audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(newSoundVideoChannel,newSoundVideoChannel);
	//*********************************************************************************************************//
	if (oldChannel == newSoundVideoChannel) return;
	pLocalParam->oldsoundVideoChannel = oldChannel;
	
	if(newSoundVideoChannel == CHANNEL_RADIO || newSoundVideoChannel == CHANNEL_MP3  ||newSoundVideoChannel == CHANNEL_BT)
	{
		pLocalParam->lastMediaChannel = newSoundVideoChannel;
	}
	audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_AUXSCREEN,newSoundVideoChannel);
	
	audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(oldChannel,pLocalParam->soundVideoChannel);
	audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(newSoundVideoChannel,pLocalParam->soundVideoChannel);

	audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_KEY,newSoundVideoChannel);
	audioVideoToModule_NotifyOtherModule_SetNoticeMode(MODULE_ID_BLCD,newSoundVideoChannel);
	
	if((newSoundVideoChannel == CHANNEL_THREECHANNEL) ||
		(newSoundVideoChannel == CHANNEL_MP3) ||
		(newSoundVideoChannel == CHANNEL_BACK_VIDEO) ||
		(newSoundVideoChannel == CHANNEL_SPEECH_MEDIA_CTRL))
		setRingerCtrl(0xFE);	// Stop
	else
		setRingerCtrl(0xFF);	// Play
    /*************************************************************************************************/

}

void halToAudio_Mute(int mute){
	
	LOGD("Get audio Volume Mute:%d", mute);
	pLocalParam->mute = mute;

	//Whether to pull down OSD separate Hal notifications!!!
	/*
	static int firstGetMute = 1;
	if(firstGetMute){
		firstGetMute = 0;
	}
	else {
		if(pLocalParam->bMuteIsOsd)
		{
			
			//audioVideoToModule_NotifyDvd_SetDisplayVolumeOsdOption();
			audioVideoToModule_NotifyOSD_ShowVolumeOsd();
			if(mute){
				audioVideoToModule_NotifyOsd_DisplayOSDVolume(0);
			}
			else{
				audioVideoToModule_NotifyOsd_DisplayOSDVolume(pLocalParam->volume);
			}
		}
	}
	*/
}

void halToAudio_Volume(unsigned char volume){
	LOGD("Get audio Volume:%d", volume);

	pLocalParam->volume = volume;
	g_clsAudiovideo.sendToFlyJniSdkCurVolumeValue(pLocalParam->uMaxVol,0,pLocalParam->volume);
	if((volume != 0x00) && pLocalParam->mute){ // volume != 0 && not mute
		halToAudio_Mute(0);
	}
	else if(volume == 0x00){
		halToAudio_Mute(1);
	}

	audioVideoToModule_NotifyAuxscreen_SetVolume(volume);
	setVolumeValue_ToApp(volume);

	//Whether to pull down OSD separate Hal notifications!!!
	/*
	LOGD("Get audio getVolumeTimes:%d", pLocalParam->getVolumeTimes);
	//if(pLocalParam->getVolumeTimes<3){
	if(pLocalParam->getVolumeTimes<1){
		pLocalParam->getVolumeTimes += 1;
		return;
	}
	else{
    	u16 curPage = 0;
		u8 curpageLen = 0;
		getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&curPage, &curpageLen);
		if(PAGE_BLACK != curPage){
			if(pLocalParam->bMuteIsOsd)
			{
				audioVideoToModule_NotifyOSD_ShowVolumeOsd();//? edited by ygp
				//audioVideoToModule_NotifyOsd_DisplayOSDVolume(volume);
			}
		}
	}
	
	pLocalParam->bMuteIsOsd = true;
	*/
}

void halToAudio_LRBalance(unsigned char balance){
	pLocalParam->balance = balance;
	LOGD("halToAudio_LRBalance:%d",balance);
	setExProgressSinglePos(CONTROLID_AUDIO_LISTENPOS, 0x01, (int)balance);

	if(bScrBlVisible)
		setExProgressSinglePos(CONTROLID_AUDIO_SCROLLBAR_LISTENPOS, 0x01, (int)balance);
	bScrBlVisible = true;
	g_clsAudiovideo.sendToApp_SoundBalanceValue(0x00,balance);
}

void halToAudio_FRFader(unsigned char fader){
	pLocalParam->fader= fader;
	LOGD("halToAudio_FRFader:%d",fader);
	setExProgressSinglePos(CONTROLID_AUDIO_LISTENPOS, 0x00, (int)fader);

	if(bScrFdVisible)
		setExProgressSinglePos(CONTROLID_AUDIO_SCROLLBAR_LISTENPOS, 0x00, (int)fader);
	bScrFdVisible = true;
	g_clsAudiovideo.sendToApp_SoundBalanceValue(0x01,fader);
}

void halToAudio_TrebFreq(unsigned char freq){
	LOGD("halToAudio_TrebFreq:%d",freq);
	pLocalParam->treb= freq;
	setAnalogData(CONTROLID_AUDIO_TREB_FREQ,(short)freq);//+1
	g_clsAudiovideo.sendToApp_HighSchoolBassFreqValue(0x02,freq);
}

void halToAudio_TrebLevel(unsigned char level){
	LOGD("halToAudio_TrebLevel:%d",level);
	pLocalParam->trebPos = level;
	setAnalogData(CONTROLID_AUDIO_TREB_GAUGE,(short)level);
	g_clsAudiovideo.sendToApp_HighSchoolBassLevelValue(0x02,level);
}

void halToAudio_MidFreq(unsigned char freq){
	pLocalParam->mid = freq;
	setAnalogData(CONTROLID_AUDIO_MID_FREQ,(short)freq);//+1
	g_clsAudiovideo.sendToApp_HighSchoolBassFreqValue(0x01,pLocalParam->mid);
}

void halToAudio_MidLevel(unsigned char level){
	pLocalParam->midPos = level;
	setAnalogData(CONTROLID_AUDIO_MID_GAUGE,(short)level);
	g_clsAudiovideo.sendToApp_HighSchoolBassLevelValue(0x01,level);
}

void halToAudio_BassFreq(unsigned char freq){
	pLocalParam->bass = freq;
	setAnalogData(CONTROLID_AUDIO_BASS_FREQ,(short)freq);//+1
	g_clsAudiovideo.sendToApp_HighSchoolBassFreqValue(0x00,pLocalParam->bass);
}

void halToAudio_BassLevel(unsigned char level){
	pLocalParam->bassPos = level;
	setAnalogData(CONTROLID_AUDIO_BASS_GAUGE,(short)level);
	g_clsAudiovideo.sendToApp_HighSchoolBassLevelValue(0x00,level);
}

void halToAudio_LoudnessFreq(unsigned char freq){
	pLocalParam->loudness = freq;
	setAnalogData(CONTROLID_AUDIO_LOUD_FREQ,(short)freq);//+1
}

void halToAudio_LoudnessLevel(unsigned char level){
	pLocalParam->loudnessPos = level;
	setAnalogData(CONTROLID_AUDIO_LOUD_GAUGE,(short)level);
}

void setEQValue(int pos, unsigned char EQValue){
	if(pos < 0 || pos > 10){
		return;
	}

	if(EQValue > 24){
		return;
	}
	
	setAnalogData(CONTROLID_EQ_GAUGE_SEEKBARGAUGE_BEGIN + pos, (short)EQValue);
}

void halToAudio_EQALL(unsigned char *EQs, int len){
	LOGI("***************EQValue start***********************");
	int i = 0;
	for(;i<10;i++)
	{
		pLocalParam->EQValue[i] = EQs[i];
		LOGI("halToAudio_EQALL:%d,%d", i, pLocalParam->EQValue[i]);
		setEQValue(i, EQs[i]);
		g_clsAudiovideo.sendToApp_EQFreqValue(i, EQs[i]);
	}
	LOGI("***************************************************");
}

void halToAudio_SingleEQValue(unsigned char indexfreq, unsigned char value){

	pLocalParam->EQValue[indexfreq] = value;

	setEQValue(indexfreq, value);
	g_clsAudiovideo.sendToApp_EQFreqValue(indexfreq, value);
}

void halToAudio_InnerEQSetting(unsigned char type){
	pLocalParam->settingIndex = type;
	appToAudioVideo_displayEQType(type);
	g_clsAudiovideo.sendToApp_EQPresetValue(type);
}

void halToAudio_SaveCustomEQSetting(unsigned char param)
{
	LOGD("[%s] param:%x",__FUNCTION__,param);
	switch(param)
	{
		case 0x00:
			break;
		case 0x01:
			break;
		case 0x02:
			break;
		default:break;
	}
	if(param == 0x00 || param == 0x01 || param == 0x02)
	{
		appToAudio_SurroundIndex_MouseDown(CONTROLID_EQ_RECORD_1+param);
	}
}

void halToAudio_Position(unsigned char pos){

	pLocalParam->soundPos = pos;
	setProgressRange(CONTROLID_AUDIO_LISTENPOS,(int)pos);
	setProgressRange(CONTROLID_AUDIO_SCROLLBAR_LISTENPOS,(int)pos);
}

void halToAudio_MixedNaviVoice(char mixedVoice){
	pLocalParam->mixedNaviVoiceState = mixedVoice;
	if(pLocalParam->notifyAppForMixedNaviVoice){
		pLocalParam->notifyAppForMixedNaviVoice = 0;
		setMixedExternalAppVoiceState(mixedVoice);
	}
}

void halToAudio_LoudnessSwitch(char onOFF){
	pLocalParam->bIsLoudnessOn = (int)onOFF;
	Display_LoudNessOnOFF();
	g_clsAudiovideo.sendToApp_LoudnessSwitchStatus(onOFF);
}

void halToAudio_SubSwitch(char onOFF){
	pLocalParam->subState = onOFF;
	appToAudiovideo_Display_SubOnOFF();

}

void halToAudio_SubFilter(unsigned char subFilter){
	appToAudiovideo_Display_SubFilter(subFilter);

}

void halToAudio_SubLevel(unsigned char subLevel){

	pLocalParam->subLevel = subLevel;
	appToAudio_Display_ScrollSubLevel();

}

void halToAudio_SoundFunData(u8 *str,int len)
{
	u8 *pUnicodeBuf = (u8*)malloc(len*2+2);
	memset(pUnicodeBuf, 0, len*2+2);
	int nUnicodeBufLen = ansi_str_to_unicode16(str, (unicode16_t*)pUnicodeBuf);
	setSerialData(CONTROLID_AUDIO_SET_PARAM_TXT,pUnicodeBuf,nUnicodeBufLen*2);
	free(pUnicodeBuf);

}

void halInit_audio(void){
//		audioToHal_Init(0x01);
//		audioToHal_SetSoundChannel(0x01);	// DVD soundChannel
//		audioToHal_SetMute(0x00);
//		audioToHal_SetVolume(40);	// 0~60
}

void halToAudio_IsMuteState(u8 p)
{
	g_clsAudiovideo.sendToFlyJniSdkCurCDIsMute(p);
}

void halToAudio_WetherToPullDownOSD_VolumeChange(bool s)
{
	if(s == true)//Drop down OSD!!!
	{
		if(pLocalParam->bMuteIsOsd == true)
		{
			u16 curPage = 0;
			u8 curpageLen = 0;
			getOtherModuleParam(MODULE_ID_SYSTEM, CUR_PAGE, (u8*)&curPage, &curpageLen);
			switch(curPage)
			{
				case PAGE_BLACK:
				case PAGE_BACK_VIDEO:
				case PAGE_BACK_RADAR:
				case PAGE_BACK_FULL_VIDEO:
				case PAGE_BACK_FULL_VIDEO_CONTROL:
				case PAGE_BACK_VIDEO_T123COLORSET_PAGE:
				{
					//Not allowed to display drop-down OSD!!!
				}
				break;
				default:
				{
					audioVideoToModule_NotifyOSD_ShowVolumeOsd();
				}
				break;
			}//switch
		}
		else
		{
			//The UI interface has been expressed and the drop-down OSD will block the interface operation, so you do not need to pull down OSD.
		}

		pLocalParam->bMuteIsOsd = true;
		
	}
	else//Don't drop-down OSD!!!
	{
	}
}

void getCurChannelIsMuteSysMediaSound(int nChannel)
{
	switch(nChannel)
	{
		/*
		case  CHANNEL_NOCHANNEL:
		case  CHANNEL_DVD_CTRL:
		case  CHANNEL_DVD_VIDEO:
		case  CHANNEL_CDC_CTRL:
		case  CHANNEL_CDC_VIDEO:
		case  CHANNEL_RADIO:�
		case  CHANNEL_AUX_CTRL:
		case  CHANNEL_AUX_VIDEO:
		case  CHANNEL_IPOD_CTRL:
		case  CHANNEL_IPOD_VIDEO:
		case  CHANNEL_TV_CTRL:
		case  CHANNEL_TV_VIDEO:
		case  CHANNEL_SRADIO:
		case  CHANNEL_DVR_CTRL:
		case  CHANNEL_DVR_VIDEO	:
		case  CHANNEL_DNV_CTRL:
		case  CHANNEL_DNV_VIDEO:
		case  CHANNEL_BACK_VIDEO:
		case  CHANNEL_BACK_NOVIDEO:
			break;
		*/
		case CHANNEL_MP3:
		case CHANNEL_BT:
		case CHANNEL_SPEECH_MEDIA_CTRL:
		case CHANNEL_THREECHANNEL:
			setIsMute_CurSysMediaChannelToApp(0);
		break;
		default:
			setIsMute_CurSysMediaChannelToApp(1);
		break;
	}

}

void analyseHalMessage_AUDIO(unsigned char resCmd, unsigned char *param, unsigned char len){
	LOGD("[%s] resCmd %x param[0] %x param[1] %x len:%x",__FUNCTION__,resCmd,param[0],param[1],len);
	switch(resCmd){
		case 0x01:
			halToAudio_InitCmd(param[0]);  //
			break;
		case 0x02:
			halToAudio_InitState(param[0]);	//
			break;
		case 0x08:
			halToAudio_SoundCardState(param[0]);
			break;
		case 0x10:
			halToAudio_SoundChannel(param[0]);//
			break;
		case 0x12:
			halToAudio_Volume(param[0]);	//
			break;
		case 0x13:
			halToAudio_LRBalance(param[0]);//
			break;
		case 0x14:
			halToAudio_FRFader(param[0]);	//
			break;
		case 0x15:
			halToAudio_TrebFreq(param[0]);	//
			break;
		case 0x16:
			halToAudio_TrebLevel(param[0]);	//
			break;
		case 0x17:
			halToAudio_MidFreq(param[0]);	//
			break;
		case 0x18:
			halToAudio_MidLevel(param[0]);	//
			break;
		case 0x19:
			halToAudio_BassFreq(param[0]);	//
			break;
		case 0x1A:
			halToAudio_BassLevel(param[0]);	//
			break;
		case 0x1B:
			halToAudio_LoudnessFreq(param[0]);	//
			break;
		case 0x1C:
			halToAudio_LoudnessLevel(param[0]);	//
			break;
		case 0x1D:
			halToAudio_EQALL(param, (int)len);	//
			break;
		case 0x1E:
			halToAudio_SingleEQValue(param[0], param[1]);	//
			break;
		case 0x1f:
			halToAudio_AudioChannelVolume(param , len);
			break;
		case 0x21:
			halToAudio_InnerEQSetting(param[0]);	 //
			break;
		case 0x22:
			halToAudio_SaveCustomEQSetting(param[0]);
			break;
		case 0x23:
			halToAudio_Position((char)param[0]);	//
			break;
		case 0x24:
			halToAudio_MixedNaviVoice((char)param[0]);//
			break;
		case 0x25:
			break;
		case 0x26:
			halToAudio_IsMuteState(param[0]);
			break;
		case 0x27:
			{
				if(param[0] == 0x01)
					halToAudio_WetherToPullDownOSD_VolumeChange(true);
			 	else if(param[0] == 0x00)
					halToAudio_WetherToPullDownOSD_VolumeChange(false);	
			}
			break;
		case 0x30:
			halToAudio_LoudnessSwitch((char)param[0]);//
			break;
		case 0x31:
			halToAudio_SubSwitch((char)param[0]);
			break;
		case 0x32:
			halToAudio_SubFilter(param[0]);
			break;
		case 0x33:
			halToAudio_SubLevel(param[0]);
			break;
		case 0x36:
			halToAudio_SoundFunData(param,len);
			break;
		default:break;
	}
}
/********************************************************************/


void halToVideo_InitCmd(u8 cParam){
	LOGI("*******Video InitCmd*******");
}

void halToVideo_InitState(u8 cParam){
	LOGI("*******Video InitState*******");
}

void halToVideo_VideoChannel(u8 cParam, u8 videoState){
	
	pLocalParam->soundChannel = cParam;
	pLocalParam->videoChannel = videoState;
	bDoSpecial_ChanceSpeechBack = false;

	LOGD("[%s] pLocalParam->soundChannel:%x  pLocalParam->videoChannel:%x",__FUNCTION__,pLocalParam->soundChannel,pLocalParam->videoChannel);
	combineSoundVideoChannel();
}

void halToVideo_SetItemValue(u8 cParam,u8 cValue){
	LOGD("*******halToVideo_SetItemValue*******, type:%x, pos:%d",cParam, cValue);
	audioVideoToModule_NotifyDvd_SetOsdVideSetting(cParam, cValue);
}

void halToVideo_FinishCamera(u8 cParam){
	LOGW("[%s] bIsVideoOpen:%d",__FUNCTION__,cParam);
	pLocalParam->bIsVideoOpen = cParam;
		
	#ifdef MSM8x25
		LOGD("It is a MSM8X25 TAG");
		AudioVideoToApp_SetCameraIsReady();
	#else
	    LOGD("bIsRetrySendCameraReady:%d",pLocalParam->bIsRetrySendCameraReady);
		if(pLocalParam->bIsRetrySendCameraReady){
			AudioVideoToApp_SetCameraIsReady();
			pLocalParam->bIsRetrySendCameraReady = false;
		}
	#endif
}

void halToVideo_whetherToSupport_aboutUsbCamera(u8 state)
{
	LOGD("[%s] state:%d",__FUNCTION__,state);
	pLocalParam->bIsSupportUsbCamera = state;
}

void analyseHalMessage_VIDEO(unsigned char resCmd, unsigned char *param, unsigned char len){
	switch(resCmd){
		case 0x01: /*��ʼ������*/
			halToVideo_InitCmd(param[0]);
			break;
		case 0x02: /*��ʼ��״̬*/
			halToVideo_InitState(param[0]);
			break;
		case 0x10: /*��Ƶͨ��*/
			halToVideo_VideoChannel(param[0],param[1]);
			break;
		case 0x11: /*��Ƶ������ֵ*/
			halToVideo_SetItemValue(param[0], param[1]);
			break;
		case 0x21: /*�����Ƿ���Խ�����Ƶ��8803ר�ã�*/
			halToVideo_FinishCamera(param[0]);
			break;
		case 0xF0:
			halToVideo_whetherToSupport_aboutUsbCamera(param[0]);
			break;
		default:break;
	}
}

void halToAudio_AudioChannelVolume(u8  *param, u8 len)
{
	LOGD("%s  Channel:%x    Volume:%x",__FUNCTION__,param[0],param[1]);
	switch(param[0])
	{
		case 0x00:
		{
			if(pLocalParam->sdkMediaVolume == param[1])
				return;
			pLocalParam->sdkMediaVolume = param[1];
		}
			break;
		case 0x01:
		{
			if(pLocalParam->sdkCallingVolume == param[1])
				return;
			pLocalParam->sdkCallingVolume = param[1];
		}
			break;
		default:break;
	}
	g_clsAudiovideo.sendToSdk_AudioCurChannelVolume(param[0],param[1]);
}
