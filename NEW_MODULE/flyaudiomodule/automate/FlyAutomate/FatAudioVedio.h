#pragma once
#include "fly_log.h"

class CFatHal;
class CFatApp;
class CFatModule;
class CFatAudioVedio
{
	typedef void (CFatAudioVedio::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatAudioVedio(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatAudioVedio(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;

public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);

private:
	void SelectVolume(u8* pCmd, u8 ucLen);
	void SelectMuteOn(u8* pCmd, u8 ucLen);
	void SelectMuteOff(u8* pCmd, u8 ucLen);
	void ResponseValueVolume(u8* pCmd, u8 ucLen);
	void SelectLengthwaysBalance(u8* pCmd, u8 ucLen);
	void SelectCrosswiseBalance(u8* pCmd, u8 ucLen);
	void ResponseValueBalance(u8* pCmd, u8 ucLen);
	void SelectEqualizer(u8* pCmd, u8 ucLen);
	void ResponseValueEqualizer(u8* pCmd, u8 ucLen);
};
