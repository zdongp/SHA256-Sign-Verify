#ifndef __APP_REQUEST_FUNCTION_DVD_H__
#define __APP_REQUEST_FUNCTION_DVD_H__

void externalCtrlToSpeechApp_StartSpeechRecognitionActivity();
void externalCtrlToSpeechApp_RequestCtrlCmd(u8 p);

void externalCtrlToRemoteDiagnosticsApp_SysInfors(u8 *p,int len);
void externalCtrlToApp_selectedSongs(u8 p);
void externalCtrlToApp_CtrlVoiceSwitch(u8 p);


#endif
