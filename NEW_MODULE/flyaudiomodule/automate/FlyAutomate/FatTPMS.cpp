#include "FatTPMS.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"
CFatTPMS::CFatTPMS(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["H101"] = &CFatTPMS::EnterTPMS;
	mapCmdFunc["H102"] = &CFatTPMS::ExecutePair;
	mapCmdFunc["H103"] = &CFatTPMS::ResponseValuePairStatus;
}

CFatTPMS::~CFatTPMS(void)
{
}

void CFatTPMS::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatTPMS::EnterTPMS( u8* pCmd, u8 ucLen )
{
	m_pFatHal->SetCurFatState(FAT_TPMS);
	m_pFatModule->NotifySystemJumpPage(PAGE_TPMS);
	m_pFatHal->Send_DriverACK();
}

void CFatTPMS::ExecutePair( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_TPMS, CONTROLID_TPMS_PAIR);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_TPMS, CONTROLID_TPMS_PAIR);
	m_pFatHal->Send_DriverACK();
}

void CFatTPMS::ResponseValuePairStatus( u8* pCmd, u8 ucLen )
{
	u8 ucParamLen = 0;
	u8 ucPair = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_TPMS, PAIR_STATUS, &ucPair, &ucParamLen);
	u8 szPair[] = {'4', 'S', '0'};
	if (0x01 == ucPair)
		szPair[2] = '1';
	m_pFatHal->SendResponseMsg(szPair, 3);
}
