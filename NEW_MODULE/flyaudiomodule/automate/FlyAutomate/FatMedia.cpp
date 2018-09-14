#include "FatMedia.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"
CFatMedia::CFatMedia(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["6101"] = &CFatMedia::EnterMusic;
	mapCmdFunc["6102"] = &CFatMedia::SelectMusic;
	mapCmdFunc["6103"] = &CFatMedia::EnterMusicAndSelectMusic;
	mapCmdFunc["64AS"] = &CFatMedia::InquireTheMachineForTheSdcard;
	mapCmdFunc["I101"] = &CFatMedia::EnterVedio;
	mapCmdFunc["I102"] = &CFatMedia::SelectVedio;
	mapCmdFunc["I103"] = &CFatMedia::EnterVedioAndSelectVedio;
	mapCmdFunc["7603"] = &CFatMedia::G8IISelectMusic;
	mapCmdFunc["7101"] = &CFatMedia::EnterMusic;
	mapCmdFunc["7103"] = &CFatMedia::EnterMusicAndSelectMusic;
	mapCmdFunc["7104"] = &CFatMedia::ScanMusic;
	mapCmdFunc["71AS"] = &CFatMedia::DetectionUSB1;
}

CFatMedia::~CFatMedia(void)
{
}

void CFatMedia::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatMedia::ResponseInfoCurFatState()
{
	u8 szQuery[] = {'6', '1', '1', '0', '0', '0', '0'};
	u8 ucPlayStatus = 0;
	u8 ucCurTrack = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_MEDIA, MEDIA_PLAY_STATUS, &ucPlayStatus, &ucParamLen);
	m_pFatModule->getOtherModuleParam(MODULE_ID_MEDIA, MEDIA_CUR_TRACK, &ucCurTrack, &ucParamLen);
	u8 ucVolume = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_VOLUME, &ucVolume, &ucParamLen);
	if(FAT_VAP == m_pFatHal->GetCurFatState())
		szQuery[1] = '2';
	FLY_LOG(LOG_LV_DEBUG, "ucPlayStatus = %d ucCurTrack = %d", ucPlayStatus, ucCurTrack);
	// 	sprintf((char*)(szQuery+3), "%02X", nFreq);
	// 	sprintf((char*)(szQuery+5), "%02X", ucVolume);
	TransformIntegerToAcsii(szQuery+2, ucPlayStatus, 16, 1);
	TransformIntegerToAcsii(szQuery+3, ucCurTrack, 16, 2);
	TransformIntegerToAcsii(szQuery+5, ucVolume, 16, 2);
	m_pFatHal->SendResponseMsg(szQuery, sizeof(szQuery));
}

void CFatMedia::JumpMediaByCommand( u8 ucFlag )
{
	u8 szCmd[] = {0xFA, 0x01, 0x00};
	if ('6' == ucFlag || '7' == ucFlag)
	{
		m_pFatHal->SetCurFatState(FAT_MUSIC);
		szCmd[2] = 0x00;
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_MEDIA, CONTROLID_MENU_MEDIA);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_MEDIA, CONTROLID_MENU_MEDIA);
	}
	else if ('I' == ucFlag)
	{
		m_pFatHal->SetCurFatState(FAT_VAP);
		szCmd[2] = 0x01;
	}
	FLY_LOG(LOG_LV_DEBUG, "ucFlag = %c", ucFlag);
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
}

void CFatMedia::EnterMusic( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[0]);
	m_pFatModule->NotifyMP3_UsbStateInit();
	m_pFatHal->Send_DriverACK();
}

void CFatMedia::SelectMusic( u8* pCmd, u8 ucLen )
{
	int nIndex = TransformAcsiiToInteger(pCmd+4, 2);
	FLY_LOG(LOG_LV_DEBUG, "nIndex = %d", nIndex);
	//u8 szCmd[] = {0xFA, 0x02, 0x00, 0x00};
	//memcpy(szCmd+2, &nIndex, 2);
	//m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
	m_pFatModule->NotifyMP3_SelectMusicPlay((u8)nIndex);
	m_pFatHal->Send_DriverACK();
}

void CFatMedia::G8IISelectMusic( u8* pCmd, u8 ucLen)
{
	JumpMediaByCommand(pCmd[0]);
	int nIndex = TransformAcsiiToInteger(pCmd+4, 2);
	FLY_LOG(LOG_LV_DEBUG, "G8IISelectMusic:nIndex = %d", nIndex);
	m_pFatModule->NotifyMP3_SelectMusicPlay((u8)nIndex);
	m_pFatHal->Send_DriverACK();
}

void CFatMedia::EnterMusicAndSelectMusic( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[0]);
	SelectMusic(pCmd, ucLen);
}

void CFatMedia::EnterVedio( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[0]);
	m_pFatHal->Send_DriverACK();
}

void CFatMedia::SelectVedio( u8* pCmd, u8 ucLen )
{
	int nIndex = TransformAcsiiToInteger(pCmd+4, 2);
	FLY_LOG(LOG_LV_DEBUG, "nIndex = %d", nIndex);
	u8 szCmd[] = {0xFA, 0x03, 0x00, 0x00};
	memcpy(szCmd+2, &nIndex, 2);
	m_pFatApp->setCommand(0x00, szCmd, sizeof(szCmd));
	m_pFatHal->Send_DriverACK();
}

void CFatMedia::EnterVedioAndSelectVedio( u8* pCmd, u8 ucLen )
{
	JumpMediaByCommand(pCmd[0]);
	SelectVedio(pCmd, ucLen);
}

void CFatMedia::InquireTheMachineForTheSdcard(u8* pCmd, u8 ucLen)
{
	u8 ucIsSdcardStaus = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, SDCARD1_STATUS, &ucIsSdcardStaus, &ucParamLen);

	m_pFatHal->Send_DriverACK_Data(ucIsSdcardStaus);
}
void CFatMedia::ScanMusic( u8* pCmd, u8 ucLen )
{
	m_pFatModule->NotifyMP3_GoToAutoMate();
	m_pFatHal->Send_DriverACK();
}

void CFatMedia::DetectionUSB1( u8* pCmd, u8 ucLen )
{
	u8 ucIsSdcardStaus = 0;
	u8 ucParamLen = 0;
	m_pFatModule->NotifyMP3_DetectionUSB();
	m_pFatModule->getOtherModuleParam(MODULE_ID_MEDIA,MEDIA_USB1_STATUS,&ucIsSdcardStaus,&ucParamLen);
	m_pFatHal->Send_DriverACK_Data(ucIsSdcardStaus);
}