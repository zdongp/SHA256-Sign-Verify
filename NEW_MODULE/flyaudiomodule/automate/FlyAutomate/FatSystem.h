#pragma once
#include "fly_log.h"

#define HALTOKEY_KEYVAL_SLEEP			0x01
#define SYS_SETUP_ON	0x01
#define SYS_SETUP_OFF	0x00
class CFatHal;
class CFatApp;
class CFatModule;
class CFatSystem
{
	typedef void (CFatSystem::*pFunc)(u8* pCmd, u8 ucLen);
public:
	CFatSystem(CFatHal* pFatHal, CFatApp* pFatApp, CFatModule* pFatModule);
	~CFatSystem(void);

private:
	CFatHal*			m_pFatHal;
	CFatApp*			m_pFatApp;
	CFatModule*	m_pFatModule;

	map<string, pFunc>mapCmdFunc;

public:
	void AnalyseFATCommand(u8* pCmd, u8 ucLen);

private:
	void ResponseFactoryPattern_Status(u8* pCmd, u8 ucLen);
	void ResponseHaveEnterAutomate(u8* pCmd, u8 ucLen);
	void EnterOrQuitStandby(u8* pCmd, u8 ucLen);
	void RestoreDefaults(u8* pCmd, u8 ucLen);
	void ReStartSystem(u8* pCmd, u8 ucLen);
	void ResponseInfoMCU(u8* pCmd, u8 ucLen);
	void ResponseInfoBarCode(u8* pCmd, u8 ucLen);
	void ResponseInfoBluetoothVersion(u8* pCmd, u8 ucLen);
	void ResponseInfoMEPG(u8* pCmd, u8 ucLen);
	void ResponseInfoFID( u8* pCmd, u8 ucLen );
	void ResponseGetBrakeCarStatus(u8* pCmd, u8 ucLen);
	void ResponseValueBattery(u8* pCmd, u8 ucLen);
	void SelectPrevSteeringWheel(u8* pCmd, u8 ucLen);
	void SelectNextSteeringWheel(u8* pCmd, u8 ucLen);
	void SelectAUXInputSource(u8* pCmd, u8 ucLen);
	void EnableBackCarVedio(u8* pCmd, u8 ucLen);
	void SelectLuminance(u8* pCmd, u8 ucLen);
	void ResponseValueLuminance(u8* pCmd, u8 ucLen);
	void ResponseAudioValueMax( u8* pCmd, u8 ucLen );
	void ResponseInfoIMEI( u8* pCmd, u8 ucLen );
	void ResponseInforBrakeStatusClose(u8* pCmd, u8 ucLen);
	void ResponseInforBrakeStatusOpen(u8* pCmd, u8 ucLen);


	void EnterCloseWifi(u8* pCmd, u8 ucLen);
	void EnterOpenWifi(u8* pCmd, u8 ucLen);
	void EnterClose4G(u8* pCmd, u8 ucLen);
	void EnterOpen4G(u8* pCmd, u8 ucLen);
	void ConnectWIFI(u8* pCmd, u8 ucLen);
	void IntoTheBaiduPage_WIFI(u8* pCmd, u8 ucLen);
	void InquireWifiConntectStatus(u8* pCmd, u8 ucLen);
	void InquireWifiNetworkSignalStrength(u8* pCmd, u8 ucLen);
	void Inquire4GNetworkSignalStrength(u8* pCmd, u8 ucLen);
	void IntoTheBaiduPage_4G(u8* pCmd, u8 ucLen);
	void ResponseInfoMAC(u8* pCmd, u8 ucLen);
	void ResponseInfoSdMemoryUsage(u8* pCmd, u8 ucLen);
	void ResponseInfoSdTheTotalSize(u8* pCmd, u8 ucLen);
	void WithdrawTheBaiduPage_WIFI(u8* pCmd, u8 ucLen);
	void ResponseWiFiWhetherAccessToTheInternet(u8* pCmd, u8 ucLen);
	void WithdrawTheBaiduPage_4G(u8* pCmd, u8 ucLen);
	void Response4GWhetherAccessToTheInternet(u8* pCmd, u8 ucLen);

};
