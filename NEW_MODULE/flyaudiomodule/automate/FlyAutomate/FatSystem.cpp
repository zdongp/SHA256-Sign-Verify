#include "FatSystem.h"
#include "FatApp.h"
#include "FatModule.h"
#include "FatHal.h"
#include "FatParam.h"

extern "C"{
#include "unicodestring.h"
};

CFatSystem::CFatSystem(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule)
{
	m_pFatHal = pFatHal;
	m_pFatApp = pFatApp;
	m_pFatModule = pFatModule;

	mapCmdFunc["0101"] = &CFatSystem::ResponseFactoryPattern_Status;
	mapCmdFunc["0102"] = &CFatSystem::ResponseFactoryPattern_Status;
	mapCmdFunc["01AS"] = &CFatSystem::ResponseHaveEnterAutomate;
	mapCmdFunc["0201"] = &CFatSystem::EnterOrQuitStandby;
	mapCmdFunc["0202"] = &CFatSystem::EnterOrQuitStandby;
	mapCmdFunc["0301"] = &CFatSystem::RestoreDefaults;
	mapCmdFunc["0302"] = &CFatSystem::ReStartSystem;
	mapCmdFunc["1100"] = &CFatSystem::ResponseInforBrakeStatusClose;
	mapCmdFunc["1101"] = &CFatSystem::ResponseInforBrakeStatusOpen;
	mapCmdFunc["12AS"] = &CFatSystem::ResponseInfoMCU;
	mapCmdFunc["14AS"] = &CFatSystem::ResponseInfoBarCode;
	mapCmdFunc["15AS"] = &CFatSystem::ResponseInfoBluetoothVersion;
	mapCmdFunc["16AS"] = &CFatSystem::ResponseInfoMEPG;
	mapCmdFunc["1EAS"] = &CFatSystem::ResponseInfoFID;
	mapCmdFunc["18AS"] = &CFatSystem::ResponseGetBrakeCarStatus;
	mapCmdFunc["19AS"] = &CFatSystem::ResponseValueBattery;
	mapCmdFunc["1A01"] = &CFatSystem::SelectPrevSteeringWheel;
	mapCmdFunc["1A02"] = &CFatSystem::SelectNextSteeringWheel;
	mapCmdFunc["1F00"] = &CFatSystem::SelectAUXInputSource;
	mapCmdFunc["1F01"] = &CFatSystem::SelectAUXInputSource;
	mapCmdFunc["1G00"] = &CFatSystem::EnableBackCarVedio;
	mapCmdFunc["1G01"] = &CFatSystem::EnableBackCarVedio;
	mapCmdFunc["3101"] = &CFatSystem::SelectLuminance;
	mapCmdFunc["31AS"] = &CFatSystem::ResponseValueLuminance;
	mapCmdFunc["1BAS"] = &CFatSystem::ResponseAudioValueMax;
	mapCmdFunc["1CAS"] = &CFatSystem::ResponseInfoIMEI;
	mapCmdFunc["1DAS"] = &CFatSystem::ResponseInfoSdMemoryUsage;
	mapCmdFunc["1FAS"] = &CFatSystem::ResponseInfoSdTheTotalSize;
	mapCmdFunc["1H00"] = &CFatSystem::EnterCloseWifi;
	mapCmdFunc["1H01"] = &CFatSystem::EnterOpenWifi;
	mapCmdFunc["1I00"] = &CFatSystem::EnterClose4G;
	mapCmdFunc["1I01"] = &CFatSystem::EnterOpen4G;
	mapCmdFunc["J100"] = &CFatSystem::ConnectWIFI;
	mapCmdFunc["J101"] = &CFatSystem::IntoTheBaiduPage_WIFI;
	mapCmdFunc["J102"] = &CFatSystem::WithdrawTheBaiduPage_WIFI;
	mapCmdFunc["J1AS"] = &CFatSystem::InquireWifiConntectStatus;
	mapCmdFunc["J2AS"] = &CFatSystem::InquireWifiNetworkSignalStrength;
	mapCmdFunc["J3AS"] = &CFatSystem::ResponseInfoMAC;
	mapCmdFunc["J4AS"] = &CFatSystem::ResponseWiFiWhetherAccessToTheInternet;
	mapCmdFunc["K1AS"] = &CFatSystem::Inquire4GNetworkSignalStrength;
	mapCmdFunc["K200"] = &CFatSystem::IntoTheBaiduPage_4G;
	mapCmdFunc["K202"] = &CFatSystem::WithdrawTheBaiduPage_4G;
	mapCmdFunc["K2AS"] = &CFatSystem::Response4GWhetherAccessToTheInternet;
}

