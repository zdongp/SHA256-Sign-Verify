#pragma once
#include "fly_log.h"

enum emCtrlScan
{
	emCtrl_SCAN = 0x00, 
	emCtrl_SCAN_INC = 0x01, 
	emCtrl_SCAN_DEC = 0x02, 
	emCtrl_STOP = 0x03, 
	emCtrl_SCAN_REPEAT = 0x04, 
	emCtrl_SCAN_REPEAT_INC = 0x05, 
	emCtrl_SCAN_REPEAT_DEC = 0x06
};

enum emImitateKey
{
	emImitateKey_FM1 = 0x01, 
	emImitateKey_FM2 = 0x02, 
	emImitateKey_AM = 0x03, 
	emImitateKey_STOPRADIO = 0x04, 
	emImitateKey_AF = 0x05, 
	emImitateKey_TA = 0x06,
	emImitateKey_FreqInc = 0x07, 
	emImitateKey_FreqDec = 0x08
};

class CFatHal;
class CFatApp;
class CFatModule;
class CFatRadio
{
	typedef void (CFatRadio::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatRadio(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatRadio(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;
	u16 m_nCheckFreq;
	bool m_bCheckSearch;
public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);
	void AnalyseHalMsgFromRadio( u8 * p, u8 len, u8 cmd );
	void ResponseInfoCurFatState();
private:
	void JumpMediaByCommand( u8 ucFlag );
	u16 CalculateRadioFreq(short nStep);
	void EnterRadio(u8* pCmd, u8 ucLen);
	void SelectRadioFrequency(u8* pCmd, u8 ucLen);
	void EnterAndSelectRadioFrequency(u8* pCmd, u8 ucLen);
	void ExecuteSpecifyFreqSearch(u8* pCmd, u8 ucLen);
	void ExecuteScan(u8* pCmd, u8 ucLen);
};
