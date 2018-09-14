/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "FatParam.h"
#include "fly_log.h"
#include "FatAudioVedio.h"
#include "FatAUX.h"
#include "FatBlueTooth.h"
#include "FatDVD.h"
#include "FatDVR.h"
#include "FatMedia.h"
#include "FatRadio.h"
#include "FatSystem.h"
#include "FatTPMS.h"
#include "FatiPod.h"
enum emResponseMsg
{
	RESPONSE_NORMAL = 0,
	RESPONSE_INFO,
	RESPONSE_VALUE,
	RESPONSE_RESULT
};

enum emFatStatus
{
	FAT_NULL = 0x00, 
	FAT_FM, 
	FAT_AM, 
	FAT_DVD, 
	FAT_MUSIC, 
	FAT_VAP,
	FAT_AUX,
	FAT_GPS, 
	FAT_BT, 
	FAT_DVR, 
	FAT_TPMS
};

#define EQ_CLASS		2		
#define EQ_POP			3
#define EQ_ROCK			4
#define EQ_JAZZ			5

class CFatModule;
class CFatApp;
class CFatSystem;
class CFatAudioVedio;
class CFatRadio;
class CFatDVD;
class CFatMedia;
class CFatAUX;
class CFatBlueTooth;
class CFatDVR;
class CFatTPMS;
class CFatiPod;
class CFatApp;
class CFatModule;
class CFatParam;
class CFatHal : public CFlyHal
{
	SINGLETON_IMPLEMENT(CFatHal)
private:
	CFatHal(void);
public:
	virtual ~CFatHal(void);

public:
	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);

	void analyseHalMessage(halid_t halId, u8 cmd, u8 *p, u8 len);
	void AnalyseHalMsgFromDVR( u8 * pCmd, u8 ucLen );


private:
	CFatApp *m_pFatApp;
	CFatModule *m_pFatModule;
	CFatHal *m_pFatHal;
	CFatParam *m_pFatParam;

	CFatSystem* m_pFatSystem;
	CFatAudioVedio* m_pFatAudioVedio;
	CFatRadio* m_pFatRadio;
	CFatDVD* m_pFatDVD;
	CFatMedia* m_pFatMedia;
	CFatAUX* m_pFatAUX;
	CFatBlueTooth* m_pFatBlueTooth;
	CFatDVR* m_pFatDVR;
	CFatTPMS* m_pFatTPMS;
	CFatiPod* m_pFatiPod;

public:
	void SetCurFatState(emFatStatus emCurState);
	emFatStatus GetCurFatState();

	bool JudgeAutomateState(u8* pCmd, u8 ucLen);
	void SendResponseMsg(u8* pMsg, u8 ucLen);
	void Send_DriverACK();
	void Send_CurFatStatus();

	void Set_LCDBrightness(u8 ucBright);
	void Set_StandbyState(u8 ucStandby);

	void Set_Volume(u8 ucVolume);
	void Set_Mute(bool bMute);
	void Set_FrontRearBalance(u8 ucBalance);
	void Set_LeftRightBalance(u8 ucBalance);
	void Set_Equalizer(u8 ucEqualizer);

	void Set_RadioSoftWareImitateKey(u8 ucKey);
	void Set_RadioScanCtrl(u8 ucCtrl);
	void Set_RadioFrequency(u16 nFreq);
	void Send_DriverACK_Data(u8 p);
private:
	emFatStatus m_emCurFatState;
};