CFatSystem::~CFatSystem(void)
{
}

void CFatSystem::AnalyseFATCommand( u8* pCmd, u8 ucLen )
{
	string strCmd;
	strCmd.assign((char*)pCmd, 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	static map<string, pFunc>::iterator it;
	it = mapCmdFunc.find(strCmd);
	if(it != mapCmdFunc.end())
		(this->*it->second)(pCmd, ucLen);
}

void CFatSystem::ResponseFactoryPattern_Status(u8* pCmd, u8 ucLen)
{
	static u8 ucEnterOrQuit = 0;
	if ('1' == pCmd[3])
	{
	    if(ucEnterOrQuit == 1)return;
	    
	    ucEnterOrQuit = 1;
		m_pFatModule->NotifyBlueToothIntoAutomateMode_PairingPincodeToDefault();
	}
	else if ('2' == pCmd[3])
	{
	    ucEnterOrQuit = 0;
	}
}

void CFatSystem::ResponseHaveEnterAutomate( u8* pCmd, u8 ucLen )
{
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::EnterOrQuitStandby( u8* pCmd, u8 ucLen )
{
// 	u8 ucParamLen = 0;
// 	u8 ucStandby = 0;
// 	m_pFatModule->getOtherModuleParam(MODULE_ID_SYSTEM, SLEEP_STATE, &ucStandby, &ucParamLen);
// 	FLY_LOG(LOG_LV_DEBUG, "CFatSystem::EnterOrQuitStandby------>ucEnterOrQuit = %c ucStandby = %d", ucEnterOrQuit, ucStandby);
	u8 ucEnterOrQuit = pCmd[3];
	if ('1' == ucEnterOrQuit)
		m_pFatHal->Set_StandbyState(0x01);
	else if ('2' == ucEnterOrQuit)
		m_pFatHal->Set_StandbyState(0x00);
	
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::RestoreDefaults( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_TIMER, MODULE_ID_SYSTEM, CONTROLID_SETUP_SYSTEM_RESET);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::ReStartSystem( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_SYSTEM, CONTROLID_SETUP_RESTART_DIALOG_OK);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_SYSTEM, CONTROLID_SETUP_RESTART_DIALOG_OK);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::ResponseInforBrakeStatusClose(u8* pCmd, u8 ucLen)
{
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::ResponseInforBrakeStatusOpen(u8* pCmd, u8 ucLen)
{
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::ResponseInfoMCU( u8* pCmd, u8 ucLen )
{
	u8 szMCU[CMD_TO_INFORS_MAX_LEN];
	memset(szMCU,0,sizeof(szMCU));
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SYSTEM, MCU_INFO, szMCU, &ucParamLen);
	int nInfoLen = strlen((char*)szMCU);
	if(nInfoLen > 1){
		if(szMCU[nInfoLen-1] == 0x0A){
			nInfoLen = nInfoLen -1;
		}
	}
	
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		memcpy(pMsg+1, szMCU, nInfoLen);
	}

	//for(int i = 0;i < (nInfoLen+1);i++)
	//{
	//	FLY_LOG(LOG_LV_DEBUG, "pMsg = %x", pMsg[i]);
	//}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;
}

void CFatSystem::ResponseInfoBarCode( u8* pCmd, u8 ucLen )
{
	u8 szBarCode[CMD_TO_INFORS_MAX_LEN];
	memset(szBarCode,0,sizeof(szBarCode));
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, BARCODE_INFO, szBarCode, &ucParamLen);
	int nInfoLen = strlen((char*)szBarCode);
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		memcpy(pMsg+1, szBarCode, nInfoLen);
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;
}

void CFatSystem::ResponseInfoBluetoothVersion(u8* pCmd, u8 ucLen)
{
	u8 szBtVersion[CMD_TO_INFORS_MAX_LEN];
	memset(szBtVersion,0,sizeof(szBtVersion));
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_BT, BT_VERSION_INFO, szBtVersion, &ucParamLen);
	int nInfoLen = strlen((char*)szBtVersion);
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		//strncat((char*)pMsg, (char*)szBtVersion, nInfoLen);
		memcpy(pMsg+1, szBtVersion, nInfoLen);
		m_pFatModule->NotifyBlueToothIntoAutomateMode_PairingPincodeToDefault();
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;
}

