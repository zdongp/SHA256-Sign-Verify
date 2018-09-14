#ifndef __OTHER_MODULE_REQUEST_FUNCTION_H__
#define __OTHER_MODULE_REQUEST_FUNCTION_H__

void externalctrlToModule_NotifySystem_SwitchModule(void);
void externalctrlToModule_NotifySystem_jumpPage(u16 pageId);
void externalctrlToModule_NotifySystem_jumpPrePage(void);

void ExternalCtrlToAudiovideo_SetVol(u8 *cmd,u8 len);
void ExternalCtrlToRadio_SetRadio(u8 *cmd,u8 len);
void ExternalCtrlToOtherModule_SetPlayState(u8 cmd);
void ExternalCtrlToKeyModule(u8 *param,u8 len);
void ExternalCtrl_FlyauidioApp_Management(u8 *param,u8 len);
void ExternalCtrlToAC_Message(u8 *param,u8 len);
void ExternalCtrlToBt_Message(u8 *param,u8 len);
void ExternalCtrlToSystem_Message(u8 *param,u8 len);
void ExternalCtrlToSystem_about_JumpPageMessage(u8 *param,u8 len);

void ExternalCtrlToAudiovideo_aboutSpeechApp_MediaState(u8 cmd);
void ExternalCtrlToAudiovideo_aboutSpeechState(u8 cmd);
void ExternalCtrlToAudiovideo_SetChannel(u8 cmd);

void ExternalCtrlToAudiovideo_EndSpeechToThelastAudioChannel(u8 cmd);
void ExternalCtrlToSysModule_MicUsingState(u8 param);
void ExternalCtrlToAudiovideo_aboutSpeechState_New(u8 cmd);
void externalctrlToMediaModule_VoiceStatus(u8 ToMode,u8 param);

#endif
