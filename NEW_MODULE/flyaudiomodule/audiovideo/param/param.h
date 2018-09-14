#ifndef __PARAM_H__
#define __PARAM_H__

//moupeng 2015/7/25
#include "CNotifyAndResponseFlyJniSdk.h"

//enum EQ_Type{EQ_NOCLASS = 0,EQ_CLASS = 1,EQ_POP = 2,EQ_RECORD1= 3,EQ_RECORD2 = 4,EQ_RECORD3 = 5};

#define M8803

#define LIDBG_HOLD_HOOTANIM "lidbg.hold_bootanim"

#define MIXED_NAVI_VOICE_STATE_GPS			(1)
#define MIXED_NAVI_VOICE_STATE_TPMS			(1<<1)
#define MIXED_NAVI_VOICE_STATE_APPCLOCK		(1<<2)


//å…³èƒŒå…‰
#define LCD_CLOSE					0
#define LCD_OPEN					1
#define LCD_OPEN_DEFAULT_TIME		7000 //ms
#define TIME_CYCLE_ENTER_OR_EXIT_VIDEO						1000

#define PROGRESSIVE_VOLUME_LEVEL   3

#define TIME_CYCLE_ENTER_OR_EXIT_VIDEO_3561	 0 //Goto BackVideo

typedef struct {
	char str_WhichProject[20];
	u8 uModuleAudio_is_T123;
	
	// Temporary variable
	int setMode;		// setting mode
	int savemode;		// storage mode, mainly for booting system
	int volumeSet;		// system volume setting
	int gpsSoundOn;		// GPS voice whether turn on;
	
	// For save variable
	int getVolumeTimes;

	short soundChannel;	// current sound channel
	short videoChannel;	// video sound channel
	short soundVideoChannel;	// audio & video mixed channel
	short oldsoundVideoChannel;
	short lastMediaChannel;
	
	int volume;
	int mute;
	
	int balance;	// left right balance
	int fader;		// front rear balance
	int soundPos;	// listening voice position
	
	int bass;
	int treb;
	int loudness;
	int mid;
	int bassPos;	// bass center freq
	int trebPos;	// treb center freq
	int loudnessPos;	// loudness center freq
	int midPos;		// mid center freq;
	
	int EQCount;	// EQ level		9Level 10Level
	int EQ;			// EQ mode storage
	int settingIndex;	// current setting EQ level   EQ_NOCLASS
	int preSettingIndexControl;
	unsigned char EQValue[16];
	unsigned char EQUser1[16];
	unsigned char EQUser2[16];
	unsigned char EQUser3[16];
	// inner QE mode value
	unsigned char EQClassic[16];
	unsigned char EQPopular[16];
	unsigned char EQJazz[16];
	unsigned char EQRock[16];
	unsigned char EQDefault[16];
	// FineTurning 
	unsigned char fineTurningValue[16];
	
	bool bIsLoudnessOn;
	int subState;		// Sub On or OFF
	char subFilter;	// Sub Filter Value
	char subLevel;		// Sub Level Value
	
	int sleepMode;		// sleep mode 
	int tvStatus;		// TV status

	int imEQ;
	
	u8 soundcardSoundState;
	int preGpsSoundState;
	int gpsSoundState;
	int gpsSoundMark;
	int gpsSoundTimerING;

	int soundcardStateChangeING;
	u8 OSDSetToModule;
	int firstDisplayEQFlag;

	int bIsRetrySendCameraReady;
	int bIsVideoOpen;
	int bIsSameVideoForCamera;

	int readVolTemp;
	int readPowerOnEQTemp;

	u8 mixedNaviVoiceState;
	int canNotSetMixedNaviVoice;
	u8 notifyAppForMixedNaviVoice;

	int Car_type_version;
	int Default_channel;

	bool b_IsRequestvoice_state;/*ï¿½ï¿½ï¿½ó²¥±ï¿½ï¿½ï¿½ï¿½ï¿½*/
	bool b_MediaPlaying;/*Mediaï¿½ï¿½ï¿½ï¿½×´Ì¬*/
	bool b_mixsound;/*ï¿½ï¿½ï¿½ï¿½×´Ì¬ï¿½ï¿½ï¿½ï¿½ã±¨Ê±PAUSEï¿½ï¿½DVD*/
	bool bIsMixingSwitch;

	bool b_autoJumpAux;

	u8 uThirdPlayState;
	u8 uMaxVol;
	bool bTimeKeeperState;
	int AvAmplitude;

	//prado
	int m_nPradoAsl;
	int m_nPradoSurround;

	//buding
	u8 m_u8ChannelHaveSetToHal;
	u8 uEnableMixVoiceState;
	
	bool bMuteIsOsd;
	bool bIsSupportUsbCamera;

	u8 sdkCallingVolume;
	u8 sdkMediaVolume;

}audiovideo_local_param_t;

typedef struct{
	int soundMode;
	int volume;
	int balance;	// ï¿½ï¿½ï¿½ï¿½Æ½ï¿½ï¿½
	int fader;		// Ç°ï¿½ï¿½Æ½ï¿½ï¿½
	int soundPos;	// ï¿½ï¿½ï¿½ï¿½Î»ï¿½ï¿½
	int bass;		// 
	int treb;
	int loudness;
	int mid;
	int bassPos;
	int trebPos;
	int loudnessPos;
	int midPos;

	int EQ; //ï¿½ï¿½ï¿½ï¿½EQÄ£Ê½ï¿½æ´¢
	
	unsigned char EQValue[16];
	unsigned char EQUser1[16];
	unsigned char EQUser2[16];
	unsigned char EQUser3[16];

	unsigned char fineTurningValue[16];
}audiovideo_global_param_t;


extern audiovideo_local_param_t *pLocalParam;
extern audiovideo_global_param_t *pGlobalParam;
//moupeng 2015/7/25
extern CNotifyAndResponseFlyJniSdk g_clsAudiovideo;

void readParameter(void);
void saveParameter(void);
void readHalProperty_aboutMaxVolumeVal();


typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;

// ËùÓÐº¯Êý²»¶ÔÖ¸ÕëÔ½½ç´¦Àí
// ·µ»Øunicode16µÄ×Ö·û¸öÊý
uni16_size_t uni16_strlen(const unicode16_t *uni16);
// ½«±ê×¼×Ö·û×ª»»³Éunicode16µÄ×Ö·û
unicode16_t ansi_to_unicode16(const unsigned char ansi);
// ½«±ê×¼×Ö·û´®×ª»»³Éunicode16µÄ×Ö·û´®
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);

int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);

#endif