void CFatSystem::ResponseInfoMEPG( u8* pCmd, u8 ucLen )
{
	u8 szMEPG[CMD_TO_INFORS_MAX_LEN];
	memset(szMEPG,0,sizeof(szMEPG));
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SYSTEM, MEPG_INFO, szMEPG, &ucParamLen);
	int nInfoLen = strlen((char*)szMEPG);

	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(ucParamLen > 0){
		//strncat((char*)pMsg, (char*)szMEPG, nInfoLen);
		memcpy(pMsg+1, szMEPG, nInfoLen);
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;
}

void CFatSystem::ResponseInfoFID( u8* pCmd, u8 ucLen )
{
	u8 szFID[CMD_TO_INFORS_MAX_LEN];
	memset(szFID,0,sizeof(szFID));
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SYSTEM, FID_INFO, szFID, &ucParamLen);
	int nInfoLen = strlen((char*)szFID);
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		//strncat((char*)pMsg, (char*)szFID, nInfoLen);
		memcpy(pMsg+1, szFID, nInfoLen);
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;
}

void CFatSystem::ResponseInfoIMEI( u8* pCmd, u8 ucLen )
{
	u8 szImei[CMD_TO_INFORS_MAX_LEN];
	memset(szImei,0,sizeof(szImei));
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, IMEI_INFO, szImei, &ucParamLen);
	int nInfoLen = strlen((char*)szImei);
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		//strncat((char*)pMsg, (char*)szImei, nInfoLen);
		memcpy(pMsg+1, szImei, nInfoLen);
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;

}

void CFatSystem::ResponseGetBrakeCarStatus(u8* pCmd, u8 ucLen)
{
	u8 ucBrakeCarStaus = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SYSTEM, SYSTEM_BRAKECAR_STATUS, &ucBrakeCarStaus, &ucParamLen);

	m_pFatHal->Send_DriverACK_Data(ucBrakeCarStaus);
}

void CFatSystem::ResponseValueBattery( u8* pCmd, u8 ucLen )
{
	u8 ucBattery = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SYSTEM, BATTERY_VALUE, &ucBattery, &ucParamLen);
	u8 szBattery[] = {'I', 0x00, 0x00};
	TransformIntegerToAcsii(szBattery+1, ucBattery, 10, 2);
	FLY_LOG(LOG_LV_DEBUG, "ucBattery = %s", ucBattery);
	m_pFatHal->SendResponseMsg(szBattery,3);
}

