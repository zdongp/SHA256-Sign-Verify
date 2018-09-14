#ifndef __OTHER_MODULE_RESPONSE_FUNCTION_H__
#define __OTHER_MODULE_RESPONSE_FUNCTION_H__



void moduleToAudioVideo_FromSystem_Message(unsigned char *param, unsigned char len);
void moduleToAudioVideo_FromKey_Message(unsigned char *param, unsigned char len);
void moduleToAudioVideo_FromAudioVideo_Message(unsigned char *param,unsigned char len);
void moduleToAudioVideo_FromSync_Message(unsigned char *param,unsigned char len);

void moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(unsigned char channel);
void moduleToAudiovideo_FromCenter_Message(unsigned char *param, unsigned char len);

void moduleToAudioVideo_FromTVOrDvd_Message(unsigned char *param, unsigned char len);


void moduleToAudioVideo_FromBlueTooth_Message(unsigned char *param, unsigned char len);

void moduleToAudioVideo_FromTmps_Message(unsigned char *param, unsigned char len);

void moduleToAudiovideo_FromCenter_AnalyseGpsSoundState(unsigned char state);
void moduleToAudiovideo_FromCenter_AnalyseApp_SimulationOfGPS_Process_RequestMixedVoice(unsigned char state);

void moduleToAudioVideo_FromMedia_Message(u8* param,u8 len);
void moduleToAudioVideo_FromExternalCtrl_Message(u8* param,u8 len);
void moduleToAudioVideo_FromExtcar_Message(u8* param,u8 len);
void moduleToAudioVideo_FromAutomate_Message(unsigned char *param,unsigned char len);

void moduleToAudioVideo_SoundHandle(u8* param,u8 len);

void audioVideoToModule_NotifyOSDModule_AccordingtoChannel(int param);
void audioVideoToModule_NotifyOSDModule_PageChange(u32 enterPageID);

void updatePradoAudio(void);
void requestPradoAudio(void);
int getBackCarMode(void);

void enterOrExitVideoPreProcess(u8 p);
void SendVideoChannel_enterOrExitVideoPreProcess(u8 uChannel,u8 p,u8 iVideo);

void RequestAudioFocus(u8 p);
void RequestAudioMuteOrUnMute(u8 p);

void PageChange_ToPlayback();

bool isInThePageWithSoundChannel(u16 pageId);
int isInThePageOfDnvOrDvr(u16 pageId);

#endif
