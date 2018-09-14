#ifndef __HAL_REQUEST_COMMAND_AUDIOVIDEO_H__
#define __HAL_REQUEST_COMMAND_AUDIOVIDEO_H__



#define AUDIOTOHAL_SIMKEY_MUTE				0x01
#define AUDIOTOHAL_SIMKEY_BALANCE_INC		0x02
#define AUDIOTOHAL_SIMKEY_BALANCE_DEC		0x03
#define AUDIOTOHAL_SIMKEY_FADER_INC			0x04
#define AUDIOTOHAL_SIMKEY_FADER_DEC			0x05
#define AUDIOTOHAL_SIMKEY_TREBFREQ			0x06
#define AUDIOTOHAL_SIMKEY_TREB_INC			0x07
#define AUDIOTOHAL_SIMKEY_TREB_DEC			0x08
#define AUDIOTOHAL_SIMKEY_MIDFREQ			0x09
#define AUDIOTOHAL_SIMKEY_MID_INC			0x0A
#define AUDIOTOHAL_SIMKEY_MID_DEC			0x0B
#define AUDIOTOHAL_SIMKEY_BASSFREQ			0x0C
#define AUDIOTOHAL_SIMKEY_BASS_INC			0x0D
#define AUDIOTOHAL_SIMKEY_BASS_DEC			0x0E
#define AUDIOTOHAL_SIMKEY_LOUDNESSFREQ		0x0F
#define AUDIOTOHAL_SIMKEY_LOUDNESS_INC		0x10
#define AUDIOTOHAL_SIMKEY_LOUDNESS_DEC		0x11
#define AUDIOTOHAL_SIMKEY_SUBLEVEL_INC		0x12
#define AUDIOTOHAL_SIMKEY_SUBLEVEL_DEC		0x13

#define AUDIOTOHAL_SOUNDCH_INIT			0x00
#define AUDIOTOHAL_SOUNDCH_DVD			0x01
#define AUDIOTOHAL_SOUNDCH_CDC			0x02
#define AUDIOTOHAL_SOUNDCH_RADIO		0x03
#define AUDIOTOHAL_SOUNDCH_AUX			0x04
#define AUDIOTOHAL_SOUNDCH_IPOD			0x05
#define AUDIOTOHAL_SOUNDCH_TV			0x06
#define AUDIOTOHAL_SOUNDCH_MP3			0x07
#define AUDIOTOHAL_SOUNDCH_SRADIO		0x08
#define AUDIOTOHAL_SOUNDCH_BT			0x09
#define AUDIOTOHAL_SOUNDCH_EXT_TEL		0x0A
#define AUDIOTOHAL_SOUNDCH_3G			0x0B

#define AUDIOTOHAL_INNEREQ_NONE			0x00
#define AUDIOTOHAL_INNEREQ_DEFAULT		0x01
#define AUDIOTOHAL_INNEREQ_CLASSICAL	0x02
#define AUDIOTOHAL_INNEREQ_POPULAR		0x03
#define AUDIOTOHAL_INNEREQ_ROCK			0x04
#define AUDIOTOHAL_INNEREQ_JAZZ			0x05
#define AUDIOTOHAL_INNEREQ_USER1		0x10
#define AUDIOTOHAL_INNEREQ_USER2		0x11
#define AUDIOTOHAL_INNEREQ_USER3		0x12

#define AUDIOTOHAL_SAVE_USER1			0x00
#define AUDIOTOHAL_SAVE_USER2			0x01
#define AUDIOTOHAL_SAVE_USER3			0x02

#define AUDIOTOHAL_PHONESTATE_NOCALL	0x00
#define AUDIOTOHAL_PHONESTATE_CALLIN	0x01
#define AUDIOTOHAL_PHONESTATE_CALLING	0x02
#define AUDIOTOHAL_PHONESTATE_CALLOUT	0x03

#define AUDIOTOHAL_POS_CENTER			0x00
#define AUDIOTOHAL_POS_DRIVER			0x01
#define AUDIOTOHAL_POS_SUBDRIVER		0x02


void combineSoundVideoChannel(void);


void audioToHal_Init(char param);
void audioTohal_InitParamCmd(u8 *param,int len);
void audioToHal_SimulateKey(unsigned char key);
void audioToHal_SetSoundChannel(unsigned char soundChannel);
void audioToHal_SetMute(char mute);
void audioToHal_SetVolume(unsigned char volume);
void audioToHal_Balance(unsigned char balance);
void audioToHal_Fader(unsigned char fader);
void audioToHal_SetTrebFreq(unsigned char TredFreq);
void audioToHal_SetTredLevel(unsigned char TredLevel);
void audioToHal_SetMidFreq(unsigned char MidFreq);
void audioToHal_SetMidLevel(unsigned char MidLevel);
void audioToHal_SetBassFreq(unsigned char BassFreq);
void audioToHal_SetBassLevel(unsigned char BassLevel);
void audioToHal_SetLoudnessFreq(unsigned char LoudnessFreq);
void audioToHal_SetLoudnessLevel(unsigned char LoudnessLevel);
void audioToHal_SetEQAll(unsigned char *Eqs, int len);
void audioToHal_SetSingleEQValue(unsigned char EqFreq, unsigned char EqValue);
void audioToHal_SetSingleEQKey(unsigned char EqFreq, unsigned char EqKey);
void audioToHal_SetInnerEQSetting(unsigned char eqType);
void audioToHal_SaveUserEQSetting(unsigned char userEQ);
void audioToHal_SetPOSValue(unsigned char posValue);
void audioToHal_SetMixedNaviVoice(char mixedNaviVoice);
void audioToHal_NotifyAmplitude(u8 cAmplitude);
void audioToHal_NotifySpeechState(u8 p);
void audioToHal_NotifySpeechState_New(u8 p);
void audioToHal_SetLoudnessSwitch(bool switchOn);
void audioToHal_SetSubSwitch(char switchOn);
void audioToHal_SetSubFilter(unsigned char subFilter);
void audioToHal_SetSubLevel(unsigned char subLevel);
void audioToHal_EnableMixVoice(u8 state);
//void audioToHal_SetLoudness
void audioToHal_soundFunctionParamSet(u8 uP);

void audioToHal_SetStartVolume(unsigned char volume);





/*******************************************************************/
void videoToHal_Init(u8 param);
void videoToHal_SetVideoChannel(u8 ch,u8 videoState);//������Ƶͨ��
void videoToHal_ColorStepRegulate(u8 state);//ɫ�ʵ�������

void setToHalBackCarMode(u8 p);


//
void setToHalSystemLcd(unsigned char p, int t);
void SetVideoChannel_videoToHal_enterOrExitVideoPreProcess(u8 ch,u8 videoState,int nTimes);

#endif
