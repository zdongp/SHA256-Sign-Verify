#ifndef __APP_RESPONSE_FUNCTION_H__
#define __APP_RESPONSE_FUNCTION_H__

void analyseSpeechCtrlCmdToFlyaudio(unsigned char *param, unsigned char paramLen);
void analyseRemoteAppInfors(u8 *param, u8 paramLen);

void ExternalCtrlModuleToApp_aboutMCU();
void ExternalCtrlModuleToApp_aboutBarcode();
void ExternalCtrlModuleToApp_aboutBluetoothVersion();
void ExternalCtrlModuleToApp_aboutMPEG();
void ExternalCtrlModuleToApp_End();

void GetSpeechAppAudioStatusMsg(unsigned char *param, unsigned char paramLen);
void RemoteDureOsVoicePageState(u8 p);

#endif