void CFatSystem::ResponseAudioValueMax( u8* pCmd, u8 ucLen )
{
	u8 ucMaxVol = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_AUDIOVIDEO, MAX_VOLUME, &ucMaxVol, &ucParamLen);
	FLY_LOG(LOG_LV_DEBUG, "ucMaxVol = %d", ucMaxVol);
	u8 szMsg[] = {'I', 0x00, 0x00};
	TransformIntegerToAcsii(szMsg+1, ucMaxVol, 10, 2);
	FLY_LOG(LOG_LV_DEBUG, "szMsg = %s", szMsg);
	m_pFatHal->SendResponseMsg(szMsg, 3);
}

void CFatSystem::SelectPrevSteeringWheel( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_SYSTEM, CONTROLID_SETUP_WHEEL_CHOOSE_UP);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_SYSTEM, CONTROLID_SETUP_WHEEL_CHOOSE_UP);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::SelectNextSteeringWheel( u8* pCmd, u8 ucLen )
{
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_SYSTEM, CONTROLID_SETUP_WHEEL_CHOOSE_DOWM);
	m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_SYSTEM, CONTROLID_SETUP_WHEEL_CHOOSE_DOWM);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::SelectAUXInputSource( u8* pCmd, u8 ucLen )
{
	u8 ucCurInput = 0;
	u8 ucParamLen = 0;
	//m_pFatModule->getOtherModuleParam(MODULE_ID_SYSTEM, AUX_INPUT_SOURCE, &ucCurInput, &ucParamLen);
	u8 ucSelect = pCmd[3];
	FLY_LOG(LOG_LV_DEBUG, "ucSelect = %c ucCurInput = %d", ucSelect, ucCurInput);
	if ('0' == ucSelect && 0x00 != ucCurInput)
	{
		//m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_SYSTEM, CONTROLID_SETUP_AUX_CHOOSE_UP);
		//m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_SYSTEM, CONTROLID_SETUP_AUX_CHOOSE_UP);
	}
	else if ('1' == ucSelect && 0x01 != ucCurInput)
	{
		//m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_SYSTEM, CONTROLID_SETUP_AUX_CHOOSE_UP);
		//m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_SYSTEM, CONTROLID_SETUP_AUX_CHOOSE_UP);
	}
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::EnableBackCarVedio( u8* pCmd, u8 ucLen )
{
	u8 ucEnable = pCmd[3];
	if ('0' == ucEnable)
	{
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_SYSTEM, CONTROLID_SETUP_BACK_VIDEO_ON, SYS_SETUP_OFF);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_SYSTEM, CONTROLID_SETUP_BACK_VIDEO_ON, SYS_SETUP_OFF);
	}
	else if ('1' == ucEnable)
	{
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_DOWN, MODULE_ID_SYSTEM, CONTROLID_SETUP_BACK_VIDEO_ON, SYS_SETUP_ON);
		m_pFatApp->SendMouseOperateToOtherModule(MOUSE_STATUS_UP, MODULE_ID_SYSTEM, CONTROLID_SETUP_BACK_VIDEO_ON, SYS_SETUP_ON);
	}
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::SelectLuminance( u8* pCmd, u8 ucLen )
{
	m_pFatHal->Set_LCDBrightness(TransformAcsiiToInteger(pCmd+4, 2));
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::ResponseValueLuminance( u8* pCmd, u8 ucLen )
{
	u8 ucLuminance = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SYSTEM, LCD_STATE, &ucLuminance, &ucParamLen);
	u8 szLuminance[] = {'I', 0x00, 0x00};
	TransformIntegerToAcsii(szLuminance+1, ucLuminance, 10, 2);
	FLY_LOG(LOG_LV_DEBUG, "szLuminance = %s", szLuminance);
	m_pFatHal->SendResponseMsg(szLuminance,3);
}

