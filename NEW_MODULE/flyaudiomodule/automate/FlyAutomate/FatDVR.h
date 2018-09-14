#pragma once
#include "fly_log.h"

class CFatHal;
class CFatApp;
class CFatModule;
class CFatDVR
{
	typedef void (CFatDVR::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatDVR(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatDVR(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;

public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);
	void ResponseInfoCurFatState();
private:
	void EnterDVR(u8* pCmd, u8 ucLen);
};
