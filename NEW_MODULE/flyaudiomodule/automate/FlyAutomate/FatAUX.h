#pragma once
#include "fly_log.h"

class CFatHal;
class CFatApp;
class CFatModule;
class CFatAUX
{
	typedef void (CFatAUX::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatAUX(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatAUX(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;

public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);
	void ResponseInfoCurFatState();
private:
	void EnterAUX(u8* pCmd, u8 ucLen);
};
