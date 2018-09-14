#ifndef __HAL_RESPONSE_COMMAND_AUDIOVIDEO_H__
#define __HAL_RESPONSE_COMMAND_AUDIOVIDEO_H__

#include "global.h"
#include "messageQueue.h"


#define HALTOAUDIO_INIT_CMD					0x01
#define HALTOAUDIO_INIT_STATE				0x02
#define HALTOAUDIO_SOUND_CHANNEL			0x10
#define HALTOAUDIO_VOLUME					0x12
#define HALTOAUDIO_LEFTRIGHT_BALANCE		0x13
#define HALTOAUDIO_FRONTREAR_BALANCE		0x14
#define HALTOAUDIO_TREB_FREQ				0x15
#define HALTOAUDIO_TREB_LEVEL				0x16
#define HALTOAUDIO_MID_FREQ					0x17
#define HALTOAUDIO_MID_LEVEL				0x18
#define HALTOAUDIO_BASS_FREQ				0x19
#define HALTOAUDIO_BASS_LEVEL				0x1A
#define HALTOAUDIO_LOUDNESS_FREQ			0x1B
#define HALTOAUDIO_LOUDNESS_LEVEL			0x1C
#define HALTOAUDIO_EQALL					0x1D
#define HALTOAUDIO_SINGLE_EQVALUE			0x1E
#define HALTOAUDIO_INNER_EQSETTING			0x21
#define HALTOAUDIO_POS_VALUE				0x23
#define HALTOAUDIO_NAVI_VOICE				0x24
#define HALTOAUDIO_LOUDNESS_SWITCH			0x30
#define HALTOAUDIO_SUB_SWITCH				0x31
#define HALTOAUDIO_SUB_FILTER				0x32
#define HALTOAUDIO_SUB_LEVEL				0x33


void halInit_audio(void);


void analyseHalMessage_AUDIO(unsigned char resCmd, unsigned char *param, unsigned char len);
void analyseHalMessage_VIDEO(unsigned char resCmd, unsigned char *param, unsigned char len);

void halToAudio_SoundFunData(u8 *str,int len);
void halToAudio_IsMuteState(u8 p);
void halToAudio_WetherToPullDownOSD_VolumeChange(bool s);
void getCurChannelIsMuteSysMediaSound(int nChannel);
void halToVideo_whetherToSupport_aboutUsbCamera(u8 state);
void halToAudio_AudioChannelVolume(u8  *param, u8 len);


#endif
