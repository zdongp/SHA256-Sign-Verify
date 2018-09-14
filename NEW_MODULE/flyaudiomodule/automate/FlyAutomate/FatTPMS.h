#pragma once
#include "fly_log.h"

class CFatHal;
class CFatApp;
class CFatModule;
class CFatTPMS
{
	typedef void (CFatTPMS::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatTPMS(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatTPMS(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;

public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);

private:
	void EnterTPMS(u8* pCmd, u8 ucLen);
	void ExecutePair(u8* pCmd, u8 ucLen);
	void ResponseValuePairStatus(u8* pCmd, u8 ucLen);
};
