#pragma once
#include "fly_log.h"

#define HALTOKEY_KEYVAL_OPEN			0x34

enum E_PLAY_STATUS
{
	PLAY_STATUS_STOP, 
	PLAY_STATUS_PRESTOP, 
	PLAY_STATUS_PLAY, 
	PLAY_STATUS_PAUSE, 
	PLAY_STATUS_SCANF, 
	PLAY_STATUS_SCANB,
	PLAY_STATUS_STILL, 
	PLAY_STATUS_SLOWF, 
	PLAY_STATUS_SLOWB,	
	PLAY_STATUS_UNKNOW
};

enum E_DISC_TYPE
{
	DISC_TYPE_DVD, 
	DISC_TYPE_VCD, 
	DISC_TYPE_CD, 
	DISC_TYPE_DATA, 
	DISC_TYPE_PCD, 
	DISC_TYPE_CDG, 
	DISC_TYPE_UNKNOW,
	DISC_TYPE_NODISC
};

class CFatHal;
class CFatApp;
class CFatModule;
class CFatDVD
{
	typedef void (CFatDVD::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatDVD(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatDVD(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;
	u8 m_ucTrackListOrFolder;
public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);
	void ResponseInfoCurFatState();
private:
	void JumpMediaByCommand( u8 ucFlag );
	//CD
	void EnterTrackList(u8* pCmd, u8 ucLen);
	void SelectTrack(u8* pCmd, u8 ucLen);
	void EnterTrackListAndSelectSong(u8* pCmd, u8 ucLen);
	//DVD
	void EnterFolder(u8* pCmd, u8 ucLen);
	void SelectFolder(u8* pCmd, u8 ucLen);
	void EnterFolderAndSelectFolder(u8* pCmd, u8 ucLen);
	void EnterVedioShow(u8* pCmd, u8 ucLen);

	void SelectPlayOrPause(u8* pCmd, u8 ucLen);
	void TakeOutDisc(u8* pCmd, u8 ucLen);
};
