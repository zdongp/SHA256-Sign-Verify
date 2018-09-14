#include "FatDVR.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"
CFatDVR::CFatDVR(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["E101"] = &CFatDVR::EnterDVR;
}

CFatDVR::~CFatDVR(void)
{
}

void CFatDVR::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatDVR::ResponseInfoCurFatState()
{
	u8 szQuery[] = {'E', '1', '1', '1', '1', '1', '1'};
	m_pFatHal->SendResponseMsg(szQuery, sizeof(szQuery));
}

void CFatDVR::EnterDVR( u8* pCmd, u8 ucLen )
{
	m_pFatHal->SetCurFatState(FAT_DVR);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_DVR, CONTROLID_MENU_DRIVING_RECORD);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_DVR, CONTROLID_MENU_DRIVING_RECORD);
	//m_pFatModule->NotifySystemJumpPage(PAGE_DRIVING_RECORD_NO_SIGN);
	m_pFatHal->Send_DriverACK();
}
