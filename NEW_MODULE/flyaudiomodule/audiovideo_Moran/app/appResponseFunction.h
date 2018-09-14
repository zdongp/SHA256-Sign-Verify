#ifndef __APP_RESPONSE_FUNCTION_AUDIOVIDEO_H__
#define __APP_RESPONSE_FUNCTION_AUDIOVIDEO_H__

/*
#define FUNCID_SOUND_DVD_BTN_MUTE	0x10110	//DVDæ≤“Ù	æ≤“Ù∞¥≈•
#define FUNCID_SOUND_RADIO_BTN_MUTE	0x10111	//RADIOæ≤“Ù	
#define FUNCID_SOUND_IPOD_BTN_MUTE	0x10112	//IPODæ≤“Ù	
#define FUNCID_SOUND_USB_BTN_MUTE	0x10113	//USBæ≤“Ù	
#define FUNCID_SOUND_XM_RADIO_BTN_MUTE	0x10114	//XMRADIOæ≤“Ù	
#define FUNCID_SOUND_BLCD_BTN_MUTE	0x10115	//BLCDæ≤“Ù	
*/


	

#define EQ_NOCLASS		0
#define EQ_DEFAULT		1
#define EQ_CLASS		2		
#define EQ_POP			3
#define EQ_ROCK			4
#define EQ_JAZZ			5


#define EQ_RECORD1		0x10
#define EQ_RECORD2		0x11
#define EQ_RECORD3		0x12



void appToAudioVideo_EQ_Gauge_MouseUp(char index, unsigned char *param, unsigned char len);


void appToAudioVideo_EQ_Sound(void);
void appToAudioVideo_EQ_Eq(void);
void appToAudioVideo_EQ_SaveUser(char user);
void appToAudioVideo_EQ_Back(void);
void appToAudioVideo_EQ_Reset(void);

void appToAudioVideo_Audio_Sound(void);
void appToAudioVideo_Audio_Eq(void);
void appToAudioVideo_Audio_Back(void);
void appToAudioVideo_MENUAudio(void);



void appToAudioVideo_Audio_LoudDec_MouseUp(void);
void appToAudioVideo_Audio_LoudDec_MouseDown(void);
void appToAudioVideo_Audio_LoudInc_MouseUp(void);
void appToAudioVideo_Audio_LoudInc_MouseDown(void);

void appToAudioVideo_Audio_TrebDec_MouseUp(void);
void appToAudioVideo_Audio_TrebDec_MouseDown(void);
void appToAudioVideo_Audio_TrebInc_MouseUp(void);
void appToAudioVideo_Audio_TrebInc_MouseDown(void);

void appToAudioVideo_Audio_MidDec_MouseUp(void);
void appToAudioVideo_Audio_MidDec_MouseDown(void);
void appToAudioVideo_Audio_MidInc_MouseUp(void);
void appToAudioVideo_Audio_MidInc_MouseDown(void);

void appToAudioVideo_Audio_BassDec_MouseUp(void);
void appToAudioVideo_Audio_BassDec_MouseDown(void);
void appToAudioVideo_Audio_BassInc_MouseUp(void);
void appToAudioVideo_Audio_BassInc_MouseDown(void);


void appToAudioVideo_Audio_Left_MouseUp(void);
void appToAudioVideo_Audio_Left_MouseDown(void);
void appToAudioVideo_Audio_Right_MouseUp(void);
void appToAudioVideo_Audio_Right_MouseDown(void);
void appToAudioVideo_Audio_Front_MouseUp(void);
void appToAudioVideo_Audio_Front_MouseDown(void);
void appToAudioVideo_Audio_Rear_MouseUp(void);
void appToAudioVideo_Audio_Rear_MouseDown(void);
void appToAudioVideo_Audio_TouchListen(u8 *param, u8 len);
void appToAudio_Scrollbar_faderBalance(u8 *param, u8 len);
void UI_Scrollbar_faderBalanceValue();
void appToAudioVideo_Audio_Param_Reset();

void appToAudioVideo_Audio_TrebDec_MouseTimer(void);
void appToAudioVideo_Audio_TrebInc_MouseTimer(void);
void appToAudioVideo_Audio_MidDec_MouseTimer(void);
void appToAudioVideo_Audio_MidInc_MouseTimer(void);
void appToAudioVideo_Audio_BassDec_MouseTimer(void);
void appToAudioVideo_Audio_BassInc_MouseTimer(void);
void appToAudioVideo_Audio_Left_MouseTimer(void);
void appToAudioVideo_Audio_Right_MouseTimer(void);
void appToAudioVideo_Audio_Front_MouseTimer(void);
void appToAudioVideo_Audio_Rear_MouseTmier(void);


void appToAudioVideo_Audio_LoudFreq_MouseUp(void);
void appToAudioVideo_Audio_LoudFreq_MouseDown(void);
void appToAudioVideo_Audio_TrebFreq_MouseUp(void);

void appToAudioVideo_Audio_TrebFreq_MouseDown(void);

void appToAudioVideo_Audio_MidFreq_MouseUp(void);

void appToAudioVideo_Audio_MidFreq_MouseDown(void);



void appToAudioVideo_Audio_BassFreq_MouseUp(void);

void appToAudioVideo_Audio_BassFreq_MouseDown(void);

/////////////////////



////////////////////////////////////////////////////////////
//Bass+
void BassAdd(void);

//Bass-
void BassSub(void);

//Treb+
void TrebAdd(void);
//Treb-
void TrebSub(void);
//Loud+
void LoudAdd(void);
//Loud-
void LoudSub(void);
//Mid+
void MidAdd(void);
//Mid-
void MidSub(void);
//Front
void FaderSub(void);
//Rear
void FaderAdd(void);
//Left
void BalanceSub(void);
//Right;
void BalanceAdd(void);

/////////////////////////


void Display_LoudNessOnOFF(void);

void appToAudio_DisPlayMuteState(int  mute);

//////////////////11-9/////////////////////////////
void appToAudioVideo_cancelEQSeleted(void);
void appToAudioVideo_displayEQType(int classtype);
void appToAudio_SurroundIndex_MouseUp(int ctrlID);
void appToAudio_SurroundIndex_MouseDown(int ctrlID);

void appToAudio_SetLoudnessSwith();
void appToAudio_SetMix_On_Off();

void clickPradoAsl(u8 mouseEvent);
void clickPradoSurround(u8 mouseEvent);
void clickAudioDataSet(u8 param);
void appToAudio_Eq_Set();
void appToAudio_Eq_Set_box();

#endif
