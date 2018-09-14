#pragma once
#include "fly_log.h"

class CFatHal;
class CFatApp;
class CFatModule;
class CFatBlueTooth
{
	typedef void (CFatBlueTooth::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatBlueTooth(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatBlueTooth(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;

public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);
	void ResponseInfoCurFatState();
private:
	void OpenOrCloseBlueTooth(u8* pCmd, u8 ucLen);
	void EnterBlueTooth(u8* pCmd, u8 ucLen);
	void EnterCSRBoxTest(u8* pCmd, u8 ucLen);
	void AnswerCall(u8* pCmd, u8 ucLen);
	void HangUp(u8* pCmd, u8 ucLen);
	void AnswerByCar(u8* pCmd, u8 ucLen);
	void AnswerByPhone(u8* pCmd, u8 ucLen);
	void DeleteAllSearchRecord(u8* pCmd, u8 ucLen);
	void ResponseStatusConnect(u8* pCmd, u8 ucLen);
	void ResponseBluetoothAddrs(u8* pCmd, u8 ucLen);
	void ResponseAutomateSideToPaired(u8* pCmd, u8 ucLen);
	void ResponseAutomateSideDonotToPaired(u8* pCmd, u8 ucLen);
	void ResponseBtIsPairBox(u8* pCmd, u8 ucLen);
};
