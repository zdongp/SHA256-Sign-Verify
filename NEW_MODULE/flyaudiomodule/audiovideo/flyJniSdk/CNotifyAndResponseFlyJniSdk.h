//moupeng 2015/7/25
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <flyutils/debug.h>
#include <cstring>
#include "global.h"
#include "otherModuleRequestCommand.h"
#include "otherModuleRequestFunction.h"
#include "moduleParamRequest.h"

#define MESSAGETYPE_STATUS			0x00
#define MESSAGETYPE_CONTROL		0x01

class  CNotifyAndResponseFlyJniSdk
{
public:
    CNotifyAndResponseFlyJniSdk();
     ~CNotifyAndResponseFlyJniSdk();
    void  sendToFlyJniSdkSoundVideoChannel(u8 soundChannel);
	void  analyseFromFlyJniSdkMessage(unsigned char *p,int len);
	void sendToFlyJniSdkCurCDIsMute(u8 p);
	void sendToFlyJniSdkCurAudioIsAndroidChannel(u8 p);
	void sendToFlyJniSdkCurVolumeValue(u8 max,u8 min ,u8 param);
	void sdkToAudioVideoSetVolumeSpecificValue(u8 param , u8 MaxValue);

	void sendToAppAudioStatusInfo(u8 *buf,int len);

	void sendToApp_AudioChannelChange(u8 param);
	void sdkToAudioVideoSetVolumeAddOrDec(u8 param,u8 value,u8 curValue,u8 MaxValue);
	void analyseFormSdkMessageAudio(u8 *param, int len);
	void analyseSdkGetHighSchoolBassInfo(u8 *param);
	void sendToApp_EQFreqValue(u8 num, u8 Freq);
	void sendToApp_EQPresetValue(u8 num);
	void sendToApp_HighSchoolBassLevelValue(u8 num,u8 Freq);
	void sendToApp_SoundBalanceValue(u8 num,u8 Freq);
	void sendToApp_HighSchoolBassFreqValue(u8 num,u8 Freq);
	void sendToApp_LoudnessSwitchStatus(u8 status);
	void sendToSdk_AudioCurChannelVolume(u8 sdkSoundChannel,u8 sdkVolume);
	void analyseFromFlyJniSdkGetChannelVolume(unsigned char *p,int len);
	void analyseFromFlyJniSdkSetVolumeAddOrRed(u8 *buf,int len);
};
