#pragma once
#include "FlyJniSdkModule.h"


class CFlyJniSdkModuleAudioVideo : public CFlyJniSdkModule
{
public:
	CFlyJniSdkModuleAudioVideo(void);
	virtual ~CFlyJniSdkModuleAudioVideo(void);
	void getAudioVideoMessage(u8 *p, u8 len);
	void onAudioVideoSoundVideoChannel(u8 p);	
	void getAppCtrlMessage(u8 *p, u8 len);	
	void SetAudioVideo_Channel(u8 p);
	void onAudioVideoSoundIsMute(u8 p);
	void onAudioVideoIsAndroidChannel(u8 p);
	void analyseAudioVideoAppMessageType(u8 *p, u8 len);
	void analyseAudioVideoControlAudioOperationMassage(u8 *buf ,u8 len);
	void analyseReturnAudioStatusMassage(u8 *buf ,u8 len);
	void sendToAudioSetMute(u8 param);
	void sendToAudioSetMute_NoOSD(u8 param);
	void sendToAudioSetVolume(u8 *param,int len);
	void sendToAudiogetCurVolumeValue(u8 param);
	void sendToAudioSetSpecificVolume(u8 param);
	void sendToAudiogetCurAudioChannel(u8 param);
	void sendToAudioSetChangeAudioChannel(u8 param);
	void sendToAudiogetCurEQFreqPointValue(u8 param);
	void sendToAudiogetCurEQPresetValue(u8 param);
	void sendToAudiogetCurHighSchoolBassValue(u8 param,u8 param1);
	void sendToAudiogetCurSoundBalanceValue(u8 param);
	void sendToAudiogetCurLoudnessValue(u8 param);
	void sendToAudioSetEQFreqPointValue(u8 param,u8 param1);
	void sendToAudioSetEQPresetValue(u8 param);
	void sendToAudioSetSaveEQCustomValue(u8 param);
	void sendToAudioSetHighSchoolBassValue(u8 param,u8 param1);
	void sendToAudioSetHighSchoolBassFreqSwitch(u8 param,u8 param1);
	void sendToAudioSetSoundBalance(u8 param,u8 param1);
	void sendToAudioSetLoudnessSwitch(u8 param);	
	void sendToAudiogetCurChannelVolume(u8 *buf,int len);
	void sendToAudioSetVolumeAddOrRed(u8 *param,int len);
	/****************send To App*****************/
	void sendToAppCurVolumeValue(u8 *param,int len);

	//
	void sendToAudioRequestFocus(u8 param);
	void sendToAudioRequestMuteOrUnMute(u8 param);
};

