#ifndef __VOICELOGIC_H__
#define __VOICELOGIC_H__

void getVoiceStatus(u8 *param,int len);
void analyseVoiceStatus(u8 *param,int len);
void getVoiceForStartStatus();
void getVoiceForQuitStatus();
void quitVoiceCtrlMediaPlay(u8 param);
#endif
