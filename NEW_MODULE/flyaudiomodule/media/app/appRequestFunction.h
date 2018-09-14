#ifndef __APP_REQUEST_FUNCTION_H__
#define __APP_REQUEST_FUNCTION_H__

void mediaToApp_playNext(void);
void mediaToApp_palyPrev(void);


void mediaToApp_stop(void);
void mediaToApp_play(void);
void mediaToApp_pause(void);
void mediaToApp_SendMediaChannelState(u8 bMediaChannel);

void Automate_selectMusic(u8 b);
void Automate_GoToAutoMate(u8 b);
void Automate_getUSBState(u8 b);
void mediaToApp_SetplayMod(u8 b);
void mediaToApp_finishPlay(void);
void mediaToApp_SpecifyToPlayTheSongOrNo(u8 *param, int len);
void mediaToApp_enterMediaChannel_IsNormal(u8 p);



#endif
