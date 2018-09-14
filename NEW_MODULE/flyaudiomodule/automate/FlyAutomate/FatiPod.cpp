#include "FatiPod.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"
#include "CP.h"
CFatiPod::CFatiPod(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["83AS"] = &CFatiPod::ResponseInfoWorkStatus;
}

CFatiPod::~CFatiPod(void)
{
}

void CFatiPod::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatiPod::ResponseInfoCurFatState()
{
	u8 szQuery[] = {'8', '1', '1', '0', '0', '0', '0'};
	u8 ucPlayStatus = 0;
	u8 ucCurTrack = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_MEDIA, MEDIA_PLAY_STATUS, (u8*)&ucPlayStatus, &ucParamLen);
	m_pFatModule->getOtherModuleParam(MODULE_ID_MEDIA, MEDIA_CUR_TRACK, (u8*)&ucCurTrack, &ucParamLen);
	u8 ucVolume = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_VOLUME, &ucVolume, &ucParamLen);
	if(FAT_VAP == m_pFatHal->GetCurFatState())
		szQuery[1] = '2';
	// 	sprintf((char*)(szQuery+3), "%02X", nFreq);
	// 	sprintf((char*)(szQuery+5), "%02X", ucVolume);
	TransformIntegerToAcsii(szQuery+2, ucPlayStatus, 16, 1);
	TransformIntegerToAcsii(szQuery+3, ucCurTrack+1, 16, 2);
	TransformIntegerToAcsii(szQuery+5, ucVolume, 16, 2);
	m_pFatHal->SendResponseMsg(szQuery, sizeof(szQuery));
}

void CFatiPod::EnterDVR( u8* pCmd, u8 ucLen )
{
	m_pFatHal->SetCurFatState(FAT_DVR);
	m_pFatModule->NotifySystemJumpPage(PAGE_DRIVING_RECORD_MENU);
	m_pFatHal->Send_DriverACK();
}

void CFatiPod::ResponseInfoWorkStatus( u8* pCmd, u8 ucLen )
{
	u8 szMsg[] = {'8', 'S', '0'};
	CCP iccp;
	FLY_LOG(LOG_LV_DEBUG, "iccp.GetDeviceVersion() = 0x%x", iccp.GetDeviceVersion());
	FLY_LOG(LOG_LV_DEBUG, "iccp.GetFWVersion() = 0x%x", iccp.GetFWVersion());
	FLY_LOG(LOG_LV_DEBUG, "iccp.GetAuthProtocolMajor() = 0x%x", iccp.GetAuthProtocolMajor());
	FLY_LOG(LOG_LV_DEBUG, "iccp.GetAuthProtocolMinor() = 0x%x", iccp.GetAuthProtocolMinor());
	if (0x05 == iccp.GetDeviceVersion() &&
		0x01 == iccp.GetFWVersion() &&
		0x02 == iccp.GetAuthProtocolMajor() &&
		0x00 == iccp.GetAuthProtocolMinor())
	{
		szMsg[2] = '1';
	}
	m_pFatHal->SendResponseMsg(szMsg, sizeof(szMsg));
}