void CFatSystem::EnterCloseWifi(u8* pCmd, u8 ucLen)
{
	m_pFatApp->controlWIFI(0x00);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::EnterOpenWifi(u8* pCmd, u8 ucLen)
{
	m_pFatApp->controlWIFI(0x01);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::EnterClose4G(u8* pCmd, u8 ucLen)
{
	m_pFatApp->control4G(0x00);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::EnterOpen4G(u8* pCmd, u8 ucLen)
{
	m_pFatApp->control4G(0x01);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::ConnectWIFI(u8* pCmd, u8 ucLen)
{
	string strCmd;
	strCmd.assign((char*)(&pCmd[4]), ucLen - 4);
	FLY_LOG(LOG_LV_DEBUG, "strCmd = %s", strCmd.c_str());
	u8 len = ucLen - 4 + 2;
	u8* pMsg = new u8[len];
	memset(pMsg, 0, len);
	pMsg[0] = 0x86;
	pMsg[1] = 0x01;
	memcpy(&pMsg[2],&pCmd[4],ucLen - 4);
	m_pFatApp->setCommand(0x00, pMsg, len);
	m_pFatHal->Send_DriverACK();

	delete[] pMsg;
	pMsg = NULL;
}

void CFatSystem::ResponseInfoMAC(u8* pCmd, u8 ucLen)
{
	u8 szMac[CMD_TO_INFORS_MAX_LEN];
	memset(szMac,0,sizeof(szMac));
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, WLAN_MAC_INFO, szMac, &ucParamLen);
	int nInfoLen = strlen((char*)szMac);
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		memcpy(pMsg+1, szMac, nInfoLen);
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;
}

void CFatSystem::IntoTheBaiduPage_WIFI(u8* pCmd, u8 ucLen)
{
	m_pFatApp->GoBaiduPageWifi(0x01);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::InquireWifiConntectStatus(u8* pCmd, u8 ucLen)
{
	u8 ucWifiConntectStatus = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, WIFI_CONNECT_STATUS, &ucWifiConntectStatus, &ucParamLen);
	m_pFatHal->Send_DriverACK_Data(ucWifiConntectStatus);
}

void CFatSystem::InquireWifiNetworkSignalStrength(u8* pCmd, u8 ucLen)
{
	short ucWifiNetworkSignal = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, NETWORK_SIGNAL_WIFI, (u8*)&ucWifiNetworkSignal, &ucParamLen);
	FLY_LOG(LOG_LV_DEBUG, "ucWifiNetworkSignal = %d", ucWifiNetworkSignal);
	u8 szWifiNetworkSignal[] = {'S', 0x00, 0x00};
	TransformIntegerToAcsii(szWifiNetworkSignal+1, ucWifiNetworkSignal, 10, 2);
	FLY_LOG(LOG_LV_DEBUG, "szWifiNetworkSignal = %s", szWifiNetworkSignal);
	m_pFatHal->SendResponseMsg(szWifiNetworkSignal,3);

}

void CFatSystem::Inquire4GNetworkSignalStrength(u8* pCmd, u8 ucLen)
{
	short uc4GNetworkSignal = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, NETWORK_SIGNAL_4G, (u8*)&uc4GNetworkSignal, &ucParamLen);
	FLY_LOG(LOG_LV_DEBUG, "uc4GNetworkSignal = %d", uc4GNetworkSignal);
	u8 sz4GNetworkSignal[] = {'S', 0x00, 0x00};
	TransformIntegerToAcsii(sz4GNetworkSignal+1, uc4GNetworkSignal, 10, 2);
	FLY_LOG(LOG_LV_DEBUG, "sz4GNetworkSignal = %s", sz4GNetworkSignal);
	m_pFatHal->SendResponseMsg(sz4GNetworkSignal,3);
}

void CFatSystem::IntoTheBaiduPage_4G(u8* pCmd, u8 ucLen)
{
	m_pFatApp->GoBaiduPage4G(0x01);
	m_pFatHal->Send_DriverACK();
} 

void CFatSystem::ResponseInfoSdMemoryUsage(u8* pCmd, u8 ucLen)
{
	char szMemoryUsageTotal[CMD_TO_INFORS_MAX_LEN];
	memset(szMemoryUsageTotal,0,sizeof(szMemoryUsageTotal));

	u8 szMemoryUsageSD1[CMD_TO_INFORS_MAX_LEN];
	memset(szMemoryUsageSD1,0,sizeof(szMemoryUsageSD1));
	u8 ucParamLen1 = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, MEMORY_USAGE_SD1, szMemoryUsageSD1, &ucParamLen1);

	u8 szMemoryUsageSD0[CMD_TO_INFORS_MAX_LEN];
	memset(szMemoryUsageSD0,0,sizeof(szMemoryUsageSD0));
	u8 ucParamLen0 = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, MEMORY_USAGE_SD0, szMemoryUsageSD0, &ucParamLen0);

	long lTotal = atol((char*)szMemoryUsageSD1) + atol((char*)szMemoryUsageSD0);
	sprintf(szMemoryUsageTotal,"%d",lTotal);
	int nInfoLen = strlen(szMemoryUsageTotal);
	
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		memcpy(pMsg+1, szMemoryUsageTotal, nInfoLen);
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;
}

