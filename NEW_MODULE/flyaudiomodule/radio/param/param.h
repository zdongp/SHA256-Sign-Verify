#ifndef __PARAM_H__
#define __PARAM_H__

typedef enum {FM1, FM2, AM}E_RadioChannel;
typedef enum {Ctrl_SCAN = 0x00, Ctrl_SCAN_INC = 0x01, Ctrl_SCAN_DEC = 0x02, Ctrl_STOP = 0x03, Ctrl_SCAN_REPEAT = 0x04, Ctrl_SCAN_REPEAT_INC = 0x05, Ctrl_SCAN_REPEAT_DEC = 0x06}E_CtrlScan;

#define BUTTON_UP 		0
#define BUTTON_DOWN		1
#define BUTTON_DISABLE	2

#define CTRL_ENABLE		1
#define CTRL_DISABLE	0

#define CUR_FREQ_SHU_ZU_SIZE	50

#define CHANNEL_NUM			3
#define CHANNEL_RECORD_NUM	6

//begin   yangzhong  2012-12-31 
#define INPUT_FREQUENCY_MAX_LEN 8
#define FREQUENCY_MAX_PAGE 40
#define SEARCH 1
#define NO_SEARCH 0
#include "CNotifyAndResponseFlyJniSdk.h"


//search state
//#define NOSEARCH 0
//#define CLEAR_AND_SAVE 1
//#define APPEND_AND_SAVE 2

typedef struct 
{
	int len;
	u8 frequencyNumber[INPUT_FREQUENCY_MAX_LEN];
}InputFrequency;

typedef struct
{
	u16 wCurFrequency;
	int cCurRecordIndex;
	u8 cCurRecordNum;
	u16 wRadioFreqRecord[CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE];
	u8 bRadioFreqRecordState[CHANNEL_RECORD_NUM * FREQUENCY_MAX_PAGE];
	//2013-01-07 09:13:46
	short curPage;
	short totalPages;
	//
}ST_RadioChannelRecord;

typedef struct
{	
	u16 usFreqMin;
	u16 usFreqMax;

	u8 uFreqManualStep;
	u8 uFreqScanStep;
	
}ST_RadioInitParamInfors;

typedef struct{
	u8 bIsRadioInitOK;
	E_CtrlScan eScanState;
	u8 bIsRadioPowerOn;
	u8 nFlashState;

	u8 szCurFreq[CUR_FREQ_SHU_ZU_SIZE];
	E_RadioChannel eRadioChannel;
	u8 bIsHasRadioStationAndInfo;
	ST_RadioChannelRecord stszRadioChannelRecord[CHANNEL_NUM];
	u32 dwszCurChannelCurFreqRecFuncID[CHANNEL_NUM];
	u32 dwszCurChannelPreFreqRecFuncID[CHANNEL_NUM];
	u8 bIsNeedCmpWithRecFreq;

	//begin   yangzhong
	u8 isSearch;
	u8 searchSaveIndex;
	u16 fmBeginFreq;
	u16 fmEndFreq;
	u16 amBeginFreq;
	u16 amEndFreq;
	u8 afState;
	u8 taState;
	InputFrequency inputFrequency;
	u8 fmStep;
	u8 amStep;
	u8 curStep;
	u8 scanCtrlType;
	u8 searchBeginIndex;
	u8 sensitivitystate;  /*��̨������״̬*/
	u8 radioTAstate;
	u8 radioAFstate;
	u8 szStationName[256];
	u8 cTAAFVisible;

	bool bUiButtonDownNoShow;
	u8 u8RadioCountryCode;

	ST_RadioInitParamInfors st_RadioInitParamInfors[CHANNEL_NUM];
	unsigned long uPanelKeyTuneTime;
	//end
	
}radio_local_param_t;

/*
	struct FreqPageRecord
	{
		u8 pageIndex;
		u16 wRadioFreqRecord[CHANNEL_RECORD_NUM];
		u8 bRadioFreqRecordState[CHANNEL_RECORD_NUM];
		struct FreqPageRecord *nextFreqPageRecord;
		
	};
	typedef struct
	{
		u16 wCurFrequency;
		//u16 wRadioFreqRecord[CHANNEL_RECORD_NUM];
		u8 cCurRecordIndex;
		u8 cCurRecordNum;
		u8 cCurRecordPage;
		u8 totalRecordPages;
		struct FreqPageRecord *curFreqPageRecord;
		struct FreqPageRecord *curRecordFreqPageRecord;
		//u8 bRadioFreqRecordState[CHANNEL_RECORD_NUM];
		struct FreqPageRecord *freqPageRecord;
	}ST_RadioChannelRecord;

	
	typedef struct{
		u8 bIsRadioInitOK;
		E_CtrlScan eScanState;
		u8 bIsRadioPowerOn;
		u8 nFlashState;
		u8 szCurFreq[CUR_FREQ_SHU_ZU_SIZE];
		E_RadioChannel eRadioChannel;
		u8 bIsHasRadioStationAndInfo;
		ST_RadioChannelRecord stszRadioChannelRecord[CHANNEL_NUM];
		u32 dwszCurChannelCurFreqRecFuncID[CHANNEL_NUM];
		u32 dwszCurChannelPreFreqRecFuncID[CHANNEL_NUM];
		u8 bIsNeedCmpWithRecFreq;
		u8 isAFOpen;
		u8 isTAOpen;
		//begin  
		 
		//end
		
	}radio_local_param_t;

*/
typedef struct{
	u8 bIsRadioPowerOn;
	E_RadioChannel eRadioChannel;
	ST_RadioChannelRecord stszRadioChannelRecord[CHANNEL_NUM];
	
}radio_global_param_t;

extern radio_local_param_t *pLocalParam;
extern radio_global_param_t *pGlobalParam;
extern CNotifyAndResponseFlyJniSdk  g_clsNotifyAndResponseFlyJniSdk ;


void readParameter(void);
void saveParameter(void);


typedef unsigned short		unicode16_t;
typedef int		uni16_size_t;
uni16_size_t uni16_strlen(const unicode16_t *uni16);
unicode16_t ansi_to_unicode16(const unsigned char ansi);
uni16_size_t ansi_str_to_unicode16(u8 *ansi, unicode16_t *uni16);
unicode16_t *uni16_strcpy(unicode16_t *dest, const unicode16_t *src);
unicode16_t *uni16_strcat(unicode16_t *dest, const unicode16_t *src);
uni16_size_t utf8_to_unicode16(const unsigned char *utf8, unicode16_t *uni16);


int utf8_2_ucs2(u8 *pInput, int nInputLen, u8 *pOutput, int nOutputSize);
int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);
int enc_get_utf8_size(const unsigned char pInput);



#endif
