#ifndef __OTHERMODULE_REQUEST_FUNCTION_AUDIOVIDEO_H__
#define __OTHERMODULE_REQUEST_FUNCTION_AUDIOVIDEO_H__


//��ָ��ҳ
void audioVideoToModule_NotifySystem_JumpPage(u16 nPageId);
//��ǰһҳ
void audioVideoToModule_NotifySystem_JumpPrePage(void);

void audioVideoToModule_NotifyAuxscreen_SetVolume(unsigned char volume);

void audioVideoToModule_NotifyOtherModule_SetNoticeMode(unsigned char toModule, int newSoundVideoChannel);

void audioVideoToModule_NotifyOtherModule_NoticeSoundChannel(int oldSoundVideoChannel,int curSoundVideoChannel);


void audioVideoToModule_NotifySystem_FirstEnterSoundMode(void );
void moduleToAudioVideo_FromAudioVideo_SetSoundVideoChannel(u8 param);


void audioVideoToModule_NotifyOsd_DisplayOSDVolume(unsigned char vol);
void audioVideoToModule_NotifyOsdModule_ViewSwitch(unsigned char param);
void audioVideoToModule_NotifyOsdModule_OSDPage(unsigned char param);

void audioVideoToModule_NotifyOSD_ShowVolumeOsd(void);

void audioVideoToModule_NotifyDvd_SetOsdVideSetting(unsigned char type, unsigned char value);

void audioVideoToModule_NotifyOSD_SendOsdDebugInfo(void);

void setTimerCloseVideo(void);

void audioVideoToModule_NotifySystem_StartGPS(void);
void audioVideoToModule_NotifyRadio_Init(u8 p);

void NotifySystem_StartGPS(u8 p);
void audioVideoToModule_NotifyExternalctrl_EndTheVoice();
void audioVideoToModule_NotifySystem_JumpToCurMediaPage();
void audioVideoToModule_NotifyMediaModule_IsNormalToMediaChannel(u8 p);

#endif