void CFatSystem::ResponseInfoSdTheTotalSize(u8* pCmd, u8 ucLen)
{
	char szTheTotalSize[CMD_TO_INFORS_MAX_LEN];
	memset(szTheTotalSize,0,sizeof(szTheTotalSize));

	u8 szTotalSizeSD1[CMD_TO_INFORS_MAX_LEN];
	memset(szTotalSizeSD1,0,sizeof(szTotalSizeSD1));
	u8 ucParamLen1 = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, TOTAL_SIZE_SD1, szTotalSizeSD1, &ucParamLen1);

	u8 szTotalSizeSD0[CMD_TO_INFORS_MAX_LEN];
	memset(szTotalSizeSD0,0,sizeof(szTotalSizeSD0));
	u8 ucParamLen0 = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, TOTAL_SIZE_SD0, szTotalSizeSD0, &ucParamLen0);
	
	long lTotal = atol((char*)szTotalSizeSD1) + atol((char*)szTotalSizeSD0);
	sprintf(szTheTotalSize,"%d",lTotal);
	int nInfoLen = strlen(szTheTotalSize);
	
	u8* pMsg = new u8[nInfoLen+1];
	memset(pMsg, 0, nInfoLen+1);
	pMsg[0] = 'S';
	if(nInfoLen > 0){
		memcpy(pMsg+1, szTheTotalSize, nInfoLen);
	}
	FLY_LOG(LOG_LV_DEBUG, "pMsg = %s", pMsg);
	m_pFatHal->SendResponseMsg(pMsg, nInfoLen+1);
	delete[] pMsg;
	pMsg = NULL;

}

void CFatSystem::WithdrawTheBaiduPage_WIFI(u8* pCmd, u8 ucLen)
{
	m_pFatApp->GoBaiduPageWifi(0x00);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::ResponseWiFiWhetherAccessToTheInternet(u8* pCmd, u8 ucLen)
{
	u8 ucWifiNetwork_Status = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, NETWORK_WIFI_STATUS, &ucWifiNetwork_Status, &ucParamLen);
	m_pFatHal->Send_DriverACK_Data(ucWifiNetwork_Status);
}

void CFatSystem::WithdrawTheBaiduPage_4G(u8* pCmd, u8 ucLen)
{
	m_pFatApp->GoBaiduPage4G(0x00);
	m_pFatHal->Send_DriverACK();
}

void CFatSystem::Response4GWhetherAccessToTheInternet(u8* pCmd, u8 ucLen)
{
	u8 uc4GNetwork_Status = 0;
	u8 ucParamLen = 0;
	m_pFatModule->getOtherModuleParam(MODULE_ID_SERVICE, NETWORK_4G_STATUS, &uc4GNetwork_Status, &ucParamLen);
	m_pFatHal->Send_DriverACK_Data(uc4GNetwork_Status);
}





