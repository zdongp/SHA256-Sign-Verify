#include "FatAUX.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"

CFatAUX::CFatAUX(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["9101"] = &CFatAUX::EnterAUX;
}

CFatAUX::~CFatAUX(void)
{
}

void CFatAUX::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatAUX::ResponseInfoCurFatState()
{
	u8 szQuery[] = {'9', '1', '1', '1', '1', '0', '0'};
	u8 ucVolume = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, CUR_VOLUME, &ucVolume, &ucParamLen);
	//sprintf((char*)(szQuery+5), "%02X", ucVolume);
	TransformIntegerToAcsii(szQuery+5, ucVolume, 16, 2);
	m_pFatHal->SendResponseMsg(szQuery, sizeof(szQuery));
}

void CFatAUX::EnterAUX( u8* pCmd, u8 ucLen )
{
	m_pFatHal->SetCurFatState(FAT_AUX);
	//m_pFatModule->NotifySystemJumpPage(PAGE_AUX);
	#ifdef MTK_3561_64
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_AUX, CONTROLID_MENU_AUX);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_AUX, CONTROLID_MENU_AUX);
	#else
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_AUX, CONTROLID_AUX_SET_VIDEO_SWITCH);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_AUX, CONTROLID_AUX_SET_VIDEO_SWITCH);
	#endif
	m_pFatHal->Send_DriverACK();
}
