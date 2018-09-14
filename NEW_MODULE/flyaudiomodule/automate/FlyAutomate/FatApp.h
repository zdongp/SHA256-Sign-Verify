/*
	author: YanBin Deng
	  date: 2014/09/01  
*/
#pragma once
#include "FatParam.h"
#include "pageID.h"
#include "controlID.h"

class CFatModule;
class CFatHal;
class CFatParam;
class CFatApp : public CFlyApp
{
	SINGLETON_IMPLEMENT(CFatApp)
private:
	CFatApp(void);
public:
	virtual ~CFatApp(void);

public:
	void init(void);
	void initObject(CFlyApp* pFlyApp, CFlyHal* pFlyHal, CFlyModule* pFlyModule, CFlyParam* pFlyParam);
	void processMouseMsg(u32 id, E_MOUSE_STATUS e, u8 *p, u8 len);
	void SendMouseOperateToOtherModule(E_MOUSE_STATUS e, u8 arrivedModuleId, u32 u32_contrID);
	void SendMouseOperateToOtherModule(E_MOUSE_STATUS e, u8 arrivedModuleId, u32 u32_contrID,u8 u8_MouseStatus);
public:
	void GetIMEI();
	void GetCarMAC();
	void GetWifiConnectStatus();
	void GetWifiNetworksignalStrength();
	void Get4GNetworksignalStrength();
	void GetSd1Status();
	void GetSd1MemoryUsage();
	void GetSd1TheTotalSize();
	void GetSd0MemoryUsage();
	void GetSd0TheTotalSize();
	void control4G(u8 p);
	void controlWIFI(u8 p);
	void GoBaiduPageWifi(u8 p);
	void GoBaiduPage4G(u8 p);
	void ToUIcurIsAutomateMode(u8 p);
	void GetWifiWhetherInternetStatus();
	void Get4GWhetherInternetStatus();
private:
	CFatApp *m_pFatApp;
	CFatModule *m_pFatModule;
	CFatHal *m_pFatHal;
	CFatParam *m_pFatParam;
};

