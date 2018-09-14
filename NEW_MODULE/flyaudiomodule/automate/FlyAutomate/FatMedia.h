#pragma once
#include "fly_log.h"

class CFatHal;
class CFatApp;
class CFatModule;
class CFatMedia
{
	typedef void (CFatMedia::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatMedia(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatMedia(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;

public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);
	void ResponseInfoCurFatState();
private:
	void JumpMediaByCommand( u8 ucFlag );
	void EnterMusic(u8* pCmd, u8 ucLen);
	void SelectMusic(u8* pCmd, u8 ucLen);
	void EnterMusicAndSelectMusic(u8* pCmd, u8 ucLen);

	void EnterVedio(u8* pCmd, u8 ucLen);
	void SelectVedio(u8* pCmd, u8 ucLen);
	void EnterVedioAndSelectVedio(u8* pCmd, u8 ucLen);

	void G8IISelectMusic( u8* pCmd, u8 ucLen);
	void InquireTheMachineForTheSdcard(u8* pCmd, u8 ucLen);
	void ScanMusic( u8* pCmd, u8 ucLen );
	void DetectionUSB1( u8* pCmd, u8 ucLen );
};
