#include "FatBlueTooth.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"
CFatBlueTooth::CFatBlueTooth(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["B100"] = &CFatBlueTooth::OpenOrCloseBlueTooth;
	mapCmdFunc["B101"] = &CFatBlueTooth::EnterBlueTooth;
	mapCmdFunc["B102"] = &CFatBlueTooth::EnterCSRBoxTest;
	mapCmdFunc["B104"] = &CFatBlueTooth::OpenOrCloseBlueTooth;
	mapCmdFunc["B105"] = &CFatBlueTooth::AnswerCall;
	mapCmdFunc["B106"] = &CFatBlueTooth::HangUp;
	mapCmdFunc["B107"] = &CFatBlueTooth::AnswerByCar;
	mapCmdFunc["B108"] = &CFatBlueTooth::AnswerByPhone;
	mapCmdFunc["B109"] = &CFatBlueTooth::DeleteAllSearchRecord;
	mapCmdFunc["B2AS"] = &CFatBlueTooth::ResponseStatusConnect;
	mapCmdFunc["B4AS"] = &CFatBlueTooth::ResponseBluetoothAddrs;

	mapCmdFunc["B500"] = &CFatBlueTooth::ResponseAutomateSideToPaired;
	mapCmdFunc["B501"] = &CFatBlueTooth::ResponseAutomateSideDonotToPaired;
	mapCmdFunc["B510"] = &CFatBlueTooth::ResponseBtIsPairBox;
}

CFatBlueTooth::~CFatBlueTooth(void)
{
}

void CFatBlueTooth::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatBlueTooth::ResponseInfoCurFatState()
{
	u8 ucPhoneStatus = 0x00;
	u8 ucPowerStatus = 0x00;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_BT, BT_MOBILE_STATUS, &ucPhoneStatus, &ucParamLen);
	m_pFatModule->getOtherModuleParam(MODULE_ID_BT, BT_POWER_STATUS, &ucPowerStatus, &ucParamLen);
	u8 szQuery[] = {'B', '0', '0', '1', '1', '1', '1'};
	if (0x01 == ucPowerStatus)
		szQuery[4] = '1';
	if (PHONE_STATUS_UNINIT != ucPhoneStatus &&
		PHONE_STATUS_FREE != ucPhoneStatus &&
		PHONE_STATUS_UNKNOW != ucPhoneStatus)
		szQuery[5] = '1';
	m_pFatHal->SendResponseMsg(szQuery, sizeof(szQuery));
}

void CFatBlueTooth::OpenOrCloseBlueTooth( u8* pCmd, u8 ucLen )
{
	u8 ucPowerStatus = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_BT, BT_POWER_STATUS, &ucPowerStatus, &ucParamLen);
	u8 ucOpenOrClose = pCmd[3];
	FLY_LOG(LOG_LV_DEBUG, "ucOpenOrClose = %c ucPowerStatus = %d", ucOpenOrClose, ucPowerStatus);
	if (('0' == ucOpenOrClose && 1 == ucPowerStatus) ||
		('4' == ucOpenOrClose && 0 == ucPowerStatus))
	{
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NO_BLUETOOTH);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NO_BLUETOOTH);
	}

	if('0' == ucOpenOrClose && 1 == ucPowerStatus)
	{
		m_pFatModule->NotifyBlueToothSendBtPower(0);
	}
	else if('4' == ucOpenOrClose && 0 == ucPowerStatus)
	{
		m_pFatModule->NotifyBlueToothSendBtPower(1);
	}
	
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::EnterBlueTooth( u8* pCmd, u8 ucLen )
{
	m_pFatHal->SetCurFatState(FAT_BT);
	m_pFatModule->NotifySystemJumpPage(PAGE_BLUETOOTH_MAIN);
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::EnterCSRBoxTest( u8* pCmd, u8 ucLen )
{
	m_pFatModule->NotifyBlueToothDiscoverable(0x01);
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::AnswerCall( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_DIAL);

	m_pFatModule->NotifyBlueToothSendBt_CallingOrHandupr(1);
	
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::HangUp( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_HANG_UP);

	m_pFatModule->NotifyBlueToothSendBt_CallingOrHandupr(0);
	
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::AnswerByCar( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_CAR_ANSWER);

	m_pFatModule->NotifyBlueToothSendBt_AudioTransfer(0);
	
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::AnswerByPhone( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_MAIN_NEW_PHONE_ANSWER);

	m_pFatModule->NotifyBlueToothSendBt_AudioTransfer(1);
	
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::DeleteAllSearchRecord( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_ALL);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_DELETE_ALL);

	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_OK);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_BT, CONTROLID_BLUETOOTH_AUDIOVOX_SEACH_FRAME_BG_OK);

	m_pFatModule->NotifyBlueToothSendBt_CallLogsAllClear(1);
	
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::ResponseStatusConnect( u8* pCmd, u8 ucLen )
{
	u8 ucConnectStatus = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_BT, BT_HF_CONNECT_STATUS, &ucConnectStatus, &ucParamLen);
	u8 szConnect[] = {'A', 'C', 'K', '0'};
	if (0x01 == ucConnectStatus)
		szConnect[3] = '1';
	m_pFatHal->SendResponseMsg(szConnect, 4);
}

void CFatBlueTooth::ResponseBluetoothAddrs(u8* pCmd, u8 ucLen)
{
	u8 szBtMac[CMD_TO_INFORS_MAX_LEN];
	memset(szBtMac,0,sizeof(szBtMac));
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_BT, BT_ADDR, szBtMac, &ucParamLen);
	int nInfoLen = strlen((char*)szBtMac);
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		//strncat((char*)pMsg, (char*)szBtMac, nInfoLen);
		memcpy(pMsg+1, szBtMac, nInfoLen);
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;

}

 
void CFatBlueTooth::ResponseAutomateSideToPaired(u8* pCmd, u8 ucLen)
{
	m_pFatModule->NotifyBlueToothDiscoverablePairing(0x01);
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::ResponseAutomateSideDonotToPaired(u8* pCmd, u8 ucLen)
{
	m_pFatModule->NotifyBlueToothDiscoverablePairing(0x00);
	m_pFatHal->Send_DriverACK();
}

void CFatBlueTooth::ResponseBtIsPairBox(u8* pCmd, u8 ucLen)
{
	u8 uPairStatus = 0;
	u8 uPairStatusLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_BT, BT_IS_PAIR_BOX, &uPairStatus, &uPairStatusLen);
	u8 szConnect[] = {'A', 'C', 'K', '0'};
	if (0x01 == uPairStatus)
		szConnect[3] = '1';
	m_pFatHal->SendResponseMsg(szConnect, 4);

}