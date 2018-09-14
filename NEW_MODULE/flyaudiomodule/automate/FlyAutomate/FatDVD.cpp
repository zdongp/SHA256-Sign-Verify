#include "FatDVD.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"
CFatDVD::CFatDVD(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["5101"] = &CFatDVD::EnterTrackList;
	mapCmdFunc["5102"] = &CFatDVD::SelectTrack;
	mapCmdFunc["5103"] = &CFatDVD::EnterTrackListAndSelectSong;
	mapCmdFunc["5201"] = &CFatDVD::EnterFolder;
	mapCmdFunc["5202"] = &CFatDVD::SelectFolder;
	mapCmdFunc["5203"] = &CFatDVD::EnterFolderAndSelectFolder;
	mapCmdFunc["5204"] = &CFatDVD::EnterVedioShow;
	mapCmdFunc["5901"] = &CFatDVD::SelectPlayOrPause;
	mapCmdFunc["5902"] = &CFatDVD::SelectPlayOrPause;
	mapCmdFunc["5903"] = &CFatDVD::TakeOutDisc;

	m_ucTrackListOrFolder = 0x00;
}

CFatDVD::~CFatDVD(void)
{
}

void CFatDVD::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatDVD::ResponseInfoCurFatState()
{
	u8 ucParamLen = 0;
	u8 ucPlayStatus = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_DVD, CUR_PLAY_STATUS, &ucPlayStatus, &ucParamLen);
	u8 ucDiscType = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_DVD, CUR_DISC_TYPE, &ucDiscType, &ucParamLen);

	u8 ucCurIndex = 0;
	if ('1' == m_ucTrackListOrFolder)
		m_pFatModule->getOtherModuleParam(MODULE_ID_DVD, CUR_TRACK_NUM, &ucCurIndex, &ucParamLen);
	else if ('2' == m_ucTrackListOrFolder)
		m_pFatModule->getOtherModuleParam(MODULE_ID_DVD, CUR_CHAPTER_NUM, &ucCurIndex, &ucParamLen);
	
	u8 ucVolume = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_VOLUME, &ucVolume, &ucParamLen);

	u8 szQuery[] = {'5', '0', '0', '0', '0', '0', '0'};

	if (DISC_TYPE_NODISC == ucDiscType)
		szQuery[1] = '0';
	else if (DISC_TYPE_CD == ucDiscType)
		szQuery[1] = '1';
	else if (DISC_TYPE_DVD == ucDiscType)
		szQuery[1] = '2';
	else if (DISC_TYPE_VCD == ucDiscType)
		szQuery[1] = '3';
	else//DISC_TYPE_UNKNOW
		szQuery[1] = '4';

// 	sprintf((char*)(szQuery+2), "%d", ucPlayStatus);
// 	sprintf((char*)(szQuery+3), "%02X", ucCurIndex);
// 	sprintf((char*)(szQuery+5), "%02X", ucVolume);
	TransformIntegerToAcsii(szQuery+2, ucPlayStatus, 10, 1);
	TransformIntegerToAcsii(szQuery+3, ucCurIndex, 16, 2);
	TransformIntegerToAcsii(szQuery+5, ucVolume, 16, 2);
	m_pFatHal->SendResponseMsg(szQuery, sizeof(szQuery));
}

void CFatDVD::JumpMediaByCommand( u8 ucFlag )
{
	m_pFatHal->SetCurFatState(FAT_DVD);
	m_ucTrackListOrFolder = ucFlag;
	u16 nCurPage = m_pFatModule->getCurPageId();
	if ('1' == ucFlag && PAGE_DVD_TRACKLIST != nCurPage)
	{
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_DVD, CONTROLID_DVD_MAIN_TRACKLIST);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_DVD, CONTROLID_DVD_MAIN_TRACKLIST);
		//m_pFatModule->setPage(PAGE_DVD_TRACKLIST);
	}
	else if ('2' == ucFlag && PAGE_DVD_FOLDER != nCurPage)
	{
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_DVD, CONTROLID_DVD_MAIN_FOLDER_BUTTON);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_DVD, CONTROLID_DVD_MAIN_FOLDER_BUTTON);
		//m_pFatModule->setPage(PAGE_DVD_FOLDER);
	}
}

void CFatDVD::EnterTrackList( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[1]);
	m_pFatHal->Send_DriverACK();
}

void CFatDVD::SelectTrack( u8* pCmd, u8 ucLen )
{
	u8 ucTrack = TransformAcsiiToInteger(pCmd+4, 2) - 1;
	FLY_LOG(LOG_LV_DEBUG, "ucTrack = %d", ucTrack);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_DVD, CONTROLID_DVD_TRACKLIST_BEGIN+ucTrack);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_DVD, CONTROLID_DVD_TRACKLIST_BEGIN+ucTrack);
	m_pFatHal->Send_DriverACK();
}

void CFatDVD::EnterTrackListAndSelectSong( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[1]);
	SelectTrack(pCmd, ucLen);
}

void CFatDVD::EnterFolder( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[1]);
	m_pFatHal->Send_DriverACK();
}

void CFatDVD::SelectFolder( u8* pCmd, u8 ucLen )
{
	u8 ucFolder = TransformAcsiiToInteger(pCmd+4, 2) - 1;
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_DVD, CONTROLID_DVD_TRACKLIST_BEGIN+ucFolder);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_DVD, CONTROLID_DVD_TRACKLIST_BEGIN+ucFolder);
	m_pFatHal->Send_DriverACK();
}

void CFatDVD::EnterFolderAndSelectFolder( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[1]);
	SelectFolder(pCmd, ucLen);
}

void CFatDVD::EnterVedioShow( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_DVD, CONTROLID_DVD_MAIN_VIDEO);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_DVD, CONTROLID_DVD_MAIN_VIDEO);
	m_pFatHal->Send_DriverACK();
}

void CFatDVD::SelectPlayOrPause( u8* pCmd, u8 ucLen )
{
	u8 ucPlayStatus = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_DVD, CUR_PLAY_STATUS, &ucPlayStatus, &ucParamLen);
	if (('1' == pCmd[3] && PLAY_STATUS_PAUSE != ucPlayStatus) ||
		('2' == pCmd[3] && PLAY_STATUS_PLAY != ucPlayStatus))
	{
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_DVD, CONTROLID_DVD_MAIN_PLAYPAUSE);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_DVD, CONTROLID_DVD_MAIN_PLAYPAUSE);
	}
	m_pFatHal->Send_DriverACK();
}

void CFatDVD::TakeOutDisc( u8* pCmd, u8 ucLen )
{
	m_pFatModule->SendKeyValueToOtherModule(HALTOKEY_KEYVAL_OPEN, MODULE_ID_DVD);
	m_pFatHal->Send_DriverACK();
}
